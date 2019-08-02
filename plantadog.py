import serial
import time

from datadog import initialize, api

# reads environment variables for
# DD_API_KEY and DD_APP_KEY
initialize()

# initialize serial port... you'll probably change this
port = '/dev/tty.usbmodem54572501'
teensy = serial.Serial(port, 9600, timeout=5)

while True:
    # first, see if the teensy has said anything
    from_teensy = teensy.read_all()
    if from_teensy:
        print(from_teensy)
    time.sleep(100)
    # to write to teensy...
    # will do for an event posted to DD
    # teensy.write(bytes("test", ascii))

