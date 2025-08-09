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



/* Defines for PWM_MOTO */
#define PWM_MOTO_INST                                                      TIMG0
#define PWM_MOTO_INST_IRQHandler                                TIMG0_IRQHandler
#define PWM_MOTO_INST_INT_IRQN                                  (TIMG0_INT_IRQn)
#define PWM_MOTO_INST_CLK_FREQ                                          32000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_MOTO_C0_PORT                                              GPIOA
#define GPIO_PWM_MOTO_C0_PIN                                      DL_GPIO_PIN_12
#define GPIO_PWM_MOTO_C0_IOMUX                                   (IOMUX_PINCM34)
#define GPIO_PWM_MOTO_C0_IOMUX_FUNC                  IOMUX_PINCM34_PF_TIMG0_CCP0
#define GPIO_PWM_MOTO_C0_IDX                                 DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_MOTO_C1_PORT                                              GPIOA
#define GPIO_PWM_MOTO_C1_PIN                                      DL_GPIO_PIN_13
#define GPIO_PWM_MOTO_C1_IOMUX                                   (IOMUX_PINCM35)
#define GPIO_PWM_MOTO_C1_IOMUX_FUNC                  IOMUX_PINCM35_PF_TIMG0_CCP1
#define GPIO_PWM_MOTO_C1_IDX                                 DL_TIMER_CC_1_INDEX



/* Defines for TIMER_CTRL */
#define TIMER_CTRL_INST                                                  (TIMA0)
#define TIMER_CTRL_INST_IRQHandler                              TIMA0_IRQHandler
#define TIMER_CTRL_INST_INT_IRQN                                (TIMA0_INT_IRQn)
#define TIMER_CTRL_INST_LOAD_VALUE                                      (19999U)



/* Defines for UART_LX225 */
#define UART_LX225_INST                                                    UART1
#define UART_LX225_INST_IRQHandler                              UART1_IRQHandler
#define UART_LX225_INST_INT_IRQN                                  UART1_INT_IRQn
#define GPIO_UART_LX225_TX_PORT                                            GPIOA
#define GPIO_UART_LX225_TX_PIN                                     DL_GPIO_PIN_8
#define GPIO_UART_LX225_IOMUX_TX                                 (IOMUX_PINCM19)
#define GPIO_UART_LX225_IOMUX_TX_FUNC                  IOMUX_PINCM19_PF_UART1_TX
#define UART_LX225_BAUD_RATE                                            (115200)
#define UART_LX225_IBRD_32_MHZ_115200_BAUD                                  (17)
#define UART_LX225_FBRD_32_MHZ_115200_BAUD                                  (23)





/* Port definition for Pin Group GPIO_JDQ */
#define GPIO_JDQ_PORT                                                    (GPIOA)

/* Defines for JDQ1: GPIOA.27 with pinCMx 60 on package pin 31 */
#define GPIO_JDQ_JDQ1_PIN                                       (DL_GPIO_PIN_27)
#define GPIO_JDQ_JDQ1_IOMUX                                      (IOMUX_PINCM60)
/* Port definition for Pin Group GPIO_OLED */
#define GPIO_OLED_PORT                                                   (GPIOB)

/* Defines for SCL: GPIOB.6 with pinCMx 23 on package pin 58 */
#define GPIO_OLED_SCL_PIN                                        (DL_GPIO_PIN_6)
#define GPIO_OLED_SCL_IOMUX                                      (IOMUX_PINCM23)
/* Defines for SDA: GPIOB.1 with pinCMx 13 on package pin 48 */
#define GPIO_OLED_SDA_PIN                                        (DL_GPIO_PIN_1)
#define GPIO_OLED_SDA_IOMUX                                      (IOMUX_PINCM13)
/* Port definition for Pin Group GPIO_LEFT_DIR */
#define GPIO_LEFT_DIR_PORT                                               (GPIOA)

/* Defines for IN1: GPIOA.28 with pinCMx 3 on package pin 35 */
#define GPIO_LEFT_DIR_IN1_PIN                                   (DL_GPIO_PIN_28)
#define GPIO_LEFT_DIR_IN1_IOMUX                                   (IOMUX_PINCM3)
/* Defines for IN2: GPIOA.31 with pinCMx 6 on package pin 39 */
#define GPIO_LEFT_DIR_IN2_PIN                                   (DL_GPIO_PIN_31)
#define GPIO_LEFT_DIR_IN2_IOMUX                                   (IOMUX_PINCM6)
/* Port definition for Pin Group GPIO_RIGHT_DIR */
#define GPIO_RIGHT_DIR_PORT                                              (GPIOB)

/* Defines for IN3: GPIOB.12 with pinCMx 29 on package pin 64 */
#define GPIO_RIGHT_DIR_IN3_PIN                                  (DL_GPIO_PIN_12)
#define GPIO_RIGHT_DIR_IN3_IOMUX                                 (IOMUX_PINCM29)
/* Defines for IN4: GPIOB.17 with pinCMx 43 on package pin 14 */
#define GPIO_RIGHT_DIR_IN4_PIN                                  (DL_GPIO_PIN_17)
#define GPIO_RIGHT_DIR_IN4_IOMUX                                 (IOMUX_PINCM43)
/* Port definition for Pin Group GPIO_ECD */
#define GPIO_ECD_PORT                                                    (GPIOB)

