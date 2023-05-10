import PikaStdLib
import PikaStdDevice as std
# import FC41D
import socket
import hashlib
import hmac
import base64
import time
import network

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

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect("AR300M-NOR", "goodlife")
while wlan.isconnected() == 0:
    pass


#################
print("socket test begin")
print("当前占用内存:",mem.now())
s = socket.socket()
s.setblocking(False) 
host = "112.125.89.8"
port = 37803
s.connect((host, port))
print("连接成功占用内存:",mem.now())
s.send("hello pika from fc41d")
print("发送消息占用内存:",mem.now())
m = s.recv(10)
print(m)
print("接收消息占用内存:",mem.now())
s.close()
print("关闭连接占用内存:",mem.now())
del s
print("清理现场占用内存:",mem.now())
#################

while True:
    mem.now()
    time.sleep_ms(1000)
