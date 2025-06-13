#ifndef __OLED_H
#define __OLED_H
#include "ti_msp_dl_config.h"

void OLED_WriteCommand(uint8_t command);
void OLED_WriteData(uint8_t data);
void OLED_SetCursor(uint8_t Y, uint8_t X);
void OLED_Clear(void);
void OLED_Init(void);

void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ClearLine(uint8_t line1, uint8_t line2);
void OLED_ClearColumn(uint8_t column1,uint8_t column2);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowString_FromLineToLine(uint8_t startline,char *str,uint8_t endline);
void OLED_ShowString_FromPointToLine(uint8_t Line,uint8_t Column,char *String,uint8_t endline);
void OLED_ShowNum(uint8_t Line,uint8_t Column,uint32_t Number,uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line,uint8_t Column,int32_t Number,uint8_t Length);
void OLED_ShowHexNum(uint8_t Line,uint8_t Column,uint32_t Number,uint8_t Length);
void OLED_ShowBinNum(uint8_t Line,uint8_t Column,uint32_t Number,uint8_t Length);

#endif
