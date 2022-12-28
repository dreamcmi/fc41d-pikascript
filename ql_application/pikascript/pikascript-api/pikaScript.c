/*
 * [Warning!] This file is auto-generated by pika compiler.
 * Do not edit it manually.
 * The source code is *.pyi file.
 * More details: 
 * English Doc:
 * https://pikadoc.readthedocs.io/en/latest/PikaScript%20%E6%A8%A1%E5%9D%97%E6%A6%82%E8%BF%B0.html
 * Chinese Doc:
 * https://pikadoc.readthedocs.io/zh/latest/PikaScript%20%E6%A8%A1%E5%9D%97%E6%A6%82%E8%BF%B0.html
 */

#include "PikaMain.h"
#include <stdio.h>
#include <stdlib.h>

volatile PikaObj *__pikaMain;
PikaObj *pikaScriptInit(void){
    __platform_printf("======[pikascript packages installed]======\r\n");
    pks_printVersion();
    __platform_printf("PikaStdDevice==latest\r\n");
    __platform_printf("PikaStdLib==latest\r\n");
    __platform_printf("base64==v1.0.0\r\n");
    __platform_printf("hashlib==v1.0.1\r\n");
    __platform_printf("hmac==v1.0.1\r\n");
    __platform_printf("pika_libc==v1.0.0\r\n");
    __platform_printf("socket==latest\r\n");
    __platform_printf("===========================================\r\n");
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    __pikaMain = pikaMain;
    extern unsigned char pikaModules_py_a[];
    obj_linkLibrary(pikaMain, pikaModules_py_a);
#if PIKA_INIT_STRING_ENABLE
    obj_run(pikaMain,
            "import PikaStdLib\n"
            "import PikaStdDevice as std\n"
            "# import FC41D\n"
            "import socket\n"
            "import hashlib\n"
            "import hmac\n"
            "import base64\n"
            "time = std.Time()\n"
            "mem = PikaStdLib.MemChecker()\n"
            "print('hello pikascript on FC41D')\n"
            "print('mem.max :')\n"
            "mem.max()\n"
            "print('mem.now :')\n"
            "mem.now()\n"
            "G1 = std.GPIO()\n"
            "G1.setPin('22')\n"
            "G1.setMode('in')\n"
            "G1.enable()\n"
            "G1.low()\n"
            "def cb1(signal):\n"
            "    print('cb1', signal)\n"
            "G1.setCallBack(cb1, G1.SIGNAL_RISING)\n"
            "# G2 = std.GPIO()\n"
            "# G2.setPin('23')\n"
            "# G2.setMode('out')\n"
            "# G2.enable()\n"
            "# G2.low()\n"
            "##################\n"
            "# print(\"socket test begin\")\n"
            "# print(\"当前占用内存:\",mem.now())\n"
            "# s = socket.socket()\n"
            "# host = \"112.125.89.8\"\n"
            "# port = 33911\n"
            "# s.connect((host, port))\n"
            "# print(\"连接成功占用内存:\",mem.now())\n"
            "# s.send(\"hello pika from fc41d\")\n"
            "# print(\"发送消息占用内存:\",mem.now())\n"
            "# s.close()\n"
            "# print(\"关闭连接占用内存:\",mem.now())\n"
            "# del s\n"
            "# print(\"清理现场占用内存:\",mem.now())\n"
            "##################\n"
            "# a1 = std.ADC()\n"
            "# a1.setPin('1')\n"
            "# a1.enable()\n"
            "while True:\n"
            "    mem.now()\n"
            "    G1.read()\n"
            "    # if i :\n"
            "    #     print(\"G1 high\")\n"
            "    # else:\n"
            "    #     print(\"G1 low\")\n"
            "    # a1.read()\n"
            "    # mem.now()\n"
            "    time.sleep_ms(1000)\n"
            "\n");
#else 
    obj_runModule((PikaObj*)pikaMain, "main");
#endif
    return pikaMain;
}

