import Adafruit_BBIO.PWM as PWM
import Adafruit_BBIO.UART as UART
import serial
from time import sleep
#sleep(5)
servo_pin = "P9_14"
UART.setup("UART1")
ser = serial.Serial(port = "/dev/ttyO1", baudrate = 9600)
ser.close()
#minimum duty-cycle for servo control is 1ms i.e. 5% for
50Hz freq
duty_min = 4.5
#maximum duty-cycle for servo control is 2ms i.e. 10%
for 50Hz freq
duty_max = 10.5
duty_span = duty_max - duty_min
#setting the servo at 0 degree initial position
PWM.start(servo_pin, duty_min, 50.0, 0)
ser.open()
if ser.isOpen():
print "Serial is Open"
sleep(5)
#angle = 'q'
while (1):
angle = ser.read(1)
ser.write("DataSent")
if angle == 'x':
	PWM.stop(servo_pin)
PWM.cleanup()
break
angle_f = float(ord(angle))
print("value = ", angle_f, "\r\n")
duty = ((angle_f / 180) * duty_span + duty_min)
PWM.set_duty_cycle(servo_pin, duty)
ser.close()
