# define F_CPU 8000000
#include <util/delay.h>

#define  BUTTON_PROG 0


#include "StdTypes.h"
#include "DIO_Interface.h"
#include "Butthon_interface.h"


void BUTTON_Init(void)
{
	/*Do Nothing*/
}

static bool_t Button_flagArray[BUTTON_NUM] = {TRUE, TRUE, TRUE, TRUE}; 

BUTTON_Press_State BUTTON_ReadDelay(BUTTON_type Button)
{
	BUTTON_Press_State Status = NOT_PRESSED;
	if (DIO_ReadPin(BUTTON_array[Button]) == BUTTON_PRESS_TYPE)
	{
		Status = PRESSED;
		_delay_ms(200);
	}
	return Status;
	
}

BUTTON_Press_State BUTTON_ReadBussy(BUTTON_type Button)
{
	BUTTON_Press_State Status = NOT_PRESSED;
	if (DIO_ReadPin(BUTTON_array[Button]) == BUTTON_PRESS_TYPE)
	{
		Status = PRESSED;
		while(DIO_ReadPin(Button) == BUTTON_PRESS_TYPE);
	}
	return Status;
	
}


BUTTON_Press_State BUTTON_Read(BUTTON_type Button)
{
	BUTTON_Press_State Status = NOT_PRESSED;
	
	if (DIO_ReadPin(BUTTON_array[Button]) == BUTTON_PRESS_TYPE)
	{
		if (Button_flagArray[Button]  == TRUE)
		{
			Status = PRESSED;
		}
		Button_flagArray[Button] = FALSE;
	}
	else
	{
		Button_flagArray[Button] = TRUE;
	}
	return Status;
	
}

BUTTON_Press_State BUTTON_ReadCont(BUTTON_type Button)
{
	BUTTON_Press_State Status = NOT_PRESSED;
	if (DIO_ReadPin(BUTTON_array[Button]) == BUTTON_PRESS_TYPE)
	{
		Status = PRESSED;
	}
	return Status;
	
}