import Adafruit_BBIO.ADC as ADC
import Adafruit_BBIO.UART as UART
import serial
import time
UART.setup("UART1")
ser = serial.Serial(port = "/dev/ttyO1",baudrate = 9600)
ser.close()
ser.open()
if ser.isOpen():
print "Serial is open!"
ADC.setup()
value = []
for i in range(32):
a = int(ADC.read_raw("P9_40"))
import sys
high = int('{0:016b}'.format(a)[:8],2)
low = int('{0:016b}'.format(a)[8:],2)
print(a,high,low)
#value = ADC.read_raw("AIN1")
value.append(high)
value.append(low)
print(value)
#ser.write(value)
#value.pop()
#value.pop()
time.sleep(0.5)
while (1):
print("sending....")
print(value)
str1 = ser.read(11)
ser.write(value)
str2 = ser.read(8)
print(str1)
print(str2)
time.sleep(0.1)
ser.close()