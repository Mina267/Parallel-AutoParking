#ifndef  I2C_H 
#define  I2C_H

#define I2C_START        0x08
#define I2C_MT_SLA_W_ACK 0x18
#define I2C_MT_DATA_ACK  0x28
#define I2C_REPEAT_START 0x10
#define I2C_MT_SLA_R_ACK 0x40
#define I2C_MR_DATA_NACK 0x58

void  I2C_voidInit(void);
void  I2C_voidStart(void);
u8 I2C_u8GetStatus(void);
void  I2C_voidWrite(u8 u8ByteCpy);
void  I2C_voidStop(void);
u8 I2C_u8ReadWithoutAck(void);
u8 I2C_u8ReadWithAck(void) ;

#endif