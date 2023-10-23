

#ifndef BUTTHON_INTERFACE_H_
#define BUTTHON_INTERFACE_H_
/******** Cfg *****************/
/*** PULLUP  OR PULLDOWN*******/
#define BUTTON_PRESS_TYPE PULLUP

/******** Private *************/
#define PULLUP		LOW
#define PULLDOWN	HIGH



typedef enum
{
	BUTTON1,
	BUTTON2,
	BUTTON3,
	BUTTON4
	}BUTTON_type;
	
typedef enum
{
	NOT_PRESSED,
	PRESSED
	}BUTTON_Press_State;
	
	
#define BUTTON_NUM	4


#ifdef BUTTON_PROG
const DIO_Pin_type BUTTON_array[BUTTON_NUM] = {
	PIND2,  // 1st Button
	PIND3, // 2nd Button
	PIND4, // 3rd Button
	PIND5, // 4th Button
};
#endif


void BUTTON_Init(void);
BUTTON_Press_State BUTTON_Read(BUTTON_type Button);
BUTTON_Press_State BUTTON_ReadDelay(BUTTON_type Button);
BUTTON_Press_State BUTTON_ReadBussy(BUTTON_type Button);
BUTTON_Press_State BUTTON_ReadCont(BUTTON_type Button);

#endif /* BUTTHON_INTERFACE_H_ */