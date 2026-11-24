
#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <zephyr/kernel.h>
#include "config.h"

struct sensor_data {
    double temperature;
    double humidity;
    int mq2_raw;
};

extern struct k_msgq sensor_queue;

#endif
