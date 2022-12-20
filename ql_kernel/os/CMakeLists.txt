cmake_minimum_required(VERSION 3.22)

# 检测操作系统哦
if(WIN32)
    message(STATUS "windows build .........")
elseif(UNIX)
    message(STATUS "Linux build ...........")
endif()

include(${CMAKE_CURRENT_LIST_DIR}/../../ql_build/toolchain_bk7231n.cmake)

set(ASM_OPTIONS "-g -marm -mthumb-interwork -mcpu=arm968e-s -march=armv5te -x assembler-with-cpp")
set(CMAKE_C_FLAGS "-g -DCFG_OS_FREERTOS=1 -DCFG_SOC_NAME=5 -DMG_ARCH=6 -DWIFI_BLE_COEXIST -mthumb -mcpu=arm968e-s -march=armv5te -mthumb-interwork -mlittle-endian -Os -std=c99 -ffunction-sections -Wall -Wno-format -Wno-unknown-pragmas -fsigned-char -fdata-sections -nostdlib -fno-strict-aliasing -fno-common")
set(CMAKE_CXX_FLAGS "-g -DCFG_OS_FREERTOS=1 -DWIFI_BLE_COEXIST -mthumb -mcpu=arm968e-s -march=armv5te -mthumb-interwork -mlittle-endian -Os -std=c99 -ffunction-sections -Wall -Wno-format -Wno-unknown-pragmas -fsigned-char -fdata-sections -nostdlib -fno-strict-aliasing -fno-common")
##############################################################################################
project(os VERSION 1.0.0)
# set language
enable_language(C CXX ASM)

add_definitions(-DSYS_CONFIG_FILE=<sys_config.h>)
add_definitions(-DMBEDTLS_CONFIG_FILE=<tls_config.h>)

list(APPEND include_files
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_build

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/os/include
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/os/FreeRTOSv9.0.0
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/os/FreeRTOSv9.0.0/Source/include
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/os/FreeRTOSv9.0.0/Source/portable/Keil/ARM968es

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_compoents/quectel_api/include

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_compoents/paho-mqtt/client
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_compoents/paho-mqtt/client/src
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_compoents/paho-mqtt/packet/src
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_compoents/paho-mqtt/mqtt_ui
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_compoents/paho-mqtt/mqtt_ui/ssl_mqtt
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_compoents/paho-mqtt/mqtt_ui/tcp_mqtt

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_compoents/mbedtls/mbedtls/include
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_compoents/mbedtls/mbedtls/config
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_compoents/mbedtls/mbedtls/include/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_compoents/mbedtls/mbedtls_ui
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_compoents/mbedtls/mbedtls-port/inc

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_application/quectel_demo
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_application/quectel_demo/tcp_client
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_application/quectel_demo/tcp_server

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/common
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/demo
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/app
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/app/http
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/app/config
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/app/net_work

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/common
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/ke
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/mac
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/hal
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/mm
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/ps
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/rd
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/rwnx
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/rx
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/scan
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/sta
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/tx
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/vif
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/rx/rxl
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/tx/txl
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/p2p
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/chan
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/td
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/tpc
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/lmac/src/tdls

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/umac/src/apm
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/umac/src/mesh
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/umac/src/mfp
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/umac/src/rc
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/umac/src/bam
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/umac/src/llc
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/umac/src/me
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/umac/src/rxu
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/umac/src/scanu
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/umac/src/sm
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/ip/umac/src/txu

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/include
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/common
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/common/reg
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/entry
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/dma
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/intc
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/phy
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/pwm
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/rc_beken
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/flash
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/rw_pub
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/sys_ctrl
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/general_dma
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/spidma
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/icu
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/spi
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/jpeg
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/src/cd
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/src/hid
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/src/lib
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/src/msc
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/src/uvc
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/src/drivers
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/src/drivers/hub
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/src/drivers/hid
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/src/drivers/msd
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/src/drivers/comm
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/src/drivers/compl
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/src/drivers/trans
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/src/systems/none
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/src/systems/none/afs
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/include
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/include/class
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/usb/src/example/msd

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/include
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/airkiss
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/bk7011_cal
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/temp_detect
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/wlan_ui
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/base64
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/rf_test
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/rf_use
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/usb
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/utf8
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/misc
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/sensor
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/user_driver
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/power_save
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/uart_debug
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/ethernet_intf
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/camera_intf
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/spidma_intf
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/saradc_intf
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/rwnx_intf
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/joint_up
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/force_sleep
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/video_transfer
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/ble_wifi_exchange

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/wpa_supplicant_2_9/hostapd
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/wpa_supplicant_2_9/bk_patch
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/wpa_supplicant_2_9/src
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/wpa_supplicant_2_9/src/utils
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/wpa_supplicant_2_9/src/ap
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/wpa_supplicant_2_9/src/wps
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/wpa_supplicant_2_9/src/common
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/wpa_supplicant_2_9/src/drivers
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/wpa_supplicant_2_9/wpa_supplicant

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/port
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/include
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/include/netif
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/include/lwip

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/easy_flash
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/easy_flash/inc
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/easy_flash/port
)

list(APPEND os_source_file
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/os/platform_stub.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/os/str_arch.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/os/mem_arch.c
)

include_directories(BEFORE  ${include_files} ${ble_include_file})

add_library(os STATIC ${os_source_file})
