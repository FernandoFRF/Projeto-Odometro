/*
 * File:   Odometro_Total_Parcial.c
 * Author: FernandoRF   
 *
 * Created on 5 de Novembro de 2019, 20:47
 */


#include "Config.h"
#include "displayLCD.h"
#include "EEPROM.h"    
#include "Odometro_Total_Parcial.h"




void odometroTotal(void){
    
    if (atualizaOdoTotal)
    {
        for(unsigned char i = 0x00, j = 0x05; i < 0x06, j > 0x06; i++, j--){
            unsigned char memoria = 0x10;
            odoTotal[j] = EEPROM_ReadByte (memoria + i);   
        }
        
        odoTotal[5]++;
        if (odoTotal[5] > 0x39)
        {
            odoTotal[5] = 0x30;
            odoTotal[4]++;
            if (odoTotal[4] > 0x39)
            {
                odoTotal[4] = 0x30;
                odoTotal[3]++;
                if (odoTotal[3] > 0x39)
                {
                    odoTotal[3] = 0x30;
                    odoTotal[2]++;
                    if (odoTotal[2] > 0x39)
                    {
                        odoTotal[2] = 0x30;
                        odoTotal[1]++;
                        if (odoTotal[1] > 0x39)
                        {
                            odoTotal[1] = 0x30;
                            odoTotal[0]++;
                            if (odoTotal[0] > 0x39)
                            {
                                //do nothing
                            }
                        }
                    }
                }
            }
        }
        
        unsigned char memoria = 0x10;
        for (unsigned char i = 0x00, j = 0x05; i < 0x05, j > 0x00; i++, j--){
            EEPROM_WriteByte(memoria + i, odoTotal[j]);
        }
        
        PosicaoCursorLCD(1, 7);
        EscreveFraseRamLCD(odoTotal);
        atualizaOdoTotal = 0;
    }
}

void odometroParcial(void){
    
    unsigned char trava = 0;
    static unsigned char i;
    char position = 0;
    
    if (atualizaOdoParcial){
        odoParcial[5]++;
        
        if (odoParcial[5] > 0x39){
            odoParcial[5] = 0x30;
            odoParcial[3]++;
            
            if (odoParcial[3] > 0x39){
                odoParcial[3] = 0x30;
                odoParcial[2]++;
                
                if (odoParcial[2] > 0x39){
                    odoParcial[2] = 0x30;
                    odoParcial[1]++;
                    
                    if (odoParcial[1] > 0x39){
                        odoParcial[1] = 0x30;
                        odoParcial[0]++;
                        
                        if (odoParcial[0] > 0x39){
                            for (i = 0; i <= 3; i++){
                            odoParcial[i] = '0';
                            //do nothing
                            }
                        }
                    }
                }
            }
            }
        PosicaoCursorLCD(2, 7);
        EscreveFraseRamLCD(odoParcial);
        atualizaOdoParcial = 0;
        

        if((B_Reset == 0)&&(trava == 0)) {
            odoParcial[0] = 0x30;
            odoParcial[1] = 0x30;  
            odoParcial[2] = 0x30;  
            odoParcial[3] = 0x30;
            odoParcial[5] = 0x30;  
            trava = 1;
        } else if((B_Reset == 1) && (trava == 1)){ 
                trava  = 0; 
          }
    }
}
