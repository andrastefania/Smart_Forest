
#ifndef ALERT_LOGIC_H
#define ALERT_LOGIC_H

#include <stdbool.h>
#include "sensor_data.h"

enum alert_level {
    ALERT_NORMAL,
    ALERT_WARNING,
    ALERT_CRITICAL,
    ALERT_UNKNOWN
};

struct alert_result {
    enum alert_level level;

    bool high_temperature;
    bool extreme_temperature;
    bool high_gas;
    bool extreme_gas;
    bool flame_detected;
    bool assessment_complete;
};

struct alert_result evaluate_alert(
    const struct sensor_data *data
);

#endif
