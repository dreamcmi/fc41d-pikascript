/*
 * SPDX-FileCopyrightText: 2022 Darren <1912544842@qq.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "FC41D_Time.h"
#include "ql_api_osi.h"

void FC41D_Time_sleep_ms(PikaObj* self, int ms) {
    (void)self;
    ql_rtos_task_sleep_ms(ms);
}

void FC41D_Time_sleep_s(PikaObj* self, int s) {
    (void)self;
    ql_rtos_task_sleep_s(s);
}

void FC41D_Time_platformGetTick(PikaObj* self) {
    obj_setInt(self, "tick", ql_rtos_up_time_ms);
}