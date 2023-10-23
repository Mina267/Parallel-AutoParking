#ifndef  I2C_CFG_H 
#define  I2C_CFG_H



#define I2C_MY_ADDRESS    50
#define I2C_GENERAL_CALL  ENABLED
/* I2c freq = Fcpu /(16+2(I2C_TWBR_VALUE).(I2C_PRESCALLER))*/
#define I2C_TWBR_VALUE   16
#define I2C_PRESCALLER   I2C_PRESCALLER_4 

#endif