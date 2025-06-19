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
#include "OLED.h"

int main(void)
{
    SYSCFG_DL_init();
    delay_init(CPUCLK_FREQ);
    
    OLED_Init();
    OLED_Printf(0, 0, OLED_8X16, "TIMER-QEI"); // 试验标题
    OLED_Printf(0, 16, OLED_8X16, "Cnt: 00000"); // 编码器计数
    OLED_Printf(0, 32, OLED_8X16, "Dir: "); // 编码器转动方向
    OLED_Update();

    NVIC_ClearPendingIRQ(QEI_ENCODER_INST_INT_IRQN); // 清除可能的中断标志位
    NVIC_EnableIRQ(QEI_ENCODER_INST_INT_IRQN); // 开启中断
    DL_Timer_startCounter(QEI_ENCODER_INST); // 启动编码器定时器

    while (true) {
        /*显示编码器计数值*/
        OLED_Printf(0, 16, OLED_8X16, "Cnt: %d     ", DL_Timer_getTimerCount(QEI_ENCODER_INST));

        /*显示编码器转动方向*/
        if (DL_Timer_getQEIDirection(QEI_ENCODER_INST) != DL_TIMER_QEI_DIR_DOWN) {
            OLED_Printf(0, 32, OLED_8X16, "Dir: up  ");
        } else {
            OLED_Printf(0, 32, OLED_8X16, "Dir: Down");
        }

        /*更新OLED显示*/
        OLED_Update();

        delay_ms(10);
    }
}