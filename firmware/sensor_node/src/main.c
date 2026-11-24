
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/sys/printk.h>

#define DHT_NODE DT_ALIAS(dht0)

#define WARNING_TEMP 35
#define CRITICAL_TEMP 55

struct sensor_data {
    int temperature;
    int humidity;
};

K_MSGQ_DEFINE(sensor_queue, sizeof(struct sensor_data), 10, 4);

/* Thread 1: Sensor Monitoring */
void sensor_thread(void)
{
    const struct device *dht = DEVICE_DT_GET(DHT_NODE);
    struct sensor_value temp, hum;
    struct sensor_data data;

    if (!device_is_ready(dht)) {
        printk("DHT11 not ready\n");
        return;
    }

    while (1) {
        if (sensor_sample_fetch(dht) == 0 &&
            sensor_channel_get(dht, SENSOR_CHAN_AMBIENT_TEMP, &temp) == 0 &&
            sensor_channel_get(dht, SENSOR_CHAN_HUMIDITY, &hum) == 0) {

            data.temperature = temp.val1;
            data.humidity = hum.val1;

            if (k_msgq_put(&sensor_queue, &data, K_NO_WAIT) != 0) {
                printk("[Sensor] Queue full\n");
            }
        } else {
            printk("[Sensor] DHT11 read failed\n");
        }

        k_sleep(K_SECONDS(2));
    }
}

/* Thread 2: Alert Processing */
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

        printk("Temperature: %d C | Humidity: %d %% | Status: %s\n",
               data.temperature, data.humidity, status);
    }
}

K_THREAD_DEFINE(sensor_tid, 2048, sensor_thread,
                NULL, NULL, NULL, 5, 0, 0);

K_THREAD_DEFINE(alert_tid, 1024, alert_thread,
                NULL, NULL, NULL, 5, 0, 0);

int main(void)
{
    printk("Smart Forest Monitoring started\n");
    return 0;
}
