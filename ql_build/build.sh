#!/bin/bash

# Author：Zhang Yuan
# Copyright (c)
# Script follows here:


set -e
set -u

echo "Name:$0 PID:$$, SOC = BK7231N, starting ......"

echo "Copy system_config.h"

if [ -e "sys_config.h" ];then
    rm sys_config.h
    cp ../ql_kernel/app/config/sys_config_bk7231n.h sys_config.h
else
    cp ../ql_kernel/app/config/sys_config_bk7231n.h sys_config.h
fi

echo "Packager libs "

cd ../ql_kernel/lib
if [ ! -d "objs" ];then
    mkdir objs
else
    rm -fR objs
    mkdir objs
fi

cd ../../ql_build

# cp libble.a librf_use.a libuart_debug.a libcal.a librwnx.a librf_test.a libsensor.a objs
# cp libsupplicant.a objs
# cp ../driver/libdriver.a objs
# cp ../func/libfunc.a objs
# cp ../os/libos.a ../os/librtos.a objs
# cd objs
# arm-none-eabi-ar -x libble.a
# arm-none-eabi-ar -x libcal.a
# arm-none-eabi-ar -x librf_test.a
# arm-none-eabi-ar -x librf_use.a
# arm-none-eabi-ar -x librwnx.a
# arm-none-eabi-ar -x libsensor.a
# arm-none-eabi-ar -x libsupplicant.a
# arm-none-eabi-ar -x libuart_debug.a
# arm-none-eabi-ar -x libdriver.a
# arm-none-eabi-ar -x libfunc.a
# arm-none-eabi-ar -x libos.a
# arm-none-eabi-ar -x librtos.a
# arm-none-eabi-ar -rcs libsdk.a *.o
# cp libsdk.a ../


# cd ../../../ql_build
# make build dir to build project
if [ ! -d "build" ]; then
    mkdir build
else
    rm -fR build
    mkdir build
fi

echo "Enter build dir ......"
cd build
rm -fR *
echo "Enter ql_out dir, and remove files ......"
cd ../../ql_out
rm -fR *
cd -
echo "cmake build ......"
cmake -G Ninja ..
echo "make build ......"
ninja
echo "make install ...."
ninja install
cd ../

# packager release files
cd ../ql_tools/beken_packager
./beken_packager.bat
mv all_2M.1220.bin fc41d_bsp_app_uart_2M.1220.bin ../../ql_out
cd -

# echo "remove packager libs ......."
# cd ../ql_kernel/lib
# rm libsdk.a
# rm -r objs
# cd -
