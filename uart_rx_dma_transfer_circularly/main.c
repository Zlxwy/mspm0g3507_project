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

volatile uint8_t rxData[5] = {0,0,0,0,0};

int main(void)
{
    SYSCFG_DL_init();
    delay_init(CPUCLK_FREQ);

    DL_DMA_setSrcAddr(DMA, DMA_UART_CH340_CHAN_ID, (uint32_t)(&UART_CH340_INST->RXDATA)); // 设置DMA源地址
    DL_DMA_setDestAddr(DMA, DMA_UART_CH340_CHAN_ID, (uint32_t)&rxData[0]); // 设置DMA目标地址
    DL_DMA_enableChannel(DMA, DMA_UART_CH340_CHAN_ID); // 使能DMA通道
    while (DL_DMA_isChannelEnabled(DMA, DMA_UART_CH340_CHAN_ID) == false); // 保证DMA通道已使能
    DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_14); // 点亮LED表示初始化完成

    while (true) {
        if (rxData[0] == '1' &&
            rxData[1] == '2' &&
            rxData[2] == '3' &&
            rxData[3] == '4' &&
            rxData[4] == '5') break; // 接收到"12345"则跳出循环
        delay_ms(10);
    }

    while (1) { // 接收到"12345"后，跳出上一个循环，来到这个循环，LED闪烁
        DL_GPIO_togglePins(GPIOA, DL_GPIO_PIN_14);
        delay_ms(100);
    }
}
