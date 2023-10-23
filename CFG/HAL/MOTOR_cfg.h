
#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_


#define  NUMBER_MOTORS   4

/******************PIN config ***********************************/


#define   M1_IN1	PINB0
#define   M1_IN2	PINB1
#define   M1_EN		PINB3

#define   M2_IN1	PINC3
#define   M2_IN2	PINC4
#define   M2_EN		PIND7

#define   M3_IN1	PINC4
#define   M3_IN2	PINC5
#define   M3_EN		PINB2

#define   M4_IN1	PINC6
#define   M4_IN2	PINC7
#define   M4_EN		PINB3

#define M1_PWM_PIN	OCR0
#define M2_PWM_PIN	OCR2
#define M3_PWM_PIN	OCR1A
#define M4_PWM_PIN	OCR1B



#endif /* MOTOR_CFG_H_ */