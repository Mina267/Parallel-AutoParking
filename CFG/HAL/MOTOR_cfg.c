#include "StdTypes.h"
#include "DIO_interface.h"
#include "MOTOR_interface.h"
#include "MOTOR_cfg.h"
#include "MOTOR_private.h"


const DIO_Pin_type MotorPinsArray[NUMBER_MOTORS][MOTOR_PIN_NUMBERS]={
			    /* IN1     IN2     EN  */
	/* motor 1*/{ M1_IN1, M1_IN2, M1_EN},
	/* motor 2*/{ M2_IN1, M2_IN2, M2_EN},
	/* motor 3*/{ M3_IN1, M3_IN2, M3_EN},
	/* motor 4*/{ M4_IN1, M4_IN2, M4_EN},
};