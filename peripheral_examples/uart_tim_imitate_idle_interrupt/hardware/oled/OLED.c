#include "OLED.h"
#include "OLED_FONT.h"

/***********************************************************************************
********************************硬件IIC基本读写函数*********************************
***********************************************************************************/
/**程序以MSPM0G3507的外设I2C0连接，在使用之前，一定要先去SysConfig配置好I2C0的外设**
	*PA0——SDA
	*PA1——SCL
	**SysConfig配置项目**
	*勾选Enable Controller Mode
	*时钟源选择BUSCLK
	*Standard Bus Speed选择Fast Mode Plus (1MHz)
	*PinMux选择I2C0，引脚选择PA0（I2C0_SDA）和PA1（I2C0_SCL）
	**/

#define IIC_OLED	I2C0

/**IIC指定地址写**
	*@param		从机未移位的原7位地址
	*@param		从机寄存器的地址
	*@param		要写入的字节
	**/
static void IIC_WriteByte(uint8_t EquiAddr,uint8_t RegAddr,uint8_t Byte)
{
	uint8_t buff[2] = {RegAddr,Byte};
	DL_I2C_fillControllerTXFIFO(IIC_OLED,buff,2);
	//填充主机发送缓存区
	while (!(DL_I2C_getControllerStatus(IIC_OLED) & DL_I2C_CONTROLLER_STATUS_IDLE));
	DL_I2C_startControllerTransfer(IIC_OLED,EquiAddr,DL_I2C_CONTROLLER_DIRECTION_TX,2);
	//主机开始发送，指定IIC外设、从机地址、读写方向（写方向）、数据长度（包含寄存器地址）
	//This function will send Start + Stop automatically.
	while (DL_I2C_getControllerStatus(IIC_OLED) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
}

/**IIC指定地址连续写**
	*@param		从机未移位的原7位地址
	*@param		从机寄存器的地址
	*@param		发送数据存放的数组
	*@param		发送数据的长度
	**/
static void IIC_ScanWrite(uint8_t EquiAddr,uint8_t RegAddr,uint8_t *GetArray,uint16_t len)
{
	uint8_t array[256];
	array[0]=RegAddr;
	for(uint16_t i=0;i<len;i++)
		array[i+1]=GetArray[i];
	
	DL_I2C_fillControllerTXFIFO(IIC_OLED,array,len+1);
	//填充主机发送缓存区
	while (!(DL_I2C_getControllerStatus(IIC_OLED) & DL_I2C_CONTROLLER_STATUS_IDLE));
	DL_I2C_startControllerTransfer(IIC_OLED,EquiAddr,DL_I2C_CONTROLLER_DIRECTION_TX,len+1);
	//主机开始发送，指定IIC外设、从机地址、读写方向（写方向）、数据长度（包含寄存器地址）
	while (DL_I2C_getControllerStatus(IIC_OLED) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
}

/**IIC指定地址读**
	*@param		从机的原7位地址
	*@param		从机寄存器的地址
	*@retval	读取的一个字节
	**/
static uint8_t IIC_ReadByte(uint8_t EquiAddr,uint8_t RegAddr)
{
	DL_I2C_fillControllerTXFIFO(IIC_OLED,&RegAddr,1);
	//填充主机发送缓存区（只发个寄存器地址）
	while (!(DL_I2C_getControllerStatus(IIC_OLED) & DL_I2C_CONTROLLER_STATUS_IDLE));
	DL_I2C_startControllerTransfer(IIC_OLED,EquiAddr,DL_I2C_CONTROLLER_DIRECTION_TX,1);
	//主机开始发送，指定IIC外设、从机地址、读写方向（写方向）、数据长度（包含寄存器地址）
	while (DL_I2C_getControllerStatus(IIC_OLED) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
	
	while (!(DL_I2C_getControllerStatus(IIC_OLED) & DL_I2C_CONTROLLER_STATUS_IDLE));
	DL_I2C_startControllerTransfer(IIC_OLED,EquiAddr,DL_I2C_CONTROLLER_DIRECTION_RX,1);
	//主机开始接收，指定IIC外设、从机地址、读写方向（读方向）、要读取的数据长度
	while (DL_I2C_isControllerRXFIFOEmpty(IIC_OLED));
	return DL_I2C_receiveControllerData(IIC_OLED);
}

/**IIC指定地址连续读**
	*@param		从机未移位的原7位地址
	*@param		从机寄存器的地址
	*@param		接收数据的数组
	*@param		接收数据的长度
	**/
static void IIC_ScanRead(uint8_t EquiAddr,uint8_t RegAddr,uint8_t *GetArray,uint16_t len)
{
	DL_I2C_fillControllerTXFIFO(IIC_OLED,&RegAddr,1);
	//填充主机发送缓存区（只发个寄存器地址）
	while (!(DL_I2C_getControllerStatus(IIC_OLED) & DL_I2C_CONTROLLER_STATUS_IDLE));
	DL_I2C_startControllerTransfer(IIC_OLED,EquiAddr,DL_I2C_CONTROLLER_DIRECTION_TX,1);
	//主机开始发送，指定IIC外设、从机地址、读写方向（写方向）、数据长度（包含寄存器地址）
	//This function will send Start + Stop automatically.
	while (DL_I2C_getControllerStatus(IIC_OLED) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
	
	while (!(DL_I2C_getControllerStatus(IIC_OLED) & DL_I2C_CONTROLLER_STATUS_IDLE));
	DL_I2C_startControllerTransfer(IIC_OLED,EquiAddr,DL_I2C_CONTROLLER_DIRECTION_RX,len);
	//主机开始接收，指定IIC外设、从机地址、读写方向（读方向）、要读取的数据长度
	while(len--)
	{
		while (DL_I2C_isControllerRXFIFOEmpty(IIC_OLED));
		*(GetArray++) = DL_I2C_receiveControllerData(IIC_OLED);
	}
}









/***********************************************************************************
*************************基于IIC基本读写函数的OLED驱动函数*************************
***********************************************************************************/
#define OLED_ADDR		0x3C	//未左移的7位原地址0011 1100

void OLED_WriteCommand(uint8_t command)
{IIC_WriteByte(0x3C,0x00,command);}
void OLED_WriteData(uint8_t data)
{IIC_WriteByte(0x3C,0x40,data);}

void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | Y);									//设置Y位置
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//设置X位置高4位
	OLED_WriteCommand(0x00 | (X & 0x0F));					//设置X位置低4位
}

void OLED_Clear(void)
{  
	uint8_t i, j;
	for (j=0;j<8;j++)
	{
		OLED_SetCursor(j,0);
		for(i=0;i<128;i++)
			OLED_WriteData(0x00);
	}
}

/*调用OLED初始化之前，一定要先配置好I2C0外设，初始化延时函数*/
void OLED_Init(void)
{
	uint32_t i,j; for(i=0;i<10000;i++) for(j=0;j<10000;j++);//计100M个数
	OLED_WriteCommand(0xAE);	//关闭显示
	OLED_WriteCommand(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(0x80);
	OLED_WriteCommand(0xA8);	//设置多路复用率
	OLED_WriteCommand(0x3F);
	OLED_WriteCommand(0xD3);	//设置显示偏移
	OLED_WriteCommand(0x00);
	OLED_WriteCommand(0x40);	//设置显示开始行
	OLED_WriteCommand(0xA1);	//设置左右方向，0xA1正常 0xA0左右反置
	OLED_WriteCommand(0xC8);	//设置上下方向，0xC8正常 0xC0上下反置
	OLED_WriteCommand(0xDA);	//设置COM引脚硬件配置
	OLED_WriteCommand(0x12);
	OLED_WriteCommand(0x81);	//设置对比度控制
	OLED_WriteCommand(0xCF);
	OLED_WriteCommand(0xD9);	//设置预充电周期
	OLED_WriteCommand(0xF1);
	OLED_WriteCommand(0xDB);	//设置VCOMH取消选择级别
	OLED_WriteCommand(0x30);
	OLED_WriteCommand(0xA4);	//设置整个显示打开/关闭
	OLED_WriteCommand(0xA6);	//设置正常/倒转显示
	OLED_WriteCommand(0x8D);	//设置充电泵
	OLED_WriteCommand(0x14);
	OLED_WriteCommand(0xAF);	//开启显示
	OLED_Clear();				//OLED清屏
}

/**OLED显示一个字符**
	*@param  Line 行位置，范围：1~4
	*@param  Column 列位置，范围：1~16
	*@param  Char 要显示的一个字符，范围：ASCII可见字符
**/
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{      	
	uint8_t i;
	OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);		//设置光标位置在上半部分
	for (i=0;i<8;i++)
		OLED_WriteData(OLED_F8x16[Char - ' '][i]);			//显示上半部分内容
	OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//设置光标位置在下半部分
	for (i=0;i<8;i++)
		OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);		//显示下半部分内容
}

/**清除指定行列内容**
	*@param 	起始行/起始列
	*@param 	结束行/结束列
**/
void OLED_ClearLine(uint8_t line1, uint8_t line2)
{
	for(uint8_t i=line1;i<=line2;i++)
		for(uint8_t j=1;j<=16;j++)
			OLED_ShowChar(i,j,' ');
}
void OLED_ClearColumn(uint8_t column1,uint8_t column2)
{
	for(uint8_t i=column1;i<=column2;i++)
		for(uint8_t j=1;j<=4;j++)
			OLED_ShowChar(j,i,' ');
}

/**OLED在指定位置显示字符串，单行显示，不自动换行**
  * @param		Line 起始行位置，范围：1~4
  * @param		Column 起始列位置，范围：1~16
  * @param		String 要显示的字符串，范围：ASCII可见字符
  * @retval		无
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
	uint8_t i;
	for (i=0;String[i]!='\0';i++)
		OLED_ShowChar(Line, Column + i, String[i]);
}

/**OLED从起始行显示字符串，到结束行终止显示，可自动换行**
	*@ATTENTION 本函数跳过字符\r和字符\n，不会显示出来
	*@param 	起始行
	*@param 	显示的字符
	*@param 	结束行
	**/
void OLED_ShowString_FromLineToLine(uint8_t startline,char *str,uint8_t endline)
{
	for(uint8_t i=0,j=1;str[i]!='\0';i++)
		if (str[i]!='\r'&&str[i]!='\n')
		{
			OLED_ShowChar(startline,j++,str[i]);
			if (j>=17&&startline<endline) {startline++;j=1;}
			else if (j>=17&&startline==endline) break;
		}
}

/**OLED从指定位置显示字符串，到结束行终止显示，可自动换行**
	*@ATTENTION	本函数跳过字符\r和字符\n，不会显示出来
	*@param		起始行
	*@param 	起始列
	*@param 	显示字符串
	*@param 	终止行
	**/
void OLED_ShowString_FromPointToLine(uint8_t Line,uint8_t Column,char *String,uint8_t endline)
{
	uint8_t i,j;		//j用来保持字符串稳定增加
	for (i=0,j=0; String[j]!='\0';j++)
	{
		if (String[j]!='\r'&&String[j]!='\n')
		{OLED_ShowChar(Line,Column+i,String[j]);i++;}
		if ((Column+i)==17&&Line<endline) {Line+=1;Column=1;i=0;}
		else if ((Column+i)==17&&Line==endline) break;
	}
}

/**OLED次方函数**
	*@retval		返回值等于X的Y次方
  */
static uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

/**OLED显示数字（十进制，正数)**
	*@param		Line 起始行位置，范围：1~4
	*@param		Column 起始列位置，范围：1~16
	*@param		Number 要显示的数字，范围：0~4294967295
	*@param		Length 要显示数字的长度，范围：1~10
	*@retval	无
**/
void OLED_ShowNum(uint8_t Line,uint8_t Column,uint32_t Number,uint8_t Length)
{
	for(uint8_t i=0;i<Length;i++)
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
}

/**OLED显示数字（十进制，带符号数）**
	*@param		Line 起始行位置，范围：1~4
	*@param		Column 起始列位置，范围：1~16
	*@param		Number 要显示的数字，范围：-2147483648~2147483647
	*@param		Length 要显示数字的长度，范围：1~10
	*@retval	无
**/
void OLED_ShowSignedNum(uint8_t Line,uint8_t Column,int32_t Number,uint8_t Length)
{
	uint8_t i;
	uint32_t Number1;
	if (Number >= 0)
	{
		OLED_ShowChar(Line, Column, '+');
		Number1 = Number;
	}
	else
	{
		OLED_ShowChar(Line, Column, '-');
		Number1 = -Number;
	}
	for(i=0;i<Length;i++)							
		OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
}

/**OLED显示数字（十六进制，正数）**
	*@param		Line 起始行位置，范围：1~4
	*@param		Column 起始列位置，范围：1~16
	*@param		Number 要显示的数字，范围：0~0xFFFFFFFF
	*@param		Length 要显示数字的长度，范围：1~8
	*@retval	无
**/
void OLED_ShowHexNum(uint8_t Line,uint8_t Column,uint32_t Number,uint8_t Length)
{
	uint8_t i,SingleNumber;
	for(i=0;i<Length;i++)							
	{
		SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
		if (SingleNumber < 10)
			OLED_ShowChar(Line, Column + i, SingleNumber + '0');
		else
			OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
	}
}

/**OLED显示数字（二进制，正数）**
	*@param		Line 起始行位置，范围：1~4
	*@param		Column 起始列位置，范围：1~16
	*@param		Number 要显示的数字，范围：0~1111 1111 1111 1111
	*@param		Length 要显示数字的长度，范围：1~16
	*@retval	无
**/
void OLED_ShowBinNum(uint8_t Line,uint8_t Column,uint32_t Number,uint8_t Length)
{
	for(uint8_t i=0;i<Length;i++)
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
}
