#include "StdTypes.h"
#include "I2C.h"
#include "EX_EEPROM.h"

# define F_CPU 8000000
#include <util/delay.h>

tenuErrrorStatus EEPROM_enuWriteByte(u8 u8ChipNbCpy , u8 u8ByteAddCpy , u8 u8DataCpy)
{
	 
	I2C_voidStart();
	if(I2C_u8GetStatus() != I2C_START )
	{
		return ENOK ;
	}
	/* user send to me u8ChipAddCpy  contain A2A1A0*/
	I2C_voidWrite(0b10100000|(u8ChipNbCpy <<1));
	if(I2C_u8GetStatus() != I2C_MT_SLA_W_ACK )
	{
		return ENOK ;
	}
	I2C_voidWrite(u8ByteAddCpy);
	if(I2C_u8GetStatus() != I2C_MT_DATA_ACK )
	{
		return ENOK ;
	}
	I2C_voidWrite(u8DataCpy);	
	if(I2C_u8GetStatus() != I2C_MT_DATA_ACK )
	{
		return ENOK ;
	}
	I2C_voidStop();
	_delay_ms(10);
	return EOK ;
}

tenuErrrorStatus EEPROM_enuReadByte(u8 u8ChipNbCpy , u8 u8ByteAddCpy , u8 * pu8DataCpy)
{
	I2C_voidStart();
	if(I2C_u8GetStatus() != I2C_START )
	{
		return ENOK ;
	}
	I2C_voidWrite(0b10100000|(u8ChipNbCpy <<1));
	if(I2C_u8GetStatus() != I2C_MT_SLA_W_ACK )
	{
		return ENOK ;
	}
	I2C_voidWrite(u8ByteAddCpy);
	if(I2C_u8GetStatus() != I2C_MT_DATA_ACK )
	{
		return ENOK ;
	}
	/*Repeat start condition*/
	I2C_voidStart();
	if(I2C_u8GetStatus() != I2C_REPEAT_START )
	{
		return ENOK ;
	}
	/* Chip select with read*/
	I2C_voidWrite(0b10100001|(u8ChipNbCpy <<1));
	if(I2C_u8GetStatus() != I2C_MT_SLA_R_ACK )
	{
		return ENOK ;
	}
	*pu8DataCpy = I2C_u8ReadWithoutAck();
	if(I2C_u8GetStatus() != I2C_MR_DATA_NACK )
	{
		return ENOK ;
	}
	I2C_voidStop();
	_delay_ms(10);
	return EOK ; 
}
