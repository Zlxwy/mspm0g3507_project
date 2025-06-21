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
#include "TwoMotorDriver.h"

volatile int32_t EncoderCount = 0; // 编码器计数值
volatile bool isEncoderRotatingForward = false; // 编码器旋转方向

/**
 * @brief 正转反转是相对的，可以自己定义顺时针或逆时针为正转。
 *
 * 正转（自己定义的正转）
        ___     ___     ___     ___      
   A       |___|   |___|   |___|   |___
       __     ___     ___     ___     __
   B     |___|   |___|   |___|   |___|
   
 * 反转（自己定义的反转）
       __     ___     ___     ___     __
   A     |___|   |___|   |___|   |___|
        ___     ___     ___     ___      
   B       |___|   |___|   |___|   |___
 *
 */


void GROUP1_IRQHandler(void) {
    uint32_t gpioA = DL_GPIO_getEnabledInterruptStatus(GPIO_ENCODER_PORT, GPIO_ENCODER_PHASE_A_PIN); // 获取GPIOA端口的待处理中断

    if((gpioA & GPIO_ENCODER_PHASE_A_PIN) == GPIO_ENCODER_PHASE_A_PIN) { // 如果是A相引脚中断
        if (DL_GPIO_readPins(GPIO_ENCODER_PORT, GPIO_ENCODER_PHASE_A_PIN) == GPIO_ENCODER_PHASE_A_PIN) { // 如果此时A相引脚高电平
            if (DL_GPIO_readPins(GPIO_ENCODER_PORT, GPIO_ENCODER_PHASE_B_PIN) == GPIO_ENCODER_PHASE_B_PIN) { // 如果此时B相引脚高电平
                isEncoderRotatingForward = true;
                EncoderCount++ ; // A相引脚上升沿时，B相引脚高电平，判定正转
            } else { // 如果此时B相引脚低电平
                isEncoderRotatingForward = false;
                EncoderCount-- ; // A相引脚上升沿时，B相引脚低电平，判定反转
            }
        } else { // 如果此时A相引脚低电平
            if (DL_GPIO_readPins(GPIO_ENCODER_PORT, GPIO_ENCODER_PHASE_B_PIN) == GPIO_ENCODER_PHASE_B_PIN) { // 如果此时B相引脚高电平
                isEncoderRotatingForward = false;
                EncoderCount-- ; // A相引脚下降沿时，B相引脚高电平，判定反转
            } else { // 如果此时B相引脚低电平
                isEncoderRotatingForward = true;
                EncoderCount++ ; // A相引脚下降沿时，B相引脚低电平，判定正转
            }
        }
        DL_GPIO_clearInterruptStatus(GPIO_ENCODER_PORT, GPIO_ENCODER_PHASE_A_PIN); // 清除A相引脚上的中断状态
    }

    if ((gpioA & GPIO_ENCODER_PHASE_B_PIN) == GPIO_ENCODER_PHASE_B_PIN) { // 如果是B相引脚中断
        if (DL_GPIO_readPins(GPIO_ENCODER_PORT, GPIO_ENCODER_PHASE_B_PIN) == GPIO_ENCODER_PHASE_B_PIN) { // 如果此时B相引脚高电平
            if (DL_GPIO_readPins(GPIO_ENCODER_PORT, GPIO_ENCODER_PHASE_A_PIN) == GPIO_ENCODER_PHASE_A_PIN) { // 如果此时A相引脚高电平
                isEncoderRotatingForward = false;
                EncoderCount--; // B相引脚上升沿时，A相引脚高电平，判定反转
            } else { // 如果此时A相引脚低电平
                isEncoderRotatingForward = true;
                EncoderCount++; // B相引脚上升沿时，A相引脚低电平，判定正转
            }
        } else { // 如果此时B相引脚低电平
            if (DL_GPIO_readPins(GPIO_ENCODER_PORT, GPIO_ENCODER_PHASE_A_PIN) == GPIO_ENCODER_PHASE_A_PIN) { // 如果此时A相引脚高电平
                isEncoderRotatingForward = true;
                EncoderCount++; // B相引脚下降沿时，A相引脚高电平，判定正转
            } else { // 如果此时A相引脚低电平
                isEncoderRotatingForward = false;
                EncoderCount--; // B相引脚下降沿时，A相引脚低电平，判定反转
            }
        }
        DL_GPIO_clearInterruptStatus(GPIO_ENCODER_PORT, GPIO_ENCODER_PHASE_B_PIN); // 清除引脚上的中断状态
    }
}

int main(void)
{
    SYSCFG_DL_init();
    delay_init(CPUCLK_FREQ);

    /*初始化OLED*/
    OLED_Init();
    OLED_Printf(0, 0, OLED_8X16, "LED Dimmer"); // 试验标题
    OLED_Update();

    /*初始化编码器*/
    NVIC_ClearPendingIRQ(GPIO_ENCODER_INT_IRQN);
    NVIC_EnableIRQ(GPIO_ENCODER_INT_IRQN);

    /*初始化电机驱动*/
    MotorInit();

    while (true) {
        float LeftSpeed = EncoderCount * 5; // 将编码器计数值映射至速度值
        float RightSpeed = EncoderCount * 5; // 将编码器计数值映射至速度值
        LeftSpeed = MotorSpeedClamp(LeftSpeed, -100.0, 0.0); // 限制速度值在[-100,0]之间
        RightSpeed = MotorSpeedClamp(RightSpeed, 0.0, 100.0); // 限制速度值在[0,100]之间
        SetMotorSpeed(LeftSpeed, RightSpeed); // 设置两个电机速度

        uint32_t CC0Value = DL_Timer_getCaptureCompareValue(PWM_MOTOR_INST, GPIO_PWM_MOTOR_C0_IDX); // 获取通道0的占空计数值
        uint32_t CC1Value = DL_Timer_getCaptureCompareValue(PWM_MOTOR_INST, GPIO_PWM_MOTOR_C1_IDX); // 获取通道1的占空计数值
        OLED_Printf(0, 16, OLED_8X16, "CC0Val: %d", CC0Value); // 显示通道0占空计数值
        OLED_Printf(0, 32, OLED_8X16, "CC1Val: %d", CC1Value); // 显示通道1占空计数值
        OLED_Printf(0, 48, OLED_8X16, "Cnt: %d", EncoderCount); // 显示编码器计数值
        if (isEncoderRotatingForward != false) OLED_Printf(88, 48, OLED_8X16, "up  "); // 显示编码器转动方向
        else OLED_Printf(88, 48, OLED_8X16, "Down"); // 显示编码器转动方向
        OLED_Update(); // 更新OLED显示

        delay_ms(10);
    }
}
