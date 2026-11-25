
#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <zephyr/kernel.h>
struct sensor_data {
    double temperature;
    double humidity;
    int mq2_raw;
    bool flame_detected;
};

extern struct k_msgq sensor_queue;

#endif
