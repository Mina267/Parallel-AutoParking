
#include "StdTypes.h"
#include "UART_Interface.h"
#include "UART_Services.h"



/* synch function */
void UART_SendString(c8* str)
{
	for (u16 StrIndex = 0; str[StrIndex]; StrIndex++)
	{
		UART_SendData(str[StrIndex]);
	}
	UART_SendData(13);
}


void UART_ReceiveString(c8 *str)
{
	u16 StrIndex = 0;
	
	do
	{
		str[StrIndex] = UART_ReciveData();
		StrIndex++;
		
	} while (str[StrIndex - 1] != 13);
	str[StrIndex] = 0;
	
}



void UART_SendNumber(u32 num)
{
	UART_SendData((u8)num);
	UART_SendData((u8)(num >> 8));
	UART_SendData((u8)(num >> 16));
	UART_SendData((u8)(num >> 24));
	/*
	u8 *p = (u8 *)&num;
	UART_SendNumber(p[0]);
	UART_SendNumber(p[1]);
	UART_SendNumber(p[2]);
	UART_SendNumber(p[3]);
	*/
}

u32 UART_ReceiveNumber(void)
{
	u32 num;
	u8 b1 = UART_ReciveData();
	u8 b2 = UART_ReciveData();
	u8 b3 = UART_ReciveData();
	u8 b4 = UART_ReciveData();
	
	num =	((u32)b1)		|
			((u32)b2) << 8	|
			((u32)b3) << 16	|
			((u32)b4) << 24	;
	
	/*
	u8 *p = (u8 *)&num;
	p[0] = UART_ReciveData();
	p[1] = UART_ReciveData();
	p[2] = UART_ReciveData();
	p[3] = UART_ReciveData();
	*/
	
	return num;
}






Endian_type endian_check(void)
{
	u32 num = 1;
	if (*((u8 *) (&num)) == 1)
	{
		return LITTLE;
	}
	else
	{
		return BIG;
	}
}

u32 endian_convert(u32 num)
{
	return
	((num >> 24) & 0x000000ff)	|
	((num << 24) & 0xff000000)	|
	((num >> 8)  & 0x0000ff00)	|
	((num << 8)  & 0x00ff0000)	;
	
	/*
	u8 *p = (u8 *)num;
	u8 tmp;
	tmp = p[0];
	p[0] = p[3];
	p[3] = tmp;
	
	tmp = p[1];
	p[1] = p[2];
	p[2] = tmp;
	return num;
	*/
}
u16 endian_convert_16(u16 num)
{
	return
	(num >> 8  & 0x00ff)	|
	(num << 8  & 0xff00)	;
}





void UART_SendStringCheckSum(u8*str)
{
	u8 len;
	u16 sum = 0;
	for (len = 0; str[len]; len++);
	UART_SendData(len);
	
	for (u16 StrIndex = 0; str[StrIndex]; StrIndex++)
	{
		UART_SendData(str[StrIndex]);
		sum += str[StrIndex];
	}
	
	UART_SendData((u8)sum);
	UART_SendData((u8)(sum >> 8));
}


u8 UART_ReceiveStringCheckSum(u8*str)
{
	u16 len = UART_ReciveData();
	u8 StrIndex;
	u16 sum = 0;
	u16 sumRec = 0;
	
	for (StrIndex = 0; StrIndex < len; StrIndex++)
	{
		str[StrIndex] = UART_ReciveData();
		sum += str[StrIndex];
	}
	str[StrIndex] = 0;
	
	
	u8 b1 = UART_ReciveData();
	u8 b2 = UART_ReciveData();
	sumRec =	((u16)b1)		|
				((u16)b2) << 8	;
				
	if (sumRec == sum)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
	

	
	
	
}

/* Asyn Func */




/******************************* Send Data Excution in ISR ******************************/


static c8 *Tx_Str;
static volatile bool_t Tx_flag = TRUE;

// ISR Function Run in Background
void func_tx(void)
{
	static u8 i = 1;
	if (Tx_Str[i] != 0)
	{
		UART_SendNoBlock(Tx_Str[i]);
		i++;
	}
	else
	{
		Tx_flag = TRUE;
		i = 1;
	}
	
}

UART_Service_status_t UART_SendStringAshync(c8* str)
{
	UART_Service_status_t status = UART_NOTSEND;
	if (Tx_flag)
	{
		/* Set Callback Function for UART Send */
		UART_TX_SetCallBack(func_tx);
		UART_TX_InterruptEnable();
		/* Send first Byte only and reset in ISR */
		UART_SendNoBlock(str[0]);
		Tx_Str = str;
		Tx_flag = FALSE;
		status = UART_SEND;
	}
	return status;
	
}



/******************************* Send Data Excution in Code ******************************/


static c8 *Tx2_Str;
static volatile bool_t Tx2_flag = TRUE;


static void func_tx2(void)
{
	Tx2_flag = TRUE;
	
}

void UART_SendStringInit(void)
{
	UART_TX_SetCallBack(func_tx2);
	UART_TX_InterruptEnable();
}

void UART_SendStringRunnable(void)
{
	static u8 i = 0;
	if (Tx2_flag)
	{
		if (Tx2_Str[i] != 0)
		{
			
			UART_SendNoBlock(Tx2_Str[i]);
			i++;
		}
		else
		{
			i = 0;
		}
		
		Tx2_flag = FALSE;
		
	}
		
}

void UART_SendStringSetter(c8* str)
{
	Tx2_Str = str;
}




/**************** Receive string Detect end of string by pattern ******************/

static c8 *Rx_str;
static u8 StrFinish1;
static u8 StrFinish2;
static volatile bool_t StrFinish_flag = TRUE;
static volatile bool_t StrFinish2_flag = FALSE;


static void Rx_Func(void)
{
	static u8 i = 0;
	
	Rx_str[i] = UART_ReciveNoBlock();
	if ((Rx_str[i] == StrFinish1) || (StrFinish2_flag == TRUE))
	{
		
		if (Rx_str[i] == StrFinish1)
		{
			Rx_str[i] = 0;
		}
		
		
		if ((StrFinish2 == 0) || (Rx_str[i] == StrFinish2))
		{
			StrFinish_flag = TRUE;
			
			i = -1;
		}
		else
		{
			StrFinish2_flag = TRUE;
		}
	}
	i++;
	
}

// Take str finish
void UART_ReceiveStringAshync_Init(u16 Finish)
{
	UART_RX_SetCallBack(Rx_Func);
	UART_RX_InterruptEnable();
	StrFinish1 = Finish & 0xff;
	StrFinish2 = Finish >> 8;
}


UART_Service_status_t UART_ReceiveStringAshync(c8* str)
{
	UART_Service_status_t status =  UART_NOTREADY;
	if (StrFinish_flag)
	{
		Rx_str = str;
		StrFinish_flag = FALSE;
		StrFinish2_flag = FALSE;
		status =  UART_READY;
	}
	return status;
}


UART_Service_status_t UART_ReceiveStringGetterAshync(void)
{
	UART_Service_status_t status =  UART_NOTREADY;
	if (StrFinish_flag)
	{
		status =  UART_READY;
	}
	return status;
}



