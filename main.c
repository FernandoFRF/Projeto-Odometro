/*
 * File:   main.c
 * Author: FernandoRF
 *
 * Created on 5 de Novembro de 2019, 20:48
 */

#include "Config.h"
#include "displayLCD.h"
#include "EEPROM.h"  
#include "Odometro_Total_Parcial.h"
#include "Fuel_Gauge.h"
#include "ADC.h"

/*Declaração de Prototipos de Funções*/

void initInterrupt(void);
void initHw(void);
void display(void);

void interrupt isr(void){ 
    if ((PIR1bits.CCP1IF) && (PIE1bits.CCP1IE)){
        bordaParcial++;
        bordaTotal++;
        if (bordaParcial == 500){
            atualizaOdoParcial = 1;
            bordaParcial = 0;
        }
        if (bordaTotal == 5000){
            atualizaOdoTotal = 1;
            bordaTotal = 0;
        }
        PIR1bits.CCP1IF = 0; //"reseta" o vetor de interrupcao CCP1 p/ pronto prox.
    }
}


void main(void){
    ConfiguraLCD();
    initInterrupt();
    initHw();
    Init_EEPROM();
    display();
    
    while (1)
    {
        odometroTotal();
        odometroParcial();
        //resetodoparcial
        Combustivel();
    }
}


void initInterrupt(void){
    INTCON  = 0b11100000;
    INTCON2 = 0b10000000;
    INTCON3 = 0b00000000;
    CCP1CON = 0b00000101;
    PIR1    = 0b00000000;
    PIR2    = 0b00000000;
    PIE1    = 0b00000100;
    PIE2    = 0b00000000;
    IPR1    = 0b00000000;
    IPR2    = 0b00000000;
    RCON    = 0b00000000;
}
void initHw(void){
    /* Configura todos os ports como saida*/
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISCbits.RC2 = 1;
    TRISD  = 0x00;
    TRISE = 0x0F;
    
    ADCON0 = 0b00000001;
    ADCON1 = 0b00001101; // pinos AN0 e AN1 como analogico e o resto digital (bits 3~0 = '1101')
    ADCON2 = 0b10000100; // justificado a direita (ADFM-bit 7='1')
    
    PORTEbits.RE0 = 0;

     /*coloca em nivel "0" todos os pinos*/
    LATA = 0x00;
    LATB = 0x00;
    LATD = 0x00;
    
    T0CON   = 0b01000101;   // Configura Timer 0
    CCP1CON = 0b00000101;   // Configura meu CCP para captura de borda de subida
    T1CON   = 0b01000100;   // Configura Timer 1
    T3CONbits.T3CCP1 = 0;   // Configura o valor a ser registrado do Timer 1
    INTCONbits.GIE = 1;     // Habilita interrupção global
    INTCONbits.PEIE = 1;    // Habilita interrupção periférica
}

void display(void){
    PosicaoCursorLCD(1, 7);
    EscreveFraseRamLCD(odoTotal);
    PosicaoCursorLCD(2, 7);
    EscreveFraseRamLCD(odoParcial);
    PosicaoCursorLCD(1, 14);
    EscreveFraseRamLCD("Km");
    PosicaoCursorLCD(2, 14);
    EscreveFraseRamLCD("Km");
}