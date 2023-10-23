


#ifndef DIAGNOSTIC_FRAME_H_
#define DIAGNOSTIC_FRAME_H_



/* Request order */
typedef enum
{
	BLU_FOWARD_DIR_REQ,
	BLU_BACKWARD_DIR_REQ,
	BLU_RIGHT_DIR_REQ,
	BLU_LEFT_DIR_REQ,
	BLU_STOP_REQ,
	FREE_RUN_STOP_REQ,
	FREE_RUN_START_REQ,
	LINE_FOLLOWER_STOP_REQ,
	LINE_FOLLOWER_START_REQ,
	MAZE_STOP_REQ,
	MAZE_START_REQ,
	NO_REQ
	}RecFrameStatus_t;
	

/* system modes */
typedef enum
{
	BLUETOOTH_CONTROL_MODE,
	FREE_RUN_MODE,
	LINE_FOLLOWER_MODE,
	MAZE_MODE
	}CarControl_Mode;


/* Initialization */
void Frame_Diag_Init(void);
/* return the mode system operate in and request required */
void Frame_Diag(RecFrameStatus_t *FrameStatus, CarControl_Mode *Mode);



#endif /* DIAGNOSTIC_FRAME_H_ */