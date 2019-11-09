// header das rotinas de gravar EEPROM
#ifndef __EEPROM_H
#define __EEPROM_H
#include "Config.h"

// Inicializa EEPROM
void Init_EEPROM (void);

// Le EEPROM
unsigned char EEPROM_ReadByte (unsigned char MemoryAddress);

// Grava EEPROM
void EEPROM_WriteByte(unsigned char WriteMemoryAddress, unsigned char WriteData);
//void EEPROM_WriteByteWithInterrupt(unsigned char WriteMemoryAddressInt , unsigned char *WriteDataPtr, unsigned char NumBytes);

#endif