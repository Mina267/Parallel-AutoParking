

#ifndef DIAGNOSTIC_FRAME_PRIVATE_H_
#define DIAGNOSTIC_FRAME_PRIVATE_H_

/* Change system mode request */
#define SELECT_MODE				((u8)0x7C)

/* Mode Requests */
#define BLUETOOTH_CONTROL_REQ	((u8)0x01)
#define FREE_RUN_REQ			((u8)0x02)
#define LINE_FOLLOWER_REQ		((u8)0x03)
#define MAZE_REQ				((u8)0x04)

/* Operation Requests */
#define FOWARD_DIR_REQ			((u8)0x20)
#define BACKWARD_DIR_REQ		((u8)0x30)
#define RIGHT_DIR_REQ			((u8)0x40)
#define LEFT_DIR_REQ			((u8)0x50)
#define STOP_REQ				((u8)0x60)
#define START_REQ				((u8)0x70)

#define NEGATIVE_RES			((u8)0x7f)

#define MAIN_REQ	0
#define SUB_REQ		1
#define FRAME_SIZE	2

/* Data receive Union */
typedef union
{
	u8 Diag_Array[2];
	struct
	{
		u8 u8_Byte1_Data;
		u8 u8_Byte2_Data;
	};
	struct
	{
		u16 u16_Data;
	};
	
}DiagFrame_type;

#endif /* DIAGNOSTIC_FRAME_PRIVATE_H_ */