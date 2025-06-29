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



/* Defines for TIMER_LED_MATRIX */
#define TIMER_LED_MATRIX_INST                                            (TIMA0)
#define TIMER_LED_MATRIX_INST_IRQHandler                        TIMA0_IRQHandler
#define TIMER_LED_MATRIX_INST_INT_IRQN                          (TIMA0_INT_IRQn)
#define TIMER_LED_MATRIX_INST_LOAD_VALUE                                 (9999U)




/* Port definition for Pin Group GPIO_HC595 */
#define GPIO_HC595_PORT                                                  (GPIOB)

/* Defines for DS: GPIOB.18 with pinCMx 44 on package pin 15 */
#define GPIO_HC595_DS_PIN                                       (DL_GPIO_PIN_18)
#define GPIO_HC595_DS_IOMUX                                      (IOMUX_PINCM44)
/* Defines for SHCP: GPIOB.19 with pinCMx 45 on package pin 16 */
#define GPIO_HC595_SHCP_PIN                                     (DL_GPIO_PIN_19)
#define GPIO_HC595_SHCP_IOMUX                                    (IOMUX_PINCM45)
/* Defines for STCP: GPIOB.20 with pinCMx 48 on package pin 19 */
#define GPIO_HC595_STCP_PIN                                     (DL_GPIO_PIN_20)
#define GPIO_HC595_STCP_IOMUX                                    (IOMUX_PINCM48)
/* Defines for NOE: GPIOB.24 with pinCMx 52 on package pin 23 */
#define GPIO_HC595_NOE_PIN                                      (DL_GPIO_PIN_24)
#define GPIO_HC595_NOE_IOMUX                                     (IOMUX_PINCM52)
/* Port definition for Pin Group GPIO_YMQ */
#define GPIO_YMQ_PORT                                                    (GPIOA)

/* Defines for PIN_0: GPIOA.12 with pinCMx 34 on package pin 5 */
#define GPIO_YMQ_PIN_0_PIN                                      (DL_GPIO_PIN_12)
#define GPIO_YMQ_PIN_0_IOMUX                                     (IOMUX_PINCM34)
/* Defines for PIN_1: GPIOA.13 with pinCMx 35 on package pin 6 */
#define GPIO_YMQ_PIN_1_PIN                                      (DL_GPIO_PIN_13)
#define GPIO_YMQ_PIN_1_IOMUX                                     (IOMUX_PINCM35)
/* Defines for PIN_2: GPIOA.14 with pinCMx 36 on package pin 7 */
#define GPIO_YMQ_PIN_2_PIN                                      (DL_GPIO_PIN_14)
#define GPIO_YMQ_PIN_2_IOMUX                                     (IOMUX_PINCM36)
/* Defines for PIN_3: GPIOA.15 with pinCMx 37 on package pin 8 */
#define GPIO_YMQ_PIN_3_PIN                                      (DL_GPIO_PIN_15)
#define GPIO_YMQ_PIN_3_IOMUX                                     (IOMUX_PINCM37)
/* Defines for PIN_4: GPIOA.16 with pinCMx 38 on package pin 9 */
#define GPIO_YMQ_PIN_4_PIN                                      (DL_GPIO_PIN_16)
#define GPIO_YMQ_PIN_4_IOMUX                                     (IOMUX_PINCM38)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_TIMER_LED_MATRIX_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
