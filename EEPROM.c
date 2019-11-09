#include "Config.h"
#include "EEPROM.h"
#include <stdlib.h>

void Init_EEPROM(void)
{
    EECON1 = 0b00000100;
}

unsigned char EEPROM_ReadByte (unsigned char MemoryAddress)
{
	EEADR 	= MemoryAddress; 	/* Recebe endereço na memória */
	EECON1 	= 0x01;				/* Seta bit RD - leitura */
	return(EEDATA);				/* Retorna o valor lido na EEPROM */
}

void EEPROM_WriteByte(unsigned char WriteMemoryAddress , unsigned char WriteData)
{
    EEADR = WriteMemoryAddress;	/* Recebe endereço na memória */
    EEDATA = WriteData;			/* Dado a ser escrito */
    EECON1bits.EEPGD = 0;		/* Configura registrador EECON1 para escrita */
    EECON1bits.CFGS = 0;		/* Configura registrador EECON1 para escrita */
    EECON1bits.WREN = 1;		/* Configura registrador EECON1 para escrita */
    INTCONbits.GIE = 0;			/* Desabilita interrupções */
    EECON2 = 0x55;				/* Senha #1 para iniciar processo de escrita */
    EECON2 = 0x0AA;				/* Senha #2 para iniciar processo de escrita */
    EECON1bits.WR= 1;			/* Configura registrador EECON1 para escrita */
    while(EECON1bits.WR == 1);	/* Aguarda o termino de escrita */
    INTCONbits.GIE = 1;			/* Habilita interrupções */
    EECON1bits.WREN = 0;		/*Desabilita permissão de escrita */ 
}


    
//EEPROM_WriteByte(0x10 , 0x42);
//
//unsigned char DataRead;
//DataRead = EEPROM_ReadByte(0x10);

//unsigned char *EEPROM_Wr_Data_Ptr;
//unsigned char EEPROM_Wr_NumOfByte;
//
//
//void EEPROM_WriteByteWithInterrupt(unsigned char WriteMemoryAddressInt , unsigned char *WriteDataPtr, unsigned char NumBytes)
//{
//  while(EECON1bits.WR == 1);				/* Aguarda o termino de escrita */
//	EEADR = WriteMemoryAddressInt;          /* Recebe endereço na memória */
//  EEDATA = WriteDataInterrupt;            /* Dado a ser escrito */
//  EEPROM_Wr_Data_Ptr = WriteDataPtr;
//	EEPROM_Wr_NumOfByte = NumBytes;
//  EECON1bits.WREN = 1;					/* Configura registrador EECON1 para escrita */
//	PIR2bits.EEIF = 1;						/* Seta flag de interrupção */
//	PIR2bits.EEIE = 1;						/* Habilita interrupção de EEPROM */
//}

//interrupt void ISR(void)
//{
//	if(PIR2bits.EEIF) 						/* Verifica se o flag de interrupção de EEPROM foi setado */
//	{
//		PIR2bits.EEIF = 0; 					/* Limpa flag de interrupção de EEPROM */
//		if(EEPROM_Wr_NumOfByte) 			/* Verifica se existe algum dado para ser enviado */
//		{
//			EEDATA = *EEPROM_Wr_Data_Ptr++; /* EEDATA recebe o valor a ser escrito e incrementa o ponteiro */
//			EECON2 = 0x55;					/* Senha #1 para iniciar processo de escrita */
//			EECON2 = 0xAA;					/* Senha #2 para iniciar processo de escrita */
//			EECON1bits.WR = 1;				/* Configura registrador EECON1 para escrita */
//			EEADR++;						/* Incrementa endereço de escrita */
//			EEPROM_Wr_NumOfByte--;			/* Decrementa numero de byte para escrita */
//		}
//	}
//}