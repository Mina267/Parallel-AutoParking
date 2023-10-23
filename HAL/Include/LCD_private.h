

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

static void WriteIns(u8 ins);
static void WriteData(u8 data);

#define FOURBITS	4
#define EIGHTBITS	8


#define INS_FIRST8BIT	0X38
#define INS_FIRST4BIT	0x28
#define CUR_OFF			0X0C
#define CUR_ONFIXED		0X0E
#define CUR_ONBLINK		0X0F
#define CLR_DIS			0x01
#define RIGHT_TO_LEFT	0X06
#define LEFT_TO_RIGHT	0X04

#endif /* LCD_PRIVATE_H_ */