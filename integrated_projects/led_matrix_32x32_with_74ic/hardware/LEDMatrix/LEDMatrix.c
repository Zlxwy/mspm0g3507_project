#include "LEDMatrix.h"
#include "LEDMatrix_Data.h"
#include "hc595.h"
#include "decoder_5_32.h"

// 每个uint32_t元素对应一行，从0~31对应上到下
// 所有显示图案的操作函数，都是对此显存数组进行操作
volatile uint32_t __disp_pic[32] = {0};
// 点阵屏从左到右，对应每个元素从高位到低位
// __disp_pic[0]
// __disp_pic[1]
// ...
// __disp_pic[31]

// 定时中断，用于扫描点阵屏显示，按行扫描
uint16_t DispRow = 0;
void TIMER_LED_MATRIX_INST_IRQHandler(void) {
    switch ( DL_Timer_getPendingInterrupt(TIMER_LED_MATRIX_INST) ) {
        case DL_TIMER_IIDX_LOAD:
            HC595OutputBits(0x00000000, 32); // 清除先前的显示
            DispRow = (DispRow==31) ? (0) : (DispRow+1); // 行号循环递增
            HC595ShiftBits(__disp_pic[DispRow], 32); // 当前行移入hc595移位寄存器
            YMQWritePort(DispRow); // 打开对应行的行显
            HC595LatchBits(); // 输出hc595移位寄存器中的数据
            break;
        default: break;
    }
}





// 初始化点阵屏显示
void LEDMatrix_Init(void) {
    LEDMatrix_ClearAll();
    NVIC_EnableIRQ(TIMER_LED_MATRIX_INST_INT_IRQN); // 打开定时器中断
}

// 熄灭点阵屏的所有LED
void LEDMatrix_ClearAll(void) {
    for (uint16_t i=0; i<LED_MATRIX_WIDTH; i++) {
        __disp_pic[i] = 0x00000000;
    }
}





/**
  * 坐标轴定义：
  * 左上角为(0, 0)点
  * 横向向右为X轴，取值范围：0~31
  * 纵向向下为Y轴，取值范围：0~31
  * 
  *          0        X axis      31
  *         .----------------------->
  *    0    |
  *         |
  *         |
  *         |
  *  Y axis |
  *         |
  *         |
  *         |
  *   31    |
  *         v
  * 
  */

/**
 * @brief 在点阵屏上设置一个像素点
 * @param x 像素点位置，取值范围[0,31]
 * @param y 像素点位置，取值范围[0,31]
 * @param bitval 要设置的值，LED_ON表示点亮，LED_OFF表示熄灭
 */
void LEDMatrix_SetPixel(uint16_t x, uint16_t y, bool bitval) {
    if (x>=32 || y>=32) return;
    uint32_t RowMask = 1 << (31-x);
    if (bitval) __disp_pic[y] |= RowMask;
    else        __disp_pic[y] &= ~RowMask;
}

static int intabs(int a) { return (a < 0) ? -a : a; }
void LEDMatrix_DrawLine(int x0, int y0, int x1, int y1) {
    int dx = intabs(x1 - x0);
    int dy = intabs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while (1) {
        LEDMatrix_SetPixel(x0, y0, LED_ON);  // 绘制当前点

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

/**
 * @brief 在点阵屏上显示一张图片
 * @param x 图片起始位置，取值范围[0,31]
 * @param y 图片起始位置，取值范围[0,31]
 * @param width 图片宽度，取值范围[1,32]
 * @param height 图片高度，取值范围[1,32]
 * @param image 图片数据
 */
// 图片数据格式如下所示，
// uint8_t(h->l) uint8_t(h->l) uint8_t(h->l) ...
// uint8_t(h->l) uint8_t(h->l) uint8_t(h->l) ...
// ...
void LEDMatrix_ShowImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *image) {
    uint16_t bytes_per_row = (width+7)/8;
    uint8_t temp = 0;
    for (uint16_t i=0; i<height; i++) {
        for (uint16_t j=0; j<bytes_per_row; j++) {
            temp = image[i*bytes_per_row + j];
            uint16_t xOffset = j * 8;
            for (uint16_t k=0; k<8; k++) {
                if ((xOffset + k) >= width) break;
                LEDMatrix_SetPixel(x+xOffset+k, y+i, ((temp&0x80)==0)?LED_OFF:LED_ON);
                temp <<= 1;
            }
        }
    }
}

/**
 * @brief 在点阵屏上显示一个英文字符
 * @param x 字符起始位置，取值范围[0,31]
 * @param y 字符起始位置，取值范围[0,31]
 * @param ch 要显示的字符
 * @param size 字符宽度大小
 */
void LEDMatrix_ShowENChar(uint16_t x, uint16_t y, char ch, LEDMatrixCharWidth_t size) {
    switch (size) {
        case CharWidth_6:
            LEDMatrix_ShowImage(x, y, 6, 8, &enchar_6x8[ch-' '][0]);
            break;
        case CharWidth_8:
            LEDMatrix_ShowImage(x, y, 8, 16, &enchar_8x16[ch-' '][0]);
            break;
        default: break;
    }
}

/**
 * @brief 在点阵屏上显示一个中文字符
 * @param x 字符起始位置，取值范围[0,31]
 * @param y 字符起始位置，取值范围[0,31]
 * @param index 要显示的字符索引
 * @param size 字符宽度大小
 */
void LEDMatrix_ShowCNChar(uint16_t x, uint16_t y, uint16_t index, LEDMatrixCharWidth_t size) {
    switch (size) {
        case CharWidth_16:
            LEDMatrix_ShowImage(x, y, 16, 16, &cnchar_16x16[index][0]);
            break;
        case CharWidth_11:
            LEDMatrix_ShowImage(x, y, 11, 16, &cnchar_11x16[index][0]);
            break;
        default: break;
    }
}





// 将一个uint32_t的值进行循环右移n位
uint32_t LEDMatrix_Uint32RotateRight(uint32_t val, unsigned int n) {
    n %= 32; // 防止大于32
    return (val >> n) | (val << (32 - n));
}

// 循环左移函数：将uint32_t的值循环左移n位
uint32_t LEDMatrix_Uint32RotateLeft(uint32_t val, unsigned int n) {
    n %= 32; // 确保 n 不超过 31
    return (val << n) | (val >> (32 - n));
}

/**
 * @brief 将指定行范围的行，左右移n位
 * @param row1 起始行，取值范围[0,31]
 * @param row2 结束行，取值范围[0,31]
 * @param n 移动位数，负数为左移，正数右移，取值范围[-31,31]
 */
void LEDMatrix_RowsRotateMove(uint16_t row1, uint16_t row2, int n) {
    for (uint16_t i=row1; i<=row2; i++) {
        if (n < 0) {
            __disp_pic[i] = LEDMatrix_Uint32RotateLeft(__disp_pic[i], -n);
        } else {
            __disp_pic[i] = LEDMatrix_Uint32RotateRight(__disp_pic[i], n);
        }
    }
}





// 测试一个点阵屏显示
void LEDMatrix_TestPic(void) {
    for (uint16_t i=0; i<LED_MATRIX_HEIGHT; i+=2) {
        LEDMatrix_SetPixel(i/2, i, LED_ON); // (0,0) (1,2) (2,4) ...
        LEDMatrix_SetPixel(i/2, i+1, LED_ON); // (0,1) (1,3) (2,5) ...
    }
}