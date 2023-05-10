/*
 * SPDX-FileCopyrightText: 2023 Darren <1912544842@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "pika_hal.h"

#include "common.h"
#include "ql_wlan.h"

static volatile PIKA_BOOL wifi_started = PIKA_FALSE;
static volatile PIKA_BOOL wifi_sta_connected = PIKA_FALSE;
static volatile PIKA_HAL_WIFI_STATUS wifi_sta_disconn_reason =
    PIKA_HAL_WIFI_STATUS_IDLE;
static volatile ql_wlanInterface_Typedef_e wlan_mode = QL_STATION;
static ql_network_InitTypeDef_s wifi_config = {0};

static void wlan_status_cb(ql_wlan_evt_type* ctxt) {
    switch (*ctxt) {
        case QL_WLAN_EVT_STA_IDLE:
            wifi_sta_disconn_reason = PIKA_HAL_WIFI_STATUS_IDLE;
            break;
        case QL_WLAN_EVT_STA_CONNECTED:
            wifi_sta_disconn_reason = PIKA_HAL_WIFI_STATUS_CONNECTING;
            break;
        case QL_WLAN_EVT_STA_CONNECT_FAILED:
            wifi_sta_disconn_reason = PIKA_HAL_WIFI_STATUS_CONNECT_FAIL;
            break;
        case QL_WLAN_EVT_STA_NO_AP_FOUND:
            wifi_sta_disconn_reason = PIKA_HAL_WIFI_STATUS_NO_AP_FOUND;
            break;
        case QL_WLAN_EVT_STA_DISCONNECTED:
            wifi_sta_connected = PIKA_FALSE;
            break;
        case QL_WLAN_EVT_STA_GOT_IP:
            wifi_sta_disconn_reason = PIKA_HAL_WIFI_STATUS_GOT_IP;
            wifi_sta_connected = PIKA_TRUE;
            break;
        case QL_WLAN_EVT_AP_CONNECTED:
            break;
        case QL_WLAN_EVT_AP_DISCONNECTED:
            break;
        default:
            break;
    }
}

int pika_hal_platform_WIFI_open(pika_dev* dev, char* name) {
    return 0;
}

int pika_hal_platform_WIFI_close(pika_dev* dev) {
    return 0;
}

int pika_hal_platform_WIFI_ioctl_config(pika_dev* dev,
                                        pika_hal_WIFI_config* cfg) {
    if (!wifi_started) {
        return 0;
    }

    switch (cfg->mode) {
        case PIKA_HAL_WIFI_MODE_STA:
            pika_platform_printf("Error: STA mode not support config\r\n");
            return -1;
        case PIKA_HAL_WIFI_MODE_AP:
            pika_platform_printf("Error: AP mode not support config\r\n");
            return -1;
        default:
            pika_platform_printf("Error: unknow mode config:%d\r\n", cfg->mode);
            return -1;
    }
}

int pika_hal_platform_WIFI_ioctl_enable(pika_dev* dev) {
    pika_hal_WIFI_config* cfg = (pika_hal_WIFI_config*)dev->ioctl_config;
    if (cfg->mode == PIKA_HAL_WIFI_MODE_STA) {
        wlan_mode = QL_STATION;
    } else if (cfg->mode == PIKA_HAL_WIFI_MODE_AP) {
        wlan_mode = QL_SOFT_AP;
    } else {
        pika_platform_printf("Error: unknow mode enable:%d\r\n", cfg->mode);
        return -1;
    }
    return ql_wlan_status_register_cb(wlan_status_cb);
}

int pika_hal_platform_WIFI_ioctl_disable(pika_dev* dev) {
    if (wifi_started) {
        int err = ql_wlan_stop(wlan_mode);
        if (err != 0) {
            pika_platform_printf("Error: wifi stop errcode:%d\r\n", err);
            return -1;
        }
        wifi_started = PIKA_FALSE;
        return 0;
    } else {
        return -1;
    }
}

int pika_hal_platform_WIFI_ioctl_others(pika_dev* dev,
                                        PIKA_HAL_IOCTL_CMD cmd,
                                        void* arg) {
    if (cmd == PIKA_HAL_IOCTL_WIFI_GET_STATUS) {
        *(PIKA_HAL_WIFI_STATUS*)arg = wifi_sta_disconn_reason;
        return 0;
    }
    if (cmd == PIKA_HAL_IOCTL_WIFI_GET_ACTIVE) {
        *(int*)arg = wifi_started;
        return 0;
    }
    if (cmd == PIKA_HAL_IOCTL_WIFI_SCAN) {
        return -1;
    }
    if (cmd == PIKA_HAL_IOCTL_WIFI_CONNECT) {
        pika_hal_WIFI_connect_config* conncfg =
            (pika_hal_WIFI_connect_config*)arg;

        if (os_strlen(conncfg->ssid) > SSID_MAX_LEN) {
            pika_platform_printf("Error: SSID LEN > 32\r\n");
            return -1;
        }
        os_strcpy((char*)wifi_config.wifi_ssid, conncfg->ssid);
        os_strcpy((char*)wifi_config.wifi_key, conncfg->password);
        wifi_config.wifi_mode = QL_STATION;
        wifi_config.dhcp_mode = DHCP_CLIENT;
        wifi_config.wifi_retry_interval = 100;
        if (ql_wlan_start(&wifi_config) == 0) {
            wifi_started = PIKA_TRUE;
            return 0;
        } else {
            return -1;
        }
    }
    if (cmd == PIKA_HAL_IOCTL_WIFI_GET_IFCONFIG) {
        pika_hal_WIFI_ifconfig* hal_if = (pika_hal_WIFI_ifconfig*)arg;
        ql_IPStatusTypedef_s ip_status = {0};
        int err = ql_wlan_get_ip_status(&ip_status, wlan_mode);
        if (err == 0) {
            os_memcpy(hal_if->ip, ip_status.ip, 16);
            os_memcpy(hal_if->gateway, ip_status.gate, 16);
            os_memcpy(hal_if->netmask, ip_status.mask, 16);
            os_memcpy(hal_if->dns, ip_status.dns, 16);
            return 0;
        } else {
            return -1;
        }
    }
    if (cmd == PIKA_HAL_IOCTL_WIFI_SET_IFCONFIG) {
        pika_hal_WIFI_ifconfig* hal_if = (pika_hal_WIFI_ifconfig*)arg;
        os_memcpy(wifi_config.local_ip_addr, hal_if->ip, 16);
        os_memcpy(wifi_config.gateway_ip_addr, hal_if->gateway, 16);
        os_memcpy(wifi_config.net_mask, hal_if->netmask, 16);
        os_memcpy(wifi_config.dns_server_ip_addr, hal_if->dns, 16);
        return 0;
    }
    return -1;
}
