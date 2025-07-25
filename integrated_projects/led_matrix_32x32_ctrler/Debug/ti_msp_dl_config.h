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



/* Defines for UART_CTRL */
#define UART_CTRL_INST                                                     UART0
#define UART_CTRL_INST_IRQHandler                               UART0_IRQHandler
#define UART_CTRL_INST_INT_IRQN                                   UART0_INT_IRQn
#define GPIO_UART_CTRL_TX_PORT                                             GPIOA
#define GPIO_UART_CTRL_TX_PIN                                     DL_GPIO_PIN_10
#define GPIO_UART_CTRL_IOMUX_TX                                  (IOMUX_PINCM21)
#define GPIO_UART_CTRL_IOMUX_TX_FUNC                   IOMUX_PINCM21_PF_UART0_TX
#define UART_CTRL_BAUD_RATE                                             (115200)
#define UART_CTRL_IBRD_32_MHZ_115200_BAUD                                   (17)
#define UART_CTRL_FBRD_32_MHZ_115200_BAUD                                   (23)





/* Port definition for Pin Group GPIO_LED */
#define GPIO_LED_PORT                                                    (GPIOA)

/* Defines for D2: GPIOA.14 with pinCMx 36 on package pin 7 */
#define GPIO_LED_D2_PIN                                         (DL_GPIO_PIN_14)
#define GPIO_LED_D2_IOMUX                                        (IOMUX_PINCM36)
/* Port definition for Pin Group GPIO_KEY */
#define GPIO_KEY_PORT                                                    (GPIOB)

/* Defines for K1: GPIOB.24 with pinCMx 52 on package pin 23 */
#define GPIO_KEY_K1_PIN                                         (DL_GPIO_PIN_24)
#define GPIO_KEY_K1_IOMUX                                        (IOMUX_PINCM52)
/* Defines for K2: GPIOB.18 with pinCMx 44 on package pin 15 */
#define GPIO_KEY_K2_PIN                                         (DL_GPIO_PIN_18)
#define GPIO_KEY_K2_IOMUX                                        (IOMUX_PINCM44)
/* Defines for K3: GPIOB.3 with pinCMx 16 on package pin 51 */
#define GPIO_KEY_K3_PIN                                          (DL_GPIO_PIN_3)
#define GPIO_KEY_K3_IOMUX                                        (IOMUX_PINCM16)
/* Defines for K4: GPIOB.6 with pinCMx 23 on package pin 58 */
#define GPIO_KEY_K4_PIN                                          (DL_GPIO_PIN_6)
#define GPIO_KEY_K4_IOMUX                                        (IOMUX_PINCM23)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_UART_CTRL_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
