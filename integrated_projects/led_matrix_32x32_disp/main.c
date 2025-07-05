/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti_msp_dl_config.h"
#include "delay.h"
#include "hc595.h"
#include "decoder_5_32.h"
#include "LEDMatrix.h"

// 0x01 设置显示时间
// 0x02 显示“LED点阵屏”字样
// 0x03 “LED点阵屏”字样滚动效果
volatile uint8_t disp_state = 0x01; // 初始为状态
volatile bool shouldClear = false;
void UART_DISP_INST_IRQHandler(void) {
    switch( DL_UART_getPendingInterrupt(UART_DISP_INST) ) {
        case DL_UART_IIDX_RX: // 接收中断
            disp_state = DL_UART_receiveData(UART_DISP_INST);
            shouldClear = true;
            break;
        default: break;
    }
}

uint32_t year = 2025;
uint8_t month = 6;
uint8_t date = 30;
uint8_t hour = 23;
uint8_t minute = 18;
uint8_t second = 0;
void TIMER_TIME_CNT_INST_IRQHandler(void) {
    switch ( DL_Timer_getPendingInterrupt(TIMER_TIME_CNT_INST) ) {
        case DL_TIMER_IIDX_LOAD: // 溢出中断
            second++;
            if (second == 60) {
                second = 0;
                minute++;
                if (minute == 60) {
                    minute = 0;
                    hour++;
                    if (hour == 24) {
                        hour = 0;
                        date++;
                        if (date == 31) {
                            date = 1;
                            month++;
                            if (month == 13) {
                                month = 1;
                                year++;
                            }
                        }
                    }
                }
                
            }
            break;
        default: break;

    }
}

int main(void)
{
    SYSCFG_DL_init();
    delay_init(CPUCLK_FREQ);

    /*显示器件初始化*/
    HC595Init(); // 74HC595，控制横向显示
    YMQInit(); // 5-32译码器，纵向扫描显示
    LEDMatrix_Init(); // 扫描定时器中断(312.5us)，优先级最低，控制扫描显示，312.5us一行，10ms扫描完32行
    // 当LEDMatrix_Init()后，就会在一个定时中断里扫描控制LED点阵屏显示，操作的是74HC595和5-32译码器
    
    NVIC_EnableIRQ(UART_DISP_INST_INT_IRQN);

    NVIC_EnableIRQ(TIMER_TIME_CNT_INST_INT_IRQN);
    DL_Timer_startCounter(TIMER_TIME_CNT_INST);

    while (true) {
        if (disp_state == 0x01) {
            if (shouldClear) { LEDMatrix_ClearAll(); shouldClear = false; } // 应该要清除
            LEDMatrix_ShowENChar( 4,  2, year/1000%10+'0', CharWidth_6);
            LEDMatrix_ShowENChar(10,  2, year/100%10+'0', CharWidth_6);
            LEDMatrix_ShowENChar(16,  2, year/10%10+'0', CharWidth_6);
            LEDMatrix_ShowENChar(22,  2, year/1%10+'0', CharWidth_6);
            LEDMatrix_ShowENChar( 1, 12, month/10%10+'0', CharWidth_6);
            LEDMatrix_ShowENChar( 7, 12, month/1%10+'0', CharWidth_6);
            LEDMatrix_ShowENChar(13, 12, '/', CharWidth_6);
            LEDMatrix_ShowENChar(19, 12, date/10%10+'0', CharWidth_6);
            LEDMatrix_ShowENChar(25, 12, date/1%10+'0', CharWidth_6);
            LEDMatrix_ShowENChar( 1, 22, hour/10%10+'0', CharWidth_6);
            LEDMatrix_ShowENChar( 7, 22, hour/1%10+'0', CharWidth_6);
            LEDMatrix_ShowENChar(13, 22, (second%2==0)?':':' ', CharWidth_6);
            LEDMatrix_ShowENChar(19, 22, minute/10%10+'0', CharWidth_6);
            LEDMatrix_ShowENChar(25, 22, minute/1%10+'0', CharWidth_6);
        }
        else if (disp_state == 0x02) {
            if (shouldClear) { LEDMatrix_ClearAll(); shouldClear = false; } // 应该要清除
            LEDMatrix_ShowENChar(4, 0, 'L', CharWidth_8);
            LEDMatrix_ShowENChar(12, 0, 'E', CharWidth_8);
            LEDMatrix_ShowENChar(20, 0, 'D', CharWidth_8);
            // LEDMatrix_DrawQuad(2, 15, 29, 15, 31, 1, 0, 1); // 画一个梯形 (2,1) (29,1) (31,15) (0,15)
            LEDMatrix_ShowCNChar(0, 16, 0, CharWidth_11);
            LEDMatrix_ShowCNChar(11, 16, 1, CharWidth_11);
            LEDMatrix_ShowCNChar(22, 16, 2, CharWidth_11);
        }
        else if (disp_state == 0x03) {
            LEDMatrix_RowsRotateMove(0, 31, 1);
        }
        delay_ms(10);
    }
}
