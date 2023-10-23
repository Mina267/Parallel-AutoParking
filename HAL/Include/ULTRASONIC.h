

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "DIO_interface.h"


#define  US1   PINC0
#define  US2   PINC1
#define  US3   PINC2
#define  US4   PINC3

typedef   DIO_Pin_type ULTRASONIC_type;

typedef enum{
	ULTRASONIC_1=PIND2,
	ULTRASONIC_2=PIND6,
	ULTRASONIC_3=PIND3,
	ULTRASONIC_4=PIND5,
	}ULTRASONIC_type2;


typedef enum
{
	ULTRA_NEW_DISTANCE,
	ULTRA_OLD_DISTANCE,
	}ULTRASONIC_Distance_t;

// OCRA Adjust with TOP of OCRA for Servo Motor.
#define TOP_OCRA	19999

void ULTRASONIC_Init(void);


u8 ULTRASONIC_GetDistance(ULTRASONIC_type us,u16*pdistance);
/*u16 ULTRASONIC_GetDistance2(ULTRASONIC_type2 us);*/


void ULTRASONICInt_Init(void);
void ULTRASONIC_StartRead(ULTRASONIC_type us);
u16 ULTRASONIC_DistanceGetter(void);
ULTRASONIC_Distance_t ULTRASONIC_DistanceGetterCheck(u16 *Pdistance);

#endif /* ULTRASONIC_H_ */