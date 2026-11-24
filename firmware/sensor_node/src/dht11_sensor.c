
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <errno.h>

#include "dht11_sensor.h"

#define DHT_NODE DT_ALIAS(dht0)

int dht11_read(struct sensor_data *data)
{
    const struct device *dht = DEVICE_DT_GET(DHT_NODE);
    struct sensor_value temp, hum;

    if (!device_is_ready(dht)) {
        return -ENODEV;
    }

    int ret = sensor_sample_fetch(dht);
    if (ret != 0) {
        return ret;
    }

    ret = sensor_channel_get(dht, SENSOR_CHAN_AMBIENT_TEMP, &temp);
    if (ret != 0) {
        return ret;
    }

    ret = sensor_channel_get(dht, SENSOR_CHAN_HUMIDITY, &hum);
    if (ret != 0) {
        return ret;
    }

    data->temperature = temp.val1+temp.val2 / 1000000.0;
    data->humidity = hum.val1+hum.val2 / 1000000.0;

    return 0;
}
