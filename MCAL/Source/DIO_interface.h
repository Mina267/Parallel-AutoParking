#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_



typedef enum
{
	OUTPUT,
	INFREE,
	INPULL
	}DIO_PinStatus_type;


typedef enum
{
	PINA0,
	PINA1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	TOTAL_PINS,
}DIO_Pin_type;

typedef enum
{
	PA,
	PB,
	PC,
	PD
}DIO_Port_type;

typedef enum
{
	PA_0TO3,
	PA_4TO7,
	PB_0TO3,
	PB_4TO7,
	PC_0TO3,
	PC_4TO7,
	PD_0TO3,
	PD_4TO7,

}DIO_HalfPort_type;


typedef enum
{
	LOW,
	HIGH,
}DIO_PinVoltage_type;



	
	

extern void DIO_Init(void);
extern Error_type DIO_WritePin(DIO_Pin_type Pin, DIO_PinVoltage_type  status);
extern DIO_PinVoltage_type DIO_ReadPin(DIO_Pin_type Pin);
extern Error_type DIO_TogglePin(DIO_Pin_type pin);
extern void DIO_WritePort(DIO_Port_type port,u8 value);
extern u8 DIO_ReadPort(DIO_Port_type port);
extern void DIO_WriteHalfPort(DIO_HalfPort_type port,u8 value);


#endif /* DIO_INTERFACE_H_ */