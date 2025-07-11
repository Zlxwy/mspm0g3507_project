/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     32000000



/* Defines for UART_JY901S */
#define UART_JY901S_INST                                                   UART3
#define UART_JY901S_INST_IRQHandler                             UART3_IRQHandler
#define UART_JY901S_INST_INT_IRQN                                 UART3_INT_IRQn
#define GPIO_UART_JY901S_RX_PORT                                           GPIOA
#define GPIO_UART_JY901S_RX_PIN                                   DL_GPIO_PIN_13
#define GPIO_UART_JY901S_IOMUX_RX                                (IOMUX_PINCM35)
#define GPIO_UART_JY901S_IOMUX_RX_FUNC                 IOMUX_PINCM35_PF_UART3_RX
#define UART_JY901S_BAUD_RATE                                           (115200)
#define UART_JY901S_IBRD_32_MHZ_115200_BAUD                                 (17)
#define UART_JY901S_FBRD_32_MHZ_115200_BAUD                                 (23)





/* Defines for DMA_UART_JY901S */
#define DMA_UART_JY901S_CHAN_ID                                              (0)
#define UART_JY901S_INST_DMA_TRIGGER                         (DMA_UART3_RX_TRIG)



/* Port definition for Pin Group GPIO_OLED */
#define GPIO_OLED_PORT                                                   (GPIOB)

/* Defines for SCL: GPIOB.6 with pinCMx 23 on package pin 20 */
#define GPIO_OLED_SCL_PIN                                        (DL_GPIO_PIN_6)
#define GPIO_OLED_SCL_IOMUX                                      (IOMUX_PINCM23)
/* Defines for SDA: GPIOB.7 with pinCMx 24 on package pin 21 */
#define GPIO_OLED_SDA_PIN                                        (DL_GPIO_PIN_7)
#define GPIO_OLED_SDA_IOMUX                                      (IOMUX_PINCM24)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_UART_JY901S_init(void);
void SYSCFG_DL_DMA_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
