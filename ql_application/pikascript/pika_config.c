/*
 * SPDX-FileCopyrightText: 2022 Darren <1912544842@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "pika_config.h"


int __platform_vsnprintf(char* buff,
                         size_t size,
                         const char* fmt,
                         va_list args) {
    return vsnprintf(buff, size, fmt, args);
}

int __platform_sprintf(char* buff, char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int res = vsnprintf(buff, PIKA_SPRINTF_BUFF_SIZE, fmt, args);
    va_end(args);
    return res;
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

char __platform_getchar(void) {
    char buff[1] = {0};
    ql_uart_read(QL_UART_PORT_2, buff, 1);
    return *buff;
}