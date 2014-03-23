gemma-backpack-light
====================

Tiny Adafruit Gemma backpack light.

# Requirements
* Adafruit Gemma/Trinket
* Adafruit NeoPixels
* Super bright white LED (for front facing light if desired)

# Pins
Currently I have set the following:
* `#define PIN 0` NeoPixels' DATA line on D0
* `#define LED 1` Front facing LED on D1
* `#define SWITCH 2` Mode switching by connecting D2 to GND

# Operation
If you have everything connected up the way I have, then it should work pretty well. You'll notice the onboard red LED blinking when the program runs. If you choose to have a super bright LED connected to D1 then it will blink just like the red LED. I inteded this to mimic a blinky front bike light.

To cycle through the available modes, bridge D2 to GND either with something metal or you can attach a switch. The default modes are:
* Rainbow blinking
* Red variations blinking
* Blue variations blinking
* Green variations blinking
* White blinking
