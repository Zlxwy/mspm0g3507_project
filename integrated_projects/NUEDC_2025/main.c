#include "ti_msp_dl_config.h"
#include "delay.h"
#include "OLED.h"
#include "encoder.h"
#include "ctrl.h"
#include "moto.h"
#include "lx225.h"

uint16_t run_mode = 0;
uint16_t round_cnt = 1; // 圈数从1~5循环

int main(void)
{
    SYSCFG_DL_init();

    delay_init(CPUCLK_FREQ);
    OLED_Init();
    Encoder_Init();
    Moto_Init();
    Ctrl_Init();
    LX225_SetServoAngle(4, 120, 0);
    LX225_SetServoAngle(5, 120, 0);


    /*按键选择激光打靶，或者选择循迹*/
    while (1) {
        if (DL_GPIO_readPins(GPIO_KEY_PORT, GPIO_KEY_add_PIN) == 0) { // 按下了add键
            delay_ms(20);
            while (DL_GPIO_readPins(GPIO_KEY_PORT, GPIO_KEY_add_PIN) == 0) {;}
            delay_ms(20);
            run_mode = run_mode == 0 ? 1 : 0;
        }
        if (DL_GPIO_readPins(GPIO_KEY_PORT, GPIO_KEY_enter_PIN) == 0) { // 按下enter键
            delay_ms(20);
            while (DL_GPIO_readPins(GPIO_KEY_PORT, GPIO_KEY_enter_PIN) == 0) {;}
            delay_ms(20);
            OLED_Clear();
            break;
        }
        if (run_mode == 0) OLED_Printf(0, 0, OLED_6X8, "Choose Run Mode: XJ  "); // 循迹
        else if (run_mode == 1) OLED_Printf(0, 0, OLED_6X8, "Choose Run Mode: JGDB"); // 激光打靶
        
        OLED_Update();
    }

    if (run_mode == 0) goto xunji;
    else if (run_mode == 1) goto jiguang;

    /*按键选择圈数循环*/
    xunji:
    DL_GPIO_clearPins(GPIO_FAKE_PORT, GPIO_FAKE_OUT_PIN); // 用一个GPIO来点亮openmv上的LED，符合题目的视觉模块开启要求
    while (1) {
        if (DL_GPIO_readPins(GPIO_KEY_PORT, GPIO_KEY_add_PIN) == 0) { // 按下了add键
            delay_ms(20);
            while (DL_GPIO_readPins(GPIO_KEY_PORT, GPIO_KEY_add_PIN) == 0) {;}
            delay_ms(20);
            round_cnt = round_cnt>=5?1:round_cnt+1; // 圈数从1~5循环
        }
        if (DL_GPIO_readPins(GPIO_KEY_PORT, GPIO_KEY_enter_PIN) == 0) { // 按下enter键
            delay_ms(20);
            while (DL_GPIO_readPins(GPIO_KEY_PORT, GPIO_KEY_enter_PIN) == 0) {;}
            delay_ms(20);
            Moto_start(); // 启动电机（启动电机PWM定时器的计数）
            Ctrl_Run(); // 启动控制定时中断（启动定时中断定时器的计数）
            OLED_Clear();
            OLED_Update();
            goto MainWhile; // 按下了enter键，则跳出循环，进入下一阶段
        }
        OLED_Printf(0, 0, OLED_6X8, "Round: %d", round_cnt);
        OLED_Update();
    }

    jiguang:
    DL_GPIO_setPins(GPIO_FAKE_PORT, GPIO_FAKE_OUT_PIN);
    LX225_SetServoAngle(4,158,800);
    LX225_SetServoAngle(5,111.2,800);
    delay_ms(1500);
    DL_GPIO_setPins(GPIO_JDQ_PORT, GPIO_JDQ_JDQ1_PIN);

    MainWhile: while (1) {
        // DL_GPIO_togglePins(GPIO_JDQ_PORT, GPIO_JDQ_JDQ1_PIN);
        // delay_ms(500);
        OLED_Update();
    }
}
