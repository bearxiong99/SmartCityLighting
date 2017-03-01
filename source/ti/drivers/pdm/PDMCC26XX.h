/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/** ============================================================================
 *  @file       PDMCC26XX.h
 *
 *  @brief      PDM driver implementation for a CC26XX PDM controller.
 *
 *  The PDM header file should be included in an application as follows:
 *  @code
 *  #include <ti/drivers/pdm/PDMCC26XX.h>
 *  @endcode
 *
 * # Overview #
 * This driver is written to be able to perform continuous audio streaming
 * of PDM data from a microphone. It also controls one DIO to be able
 * to turn on power to the microphone.
 *
 * This PDM driver performs two operations that requires processing
 * - PDM to PCM conversion
 * - PCM compression (optional)
 *
 * This driver is configured to process 256 bytes of PDM data provided by the I2S hardware module at a time, sampled at
 * 1.024 Mbps. The PDM driver consequently receives such a buffer approximately every 2ms.
 * A frame of ::PDMCC26XX_Params.retBufSizeInBytes PCM data bytes minus four metadata bytes is provided to the application
 * after being filled by all or part of one or more 64 byte buffers of PCM data derived from the 256 bytes of PDM data.
 * The resulting PCM frame provided to the application is a 16bit PCM signal sampled at 16kHz.
 *
 * The driver creates a separate task to run in.
 *
 * @note    The application must allow for the PDM driver task to run often enough to process the data received from
 *          I2S driver approximately every 2ms.
 *
 * The driver currently only samples on a single edge of the I2S clock.
 *
 * # General Behaviour #
 * Before using PDM on CC26XX:
 *   - The PDM driver is initialized by calling ::PDMCC26XX_init(). This should
 *     be done in main before BIOS_start() is called.
 *   - The PDM system dependencies are set by calling ::PDMCC26XX_open().
 *     The driver is also marked as taken. Prior to this the system should call ::PDMCC26XX_init().
 *     The driver also automatically allocates the first PDMCC26XX_pcmBuffer of the size
 *     specified by the application in ::PDMCC26XX_Params.retBufSizeInBytes.
 *     This call also reserves the pins for the microphone signal and power specified in the board file.
 *
 * While using PDM on CC26XX:
 *   - When PDMCC26XX_open() is called, the driver allocates one PCM buffer on the heap and the I2S module tries to allocate enough memory for its PDM buffers.
 *   - When PDMCC26XX_startStream() is called, the I2S driver starts processing the pdm stream,
 *     the PDM driver resets the internal state of the decimation filter, sets the driver to drop the first
 *     MAX(PDM_DECIMATION_STARTUP_DELAY_IN_SAMPLES, ::PDMCC26XX_Params.startupDelayWithClockInSamples),
 *     and resets the metaData (including the sequence number). The driver will keep allocating PDMCC26XX_pcmBuffers on the heap
 *     and keep them in a queue until they are requested by the application.
 *     From now on, callbacks are generated every time a buffer is ready; if callbacks are asked for.
 *   - Data is acquired by the application by calling ::PDMCC26XX_requestBuffer().
 *     After processing the buffer, the application is responsible for freeing the memory allocated
 *     for the buffer in a timely manner.
 *   - The stream is stopped when ::PDMCC26XX_stopStream() is called. Note that
 *     this is a blocking call that will wait until the I2S hardware has gracefully
 *     shut down. This will take at most 4ms, unless an error occurs.
 *     Any PCM buffers remaining must be released by the application as usual.
 *     The system is allowed to enter standby again after PDMCC26XX_stopStream() is called.
 *   - The memory held by the I2S module is freed upon calling PDMCC26XX_close(). Any completed PCM buffers must be processed and freed by the application.
 *
 * After PDM operation has ended:
 *   - Release system dependencies and free up all memory on the heap allocated for the PDM driver by calling PDMCC26XX_close().
 *
 * # Error Handling #
 *  The application is notified of errors via the registered callback function.
 *
 * ## Heap Full #
 *  If the application fails to consume PCM buffers fast enough and the heap is full
 *  when driver tries to allocate a new buffer, the driver will drop all new incoming data until a buffer
 *  can be allocated to store it. Data is dropped one PCM data buffer at a time , even though it is streamed
 *  into the device and copied into the buffer in smaller chunks.
 *  This is done to keep the data expected in any buffer in sync with the sequence number
 *  of the buffer that keeps incrementing even when the buffer is dopped. The application may keep track
 *  of lost frames by comparing sequence numbers.
 *
 *  Hence, the PDM stream will never have a buffer overflow, but if the memory available in the
 *  heap is too low it may lose frames because because there is nowhere to put the incoming
 *
 *  If the heap frees up again and the PDM task runs, it will automatically resume normal operation again.
 *  The only application-observable difference is the incremented version number.
 *
 * ## PDM Task Not Serviced In Time #
 *  The application must permit the PDM task to run often enough that it can process a PDM buffer every 2ms on average.
 *  If the application requires a larger contiguous segment of processing time, the I2S hwi may run out of empty buffers to fill
 *  with new PDM data. When the I2S driver runs out of empty PDM buffers it will pop a buffer from the full buffer queue and overwrite
 *  its old data. The I2S driver notifies the PDM driver that it has dropped a PDM buffer. Once it runs again, the PDM driver will drop
 *  enough additional PCM samples such that the sequence numbers of the PCM buffers remain aligned with the data in the audio stream.
 *  The latency between when the PDM task was last serviced and when it must be serviced again to avoid losing data is specified by
 *  ::PDMCC26XX_Params::pdmBufferQueueDepth. This permitted latency increases by 2ms for each increment of pdmBufferQueueDepth.
 *
 * ## PDMCC26XX_open Failing #
 *  ::PDMCC26XX_open() returns NULL and rolls back all prior parts of the initialisation if any part of the initialisation fails.
 *  The following can cause ::PDMCC26XX_open() to fail:
 *      - The driver is already open
 *      - The heap is full when the application calls ::PDMCC26XX_open()
 *      - The PIN driver could not allocate the requested pins for the PDM driver
 *      - The I2S driver failed to initialise
 *
 * ## PDMCC26XX_startStream Failing #
 *  ::PDMCC26XX_startStream() returns false if it fails.
 *  The following can cause ::PDMCC26XX_startStream() to fail:
 *      - The driver is already streaming
 *      - The I2S driver could not successfully start reading the pdm stream
 *      - The I2S driver could not allocate enough memory for the specified
 *        number of PDM buffers
 *
 * ## PDMCC26XX_stopStream Failing #
 *  ::PDMCC26XX_stopStream() returns false if it fails.
 *  The following can cause ::PDMCC26XX_stopStream() to fail:
 *      - The driver is not currently streaming
 *
 * # Power Management #
 *  The PDMCC26XX driver sets a power constraint while streaming to keep
 *  the device out of standby. When the stream has ended, the power constraint
 *  is released.
 *
 *  The following statements are valid:
 *    - After ::PDMCC26XX_open(): the device is still allowed to enter standby.
 *    - During ::PDMCC26XX_startStream(): the device cannot enter standby.
 *    - After ::PDMCC26XX_stopStream() succeeds: the device can enter standby.
 *    - If ::PDMCC26XX_close() is called: the device can enter standby.
 *
 *
 * # Supported Functions #
 *  | API function              | Description                                           |
 *  |---------------------------|-------------------------------------------------------|
 *  | PDMCC26XX_init()          | Initialize PDM driver                                 |
 *  | PDMCC26XX_open()          | Set system dependencies, configure pins               |
 *  | PDMCC26XX_startStream()   | Turn on mic, start stream and prevent standby         |
 *  | PDMCC26XX_stopStream()    | Stop stream and release standby hold, turn off mic    |
 *  | PDMCC26XX_requestBuffer() | Request a buffer from the driver                      |
 *  | PDMCC26XX_close()         | Disable HW and release system dependencies            |
 *
 * # Standard Use Case #
 *  The standard use case involves calling PDMCC26XX_open() once and calling PDMCC26XX_startStream() and PDMCC26XX_stopStream()
 *  to start and stop the stream as needed. PDMCC26XX_close() is called when the PDM driver will no longer be needed again.
 *  In order for the PDM driver task to run, the application pends on a semaphore that is posted in the ::PDMCC26XX_Params::callbackFxn.
 *  In this example, the application requests 128 buffers. In a real application, the process of pending on a semaphore, requesting a buffer,
 *  and freeing it would be repeated as often as required by the use case before stopping the stream.
 *  @code
 *
 *  void bufRdy_callback(PDMCC26XX_Handle handle, PDMCC26XX_StreamNotification *pStreamNotification)
 *  {
 *      PDMCC26XX_Status streamStatus = pStreamNotification->status;
 *
 *      if (streamStatus == PDMCC26XX_STREAM_BLOCK_READY || streamStatus == PDMCC26XX_STREAM_BLOCK_READY_BUT_PDM_OVERFLOW){
 *          Semaphore_post(Semaphore_handle(&bufferReadySemaphore));
 *      }
 *      else {
 *          // Handle the error
 *      }
 *  }
 *
 *  static void applicationTask(UArg a0, UArg a1){
 *      Semaphore_Params semParams;
 *      PDMCC26XX_BufferRequest bufferRequest;
 *      PDMCC26XX_Params pdmParams;
 *      const uint16_t returnBufferSize = 64;
 *      const uint8_t numberOfPcmBuffersToRequest = 128;
 *
 *      // Initialize semaphore
 *      Semaphore_Params_init(&semParams);
 *      semParams.mode = Semaphore_Mode_BINARY;
 *      Semaphore_construct(&bufferReadySemaphore, 0, &semParams);
 *
 *      // Set up parameters for PDM streaming with compression
 *      PDMCC26XX_Params_init(&pdmParams);
 *      pdmParams.callbackFxn = bufRdy_callback;
 *      pdmParams.micPowerActiveHigh = true;
 *      pdmParams.applyCompression = true;
 *      pdmParams.retBufSizeInBytes = returnBufferSize;
 *      pdmParams.mallocFxn = &malloc;
 *      pdmParams.freeFxn = &free;
 *
 *      // Try to open the PDM driver
 *      if(pdmHandle = PDMCC26XX_open(&pdmParams) == NULL){
 *          // Handle PDMCC26XX_open() failing
 *      }
 *
 *      // Try to start streaming
 *      if(PDMCC26XX_startStream(pdmHandle)){
 *          uint8_t pcmBuffersRequestedSoFar;
 *
 *          // Request numberOfPcmBuffersToRequest buffers and then stop the stream
 *          for (pcmBuffersRequestedSoFar = 0; pcmBuffersRequestedSoFar < numberOfPcmBuffersToRequest; pcmBuffersRequestedSoFar++){
 *              // Pend on the semaphore until a buffer is available from the PDM driver
 *              Semaphore_pend(Semaphore_handle(&bufferReadySemaphore), BIOS_WAIT_FOREVER);
 *
 *              // Now request a buffer as it was indicated that one is available
 *              PDMCC26XX_requestBuffer(pdmHandle, &bufferRequest);
 *
 *              // Process bufferRequest
 *
 *              // Free the buffer
 *              my_free(bufferRequest.buffer, returnBufferSize);
 *          }
 *
 *          // Try to stop the stream
 *          if(!PDMCC26XX_stopStream(pdmHandle)){
 *              // Handle PDMCC26XX_stopStream() failing
 *          }
 *      }
 *      else{
 *          // Handle PDMCC26XX_startStream() failing
 *      }
 *  }
 *
 *  @endcode
 *
 *  # Instrumentation #
 *
 *  The PDM driver interface produces log statements if instrumentation is
 *  enabled.
 *
 *  | Instrumentation           | Description                                                                           |
 *  |---------------------------|---------------------------------------------------------------------------------------|
 *  | Diags_USER1               | Logs the start and end of each API call of the PDM driver and progress through events |
 *  | Diags_USER2               | Logs occurances in the I2S sub-module  of the PDM driver                              |
 *  | Warnings                  | Logs unexpected events such as initialisations or memory allocations failing          |
 *
 *  ============================================================================
 *
 *
 */

