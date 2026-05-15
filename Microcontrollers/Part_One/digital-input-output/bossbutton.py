XKCD = "http://xkcd.com/353/"
SERIAL_PORT = "COM11"
BAUD_RATE = 9600
import serial
import webbrowser

sp = serial.Serial(SERIAL_PORT,BAUD_RATE, timeout = 5)
sp.flush()
while(1): #sit and wait forever
    response = sp.read(1) #get one byte
    if response == b"0":
        print("got OK byte. waiting for button press!")
    elif response == b"X":
        print("Got boss byte! Alarm!")
        webbrowser.open(XKCD)
    else:
        print("got nothing....still waiting....")