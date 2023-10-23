#include "StdTypes.h"
#include "UART_Interface.h"


USART_Control_StatusRegister_C_t Status = {	  UART_ASYNCHRONOUS
											, UART_DISABLE_PARITY
											, UART_STOP_1_BIT
											, UART_8_BIT
											, UART_RISINGXCK_EDGE
											, UART_9600_BAUDRATE };