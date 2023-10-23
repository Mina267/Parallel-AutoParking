


#ifndef EEPROM_INTRFACE_H_
#define EEPROM_INTRFACE_H_
volatile bool_t Intr_Flag; 
typedef enum
{
	EE_READ,
	EE_NREAD,
	EE_WRITE,
	EE_NWRITE,
	EE_READY,
	EE_NREADY,
	}EEPROM_status;

void EEPROM_Init(void);
void EEPROM_writeBusy(u16 Address, u8 Data);
u8 EEPROM_readBusy(u16 Address);
EEPROM_status EEPROM_write(u16 Address, u8 Data);
EEPROM_status EEPROM_read(u16 Address, u8 *Pdata);
EEPROM_status EEPROM_STATUS(void);
void EEPROM_InterruptEnable(void);
void EEPROM_InterruptDisable(void);
EEPROM_status EEPROM_Status(void);
void EEPROM_SetCallBack(void(*LocalFptr)(void));

#endif /* EEPROM_INTRFACE_H_ */