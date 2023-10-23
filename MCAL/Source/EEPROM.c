#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "EEPROM_intrface.h"

static void (*EEPROM_Fptr) (void)=NULLPTR;
/*static*/ volatile bool_t Intr_Flag = TRUE; 

void EEPROM_Init(void)
{
	/*Do Nothing*/
}






void EEPROM_writeBusy(u16 Address, u8 Data)
{
	/* Wait for completion of previous write */
	while(READ_BIT(EECR, EEWE));
	/* Set up address and data registers */
	EEAR = Address;
	EEDR = Data;
	/* Write logical one to EEMWE */
	SET_BIT(EECR, EEMWE);
	/* Start EEPROM write by setting EEWE */
	SET_BIT(EECR, EEWE);
	

}
 
u8 EEPROM_readBusy(u16 Address)
{
	/* Wait for completion of previous write */
	while(READ_BIT(EECR, EEWE));
	/* Set up address register */
	EEAR = Address;
	/* Start EEPROM read by writing EERE */
	SET_BIT(EECR, EERE);
	/* Return data from data register */
	return EEDR;
}














EEPROM_status EEPROM_write(u16 Address, u8 Data)
{
	EEPROM_status Status = EE_NWRITE;
	if (Intr_Flag)
	{
		/* Set up address and data registers */
		EEAR = Address;
		EEDR = Data;
		/* Write logical one to EEMWE */
		SET_BIT(EECR, EEMWE);
		/* Start EEPROM write by setting EEWE */
		SET_BIT(EECR, EEWE);
		
		Intr_Flag = FALSE;
		Status = EE_WRITE;
	}
	return Status;
}

EEPROM_status EEPROM_read(u16 Address, u8 *Pdata)
{
	EEPROM_status Status = EE_NREAD;
	if (Intr_Flag)
	{
		/* Set up address register */
		EEAR = Address;
		/* Start EEPROM read by writing EERE */
		SET_BIT(EECR, EERE);
		/* Return data from data register */
		*Pdata = EEDR;
		
		Intr_Flag = FALSE;
		Status = EE_READ;
	}
	return Status;
	
	
}

EEPROM_status EEPROM_Status(void)
{
	EEPROM_status Status = EE_NREADY;
	if (Intr_Flag == TRUE)
	{
		Status = EE_READY;
	}
	return Status;
}

/**************************** EEPROM Interrupt functions **************************************/

void EEPROM_InterruptEnable(void)
{
	SET_BIT(EECR, EERIE);
}
void EEPROM_InterruptDisable(void)
{
	CLR_BIT(EECR, EERIE);
}

/**************************** EEPROM Call Back functions **************************************/

void EEPROM_SetCallBack(void(*LocalFptr)(void))
{
	EEPROM_Fptr = LocalFptr;
}

/**************************** EEPROM ISR functions **************************************/


ISR(EE_RDY_vect)
{
	Intr_Flag = TRUE;

	if (EEPROM_Fptr != NULLPTR)
	{
		EEPROM_Fptr();
	}
}