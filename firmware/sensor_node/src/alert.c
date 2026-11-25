
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "sensor_data.h"
#include "alert_logic.h"
#include "config.h"

void alert_thread(void)
{
    struct sensor_data data;

    while (1) {
        if (k_msgq_get(&sensor_queue, &data, K_FOREVER) != 0) {
            continue;
        }

        bool dht_ok = (data.temperature != DHT_ERROR_VALUE);
        bool mq2_ok = (data.mq2_raw != MQ2_ERROR_VALUE);

        struct alert_result result = evaluate_alert(&data);

        const char *status;

        switch (result.level) {
        case ALERT_NORMAL:
            status = "NORMAL";
            break;
        case ALERT_WARNING:
            status = "WARNING";
            break;
        case ALERT_CRITICAL:
            status = "CRITICAL";
            break;
        default:
            status = "UNKNOWN";
            break;
        }

        const char *reason = "NONE";

        if (result.extreme_temperature) {
            reason = "EXTREME_TEMP";
        } else if (result.high_temperature) {
            reason = "HIGH_TEMP";
        }

        if (dht_ok && mq2_ok) {
            printk("T:%.2f H:%.2f G:%d S:%s R:%s\n",
                   data.temperature, data.humidity,
                   data.mq2_raw, status, reason);
        } else if (dht_ok) {
            printk("T:%.2f H:%.2f G:N/A S:%s R:%s\n",
                   data.temperature, data.humidity,
                   status, reason);
        } else if (mq2_ok) {
            printk("T:N/A H:N/A G:%d S:%s R:%s\n",
                   data.mq2_raw, status, reason);
        } else {
            printk("T:N/A H:N/A G:N/A S:%s R:%s\n",
                   status, reason);
        }
    }
}

K_THREAD_DEFINE(alert_tid, 1024, alert_thread,
                NULL, NULL, NULL, 5, 0, 0);
