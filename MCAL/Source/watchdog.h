#ifndef WATCHDOG_H_
#define WATCHDOG_H_

typedef enum {
	WDT_TIMEOUT_16MS = 0,
	WDT_TIMEOUT_32MS,
	WDT_TIMEOUT_65MS,
	WDT_TIMEOUT_130MS,
	WDT_TIMEOUT_260MS,
	WDT_TIMEOUT_520MS,
	WDT_TIMEOUT_1S,
	WDT_TIMEOUT_2S
} watchdog_timeout_t;

/* A function to set the watchdog timer with the specified timeout value */ 
void watchdog_set(watchdog_timeout_t time);
/* A function to stop the watchdog timer */
void watchdog_stop(void);
/* Reset Watch Dog Timer */
void watchdog_Reset(watchdog_timeout_t time);

 


#endif /* WATCHDOG_H_ */