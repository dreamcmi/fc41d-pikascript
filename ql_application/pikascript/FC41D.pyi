# SPDX-FileCopyrightText: 2022 Darren <1912544842@qq.com>
# SPDX-License-Identifier: Apache-2.0


from PikaObj import *
import PikaStdDevice
import PikaStdTask

class Time(PikaStdDevice.Time):
    # override
    def sleep_s(self, s: int):
        pass

    # override
    def sleep_ms(self, ms: int):
        pass

    # override
    def platformGetTick():
        pass
