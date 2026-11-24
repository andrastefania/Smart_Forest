
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

#define DHT_NODE DT_ALIAS(dht0)

int main(void)
{
    const struct device *dht = DEVICE_DT_GET(DHT_NODE);
    struct sensor_value temperature;
    struct sensor_value humidity;

    if (!device_is_ready(dht)) {
        printk("DHT11 not ready\n");
        return 0;
    }

    while (1) {
        int ret = sensor_sample_fetch(dht);

        if (ret == 0) {
            sensor_channel_get(dht, SENSOR_CHAN_AMBIENT_TEMP,
                               &temperature);
            sensor_channel_get(dht, SENSOR_CHAN_HUMIDITY,
                               &humidity);

            printk("Temperature: %d C | Humidity: %d %%\n",
                   temperature.val1, humidity.val1);
        } else {
            printk("DHT11 read failed: %d\n", ret);
        }

        k_sleep(K_SECONDS(2));
    }
}
