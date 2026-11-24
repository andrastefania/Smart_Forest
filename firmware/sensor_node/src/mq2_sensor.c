
#include <zephyr/device.h>
#include <zephyr/drivers/adc.h>
#include <errno.h>

#include "mq2_sensor.h"

#define ADC_NODE DT_PATH(zephyr_user)

static const struct adc_dt_spec mq2_adc =
    ADC_DT_SPEC_GET_BY_IDX(ADC_NODE, 0);

int mq2_init(void)
{
    if (!adc_is_ready_dt(&mq2_adc)) {
        return -ENODEV;
    }

    return adc_channel_setup_dt(&mq2_adc);
}

int mq2_read(int *raw_value)
{
    int16_t sample = 0;

    struct adc_sequence sequence = {
        .buffer = &sample,
        .buffer_size = sizeof(sample),
    };

    int ret = adc_sequence_init_dt(&mq2_adc, &sequence);
    if (ret != 0) {
        return ret;
    }

    ret = adc_read_dt(&mq2_adc, &sequence);
    if (ret != 0) {
        return ret;
    }

    *raw_value = sample;

    return 0;
}
