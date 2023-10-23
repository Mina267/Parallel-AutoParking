#ifndef  I2C_PRIV_H 
#define  I2C_PRIV_H

#define ENABLED    1
#define DISABLED   0

#define I2C_PRESCALLER_1     0
#define I2C_PRESCALLER_4     1
#define I2C_PRESCALLER_16    2
#define I2C_PRESCALLER_64    3

#define TWBR *((volatile u8*) 0x20 )
#define TWCR *((volatile u8*) 0x56 )
#define TWSR *((volatile u8*) 0x21 )
#define TWDR *((volatile u8*) 0x23 )
#define TWAR *((volatile u8*) 0x22 )

#endif