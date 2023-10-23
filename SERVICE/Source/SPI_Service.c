#include "StdTypes.h"
#include "Utils.h"
#include "EX_Interrupt.h"
#include "SPI_Service_Private.h"
#include "SPI_Service.h"
#include "SPI_Interface.h"
#include "SPI_Service_Cfg.h"
#include "MemMap.h"

# define F_CPU 8000000
#include <util/delay.h>

/***********************************************************************************************/
/********************** Receive and Send Frames using SPI Interrupt ****************************/
/***********************************************************************************************/

/****************************** Q Frame *******************************/
static volatile c8 QFrame_Rec[Q_FRAME_REC_SIZE][SPI_FRAME_SIZE];
static volatile u8 QFrame_Cnt;
static volatile u8 QFrame_In;
static volatile u8 QFrame_Out;
static volatile Q_status_t QFrame_status = Q_EMPTY;

/********************* Frame Send Receive Functions *******************/
static  u8 *SPI_SendFrame/*[SPI_FRAME_SIZE]*/;
static volatile bool_t SendFrame_Flag = FALSE;


#include "LCD_interface.h"

/* Send frame from Interrupt initialization 
 * Set call back of SPI 
 * Enable SPI interrupt 
 * can not use very high speed faster than interrupt response */
void SPI_sendFrameInit(void)
{
	SPI_SetCallBack(Frame_SPICallBack);
	SPI_InterruptEnable();
}



/* Set Frame wanted to send */
void SPI_SetterSendFrame(u8 *frame)
{
	if (!SendFrame_Flag)
	{
		/* Set local frame to static global frame buffer */
		SPI_SendFrame = frame;
		/* Put first Bytes in buffer
		 * For master this will start transfer data 
		 * For slave this will initialize buffer for master when start communication */ 
		SPI_SendNoBlock(SPI_FRAME_START_PATTERN);
		/* Flag indicate start and end last sending
		 * for event synchronization with SPI ISR */ 
		SendFrame_Flag = TRUE;
	}
	
	
}

/* Queue for received frame from SPI */
Q_status_t SPI_ReceiveFrameGetter(u8 *FrameReceive)
{
	/* If Data Count equal to Zero there is no element in queue */
	if (QFrame_Cnt == Q_EMPTY)
	{
		// Update Status to Empty
		QFrame_status = Q_EMPTY;
	}
	else
	{
		u16 FrameIndex;
		/* Copy Data from Queue to User Frame by value */
		for (FrameIndex = 0; FrameIndex < SPI_FRAME_SIZE; FrameIndex++)
		{
			FrameReceive[FrameIndex] = QFrame_Rec[QFrame_Out][FrameIndex];
		}
		/* Update where index for Queue to put next data to out */
		QFrame_Out = (QFrame_Out + 1) % Q_FRAME_REC_SIZE;
		/* Decrement counter of new number of element in Queue */
		QFrame_Cnt--;
	}
	/* Return status */
	return QFrame_status;
}


