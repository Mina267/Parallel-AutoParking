
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define READ_VOLT(read)		((u16)(((u32)5000 * (u32)(read)) / (u32)1024))

#define AREF ((u16)3000)

typedef enum
{
	VREF_AREF,
	VREF_AVCC,
	VREF_256
	}ADC_Vref_type;


typedef enum
{
	CH_0=0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
	}ADC_Channel_type;

typedef enum
{
	ADC_SCALER_2=1,
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128,
	}ADC_Prescaler_type;
	
	
	
typedef enum
{
	ADC_NOREAD,
	ADC_READ,
	}ADC_Status_type;




void ADC_Init(ADC_Vref_type Vref, ADC_Prescaler_type scaler);
u16 ADC_Read(ADC_Channel_type ch);
u16 ADC_ReadVolt(ADC_Channel_type ch);
void ADC_StartConversion(ADC_Channel_type ch);
u16 ADC_GetRead(void);
ADC_Status_type ADC_GetReadPeroidic(u16 *Pdata);
void ADC_Enable(void);
void ADC_Disable(void);

/**************************** ADC Interrupt function **************************************/
void ADC_ClearedFlag(void);
void ADC_InterruptEnable(void);
void ADC_InterruptDisable(void);
/********************************* ADC Call Back function *****************************************/
void ADC_SetCallBack(void(*LocalPtr)(void));


#endif /* ADC_INTERFACE_H_ */