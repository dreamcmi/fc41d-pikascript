/*
 * SPDX-FileCopyrightText: 2022 Darren <1912544842@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "pika_hal.h"
#include "ql_spi.h"

int pika_hal_platform_SPI_open(pika_dev* dev, char* name) {
    ql_spi_config_s* platform_spi = pikaMalloc(sizeof(ql_spi_config_s));
    memset(platform_spi, 0, sizeof(ql_spi_config_s));
    dev->platform_data = platform_spi;
    if (name[0] == 'S' && name[1] == 'P' && name[2] == 'I' && name[3] == '1') {
        return 0;
    } else {
        return -1;
    }
}

int pika_hal_platform_SPI_close(pika_dev* dev) {
    ql_spi_config_s* platform_spi = (ql_spi_config_s*)dev->platform_data;
    if (NULL != platform_spi) {
        pikaFree(platform_spi, sizeof(ql_spi_config_s));
    }
    return 0;
}

int pika_hal_platform_SPI_ioctl_config(pika_dev* dev,
                                       pika_hal_SPI_config* cfg) {
    ql_spi_config_s* platform_spi = (ql_spi_config_s*)dev->platform_data;
    switch (cfg->master_or_slave) {
        case PIKA_HAL_SPI_MASTER:
            platform_spi->masterorslave = QL_SPI_MASTER;
            break;
        case PIKA_HAL_SPI_SLAVE:
            platform_spi->masterorslave = QL_SPI_SLAVE;
            break;
        default:
            return -1;
            break;
    }
    switch (cfg->lsb_or_msb) {
        case PIKA_HAL_SPI_MSB:
            platform_spi->transmode = QL_SPI_MSB;
            break;
        case PIKA_HAL_SPI_LSB:
            platform_spi->transmode = QL_SPI_LSB;
            break;
        default:
            return -1;
            break;
    }
    switch (cfg->mode) {
        case PIKA_HAL_SPI_MODE_0:
            platform_spi->cpol = QL_SPI_CPOL_LOW;
            platform_spi->cpha = QL_SPI_CPHA_1Edge;

            break;
        case PIKA_HAL_SPI_MODE_1:
            platform_spi->cpol = QL_SPI_CPOL_LOW;
            platform_spi->cpha = QL_SPI_CPHA_2Edge;

            break;
        case PIKA_HAL_SPI_MODE_2:
            platform_spi->cpol = QL_SPI_CPOL_HIGH;
            platform_spi->cpha = QL_SPI_CPHA_1Edge;

            break;
        case PIKA_HAL_SPI_MODE_3:
            platform_spi->cpol = QL_SPI_CPOL_HIGH;
            platform_spi->cpha = QL_SPI_CPHA_2Edge;
            break;
        default:
            return -1;
            break;
    }
    platform_spi->spiclk = cfg->speed;
    return 0;
}

int pika_hal_platform_SPI_ioctl_enable(pika_dev* dev) {
    ql_spi_config_s* platform_spi = (ql_spi_config_s*)dev->platform_data;
    ql_spi_messag_s spi_msg;
    spi_msg.recv_buf = NULL;
    spi_msg.recv_len = 0;
    spi_msg.send_buf = NULL;
    spi_msg.send_len = 0;
    ql_spi_errcode_e err = ql_spi_init(*platform_spi, &spi_msg);
    return -(int)err;
}

int pika_hal_platform_SPI_ioctl_disable(pika_dev* dev) {
    // ql_spi_config_s* platform_spi = (ql_spi_config_s*)dev->platform_data;
    return -1;
}

int pika_hal_platform_SPI_write(pika_dev* dev, void* buf, size_t count) {
    // ql_spi_config_s* platform_spi = (ql_spi_config_s*)dev->platform_data;
    ql_spi_messag_s spi_msg;
    spi_msg.recv_buf = NULL;
    spi_msg.recv_len = 0;
    spi_msg.send_buf = (uint8_t*)buf;
    spi_msg.send_len = (uint32_t)count;
    ql_spi_errcode_e err = ql_spi_transfer(&spi_msg);
    return -(int)err;
}

int pika_hal_platform_SPI_read(pika_dev* dev, void* buf, size_t count) {
    // ql_spi_config_s* platform_spi = (ql_spi_config_s*)dev->platform_data;
    ql_spi_messag_s spi_msg;
    spi_msg.recv_buf = (uint8_t*)buf;
    spi_msg.recv_len = (uint32_t)count;
    spi_msg.send_buf = NULL;
    spi_msg.send_len = 0;
    ql_spi_errcode_e err = ql_spi_transfer(&spi_msg);
    return -(int)err;
}