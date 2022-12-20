# change list
| 日期 | 版本 | 说明 |
- 2022-10-31： version 0.1 ZhangYuanyuan  first release

# 环境搭建
## 交叉编译链安装
1. 交叉编译链必须安装 `arm-none-eabi-gcc` `version: 5.4.1 20160919`,否则相应的`lib`库使用会异常；可以不进行安装，sdk中已存在；
2. `cmake`建议安装最新版本，必须要要安装的软件，目前支持3.18版本以上的`cmake`，在使用前请确保`cmake`;
3. 对于64位的系统，请务必先按照FAQ中1描述，安装32位程序的支持；


# 文件目录说明
1. `ql_application`: `demo`和用户自己的应用工程代码防止的位置
2. `ql_build`:       放置和编译相关的脚本文件
3. `ql_components`:  放置组建，包括第三方组建，以及`quectel api`组建
4. `ql_kernel`: 放置与芯片相关的代码以及代码库，包括对RTOS的支持，目前仅支持FreeRTOS
5. `ql_out`: 工程编译输出，用于烧录的文件，包括.bin,map以及编译日志等
6. `ql_tools`: 编译过程中需要使用的工具链

# 编译说明
1. 进入`ql_build`目录
2. 运行`build.sh`脚本
3. 等待编译完成，在`ql_out`目录中查看生成数据
> `all_2M.1220.bin`
> 
> `fc41d_bsp_app.bin`
> 
> `fc41d_bsp_app.elf`
> 
> `fc41d_bsp_app.map`
> 
> `fc41d_bsp_app_uart_2M.1220.bin`
> 
> `make_log.txt`:编译过程中的记录
> 
> `make_error_log.txt`:记录编译中的警告以及错误
> 
> 注意：该目录的文件会在下一次编译时主动清除

# 用户如何添加自己的工程
1. 在`ql_application` 下创建用户工程 例如：`user_demo`
2. 在用户的工程中添加对应的`.h` 或者`.c`文件
3. 将源文件添加到工程编译链接中
4. 进入`ql_build`文件夹，找到其中的`CMakeLists.txt`文件打开，定位到 `# TODO: add user include file inc here:`
5. 在上述定位的位置添加用户的头文件所在的文件路径，请注意路经
6. 添加源文件，同样是进入`ql_build`文件夹，定位到`# TODO: add user source files(s/c/c++) here:`
7. 在上述位置添加用户的源文件，注意路径

# FAQ
1. 编译工具运行异常如何解决？
```
sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386
sudo apt install lib32z1
```

2.
