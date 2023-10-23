#include "StdTypes.h"
#include "UART_Interface.h"
#include "UART_Services.h"
#include "UART_STACK.h"





static u8 Stack[STACK_SIZE];
static u8 Sp;

Stack_Status_t Stack_Push (u8 data)
{
	Stack_Status_t status = STACK_PUSHED;
	if (Sp == STACK_SIZE)
	{
		status = STACK_FULL;
	}
	else
	{
		Stack[Sp] = data;
		Sp++;
	}
	return status;
}

Stack_Status_t Stack_Pop (u8 *Pdata)
{
	Stack_Status_t status = STACK_POP;
	if (Sp == STACK_EMPTY)
	{
		status = STACK_EMPTY;
	}
	else
	{
		Sp--;
		*Pdata = Stack[Sp];
	}
	return status;
}

