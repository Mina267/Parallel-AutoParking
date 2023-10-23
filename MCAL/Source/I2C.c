#include "StdTypes.h"
#include "Utils.h"

#include "I2C.h"
#include "I2C_cfg.h"
#include "I2C_priv.h"
void  I2C_voidInit(void)
{
	 /* init address to mc if any master try to connect ,it will be through this address*/
	u8 u8MyAddLoc = 0 ;
	u8MyAddLoc = I2C_MY_ADDRESS <<1 ;
	#if I2C_GENERAL_CALL == ENABLED
	SET_BIT(u8MyAddLoc , 0 ) ;
	#else 
	CLR_BIT(u8MyAddLoc , 0 ) ;
	#endif 
    TWAR  = u8MyAddLoc ;    /*TWAR is address register*/    
	/* congigure clock by bits 0 , 1 in a TWSR reg */   
	#if   I2C_PRESCALLER == I2C_PRESCALLER_1
	TWSR = 0b00000000;
	#elif I2C_PRESCALLER == I2C_PRESCALLER_4
	TWSR = 0b00000001;
	#elif I2C_PRESCALLER == I2C_PRESCALLER_16
	TWSR = 0b00000010;
	#else
	TWSR = 0b00000011;
	#endif
	TWBR = I2C_TWBR_VALUE ;  /* configure the frequency of the clock by the macros I2C_TWBR_VALUE in  TWBR REG*/

	TWCR = 0b00000100;  /* enable I2C prepheral by set bit 2 by 1 in  TWCR REG */ 
}
void  I2C_voidStart(void)  /* master try to send start condition*/
{
	TWCR = 0b10100100;  /* clear flag bit number 7 by writ  1 , disable ACK bit number 6 by write 0 */
	                    /* enable I2C by bit 2 ,set bit 5 by 1 to make start condition */
	
	while(READ_BIT(TWCR,7)==0);  /* wait for INTerrupt  flag is heigh when start condition is done , bit 7 in TWCR REG is heigh */
}
u8 I2C_u8GetStatus(void)
{
	/* check on status code that returned after any peration in frame  */
	return (TWSR &0xF8) ;  /* status code is stored in last 5 bits in TWSR REG , so ANDing it with 0xF8 or 0b11111000 */
}
void  I2C_voidWrite(u8 u8ByteCpy)
{
	/* store value of u8ByteCpy in TWDR data REG  */
	TWDR = u8ByteCpy ;
	TWCR = 0b10000100;  /* clear flag bit number 7 by writ  1 , disable ACK bit number 6 by write 0 ,enable I2C by bit 2*/
	while(READ_BIT(TWCR,7)==0); /* wait for INTerrupt  flag is heigh when data stored in TWDR REG  , bit 7 in TWCR REG is heigh */
}
void  I2C_voidStop(void)
{
	TWCR = 0b10010100; /* set bit number 4 by 1 to mak stop condition */
}
u8 I2C_u8ReadWithoutAck(void)
{
	TWCR = 0b10000100;  /* clear flag bit number 7 by writ  1 , disable ACK bit number 6 by write 0 ,enable I2C by bit 2*/
	while(READ_BIT(TWCR,7)==0); /* wait until TWDR REG store the recieved data , after receiving flag is heigh  */
	return TWDR ; 
}

u8 I2C_u8ReadWithAck(void)
{
	TWCR = 0b11000100; /* set ACK  by bit number 6 */ 
	while(READ_BIT(TWCR,7)==0);
	return TWDR ;
}







