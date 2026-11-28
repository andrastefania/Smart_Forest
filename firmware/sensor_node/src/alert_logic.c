
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

    /* Gas */
    if (data->mq2_raw != MQ2_ERROR_VALUE) {
        result.high_gas =
            data->mq2_raw >= MQ2_HIGH_THRESHOLD;

        result.extreme_gas =
            data->mq2_raw >= MQ2_EXTREME_THRESHOLD;
    }

    /* Flame */
    result.flame_detected =
        (data->flame_detected == FLAME_DETECTED);

    /* Check if all sensors provided valid measurements */
    result.assessment_complete =
        (data->temperature != DHT_ERROR_VALUE) &&
        (data->mq2_raw != MQ2_ERROR_VALUE) &&
        (data->flame_detected == FLAME_NOT_DETECTED ||
         data->flame_detected == FLAME_DETECTED);

    /* Count distinct hazard categories */
    int danger_count =
        (result.high_temperature || result.extreme_temperature) +
        (result.high_gas || result.extreme_gas) +
        result.flame_detected;

    /* Determine alert level */
    if (result.flame_detected || danger_count >= 2) {
        result.level = ALERT_CRITICAL;
    } else if (danger_count == 1) {
        result.level = ALERT_WARNING;
    } else if (result.assessment_complete) {
        result.level = ALERT_NORMAL;
    }

    return result;
}