#ifndef ti_drivers_pdm_PDMCC26XX__include
#define ti_drivers_pdm_PDMCC26XX__include

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * The following allows this header file to be included in an application file
 * which also includes ti/sysbios/hal/Hwi.h.
 */
#define ti_sysbios_family_arm_m3_Hwi__nolocalnames

#include <ti/sysbios/knl/Semaphore.h>
#include <ti/drivers/PIN.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26XX.h>

/*********************************************************************
 * CONSTANTS
 */

/*! Defines TI-RTOS stack size allocation. It is a conservative estimate.
 *  Change this to save a few bytes of RAM on stack allocation. The stack usage
 *  is independent of the PCM return buffer size specified by the application.
 *  When using logging, increase this value.
 *  This value is also dependent on the malloc and free function implementations
 *  provided by the application as both are called from PDM task context.
 */
#ifndef PDM_TASK_STACK_SIZE
#define PDM_TASK_STACK_SIZE             550
#endif

/*! Uncompressed PCM sample size in bits @note Internal use only since only 16 bits are supported */
#define PCM_SAMPLE_SIZE                 16 // Only 16 bits supported for now

/*! Compression rate if compression is enabled */
#define PCM_COMPRESSION_RATE            4

/*! Minimum number of PDM buffers required by the driver to safely use the I2S module */
#define MINIMUM_PDM_BUFFER_QUEUE_DEPTH  3

