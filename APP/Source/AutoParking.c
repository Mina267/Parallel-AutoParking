# define F_CPU 8000000
#include <util/delay.h>

#include "StdTypes.h"
#include "MemMap.h"
#include "Timers.h"
#include "Read_Ultrasonic.h"
#include "Timers_Services.h"
#include "BCM.h"
#include "UART_Services.h"
#include "MOTOR_interface.h"
#include "Servo_Interface.h"
#include "LCD_interface.h"
#include "LEDS.h"
#include "AutoParking.h"
#include "AutoParking_Private.h"
#include "AutoParking_Cfg.h"
#include "UART_Interface.h"



typedef enum
{
	SEARCHING_SPOT,
	PARKING_PROTOCOL,
	DETECT_OBSTALE,
	REVERSE_PARKING,
	PARKING_DONE
	}Parking_Status;


/*Parking_Status*/ 
	
static volatile u16 Car_velocity;
/* Finding parking Spot Variables */
static volatile bool_t StartCompDis_Flag = FALSE;
static volatile u16 Distance;
static volatile u16 DistanceToStart_Parking;
static volatile bool_t PLaceFit_FirstFlag = FALSE;
static volatile bool_t PLaceFit_SecondFlag = FALSE;
static volatile bool_t ParkingProtocol_flag = FALSE;
static volatile bool_t SpotCondition_flag = FALSE;
static bool_t ResetToFindingParkingSpot_flag = TRUE;
static u8 Sent_flags[4] = {1, 1, 1, 1};

/* Parking Protocol Variables */
static volatile u8 ParkingSteps_flag = FIRST_STEP;
static volatile bool_t StartStep_flag = TRUE;
static volatile bool_t ParkingDone_Flag = FALSE;
static volatile Direction_status Dir_Motor = M_CCW;
/* Reverse Parking Protocol Variables */
static volatile bool_t WaitingHindrance_flag = FALSE;
static volatile bool_t ReverseParkingProtocol_flag = FALSE;
static volatile u32 HindranceCnt = 0;
static bool_t Handicaps_flag = FALSE;


void AutoParking_Init(void)
{
	Servo_Init();
	Read_Ultrasonic_Init();
	Servo_Setposition2(SERVO_DEFAULTANGLE);
	
	// Calculate Distance
	Timer1_OVF_SetCallBack(Timer1_OV_CallBack_func);
	Timer1_OVF_InterruptEnable();
	
	
	//Speed of Car in cm/sec 
	Car_velocity = START_CAR_VELOCITY;
	
	
	/* Motor Start configuration */
	TIMER0_Init(TIMER0_PHASECORRECT_MODE, TIMER0_SCALER_1024);
	TIMER0_OC0Mode(OC0_NON_INVERTING);
	MOTOR_Init();
	MOTOR_Speed_dir(CAR_MOTOR, 80, M_CW);
	
	// Parking Steps
	TIMER2_Init(TIMER2_NORMAL_MODE, TIMER2_SCALER_64);
	TIMER2_OV_SetCallBack(OCR_timer2_callBack);
	TIMER2_OV_InterruptEnable();
	
	// Send Message of car status with UART
	UART_Init(UART_9600_BAUDRATE);
	BCM_SendStringInit();
	
	sei();
	
}






void AutoParking_Runnable(void)
{
	Read_Ultrasonic_Runnable();
	
	/*
	LCD_SetCursor(0,0);
	LCD_WriteNumber_4D(Read_Ultrasonic_Getter(SIDE_FRONT_ULTRA));
	*/
	BCM_SendStringRunnable();
	

	//ParkingProtocol_flag = TRUE;
	/* Execute parking protocol will system in parking mode and not done parking */ 
	if ((ParkingProtocol_flag) && (!ParkingDone_Flag))
	{
		Parking_Protocol();
	}
	else
	{
		if (ResetToFindingParkingSpot_flag)
		{
			Servo_Setposition2(SERVO_DEFAULTANGLE);
			MOTOR_Speed_dir(CAR_MOTOR, 80, M_CW);
			ResetToFindingParkingSpot_flag = FALSE;
		}
		/* Finding Parking spot */
		FindingParkingSpot_Protocol();
	}
	
	/* Display Car state in LCD */
	DisplayOn_LCD();

	
	
	
	
}


