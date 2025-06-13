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

volatile bool isTimeoutInterrupt = false;

void UART_CH340_INST_IRQHandler(void) { // 串口ISR
    switch( DL_UART_getPendingInterrupt(UART_CH340_INST) ) {
        case DL_UART_IIDX_RX_TIMEOUT_ERROR: // 当发生超时中断时
            isTimeoutInterrupt = true; // 置标志位 isTimeoutInterrupt 为 true
            break;
        default: break;
    }
}

int main(void) {
    SYSCFG_DL_init();
    delay_init(CPUCLK_FREQ);

    NVIC_ClearPendingIRQ(UART_CH340_INST_INT_IRQN); // 清除可能的中断标志位
    NVIC_EnableIRQ(UART_CH340_INST_INT_IRQN); // 使能串口中断

    while (1) {
        if (isTimeoutInterrupt) { // 检测到标志位 isTimeoutInterrupt 为 true
            DL_GPIO_togglePins(GPIO_LED_PORT, GPIO_LED_PIN_D2_PIN); // 翻转LED
            isTimeoutInterrupt = false; // 恢复标志位 isTimeoutInterrupt 为 false
        }
        delay_ms(20);
    }
}
