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
#include "hc595.h"
#include "decoder_5_32.h"
#include "LEDMatrix.h"



int main(void)
{
    SYSCFG_DL_init();
    HC595Init();
    YMQInit();
    LEDMatrix_Init();

    while (true) {
        // // 测试74HC595数码管显示
        // uint8_t DispNum[8] = {9,2,11,6,0,10,5,2}; // 显示"25 06-29"
        // for (uint8_t i=0; i<8; i++) {
        //     MyCasegShowNum(i, DispNum[i]);
        // }

        // // 测试YMQ译码器电平输出
        // for (int i=0; i<32; i++) {
        //     YMQWritePort(i);
        //     delay_cycles(16000000);
        // }

        // 测试LED点阵屏一个图案显示
        LEDMatrix_TestPic();
        delay_cycles(16000000);
        LEDMatrix_ShowENChar(4, 0, 'L', CharWidth_8);
        LEDMatrix_ShowENChar(12, 0, 'E', CharWidth_8);
        LEDMatrix_ShowENChar(20, 0, 'D', CharWidth_8);
        LEDMatrix_ShowCNChar(0, 16, 0, CharWidth_11);
        LEDMatrix_ShowCNChar(11, 16, 1, CharWidth_11);
        LEDMatrix_ShowCNChar(22, 16, 2, CharWidth_11);
        delay_cycles(16000000);
    }
}
