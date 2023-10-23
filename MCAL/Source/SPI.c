#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "SPI_Interface.h"

static void (*SPI_Fptr) (void) = NULLPTR;


void SPI_Init(SPI_Mode_type Mode, SPI_clk_t clk, SPI_DoubleSpeed_t speed)
{
	// Master mode
	switch (Mode)
	{
		case MASTER:
		SET_BIT(SPCR, MSTR);
		break;
		
		case SLAVE:
		CLR_BIT(SPCR, MSTR);
		break;
	}
	// Speed mode
	WRITE_BIT(SPSR, SPI2X, speed);
	// CLK
	SPCR = (SPCR & 0xfc) | clk;
	// SPI Enable
	SET_BIT(SPCR, SPE);
}

void SPI_SlaveInit(void)
{
	CLR_BIT(SPCR, MSTR);
	// SPI Enable
	SET_BIT(SPCR, SPE);
}

u8 SPI_SendReceive(u8 data)
{
	SPDR = data;
	while (!READ_BIT(SPSR, SPIF));
	return SPDR;
}


u8 SPI_ReceivePerodic(u8 *Pdata)
{
	if (READ_BIT(SPSR, SPIF))
	{
		*Pdata = SPDR;
		return 1;
	}
	return 0;
}

void SPI_SendNoBlock(u8 data)
{
	SPDR = data;
}

u8 SPI_ReceiveNoBlock(void)
{
	return SPDR;
}


void SPI_InterruptEnable(void)
{
	SET_BIT(SPCR, SPIE);
}

void SPI_InterruptDisable(void)
{
	CLR_BIT(SPCR, SPIE);
}



/**************************** SPI Call Back functions **************************************/

void SPI_SetCallBack(void(*LocalFptr)(void))
{
	SPI_Fptr = LocalFptr;
}

/**************************** SPI ISR functions **************************************/


ISR(SPI_STC_vect)
{
	if (SPI_Fptr != NULLPTR)
	{
		SPI_Fptr();
	}
}