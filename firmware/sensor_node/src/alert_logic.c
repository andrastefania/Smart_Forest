
#include "alert_logic.h"

struct alert_result evaluate_alert(
    const struct alert_conditions *conditions)
{
    struct alert_result result = {
        .level = ALERT_UNKNOWN,
        .causes = *conditions
    };

    int danger_count =
        conditions->high_temperature +
        conditions->gas_detected +
        conditions->flame_detected;

    if (danger_count >= 2) {
        result.level = ALERT_CRITICAL;
    } else if (danger_count == 1) {
        result.level = ALERT_WARNING;
    } else if (conditions->assessment_complete) {
        result.level = ALERT_NORMAL;
    }

    return result;
}
