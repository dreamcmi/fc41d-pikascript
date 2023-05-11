# 最小的cmake版本
cmake_minimum_required(VERSION 3.18)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

include(${CMAKE_CURRENT_SOURCE_DIR}/config.cmake)

# 检测操作系统哦
if(WIN32)
    message(STATUS "windows build .........")
elseif(UNIX)
    message(STATUS "Linux build ...........")
endif()

# set target name
##################################################
## fc41d_app:     使用beken7231n.lds     链接脚本 ##
## fc41d_bsp_app: 使用beken7231n_bsp.lds 链接脚本 ##
##################################################
set(target "fc41d_bsp_app" CACHE STRING "Please select the building target ...")
set_property(CACHE target PROPERTY STRINGS
    fc41d_app
    fc41d_bsp_app
)

if(${target} STREQUAL "fc41d_bsp_app")
    set(ld_file "${CMAKE_CURRENT_LIST_DIR}/bk7231n_bsp.lds")
elseif(${target} STREQUAL "fc41d_app")
    set(ld_file "${CMAKE_CURRENT_LIST_DIR}/bk7231n.lds")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/toolchain_bk7231n.cmake)

set(CMAKE_C_LINK_FLAGS "-g -marm -mcpu=arm968e-s -mthumb-interwork -nostdlib -Xlinker -Map=beken.map -Wl,--gc-sections -Wl,-wrap,malloc -Wl,-wrap,_malloc_r -Wl,-wrap,free -Wl,-wrap,_free_r -Wl,-wrap,zalloc -Wl,-wrap,calloc -Wl,-wrap,realloc -Wl,-wrap,_realloc_r -Wl,-wrap,printf -Wl,-wrap,vsnprintf -Wl,-wrap,snprintf -Wl,-wrap,sprintf -Wl,-wrap,puts")
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> <CMAKE_C_LINK_FLAGS> -o <TARGET> <OBJECTS> <LINK_LIBRARIES> <LINK_FLAGS>")

## 设置编译参数和连接参数 -marm -mcpu=arm968e-s -mthumb-interwork -nostdlib
set(ASM_OPTIONS "-g -marm -mthumb-interwork -mcpu=arm968e-s -march=armv5te -x assembler-with-cpp")
set(CMAKE_C_FLAGS "-g -DCFG_OS_FREERTOS=1 -DWIFI_BLE_COEXIST -mthumb -mcpu=arm968e-s -march=armv5te -mthumb-interwork -mlittle-endian -Os -std=c99 -ffunction-sections -Wall -Wno-format -Wno-unknown-pragmas -fsigned-char -fdata-sections -nostdlib -fno-strict-aliasing -fno-common")
set(CMAKE_CXX_FLAGS "-g -DCFG_OS_FREERTOS=1 -DWIFI_BLE_COEXIST -mthumb -mcpu=arm968e-s -march=armv5te -mthumb-interwork -mlittle-endian -Os -std=c99 -ffunction-sections -Wall -Wno-format -Wno-unknown-pragmas -fsigned-char -fdata-sections -nostdlib -fno-strict-aliasing -fno-common")
###########################################################################
project(fc41d VERSION 1.0)

enable_language(ASM C)

