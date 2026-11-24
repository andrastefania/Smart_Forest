
#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <zephyr/kernel.h>

struct sensor_data {
    double temperature;
    double humidity;
};

extern struct k_msgq sensor_queue;

#endif
