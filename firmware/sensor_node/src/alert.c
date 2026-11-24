
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "sensor_data.h"

#define WARNING_TEMP 35
#define CRITICAL_TEMP 55

void alert_thread(void)
{
    struct sensor_data data;
    const char *status;

    while (1) {
        if (k_msgq_get(&sensor_queue, &data, K_FOREVER) != 0) {
            continue;
        }

        if (data.temperature >= CRITICAL_TEMP) {
            status = "CRITICAL";
        } else if (data.temperature >= WARNING_TEMP) {
            status = "WARNING";
        } else {
            status = "NORMAL";
        }

        printk("Temperature: %.2f C | Humidity: %.2f %% | Status: %s\n",
               data.temperature, data.humidity, status);
    }
}

K_THREAD_DEFINE(alert_tid, 1024, alert_thread,
                NULL, NULL, NULL, 5, 0, 0);
