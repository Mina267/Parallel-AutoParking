#include "StdTypes.h"
#include "String_Analysis.h"


/************ Analysis string of RGB mode ****************/
/* Take String From UART. and analysis Command User send */
RGB_CommandStatus_t StrAnalysisRGBMode(char *Str_Recived, char *StrCommand, char *StrTask)
{
	/* Receive string analysis Status */ 
	RGB_CommandStatus_t CommandStatus = RGB_ACCEPTED_COMMAND;
	/* If string is NULL */
	if (Str_Recived[FIRST_CHAR] == NULL)
	{
		CommandStatus = RGB_NO_COMMAND;
	}
	else
	{
		u8 ColorIndex = 0;
		u8 StrIndex;
		// Take First Command "RGB"
		for (StrIndex = 0; Str_Recived[StrIndex] != '_'; StrIndex++)
		{
			// If did not Found '_' and found NULL Exit.
			if (Str_Recived[StrIndex] == NULL)
			{
				CommandStatus = RGB_WEONG_COMMAND;
				break;
			}
			/* Save command receive to command string */
			StrCommand[StrIndex] = Str_Recived[StrIndex];
		}
		/* NULL at end of String */
		StrCommand[StrIndex] = NULL;
		/* Increment string Index */
		StrIndex++;
		/* Check if First Command is RGB */
		if (Str_cmp(StrCommand, "RGB") == STR_NOMATCH)
		{
			CommandStatus = RGB_WEONG_COMMAND;
		}
		/* Take Name of color */
		while (Str_Recived[StrIndex])
		{
			/* Save color name receive to color string */
			StrTask[ColorIndex] = Str_Recived[StrIndex];
			/* Increment color Index */
			ColorIndex++;
			/* Increment string Index */
			StrIndex++;
		}
		/* NULL at end of String */
		StrTask[ColorIndex] = NULL;
		
		/* If StrTask Still NULL then there is no color */
		if (StrTask == NULL)
		{
			CommandStatus = RGB_WEONG_COMMAND;
		}
	}
	/* Return Status of analysis of string */
	return CommandStatus;
}



/************ Analysis string of Smart home mode ********/
SH_CommandStatus_t StrAnalysis_SmartHomeMode(c8 *Str_Recived, c8 *StrCommand, u32 *NumOrder, c8 *LCD_Str)
{
	/* Receive string analysis Status */ 
	SH_CommandStatus_t CommandStatus = SH_ACCEPTED_COMMAND;
	bool_t Num_flag = TRUE;
	u8 LCD_flag = LCD_NO_STR;
	u8 LCD_StrIndex = 0;
	u8 StrIndex;
	
	/* If string is NULL */
	if (Str_Recived[FIRST_CHAR] == NULL)
	{
		CommandStatus = SH_WEONG_COMMAND;
	}
	else
	{
		/************************************** Take Task name *****************************************/
		for (StrIndex = 0; Str_Recived[StrIndex] != '_'; StrIndex++)
		{
			/* If found NULL Break */
			if (Str_Recived[StrIndex] == NULL)
			{
				Num_flag = FALSE;
				break;
			}
			/* If Found '-' Break and set LCD_flag to 1.
			 * means string receive to write in LCD */
			else if (Str_Recived[StrIndex] == '-')
			{
				
				LCD_flag = LCD_STR_FOUND;
				/* No Number */
				Num_flag = FALSE;
				break;
			}
			/* Store task name in strCommand */
			StrCommand[StrIndex] = Str_Recived[StrIndex];
		}
		/* NULL at end of String */
		StrCommand[StrIndex] = 0;
		/* Increment string Index */
		StrIndex++;
		
		
		/************************************** Take LCD Task string ***************************************/
		/* If task is LCD then user send string to write in LCD */
		if (Str_cmp(StrCommand, "LCD") == STR_MATCH && LCD_flag == LCD_STR_FOUND)
		{
			LCD_flag = LCD_TASK_FOUND;
		}
		/* If not wrong frame command */
		else
		{
			CommandStatus = SH_WEONG_COMMAND;
		}
		
		// To Write Strings in LCD
		if (LCD_flag == LCD_TASK_FOUND)
		{
			/* Loop Until reach NULL */
			while (Str_Recived[StrIndex])
			{
				/* Store string to write in LCD in LCD string */
				LCD_Str[LCD_StrIndex] = Str_Recived[StrIndex];
				/* Increment LCD Index */
				LCD_StrIndex++;
				/* Increment string Index */
				StrIndex++;
			}
			/* NULL at end of String */
			LCD_Str[LCD_StrIndex] = NULL;
		}
		
		/************************************** Take Task order number ***************************************/
		/* Set number of task order to zero */
		*NumOrder = 0;
		/* Take Task number if can */
		if (Num_flag)
		{
			/* Loop Until reach NULL */ 
			while (Str_Recived[StrIndex])
			{
				/* If character is Number */ 
				if ((Str_Recived[StrIndex] >= '0' && Str_Recived[StrIndex] <= '9'))
				{
					/* Equation to convert ASCII to real number */
					*NumOrder = (*NumOrder * 10) + (Str_Recived[StrIndex] - '0');
				}
				/* If not string error Wrong command received */
				else
				{
					CommandStatus = SH_WEONG_COMMAND;
				}
				/* Increment string Index */
				StrIndex++;
			}
		}
	}
	/* Return Status of analysis of string */
	return CommandStatus;
}


/* Received  , Expected return STR_NOMATCH or STR_MATCH */
STR_Status Str_cmp(c8 *strReceive, c8 *StrExpected)
{
	/* Convert receive string to upper case to compare strings ceaseless */
	Str_toUpper(strReceive);
	/* Loop until both reach NULL */
	for (u8 Index = 0; strReceive[Index] || StrExpected[Index]; Index++)
	{
		/* If there is no match return no match */
		if (strReceive[Index] != StrExpected[Index])
		{
			return STR_NOMATCH;
		}
	}
	/* If two strings match return strings match */
	return STR_MATCH;
}

/* Convert String to upper case */
void Str_toUpper(c8 *str)
{
	/* Loop Until reach NULL */ 
	for (u8 Index = 0; str[Index]; Index++)
	{
		/* If char is lower case convert to upper */
		if (str[Index] >= 'a' && str[Index] <= 'z')
		{
			str[Index] = str[Index] - 'a' + 'A';
		}
	}
}

