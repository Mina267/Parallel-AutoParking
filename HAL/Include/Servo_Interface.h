

#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_

void Servo_Init(void);

void Servo_Setposition(u16 angle);
void Servo_Setposition2(u16 angle);


#define SERVO_PIN	PINC0

void Servo_Init_8Bit(void);
void Servo_Setposition_8Bit(u16 angle);

#endif /* SERVO_INTERFACE_H_ */