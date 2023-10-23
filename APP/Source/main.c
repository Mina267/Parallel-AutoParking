#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "AutoParking.h"





int main(void)
{
	
	DIO_Init();
	LCD_Init();

	sei();
	

	AutoParking_Init();
	while (1)
	{
		AutoParking_Runnable();
		
	}
	return 0;
}
























