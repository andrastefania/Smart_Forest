
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "sensor_data.h"
#include "dht11_sensor.h"

K_MSGQ_DEFINE(sensor_queue, sizeof(struct sensor_data), 10, 4);

/* Thread 1: Sensor Monitoring */
void sensor_thread(void)
{
    struct sensor_data data;

    while (1) {
        int ret = dht11_read(&data);

        if (ret == 0) {
            if (k_msgq_put(&sensor_queue, &data, K_NO_WAIT) != 0) {
                printk("[Sensor] Queue full\n");
            }
        } else {
            printk("[Sensor] DHT11 read failed: %d\n", ret);
        }

        k_sleep(K_SECONDS(2));
    }
}

K_THREAD_DEFINE(sensor_tid, 2048, sensor_thread,
                NULL, NULL, NULL, 5, 0, 0);
