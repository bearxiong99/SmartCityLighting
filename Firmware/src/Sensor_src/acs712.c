/*
 * acs712.c
 *
 *  Created on: Feb 27, 2017
 *      Author: curew
 */


#include "acs712.h"

ADC_Handle a_init(void) {
    ADC_Handle adc;
    ADC_Params ad_params;
    ADC_Params_init(&ad_params);
    adc = ADC_open(Board_ADC0, &ad_params);
    return adc;
}

/*Handle GPIO Signal*/
uint16_t Check_Light(ADC_Handle adc) {
    uint16_t adc_val = 0;
    if (ADC_convert(adc, &adc_val) == ADC_STATUS_SUCCESS) {
        return adc_val;
    } else {
        return 0;
    }
}