/* Send and receive data from SPI buffer ISR */	
static void Frame_SPICallBack(void)
{
	static u8 FrameIndex = 0;

	/********************** Receive Frame *******************/
	
	/* Receive data frame Index */
	static s16 Rec_FrameIndex = 0;
	/* Receive data from SPI Buffer */
	u8 DataRec = SPI_ReceiveNoBlock();
	/* If frame first byte equal to start SPI_FRAME_START_PATTERN then frame valid to receive */
	static bool_t IsFrame_flag = FALSE;
	
	/* If Data Count equal to size of queue there is no space empty in queue */
	if (QFrame_Cnt == Q_FRAME_REC_SIZE)
	{
		// Update Status to FULL
		QFrame_status = Q_FULL;
	}
	/* If frame valid */
	else if (IsFrame_flag)
	{
		/* While number of data received no equal size of frame (CFG) */
		if (Rec_FrameIndex != SPI_FRAME_SIZE )
		{
			/* Receive frame data in queue */
			QFrame_Rec[QFrame_In][Rec_FrameIndex] = DataRec;
			/* Increment frame Index */
			Rec_FrameIndex++;
		}
		/* If data receive equal to frame size so frame done */
		if (Rec_FrameIndex == SPI_FRAME_SIZE)
		{
			/* Reset Frame Index */
			Rec_FrameIndex = 0;
			/* Update where index for Queue to put next data to in */
			QFrame_In = (QFrame_In + 1) % Q_FRAME_REC_SIZE;
			/* Increment counter of new number of element in Queue */
			QFrame_Cnt++;
			/* Flag indicate end last byte Receive */ 
			IsFrame_flag = FALSE;
			
		}
	}
	
	/* check for receive start pattern 
	 * put under receive in queue to avoid put start pattern in queue */
	if (DataRec == SPI_FRAME_START_PATTERN)
	{
		/* Start pattern receive start put data in queue */
		IsFrame_flag = TRUE;
	}
	
	/********************** Send Frame *******************/
	
	/* If true start send frame set from setter */
	if (SendFrame_Flag)
	{
		/* delay to avoid problem of salve did not catch data 
		 * SLAVE did not can put data in buffer after master due to interrupt response */  
		_delay_us(5);
		/* Write data to SPI Buffer */
		SPI_SendNoBlock(SPI_SendFrame[FrameIndex]);
		/* Increment frame Index */
		FrameIndex++;
		/* If data receive equal to frame size so frame done */
		if (FrameIndex == SPI_FRAME_SIZE)
		{
			/* Indicate frame send */
			SendFrame_Flag = FALSE;
			/* Reset Frame Index */
			FrameIndex = 0;
			/* Remove previous data */
			SPI_SendFrame = NULLPTR;

		}
	}
}










/**********************************************************************************************************************/
/**********************************************************************************************************************/
/*************************** SPI Queue For data Received uing External interrupt **************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/

static c8 StrRec[Q_REC_SIZE][SPI_STR_REC_MAX_SIZE];
static u8 Qcnt;
static u8 Qin;
static u8 Qout;
static Q_status_t Qstatus = Q_EMPTY;

/***********************************************************************************/


/********************** Receive  Data using External Interrupt ****************************/

void SPI_RecStr_Init(void)
{
	EXI_Init();
	EXI_SetCallBack(EX_INT0, EXI_StrRec_callBack);
	EXI_Enable(EX_INT0);
	
}

static void EXI_StrRec_callBack(void)
{
	if (Qcnt == Q_REC_SIZE)
	{
		Qstatus = Q_FULL;
	}
	else
	{
		SPI_ReceiveStringBusy(StrRec[Qin]);
		
		Qin = (Qin + 1) % Q_REC_SIZE;
		Qcnt++;
	}
}

Q_status_t SPI_ReceiveStringGetter(c8 *Str)
{
	if (Qcnt == Q_EMPTY)
	{
		Qstatus = Q_EMPTY;
	}
	else
	{
		u16 StrIndex;
		// Copy Data from Queue to User string
		for (StrIndex = 0; StrRec[Qout][StrIndex]; StrIndex++)
		{
			Str[StrIndex] = StrRec[Qout][StrIndex];
		}
		Str[StrIndex] = 0;
		
		Qout = (Qout + 1) % Q_REC_SIZE;
		Qcnt--;
	}
	return Qstatus;
}








/**********************************************************************************************************************/
/**********************************************************************************************************************/
/************************************* Receive and Send Data using SPI Interrupt **************************************/
/**********************************************************************************************************************/

static c8 *SPI_SlaveSendStr;
static bool_t Send_Falg = TRUE; 



void SPI_StringSendReveive_Init(void)
{
	SPI_SetCallBack(Str_SPICallBack);
	SPI_InterruptEnable();
}

