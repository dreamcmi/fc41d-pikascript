## 系统环境检查 ##
if (USE_SYS_TOOLCHAIN)
find_program(arm_gcc_file_path arm-none-eabi-gcc)
if(NOT IS_ABSOLUTE ${arm_gcc_file_path})
    message(FATAL_ERROR "arm-none-eabi-gcc is not found !!!!")
endif()

if(WIN32)
    STRING(REGEX REPLACE "^(.+)/arm-none-eabi-gcc.exe*$" "\\1" arm_gcc_path ${arm_gcc_file_path})
elseif(UNIX)
    STRING(REGEX REPLACE "^(.+)/arm-none-eabi-gcc*$" "\\1" arm_gcc_path ${arm_gcc_file_path})
endif()
set(tools ${arm_gcc_path}/..)
else()
set(tools ${CMAKE_CURRENT_LIST_DIR}/../ql_tools/toolchain/gcc_arm_none_eabi/gcc-arm-none-eabi-5_4-2016q3)
endif()


if(WIN32)
    set(arm_gcc_ar ${tools}/bin/arm-none-eabi-ar.exe)
    set(arm_gcc_as ${tools}/bin/arm-none-eabi-as.exe)
    set(arm_gcc_nm ${tools}/bin/arm-none-eabi-nm.exe)
    set(arm_gcc_size ${tools}/bin/arm-none-eabi-size.exe)
    set(arm_gcc_objcopy ${tools}/bin/arm-none-eabi-objcopy.exe)
    set(arm_gcc_objdump ${tools}/bin/arm-none-eabi-objdump.exe)
elseif(UNIX)
    set(arm_gcc_ar ${tools}/bin/arm-none-eabi-ar)
    set(arm_gcc_as ${tools}/bin/arm-none-eabi-as)
    set(arm_gcc_nm ${tools}/bin/arm-none-eabi-nm)
    set(arm_gcc_size ${tools}/bin/arm-none-eabi-size)
    set(arm_gcc_objcopy ${tools}/bin/arm-none-eabi-objcopy)
    set(arm_gcc_objdump ${tools}/bin/arm-none-eabi-objdump)
endif()

if (WIN32)
    # 设置gcc工具
    set(CMAKE_C_COMPILER ${tools}/bin/arm-none-eabi-gcc.exe)
    # 设置g++工具
    set(CMAKE_CXX_COMPILER ${tools}/bin/arm-none-eabi-g++.exe)
    # 设置ld工具
    set(CMAKE_LINKER ${tools}/bin/arm-none-eabi-gcc.exe)
elseif (UNIX)
    # 设置gcc工具
    set(CMAKE_C_COMPILER ${tools}/bin/arm-none-eabi-gcc)
    # 设置g++工具
    set(CMAKE_CXX_COMPILER ${tools}/bin/arm-none-eabi-g++)
    # 设置ld工具
    set(CMAKE_LINKER ${tools}/bin/arm-none-eabi-gcc)
endif()

#指定交叉编译环境的目录
set(CMAKE_FIND_ROOT_PATH ${tools})
#从来不在指定目录(交叉编译)下查找工具程序。(编译时利用的是宿主的工具)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#只在指定目录(交叉编译)下查找库文件
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#只在指定目录(交叉编译)下查找头文件
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#只在指定的目录(交叉编译)下查找依赖包
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

