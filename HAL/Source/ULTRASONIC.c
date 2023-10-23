

#include "StdTypes.h"
#include "DIO_interface.h"
#include "Timers.h"
#include "ULTRASONIC.h"
#include "MemMap.h"

#define  F_CPU 8000000
#include <util/delay.h>


static volatile u16 t1;
static volatile u16 t2;
static volatile u8 Ultra_flag = 0;
#define Busy_Time 23000


/***************************** UltraSonic Busy W8 ******************************/
void ICU_CallBack_Ultrasoinc(void);

void ULTRASONIC_Init(void)
{
	Timer1_ICU_SetCallBack(ICU_CallBack_Ultrasoinc);
	Timer1_ICU_InterruptEnable();
}



u8 ULTRASONIC_GetDistance(ULTRASONIC_type us, u16* pdistance)
{
	TCNT1 = 0;
	u16 Busy_Cnt = 0;
	u16 time;
	Ultra_flag = 0;
	
	Timer1_InputCaptureEdge(RISING);
	DIO_WritePin(us, HIGH);
	_delay_us(10);
	DIO_WritePin(us, LOW);	
	while ((Ultra_flag < 2) && (Busy_Cnt < Busy_Time))
	{
		_delay_us(1);
		Busy_Cnt++;
	}
	
	if (Ultra_flag == 2)
	{
		time = t2 - t1;
		*pdistance = time  / 58;
		return 1;
	}
	
	return 0;
	
	
}

void ICU_CallBack_Ultrasoinc(void)
{
	
	
	if (Ultra_flag == 0)
	{
		t1 = ICR1;
		Ultra_flag++;
		Timer1_InputCaptureEdge(FALLING);
	}
	else if (Ultra_flag == 1)
	{
		t2 = ICR1;
		Ultra_flag++;
	}
}

/********************************* UltraSonic Read by Interrupt ************************************/

static volatile u16 Distance;
static volatile bool_t Get_UltraRead = FALSE;
static volatile  u8 OV_Cnt = 0;
static volatile  u8 c2 = 0;


static void ICU_CallBack_Ultrasoinc_Run(void);
static void CallBack_OCRA_OVCnt(void);




void ULTRASONICInt_Init(void)
{
	
	Timer1_ICU_SetCallBack(ICU_CallBack_Ultrasoinc_Run);
	Timer1_ICU_InterruptEnable();
	
	Timer1_OCA_SetCallBack(CallBack_OCRA_OVCnt);
	Timer1_OCA_InterruptEnable();

}


void ULTRASONIC_StartRead(ULTRASONIC_type us)
{
	if (Ultra_flag == 0)
	{
		Timer1_InputCaptureEdge(RISING);
		DIO_WritePin(us, HIGH);
		_delay_us(10);
		DIO_WritePin(us, LOW);
		Get_UltraRead = FALSE;
		//_delay_ms(10);
		Ultra_flag++;
	}
	
}

u16 ULTRASONIC_DistanceGetter(void)
{
	Ultra_flag = 0;
	return Distance;
}


ULTRASONIC_Distance_t ULTRASONIC_DistanceGetterCheck(u16 *Pdistance)
 {
	 ULTRASONIC_Distance_t Status = ULTRA_OLD_DISTANCE;
	 if (Ultra_flag == 3)
	 {
		 Status = ULTRA_NEW_DISTANCE;
		 Ultra_flag = 0;
	 }
	 *Pdistance = Distance;
	 return Status;
 }

static void ICU_CallBack_Ultrasoinc_Run(void)
{
	if (Ultra_flag == 1)
	{
		t1 = ICR1;
		OV_Cnt=0;
		Ultra_flag++;
		Timer1_InputCaptureEdge(FALLING);
	}
	else if (Ultra_flag == 2)
	{
		t2 = ICR1;
		// OCRA Adjust with TOP of OCRA for Servo Motor.
		/* Timer Prescaler 64 */
		// Distance = (((s32)t2 - (s32)t1) * (s32) 345)  / (s32)2500;
		Distance = ((t2 - t1) + (OV_Cnt * (TOP_OCRA + 1)))  / 58;
		OV_Cnt=0;
		Ultra_flag++;
		Get_UltraRead = TRUE;
	}
}


static void CallBack_OCRA_OVCnt(void)
{
	OV_Cnt++;
}