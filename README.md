gemma-backpack-light
====================

Tiny blinking Adafruit GEMMA/Trinket backpack light, mainly made for biking. I mainly wanted to avoid using the typical low cost blinky bike lights that clip on and require batteries that typically don't come in rechargeable form. This design is focused on attaching a microcontroller to my backpack that I already have with me everyday. I used the Adafruit GEMMA for developing, but you should be able to drop in an Adafruit Trinket instead if you want, just be mindful of which voltage logic you buy in the event you modify the code and start using inputs.

The bright white LED is optional, but I figured while there's a power source nearby already I should hook that in too. I'm using it as a front facing light that's powerful enough to illuminate the path and blink harsh enough for drivers to see me.

# Requirements
* Adafruit GEMMA (http://www.adafruit.com/products/1222)
* Flora RGB Smart NeoPixels version 2 (http://www.adafruit.com/products/1260)
* 1 Watt Cool White LED (http://www.adafruit.com/products/518)

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
