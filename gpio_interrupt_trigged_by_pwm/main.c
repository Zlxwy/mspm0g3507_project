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

// 由10Hz的PWM驱动GPIO中断，在中断内操作LED翻转电平
void GROUP1_IRQHandler(void) {
    uint32_t gpioA = DL_GPIO_getEnabledInterruptStatus(GPIO_EXTI_PORT, GPIO_EXTI_PIN_EXTI_PIN); // 获取GPIOA端口的待处理中断
    if((gpioA & GPIO_EXTI_PIN_EXTI_PIN) == // 将待处理中断与要检查的引脚进行按位与操作
                GPIO_EXTI_PIN_EXTI_PIN) { // 如果结果等于该引脚值
        DL_GPIO_togglePins(GPIO_LED_PORT, GPIO_LED_PIN_D2_PIN); // 翻转LED电平
        DL_GPIO_clearInterruptStatus(GPIO_EXTI_PORT, GPIO_EXTI_PIN_EXTI_PIN); // 清除引脚上的中断状态
    }
}

int main(void)
{
    SYSCFG_DL_init();

    NVIC_ClearPendingIRQ(GPIO_EXTI_INT_IRQN);
    NVIC_EnableIRQ(GPIO_EXTI_INT_IRQN);

    while (1) {
    }
}
