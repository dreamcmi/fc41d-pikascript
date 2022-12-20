import PikaStdLib
import PikaStdDevice as std
import FC41D

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

while True:
    mem.now()
    G1.low()
    G2.high()
    time.sleep_ms(500)
    G1.high()
    G2.low()
    time.sleep_ms(500)
    