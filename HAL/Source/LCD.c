#include "StdTypes.h"
#include "LCD_interface.h"
#include "MemMap.h"
#include "DIO_interface.h"
#include "LCD_cfg.h"
#include "LCD_private.h"
#include "Utils.h"

# define F_CPU 8000000
#include <util/delay.h>


#if LCD_MODE == EIGHTBITS

static void WriteIns(u8 ins)
{
	
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

static void WriteData(u8 data)
{
	DIO_WritePin(RS, HIGH);
	DIO_WritePort(LCD_PORT, data);
	DIO_WritePin(EN, HIGH);
	_delay_ms(1);
	DIO_WritePin(EN, LOW);
	_delay_ms(1);
}


void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(INS_FIRST8BIT);
	WriteIns(CUR_OFF);
	WriteIns(CLR_DIS);
	_delay_ms(1);
	WriteIns(RIGHT_TO_LEFT);
}

#elif LCD_MODE == FOURBITS

static void WriteIns(u8 ins)
{
	
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7, READ_BIT(ins, 7));
	DIO_WritePin(D6, READ_BIT(ins, 6));
	DIO_WritePin(D5, READ_BIT(ins, 5));
	DIO_WritePin(D4, READ_BIT(ins, 4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(D7, READ_BIT(ins, 3));
	DIO_WritePin(D6, READ_BIT(ins, 2));
	DIO_WritePin(D5, READ_BIT(ins, 1));
	DIO_WritePin(D4, READ_BIT(ins, 0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}



static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7, READ_BIT(data, 7));
	DIO_WritePin(D6, READ_BIT(data, 6));
	DIO_WritePin(D5, READ_BIT(data, 5));
	DIO_WritePin(D4, READ_BIT(data, 4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	DIO_WritePin(D7, READ_BIT(data, 3));
	DIO_WritePin(D6, READ_BIT(data, 2));
	DIO_WritePin(D5, READ_BIT(data, 1));
	DIO_WritePin(D4, READ_BIT(data, 0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}


void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0X02);
	WriteIns(INS_FIRST4BIT);
	WriteIns(CUR_OFF);
	WriteIns(CLR_DIS);
	_delay_ms(1);
	WriteIns(RIGHT_TO_LEFT);
}

#endif










void LCD_Clear()
{
	WriteIns(CLR_DIS);
	_delay_ms(1);
}

void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}


#define MAX_NUMIN_STR 16
void LCD_WriteNumber(s32 num)
{
	u8 StrOfNum[MAX_NUMIN_STR];
	s8 NumSize = 0;
	s8 StrIndex;
	bool_t SignFlag = FALSE;
	
	if (num < 0)
	{
		num =-num;
		SignFlag = TRUE;
	}
	else if (num == 0)
	{
		StrOfNum[NumSize] = '0';
		NumSize++;
	}
	
	
	while (num)
	{
		StrOfNum[NumSize] = (num % 10) + '0';
		num /= 10;
		NumSize++;
	}
	
	if (SignFlag)
	{
		StrOfNum[NumSize] = '-';
		NumSize++;
	}
	
	for (StrIndex = NumSize - 1; StrIndex >= 0; StrIndex--)
	{
		LCD_WriteChar(StrOfNum[StrIndex]);
	}
}


void LCD_WriteFloat(s32 num, s32 frac)
{
	LCD_WriteNumber(num);
	LCD_WriteChar('.');
	LCD_WriteNumber(frac);
}


void LCD_WriteString(c8 *str)
{
	u8 strIndex;
	for (strIndex = 0; str[strIndex]; strIndex++)
	{
		LCD_WriteChar(str[strIndex]);
	}
}

void LCD_WriteFrame(c8 *str, u8 len)
{
	u8 strIndex;
	for (strIndex = 0; strIndex < len; strIndex++)
	{
		LCD_WriteChar(str[strIndex]);
		LCD_WriteChar(' ');
	}
}



void LCD_WriteStringOverFlow(u8 line ,u8 cell, c8 *str)
{
	static u8 cnt;
	cnt = cell % 16;
	
	
	u8 strIndex;
	for (strIndex = 0; str[strIndex]; strIndex++)
	{
		LCD_SetCursor(line, cnt);
		LCD_WriteChar(str[strIndex]);
		
		cnt++;
		if (cnt == 16)
		{
			if (line == 0)
			{
				line = 1;
			}
			else if (line == 1)
			{
				line = 0;
			}
			cnt = 0;
		}
	}
}



void LCD_WriteBinary(u8 num)
{
	u8 bit = 1 << (SIZEOF_U8 - 1);
	while (bit)
	{
		if (num & bit)
		{
			LCD_WriteChar('1');
		}
		else
		{
			LCD_WriteChar('0');
		}
		bit = bit >> 1;
	}
}


void LCD_WriteHex(u8 num)
{
	u8 hex_array[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	/*LCD_WriteChar('0');
	LCD_WriteChar('x');*/
	LCD_WriteChar(hex_array[(num >> 4) & 0x0f]);
	LCD_WriteChar(hex_array[(num >> 0) & 0x0f]);
}


void LCD_WriteHexU32(u32 num)
{
	u8 hex_array[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	LCD_WriteChar('0');
	LCD_WriteChar('x');
	
	u8 bits = 0;
	while (num)
	{
		bits += 4;
		LCD_WriteChar(hex_array[(num) & 0x0f]);
		num = num >> bits;
		
	}
	
}


void LCD_SetCursor(u8 line ,u8 cell)
{
	if (line == 0)
	{
		WriteIns(0x80|cell);
	}
	else if (line == 1)
	{
		WriteIns(0x80|0x40|cell);
	}
	_delay_ms(1);
}




void LCD_ClearCell(u8 line, u8 cell, u8 num)
{
	LCD_SetCursor(line, cell);
	for (u8 i = 0; i < num; i++)
	{
		LCD_WriteChar(' ');
	}
}






void LCD_makeNewShape(u8 *ShapeArray, u8 Location)
{
	WriteIns(0x40 | (Location * 8));
	
	for (u8 i = 0; i < 8; i++)
	{
		WriteData(ShapeArray[i]);
	}
	LCD_SetCursor(0,0);
}

void LCD_WriteNumber_4D(u16 num)
{
	//LCD_WriteChar(((num%100000)/10000)+'0');
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}


void LCD_WriteNumber_7D(u32 num)
{
	LCD_WriteChar(((num % 10000000) / 1000000) +'0');
	LCD_WriteChar(((num % 1000000) / 100000) +'0');
	LCD_WriteChar(((num % 100000) / 10000) +'0');
	LCD_WriteChar(((num % 10000) / 1000) +'0');
	LCD_WriteChar(((num % 1000) / 100) +'0');
	LCD_WriteChar(((num % 100) / 10) +'0');
	LCD_WriteChar(((num % 10) / 1) +'0');
}

void LCD_WriteNumber_5D(u32 num)
{
	LCD_WriteChar(((num%100000)/10000)+'0');
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}

void LCD_WriteNumber_3D(u16 num)
{
	//LCD_WriteChar(((num%100000)/10000)+'0');
	//LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}


void LCD_WriteNumber_2D(u16 num)
{
	//LCD_WriteChar(((num%100000)/10000)+'0');
	//LCD_WriteChar(((num%10000)/1000)+'0');
	//LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}
