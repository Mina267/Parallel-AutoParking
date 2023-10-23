# define F_CPU 8000000
#include <util/delay.h>

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "ADC_interface.h"

// ADC operate at Freq. from (50-200) KHz
// Adjust prescaler to 64  to give fADC = 8 MHz / 64 = 125 KHz
// ADC has 1024 step.
// Vin = (Vref * ADC) / 1024
// Vref control from ADMUX register bit 7 and 6.
// ADC has Mux. controlled by first 5 bits in ADMUX register
// To select which PIN in PORTA you want to read
// and select if you want single ended or +ve differential or -ve differential and differential Amp.
// At differential mode Vin = (Vref * ADC) / 512

// bit 7 in ADCSRA is Enable to turn on and of ADC
// if you enable ADC after adjust wanted setting ADC work in default 
//  bit 7 Conversion mode

static u16 volt_ref;
volatile bool_t ADCflag = TRUE;
static void (*ADC_Fptr) (void) = NULLPTR; 

void ADC_Init(ADC_Vref_type Vref, ADC_Prescaler_type scaler)
{
	/* Clock */
	scaler = scaler & 0x07; //00000111
	ADCSRA = ADCSRA & 0xf8;	//11111000
	ADCSRA = ADCSRA | scaler;
	/* Volt Ref */
	switch (Vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX, REFS0);
		CLR_BIT(ADMUX, REFS1);
		volt_ref = AREF;
		break; 
		case VREF_AVCC:
		SET_BIT(ADMUX, REFS0);
		CLR_BIT(ADMUX, REFS1);
		volt_ref = 5000;
		break;
		case VREF_256:
		SET_BIT(ADMUX, REFS0);
		SET_BIT(ADMUX, REFS1);
		volt_ref = 2560;
		break;
	}
	
	/* Order of ADCH and ADCL */
	CLR_BIT(ADMUX, ADLAR);
	
	/*  ADC enable */
	SET_BIT(ADCSRA, ADEN);
}




u16 ADC_Read(ADC_Channel_type ch) 
{
	ADC_InterruptDisable();
	/* Select channel */
	ch = ch & 0x1f;
	ADMUX = ADMUX & 0xe0;
	ADMUX = ch | ADMUX; 
	/* Start conversion */
	SET_BIT(ADCSRA, ADSC);
	/* W8 until finish */
	while(READ_BIT(ADCSRA, ADSC));
	/* return Read */ 
	//u16 adc = ADC;
	ADC_InterruptEnable();
	return ADC;
}


void ADC_StartConversion(ADC_Channel_type ch)
{
	if (ADCflag == TRUE)
	{
		/* Select channel */
		ch = ch & 0x1f;
		ADMUX = ADMUX & 0xe0;
		ADMUX = ch | ADMUX;
		/* Start conversion */
		SET_BIT(ADCSRA, ADSC);
		ADCflag = FALSE;
	}
	
}

u16 ADC_GetRead(void)
{
	/* W8 until finish */
	while(READ_BIT(ADCSRA, ADSC));
	ADCflag = TRUE;
	/* return Read */
	return ADC;
}

ADC_Status_type ADC_GetReadPeroidic(u16 *Pdata)
{
	ADC_Status_type status = ADC_NOREAD;
	if (!READ_BIT(ADCSRA, ADSC))
	{
		*Pdata = ADC;
		status = ADC_READ;
		ADCflag = TRUE;
	}
	return status;
}





u16 ADC_ReadVolt(ADC_Channel_type ch)
{
	u16 adc = ADC_Read(ch);
	u16 volt = (u16)(((u32) adc * (u32) volt_ref) / (u32)1024);
	return volt;
}

/**************************** ADC Enable & Disable **************************************/
void ADC_Enable(void)
{
	/*  ADC enable */
	SET_BIT(ADCSRA, ADEN);
}

void ADC_Disable(void)
{
	/*  ADC enable */
	CLR_BIT(ADCSRA, ADEN);
}


/**************************** ADC Interrupt function **************************************/

void ADC_ClearedFlag(void)
{
	SET_BIT(ADCSRA, ADIF);
}

void ADC_InterruptEnable(void)
{
	SET_BIT(ADCSRA, ADIE);
}

void ADC_InterruptDisable(void)
{
	CLR_BIT(ADCSRA, ADIE);
}
/********************************* ADC Call Back function *****************************************/

void ADC_SetCallBack(void(*LocalPtr)(void))
{
	ADC_Fptr = LocalPtr;
}
/********************************* ADC ISR functions*********************************************/

ISR(ADC_vect)
{
	ADCflag = TRUE;
	if (ADC_Fptr != NULLPTR)
	{
		ADC_Fptr();
	}
}

