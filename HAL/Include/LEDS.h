


#ifndef LEDS_H_
#define LEDS_H_

#define YEL_PIN		0
#define RED_PIN		PINC0
#define GRN_PIN		PINC1
#define BLU_PIN		PINC2


typedef enum
{
	RED_LED,
	GRN_LED,
	BLU_LED,
	YEL_LED,
	}LEDS_types;

void LEDS_On (LEDS_types led);
void LEDS_Off (LEDS_types led);

#endif /* LEDS_H_ */