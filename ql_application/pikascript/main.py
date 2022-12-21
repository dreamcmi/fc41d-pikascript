import PikaStdLib
import PikaStdDevice as std
import FC41D
import socket
import hashlib
import hmac
import base64


time = FC41D.Time()
mem = PikaStdLib.MemChecker()

print('hello pikascript on FC41D')
print('mem.max :')
mem.max()
print('mem.now :')
mem.now()

G1 = std.GPIO()
G1.setPin('22')
G1.setMode('out')
G1.enable()
G1.low()

G2 = std.GPIO()
G2.setPin('23')
G2.setMode('out')
G2.enable()
G2.low()

# ##################
# secret = "0123456789"
# payload = "helloworld"

# h = hmac.new(secret.encode(),digestmod="md5")
# h.update(payload.encode())
# print("hmac-md5:",h.hexdigest())
# mem.now()

# h = hmac.new(secret.encode(),digestmod="sha1")
# h.update(payload.encode())
# print("hmac-sha1:",h.hexdigest())
# mem.now()

# h = hmac.new(secret.encode(),digestmod="sha256")
# h.update(payload.encode())
# print("hmac-sha256:",h.hexdigest())
# mem.now()
# del h
# mem.now()
# ##################

# ##################
# if base64.b64encode(b"123456").decode() == "MTIzNDU2":
#     print("base64 encode test ok")
# else:
#     print("base64 encode test error")

# if base64.b64decode(b"\x4d\x54\x49\x7a\x4e\x44\x55\x32").decode() == "123456":
#     print("base64 decode test ok")
# else:
#     print("base64 decode test error")
# mem.now()
# ##################

# ##################
# h = hashlib.new("md5")
# h.update(payload.encode())
# print("md5:", h.hexdigest())
# mem.now()

# h = hashlib.new("sha1")
# h.update(payload.encode())
# print("sha1:", h.hexdigest())
# mem.now()

# h = hashlib.new("sha256")
# h.update(payload.encode())
# print("sha256:", h.hexdigest())
# mem.now()
# del h
# mem.now()
# ##################

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


while True:
    mem.now()
    G1.low()
    G2.high()
    time.sleep_ms(500)
    G1.high()
    G2.low()
    time.sleep_ms(500)
    