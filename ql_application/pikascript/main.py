import PikaStdLib
import PikaStdDevice as std
# import FC41D
import socket
import hashlib
import hmac
import base64


time = std.Time()
mem = PikaStdLib.MemChecker()

print('hello pikascript on FC41D')
print('mem.max :')
mem.max()
print('mem.now :')
mem.now()

G1 = std.GPIO()
G1.setPin('22')
G1.setMode('in')
G1.enable()
G1.low()


def cb1(signal):
    print('cb1', signal)


G1.setCallBack(cb1, G1.SIGNAL_RISING)

# G2 = std.GPIO()
# G2.setPin('23')
# G2.setMode('out')
# G2.enable()
# G2.low()

##################
# print("socket test begin")
# print("当前占用内存:",mem.now())
# s = socket.socket()
# host = "112.125.89.8"
# port = 33911
# s.connect((host, port))
# print("连接成功占用内存:",mem.now())
# s.send("hello pika from fc41d")
# print("发送消息占用内存:",mem.now())
# s.close()
# print("关闭连接占用内存:",mem.now())
# del s
# print("清理现场占用内存:",mem.now())
##################

# a1 = std.ADC()
# a1.setPin('1')
# a1.enable()

while True:
    mem.now()
    G1.read()
    # if i :
    #     print("G1 high")
    # else:
    #     print("G1 low")
    # a1.read()
    # mem.now()
    time.sleep_ms(1000)
