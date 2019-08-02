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
    time.sleep(1)

    # get number of hosts running
    total_hosts = api.Hosts.totals()
    print(total_hosts['total_up'])
    teensy.write(bytes(f"@T{total_hosts['total_up']:02}", 'ascii'))

    # get if any events have occurred in past 10 mins
    end_time = time.time()
    start_time = end_time - (60 * 10)
    events = api.Event.query(start=start_time,
                             end=end_time)
    teensy.write(bytes(f"@E{len(events['events']):02}", 'ascii'))

    # see if our monitor triggered
    mon = api.Monitor.get(10780655, group_states='alert')
    print(mon['overall_state'])
    if mon['overall_state'] == 'OK':
        teensy.write(bytes('@M01', 'ascii'))
    else:
        teensy.write(bytes('@M00', 'ascii'))
    time.sleep(5)
    print("Looping... ")
