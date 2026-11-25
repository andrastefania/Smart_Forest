
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
        bool flame_ok =
            (data.flame_detected != FLAME_ERROR_VALUE);
        
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

        /* Display sensor measurements */
        if (dht_ok) {
            printk("🌡️:%.2f 💧:%.2f ",
                   data.temperature, data.humidity);
        } else {
            printk("🌡️:N/A 💧:N/A ");
        }

        if (mq2_ok) {
            printk("💨:%d ", data.mq2_raw);
        } else {
            printk("💨:N/A ");
        }

        if (flame_ok) {
            printk("🔥:%d ", data.flame_detected);
        } else {
            printk("🔥:N/A ");
        }

        printk("S:%s R:", status);

        /* Display alert reasons */
        bool has_reason = false;

        if (result.extreme_temperature) {
            printk("EXTREME_TEMP");
            has_reason = true;
        } else if (result.high_temperature) {
            printk("HIGH_TEMP");
            has_reason = true;
        }

        if (result.extreme_gas) {
            printk("%sEXTREME_GAS", has_reason ? "," : "");
            has_reason = true;
        } else if (result.high_gas) {
            printk("%sHIGH_GAS", has_reason ? "," : "");
            has_reason = true;
        }

        if (result.flame_detected) {
            printk("%sFLAME", has_reason ? "," : "");
            has_reason = true;
        }

        if (!has_reason) {
            printk("NONE");
        }

        printk("\n");
    }
}

K_THREAD_DEFINE(alert_tid, 1024, alert_thread,
                NULL, NULL, NULL, 5, 0, 0);
