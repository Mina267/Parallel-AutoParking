


#ifndef AUTOPARKING_CFG_H_
#define AUTOPARKING_CFG_H_
/* Car Dimensions */
#define CAR_WIDTH				190
#define WIDTH_TOLERANCE			20
#define CAR_LENGTH				400
#define LENGTH_TOLERANCE		200
// cm/sec
#define START_CAR_VELOCITY		100
#define CAR_MOTOR				M1
// BARRIER
#define MIN_DIS_OFBARRIER		80
/* Parking protocol Steps time */
/* Time in ms */
#define FIRST_STEP_TIME			10000
#define SECOND_STEP_TIME		10000
#define THIRD_STEP_TIME			10000
#define FOURTH_STEP_TIME		5000
#define FIFTH_STEP_TIME			10000
/* Time Wait to decided this not good spot */
#define HINDRANCE_TIME			10000

#define SERVO_ADJ_DELAY			300
#define ENGINE_STOP_DELAY		300


#endif /* AUTOPARKING_CFG_H_ */