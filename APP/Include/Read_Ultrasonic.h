


#ifndef READ_ULTRASONIC_H_
#define READ_ULTRASONIC_H_


typedef enum
{
	_1ST_ULTRASONIC = 0,
	_2ND_ULTRASONIC,
	_3RD_ULTRASONIC,
	_4TH_ULTRASONIC,
	NUM_OF_ULTRASONIC,
}Read_Ultrasonic_t;


// Add Number of ultraSonic sensors
#ifdef ULTRASONIC_READ_ARRAY
const ULTRASONIC_type Ultrasonic_pins[NUM_OF_ULTRASONIC] =
{
	US1,
	US2,
	US3,
	US4,
};

#endif


void Read_Ultrasonic_Init(void);
void Read_Ultrasonic_Runnable(void);
u16 Read_Ultrasonic_Getter(Read_Ultrasonic_t UltraSonic);


#endif /* READ_ULTRASONIC_H_ */