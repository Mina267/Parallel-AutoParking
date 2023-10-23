
#ifndef STDTYPES_H_
#define STDTYPES_H_

typedef unsigned char u8;
typedef   signed char s8;
typedef    char		  c8;

typedef unsigned int u16;
typedef   signed int s16;

typedef unsigned long u32;
typedef   signed long s32;

#define NULLPTR ((void*)0)

#define NULL	(0)

typedef enum
{
	EOK,
	ENOK,
	PARAMRETER_OUT_RANGE,
	PARAMERTE_NULL_PTR
	
}tenuErrrorStatus;

typedef enum
{
	OK,
	NOK,
	ERROR,
	NULL_POINTER,
	OUT_OF_RANGE,
	}Error_type;
	
typedef enum
{
	FALSE,
	TRUE,
	}bool_t;

#define MAX_U8 ((u8) 255)
#define MIN_U8 ((u8) 0)
#define MAX_S8 ((s8) 127)
#define MIN_S8 ((s8) -128)
	
#define MAX_U16 ((u16) 65535)
#define MIN_U16 ((u16) 0)
#define MAX_S16 ((s16) 32767)
#define MIN_S16 ((s16) -32768)

#define MAX_U32 ((u32) 4294967295)
#define MIN_U32 ((u32) 0)
#define MAX_S32 ((s32) 2147483647)
#define MIN_S32 ((s32) -2147483648)

#define SIZEOF_U8	(sizeof(u8) * 8)
#define SIZEOF_U16	(sizeof(u16) * 8)
#define SIZEOF_U32	(sizeof(u32) * 8)

typedef union
{
	struct
	{
		char c1;
		char c2;
		char c3;
		char c4;
		char c5;
		char c6;
		char c7;
		char c8;
	};
	struct
	{
		short s1;
		short s2;
		short s3;
		short s4;
	};
	struct
	{
		int i1;
		int i2;
	};
	long long l;
}u64_ut;

typedef union
{
	struct
	{
		u8 u8_1;
		u8 u8_2;
		u8 u8_3;
		u8 u8_4;
		};
	struct
	{
		u16 u16_1;
		u16 u16_2;
	};
	u32 u32_t;
	
	}u32_type;
	
typedef union
{
	struct
	{
		u8 u8_1;
		u8 u8_2;

	};

	u16 u16_t;	
}u16_type;	




#endif /* STDTYPES_H_ */