#ifndef __PIKA_CONFIG__H
#define __PIKA_CONFIG__H

#include "PikaPlatform.h"
#include "mem_pub.h"
#include "ql_uart.h"
#include "stdarg.h"
#include "stdio.h"
#include "uart_pub.h"

#define __platform_printf(...) os_printf(__VA_ARGS__)

#endif