/*! PCM data metadata size. When a buffer is requested there will be metadata
 *  prepended. In other words the pointer returned points to the metadata header.
 *  Depending on the mode, this contains different information. The first byte is always
 *  an 8-bit sequence number. */
#define PCM_METADATA_SIZE               sizeof(PDMCC26XX_metaData)

/*********************************************************************
 * TYPEDEFS
 */

/*! @brief Metadata associated with an array of PCM data */
typedef struct {
    uint8_t seqNum;     /*!< Sequence number of a ::PDMCC26XX_pcmBuffer */
    int8_t si;          /*!< Step index of a ::PDMCC26XX_pcmBuffer */
    int16_t pv;         /*!< Next predicted value of a ::PDMCC26XX_pcmBuffer */
} PDMCC26XX_metaData;

/*! @brief PCM buffer pointed to in a PDMCC26XX_BufferRequest */
typedef struct {
    PDMCC26XX_metaData metaData;    /*!< Metadata for the buffer */
    uint8_t pBuffer[];              /*!< PCM data buffer */
} PDMCC26XX_pcmBuffer;

/*!
 *  @brief
 *  PDMCC26XX_MallocFxn is a function pointer for the malloc function to
 *  be used by the driver.
 */
typedef void *(*PDMCC26XX_MallocFxn)(size_t memSize);

