
#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_


#define MAX_PINS_INPORT 8
#define MAX_NUMOF_PORT	4


extern const DIO_PinStatus_type PinsStatusArray[TOTAL_PINS];
static Error_type DIO_InitPin(DIO_Pin_type Pin, DIO_PinStatus_type status);



#endif /* DIO_PRIVATE_H_ */