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
project(func VERSION 1.0.0)
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

list(APPEND func_source_file
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/func.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/usb_plug/usb_plug.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/security/security_func.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/joint_up/role_launch.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/port/ethernetif.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/port/net.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/port/sys_arch.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/api/api_lib.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/api/api_msg.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/api/err.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/api/netbuf.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/api/netdb.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/api/netifapi.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/api/sockets.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/api/tcpip.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/def.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/apps/ping/ping.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/dns.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/inet_chksum.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/init.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ip.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv4/dhcp.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv4/etharp.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv4/icmp.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv4/igmp.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv4/ip4_addr.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv4/ip4.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv4/ip4_frag.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv6/dhcp6.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv6/ethip6.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv6/icmp6.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv6/inet6.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv6/ip6_addr.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv6/ip6.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv6/ip6_frag.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv6/nd6.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/ipv6/mld6.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/mem.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/netif.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/memp.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/pbuf.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/raw.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/stats.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/sys.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/tcp.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/tcp_in.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/tcp_out.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/timeouts.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/core/udp.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/netif/ethernet.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/apps/httpd/httpd.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/lwip-2.0.2/src/apps/httpd/fs.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/dhcpd/dhcp-server.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/lwip_intf/dhcpd/dhcp-server-main.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/misc/fake_clock.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/misc/pseudo_random.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/misc/target_util.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/misc/start_type.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/misc/soft_encrypt.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/misc/flash_bypass.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/power_save/power_save.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/power_save/manual_ps.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/power_save/mcu_ps.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/power_save/low_voltage_ps.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/power_save/low_voltage_compensation.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/power_save/ap_idle.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/saradc_intf/saradc_intf.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/rwnx_intf/rw_ieee80211.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/rwnx_intf/rw_msdu.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/rwnx_intf/rw_tx_buffering.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/rwnx_intf/rw_msg_rx.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/rwnx_intf/rw_msg_tx.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/sim_uart/gpio_uart.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/sim_uart/pwm_uart.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/spidma_intf/spidma_intf.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/temp_detect/temp_detect.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/user_driver/BkDriverFlash.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/user_driver/BkDriverGpio.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/user_driver/BkDriverPwm.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/user_driver/BkDriverUart.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/user_driver/BkDriverWdg.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/user_driver/BkDriverRng.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/user_driver/BkDriverTimer.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/wlan_ui/bk_peripheral_test.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/wlan_ui/wlan_cli.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/wlan_ui/sa_ap.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/wlan_ui/sa_station.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/utf8/conv_utf8.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/camera_intf/camera_intf.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/camera_intf/camera_intf_gc2145.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/video_transfer/video_transfer.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/wlan_ui/wlan_ui.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/net_param_intf/net_param.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/base64/base_64.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/airkiss/airkiss_main.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/airkiss/airkiss_pingpong.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/airkiss/bk_airkiss.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/easy_flash/bk_ef.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/easy_flash/src/easyflash.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/easy_flash/src/ef_env.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/easy_flash/src/ef_env_wl.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/easy_flash/src/ef_iap.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/easy_flash/src/ef_log.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/easy_flash/src/ef_utils.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/easy_flash/port/ef_port.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/force_sleep/force_mcu_ps.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/force_sleep/force_mac_ps.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/ble_wifi_exchange/ble_wifi_port.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/bk7011_cal/bk_cal_pub.c
    ${CMAKE_CURRENT_LIST_DIR}/../../ql_kernel/func/hostapd_intf/hostapd_intf.c
)

include_directories(BEFORE  ${include_files} ${ble_include_file})

add_library(func STATIC ${func_source_file})
