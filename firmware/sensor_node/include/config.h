
#ifndef APP_CONFIG_H
#define APP_CONFIG_H

/* Sensor sampling */
#define SENSOR_INTERVAL_SECONDS 10

#define MQ2_COUNTER 20
#define MQ2_DELAY 20
#define MQ2_MINIMUM_VALID_RFEADINGS 15

/* Temperature thresholds (Celsius) */
#define TEMP_HIGH_THRESHOLD 35.0
#define TEMP_EXTREME_THRESHOLD 55.0

/* Sensor error values */
#define DHT_ERROR_VALUE -1000.0
#define MQ2_ERROR_VALUE -1

/* MQ-2 thresholds (raw ADC values - experimental) */
#define MQ2_HIGH_THRESHOLD 250
#define MQ2_EXTREME_THRESHOLD 400

/* Flame detection*/
#define FLAME_ERROR_VALUE -1
#define FLAME_NOT_DETECTED 0
#define FLAME_DETECTED 1

#endif
