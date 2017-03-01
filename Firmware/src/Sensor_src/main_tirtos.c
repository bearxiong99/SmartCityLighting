/*
 * Copyright (c) 2016, Texas Instruments Incorporated
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

/*
 *  ======== main_tirtos.c ========
 */
#include <stdint.h>

/* POSIX Header files */
#include <pthread.h>

/* RTOS header files */
#include <ti/sysbios/BIOS.h>

/* Driver header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
/* Example/Board Header files */
#include "Board.h"

extern void *temperatureThread(void *arg0);
extern void *consoleThread(void *arg0);
extern void *sensor_thread(void *arg0);
extern void *sensor_light2(void *arg0);
extern void *Hall_Effect_Thread(void *arg0);
extern void *Motion_Thread(void *arg0);
/* Stack size in bytes */
#define THREADSTACKSIZE    768

/*
 *  ======== main ========
 */
int main(void)
{
    pthread_t           thread;
    pthread_attr_t      pAttrs;
    struct sched_param  priParam;
    int                 retc;
    int                 detachState;

    /* Call driver init functions */
    Board_initGeneral();


    /* Set priority and stack size attributes */
    pthread_attr_init(&pAttrs);
    priParam.sched_priority = 1;

    detachState = PTHREAD_CREATE_DETACHED;
    retc = pthread_attr_setdetachstate(&pAttrs, detachState);
    if (retc != 0) {
        /* pthread_attr_setdetachstate() failed */
        while (1);
    }

    pthread_attr_setschedparam(&pAttrs, &priParam);

    retc |= pthread_attr_setstacksize(&pAttrs, THREADSTACKSIZE);
    if (retc != 0) {
        /* pthread_attr_setstacksize() failed */
        while (1);
    }

/*    retc = pthread_create(&thread, &pAttrs, consoleThread, NULL);
    if (retc != 0) {*/
        /* pthread_create() failed */
        /*while (1);
    }
*/
    /*
     *  Let's make the temperature thread a higher priority .
     *  Higher number means higher priority in TI-RTOS.
     */
    priParam.sched_priority = 1;
    pthread_attr_setschedparam(&pAttrs, &priParam);

    //retc = pthread_create(&thread, &pAttrs, temperatureThread, NULL);
    //if (retc != 0) {
        /* pthread_create() failed */
      //  while (1);
    //}
    //priParam.sched_priority = 2;

    retc = pthread_create(&thread, &pAttrs, sensor_light2, NULL);
        if (retc != 0) {
            /* pthread_create() failed */
            while (1);
        }
    //retc = pthread_create(&thread, &pAttrs, Motion_Thread, NULL);
    //retc = pthread_create(&thread, &pAttrs, Hall_Effect_Thread, NULL);
    /* Initialize the GPIO since multiple threads are using it */
    GPIO_init();
    I2C_init();
    ADC_init();
    /* Start the TI-RTOS scheduler */
    BIOS_start();

    return (0);
}