/*!
 *  @brief
 *  PDMCC26XX_FreeFxn is a function pointer for the free function to
 *  be used by the driver. This is needed for memory clean up, if something goes
 *  wrong.
 */
typedef void (*PDMCC26XX_FreeFxn)(void *ptr, size_t memSize);

/*!
 *  @brief
 *  The PDMCC26XX_Config structure contains a set of pointers used to
 *  characterize the PDMCC26XX driver implementation.
 */
typedef struct PDMCC26XX_Config {
    /*! Pointer to a driver specific data object */
    void                        *object;

    /*! Pointer to a driver specific hardware attributes structure */
    void                const   *hwAttrs;
} PDMCC26XX_Config;

/*! PDMCC26XX_Config struct defined in the board file */
extern const PDMCC26XX_Config PDMCC26XX_config[];

/*!
 *  @brief  PDMCC26XX Hardware attributes
 *
 *  These fields are used by the PDM driver
 *
 */
typedef struct PDMCC26XX_HWAttrs {
    /*! Microphone power pin */
    PIN_Id           micPower;
    /*! PDM task priority pin */
    int              taskPriority;
} PDMCC26XX_HWAttrs;

/*!
 *  @brief      A handle that is returned from a PDMCC26XX_open() call.
 */
typedef struct PDMCC26XX_Config *PDMCC26XX_Handle;

/*!
 *  @brief      Status codes that are set by the PDM driver.
 */
