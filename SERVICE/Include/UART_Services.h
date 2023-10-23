

#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

typedef enum
{
	LITTLE,
	BIG
	}Endian_type;

typedef enum
{
	UART_READY,
	UART_NOTREADY,
	UART_SEND,
	UART_RECEVIED,
	UART_NOTSEND,
	UART_NOTRECEVIED,
	}UART_Service_status_t;

void UART_SendString(c8* str);
void UART_ReceiveString(c8* str);

void UART_SendNumber(u32 num);
u32 UART_ReceiveNumber(void);

Endian_type endian_check(void);
u32 endian_convert(u32 num);

UART_Service_status_t UART_SendStringAshync(c8* str);

void UART_SendStringInit(void);
void UART_SendStringRunnable(void);
void UART_SendStringSetter(c8* str);

UART_Service_status_t UART_ReceiveStringGetterAshync(void);
UART_Service_status_t UART_ReceiveStringAshync(c8* str);
void UART_ReceiveStringAshync_Init(u16 Finish);


#endif /* UART_SERVICES_H_ */