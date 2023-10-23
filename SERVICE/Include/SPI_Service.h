

#ifndef SPI_SERVICE_H_
#define SPI_SERVICE_H_


#define SPI_FRAME_START_PATTERN		0x55
#define SPI_DUMMY					0XA5

typedef enum
{
	Q_EMPTY,
	Q_FULL,
	Q_DONE,
	}Q_status_t;
	
	
/********************** Receive and Send Frames using SPI Interrupt ******************************/
void SPI_SetterSendFrame(u8 *frame);
void SPI_sendFrameInit(void);
Q_status_t SPI_ReceiveFrameGetter(u8 *FrameReceive);

/*************************************************************************************************/
/* Send Data Synchronous used by master MCU 
 * 20 us for 4 frames */
void SPI_SendReceiveFrameSynch(u8 *Data_send, u8 *Data_Rec);


/********************** Receive  Data using External Interrupt **********************************/

void SPI_RecStr_Init(void);
Q_status_t SPI_ReceiveStringGetter(c8 *Str);

/********************** Receive and Send Data using SPI Interrupt *******************************/

void SPI_StringSendReveive_Init(void);
u8 SPI_SendStringSetter(c8 *strSend);


/********************************** Send String Synchronous *************************************/
void SPI_SendStringBusy(c8 *strSend);

/************************* Receive data Synchronous Only and send Dummy *************************/
void SPI_ReceiveStringBusy(c8 *strReceive);



/***************************** Receive and Send Fixed Frame size ********************************/
// Receive and Send Fixed frame size
void SPI_SendReceiveFrameBusy(u8 *FrameSend, u8 *FrameReceive);
void SPI_ReceiveFrameBusy(u8 *FrameReceive);
void SPI_SendFrameBusy(u8 *FrameSend);

/********************************** Send & receive **********************************************/

void SPI_FrameSend_Init(void);
void SPI_SendFrame_Setter(u8 *frame);
void SPI_ReceiveFrame_Getter(u8 *frame);





#endif /* SPI_SERVICE_H_ */