static void Str_SPICallBack(void)
{
	static s16 StrIndex = 0;
	
	/********************** Send String *******************/
	if ((SPI_SlaveSendStr[StrIndex] == 0) && (!Send_Falg))
	{
		SPI_SendNoBlock(SPI_1ST_STR_SEND_END);
		StrIndex = 0;
		Send_Falg = TRUE;
	}
	else if (!Send_Falg)
	{
		SPI_SendNoBlock(SPI_SlaveSendStr[StrIndex]);
		StrIndex++;
	}
	else if (Send_Falg)
	{
		SPI_SendNoBlock(SPI_DUMMY);
	}
	
	
	/********************** Receive String *******************/
	
	static s16 StrIndex2 = 0;
	u8 DataRec = SPI_ReceiveNoBlock();;
	if (Qcnt == Q_REC_SIZE)
	{
		Qstatus = Q_FULL;
	}
	else if (DataRec != SPI_DUMMY)
	{
		
		if (StrRec[Qin][StrIndex2] != SPI_1ST_STR_REC_END)
		{
			StrRec[Qin][StrIndex2] = DataRec;
			
			
			if (StrIndex2 == SPI_STR_REC_MAX_SIZE - 1)
			{
				StrIndex2++;
			}
			
		}
		else
		{
			StrIndex2 = 0;
			StrRec[Qin][StrIndex2] = 0;
			Qin = (Qin + 1) % Q_REC_SIZE;
			Qcnt++;
		}


	}
	
}

u8 SPI_SendStringSetter(c8 *strSend)
{
	
	if (Send_Falg)
	{
		SPI_SlaveSendStr = strSend;
		Send_Falg = FALSE;
		return 1;
	}
	return 0;
	
}



/**********************************************************************************************************************/
/******************************************** Send String Synchronous *************************************************/
/**********************************************************************************************************************/


// Master Function
void SPI_SendStringBusy(c8 *strSend)
{
	u16 StrIndex;
	for (StrIndex = 0; strSend[StrIndex]; StrIndex++)
	{
		SPI_SendReceive(strSend[StrIndex]);
	}
	
	#if SPI_1ST_STR_END != 0
	SPI_SendReceive(SPI_1ST_STR_SEND_END);
	#endif
	
	#if SPI_2ST_STR_END != 0
	SPI_SendReceive(SPI_2ST_STR_SEND_END);
	#endif
}


/***************************************************************************************************************/
/********************************** Receive data Synchronous Only and send Dummy *******************************/
/***************************************************************************************************************/
void SPI_ReceiveStringBusy(c8 *strReceive)
{
	u16 StrIndex = 0;
	u8 dataRec;
	
	dataRec = SPI_SendReceive(SPI_DUMMY);
	// Check if data receive is dummy or not
	if (dataRec == SPI_DUMMY)
	{
		strReceive[StrIndex] = 0;
	}
	else
	{
		strReceive[StrIndex] = dataRec;
	}
	
	while(strReceive[StrIndex] != SPI_1ST_STR_REC_END)
	{
		StrIndex++;
		
		dataRec = SPI_SendReceive(SPI_DUMMY);
		// Check if data receive is dummy or not
		if (dataRec == SPI_DUMMY)
		{
			strReceive[StrIndex] = 0;
		}
		else
		{
			strReceive[StrIndex] = dataRec;
		}
		
		// If Data is larger than Receive data array break.
		if (StrIndex == SPI_STR_REC_MAX_SIZE - 2)
		{
			break;
		}
	}
	// Null at end of String
	StrIndex++;
	strReceive[StrIndex] = 0;
	
	
	#if SPI_2ST_STR_REC_END != 0
	SPI_SendReceive(SPI_DUMMY);
	#endif
}



/************************************************************************************************************************/
/******************************************* Receive and Send Fixed Frame Synchronous ***********************************/
/************************************************************************************************************************/

void SPI_SendReceiveFrameBusy(u8 *FrameSend, u8 *FrameReceive)
{
	u16 FrameIndex;
	u8 dataRec;
	for (FrameIndex = 0; FrameIndex < SPI_FRAME_SIZE; FrameIndex++)
	{
		dataRec = SPI_SendReceive(FrameSend[FrameIndex]);
		
		if (dataRec != SPI_DUMMY)
		{
			FrameReceive[FrameIndex] = dataRec;
		}
		else
		{
			FrameReceive[FrameIndex] = 0;
		}
	}
}