add_definitions(-DSYS_CONFIG_FILE=<sys_config.h>)
add_definitions(-DMBEDTLS_CONFIG_FILE=<tls_config.h>)
add_link_options(-L${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/lib -lsdk -L${CMAKE_CURRENT_LIST_DIR}/../ql_components/quectel_api -lquectel_api -T${ld_file} -Xlinker -Map=${target}.map)

list(APPEND include_files
    ${CMAKE_CURRENT_LIST_DIR}/../ql_build

    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/os/include
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/os/FreeRTOSv9.0.0
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/os/FreeRTOSv9.0.0/Source/include
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/os/FreeRTOSv9.0.0/Source/portable/Keil/ARM968es

    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/quectel_api/include

    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/client
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/client/src
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/packet/src
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/mqtt_ui
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/mqtt_ui/ssl_mqtt
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/mqtt_ui/tcp_mqtt

    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/include
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/config
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/include/mbedtls
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls_ui
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls-port/inc

    ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo
    ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/tcp_client
    ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/tcp_server

    ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/5500
    ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/5500/w5500
 
    # TODO: add user include file inc here,

    ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/

    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/common
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/demo
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/app
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/app/http
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/app/config
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/app/net_work

    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/common
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/ke
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/mac
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/hal
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/mm
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/ps
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/rd
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/rwnx
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/rx
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/scan
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/sta
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/tx
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/vif
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/rx/rxl
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/tx/txl
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/p2p
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/chan
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/td
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/tpc
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/lmac/src/tdls

    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/umac/src/apm
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/umac/src/mesh
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/umac/src/mfp
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/umac/src/rc
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/umac/src/bam
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/umac/src/llc
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/umac/src/me
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/umac/src/rxu
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/umac/src/scanu
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/umac/src/sm
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/ip/umac/src/txu

    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/include
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/common
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/common/reg
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/entry
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/dma
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/intc
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/phy
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/pwm
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/rc_beken
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/flash
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/rw_pub
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/uart
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/sys_ctrl
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/gpio
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/general_dma
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/spidma
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/icu
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/i2c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/spi
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/jpeg
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/src/cd
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/src/hid
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/src/lib
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/src/msc
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/src/uvc
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/src/drivers
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/src/drivers/hub
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/src/drivers/hid
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/src/drivers/msd
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/src/drivers/comm
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/src/drivers/compl
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/src/drivers/trans
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/src/systems/none
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/src/systems/none/afs
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/include
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/include/class
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/usb/src/example/msd

    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/include
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/temp_detect
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/wlan_ui
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/base64
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/airkiss
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/bk7011_cal
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/rf_test
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/rf_use
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/usb
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/utf8
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/misc
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/sensor
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/user_driver
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/power_save
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/uart_debug
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/ethernet_intf
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/camera_intf
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/spidma_intf
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/saradc_intf
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/rwnx_intf
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/joint_up
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/force_sleep
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/video_transfer
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/ble_wifi_exchange

    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/wpa_supplicant_2_9/hostapd
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/wpa_supplicant_2_9/bk_patch
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/wpa_supplicant_2_9/src
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/wpa_supplicant_2_9/src/utils
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/wpa_supplicant_2_9/src/ap
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/wpa_supplicant_2_9/src/wps
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/wpa_supplicant_2_9/src/common
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/wpa_supplicant_2_9/src/drivers
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/wpa_supplicant_2_9/wpa_supplicant

    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/lwip_intf/lwip-2.0.2/src
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/lwip_intf/lwip-2.0.2/port
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/lwip_intf/lwip-2.0.2/src/include
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/lwip_intf/lwip-2.0.2/src/include/netif
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/lwip_intf/lwip-2.0.2/src/include/lwip

    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/easy_flash
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/easy_flash/inc
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/func/easy_flash/port
)

list(APPEND ble_include_file
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/inc
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gap/gapc
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gap/gapm
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gatt
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gatt/attc
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gatt/attm
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gatt/atts
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gatt/gattc
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/gatt/gattm
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/l2c/l2cc
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/hl/src/l2c/l2cm
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/ll/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/ll/src
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/ll/src/llc
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/ll/src/lld
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/ll/src/llm
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/ble/ll/import/reg
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/em/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/hci/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/hci/src
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/sch/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/ip/sch/import
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/aes/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/aes/src
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/common/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/dbg/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/dbg/src
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/ecc_p256/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/h4tl/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/ke/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_lib/modules/ke/src
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_pub/ui
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_pub/prf
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_pub/app/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_pub/profiles/sdp/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_pub/profiles/app/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/ble_pub/profiles/comm/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/platform/7231n/rwip/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/platform/7231n/rwip/import/reg
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/platform/7231n/nvds/api
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/platform/7231n/config
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/platform/7231n/driver/reg
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/platform/7231n/driver/rf
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/platform/7231n/driver/uart
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/platform/7231n/entry
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/arch/armv5
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/arch/armv5/ll
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/driver/ble_5_x_rw/arch/armv5/compiler
)

list(APPEND kernel_app_source_file
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/app/app.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/app/ate_app.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/app/http/utils_httpc.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/app/http/utils_net.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/app/http/utils_timer.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/app/http/lite-log.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/app/config/param_config.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_kernel/demo/ieee802_11_demo.c
)

list(APPEND quectel_demo_source_file
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/demo_main.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_ble_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_i2c_eeprom_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_timer_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_uart_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_watchdog_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_spi_flash_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_spi_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_pwm_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_gpio_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_flash_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_adc_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_lowpower_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_ble_config_network_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_wlan_config_network_demo.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_wlan_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_osi_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_tls_demo.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/ql_mqtt_demo.c

    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/tcp_client/tcp_client_demo.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/tcp_server/mongoose.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/tcp_server/tcp_websocket_server.c

    # #w5500
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/5500/wizchip_conf.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/5500/wizchip_ethnetif.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/5500/wizchip_port.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/5500/wizchip_test.c
    # ${CMAKE_CURRENT_LIST_DIR}/../ql_application/quectel_demo/5500/w5500/w5500.c

    # TODO: add user source files(s/c/c++) here:
    ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/app_main.c
)

list(APPEND mbedtls_source_file
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls-port/src/timing_alt.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls-port/src/tls_certificate.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls-port/src/tls_client.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls-port/src/tls_hardware.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls-port/src/tls_net.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls-port/src/tls_mem.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/aes.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/aesni.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/arc4.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/asn1parse.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/asn1write.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/base64.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/bignum.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/blowfish.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/camellia.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/ccm.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/certs.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/cipher.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/cipher_wrap.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/cmac.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/ctr_drbg.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/debug.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/des.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/dhm.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/ecdh.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/ecdsa.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/ecjpake.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/ecp.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/ecp_curves.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/entropy.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/error.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/entropy_poll.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/gcm.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/havege.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/hmac_drbg.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/md.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/md_wrap.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/md2.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/md4.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/md5.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/memory_buffer_alloc.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/net_sockets.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/oid.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/padlock.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/pem.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/pk.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/pk_wrap.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/pkcs5.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/pkcs11.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/pkcs12.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/pkparse.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/pkwrite.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/platform.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/ripemd160.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/rsa.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/sha1.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/sha256.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/sha512.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/ssl_cache.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/ssl_ciphersuites.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/ssl_cli.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/ssl_cookie.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/ssl_srv.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/ssl_ticket.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/ssl_tls.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/threading.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/timing.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/version.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/version_features.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/x509.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/x509_crl.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/x509_create.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/x509_crt.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/x509write_crt.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/x509write_csr.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls/library/xtea.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/mbedtls/mbedtls_ui/sl_tls.c
)

list(APPEND paho_mqtt_source_file
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/client/src/MQTTClient.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/client/src/MQTTFreeRTOS.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/client/paho_mqtt_udp.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/packet/src/MQTTConnectClient.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/packet/src/MQTTConnectServer.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/packet/src/MQTTDeserializePublish.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/packet/src/MQTTFormat.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/packet/src/MQTTPacket.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/packet/src/MQTTSerializePublish.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/packet/src/MQTTSubscribeClient.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/packet/src/MQTTSubscribeServer.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/packet/src/MQTTUnsubscribeClient.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/packet/src/MQTTUnsubscribeServer.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/mqtt_ui/ssl_mqtt/ssl_mqtt_client_port.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/mqtt_ui/tcp_mqtt/tcp_mqtt_client_port.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/mqtt_ui/mqtt_client_core.c
    ${CMAKE_CURRENT_LIST_DIR}/../ql_components/paho-mqtt/mqtt_ui/mqtt_client_com_port.c
)

include_directories(BEFORE  ${include_files} ${ble_include_file})

#add_library(driver)

file(GLOB pika_src
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-api/*.c
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-core/*.c
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/PikaStdDevice/*.c
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/PikaStdLib/*.c
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/time/*.c
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/pika_libc/*.c
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/socket/*.c
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/hashlib/*.c
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/hmac/*.c
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/base64/*.c
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/FC41D/*.c
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/network/*.c
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/_thread/*.c
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pika_config.c
)

list(APPEND pika_inc
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-api
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-core
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/PikaStdDevice
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/PikaStdLib
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/time/
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/pika_libc
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/FC41D
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/socket
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/hashlib
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/hmac
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/base64
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/network
        ${CMAKE_CURRENT_LIST_DIR}/../ql_application/pikascript/pikascript-lib/_thread
)

add_library(pikascript-core STATIC)
target_sources(pikascript-core PRIVATE ${pika_src})
target_include_directories(pikascript-core PUBLIC ${pika_inc})
target_compile_definitions(pikascript-core PRIVATE 
                            PIKA_CONFIG_ENABLE 
                            PIKA_LWIP_ENABLE 
                            PIKA_FREERTOS_ENABLE)

add_executable(${target}
    ${kernel_app_source_file}
    ${quectel_demo_source_file}
    ${mbedtls_source_file}       #ql_components_mbedtls_source_files
    ${paho_mqtt_source_file}
)
target_link_libraries(${target} PRIVATE  -Wl,--whole-archive pikascript-core  -Wl,--no-whole-archive)
set_target_properties(${target} PROPERTIES OUTPUT_NAME "${target}.elf")

if(${target} STREQUAL "fc41d_bsp_app")
add_custom_command(
    TARGET ${target}
    POST_BUILD
    COMMAND ${arm_gcc_objcopy} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${target}.elf ${CMAKE_CURRENT_BINARY_DIR}/${target}.bin
    COMMAND ${arm_gcc_objdump} --all-headers --demangle --disassemble ${CMAKE_CURRENT_BINARY_DIR}/${target}.elf > ${CMAKE_CURRENT_BINARY_DIR}/${target}.lst
)
elseif(${target} STREQUAL "fc41d_app")
add_custom_command(
    TARGET ${target}
    POST_BUILD
    COMMAND ${arm_gcc_objcopy} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${target}.elf ${CMAKE_CURRENT_BINARY_DIR}/${target}.bin
    COMMAND ${encrypt} ${CMAKE_CURRENT_BINARY_DIR}/${target}.bin 0 0 0 0 > /dev/null
)
endif()

# # set custom target
# add_custom_target(
# )
# add_custom_target(
# )

# set install dir
install(PROGRAMS
	${CMAKE_CURRENT_BINARY_DIR}/${target}.elf
    ${CMAKE_CURRENT_BINARY_DIR}/${target}.map
    ${CMAKE_CURRENT_BINARY_DIR}/${target}.bin
	DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../ql_out
)
