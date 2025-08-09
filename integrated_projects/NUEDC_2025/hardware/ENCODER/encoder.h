#ifndef __ENCODER_H
#define __ENCODER_H
#include "ti_msp_dl_config.h"
void Encoder_Init(void);
void getEncoderCNT(int16_t *left, int16_t *righ);void qlEncoderCNT(void);
#endif