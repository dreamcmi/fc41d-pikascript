
option(MBEDTLS_ENABLE   "Support mbedtls ,default on"   ON)
option(PHAO_MQTT_ENABLE "Support phao_mqtt, default on" ON)
option(BLE_MESH_ENABLE  "Support ble mesh,default off,if 
                         use the ble mesh,the ble stack 
                         version should be version 4.2"  OFF)

option(FREE_RTOS_ENABLE "FreeRTOS support FreeRTOSv9.0.0,default on" ON)
option(HOMOS_ENABLE     "Homonry os support, default off" OFF)
option(USE_SYS_TOOLCHAIN "Use system installed toolchain as project tools" OFF)



message(STATUS "MBEDNTLS  FLAG: ${MBEDTLS_ENABLE}")
message(STATUS "PHAO_MQTT FLAG: ${PHAO_MQTT_ENABLE}")
message(STATUS "BLE MESH  FLAG: ${BLE_MESH_ENABLE}")
message(STATUS "FREE_RTOS FLAG: ${FREE_RTOS_ENABLE}")
message(STATUS "HOMOS     FLAG: ${HOMOS_ENABLE}")
message(STATUS "USE_SYS_TOOLCHAIN: ${USE_SYS_TOOLCHAIN}")

