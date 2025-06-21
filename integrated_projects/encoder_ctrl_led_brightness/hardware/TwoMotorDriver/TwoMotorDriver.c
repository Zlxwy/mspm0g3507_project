#include "TwoMotorDriver.h"

// 如何使用？
// 在 interface 中接入以下宏定义
// - 两个电机 PWM 的最大计数值
// - 两个电机设置比较值的操作函数
// - 两个电机设置转向的操作函数
// - 两个电机停止的操作函数
// - 两个电机刹车的操作函数
// - 电机初始化操作

/*interface****************************************************************************************************************/
#define MOTOR_L_PERIOD_CNT  1000 // 左轮 PWM 的最大计数值
#define MOTOR_R_PERIOD_CNT  1000 // 右轮 PWM 的最大计数值

#define SET_MOTOR_L_COMPARE(mc) DL_Timer_setCaptureCompareValue(PWM_MOTOR_INST, mc, GPIO_PWM_MOTOR_C0_IDX) // 设置左轮 PWM 占空比
#define SET_MOTOR_R_COMPARE(mc) DL_Timer_setCaptureCompareValue(PWM_MOTOR_INST, mc, GPIO_PWM_MOTOR_C1_IDX) // 设置右轮 PWM 占空比

#define MOTOR_DIR_UP  ((bool)1) // 电机正转方向
#define MOTOR_DIR_DN  ((bool)0) // 电机反转方向

#define SET_MOTOR_L_DIR(dir) do { \
    bool ddiirr = dir; \
    DL_GPIO_writePinsVal(GPIO_MOTOR_PORT, GPIO_MOTOR_LIN1_PIN, ddiirr == MOTOR_DIR_DN ? GPIO_MOTOR_LIN1_PIN : 0); \
    DL_GPIO_writePinsVal(GPIO_MOTOR_PORT, GPIO_MOTOR_LIN2_PIN, ddiirr != MOTOR_DIR_DN ? GPIO_MOTOR_LIN2_PIN : 0); \
} while (0) // 设置左轮转向方向（宏定义中传入的参数不能使用两次，因此这里创建一个临时变量接收宏定义传入的参数）
#define SET_MOTOR_R_DIR(dir) do { \
    bool ddiirr = dir; \
    DL_GPIO_writePinsVal(GPIO_MOTOR_PORT, GPIO_MOTOR_RIN1_PIN, ddiirr == MOTOR_DIR_DN ? GPIO_MOTOR_RIN1_PIN : 0); \
    DL_GPIO_writePinsVal(GPIO_MOTOR_PORT, GPIO_MOTOR_RIN2_PIN, ddiirr != MOTOR_DIR_DN ? GPIO_MOTOR_RIN2_PIN : 0); \
} while (0) // 设置右轮转向方向（宏定义中传入的参数不能使用两次，因此这里创建一个临时变量接收宏定义传入的参数）

#define STOP_MOTOR_L do { \
    DL_GPIO_writePinsVal(GPIO_MOTOR_PORT, GPIO_MOTOR_LIN1_PIN, 0); \
    DL_GPIO_writePinsVal(GPIO_MOTOR_PORT, GPIO_MOTOR_LIN2_PIN, 0); \
} while (0) // 停止左轮转动
#define STOP_MOTOR_R do { \
    DL_GPIO_writePinsVal(GPIO_MOTOR_PORT, GPIO_MOTOR_RIN1_PIN, 0); \
    DL_GPIO_writePinsVal(GPIO_MOTOR_PORT, GPIO_MOTOR_RIN2_PIN, 0); \
} while (0) // 停止右轮转动

#define BRAKE_MOTOR_L do { \
    DL_GPIO_writePinsVal(GPIO_MOTOR_PORT, GPIO_MOTOR_LIN1_PIN, GPIO_MOTOR_LIN1_PIN); \
    DL_GPIO_writePinsVal(GPIO_MOTOR_PORT, GPIO_MOTOR_LIN2_PIN, GPIO_MOTOR_LIN2_PIN); \
} while (0) // 左轮刹车
#define BRAKE_MOTOR_R do { \
    DL_GPIO_writePinsVal(GPIO_MOTOR_PORT, GPIO_MOTOR_RIN1_PIN, GPIO_MOTOR_RIN1_PIN); \
    DL_GPIO_writePinsVal(GPIO_MOTOR_PORT, GPIO_MOTOR_RIN2_PIN, GPIO_MOTOR_RIN2_PIN); \
} while (0) // 右轮刹车

void MotorInit(void) {
    DL_Timer_startCounter(PWM_MOTOR_INST);
    STOP_MOTOR_L; // 停止左电机
    STOP_MOTOR_R; // 停止左电机
} // 初始化电机 PWM
/****************************************************************************************************************interface*/

/**
 * @brief 将速度的百分比数值映射至计数值（函数内无数值范围限制，勿超出范围）
 * @param SpeedPercent 速度百分比，范围限制: [0,+100]
 * @param CntMAX 最大计数值，范围限制: [0,UINT32_MAX]
 * @retval 返回映射后的计数值
 */
static uint32_t SpeedPercent2Cnt(float SpeedPercent, uint32_t CntMAX) {
    return ((float)CntMAX * SpeedPercent / 100.0f);
}

/**
 * @brief 计算给定浮点数的绝对值。如果输入值为负数，则返回其相反数；否则，返回原值。
 * @param val 输入的浮点数，无范围限制
 * @retval 返回输入浮点数的绝对值
 */
static float FloatAbs(float val) {
    return (val < 0.0f) ? -val : val;
}

/**
 * @brief 将给定的浮点数限制在指定的最小值和最大值之间。
 * @param val 待限制的浮点数
 * @param min 最小值
 * @param max 最大值
 * @retval 返回限制后的浮点数
 */
float MotorSpeedClamp(float val, float min, float max) {
    return (val < min) ? min : (val > max ? max : val);
}

/**
 * @brief 设置左右轮的速度百分比（函数内无数值范围限制，勿超出范围）
 * @param percent_l 左轮速度百分比，范围限制: [-100,+100]
 * @param percent_r 右轮速度百分比，范围限制: [-100,+100]
 */
void SetMotorSpeed(float percent_l, float percent_r) {
    SET_MOTOR_L_DIR(percent_l >= 0.0f ? MOTOR_DIR_UP : MOTOR_DIR_DN); // 设置左轮方向
    SET_MOTOR_R_DIR(percent_r >= 0.0f ? MOTOR_DIR_UP : MOTOR_DIR_DN); // 设置右轮方向

    percent_l = FloatAbs(percent_l);
    percent_r = FloatAbs(percent_r);

    SET_MOTOR_L_COMPARE(SpeedPercent2Cnt(percent_l, MOTOR_L_PERIOD_CNT));
    SET_MOTOR_R_COMPARE(SpeedPercent2Cnt(percent_r, MOTOR_R_PERIOD_CNT));
}

/**
 * @brief 停止左右两个电机。
 */
void StopMotor(void) {
    STOP_MOTOR_L;
    STOP_MOTOR_R;
}


/**
 * @brief 制动左右两个电机。
 */
void BrakeMotor(void) {
    BRAKE_MOTOR_L;
    BRAKE_MOTOR_R;
}