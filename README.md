# Plant-A-Dog
Datadog Dashboards on Your Plants

![Plant a Dog in Action](https://github.com/burningion/plantadog/raw/master/images/plantadog.jpg)

## How this works

A Python script ([plantadog.py](https://github.com/burningion/plantadog/blob/master/plantadog.py)) runs in a loop, checking Datadog for hosts up, a monitor's status, and for any new events.

If there are any, it changes some Adafruit NeoPixel rings, and makes them animate so you can see what's happening.

I ran out of time, but the plants are connected to touch sensors. I planned on using this to silence (turn off) the lights, or to turn them on for checking the status of our systems.
