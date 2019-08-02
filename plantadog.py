import serial
import time

port = '/dev/tty.usbmodem54572501'
teensy = serial.Serial(port, 9600, timeout=5)

while True:
    from_teensy = teensy.read_all()
    if from_teensy:
        print(from_teensy)
    time.sleep(100)
    # to write to teensy...
    # teensy.write(bytes("test", ascii))

