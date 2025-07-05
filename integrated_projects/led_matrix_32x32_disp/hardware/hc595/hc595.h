#ifndef __HC595_H__
#define __HC595_H__

#include "ti_msp_dl_config.h"

void HC595Init(void);

void HC595ShiftBits(uint64_t data, uint8_t bitslen);
void HC595LatchBits(void);
void HC595OutputBits(uint64_t data, uint8_t bitslen);

void MyCasegShowNum(uint8_t digit, uint8_t num);

#endif // #ifndef __HC595_H__