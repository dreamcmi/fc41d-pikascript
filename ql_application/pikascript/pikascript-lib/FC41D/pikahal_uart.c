/*
 * SPDX-FileCopyrightText: 2022 Darren <1912544842@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "pika_hal.h"
#include "ql_uart.h"

typedef struct pika_hal_fc_uart {
    ql_uart_port_number_e port;
    ql_uart_config_s config;
} pika_hal_fc_uart_t;

int pika_hal_platform_UART_open(pika_dev* dev, char* name) {
    dev->platform_data = pikaMalloc(sizeof(pika_hal_fc_uart_t));
    memset(dev->platform_data, 0, sizeof(pika_hal_fc_uart_t));
    pika_hal_fc_uart_t* platform_uart = (pika_hal_fc_uart_t*)dev->platform_data;
    if (name[0] == 'U' && name[1] == 'A' && name[2] == 'R' && name[3] =='T') {
        platform_uart->port = fast_atoi(name + 4);
        return 0;
    } else {
        return -1;
    }
}

int pika_hal_platform_UART_close(pika_dev* dev) {
    pikaFree(dev->platform_data, sizeof(pika_hal_fc_uart_t));
    return 0;
}

int pika_hal_platform_UART_read(pika_dev* dev, void* buf, size_t count) {
    pika_hal_fc_uart_t* platform_uart = (pika_hal_fc_uart_t*)dev->platform_data;
    int err = ql_uart_read(platform_uart->port, (unsigned char*)buf, count);
    return -err;
}

int pika_hal_platform_UART_write(pika_dev* dev, void* buf, size_t count) {
    pika_hal_fc_uart_t* platform_uart = (pika_hal_fc_uart_t*)dev->platform_data;
    int err = ql_uart_write(platform_uart->port, (unsigned char*)buf, count);
    return -err;
}

int pika_hal_platform_UART_ioctl_enable(pika_dev* dev) {
    pika_hal_fc_uart_t* platform_uart = (pika_hal_fc_uart_t*)dev->platform_data;
    ql_uart_errcode_e err = ql_uart_open(platform_uart->port);
    return -(int)err;
}

int pika_hal_platform_UART_ioctl_disable(pika_dev* dev) {
    pika_hal_fc_uart_t* platform_uart = (pika_hal_fc_uart_t*)dev->platform_data;
    ql_uart_errcode_e err = ql_uart_close(platform_uart->port);
    return -(int)err;
}

int pika_hal_platform_UART_ioctl_config(pika_dev* dev,
                                        pika_hal_UART_config* cfg) {
    pika_hal_fc_uart_t* platform_uart = (pika_hal_fc_uart_t*)dev->platform_data;
    platform_uart->config.baudrate = cfg->baudrate;
    
    switch (cfg->data_bits) {
        case PIKA_HAL_UART_DATA_BITS_5:
            platform_uart->config.data_bit = QL_UART_DATABIT_5;
            break;
        case PIKA_HAL_UART_DATA_BITS_6:
            platform_uart->config.data_bit = QL_UART_DATABIT_6;
            break;
        case PIKA_HAL_UART_DATA_BITS_7:
            platform_uart->config.data_bit = QL_UART_DATABIT_7;
            break;
        case PIKA_HAL_UART_DATA_BITS_8:
            platform_uart->config.data_bit = QL_UART_DATABIT_8;
            break;
        default:
            return -1;
            break;
    }

    switch (cfg->parity) {
        case PIKA_HAL_UART_PARITY_NONE:
            platform_uart->config.parity_bit = QL_UART_PARITY_NONE;
            break;
        case PIKA_HAL_UART_PARITY_ODD:
            platform_uart->config.parity_bit = QL_UART_PARITY_ODD;
            break;
        case PIKA_HAL_UART_PARITY_EVEN:
            platform_uart->config.parity_bit = QL_UART_PARITY_EVEN;
            break;
        default:
            return -1;
            break;
    }

    switch (cfg->stop_bits) {
        case PIKA_HAL_UART_STOP_BITS_1:
            platform_uart->config.stop_bit = QL_UART_STOP_1;
            break;
        case PIKA_HAL_UART_STOP_BITS_2:
            platform_uart->config.stop_bit = QL_UART_STOP_2;
            break;
        default:
            return -1;
            break;
    }

    return 0;
}
