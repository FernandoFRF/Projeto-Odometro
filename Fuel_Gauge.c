/*
 * File:   Fuel_Gauge.c
 * Author: Fernando_RF
 *
 * Created on 24 de Novembro de 2019, 18:04
 */


#include "Config.h" 
#include "displayLCD.h"
#include "Fuel_Gauge.h"
#include "ADC.h"


void Combustivel(void) {
    while(primeiroFiltro == 1) {
        for(primeiroFiltro = 0; primeiroFiltro <= 9; primeiroFiltro ++) {
            TensaoBateria();
            ValorCombustivel();
        }
    
        primeiroFiltro = 0;
    }
    
   if(tempoCombustivel >= 500) {   
        TensaoBateria();
        ValorCombustivel();
        valorADCMedia = (combArray[0] + combArray[1] + combArray[2] + combArray[3] + combArray[4] + combArray[5] + combArray[6] + combArray[7] + combArray[8] + combArray[9]) / 10; 
    
        if(valorADCMedia <= 50) {
             PORTB = 0b00000000;
        }
        if(valorADCMedia > 50 && valorADCMedia <= 85) {
             PORTB = 0b010000000;
        }
        if(valorADCMedia > 85 && valorADCMedia <= 120) {
             PORTB = 0b11000000;
        }
        if(valorADCMedia > 120 && valorADCMedia<= 155) {
             PORTB = 0b11100000;
        }
        if(valorADCMedia > 155 && valorADCMedia <= 190) {
             PORTB = 0b11110000;
        }
        if(valorADCMedia > 190 && valorADCMedia <= 225) {
             PORTB = 0b11111000;
        }
        if(valorADCMedia > 225 && valorADCMedia <= 268) {
             PORTB = 0b11111100;
        }
        if(valorADCMedia > 268 && valorADCMedia <= 370) {
             PORTB = 0b11111110;
        }
        if(valorADCMedia > 370) {
             PORTB = 0b11111111;
        }
        if(valorADCMedia> 345) {
             reserva = 1;
        }
        else {
            reserva = 0;
            PORTCbits.RC0 = 1;
        }
     
        tempoCombustivel = 0;
     
    }
   
    if(countLed >= 1000 && reserva ==1) {
        PORTCbits.RC0 = ~PORTCbits.RC0; 
        countLed = 0;
    }
   
  
}

void TensaoBateria() {
    ADCON0bits.CHS = 1 ; // Seleciona o Canal 1
    ADCRead();
     
    //6v 300= 0 / 8v 400 = 1,33 / 10v 500 = 1,66 / 12v 600 = 1,99 / 14v 700 = 2,33 / 16v 800 = 2,66 
    porcentagemTensao = 333 * valorADC; //= 333 * 600 = 199800   
}
    
void ValorCombustivel() {
    ADCON0bits.CHS = 0; // Seleciona o Canal 0
    ADCRead();

    valorADC = ((valorADC * 100000) / porcentagemTensao);
    
    combArray[numeroC] = valorADC;
    numeroC ++;
              
    if(numeroC == 10){
    numeroC = 0;
      }
     
}
