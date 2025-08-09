#ifndef __MOTO_H
#define __MOTO_H
#include "ti_msp_dl_config.h"
void Moto_Init(void);
void Moto_SetSpeed(int left, int righ);
void Moto_start(void);
void Moto_Stop(void);
void Moto_Brake(void);
#endif