

#ifndef BCM_CFG_H_
#define BCM_CFG_H_


/************************ Send String ******************************/
/* Determine maximum number for How many element in Queue */
#define QUEUE_SEND_SIZE		10
// define 1st last string pattern if you did not want set it to Zero
#define _1ST_LAST_STR_PATTERN	'\n'
// define 2nd last string pattern if you did not want set it to Zero
//#define _2ST_LAST_STR_PATTERN	 0


/************************ Recieve String ******************************/

/* Determine maximum number for How many element in Queue */
#define QUEUE_RECSTR_SIZE	3
/* Max Size of string Queue can take by value */
#define MAX_STR_SIZE		35

// Write the end of String you want to receive
// If you Did not want Second Pattern put Zero
// DockLight 1st 0x0D --> 2nd 0x0A
#define _1ST_STR_END_PATTERN	0x0d
#define _2ST_STR_END_PATTERN	0x00

/************************ Recieve Frame ******************************/
/* Size of frame you want to receive in Queue */
#define FRAME_SIZE	2
/* Determine maximum number for How many element in Queue */
#define QUEUE_REC_SIZE	5

/************************ Send Frame ******************************/
/* Size of frame you want to receive in Queue */
#define FRAME_SEND_SIZE			2
/* Determine maximum number for How many element in Queue */
#define QUEUE_SEND_FRAME_SIZE	4
/* Select if you want to send string or frame with fixed size (SEND_FRAME - SEND_STRING)
 * Deferent string will send until reach NULL
 * Will frame will send data until reach size of frame CFG previous in FRAME_SEND_SIZE macro*/
#define SEND_FRAME_TYPE		SEND_FRAME

/* define 1st last string pattern if you did not want set it to Zero */
//#define _1ST_LAST_FRAME_PATTERN	'\n'

/* define 2nd last string pattern if you did not want set it to Zero */
//#define _2ST_LAST_FRAME_PATTERN	 0


#endif /* BCM_CFG_H_ */