static void FindingParkingSpot_Protocol(void)
{
	/* If Side Front UltraSonic Find width for car.
	 * Then start to compute distance.
	 * And wait to find this distance will fit car length or not */
	if (Read_Ultrasonic_Getter(SIDE_FRONT_ULTRA) > (CAR_WIDTH + WIDTH_TOLERANCE))
	{
		
		StartCompDis_Flag = TRUE;
	}
	/* If width decrease that not fit the width of 
	 * car reset distance and stop compute distance */
	else
	{
		StartCompDis_Flag = FALSE;
		Distance = 0;
	}
	
	
	/* If Distance of Computed large enough to fit car Length.
	 * Set flag that car found first parking spot */
	if (Distance >= (CAR_LENGTH + LENGTH_TOLERANCE))
	{
		PLaceFit_FirstFlag = TRUE;
	}
	
	/* If Side Back UltraSonic Find width for car.
	 * Set second flag that car found required width */
	if (Read_Ultrasonic_Getter(SIDE_BACK_ULTRA) > (CAR_WIDTH + WIDTH_TOLERANCE))
	{
		
		PLaceFit_SecondFlag = TRUE;
	}
	
	
	
	
	/* When Distance calculated is Larger than one and half of length of the car start Parking Protocol */
	if (DistanceToStart_Parking >= (CAR_LENGTH + LENGTH_TOLERANCE))
	{
		TIMER2_OV_InterruptEnable();
		ParkingProtocol_flag = TRUE;
		
	}
	
	/* If Spot Condition Satisfied. 
	 * Move car for distance equal to car length to start parking */
	if (PLaceFit_FirstFlag && PLaceFit_SecondFlag)
	{
		SpotCondition_flag = TRUE;
	}
	
}






// Time of Interrupt is 20 ms
static void Timer1_OV_CallBack_func(void)
{
	// Calculate Distance When Side Front Ultra Find Enough Width
	if (StartCompDis_Flag)
	{
		Distance = Distance + (Car_velocity / 50);
	}
	
	// Calculate Distance needed for car in front to start Parking mode.
	if (SpotCondition_flag)
	{
		DistanceToStart_Parking += (Car_velocity / 50);
	}
	
}





static void Parking_Protocol(void)
{
	if (!ReverseParkingProtocol_flag)
	{
		Detect_Obstacle();
	}
		
	if (StartStep_flag)
	{
		Parking_steps();
		StartStep_flag = FALSE;
	}
	
	Adjust_Car();
	
	
}



static void Parking_steps(void)
{
	
	MOTOR_Speed_dir(CAR_MOTOR, 0 , M_STOP);
	_delay_ms(ENGINE_STOP_DELAY);
	LCD_SetCursor(0, 0);
	if (!ReverseParkingProtocol_flag)
	{
		LCD_WriteString("    Parking       ");
		Sent_flags[3] = 1;	
		BCM_SendStringSetter("Car is Parking. ");
	}
	else
	{
		LCD_WriteString("Reverse Parking");
		BCM_SendStringSetter("Car can not Parking is this spot. Reveres Parking Process. ");
	}
	
	/* First Step */
	if (ParkingSteps_flag == FIRST_STEP)
	{
		Servo_Setposition2(SERVO_DEFAULTANGLE - 450);
		_delay_ms(SERVO_ADJ_DELAY);
		MOTOR_Speed_dir(CAR_MOTOR, 50 , Dir_Motor);
		// time
		
	}
	/* Second Step */
	else if (ParkingSteps_flag == SECOND_STEP)
	{
		Servo_Setposition2(SERVO_DEFAULTANGLE);
		_delay_ms(SERVO_ADJ_DELAY);
		MOTOR_Speed_dir(CAR_MOTOR, 50 , Dir_Motor);
		// time
	}
	/* Third Step */
	else if (ParkingSteps_flag == THIRD_STEP)
	{
		Servo_Setposition2(450 + SERVO_DEFAULTANGLE);
		_delay_ms(SERVO_ADJ_DELAY);
		MOTOR_Speed_dir(CAR_MOTOR, 50 , Dir_Motor);
		// time
	}
	/* Fourth Step */
	else if (ParkingSteps_flag == FOURTH_STEP)
	{
		Servo_Setposition2(SERVO_DEFAULTANGLE);
		_delay_ms(SERVO_ADJ_DELAY);
		// time
	}

}

