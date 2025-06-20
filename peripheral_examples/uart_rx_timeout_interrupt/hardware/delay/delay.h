#ifndef __DELAY_H
#define __DELAY_H
#include "ti_msp_dl_config.h"

void delay_init(uint32_t sysclock);
void delay_ms(uint32_t ms_cycles);
void delay_us(uint32_t us_cycles);
void KeyDebounce(GPIO_Regs* gpio, uint32_t pins, uint32_t value);

#endif