SERIAL_PORT = "COM11"
BAUD_RATE = 9600
import serial
sp = serial.Serial(SERIAL_PORT,BAUD_RATE, timeout = 5)
sp.flush()

response = sp.read(1)
print(type(response), repr(response))
