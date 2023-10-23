#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "UART_Interface.h"
#include "UART_Private.h"




static void (*UART_RX_Fptr)(void) = NULLPTR;
static void (*UART_TX_Fptr)(void) = NULLPTR;




void UART_Init2(void)
{
	USART_UCSRC_t reg;
	/* Frame */
	reg.UCPOL_bit = Status.clk;
	
	switch(Status.charSize)
	{
		case UART_9_BIT:
		reg.UCSZ_bit = 3;
		SET_BIT(UCSRB, UCSZ2);
		break;
		default:
		reg.UCSZ_bit = Status.charSize;
		break;
	}
	
	reg.USBS_bit = Status.Stop;
	reg.UPM_bit = Status.parity;
	reg.UMSEL_bit = Status.mode;
	reg.URSEL_bit = 1;
	
	UCSRC = reg.UCSRC_reg & 0xff;
	
	/* Baud Rate */
	UBRRL = Status.BuadRate;
	/* Normal speed */
	CLR_BIT(UCSRA, U2X);
	/* Frame */
	/* Enable */
	SET_BIT(UCSRB, TXEN);
	SET_BIT(UCSRB, RXEN);

}


void UART_Init(UART_BaudRate_Select_t BaudRate)
{
	/* Baud Rate */
	UBRRL = BaudRate;
	
	/* Normal speed */
	CLR_BIT(UCSRA, U2X);
	/* Frame */
	/* Enable */
	SET_BIT(UCSRB, TXEN);
	SET_BIT(UCSRB, RXEN);
}

void UART_SendData(u8 data)
{
	while(!READ_BIT(UCSRA, UDRE));
	UDR = data;
}

u8 UART_ReciveData(void)
{
	while(!READ_BIT(UCSRA, RXC));
	return UDR;
}
u8 UART_ReciveDataPerodic(u8 *pdata)
{
	if (READ_BIT(UCSRA, RXC))
	{
		*pdata = UDR;
		return 1;
	}
	return 0;
}

void UART_SendNoBlock(u8 data)
{
	UDR = data;
}

u8 UART_ReciveNoBlock(void)
{
	return UDR;
}

void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB, RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLR_BIT(UCSRB, RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB, TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLR_BIT(UCSRB, TXCIE);
}




void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}

ISR(UART_RX_vect)
{
	if (UART_RX_Fptr != NULLPTR)
	{
		UART_RX_Fptr();
	}
}

ISR(UART_TX_vect)
{
	if (UART_TX_Fptr != NULLPTR)
	{
		UART_TX_Fptr();
	}
}