

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_



typedef enum
{
	UART_RISINGXCK_EDGE, 
	UART_FALLINGGXCK_EDGE
	}UART_ClockPolarity_t;

typedef enum
{
	UART_5_BIT,
	UART_6_BIT,
	UART_7_BIT,
	UART_8_BIT,
	UART_9_BIT = 7, 
	}UART_CharacterSize_t;


typedef enum
{
	UART_STOP_1_BIT,
	UART_STOP_2_BIT,

	}UART_StopBitSelect_t;

typedef enum
{
	
	UART_DISABLE_PARITY,
	UART_EVEN_PARITY = 2,
	UART_ODD_PARITY,
	}UART_ParityModes_t;



typedef enum
{	
	UART_ASYNCHRONOUS,
	UART_SYNCHRONOUS,
	}UART_ModeSelect_t;


typedef enum
{
	UART_2400_BAUDRATE = 207,
	UART_4800_BAUDRATE = 103,
	UART_9600_BAUDRATE = 51,
	UART_14400_BAUDRATE = 34,
	UART_19200_BAUDRATE = 25,
	UART_28800_BAUDRATE = 16,
}UART_BaudRate_Select_t;

typedef struct
{
	UART_ModeSelect_t	mode;
	UART_ParityModes_t	parity;
	UART_StopBitSelect_t Stop;
	UART_CharacterSize_t charSize;
	UART_ClockPolarity_t clk;
	UART_BaudRate_Select_t BuadRate;
	}USART_Control_StatusRegister_C_t;

 
 
 
 
void UART_Init2(void);
void UART_Init(UART_BaudRate_Select_t BaudRate);

void UART_SendData(u8 data);
u8 UART_ReciveData(void);
u8 UART_ReciveDataPerodic(u8 *pdata);
void UART_SendNoBlock(u8 data);
u8 UART_ReciveNoBlock(void);
void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);
void UART_RX_SetCallBack(void (*LocalFptr)(void));
void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);
void UART_TX_SetCallBack(void (*LocalFptr)(void));


#endif /* UART_INTERFACE_H_ */