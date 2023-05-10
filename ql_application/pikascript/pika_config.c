/*
 * SPDX-FileCopyrightText: 2022 Darren <1912544842@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "pika_config.h"

int pika_platform_putchar(char ch) {
    unsigned char str[1] = {(unsigned char)ch};
    return ql_uart_write(QL_UART_PORT_2, str, 1);
}

void* pika_platform_malloc(size_t size) {
    return os_malloc(size);
}

void* pika_platform_realloc(void* ptr, size_t size) {
    return os_realloc(ptr, size);
}

void* pika_platform_calloc(size_t num, size_t size) {
    return os_calloc(num, size);
}

void pika_platform_free(void* ptr) {
    os_free(ptr);
}

void* pika_platform_memset(void* mem, int ch, size_t size) {
    return os_memset(mem, ch, size);
}

void* pika_platform_memcpy(void* dir, const void* src, size_t size) {
    return os_memcpy(dir, src, size);
}

int pika_platform_memcmp(const void* s1, const void* s2, size_t n) {
    return os_memcmp(s1, s2, n);
}

void* pika_platform_memmove(void* s1, void* s2, size_t n) {
    return os_memmove(s1, s2, n);
}

void pika_platform_disable_irq_handle(void) {
    ql_rtos_exit_critical();
}

void pika_platform_enable_irq_handle(void) {
    ql_rtos_enter_critical();
}

char pika_platform_getchar() {
    char buff[1] = {0};
    int err = -1;
    while (err != 0) {
        err = ql_uart_read(QL_UART_PORT_2, (unsigned char*)buff, 1);
        vTaskDelay(1);
    }
    return buff[0];
}
