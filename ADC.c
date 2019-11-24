/*
 * File:   ADC.c
 * Author: Fernando_RF
 *
 * Created on 24 de Novembro de 2019, 18:05
 */


#include "Config.h" 
#include "displayLCD.h"
#include "Fuel_Gauge.h"
#include "ADC.h"


void ADCRead(void)
{
    ADCON0bits.GO = 1;              // Inicia Conversão A/D
    __delay_ms(10);
    if(ADCON0bits.GO_DONE == 0)
    {
        valorADC = (ADRESH<<8)+ADRESL; // Monta uma word  
    }
}