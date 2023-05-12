/*
 * SPDX-FileCopyrightText: 2022 Darren <1912544842@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "common.h"
#include "error.h"
#include "include.h"
#include "lfs_port.h"
#include "pikascript.h"
#include "ql_adc.h"
#include "ql_api_osi.h"
#include "ql_gpio.h"
#include "ql_uart.h"
#include "ql_wlan.h"
#include "rtos_pub.h"
#include "uart_pub.h"

// typedef struct fc41d_port {
//     uint8_t id;
//     char* name;
//     ql_gpio_num_e num;
// } fc41d_port_t;

// static fc41d_port_t led[] = {
//     {1, "GPIO1", QL_GPIO22}, {2, "GPIO2", QL_GPIO23}, {3, "GPIO3",
//     QL_GPIO28}, {4, "GPIO4", QL_GPIO24}, {5, "PWM1", QL_GPIO6},   {6, "PWM2",
//     QL_GPIO7}, {7, "PWM3", QL_GPIO8},   {8, "PWM4", QL_GPIO9},
// };

static ql_task_t pika_thread_handle = NULL;

static void pika_thread() {
    os_printf("pika_thread entry\r\n");
    ql_adc_thread_init();

    int err = lfs_ll_mount();
    os_printf("lfs mount:%d\r\n", err);

    lfs_file_t file;
    char lines[] = {"print(\"hello from test.py\")\n"};
    lfs_file_open(&lfs_flash, &file, "test.py", LFS_O_RDWR | LFS_O_CREAT);
    lfs_file_rewind(&lfs_flash, &file);
    lfs_file_write(&lfs_flash, &file, lines, sizeof(lines));
    lfs_file_close(&lfs_flash, &file);

    os_printf("pika entry\r\n");

    // pikaScriptShell(pikaScriptInit());

    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    extern unsigned char pikaModules_py_a[];
    obj_linkLibrary(pikaMain, pikaModules_py_a);
    pikaScriptShell(pikaMain);
    obj_deinit(pikaMain);
    os_printf("pika run end\r\n");

    while (1) {
        ql_rtos_task_sleep_ms(1000);
    }
}

void ql_demo_main() {
    int ret;
    os_printf("demo test start \n");

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