/* Adjust car position  if the space behind car is to large */
static void Adjust_Car(void)
{
	static bool_t AdjustMSG_flag = TRUE;
	/* Fifth Step */
	if (ParkingSteps_flag == FIFTH_STEP)
	{
		
		if (Read_Ultrasonic_Getter(BACK_RIGHT_ULTRA) < (LENGTH_TOLERANCE / 2) ||
			(Read_Ultrasonic_Getter(BACK_LEFT_ULTRA) < (LENGTH_TOLERANCE / 2)))
		{
			if (AdjustMSG_flag)
			{
				BCM_SendStringSetter("Car Adjust itself. ");
				AdjustMSG_flag = FALSE;
			}
			
			MOTOR_Speed_dir(CAR_MOTOR, 50 , M_CW);
		}
		/* If car is adjust then car is finishing it parking */ 
		else
		{
			MOTOR_Speed_dir(CAR_MOTOR, 0 , M_STOP);
			ParkingDone_Flag =  TRUE;
		}
	}
}





static void Detect_Obstacle(void)
{
	if (ParkingSteps_flag >= FIRST_STEP && ParkingSteps_flag <= THIRD_STEP)
	{
		
		if ((Read_Ultrasonic_Getter(BACK_RIGHT_ULTRA) <= (MIN_DIS_OFBARRIER)) ||
			(Read_Ultrasonic_Getter(BACK_LEFT_ULTRA) <= (MIN_DIS_OFBARRIER)))
		{
			WaitingHindrance_flag = TRUE;
			StartStep_flag = FALSE;
			if (Handicaps_flag == FALSE)
			{
				MOTOR_Speed_dir(CAR_MOTOR, 0 , M_STOP);
				Handicaps_flag = TRUE;
			}
		}
		else
		{	
			HindranceCnt = 0;
			WaitingHindrance_flag = FALSE;
			if (Handicaps_flag)
			{
				StartStep_flag = TRUE;
				Handicaps_flag = FALSE;
			}
		}
		
		
	}
}





