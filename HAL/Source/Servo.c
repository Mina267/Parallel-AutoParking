#include "StdTypes.h"
#include "Timers.h"
#include "DIO_interface.h"
#include "MemMap.h"
#include "Servo_Interface.h"

void Servo_Init(void)
{
	Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE, TIMER1_SCALER_8);
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	// freq 50 Hz
	OCR1A = 19999;
}


void Servo_Setposition(u16 angle)
{
	OCR1B = ((angle * (u32)2000) / 1800) + 499;
}

void Servo_Setposition2(u16 angle)
{
	OCR1B = ((angle * (u32)1000) / 1800) + 999;
}



/*************************** Operate servo with timer0 and Dio pin *****************************/

static u8 overFlow;
static volatile u8 compare;
static u16 freq_OverFlow;
static volatile u8 flag = 0;


static void OV_CallBack(void)
{
	
	TCNT0 = 6;
	static u8 c;
	c++;
	if (c == overFlow)
	{
		if (compare == 0)
		{
			DIO_WritePin(SERVO_PIN, LOW);
			
		}
		else
		{
			OCR0 = compare;
			flag = 1;
		}
	}
	
	if (c == freq_OverFlow)
	{
		DIO_WritePin(SERVO_PIN, HIGH);
		c = 0;
	}
	
	
}

static void OC_CallBack(void)
{
	
	if (flag)
	{
		DIO_WritePin(SERVO_PIN, LOW);
		flag = 0;
	}
	
}

void Servo_Init_8Bit(void)
{
	TIMER0_Init(TIMER0_NORMAL_MODE, TIMER0_SCALER_8);
	TIMER0_OC0Mode(OC0_DISCONNECTED);
	TIMER0_OC_SetCallBack(OC_CallBack);
	TIMER0_OV_SetCallBack(OV_CallBack);
	TIMER0_OC_InterruptEnable();
	TIMER0_OV_InterruptEnable();
	TCNT0 = 6;
}

void Servo_Setposition_8Bit(u16 angle)
{
	u16 Duty = ((angle * (u32)1000) / 1800) + 999;
	u16 freq = 50;
	freq_OverFlow = (1000000 / freq) / 250;
	Duty -= (Duty / 250) * 5;
	overFlow = Duty / 250;
	compare = Duty - overFlow * 250;
}