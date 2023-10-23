
#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


void LCD_Init(void);
void LCD_Clear(void);
void LCD_WriteNumber(s32 num);
void LCD_WriteFloat(s32 num, s32 frac);
void LCD_WriteChar(u8 ch);
void LCD_WriteString(c8 *str);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u8 num);
/** line 0:1  cell 0:15 **/
void LCD_SetCursor(u8 line ,u8 cell);
void LCD_SetCursorString(u8 line,u8 cell,u8*str);
void LCD_ClearCell(u8 line, u8 cell, u8 num);
void LCD_WriteStringOverFlow(u8 line ,u8 cell, c8 *str);
void LCD_WriteNumber_4D(u16 num);
void LCD_makeNewShape(u8 *ShapeArray, u8 ShapeIndex);
void LCD_WriteHexU32(u32 num);
void LCD_WriteNumber_5D(u32 num);
void LCD_WriteFrame(c8 *str, u8 len);
void LCD_WriteNumber_3D(u16 num);
void LCD_WriteNumber_2D(u16 num);

#endif /* LCD_INTERFACE_H_ */