/*
 * File:   ambient.c
 * Author: C16783
 *
 * Created on May 13, 2020, 11:56 AM
 */


#include "ambient.h"
#include "mcc_generated_files/adc/adc.h"

float Ambient_ReadSensor(void) {
    ADC_ConversionStart();
    while( 0 == ADC_IsConversionDone() );
    while( 0 == ADC_IsThresholdInterruptFlagSet() );
    return ADC_FilterValueGet();
}

float AmbientCompensation(void) {
    float Ambient_Raw, Ambient_Volt, Light_Intensity;
    Ambient_Raw = Ambient_ReadSensor();
    Ambient_Volt = (Ambient_Raw / ADCC_RESOLUTION)*(ADCC_POS_REFERENCE); // Calculate ADC voltage using conversion result;
    Light_Intensity = (POLY1_TERM1 * Ambient_Volt) + POLY1_TERM0; // Calculate ambient light intensity;
    return (Light_Intensity); // Return light intensity (uW/cm^2);
}