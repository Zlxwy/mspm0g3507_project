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

// 两个示例数据包，每个数据包含有3帧数据，分别为角加速度、角速度、角度，
// 每帧数据含有11个字节，共33个字节。
// 数据包 含有 什么数据，可以在维特上位机里设置。
// 55 51 1F 07 5A 02 CC 02 7D 0C 7F  55 52 11 00 34 00 EF FF 7D 0C 63  55 53 48 1B D5 D2 F4 01 FB 46 E8
// 55 51 24 07 59 02 D9 02 80 0C 93  55 52 12 00 2E 00 F4 FF 80 0C 66  55 53 48 1B D8 D2 F5 01 FB 46 EC
#define RX_LEN_MAX  (33*2) // 一个数据包有33个字节，长度66的数组就刚好接收完两个数据包
volatile uint8_t rxData[RX_LEN_MAX]; // 接收数组，存放JY901S的原始数据

int main(void)
{
    SYSCFG_DL_init();
    delay_init(CPUCLK_FREQ);

    /*在进行以下初始化后，数组 rxData 中便会自动更新 JY901S 的数据了，这是完全由 DMA 进行操作的*/
    DL_DMA_setSrcAddr(DMA, DMA_UART_JY901S_CHAN_ID, (uint32_t)(&UART_JY901S_INST->RXDATA)); // 设置DMA源地址
    DL_DMA_setDestAddr(DMA, DMA_UART_JY901S_CHAN_ID, (uint32_t)&rxData[0]); // 设置DMA目标地址
    DL_DMA_enableChannel(DMA, DMA_UART_JY901S_CHAN_ID); // 使能DMA通道
    while (DL_DMA_isChannelEnabled(DMA, DMA_UART_JY901S_CHAN_ID) == false); // 确保DMA通道已使能
    
    OLED_Init();
    OLED_Printf(0, 1, OLED_6X8, "JY901S ANGLE and GYRO");
    OLED_Printf(0, 10, OLED_6X8, "Initializing...");
    OLED_Update();

    bool hasFoundFrameHead = false; // 是否已经找到帧头
    uint8_t FrameHeadIndex[3] = {0}; // 帧头在数组 rxData 中的索引
    while (true) {
        if (!hasFoundFrameHead) { // 如果没有找到帧头
            for (int i=0; i<RX_LEN_MAX/2; i++) { // 遍历接收数组 rxData 前半部分
                if (rxData[i] == 0x55 && rxData[i+1] == 0x51) { // 如果发现帧头 (0x55 0x51)
                    FrameHeadIndex[0] = i + 11*0; // 获取角加速度数据在数组中的索引 (0x55 0x51)
                    FrameHeadIndex[1] = i + 11*1; // 获取角速度数据在数组中的索引 (0x55 0x52)
                    FrameHeadIndex[2] = i + 11*2; // 获取角度数据在数组中的索引 (0x55 0x53)
                    hasFoundFrameHead = true; // 已找到帧头在 rxData 中的索引
                    // 除非帧头丢失，否则之后的循环就不会再进入 if(!hasFoundFrameHead) 了
                    break; // 跳出 for 循环
                }
            }
        } else { // 如果 hasFoundFrameHead 为 true
            if (rxData[FrameHeadIndex[0]] != 0x55) { // 但帧头并不符合（帧头丢失）
                hasFoundFrameHead = false; // 将 hasFoundFrameHead 置 false ，重新寻找帧头
                continue; // 重新进入 while (true) 循环，不会执行以下代码
            }

            /*组合出有符号16位角加速度数据*/
            int16_t accX_int16 = rxData[FrameHeadIndex[0]+2] | (rxData[FrameHeadIndex[0]+3]<<8);
            int16_t accY_int16 = rxData[FrameHeadIndex[0]+4] | (rxData[FrameHeadIndex[0]+5]<<8);
            int16_t accZ_int16 = rxData[FrameHeadIndex[0]+6] | (rxData[FrameHeadIndex[0]+7]<<8);
            /*组合出有符号16位角速度数据*/
            int16_t gyroX_int16 = rxData[FrameHeadIndex[1]+2] | (rxData[FrameHeadIndex[1]+3]<<8);
            int16_t gyroY_int16 = rxData[FrameHeadIndex[1]+4] | (rxData[FrameHeadIndex[1]+5]<<8);
            int16_t gyroZ_int16 = rxData[FrameHeadIndex[1]+6] | (rxData[FrameHeadIndex[1]+7]<<8);
            /*组合出有符号16位角度数据*/
            int16_t angleX_int16 = rxData[FrameHeadIndex[2]+2] | (rxData[FrameHeadIndex[2]+3]<<8);
            int16_t angleY_int16 = rxData[FrameHeadIndex[2]+4] | (rxData[FrameHeadIndex[2]+5]<<8);
            int16_t angleZ_int16 = rxData[FrameHeadIndex[2]+6] | (rxData[FrameHeadIndex[2]+7]<<8);

            /*计算出角加速度数据（单位：g，约9.8m/s^2）*/
            float accX_float = (float)accX_int16 * 16.0 / 32768.0; // roll
            float accY_float = (float)accY_int16 * 16.0 / 32768.0; // pitch
            float accZ_float = (float)accZ_int16 * 16.0 / 32768.0; // yaw
            /*计算出角速度数据（单位：度每秒）*/
            float gyroX_float = (float)gyroX_int16 * 2000.0 / 32768.0;
            float gyroY_float = (float)gyroY_int16 * 2000.0 / 32768.0;
            float gyroZ_float = (float)gyroZ_int16 * 2000.0 / 32768.0;
            /*计算出角度数据（单位：度）*/
            float angleX_float = (float)angleX_int16 * 180.0 / 32768.0;
            float angleY_float = (float)angleY_int16 * 180.0 / 32768.0;
            float angleZ_float = (float)angleZ_int16 * 180.0 / 32768.0;

            /*显示角度数据（带正负号，(8-1-1-3=3)位整数位，3位小数位）*/
            OLED_ClearArea(0, 10, 128, 54);
            OLED_Printf(0, 10, OLED_6X8, "Roll:  %+8.3f", angleX_float); // roll
            OLED_Printf(0, 19, OLED_6X8, "Pitch: %+8.3f", angleY_float); // pitch
            OLED_Printf(0, 28, OLED_6X8, "Yaw:   %+8.3f", angleZ_float); // yaw
            OLED_Printf(0, 37, OLED_6X8, "GyroX: %+8.3f", gyroX_float);
            OLED_Printf(0, 46, OLED_6X8, "GyroY: %+8.3f", gyroY_float);
            OLED_Printf(0, 55, OLED_6X8, "GyroZ: %+8.3f", gyroZ_float);
            OLED_Update();
        }
        delay_ms(10);
    }
}