void SPI_ReceiveFrameBusy(u8 *FrameReceive)
{
	u16 FrameIndex;
	u8 dataRec;
	bool_t Correct_Frame_flag = FALSE;
	
	dataRec = SPI_SendReceive(SPI_DUMMY);
	_delay_ms(1);
	if (dataRec == SPI_FRAME_START_PATTERN)
	{
		Correct_Frame_flag = TRUE;
	}
	for (FrameIndex = 0; FrameIndex < SPI_FRAME_SIZE; FrameIndex++)
	{
		dataRec = SPI_SendReceive(0x33);
		
		if (Correct_Frame_flag)
		{
			FrameReceive[FrameIndex] = dataRec;
			
		}
		_delay_ms(1);

	}
}



void SPI_SendFrameBusy(u8 *FrameSend)
{
	u16 FrameIndex;
	for (FrameIndex = 0; FrameIndex < SPI_FRAME_SIZE; FrameIndex++)
	{
		SPI_SendReceive(FrameSend[FrameIndex]);
	}
}



/*******************************************************************************************************/
/******************** Send and Receive Frame inside interrupt Synchronous ******************************/
/*******************************************************************************************************/

/* Send Data Synchronous used by master MCU *
 * 20 us for 4 frames */
void SPI_SendReceiveFrameSynch(u8 *Data_send, u8 *Data_Rec)
{
	for (u16 i = 0; i < 4; i++)
	{
		Data_Rec[i] = SPI_SendReceive(Data_send[i]);
		/* Delay in first byte to make time for slave to enter interrupt */
		if (i == 0) {_delay_us(6);}
	}
}






/*********************************************************  Send & receive **************************************************/


#define SPI_DATA_FRAME_SIZE			4

u8 Send_frame[SPI_DATA_FRAME_SIZE];
u8 Rec_frame[SPI_DATA_FRAME_SIZE];
static bool_t New_frame_flag = FALSE;
static bool_t Send_flag = TRUE;

static void SPI_SlaveCallBack(void)
{
	u8 i;
	u8 j;
	/* Receive Frame and Send Frame Synchronous in SPI ISR */
	for (i = 1, j = 0; i < SPI_DATA_FRAME_SIZE; i++, j++)
	{
		while (!READ_BIT(SPSR, SPIF));
		Rec_frame[j] = SPDR;
		
		/* If there is new Frame to Send */
		if (!Send_flag)
		{
			SPDR = Send_frame[i];
		}
	}
	/* Receive Last byte from SPI buffer */
	while (!READ_BIT(SPSR, SPIF));
	Rec_frame[j] = SPDR;
	
	/* Reset Flag to be ready for new data to receive */
	New_frame_flag = TRUE;
	Send_flag = TRUE;
}


void SPI_FrameSend_Init(void)
{
	SPI_SetCallBack(SPI_SlaveCallBack);
	SPI_SlaveInit();
	SPI_InterruptEnable();
}


void SPI_SendFrame_Setter(u8 *frame)
{
	/* Check First if previous Frame Send */
	if (Send_flag)
	{
		/* Put First Byte on SPI Buffer to be ready for sending */
		SPI_SendNoBlock(frame[0]);
		/* Copy Frame to send By SPI by Value to buffer */
		for (int i = 0; i < SPI_DATA_FRAME_SIZE; i++)
		{
			Send_frame[i] = frame[i];
		}
		Send_flag = FALSE;
	}
	
}

void SPI_ReceiveFrame_Getter(u8 *frame)
{
	/* Check First if there is new Frame Received */
	if (New_frame_flag)
	{
		/* Copy Frame Receives By SPI by Value to User Frame */
		for (int i = 0; i < SPI_DATA_FRAME_SIZE; i++)
		{
			frame[i] = Rec_frame[i];
		}
		New_frame_flag = FALSE;
	}
}



