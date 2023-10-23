# define F_CPU 8000000
#include <util/delay.h>


#include "StdTypes.h"
#include "DIO_interface.h"
#include "Buzz_interface.h"

void BuzzSound(void)
{
	DIO_WritePin(BUZPIN, HIGH);
	_delay_ms(100);
	DIO_WritePin(BUZPIN, LOW);
}

void BuzzOn(void)
{
	DIO_WritePin(BUZPIN, HIGH);
}

void BuzzOff(void)
{
	DIO_WritePin(BUZPIN, LOW);
}