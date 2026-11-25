
#include "alert_logic.h"
#include "config.h"

struct alert_result evaluate_alert(
    const struct sensor_data *data)
{
    struct alert_result result = {
        .level = ALERT_UNKNOWN,
        .assessment_complete = false
    };

    /* Temperature */
    if (data->temperature != DHT_ERROR_VALUE) {
        result.high_temperature =
            data->temperature >= TEMP_HIGH_THRESHOLD;

        result.extreme_temperature =
            data->temperature >= TEMP_EXTREME_THRESHOLD;
    }

    /* Gas thresholds - to be calibrated */
    result.high_gas = false;
    result.extreme_gas = false;

    /* Flame detection - not yet integrated */
    result.flame_detected = false;

    /* Count distinct hazard categories */
    int danger_count =
        (result.high_temperature || result.extreme_temperature) +
        (result.high_gas || result.extreme_gas) +
        result.flame_detected;

    if (danger_count >= 2) {
        result.level = ALERT_CRITICAL;
    } else if (danger_count == 1) {
        result.level = ALERT_WARNING;
    } else if (result.assessment_complete) {
        result.level = ALERT_NORMAL;
    }

    return result;
}
