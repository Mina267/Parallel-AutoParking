#include "StdTypes.h"
#include "UART_Interface.h"
#include "BCM.h"

#include "Diagnostic_Frame.h"
#include "Diagnostic_Frame_Private.h"


static UART_Rec_status_t Rec_status;
static DiagFrame_type Diag_Data;

/* Initialization */
void Frame_Diag_Init(void)
{
	BCM_FrameReceive_Init();
	BCM_SendFrmaeInit();
}


void Frame_Diag(RecFrameStatus_t *FrameStatus, CarControl_Mode *Mode)
{
	Rec_status = BCM_FrameReceive_GetterFrameAshync(Diag_Data.Diag_Array);
	static u8 res_frame[FRAME_SIZE];
	res_frame[MAIN_REQ] = NEGATIVE_RES;
	
	*FrameStatus = NO_REQ;
	if (Rec_status == FRAME_RECEIVED)
	{
		/* If user request Select mode frame to change operation mode */
		if (Diag_Data.Diag_Array[MAIN_REQ] == SELECT_MODE)
		{
			/* If user request Bluetooth mode operation change mode to it */
			if (Diag_Data.Diag_Array[SUB_REQ] == BLUETOOTH_CONTROL_REQ)
			{
				*Mode = BLUETOOTH_CONTROL_MODE;
			}
			/* If user request Free run mode operation change mode to it */
			else if (Diag_Data.Diag_Array[SUB_REQ] == FREE_RUN_REQ)
			{
				*Mode = FREE_RUN_MODE;
			}
			/* If user request Free lone flower operation change mode to it */
			else if (Diag_Data.Diag_Array[SUB_REQ] == LINE_FOLLOWER_REQ)
			{
				*Mode = LINE_FOLLOWER_MODE;
			}
			/* If user request kine follower mode operation change mode to it */
			else if (Diag_Data.Diag_Array[SUB_REQ] ==  MAZE_REQ)
			{
				*Mode = MAZE_MODE;
			}
			/* If mode not in operating CFG car mode send negative response */
			else
			{
				/* Send Negative Response Frame */;
				res_frame[SUB_REQ] = (SELECT_MODE + 0x40);
				BCM_SendFrameSetter(res_frame);
			}
		}
		else if ((Diag_Data.Diag_Array[MAIN_REQ] == BLUETOOTH_CONTROL_REQ) && (*Mode == BLUETOOTH_CONTROL_MODE))
		{
			if (Diag_Data.Diag_Array[SUB_REQ]  == FOWARD_DIR_REQ)
			{
				*FrameStatus = BLU_FOWARD_DIR_REQ;
			}
			else if (Diag_Data.Diag_Array[SUB_REQ]  == BACKWARD_DIR_REQ)
			{
				*FrameStatus= BLU_BACKWARD_DIR_REQ;
			}
			else if (Diag_Data.Diag_Array[SUB_REQ]  == RIGHT_DIR_REQ)
			{
				*FrameStatus = BLU_RIGHT_DIR_REQ;
			}
			else if (Diag_Data.Diag_Array[SUB_REQ]  == LEFT_DIR_REQ)
			{
				*FrameStatus = BLU_LEFT_DIR_REQ;
			}
			/* Stop request */
			else if (Diag_Data.Diag_Array[SUB_REQ]  == STOP_REQ)
			{
				*FrameStatus = BLU_STOP_REQ;
			}
			/* If request received not in CFG frames send to user negative response */
			else
			{
				/* Send Negative Response Frame */
				res_frame[SUB_REQ] = (BLUETOOTH_CONTROL_REQ + 0x40);
				BCM_SendFrameSetter(res_frame);
			}
		}
		else if ((Diag_Data.Diag_Array[MAIN_REQ] == LINE_FOLLOWER_REQ) && (*Mode == LINE_FOLLOWER_MODE))
		{
			/* Start request */
			if (Diag_Data.Diag_Array[SUB_REQ]  == START_REQ)
			{
				*FrameStatus = LINE_FOLLOWER_START_REQ;
			}
			/* Stop request */
			else if (Diag_Data.Diag_Array[SUB_REQ]  == STOP_REQ)
			{
				*FrameStatus = LINE_FOLLOWER_STOP_REQ;
			}
			else
			{
				/* Send Negative Response Frame */
				res_frame[SUB_REQ] = (LINE_FOLLOWER_REQ + 0x40);
				BCM_SendFrameSetter(res_frame);
			}
			
		}
		else if ((Diag_Data.Diag_Array[MAIN_REQ] == FREE_RUN_REQ) && (*Mode == FREE_RUN_MODE))
		{
			/* Start request */
			if (Diag_Data.Diag_Array[SUB_REQ]  == START_REQ)
			{
				*FrameStatus = FREE_RUN_START_REQ;
			}
			/* Stop request */
			else if (Diag_Data.Diag_Array[SUB_REQ]  == STOP_REQ)
			{
				*FrameStatus = FREE_RUN_STOP_REQ;
			}
			else
			{
				/* Send Negative Response Frame */
				res_frame[SUB_REQ] = (FREE_RUN_REQ + 0x40);
				BCM_SendFrameSetter(res_frame);
			}
			
		}
		else if ((Diag_Data.Diag_Array[MAIN_REQ] == MAZE_REQ) && (*Mode == MAZE_MODE))
		{
			/* Start request */
			if (Diag_Data.Diag_Array[SUB_REQ]  == START_REQ)
			{
				*FrameStatus = MAZE_START_REQ;
			}
			/* Stop request */
			else if (Diag_Data.Diag_Array[SUB_REQ]  == STOP_REQ)
			{
				*FrameStatus = MAZE_STOP_REQ;
			}
			else
			{
				/* Send Negative Response Frame */
				res_frame[SUB_REQ] = (MAZE_REQ + 0x40);
				BCM_SendFrameSetter(res_frame);
			}
		}
		else
		{
			/* Send Negative Response Frame */
			res_frame[SUB_REQ] = (Diag_Data.Diag_Array[MAIN_REQ] + 0x40);
			BCM_SendFrameSetter(res_frame);			
		}
		
		BCM_SendFrameRunnable();
		
		/* Delete frame as indicate it read and executed */
		Diag_Data.u16_Data = NULL;
	}

	
}