// 1ms
static void OCR_timer2_callBack(void)
{
	TCNT2 = 132;
	
	static u32 Time_Cnt = 0;
	
	/* If System in parking protocol and there is no any obstacle that prevent parking process */
	if ((ParkingProtocol_flag) && (!WaitingHindrance_flag))
	{
		// Parking Stop Flag Increment
		Time_Cnt++;
		
		/* When time of the first step finish move to second step */
		if (Time_Cnt == _1ST_STEP)
		{
			ParkingSteps_flag = SECOND_STEP;
			StartStep_flag = TRUE;
		}
		/* When time of the second step finish move to Third step */
		else if (Time_Cnt == _2ND_STEP)
		{
			ParkingSteps_flag = THIRD_STEP;
			StartStep_flag = TRUE;
		}
		/* When time of the Third step finish move to Fourth step */
		else if (Time_Cnt == _3RD_STEP)
		{
			ParkingSteps_flag = FOURTH_STEP;
			StartStep_flag = TRUE;
		}
		/* When time of the Fourth step finish move to Fifth step */
		else if (Time_Cnt == _4TH_STEP)
		{
			ParkingSteps_flag = FIFTH_STEP;
		}
		/* At Finishing fifth step parking protocol is done */
	}
	
	
	/* waiting specific time when car find any backward obstacle by 
	 * backward ultrasonic sensor Detect any barrier */
	if ((WaitingHindrance_flag))
	{	
		HindranceCnt++;
		/* If time waiting reach to max time to wait barrier to remove */
		if (HindranceCnt == HINDRANCE_TIME)
		{
			/* Reverse motor direction to start reverse protocol */
			Dir_Motor = M_CW;
			ReverseParkingProtocol_flag = TRUE;
			/* Ensure that the parking protocol starting or not 
			 * to start reverse parking protocol */ 
			if (Time_Cnt > MIN_TIME_TO_START_REVESE_PARKING)
			{
				StartStep_flag = TRUE;	
			}
			
		}
	}
	
	/* Reverse Parking if there is barrier */
	if (ReverseParkingProtocol_flag == TRUE)
	{
		Time_Cnt--;

		/* If Reverse parking protocol finish Reset system to start searching for new spot */ 
		if (Time_Cnt == 0)
		{
			Reset_System();
		}
		else if (Time_Cnt == _1ST_STEP)
		{
			ParkingSteps_flag = FIRST_STEP;
			StartStep_flag = TRUE;
		}
		else if (Time_Cnt == _2ND_STEP)
		{
			ParkingSteps_flag = SECOND_STEP;
			StartStep_flag = TRUE;
		}
	
	}
	
}



static void DisplayOn_LCD(void)
{

	LCD_SetCursor(0, 0);
	
	if ((SpotCondition_flag) && (!ParkingProtocol_flag))
	{
		if (Sent_flags[0] == 1)
		{
			LCD_WriteString("Park Spot Found");
			BCM_SendStringSetter("Car founding parking spot. ");
			Sent_flags[0] = 0;
			 Flag_true(0);
		}
	}
	else if ((ParkingDone_Flag))
	{
		if (Sent_flags[1] == 1)
		{
			LCD_WriteString("   Car Parked");
			BCM_SendStringSetter("Car Parked. ");
			Sent_flags[1] = 0;
			Flag_true(1);
		}
	}
	else if (!ParkingProtocol_flag)
	{
		if (Sent_flags[2] == 1)
		{
			LCD_WriteString(" Searching Spot    ");
			BCM_SendStringSetter("Car searching for parking spot. ");
			Sent_flags[2] = 0;
			Flag_true(2);
		}
	}
	else if (WaitingHindrance_flag)
	{
		if (Sent_flags[3] == 1)
		{
			LCD_WriteString("    Barrier    ");
			BCM_SendStringSetter("There is Barrier. Car Wait Barrier to remove.");
			Sent_flags[3] = 0;
			Flag_true(3);
		}
	}
}


static void Flag_true (u8 Index)
{
	for (u8 FlagIndex = 0; FlagIndex < 4; FlagIndex++)
	{
		if (FlagIndex != Index)
		{
			Sent_flags[FlagIndex] = 1;
		}
	}
}

/* Reset system to start state */
static void Reset_System(void)
{
	ParkingProtocol_flag = FALSE;
	StartStep_flag = TRUE;
	Dir_Motor = M_CCW;
	ReverseParkingProtocol_flag = FALSE;
	ParkingSteps_flag = FIRST_STEP;
	ParkingDone_Flag = FALSE;
	

	
	WaitingHindrance_flag = FALSE;
	HindranceCnt = 0;
	Handicaps_flag = FALSE;
	
	Servo_Setposition2(SERVO_DEFAULTANGLE);
	MOTOR_Speed_dir(CAR_MOTOR, 80, M_CW);
	ResetToFindingParkingSpot_flag = TRUE;
	// Reset Variables
	Distance = 0;
	DistanceToStart_Parking = 0;
	PLaceFit_SecondFlag = FALSE;
	PLaceFit_FirstFlag = FALSE;
	StartCompDis_Flag = FALSE;
	SpotCondition_flag = FALSE;
}
