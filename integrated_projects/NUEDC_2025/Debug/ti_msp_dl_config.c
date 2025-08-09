/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerA_backupConfig gTIMER_CTRLBackup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_PWM_MOTO_init();
    SYSCFG_DL_TIMER_CTRL_init();
    SYSCFG_DL_UART_LX225_init();
    /* Ensure backup structures have no valid state */

	gTIMER_CTRLBackup.backupRdy 	= false;


}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_saveConfiguration(TIMER_CTRL_INST, &gTIMER_CTRLBackup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_restoreConfiguration(TIMER_CTRL_INST, &gTIMER_CTRLBackup, false);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerG_reset(PWM_MOTO_INST);
    DL_TimerA_reset(TIMER_CTRL_INST);
    DL_UART_Main_reset(UART_LX225_INST);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerG_enablePower(PWM_MOTO_INST);
    DL_TimerA_enablePower(TIMER_CTRL_INST);
    DL_UART_Main_enablePower(UART_LX225_INST);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_MOTO_C0_IOMUX,GPIO_PWM_MOTO_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_MOTO_C0_PORT, GPIO_PWM_MOTO_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_MOTO_C1_IOMUX,GPIO_PWM_MOTO_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_MOTO_C1_PORT, GPIO_PWM_MOTO_C1_PIN);
    
	DL_GPIO_initPeripheralOutputFunctionFeatures(
		 GPIO_PWM_MOTO_C0_IOMUX, GPIO_PWM_MOTO_C0_IOMUX_FUNC,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_DRIVE_STRENGTH_LOW, DL_GPIO_HIZ_DISABLE);
	DL_GPIO_initPeripheralOutputFunctionFeatures(
		 GPIO_PWM_MOTO_C1_IOMUX, GPIO_PWM_MOTO_C1_IOMUX_FUNC,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_DRIVE_STRENGTH_LOW, DL_GPIO_HIZ_DISABLE);

    
	DL_GPIO_initPeripheralOutputFunctionFeatures(
		 GPIO_UART_LX225_IOMUX_TX, GPIO_UART_LX225_IOMUX_TX_FUNC,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_DRIVE_STRENGTH_LOW, DL_GPIO_HIZ_DISABLE);

    DL_GPIO_initDigitalOutput(GPIO_JDQ_JDQ1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_OLED_SCL_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_OLED_SDA_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_LEFT_DIR_IN1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_LEFT_DIR_IN2_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_RIGHT_DIR_IN3_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_RIGHT_DIR_IN4_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_ECD_LEFT_A_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_ECD_LEFT_B_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_ECD_RIGH_A_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_ECD_RIGH_B_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_TRK_P0_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_TRK_P1_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_TRK_P2_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_TRK_P3_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_TRK_P4_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_TRK_P5_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_TRK_P6_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_TRK_P7_IOMUX);

    DL_GPIO_initDigitalInputFeatures(GPIO_KEY_add_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_KEY_enter_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_KEY_xxx_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_FAKE_IN_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(GPIO_FAKE_OUT_IOMUX);

    DL_GPIO_clearPins(GPIOA, GPIO_JDQ_JDQ1_PIN |
		GPIO_LEFT_DIR_IN1_PIN |
		GPIO_LEFT_DIR_IN2_PIN |
		GPIO_FAKE_OUT_PIN);
    DL_GPIO_enableOutput(GPIOA, GPIO_JDQ_JDQ1_PIN |
		GPIO_LEFT_DIR_IN1_PIN |
		GPIO_LEFT_DIR_IN2_PIN |
		GPIO_FAKE_OUT_PIN);
    DL_GPIO_clearPins(GPIOB, GPIO_RIGHT_DIR_IN3_PIN |
		GPIO_RIGHT_DIR_IN4_PIN);
    DL_GPIO_setPins(GPIOB, GPIO_OLED_SCL_PIN |
		GPIO_OLED_SDA_PIN);
    DL_GPIO_enableOutput(GPIOB, GPIO_OLED_SCL_PIN |
		GPIO_OLED_SDA_PIN |
		GPIO_RIGHT_DIR_IN3_PIN |
		GPIO_RIGHT_DIR_IN4_PIN);
    DL_GPIO_setLowerPinsPolarity(GPIOB, DL_GPIO_PIN_15_EDGE_RISE |
		DL_GPIO_PIN_13_EDGE_RISE |
		DL_GPIO_PIN_8_EDGE_RISE |
		DL_GPIO_PIN_7_EDGE_RISE);
    DL_GPIO_clearInterruptStatus(GPIOB, GPIO_ECD_LEFT_A_PIN |
		GPIO_ECD_LEFT_B_PIN |
		GPIO_ECD_RIGH_A_PIN |
		GPIO_ECD_RIGH_B_PIN);
    DL_GPIO_enableInterrupt(GPIOB, GPIO_ECD_LEFT_A_PIN |
		GPIO_ECD_LEFT_B_PIN |
		GPIO_ECD_RIGH_A_PIN |
		GPIO_ECD_RIGH_B_PIN);

}


SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
    /* Set default configuration */
    DL_SYSCTL_disableHFXT();
    DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_1);
    DL_SYSCTL_setMCLKDivider(DL_SYSCTL_MCLK_DIVIDER_DISABLE);
    /* INT_GROUP1 Priority */
    NVIC_SetPriority(GPIOB_INT_IRQn, 0);

}


/*
 * Timer clock configuration to be sourced by  / 1 (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   32000000 Hz = 32000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gPWM_MOTOClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U
};

static const DL_TimerG_PWMConfig gPWM_MOTOConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 1000,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_MOTO_init(void) {

    DL_TimerG_setClockConfig(
        PWM_MOTO_INST, (DL_TimerG_ClockConfig *) &gPWM_MOTOClockConfig);

    DL_TimerG_initPWMMode(
        PWM_MOTO_INST, (DL_TimerG_PWMConfig *) &gPWM_MOTOConfig);

    DL_TimerG_setCaptureCompareOutCtl(PWM_MOTO_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_MOTO_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_MOTO_INST, 0, DL_TIMER_CC_0_INDEX);

    DL_TimerG_setCaptureCompareOutCtl(PWM_MOTO_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_MOTO_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_MOTO_INST, 0, DL_TIMER_CC_1_INDEX);

    DL_TimerG_enableClock(PWM_MOTO_INST);


    
    DL_TimerG_setCCPDirection(PWM_MOTO_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );


}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   4000000 Hz = 4000000 Hz / (8 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gTIMER_CTRLClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 0U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_CTRL_INST_LOAD_VALUE = (5 ms * 4000000 Hz) - 1
 */
static const DL_TimerA_TimerConfig gTIMER_CTRLTimerConfig = {
    .period     = TIMER_CTRL_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC_UP,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_CTRL_init(void) {

    DL_TimerA_setClockConfig(TIMER_CTRL_INST,
        (DL_TimerA_ClockConfig *) &gTIMER_CTRLClockConfig);

    DL_TimerA_initTimerMode(TIMER_CTRL_INST,
        (DL_TimerA_TimerConfig *) &gTIMER_CTRLTimerConfig);
    DL_TimerA_enableInterrupt(TIMER_CTRL_INST , DL_TIMERA_INTERRUPT_LOAD_EVENT);
    DL_TimerA_enableClock(TIMER_CTRL_INST);





}



static const DL_UART_Main_ClockConfig gUART_LX225ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_LX225Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_LX225_init(void)
{
    DL_UART_Main_setClockConfig(UART_LX225_INST, (DL_UART_Main_ClockConfig *) &gUART_LX225ClockConfig);

    DL_UART_Main_init(UART_LX225_INST, (DL_UART_Main_Config *) &gUART_LX225Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115211.52
     */
    DL_UART_Main_setOversampling(UART_LX225_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_LX225_INST, UART_LX225_IBRD_32_MHZ_115200_BAUD, UART_LX225_FBRD_32_MHZ_115200_BAUD);



    DL_UART_Main_enable(UART_LX225_INST);
}