typedef enum PDMCC26XX_Status {
    PDMCC26XX_STREAM_IDLE,              /*!< Idle mode. Stream not started */
    PDMCC26XX_STREAM_BLOCK_READY,       /*!< Buffer ready */
    PDMCC26XX_STREAM_BLOCK_READY_BUT_PDM_OVERFLOW,      /*!< Buffer ready, but
                                         * the I2S module has had to drop data . */
    PDMCC26XX_STREAM_ERROR,             /*!< The I2S module encountered a hardware error. Likely
                                         * because the target address for the I2S DMA was NULL
                                         */
    PDMCC26XX_STREAM_STOPPING,          /*!< A stop was requested and this is the
                                         * last buffer to be produced.*/
    PDMCC26XX_STREAM_STOPPED,           /*!< Unused */
    PDMCC26XX_STREAM_FAILED_TO_STOP     /*!< Buffer ready */
} PDMCC26XX_Status;

/*!
 *  @brief      Predefined gain settings.
 *
 *  Gain is controlled by modifying the first coefficient of the PDM filter.
 *  Use these defines to get correct gain setting. All these values are in
 *  dB. Default filter will add 12dB gain. In fact this is not an amplification,
 *  this setting uses all the information in the PDM samples, so if use case
 *  allows it this will have the least compromised range. PDM2PCM algotrithm
 *  returns false if any of the samples decimated goes above 2^16 - 1, i.e.
 *  the sample clipped during decimation. This information can be used for
 *  automatic gain control.
 */
typedef enum PDMCC26XX_Gain {
    PDMCC26XX_GAIN_24,  /*!< 24dB gain */
    PDMCC26XX_GAIN_18,  /*!< 18dB gain */
    PDMCC26XX_GAIN_12,  /*!< 12dB gain. Default */
    PDMCC26XX_GAIN_6,   /*!<  6dB gain */
    PDMCC26XX_GAIN_0,   /*!<  0dB gain */
    PDMCC26XX_GAIN_END  /*!< Internal use only */
} PDMCC26XX_Gain;

/*!
 *  @brief
 *  A ::PDMCC26XX_StreamNotification data structure is used with PDMCC26XX_CallbackFxn().
 *  Provides notification about available buffers and potential errors
 */
typedef struct PDMCC26XX_StreamNotification {
    void      *arg;             /*!< Argument to be passed to the callback function */
    PDMCC26XX_Status status;    /*!< Status code set by PDMCC26XX driver */
} PDMCC26XX_StreamNotification;

/*!
 *  @brief      The definition of a callback function used when buffers are ready
 *
 *  @param      PDMCC26XX_Handle          PDMCC26XX_Handle
 */
typedef void (*PDMCC26XX_CallbackFxn) (PDMCC26XX_Handle handle, PDMCC26XX_StreamNotification *streamNotification);

/*!
 *  @brief
 *  A ::PDMCC26XX_BufferRequest data structure is used with PDMCC26XX_requestBuffer().
 *
 *  buffer is a pointer to the requested buffer. It is NULL if no buffer is available.
 *  Each buffer contains a metadata header of size PCM_METADATA_SIZE. The first
 *  byte of the metadata is always an 8 bit sequence number. The other bytes
 *  depends on mode.
 *
 *  Mode                | Interpretation of bufferIn being NULL after returning |
 *  --------------------|-------------------------------------------------------|
 *  Blocking mode       | Request timed out and still no buffer available       |
 *  Non-Blocking mode   | No buffer available                                   |
 *
 */
typedef struct PDMCC26XX_BufferRequest {
    PDMCC26XX_pcmBuffer      *buffer;           /*!< Pointer to requested buffer. Note that this
                                                 * includes PCM_METADATA_SIZE bytes of metadata
                                                 * as a header */
    PDMCC26XX_Status status;                    /*!< Status code set by PDMCC26XX_requestBuffer */
} PDMCC26XX_BufferRequest;

/*!
 *  @brief
 *  PDMCC26XX Parameters are used to with the PDMCC26XX_open() call. Default values for
 *  these parameters are set using PDMCC26XX_Params_init().
 *
 *  @sa     PDMCC26XX_Params_init
 */
