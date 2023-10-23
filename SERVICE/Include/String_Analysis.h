


#ifndef STRING_ANALYSIS_H_
#define STRING_ANALYSIS_H_

#define FIRST_CHAR		0
#define LCD_NO_STR			0
#define LCD_STR_FOUND		1
#define LCD_TASK_FOUND		2


// RGB String analysis enum.
typedef enum
{
	RGB_WEONG_COMMAND,
	RGB_NO_COMMAND,
	RGB_ACCEPTED_COMMAND,
	}RGB_CommandStatus_t;

// Smart Home String analysis enum.
typedef enum
{
	SH_WEONG_COMMAND,
	SH_NO_COMMAND,
	SH_ACCEPTED_COMMAND,
	}SH_CommandStatus_t;
	
/* String compare ceaseless	*/
typedef enum
{
	STR_NOMATCH,
	STR_MATCH,
	}STR_Status;

/************ Analysis string of RGB mode ****************/
// Take String From UART. and analysis Command User send
RGB_CommandStatus_t StrAnalysisRGBMode(char *Str_Recived, char *StrCommand, char *StrTask);
/************ Analysis string of Smart home mode ********/
SH_CommandStatus_t StrAnalysis_SmartHomeMode(c8 *Str_Recived, c8 *StrCommand, u32 *NumOrder, c8 *LCD_Str);

/* String compare ceaseless but should Expected be all upper case
 * Received  , Expected return STR_NOMATCH or STR_MATCH */
STR_Status Str_cmp(c8 *strReceive, c8 *StrExpected);
/* Convert String to upper case */
void Str_toUpper(c8 *str);

#endif /* STRING_ANALYSIS_H_ */