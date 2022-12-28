/*
 * SPDX-FileCopyrightText: 2022 Darren <1912544842@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "common.h"
#include "error.h"
#include "include.h"
#include "ql_api_osi.h"
#include "ql_gpio.h"
#include "ql_adc.h"
#include "ql_wlan.h"
#include "rtos_pub.h"
#include "uart_pub.h"
#include "pikascript.h"

typedef struct fc41d_port {
    uint8_t id;
    char* name;
    ql_gpio_num_e num;
} fc41d_port_t;

static fc41d_port_t led[] = {
    {1, "GPIO1", QL_GPIO22}, {2, "GPIO2", QL_GPIO23}, {3, "GPIO3", QL_GPIO28},
    {4, "GPIO4", QL_GPIO24}, {5, "PWM1", QL_GPIO6},   {6, "PWM2", QL_GPIO7},
    {7, "PWM3", QL_GPIO8},   {8, "PWM4", QL_GPIO9},
};

static ql_sem_t wlan_ready_sem = NULL;
static ql_task_t pika_thread_handle = NULL;

static void wlan_status(ql_wlan_evt_type* ctxt) {
    ql_LinkStatusTypeDef_s linkStatus;
    os_memset(&linkStatus, 0x0, sizeof(LinkStatusTypeDef));
    os_printf("[wlan-debug]status change:%d\r\n", *ctxt);

    ql_wlan_get_link_status(&linkStatus);
    ql_wlan_log("[D]sta:rssi=%d,ssid=%s,bssid=" MACSTR
                ",channel=%d,cipher_type:",
                linkStatus.wifi_strength, linkStatus.ssid,
                MAC2STR(linkStatus.bssid), linkStatus.channel);
    if (*ctxt == QL_WLAN_EVT_STA_GOT_IP) {
        ql_rtos_semaphore_release(wlan_ready_sem);
    }
}

static void pika_thread() {
    os_printf("pika_thread entry\r\n");
    ql_adc_thread_init();
    ql_network_InitTypeDef_s wNetConfig;

    os_memset(&wNetConfig, 0x0, sizeof(network_InitTypeDef_st));

    os_strcpy((char*)wNetConfig.wifi_ssid, "AR300M-NOR");
    os_strcpy((char*)wNetConfig.wifi_key, "goodlife");
    wNetConfig.wifi_mode = QL_STATION;
    wNetConfig.dhcp_mode = DHCP_CLIENT;
    wNetConfig.wifi_retry_interval = 100;

    os_printf("[D]ssid:%s key:%s\r\n", wNetConfig.wifi_ssid,
              wNetConfig.wifi_key);

    ql_wlan_status_register_cb(wlan_status);
    ql_wlan_start(&wNetConfig);

    if (wlan_ready_sem) {
        ql_rtos_semaphore_wait(wlan_ready_sem, BEKEN_WAIT_FOREVER);
        os_printf("[wifi-debug]connect ok and got ip \r\n");
        goto pika_run;
    } else {
        os_printf("[wifi-debug]sem error\r\n");
        goto exit;
    }

pika_run:
    os_printf("pika entry\r\n");

    uint64_t i = 1;
    os_printf("test uint64_t:%llu\r\n", i);
    os_printf("test uint64_t:%d\r\n", i);

    pikaScriptInit();

    os_printf("pika run end\r\n");
exit:
    while (1) {
        ql_rtos_task_sleep_ms(1000);
    }
}

void ql_demo_main() {
    int ret;
    os_printf("demo test start \n");

    ret = ql_rtos_semaphore_create(&wlan_ready_sem, 1);
    if (ret != kNoErr) {
        os_printf("[D]rtos_init_semaphore err:%d\r\n", ret);
        if (wlan_ready_sem != NULL) {
            ql_rtos_semaphore_delete(wlan_ready_sem);
        }
    }

    ret = ql_rtos_task_create(&pika_thread_handle, 8192,
                              THD_EXTENDED_APP_PRIORITY, "pikascript",
                              pika_thread, 0);

    if (ret != kNoErr) {
        os_printf("Error: Failed to create thread: %d\r\n", ret);
        if (pika_thread_handle != NULL) {
            ql_rtos_task_delete(pika_thread_handle);
        }
    }
}
