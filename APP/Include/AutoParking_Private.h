

#ifndef AUTOPARKING_PRIVATE_H_
#define AUTOPARKING_PRIVATE_H_

#define FIRST_STEP		1
#define SECOND_STEP		2
#define THIRD_STEP		3
#define FOURTH_STEP		4
#define FIFTH_STEP		5

#define _1ST_STEP	((u32)FIRST_STEP_TIME)
#define _2ND_STEP	((u32)FIRST_STEP_TIME + (u32)SECOND_STEP_TIME)
#define _3RD_STEP	((u32)FIRST_STEP_TIME + (u32)SECOND_STEP_TIME + (u32)THIRD_STEP_TIME)
#define _4TH_STEP	((u32)FIRST_STEP_TIME + (u32)SECOND_STEP_TIME + (u32)THIRD_STEP_TIME + (u32)FOURTH_STEP_TIME)
#define _5TH_STEP	((u32)FIRST_STEP_TIME + (u32)SECOND_STEP_TIME + (u32)THIRD_STEP_TIME + (u32)FOURTH_STEP_TIME  + (u32)FIFTH_STEP_TIME)

#define SERVO_DEFAULTANGLE 900

#define MIN_TIME_TO_START_REVESE_PARKING	50

typedef enum
{
	SIDE_FRONT_ULTRA = _1ST_ULTRASONIC,
	SIDE_BACK_ULTRA = _2ND_ULTRASONIC,
	BACK_RIGHT_ULTRA = _3RD_ULTRASONIC,
	BACK_LEFT_ULTRA = _4TH_ULTRASONIC,
	}UltraSonic_Pos_t;



// Finding Spot Protocol.
static void Timer1_OV_CallBack_func(void);
static void FindingParkingSpot_Protocol(void);

//Parking Protocol.
static void Parking_Protocol(void); 
static void OCR_timer2_callBack(void);
static void Parking_steps(void);
static void Adjust_Car(void);

static void Detect_Obstacle(void);

// LCD Display.
static void DisplayOn_LCD(void);
static void Flag_true (u8 Index);

static void Reset_System(void);

#endif /* AUTOPARKING_PRIVATE_H_ */





