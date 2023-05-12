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
        if (err == 0) {
            return buff[0];
        }
        vTaskDelay(1);
    }
    // return buff[0];
}

static int __lfs_fmodeflags(const char* mode) {
    int flags;
    if (strchr(mode, '+'))
        flags = LFS_O_RDWR;
    else if (*mode == 'r')
        flags = LFS_O_RDONLY;
    else
        flags = LFS_O_WRONLY;
    if (*mode == 'w')
        flags |= LFS_O_TRUNC;
    if (*mode == 'a')
        flags |= LFS_O_APPEND;
    return flags;
}

FILE* pika_platform_fopen(const char* filename, const char* modes) {
    lfs_file_t* _pika_lfs_file = os_malloc(sizeof(lfs_file_t));
    int mode = __lfs_fmodeflags(modes);
    if (lfs_file_open(&lfs_flash, _pika_lfs_file, filename, mode) ==
        LFS_ERR_OK) {
        return (FILE*)_pika_lfs_file;
    } else {
        os_free(_pika_lfs_file);
        return NULL;
    }
}

int pika_platform_fclose(FILE* stream) {
    if (lfs_file_close(&lfs_flash, (lfs_file_t*)stream) == LFS_ERR_OK) {
        os_free(stream);
        return 0;
    } else {
        return -1;
    }
}

size_t pika_platform_fwrite(const void* ptr,
                            size_t size,
                            size_t n,
                            FILE* stream) {
    return (size_t)lfs_file_write(&lfs_flash, (lfs_file_t*)stream, ptr,
                                  (lfs_size_t)(size * n));
}

size_t pika_platform_fread(void* ptr, size_t size, size_t n, FILE* stream) {
    return (size_t)lfs_file_read(&lfs_flash, (lfs_file_t*)stream, ptr,
                                 (lfs_size_t)(size * n));
}

int pika_platform_fseek(FILE* stream, long offset, int whence) {
    return (int)lfs_file_seek(&lfs_flash, (lfs_file_t*)stream,
                              (lfs_soff_t)offset, whence);
}

long pika_platform_ftell(FILE* stream) {
    return (long)lfs_file_tell(&lfs_flash, (lfs_file_t*)stream);
}
