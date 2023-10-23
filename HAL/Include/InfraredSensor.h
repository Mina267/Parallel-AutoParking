

#ifndef INFRAREDSENSOR_H_
#define INFRAREDSENSOR_H_

/* IR enum */
typedef enum
{
	_1_INFRA_SENSOR = 0,
	_2_INFRA_SENSOR = 1,
	}InfraredSensor_t;

/* Status of IR sensor */
typedef enum
{
	DETECTED_OBSTACLE,
	NO_OBSTACLE
	}InfraredSensor_Status_t;

#define _1_IR_PIN			PINC6
#define _2_IR_PIN			PINB2

#define LEFT_IR_SENSOR		_1_IR_PIN
#define RIGHT_IR_SENSOR		_2_IR_PIN


/* Initialization Infra red sensor with external interrupt
 * Enable external interrupt zero & one
 *`Set call back function of external interrupt
 * Initialize interrupt on falling edge.
 */
void InfraredSensorEXI_Init(void);
/* Initialization Infra red sensor with DIO */
void InfraredSensor_Init(void);
/* Running of infra red sensor */
void InfraredSensor_Runnable(void);
/* Get status of IR Sensor read */
InfraredSensor_Status_t InfraredSensor_Getter(InfraredSensor_t Sensor);

#endif /* INFRAREDSENSOR_H_ */