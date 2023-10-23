#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#include "watchdog.h"



//  a function to set the watchdog timer with the specified timeout value
void watchdog_set(watchdog_timeout_t time)
{
	// ORing the time value with the default value of ( 0x08 = 0b00001000 ) 
	u8 wdtcsr_value = 0x08 | time ;  

	// Enable changing the watchdog timer settings by writing specific values to the WDTCSR register
	// This requires two writes within four clock cycles, so we do it in one step by ORing the values
	// Note that the WDTOE and WDE bits must be written to logic one before the actual settings can be changed
	WDTCR = WDTCR | (1 << WDTOE) | (1 << WDE);

	// Set the new watchdog timer value by writing the new WDTCSR register value
	// This clears the WDTOE bit and starts the watchdog timer with the new timeout value
	WDTCR = wdtcsr_value;
}

//  a function to stop the watchdog timer  
void watchdog_stop(void)
{
	/* Write logical one to WDTOE and WDE */
	WDTCR = (1<<WDTOE) | (1<<WDE);
	/* Turn off WDT */
	WDTCR = 0x00;
}
/* Reset Watch Dog Timer */
void watchdog_Reset(watchdog_timeout_t time)
{
	watchdog_stop();
	watchdog_set(time);
}