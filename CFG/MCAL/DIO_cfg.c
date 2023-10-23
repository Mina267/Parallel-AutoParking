#include "StdTypes.h"
#include "DIO_interface.h"

const DIO_PinStatus_type PinsStatusArray[TOTAL_PINS] = {
	INFREE, /* Port A Pin 0 */ /* ADC 0 */
	OUTPUT, /* Port A Pin 1 */ /* ADC 1 */
	OUTPUT, /* Port A Pin 2 */ /* ADC 2 */
	OUTPUT, /* Port A Pin 3 */ /* ADC 3 */
	OUTPUT, /* Port A Pin 4 */ /* ADC 4 */
	OUTPUT, /* Port A Pin 5 */ /* ADC 5 */
	OUTPUT, /* Port A Pin 6 */ /* ADC 6 */
	INFREE, /* Port A Pin 7 */ /* ADC 7 */
	INPULL, /* Port B Pin 0 */ /* T0 / XCK */ 
	INPULL, /* Port B Pin 1 */ /* T1 */
	INPULL, /* Port B Pin 2 */ /* AIN0 / INT2 */
	OUTPUT, /* Port B Pin 3 */ /* AIN1 / OC0 */
	OUTPUT, /* Port B Pin 4 */ /* SS */
	OUTPUT, /* Port B Pin 5 */ /* MOSI */
	INFREE, /* Port B Pin 6 */ /* MISO */
	OUTPUT, /* Port B Pin 7 */ /* SCK */
	OUTPUT, /* Port C Pin 0 */ /* SCL */
	OUTPUT, /* Port C Pin 1 */ /* SDA */
	OUTPUT, /* Port C Pin 2 */ /* TCK */
	OUTPUT, /* Port C Pin 3 */ /* TMS */
	OUTPUT, /* Port C Pin 4 */ /* TDO */
	OUTPUT, /* Port C Pin 5 */ /* TDI  */
	OUTPUT, /* Port C Pin 6 */ /* TOSC1 */
	OUTPUT, /* Port C Pin 7 */ /* TOSC0 */
	OUTPUT, /* Port D Pin 0 */ /* RXD */
	OUTPUT, /* Port D Pin 1 */ /* TXD */
	INPULL, /* Port D Pin 2 */ /* INT0 */
	INPULL, /* Port D Pin 3 */ /* INT1 */
	INPULL, /* Port D Pin 4 */ /* OCR1B */
	INPULL, /* Port D Pin 5 */ /* OCR1A */
	OUTPUT, /* Port D Pin 6 */ /* ICP1 */
	OUTPUT, /* Port D Pin 7 */ /* OC2 */
};

