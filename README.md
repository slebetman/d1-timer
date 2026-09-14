# D1 Timer

Simple electronic timer for ESC configurable via Wifi.

## Operation

The timer should be connected to an ESC and is powered via the ESC's built-in BEC.

When connected to the battery the timer will first blink rapidly before enabling
the button. This is to allow the ESC to initialise.

Clicking the button starts the timer. When the timer is running it will blink
slowly until the timer stops.

Clicking the button **while** the timer is running will stop the timer immediately.
Use this if you decide to cancel your launch/takeoff.

## ESC Calibration

If press and hold the button while applying power to the timer it will start with
the throttle at **maximum** value. Releasing the button will return the throttle
to its **minimum** value. Most ESCs can be calibrated this way.

Wait until you hear your ESC's calibration tune before releasing the button.

## Configuring the Timer

The timer acts as a Wifi access point. You can connect to the timer as a wifi.
The timer's SSID is **"TIMER_xxxxx"** where *"x"* are numbers. For example the
timer may appear as "TIMER_00016".

Once you've connected to the timer you can access the settings with your web
browser by browsing to **"http://192.168.0.1"**.
