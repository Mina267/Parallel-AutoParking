#include "StdTypes.h"
#include "DIO_interface.h"
#include "MOTOR_interface.h"
#include "MOTOR_cfg.h"
#include "MOTOR_private.h"
#include "MemMap.h"

void MOTOR_Init(void)
{
	//DIO_WritePin(MotorPinsArray[M1][EN], HIGH);
	//DIO_WritePin(MotorPinsArray[M2][EN], HIGH);
	//DIO_WritePin(MotorPinsArray[M3][EN], HIGH);
	//DIO_WritePin(MotorPinsArray[M4][EN], HIGH);
}



Error_type MOTOR_Stop(MOTOR_type motor)
{
	Error_type ErrorStatus = OK;
	if (motor > NUMBER_MOTORS)
	{
		ErrorStatus = OUT_OF_RANGE;
	}
	else
	{
		DIO_WritePin(MotorPinsArray[motor][IN1], LOW);
		DIO_WritePin(MotorPinsArray[motor][IN2], LOW);
	}
	return ErrorStatus;
}

Error_type MOTOR_CW(MOTOR_type motor)
{
	Error_type ErrorStatus = OK;
	if (motor > NUMBER_MOTORS)
	{
		ErrorStatus = OUT_OF_RANGE;
	}
	else
	{
		DIO_WritePin(MotorPinsArray[motor][IN1], HIGH);
		DIO_WritePin(MotorPinsArray[motor][IN2], LOW);
	}
	return ErrorStatus;
	
	
}
Error_type MOTOR_CCW(MOTOR_type motor)
{
	Error_type ErrorStatus = OK;
	if (motor > NUMBER_MOTORS)
	{
		ErrorStatus = OUT_OF_RANGE;
	}
	else
	{
		DIO_WritePin(MotorPinsArray[motor][IN1], LOW);
		DIO_WritePin(MotorPinsArray[motor][IN2], HIGH);
	}
	return ErrorStatus;
}

/*  speed from 0 to 100  %**/
void MOTOR_Speed(MOTOR_type motor,u8 speed)
{
	switch (motor)
	{
		case M1:
		M1_PWM_PIN  = (speed * 255) / 100;
		break;
		
		case M2:
		M2_PWM_PIN = (speed * 255) / 100;
		break;
		
		case M3:
		M3_PWM_PIN = (speed * 255) / 100;
		break;
		
		case M4:
		M4_PWM_PIN = (speed * 255) / 100;
		break;
	}
	
}


void MOTOR_Speed_dir(MOTOR_type motor,u8 speed , Direction_status status)
{
	switch (motor)
	{
		case M1:
		M1_PWM_PIN  = (speed * 255) / 100;
		break;
		
		case M2:
		M2_PWM_PIN = (speed * 255) / 100;
		break;
		
		case M3:
		M3_PWM_PIN = (speed * 255) / 100;
		break;
		
		case M4:
		M4_PWM_PIN = (speed * 255) / 100;
		break;
	}
	
	
	switch (status)
	{
		case M_CW:
		DIO_WritePin(MotorPinsArray[motor][M_IN1], HIGH);
		DIO_WritePin(MotorPinsArray[motor][M_IN2], LOW);
		break;
		case M_CCW:
		DIO_WritePin(MotorPinsArray[motor][M_IN1], LOW);
		DIO_WritePin(MotorPinsArray[motor][M_IN2], HIGH);
		break;
		case M_STOP:
		DIO_WritePin(MotorPinsArray[motor][M_IN1], LOW);
		DIO_WritePin(MotorPinsArray[motor][M_IN2], LOW);
		break;
	}

}


void MOTOR_dir(MOTOR_type motor, Direction_status status)
{
	switch (status)
	{
		case M_CW:
		DIO_WritePin(MotorPinsArray[motor][M_IN1], HIGH);
		DIO_WritePin(MotorPinsArray[motor][M_IN2], LOW);
		break;
		case M_CCW:
		DIO_WritePin(MotorPinsArray[motor][M_IN1], LOW);
		DIO_WritePin(MotorPinsArray[motor][M_IN2], HIGH);
		break;
		case M_STOP:
		DIO_WritePin(MotorPinsArray[motor][M_IN1], LOW);
		DIO_WritePin(MotorPinsArray[motor][M_IN2], LOW);
		break;
	}
}