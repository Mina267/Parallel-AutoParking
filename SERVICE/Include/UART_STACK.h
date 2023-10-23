
#ifndef UART_STACK_H_
#define UART_STACK_H_



#define STACK_SIZE	10

typedef enum
{
	STACK_EMPTY = 0,
	STACK_FULL,
	STACK_PUSHED,
	STACK_POP,
}Stack_Status_t;


Stack_Status_t Stack_Push (u8 data);
Stack_Status_t Stack_Pop (u8 *Pdata);


#endif /* UART_STACK_H_ */