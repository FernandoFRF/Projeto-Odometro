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




void odometroTotal(void)
{
    static unsigned char odoTotal[] = "000000";
    
    odoTotal [5] = EEPROM_ReadByte (0x00);
    odoTotal [4] = EEPROM_ReadByte (0x01);
    odoTotal [3] = EEPROM_ReadByte (0x02);
    odoTotal [2] = EEPROM_ReadByte (0x03);
    odoTotal [1] = EEPROM_ReadByte (0x04);
    odoTotal [0] = EEPROM_ReadByte (0x05);
    
    if (atualizaOdoTotal)
    {
               
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
                                odoTotal[0] = 0x30;
                                //do nothing
                            }
                        }
                    }
                }
            }
        }
    }
        
        atualizaOdoTotal = 0;
        PosicaoCursorLCD(1, 7);
        EscreveFraseRamLCD(odoTotal);
        
        EEPROM_WriteByte(0x00, odoTotal[5]);
        EEPROM_WriteByte(0x01, odoTotal[4]);
        EEPROM_WriteByte(0x02, odoTotal[3]);
        EEPROM_WriteByte(0x03, odoTotal[2]);
        EEPROM_WriteByte(0x04, odoTotal[1]);
        EEPROM_WriteByte(0x05, odoTotal[0]);
        
//        EEPROM_WriteByte(0x00, 0x30);
//        EEPROM_WriteByte(0x01, 0x30);
//        EEPROM_WriteByte(0x02, 0x30);
//        EEPROM_WriteByte(0x03, 0x30);
//        EEPROM_WriteByte(0x04, 0x30);
//        EEPROM_WriteByte(0x05, 0x30);
        
    
}

void odometroParcial(void){
    
    unsigned char trava = 0;
    static unsigned char i;
    char position = 0;
    
    if (atualizaOdoParcial)
    {
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
        
    }
    if((B_Reset == 0)&&(trava == 0)) 
    {
        odoParcial[0] = 0x30;
        odoParcial[1] = 0x30;  
        odoParcial[2] = 0x30;  
        odoParcial[3] = 0x30;
        odoParcial[5] = 0x30;  
        PosicaoCursorLCD(2, 7);
        EscreveFraseRamLCD(odoParcial);

        trava = 1;
    } 
    else if((B_Reset == 1) && (trava == 1))
    { 
        trava  = 0; 
    }

}
