cmake_minimum_required(VERSION 3.22)

# 检测操作系统哦
if(WIN32)
    message(STATUS "windows build .........")
elseif(UNIX)
    message(STATUS "Linux build ...........")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/../../ql_build/toolchain_bk7231n.cmake)

set(ASM_OPTIONS "-g -marm -mthumb-interwork -mcpu=arm968e-s -march=armv5te -x assembler-with-cpp")
set(CMAKE_C_FLAGS "-g -DCFG_OS_FREERTOS=1 -DCFG_SOC_NAME=5 -DMG_ARCH=6 -DWIFI_BLE_COEXIST -mthumb -mcpu=arm968e-s -march=armv5te -mthumb-interwork -mlittle-endian -Os -std=c99 -ffunction-sections -Wall -Wno-format -Wno-unknown-pragmas -fsigned-char -fdata-sections -nostdlib -fno-strict-aliasing -fno-common")
set(CMAKE_CXX_FLAGS "-g -DCFG_OS_FREERTOS=1 -DWIFI_BLE_COEXIST -mthumb -mcpu=arm968e-s -march=armv5te -mthumb-interwork -mlittle-endian -Os -std=c99 -ffunction-sections -Wall -Wno-format -Wno-unknown-pragmas -fsigned-char -fdata-sections -nostdlib -fno-strict-aliasing -fno-common")
##############################################################################################
project(driver VERSION 1.0.0)
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

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_components/quectel_api/include

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_components/paho-mqtt/client
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_components/paho-mqtt/client/src
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_components/paho-mqtt/packet/src
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_components/paho-mqtt/mqtt_ui
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_components/paho-mqtt/mqtt_ui/ssl_mqtt
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_components/paho-mqtt/mqtt_ui/tcp_mqtt

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_components/mbedtls/mbedtls/include
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_components/mbedtls/mbedtls/config
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_components/mbedtls/mbedtls/include/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_components/mbedtls/mbedtls_ui
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_components/mbedtls/mbedtls-port/inc

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

list(APPEND ble_include_file
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/inc
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gap/gapc
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gap/gapm
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gatt
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gatt/attc
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gatt/attm
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gatt/atts
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gatt/gattc
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gatt/gattm
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/l2c/l2cc
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/l2c/l2cm
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/ll/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/ll/src
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/ll/src/llc
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/ll/src/lld
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/ll/src/llm
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/ll/import/reg
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/em/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/hci/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/hci/src
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/sch/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/sch/import
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/aes/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/aes/src
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/common/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/dbg/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/dbg/src
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/ecc_p256/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/h4tl/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/ke/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/ke/src
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/ui
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/prf
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/app/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/profiles/sdp/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/profiles/app/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/profiles/comm/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/platform/7231n/rwip/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/platform/7231n/rwip/import/reg
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/platform/7231n/nvds/api
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/platform/7231n/config
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/platform/7231n/driver/reg
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/platform/7231n/driver/rf
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/platform/7231n/driver/uart
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/platform/7231n/entry
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/arch/armv5
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/arch/armv5/ll
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/arch/armv5/compiler
)

list(APPEND driver_source_file
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/driver.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/entry/arch_main.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/entry/boot_handlers.S
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/entry/boot_vectors.S

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/common/dd.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/common/drv_model.c

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/dma/dma.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/general_dma/general_dma.c

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/calendar/calendar.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/flash/flash.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/fft/fft.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/gpio/gpio.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/icu/icu.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/intc/intc.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/irda/irda.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/macphy_bypass/mac_phy_bypass.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/phy/phy_trident.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/rw_pub/rw_platf_pub.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/saradc/saradc.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/sys_ctrl/sys_ctrl.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/wdt/wdt.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/jpeg/jpeg_encoder.c

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/uart/printf.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/uart/Retarget.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/uart/uart.c

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/security/security.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/security/hal_aes.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/security/hal_sha.c

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/i2c/i2c1.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/i2c/i2c2.c

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/pwm/pwm.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/pwm/pwm_bk7231n.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/pwm/mcu_ps_timer.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/pwm/bk_timer.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/pwm/bk_timer_extense.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/pwm/pwm_mutex.c

    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/qspi/qspi.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/spi/spi_bk7231n.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/spi/spi_master_bk7231n.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/spi/spi_slave_bk7231n.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/spi/spi_flash.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/spidma/spidma.c
)

list(APPEND driver_ble_source_file

)

list(APPEND driver_ble_5x_source_file
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/prf/prf.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/prf/prf_utils.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/profiles/comm/src/comm.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/profiles/comm/src/comm_task.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/app/src/app_comm.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/app/src/app_ble.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/app/src/app_task.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/ui/ble_ui.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/platform/7231n/rwip/src/rwip.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/platform/7231n/rwip/src/rwble.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/platform/7231n/entry/ble_main.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/platform/7231n/driver/rf/rf_xvr.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/platform/7231n/driver/rf/ble_rf_port.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/platform/7231n/driver/uart/uart_ble.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/app/src/app_ble_init.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/app/src/app_sdp.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/profiles/sdp/src/sdp_common.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/driver/ble_5_x_rw/ble_pub/profiles/sdp/src/sdp_comm_task.c
)

include_directories(BEFORE  ${include_files} ${ble_include_file})

add_library(driver STATIC ${driver_source_file} ${driver_ble_5x_source_file})
