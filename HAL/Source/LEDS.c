#include "StdTypes.h"
#include "DIO_interface.h"
#include "LEDS.h"

void LEDS_On (LEDS_types led)
{
	switch (led)
	{
		case YEL_LED:
		DIO_WritePin(YEL_PIN, HIGH);
		break;
		
		case BLU_LED:
		DIO_WritePin(BLU_PIN, HIGH);
		break;
		
		case GRN_LED:
		DIO_WritePin(GRN_PIN, HIGH);
		break;
		
		case RED_LED:
		DIO_WritePin(RED_PIN, HIGH);
		break;
	}
}

void LEDS_Off (LEDS_types led)
{
	switch (led)
	{
		case YEL_LED:
		DIO_WritePin(YEL_PIN, LOW);
		break;
		
		case BLU_LED:
		DIO_WritePin(BLU_PIN, LOW);
		break;
		
		case GRN_LED:
		DIO_WritePin(GRN_PIN, LOW);
		break;
		
		case RED_LED:
		DIO_WritePin(RED_PIN, LOW);
		break;
	}
}