/* Defines for LEFT_A: GPIOB.15 with pinCMx 32 on package pin 3 */
// pins affected by this interrupt request:["LEFT_A","LEFT_B","RIGH_A","RIGH_B"]
#define GPIO_ECD_INT_IRQN                                       (GPIOB_INT_IRQn)
#define GPIO_ECD_INT_IIDX                       (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define GPIO_ECD_LEFT_A_IIDX                                (DL_GPIO_IIDX_DIO15)
#define GPIO_ECD_LEFT_A_PIN                                     (DL_GPIO_PIN_15)
#define GPIO_ECD_LEFT_A_IOMUX                                    (IOMUX_PINCM32)
/* Defines for LEFT_B: GPIOB.13 with pinCMx 30 on package pin 1 */
#define GPIO_ECD_LEFT_B_IIDX                                (DL_GPIO_IIDX_DIO13)
#define GPIO_ECD_LEFT_B_PIN                                     (DL_GPIO_PIN_13)
#define GPIO_ECD_LEFT_B_IOMUX                                    (IOMUX_PINCM30)
/* Defines for RIGH_A: GPIOB.8 with pinCMx 25 on package pin 60 */
#define GPIO_ECD_RIGH_A_IIDX                                 (DL_GPIO_IIDX_DIO8)
#define GPIO_ECD_RIGH_A_PIN                                      (DL_GPIO_PIN_8)
#define GPIO_ECD_RIGH_A_IOMUX                                    (IOMUX_PINCM25)
/* Defines for RIGH_B: GPIOB.7 with pinCMx 24 on package pin 59 */
#define GPIO_ECD_RIGH_B_IIDX                                 (DL_GPIO_IIDX_DIO7)
#define GPIO_ECD_RIGH_B_PIN                                      (DL_GPIO_PIN_7)
#define GPIO_ECD_RIGH_B_IOMUX                                    (IOMUX_PINCM24)
/* Port definition for Pin Group GPIO_TRK */
#define GPIO_TRK_PORT                                                    (GPIOB)

/* Defines for P0: GPIOB.18 with pinCMx 44 on package pin 15 */
#define GPIO_TRK_P0_PIN                                         (DL_GPIO_PIN_18)
#define GPIO_TRK_P0_IOMUX                                        (IOMUX_PINCM44)
/* Defines for P1: GPIOB.19 with pinCMx 45 on package pin 16 */
#define GPIO_TRK_P1_PIN                                         (DL_GPIO_PIN_19)
#define GPIO_TRK_P1_IOMUX                                        (IOMUX_PINCM45)
/* Defines for P2: GPIOB.20 with pinCMx 48 on package pin 19 */
#define GPIO_TRK_P2_PIN                                         (DL_GPIO_PIN_20)
#define GPIO_TRK_P2_IOMUX                                        (IOMUX_PINCM48)
/* Defines for P3: GPIOB.21 with pinCMx 49 on package pin 20 */
#define GPIO_TRK_P3_PIN                                         (DL_GPIO_PIN_21)
#define GPIO_TRK_P3_IOMUX                                        (IOMUX_PINCM49)
/* Defines for P4: GPIOB.22 with pinCMx 50 on package pin 21 */
#define GPIO_TRK_P4_PIN                                         (DL_GPIO_PIN_22)
#define GPIO_TRK_P4_IOMUX                                        (IOMUX_PINCM50)
/* Defines for P5: GPIOB.23 with pinCMx 51 on package pin 22 */
#define GPIO_TRK_P5_PIN                                         (DL_GPIO_PIN_23)
#define GPIO_TRK_P5_IOMUX                                        (IOMUX_PINCM51)
/* Defines for P6: GPIOB.24 with pinCMx 52 on package pin 23 */
#define GPIO_TRK_P6_PIN                                         (DL_GPIO_PIN_24)
#define GPIO_TRK_P6_IOMUX                                        (IOMUX_PINCM52)
/* Defines for P7: GPIOB.25 with pinCMx 56 on package pin 27 */
#define GPIO_TRK_P7_PIN                                         (DL_GPIO_PIN_25)
#define GPIO_TRK_P7_IOMUX                                        (IOMUX_PINCM56)
/* Port definition for Pin Group GPIO_KEY */
#define GPIO_KEY_PORT                                                    (GPIOA)

/* Defines for add: GPIOA.14 with pinCMx 36 on package pin 7 */
#define GPIO_KEY_add_PIN                                        (DL_GPIO_PIN_14)
#define GPIO_KEY_add_IOMUX                                       (IOMUX_PINCM36)
/* Defines for enter: GPIOA.15 with pinCMx 37 on package pin 8 */
#define GPIO_KEY_enter_PIN                                      (DL_GPIO_PIN_15)
#define GPIO_KEY_enter_IOMUX                                     (IOMUX_PINCM37)
/* Defines for xxx: GPIOA.16 with pinCMx 38 on package pin 9 */
#define GPIO_KEY_xxx_PIN                                        (DL_GPIO_PIN_16)
#define GPIO_KEY_xxx_IOMUX                                       (IOMUX_PINCM38)
/* Port definition for Pin Group GPIO_FAKE */
#define GPIO_FAKE_PORT                                                   (GPIOA)

/* Defines for IN: GPIOA.24 with pinCMx 54 on package pin 25 */
#define GPIO_FAKE_IN_PIN                                        (DL_GPIO_PIN_24)
#define GPIO_FAKE_IN_IOMUX                                       (IOMUX_PINCM54)
/* Defines for OUT: GPIOA.25 with pinCMx 55 on package pin 26 */
#define GPIO_FAKE_OUT_PIN                                       (DL_GPIO_PIN_25)
#define GPIO_FAKE_OUT_IOMUX                                      (IOMUX_PINCM55)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_MOTO_init(void);
void SYSCFG_DL_TIMER_CTRL_init(void);
void SYSCFG_DL_UART_LX225_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
