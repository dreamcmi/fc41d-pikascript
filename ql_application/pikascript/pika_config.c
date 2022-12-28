/*
 * SPDX-FileCopyrightText: 2022 Darren <1912544842@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "pika_config.h"

// int __platform_vsnprintf(char* buff,
//                          size_t size,
//                          const char* fmt,
//                          va_list args) {
//     return vsnprintf(buff, size, fmt, args);
// }

// int __platform_sprintf(char* buff, char* fmt, ...) {
//     va_list args;
//     va_start(args, fmt);
//     int res = vsnprintf(buff, PIKA_SPRINTF_BUFF_SIZE, fmt, args);
//     va_end(args);
//     return res;
// }

int __platform_putchar(char ch) {
    unsigned char str[1] = {0};
    str[0] = ch;
    ql_uart_write(QL_UART_PORT_2, str, 1);
}


void __platform_sleep_ms(uint32_t ms) {
    ql_rtos_task_sleep_ms((uint32_t)ms);
}

void __platform_sleep_s(uint32_t s) {
    ql_rtos_task_sleep_s((uint32_t)s);
}

int64_t __platform_getTick(void) {
    return (int64_t)ql_rtos_up_time_ms();
}

void* __platform_malloc(size_t size) {
    return os_malloc(size);
}

void* __platform_realloc(void* ptr, size_t size) {
    return os_realloc(ptr, size);
}

void* __platform_calloc(size_t num, size_t size) {
    return os_calloc(num, size);
}

void __platform_free(void* ptr) {
    os_free(ptr);
}

void* __platform_memset(void* mem, int ch, size_t size) {
    return os_memset(mem, ch, size);
}

void* __platform_memcpy(void* dir, const void* src, size_t size) {
    return os_memcpy(dir, src, size);
}

int __platform_memcmp(const void* s1, const void* s2, size_t n) {
    return os_memcmp(s1, s2, n);
}

void* __platform_memmove(void* s1, void* s2, size_t n) {
    return os_memmove(s1, s2, n);
}

void __platform_disable_irq_handle(void) {
    ql_rtos_exit_critical();
}

void __platform_enable_irq_handle(void) {
    ql_rtos_enter_critical();
}

char __platform_getchar(void) {
    unsigned char buff[1] = {0};
    ql_uart_read(QL_UART_PORT_2, buff, 1);
    return *buff;
}