typedef struct PDMCC26XX_Params {
    /* PDM control variables */
    bool                    useDefaultFilter;       /*!< Set to TRUE to apply default filter. Set to FALSE to apply
                                                     * PDMCC26XX_Params::decimationFilter.
                                                     */
    bool                    micPowerActiveHigh;     /*!< Set to TRUE if setting the GPIO high powers the microphone */
    bool                    applyCompression;       /*!< Set to TRUE to apply compression. Setting it to FALSE allows
                                                     * user to apply own compression scheme.
                                                     */
    uint8_t                 pdmBufferQueueDepth;    /*! PDM buffer queue depth in number of blocks. We assume that we will be able to
                                                     *  consume approximately one buffer per 2ms. This allows us to use the minium
                                                     *  number of blocks (3) for the PDMCC26XX driver.
                                                     *  If the application can not service the PDM task within the 2ms time window, increase this value
                                                     *  to permit more latency in processing incoming PDM data at the cost of increased
                                                     *  RAM useage.
                                                     */
    uint16_t                retBufSizeInBytes;      /*!< Size of returned buffers. It is not reccomended to make this value
                                                     *   less than 64, the driver will not crash, but the equence numbers may
                                                     *   become unaligned with the data in the buffer. */
    int32_t                 *decimationFilter;      /*!< Filter that is applied if
                                                     * PDMCC26XX_Params::useDefaultFilter is
                                                     * set to FALSE
                                                     */
    uint32_t                startupDelayWithClockInSamples; /*!< Some digital microphones have a startup delay.
                                                             * Set the number of samples to discard after powering the microphone
                                                             * starting to clock in data.
                                                             */
    PDMCC26XX_CallbackFxn   callbackFxn;            /*!< Callback function pointer */
    PDMCC26XX_Gain          micGain;                /*!< Microphone gain */
    PDMCC26XX_MallocFxn     mallocFxn;              /*!< Malloc function pointer */
    PDMCC26XX_FreeFxn       freeFxn;                /*!< Free function pointer */
    uintptr_t               custom;                 /*!< Custom argument used by driver implementation */
} PDMCC26XX_Params;

/*!
 *  @brief  PDMCC26XX Object
 *
 *  The application must not access any member variables of this structure!
 */
typedef struct PDMCC26XX_Object {
    /* PDM control variables */
    bool                            useDefaultFilter;       /*!< Set to TRUE to apply default
                                                             * filter. Set to FALSE to apply
                                                             * PDMCC26XX_Params::decimationFilter.
                                                             */
    bool                            streamStarted;          /*!< Stream started flag */
    bool                            micPowerActiveHigh;     /*!< Set to TRUE if setting the GPIO high powers the microphone */
    bool                            applyCompression;       /*!< Set to TRUE to apply compression. Setting it to FALSE allows
                                                             * user to apply own compression scheme.
                                                             */
    bool                            isOpen;                 /*!< Has the object been opened */
    uint16_t                        retBufSizeInBytes;      /*!< Size of returned buffers */
    uint16_t                        pcmBufferSizeInBytes;   /*!< Size of the pcm buffer inside the returnBuffer is equal to retBufSizeInBytes - PCM_METADATA_SIZE */
    uint32_t                        startupDelayWithClockInSamples; /*!< Some digital microphones have a startup delay.
                                                                     * Set the number of samples to discard after powering the microphone
                                                                     * starting to clock in data.
                                                                     */
    int32_t                         *decimationFilter;      /*!< Filter that is applied if PDMCC26XX_Params::decimationFilter is
                                                             * set to FALSE
                                                             */
    PDMCC26XX_StreamNotification    *streamNotification;    /*!< Stream state variable */
    PDMCC26XX_Gain                  micGain;                /*!< Microphone gain */
    PDMCC26XX_CallbackFxn           callbackFxn;            /*!< Callback function pointer */
    PDMCC26XX_MallocFxn             mallocFxn;              /*!< Malloc function pointer */
    PDMCC26XX_FreeFxn               freeFxn;                /*!< Free function pointer */
    PIN_State                       pinState;               /*!< Pin driver state object */
    PIN_Handle                      pinHandle;              /*!< Pin driver handle */
    ti_sysbios_family_arm_m3_Hwi_Struct hwi;                /*!< Hwi object handle */
} PDMCC26XX_Object;

/*!
 *  @brief PDM CC26XX initialization
 *
 */
extern void PDMCC26XX_init(PDMCC26XX_Handle handle);

