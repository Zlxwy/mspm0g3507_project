#include "lx225.h"

// 115200波特率
// 8bits数据位
// 无校验位
// 1位停止位
// 失能硬件流控

/*interface***********************************************************************/
#define SEND_BYTE_BLOCKING(b) do { \
    while (DL_UART_isTXFIFOFull(UART_LX225_INST)); \
    DL_UART_transmitData(UART_LX225_INST, b); \
} while (0) // 阻塞地发送一个字节
/***********************************************************************interface*/

ServoCommand
    SERVO_MOVE_TIME_WRITE = {1, 7}, // 在指定时间内转动到指定角度
    SERVO_MOVE_TIME_WAIT_WRITE = {7, 7}, //指定转动时间和转动角度，在SERVO_MOVE_START发送后才执行
    SERVO_MOVE_START = {11, 3}, //立即执行SERVO_MOVE_TIME_WAIT_WRITE写入的参数
    SERVO_MOVE_STOP = {12, 3}, //停止舵机当前的转动
    SERVO_ID_WRITE = {13, 4}, //更改舵机的ID号
    SERVO_ANGLE_LIMIT_WRITE = {20, 7}, //限制舵机的转动角度值，可掉电保存
    SERVO_OR_MOTOR_MODE_WRITE = {29, 7}, //设置为舵机或电机模式，不掉电保存
    SERVO_LED_CTRL_WRITE = {33, 4}; //控制LED的亮灭



/************************************************************
************数据处理函数，用来处理两个字节的数据***************
************************************************************/

/**
 * @brief 处理角度数据（仅供源文件内部使用）
 * @param Angle 角度值，范围限制: [0,1000]，对应[0,240]度，精度0.24度
 * @param GetArray 接收数组
 */
static void ProcessAngle(uint16_t Angle, uint8_t *GetArray) {
    GetArray[0] = Angle; // 低8位数据
    GetArray[1] = Angle >> 8; // 高8位数据
}

/**
 * @brief 处理时间数据（仅供源文件内部使用）
 * @param Time 时间值，范围限制: [0,30000]，对应[0,300000]毫秒，精度1毫秒
 * @param GetArray 接收数组
 */
static void ProcessTime(uint16_t ms, uint8_t *GetArray) {
    GetArray[0] = ms; // 低8位数据
    GetArray[1] = ms >> 8; // 高8位数据
}

/**
 * @brief 处理速度数据（仅供源文件内部使用）
 * @param Speed 速度值，范围限制: [-1000,1000]（对应顺时针最大转速~逆时针最大转速，这个转速具体角速度多少暂时未知）
 * @param GetArray 接收数组
 */
static void ProcessSpeed(int16_t Speed, uint8_t *GetArray) {
    GetArray[0] = Speed; // 低8位数据
    GetArray[1] = Speed >> 8; // 高8位数据
}

/**
 * @brief 计算LX-16A指定格式的校验字节（仅供源文件内部使用）
 * @note Checksum = ~(ID号+数据长度+指令号+多个参数)
 * @param ServoID 舵机ID号
 * @param sc 指令名（已包含数据长度和指令号）
 * @param CmdArray 指令存放的数组（已转换的、可直接按顺序发送的数据）
 * @retval LX-16A指定格式的校验字节
 */
static uint8_t CalChecksum(uint8_t ServoID, ServoCommand sc, uint8_t *CmdArray) {
    uint8_t Checksum = ServoID + sc.DataLen + sc.CommandIndex;
    for (uint16_t i=0; i<sc.DataLen-3; i++) Checksum += CmdArray[i];
    return ~Checksum;
}

/**
 * @brief 串口发送控制指令给总线舵机（仅供源文件内部使用）
 * @param ServoID 要控制的舵机ID号
 * @param sc 指令名（已包含数据长度和指令号）
 * @param CmdArray 指令存放的数组（已转换的、可直接按顺序发送的数据）
 */
static void LX225_SendCommand(uint8_t ServoID, ServoCommand sc, uint8_t *CmdArray) {
    for (uint16_t i=0; i<2; i++) DL_UART_transmitDataBlocking(UART_LX225_INST,0x55); //发送帧头
    DL_UART_transmitDataBlocking(UART_LX225_INST, ServoID); // 发送舵机ID
    DL_UART_transmitDataBlocking(UART_LX225_INST, sc.DataLen); // 发送数据长度
    DL_UART_transmitDataBlocking(UART_LX225_INST, sc.CommandIndex); // 发送指令号
    for (uint16_t i=0; i<sc.DataLen-3; i++) DL_UART_transmitDataBlocking(UART_LX225_INST,CmdArray[i]); // 发送参数数据
    DL_UART_transmitDataBlocking(UART_LX225_INST, CalChecksum(ServoID,sc,CmdArray)); // 发送校验和
}


/************************************************************
*************************直接操控函数*************************
************************************************************/

/**
 * @brief 控制舵机在指定时间内转动到指定位置
 * @param ServoID 舵机ID号
 * @param Angle 角度位置，单位为度，范围限制: [0,240]
 * @param ms 转动时间，单位为毫秒，范围限制: [0,30000]
 */
void LX225_SetServoAngle(uint8_t ServoID, float Angle, uint16_t ms) {
    uint16_t Angle_uint16 = Angle * 25.0 / 6.0; // 将[0,240]度的角度值映射到[0,1000]
    uint8_t param[4]; // 用来存放发送的数据

    ProcessAngle(Angle_uint16, &param[0]); // 将角度值转换为两个字节的数据
    ProcessTime(ms, &param[2]); // 将时间值转换为两个字节的数据
    LX225_SendCommand(ServoID, SERVO_MOVE_TIME_WRITE, param);
}

/**
 * @brief 更改舵机的ID号
 * @param ServoID 舵机当前的ID号
 * @param NewID 舵机要更改的新ID号
 */
void LX225_SetServoID(uint8_t ServoID, uint8_t NewID) {
    LX225_SendCommand(ServoID, SERVO_ID_WRITE, &NewID);
}