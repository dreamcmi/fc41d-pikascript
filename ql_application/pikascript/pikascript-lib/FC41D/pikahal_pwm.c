/*
 * SPDX-FileCopyrightText: 2022 Darren <1912544842@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "pika_hal.h"
#include "ql_pwm.h"

typedef struct pika_hal_fc_pwm {
    ql_pwm_channel_e port;
    uint32_t period;
    uint32_t duty_cycle;
} pika_hal_fc_pwm_t;

int pika_hal_platform_PWM_open(pika_dev* dev, char* name) {
    dev->platform_data = pikaMalloc(sizeof(pika_hal_fc_pwm_t));
    memset(dev->platform_data, 0, sizeof(pika_hal_fc_pwm_t));
    pika_hal_fc_pwm_t* platform_pwm = (pika_hal_fc_pwm_t*)dev->platform_data;
    if (name[0] == 'P' && name[1] == 'W' && name[2] == 'M') {
        platform_pwm->port = fast_atoi(name + 3);
        return 0;
    } else {
        return -1;
    }
    return 0;
}

int pika_hal_platform_PWM_close(pika_dev* dev) {
    pikaFree(dev->platform_data, sizeof(pika_hal_fc_pwm_t));
    return 0;
}

int pika_hal_platform_PWM_read(pika_dev* dev, void* buf, size_t count) {
    /* not support */
    return -1;
}

int pika_hal_platform_PWM_write(pika_dev* dev, void* buf, size_t count) {
    /* not support */
    return -1;
}

int pika_hal_platform_PWM_ioctl_enable(pika_dev* dev) {
    ql_pwm_errcode_e err;
    pika_hal_fc_pwm_t* platform_pwm = (pika_hal_fc_pwm_t*)dev->platform_data;
    err = ql_pwmInit(platform_pwm->port, platform_pwm->period,
                     platform_pwm->duty_cycle);
    if (err == QL_PWM_SUCCESS) {
        err = ql_pwmInit_level(platform_pwm->port, QL_PWM_INIT_LEVEL_LOW);
        if (err == QL_PWM_SUCCESS) {
            err = ql_pwm_enable(platform_pwm->port);
            goto exit;
        } else {
            goto exit;
        }
    } else {
        goto exit;
    }
exit:
    return -(int)err;
}

int pika_hal_platform_PWM_ioctl_disable(pika_dev* dev) {
    pika_hal_fc_pwm_t* platform_pwm = (pika_hal_fc_pwm_t*)dev->platform_data;
    ql_pwm_errcode_e err = ql_pwm_disable(platform_pwm->port);
    return -(int)err;
}

int pika_hal_platform_PWM_ioctl_config(pika_dev* dev,
                                       pika_hal_PWM_config* cfg) {
    pika_hal_fc_pwm_t* platform_pwm = (pika_hal_fc_pwm_t*)dev->platform_data;
    platform_pwm->period = cfg->period;
    platform_pwm->duty_cycle = cfg->duty;
    return 0;
}
