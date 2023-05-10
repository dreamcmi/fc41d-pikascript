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

static void wlan_status(ql_wlan_evt_type* ctxt) {
    ql_LinkStatusTypeDef_s linkStatus = {0};
    switch (*ctxt) {
        case QL_WLAN_EVT_STA_IDLE:
            wifi_sta_disconn_reason = PIKA_HAL_WIFI_STATUS_IDLE;
            break;
        case QL_WLAN_EVT_STA_CONNECTED:
            wifi_sta_disconn_reason = PIKA_HAL_WIFI_STATUS_CONNECTING;
            ql_wlan_get_link_status(&linkStatus);
            ql_wlan_log("[D]sta:rssi=%d,ssid=%s,bssid=" MACSTR
                        ",channel=%d,cipher_type:",
                        linkStatus.wifi_strength, linkStatus.ssid,
                        MAC2STR(linkStatus.bssid), linkStatus.channel);
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

    pika_debug("regist event handler");
    return ql_wlan_status_register_cb(wlan_status);
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
    }
    return -1;
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
        ql_network_InitTypeDef_s wNetConfig = {0};
        pika_hal_WIFI_connect_config* conncfg =
            (pika_hal_WIFI_connect_config*)arg;

        os_strcpy((char*)wNetConfig.wifi_ssid, conncfg->ssid);
        os_strcpy((char*)wNetConfig.wifi_key, conncfg->password);
        wNetConfig.wifi_mode = QL_STATION;
        wNetConfig.dhcp_mode = DHCP_CLIENT;
        wNetConfig.wifi_retry_interval = 100;
        if (ql_wlan_start(&wNetConfig) == 0) {
            wifi_started = PIKA_TRUE;
            return 0;
        }
        return -1;
    }
    if (cmd == PIKA_HAL_IOCTL_WIFI_GET_IFCONFIG) {
        return -1;
    }
    if (cmd == PIKA_HAL_IOCTL_WIFI_SET_IFCONFIG) {
        return -1;
    }
    return -1;
}