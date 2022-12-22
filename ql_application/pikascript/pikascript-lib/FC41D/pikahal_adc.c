/*
 * SPDX-FileCopyrightText: 2022 Darren <1912544842@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "pika_hal.h"
#include "ql_adc.h"

static void ql_adc_callback(int new_mv, void* user_data) {
    int* data = (int*)user_data;
    *data = new_mv;
}

int pika_hal_platform_ADC_open(pika_dev* dev, char* name) {
    ql_adc_obj_s* platform_adc = pikaMalloc(sizeof(ql_adc_obj_s));
    int* user_data = pikaMalloc(sizeof(int));
    memset(platform_adc, 0, sizeof(ql_adc_obj_s));
    ql_adc_errcode_e err = ql_adc_channel_init(platform_adc, ql_adc_callback,
                                               fast_atoi(name), user_data);
    dev->platform_data = platform_adc;
    return -(int)err;
}

int pika_hal_platform_ADC_close(pika_dev* dev) {
    ql_adc_obj_s* platform_adc = (ql_adc_obj_s*)dev->platform_data;
    if (NULL != platform_adc->user_data) {
        pikaFree(platform_adc->user_data, sizeof(int));
    }
    if (NULL != platform_adc) {
        pikaFree(platform_adc, sizeof(ql_adc_obj_s));
    }
    return 0;
}

int pika_hal_platform_ADC_ioctl_config(pika_dev* dev,
                                       pika_hal_ADC_config* cfg) {
    /* Not support */
    return -1;
}

int pika_hal_platform_ADC_read(pika_dev* dev, void* buf, size_t count) {
    ql_adc_obj_s* platform_adc = (ql_adc_obj_s*)dev->platform_data;
    *(int*)buf = *(int*)platform_adc->user_data;
    return 0;
}

int pika_hal_platform_ADC_write(pika_dev* dev, void* buf, size_t count) {
    /* Not support */
    return -1;
}

int pika_hal_platform_ADC_ioctl_enable(pika_dev* dev) {
    ql_adc_obj_s* platform_adc = (ql_adc_obj_s*)dev->platform_data;
    ql_adc_errcode_e err = ql_adc_channel_start(platform_adc);
    return -(int)err;
}

int pika_hal_platform_ADC_ioctl_disable(pika_dev* dev) {
    ql_adc_obj_s* platform_adc = (ql_adc_obj_s*)dev->platform_data;
    ql_adc_errcode_e err = ql_adc_channel_stop(platform_adc);
    return -(int)err;
}