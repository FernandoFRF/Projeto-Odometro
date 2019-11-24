#ifndef __FUEL_GAUGE_HEADER
#define	__FUEL_GAUGE_HEADER

#include "Config.h"	


unsigned char numeroC = 0;
unsigned char reserva = 0;

//unsigned char CanalADC = 0;
unsigned char primeiroFiltro = 0;

unsigned int countLed = 0;
unsigned int tempoCombustivel = 0;

unsigned int valorADCMedia = 0;
unsigned int combArray[10];
unsigned int valorTensao = 0;
long porcentagemTensao = 0;

void Combustivel(void);
void TensaoBateria(void);
void ValorCombustivel(void);

#endif