/*!
 *  @brief  Function to initialize the CC26XX PDM peripheral specified by the
 *          particular handle. The parameter specifies which mode the PDM
 *          will operate.
 *
 *  The function will set a dependency on the PDM module, which in turn powers up the module and enables the clock.
 *  IOs are also allocated, however the PDM driver will not begin streaming audio until PDMCC26XX_startStream() is called.
 *
 *  @pre    PDM controller has been initialized
 *
 *  @param  params        Pointer to a parameter block. Will use default parameters if NULL
 *
 *  @return A PDMCC26XX_Handle on success or a NULL on an error or if it has been
 *          already opened
 *
 *  @sa     PDMCC26XX_close()
 */
extern PDMCC26XX_Handle  PDMCC26XX_open(PDMCC26XX_Params *params);

/*!
 *  @brief  Function to close a given CC26XX PDM peripheral specified by the
 *          PDM handle.
 *
 *  Posts an event that shuts down the I2S hardware, frees all memory used by the driver on the heap,
 *  releases the pins back to the PIN driver, and releases the dependency on the corresponding power domain.
 *
 *  @pre    PDMCC26XX_open() has to be called first.
 *
 *  @post   The PDM task must be allowed to run to synchronously shut down the driver
 *
 *  @param  handle  A PDMCC26XX_Handle returned from PDMCC26XX_open()
 *
 *  @sa     PDMCC26XX_open
 */
extern void PDMCC26XX_close(PDMCC26XX_Handle handle);

/*!
 *  @brief  Function to start streaming PDM data.
 *
 *  Posts an event that tells the I2S hardware to start streaming and the PDM task to start processing incoming data.
 *
 *  @pre    PDMCC26XX_open() has to be called first.
 *
 *  @post   The PDM task must be allowed to run (by e.g. pending on a semaphore in the application task)
 *          to process incoming PDM data from the I2S module.
 *
 *  @param  handle A PDM handle returned from PDMCC26XX_open()
 *
 *  @return true if transfer is successful and false if not
 *
 *  @sa     PDMCC26XX_open(), PDMCC26XX_stopStream()
 */
extern bool PDMCC26XX_startStream(PDMCC26XX_Handle handle);

/*!
 *  @brief  Function to stop streaming PDM data.
 *
 *  Blocks while the I2S module shuts down gracefully. Subsequently posts an event to let the PDM task process any remaining data.
 *
 *  @pre    PDMCC26XX_startStream() has to be called first.
 *
 *  @param  handle A PDM handle returned from PDMCC26XX_open()
 *
 *  @return True if stream stopped successfully and false if not
 *
 *  @post   Process all available PCM buffers by calling PDMCC26XX_requestBuffer() until it returns false.
 *          Otherwise, the available PCM buffers will take up space on the heap until PDMCC26XX_close() or PDMCC26XX_startStream() are called.
 *
 *  @sa     PDMCC26XX_open(), PDMCC26XX_startStream()
 */
extern bool PDMCC26XX_stopStream(PDMCC26XX_Handle handle);

/*!
 *  @brief  Function for requesting buffer.
 *
 *  PDMCC26XX_requestBuffer returns immediately even if no buffer is available.
 *  The caller is notified through events each time a buffer is available.
 *  However, more than one buffer may be available. Hence, the caller should
 *  request even without notification if the caller is ready to process.
 *
 *  @pre    PDMCC26XX_open() and PDMCC26XX_startStream() has to be called first.
 *
 *  @param  handle A PDM handle returned from PDMCC26XX_open()
 *
 *  @param  *bufferRequest Pointer to PDMCC26XX_BufferRequest struct
 *
 *  @return True if request is successful and false if not
 *
 *  @sa     PDMCC26XX_open(), PDMCC26XX_startStream()
 */
extern bool PDMCC26XX_requestBuffer(PDMCC26XX_Handle handle, PDMCC26XX_BufferRequest *bufferRequest);

/*
 * ======== PDMCC26XX_Params_init ========
 * @brief   Function for initialising a PDMCC26XX_Params instance to its default value
 *
 * @param   params Pointer to a set of uninitialised params
 *
 */
extern void PDMCC26XX_Params_init(PDMCC26XX_Params *params);


/* Do not interfere with the app if they include the family Hwi module */
#undef ti_sysbios_family_arm_m3_Hwi__nolocalnames

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_pdm_PDMCC26XX__include */
