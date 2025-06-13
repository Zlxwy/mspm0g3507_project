#ifndef __CH340_H
#define __CH340_H
#include "ti_msp_dl_config.h"

uint8_t get_ch340_TC_flag(void);
uint8_t* get_ch340_rx_package(void);
uint16_t get_ch340_rx_len(void);
void clear_ch340_rx_package(void);

void uart_ch340_send_byte_blocking(uint8_t data);
void uart_ch340_printf(char* fmt,...);

void ch340_init(void);

#endif