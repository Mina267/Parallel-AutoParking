

#ifndef RELAY_INTERFACE_H_
#define RELAY_INTERFACE_H_

#define _1_RELAY_PIN	PINC4
#define _2_RELAY_PIN	PINC3

typedef enum
{
	_1_RELAY = 1,
	_2_RELAY,
	RELAY_ALL,
}RELAY_t;


void RELAY_On(RELAY_t Relay);
void RELAY_Off(RELAY_t Relay);



#endif /* RELAY_INTERFACE_H_ */