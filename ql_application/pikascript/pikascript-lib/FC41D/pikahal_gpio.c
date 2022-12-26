/*
 * SPDX-FileCopyrightText: 2022 Darren <1912544842@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "pika_hal.h"
#include "ql_gpio.h"

typedef struct pika_hal_fc_gpio {
    ql_gpio_num_e port;
    ql_gpio_mode_e mode;
} pika_hal_fc_gpio_t;

static void _fc_gpio_irq(void* arg);

int pika_hal_platform_GPIO_open(pika_dev* dev, char* name) {
    dev->platform_data = pikaMalloc(sizeof(pika_hal_fc_gpio_t));
    memset(dev->platform_data, 0, sizeof(pika_hal_fc_gpio_t));
    pika_hal_fc_gpio_t* platform_gpio = (pika_hal_fc_gpio_t*)dev->platform_data;
    platform_gpio->port = fast_atoi(name);
    // __platform_printf("gpio open:%d\r\n", platform_gpio->port);
    return 0;
}

int pika_hal_platform_GPIO_close(pika_dev* dev) {
    pikaFree(dev->platform_data, sizeof(pika_hal_fc_gpio_t));
    return 0;
}

int pika_hal_platform_GPIO_read(pika_dev* dev, void* buf, size_t count) {
    uint8_t value = 0;
    pika_hal_fc_gpio_t* platform_gpio = (pika_hal_fc_gpio_t*)dev->platform_data;
    ql_gpio_get_level(platform_gpio->port, &value);
    memcpy(buf, &value, sizeof(value));
    return 0;
}

int pika_hal_platform_GPIO_write(pika_dev* dev, void* buf, size_t count) {
    pika_hal_fc_gpio_t* platform_gpio = (pika_hal_fc_gpio_t*)dev->platform_data;
    uint32_t value_out = 0;
    memcpy(&value_out, buf, sizeof(value_out));
    // __platform_printf("write value:%d\r\n", value_out);
    ql_gpio_set_level(platform_gpio->port, value_out);
    return 0;
}

int pika_hal_platform_GPIO_ioctl_enable(pika_dev* dev) {
    pika_hal_fc_gpio_t* platform_gpio = (pika_hal_fc_gpio_t*)dev->platform_data;
    // __platform_printf("gpio enable:%d %d\r\n", platform_gpio->port,
    //                   platform_gpio->mode);
    ql_gpio_init(platform_gpio->port, platform_gpio->mode);
    return 0;
}

int pika_hal_platform_GPIO_ioctl_disable(pika_dev* dev) {
    pika_hal_fc_gpio_t* platform_gpio = (pika_hal_fc_gpio_t*)dev->platform_data;
    ql_gpio_deinit(platform_gpio->port);
    return 0;
}

int pika_hal_platform_GPIO_ioctl_config(pika_dev* dev,
                                        pika_hal_GPIO_config* cfg) {
    pika_hal_fc_gpio_t* platform_gpio = (pika_hal_fc_gpio_t*)dev->platform_data;
    switch (cfg->dir) {
        case PIKA_HAL_GPIO_DIR_OUT:
            switch (cfg->pull) {
                case PIKA_HAL_GPIO_PULL_NONE:
                    platform_gpio->mode = QL_GMODE_OUTPUT;
                    break;
                case PIKA_HAL_GPIO_PULL_UP:
                    platform_gpio->mode = QL_GMODE_OUTPUT_PULLUP;
                    break;
                case PIKA_HAL_GPIO_PULL_DOWN:
                    platform_gpio->mode = QL_GMODE_OUTPUT;
                    __platform_printf("[W]not support OUTPUT_PULL_DOWN\r\n");
                    break;
                default:
                    return -1;
                    break;
            }
            break;
        case PIKA_HAL_GPIO_DIR_IN:
            switch (cfg->pull) {
                case PIKA_HAL_GPIO_PULL_NONE:
                    platform_gpio->mode = QL_GMODE_INPUT;
                    break;
                case PIKA_HAL_GPIO_PULL_UP:
                    platform_gpio->mode = QL_GMODE_INPUT_PULLUP;
                    break;
                case PIKA_HAL_GPIO_PULL_DOWN:
                    platform_gpio->mode = QL_GMODE_INPUT_PULLDOWN;
                    break;
                default:
                    return -1;
            }
        default:
            return -1;
    }
    if (NULL != cfg->event_callback &&
        PIKA_HAL_EVENT_CALLBACK_ENA_ENABLE == cfg->event_callback_ena) {
        switch (cfg->event_callback_filter) {
            case PIKA_HAL_GPIO_EVENT_SIGNAL_RISING:
                ql_gpio_int_init(platform_gpio->port,
                                 QL_IRQ_TRIGGER_RISING_EDGE, _fc_gpio_irq);
                break;
            case PIKA_HAL_GPIO_EVENT_SIGNAL_FALLING:
                ql_gpio_int_init(platform_gpio->port,
                                 QL_IRQ_TRIGGER_FALLING_EDGE, _fc_gpio_irq);
                break;
            default:
                __platform_printf(
                    "Error: not supported event callback filter %d\r\n",
                    cfg->event_callback_filter);
                return -1;
        }
    }
    return 0;
}

static void _fc_gpio_irq(void* arg) {}
