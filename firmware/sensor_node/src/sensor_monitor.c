
#include <zephyr/kernel.h>

#include "sensor_data.h"
#include "dht11_sensor.h"
#include "mq2_sensor.h"
#include "config.h"

K_MSGQ_DEFINE(sensor_queue, sizeof(struct sensor_data), 10, 4);

void sensor_thread(void)
{
    struct sensor_data data;
    bool mq2_ready = (mq2_init() == 0);

    while (1) {
        data.temperature = DHT_ERROR_VALUE;
        data.humidity = DHT_ERROR_VALUE;
        data.mq2_raw = MQ2_ERROR_VALUE;
        data.flame_detected= false;

        if (dht11_read(&data) != 0) {
            data.temperature = DHT_ERROR_VALUE;
            data.humidity = DHT_ERROR_VALUE;
        }

        if (mq2_ready) {
            if (mq2_read(&data.mq2_raw) != 0) {
                data.mq2_raw = MQ2_ERROR_VALUE;
            }
        }

        k_msgq_put(&sensor_queue, &data, K_NO_WAIT);

        k_sleep(K_SECONDS(SENSOR_INTERVAL_SECONDS));
    }
}

K_THREAD_DEFINE(sensor_tid, 2048, sensor_thread,
                NULL, NULL, NULL, 5, 0, 0);
