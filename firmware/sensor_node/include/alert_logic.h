
#ifndef ALERT_LOGIC_H
#define ALERT_LOGIC_H

#include <stdbool.h>

enum alert_level {
    ALERT_NORMAL,
    ALERT_WARNING,
    ALERT_CRITICAL,
    ALERT_UNKNOWN
};

struct alert_conditions {
    bool high_temperature;
    bool gas_detected;
    bool flame_detected;
    bool assessment_complete;
};

struct alert_result {
    enum alert_level level;
    struct alert_conditions causes;
};

struct alert_result evaluate_alert(
    const struct alert_conditions *conditions
);

#endif
