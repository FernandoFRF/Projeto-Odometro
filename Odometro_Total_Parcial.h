#ifndef __ODOMETRO_TOTAL_PARCIAL_H
#define __ODOMETRO_TOTAL_PARCIAL_H

#include "Config.h"

void odometroTotal (void);
void odometroParcial (void);

unsigned char odoTotal[] = "000000";
unsigned char odoParcial[] = "0000,0";
unsigned int atualizaOdoParcial;
unsigned int atualizaOdoTotal;
unsigned int bordaParcial = 0;
unsigned int bordaTotal = 0;

#endif