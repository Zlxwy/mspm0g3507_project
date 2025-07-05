#ifndef __LED_MATRIX_H__
#define __LED_MATRIX_H__

#include "ti_msp_dl_config.h"

#define LED_MATRIX_WIDTH  32
#define LED_MATRIX_HEIGHT 32
#define LED_ON   true
#define LED_OFF  false

extern volatile uint32_t __disp_pic[32];

typedef enum {
    CharWidth_6 = 6,
    CharWidth_8 = 8,
    CharWidth_11 = 11,
    CharWidth_16 = 16,
} LEDMatrixCharWidth_t;

void LEDMatrix_Init(void);
void LEDMatrix_ClearAll(void);

void LEDMatrix_SetPixel(uint16_t x, uint16_t y, bool bitval);
void LEDMatrix_DrawLine(int x0, int y0, int x1, int y1);
void LEDMatrix_DrawQuad(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
void LEDMatrix_ShowImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *image);
void LEDMatrix_ShowENChar(uint16_t x, uint16_t y, char ch, LEDMatrixCharWidth_t size);
void LEDMatrix_ShowCNChar(uint16_t x, uint16_t y, uint16_t index, LEDMatrixCharWidth_t size);

uint32_t LEDMatrix_Uint32RotateRight(uint32_t val, unsigned int n);
uint32_t LEDMatrix_Uint32RotateLeft(uint32_t val, unsigned int n);
void LEDMatrix_RowsRotateMove(uint16_t row1, uint16_t row2, int n);

void LEDMatrix_TestPic(void);

#endif // __LED_MATRIX_H__