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

DL_TimerA_backupConfig gTIMER_LED_MATRIXBackup;
DL_TimerA_backupConfig gTIMER_TIME_CNTBackup;

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
    SYSCFG_DL_TIMER_LED_MATRIX_init();
    SYSCFG_DL_TIMER_TIME_CNT_init();
    SYSCFG_DL_UART_DISP_init();
    /* Ensure backup structures have no valid state */
	gTIMER_LED_MATRIXBackup.backupRdy 	= false;
	gTIMER_TIME_CNTBackup.backupRdy 	= false;


}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_saveConfiguration(TIMER_LED_MATRIX_INST, &gTIMER_LED_MATRIXBackup);
	retStatus &= DL_TimerA_saveConfiguration(TIMER_TIME_CNT_INST, &gTIMER_TIME_CNTBackup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_restoreConfiguration(TIMER_LED_MATRIX_INST, &gTIMER_LED_MATRIXBackup, false);
	retStatus &= DL_TimerA_restoreConfiguration(TIMER_TIME_CNT_INST, &gTIMER_TIME_CNTBackup, false);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerA_reset(TIMER_LED_MATRIX_INST);
    DL_TimerA_reset(TIMER_TIME_CNT_INST);
    DL_UART_Main_reset(UART_DISP_INST);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerA_enablePower(TIMER_LED_MATRIX_INST);
    DL_TimerA_enablePower(TIMER_TIME_CNT_INST);
    DL_UART_Main_enablePower(UART_DISP_INST);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_DISP_IOMUX_RX, GPIO_UART_DISP_IOMUX_RX_FUNC);

    DL_GPIO_initDigitalOutput(GPIO_HC595_DS_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_HC595_SHCP_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_HC595_STCP_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_HC595_NOE_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_YMQ_PIN_0_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_YMQ_PIN_1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_YMQ_PIN_2_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_YMQ_PIN_3_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_YMQ_PIN_4_IOMUX);

    DL_GPIO_clearPins(GPIO_YMQ_PORT, GPIO_YMQ_PIN_0_PIN |
		GPIO_YMQ_PIN_1_PIN |
		GPIO_YMQ_PIN_2_PIN |
		GPIO_YMQ_PIN_3_PIN |
		GPIO_YMQ_PIN_4_PIN);
    DL_GPIO_enableOutput(GPIO_YMQ_PORT, GPIO_YMQ_PIN_0_PIN |
		GPIO_YMQ_PIN_1_PIN |
		GPIO_YMQ_PIN_2_PIN |
		GPIO_YMQ_PIN_3_PIN |
		GPIO_YMQ_PIN_4_PIN);
    DL_GPIO_clearPins(GPIO_HC595_PORT, GPIO_HC595_DS_PIN |
		GPIO_HC595_SHCP_PIN |
		GPIO_HC595_STCP_PIN |
		GPIO_HC595_NOE_PIN);
    DL_GPIO_enableOutput(GPIO_HC595_PORT, GPIO_HC595_DS_PIN |
		GPIO_HC595_SHCP_PIN |
		GPIO_HC595_STCP_PIN |
		GPIO_HC595_NOE_PIN);

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

}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   32000000 Hz = 32000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gTIMER_LED_MATRIXClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 0U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_LED_MATRIX_INST_LOAD_VALUE = (312.5 us * 32000000 Hz) - 1
 */
static const DL_TimerA_TimerConfig gTIMER_LED_MATRIXTimerConfig = {
    .period     = TIMER_LED_MATRIX_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC_UP,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_LED_MATRIX_init(void) {

    DL_TimerA_setClockConfig(TIMER_LED_MATRIX_INST,
        (DL_TimerA_ClockConfig *) &gTIMER_LED_MATRIXClockConfig);

    DL_TimerA_initTimerMode(TIMER_LED_MATRIX_INST,
        (DL_TimerA_TimerConfig *) &gTIMER_LED_MATRIXTimerConfig);
    DL_TimerA_enableInterrupt(TIMER_LED_MATRIX_INST , DL_TIMERA_INTERRUPT_LOAD_EVENT);
	NVIC_SetPriority(TIMER_LED_MATRIX_INST_INT_IRQN, 1);
    DL_TimerA_enableClock(TIMER_LED_MATRIX_INST);





}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   15625 Hz = 4000000 Hz / (8 * (255 + 1))
 */
static const DL_TimerA_ClockConfig gTIMER_TIME_CNTClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 255U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_TIME_CNT_INST_LOAD_VALUE = (1s * 15625 Hz) - 1
 */
static const DL_TimerA_TimerConfig gTIMER_TIME_CNTTimerConfig = {
    .period     = TIMER_TIME_CNT_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC_UP,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_TIME_CNT_init(void) {

    DL_TimerA_setClockConfig(TIMER_TIME_CNT_INST,
        (DL_TimerA_ClockConfig *) &gTIMER_TIME_CNTClockConfig);

    DL_TimerA_initTimerMode(TIMER_TIME_CNT_INST,
        (DL_TimerA_TimerConfig *) &gTIMER_TIME_CNTTimerConfig);
    DL_TimerA_enableInterrupt(TIMER_TIME_CNT_INST , DL_TIMERA_INTERRUPT_LOAD_EVENT);
	NVIC_SetPriority(TIMER_TIME_CNT_INST_INT_IRQN, 0);
    DL_TimerA_enableClock(TIMER_TIME_CNT_INST);





}



static const DL_UART_Main_ClockConfig gUART_DISPClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_DISPConfig = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_DISP_init(void)
{
    DL_UART_Main_setClockConfig(UART_DISP_INST, (DL_UART_Main_ClockConfig *) &gUART_DISPClockConfig);

    DL_UART_Main_init(UART_DISP_INST, (DL_UART_Main_Config *) &gUART_DISPConfig);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115211.52
     */
    DL_UART_Main_setOversampling(UART_DISP_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_DISP_INST, UART_DISP_IBRD_32_MHZ_115200_BAUD, UART_DISP_FBRD_32_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_DISP_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);
    /* Setting the Interrupt Priority */
    NVIC_SetPriority(UART_DISP_INST_INT_IRQN, 0);


    DL_UART_Main_enable(UART_DISP_INST);
}

