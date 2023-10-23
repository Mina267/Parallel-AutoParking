#include "StdTypes.h"
#include "DIO_interface.h"
#include "RELAY_Interface.h"


void RELAY_On(RELAY_t Relay)
{
	switch(Relay)
	{
		case _1_RELAY:
		DIO_WritePin(_1_RELAY_PIN, HIGH);
		break;
		
		case _2_RELAY:
		DIO_WritePin(_2_RELAY_PIN, HIGH);
		break;
		
		case RELAY_ALL:
		DIO_WritePin(_1_RELAY_PIN, HIGH);
		DIO_WritePin(_2_RELAY_PIN, HIGH);
	}
}



void RELAY_Off(RELAY_t Relay)
{
	switch(Relay)
	{
		case _1_RELAY:
		DIO_WritePin(_1_RELAY_PIN, LOW);
		break;
		
		case _2_RELAY:
		DIO_WritePin(_2_RELAY_PIN, LOW);
		break;
		
		case RELAY_ALL:
		DIO_WritePin(_1_RELAY_PIN, LOW);
		DIO_WritePin(_2_RELAY_PIN, LOW);
	}
}


