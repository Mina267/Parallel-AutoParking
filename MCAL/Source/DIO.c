#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_interface.h"
#include "DIO_private.h"


static  Error_type DIO_InitPin(DIO_Pin_type pin, DIO_PinStatus_type status)
{
	DIO_Port_type port =  pin / MAX_PINS_INPORT;
	u8 pin_num =  pin % MAX_PINS_INPORT;
	
	Error_type errorStatus = OK;
	
	if (port >= MAX_NUMOF_PORT || pin >= TOTAL_PINS)
	{
		errorStatus = OUT_OF_RANGE;
	}
	
	switch (status)
	{
		case OUTPUT:
		switch (port)
		{
			case PA:
			SET_BIT(DDRA, pin_num);
			CLR_BIT(PORTA, pin_num);
			break;
			case PB:
			SET_BIT(DDRB, pin_num);
			CLR_BIT(PORTB, pin_num);
			break;
			case PC:
			SET_BIT(DDRC, pin_num);
			CLR_BIT(PORTC, pin_num);
			break;
			case PD:
			SET_BIT(DDRD, pin_num);
			CLR_BIT(PORTD, pin_num);
			break;
		}
		break;
		
		case INFREE:
		switch (port)
		{
			case PA:
			CLR_BIT(DDRA, pin_num);
			CLR_BIT(PORTA, pin_num);
			break;
			case PB:
			CLR_BIT(DDRB, pin_num);
			CLR_BIT(PORTB, pin_num);
			break;
			case PC:
			CLR_BIT(DDRC, pin_num);
			CLR_BIT(PORTC, pin_num);
			break;
			case PD:
			CLR_BIT(DDRD, pin_num);
			CLR_BIT(PORTD, pin_num);
			break;
		}
		break;
		
		case INPULL:
		switch (port)
		{
			case PA:
			CLR_BIT(DDRA, pin_num);
			SET_BIT(PORTA, pin_num);
			break;
			case PB:
			CLR_BIT(DDRB, pin_num);
			SET_BIT(PORTB, pin_num);
			break;
			case PC:
			CLR_BIT(DDRC, pin_num);
			SET_BIT(PORTC, pin_num);
			break;
			case PD:
			CLR_BIT(DDRD, pin_num);
			SET_BIT(PORTD, pin_num);
			break;
		}
		break;
	}
	return errorStatus;
}

// Write in output Pin (DDR = 1) 5v or 0  
Error_type DIO_WritePin(DIO_Pin_type Pin, DIO_PinVoltage_type  volt)
{
	DIO_Port_type port =  Pin / MAX_PINS_INPORT;
	u8 pin_num =  Pin % MAX_PINS_INPORT;
	Error_type errorStatus = OK;
	
	if (port >= MAX_NUMOF_PORT || Pin > TOTAL_PINS)
	{
		errorStatus = OUT_OF_RANGE;
	}
	
	switch (volt)
	{
		case HIGH:
		switch (port)
		{
			case PA:
			SET_BIT(PORTA, pin_num);
			break;
			case PB:
			SET_BIT(PORTB, pin_num);
			break;
			case PC:
			SET_BIT(PORTC, pin_num);
			break;
			case PD:
			SET_BIT(PORTD, pin_num);
			break;
		}
		break;
		
		case LOW:
		switch (port)
		{
			case PA:
			CLR_BIT(PORTA, pin_num);
			break;
			case PB:
			CLR_BIT(PORTB, pin_num);
			break;
			case PC:
			CLR_BIT(PORTC, pin_num);
			break;
			case PD:
			CLR_BIT(PORTD, pin_num);
			break;
		}
		break;
	}
	
	return errorStatus;
}

// Toggle output Pin (DDR = 1) from 5v to 0 or vis versa  
extern Error_type DIO_TogglePin(DIO_Pin_type Pin)
{
	DIO_Port_type port =  Pin / MAX_PINS_INPORT;
	u8 pin_num =  Pin % MAX_PINS_INPORT;
	Error_type errorStatus = OK;
	
	if (port >= MAX_NUMOF_PORT || Pin > TOTAL_PINS)
	{
		errorStatus = OUT_OF_RANGE;
	}
	

	switch (port)
	{
		case PA:
		TOG_BIT(PORTA, pin_num);
		break;
		case PB:
		TOG_BIT(PORTB, pin_num);
		break;
		case PC:
		TOG_BIT(PORTC, pin_num);
		break;
		case PD:
		TOG_BIT(PORTD, pin_num);
		break;
	}
	return errorStatus;
}




DIO_PinVoltage_type DIO_ReadPin(DIO_Pin_type Pin)
{
	DIO_Port_type port =  Pin / MAX_PINS_INPORT;
	u8 pin_num =  Pin % MAX_PINS_INPORT;
	DIO_PinVoltage_type voltage = LOW;
	
	switch (port)
	{
		case PA:
		voltage = READ_BIT(PINA, pin_num);
		break;
		case PB:
		voltage = READ_BIT(PINB, pin_num);
		break;
		case PC:
		voltage = READ_BIT(PINC, pin_num);
		break;
		case PD:
		voltage = READ_BIT(PIND, pin_num);
		break;
	}
	
	return voltage;
}


	
// Initialized all pin
extern void DIO_Init(void)
{
	for (DIO_Pin_type PinIndex = PINA0; PinIndex < TOTAL_PINS; PinIndex++)
	{
		DIO_InitPin(PinIndex, PinsStatusArray[PinIndex]);
	}
}


// Write in all port in one time
extern void DIO_WritePort(DIO_Port_type port,u8 value)
{
	switch (port)
	{
		case PA:
		PORTA = value;
		break;
		
		case PB:
		PORTB = value;
		break;
		
		case PC:
		PORTC = value;
		break;
		
		case PD:
		PORTD = value;
		break;
	}
}

// Read all port in one time
extern u8 DIO_ReadPort(DIO_Port_type port)
{
	u8 value = PORTA;
	switch (port)
	{
		case PA:
		value = PORTA;
		break;
		
		case PB:
		value = PORTB;
		break;
		
		case PC:
		value = PORTC;
		break;
		
		case PD:
		value = PORTD;
		break;
	}
	
	return value;
}




// Write in all port in one time
extern void DIO_WriteHalfPort(DIO_HalfPort_type port,u8 value)
{
	value = value & 0x0f;
	switch (port)
	{
		
		case PA_0TO3:
		PORTA = (value) | (PORTA & 0xf0);
		break;
		
		case PA_4TO7:
		PORTA = (value << 4) | (PORTA & 0x0f);
		break;
		
		case PB_0TO3:
		PORTB = (value) | (PORTB & 0xf0);;
		break;
		
		case PB_4TO7:
		PORTB = (value << 4) | (PORTB & 0x0f);
		break;
		
		case PC_0TO3:
		PORTC = (value) | (PORTC & 0xf0);;
		break;
		
		case PC_4TO7:
		PORTC = (value << 4) | (PORTC & 0x0f);
		break;
		
		case PD_0TO3:
		PORTD = (value) | (PORTD & 0xf0);;
		break;
		
		case PD_4TO7:
		PORTD = (value << 4) | (PORTD & 0x0f);
		break;
	}
}