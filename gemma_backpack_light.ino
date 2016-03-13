// Version 1.1
// Binary sketch size: 3,830 bytes (of a 5,310 byte maximum)

#include <Adafruit_NeoPixel.h>

// NeoPixels on D0
// Front LED on D1
// Mode change detection on D2
#define PIN 0
#define LED 1
#define SWITCH 2

// Change to how many LEDs in your strand
#define NUM_OF_PIXELS 8

// Used for colour variance in random colour generation
#define WIGGLE 60

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip =
    Adafruit_NeoPixel(NUM_OF_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(SWITCH, INPUT);
  digitalWrite(SWITCH, HIGH);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

uint8_t front_led_iter = 0;
uint8_t colour_mode = 0;

void loop() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {

    // Randomly choose if pixel will be on this round
    if ((rand() % 7) == 0) {

      // Depending on the current mode, prefer certain colours
      switch (colour_mode) {
      case 0:
        strip.setPixelColor(i, skewRainbow());
        break;
      case 1:
        strip.setPixelColor(i, skewRed());
        break;
      case 2:
        strip.setPixelColor(i, skewYellow());
        break;
      case 3:
        strip.setPixelColor(i, skewGreen());
        break;
      case 4:
        strip.setPixelColor(i, skewCyan());
        break;
      case 5:
        strip.setPixelColor(i, skewBlue());
        break;
      case 6:
        strip.setPixelColor(i, skewViolet());
        break;
      case 7:
        // Blink pure white
        strip.setPixelColor(i, 255, 255, 255);
        break;
      }
    } else {
      strip.setPixelColor(i, 0);
    }
  }
  strip.show();

  readSwitch();

  // Keep LED on for 75% time
  if (front_led_iter % 4 == 0) {
    digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, HIGH);
  }
  front_led_iter++;
  delay(100);
}

// Colours unleashed!
uint32_t skewRainbow() {
  return strip.Color(rand() % 256, rand() % 256, rand() % 256);
}

// Try to stick to blue.
uint32_t skewBlue() {
  return strip.Color(rand() % WIGGLE, rand() % WIGGLE, rand() % 100 + 156);
}

// Some sky painting.
uint32_t skewCyan() {
  return strip.Color(rand() % WIGGLE, rand() % 100 + 156, rand() % 100 + 156);
}

// Have a bit more green, please.
uint32_t skewGreen() {
  return strip.Color(rand() % WIGGLE, rand() % 100 + 156, rand() % WIGGLE);
}

// How romantically red.
uint32_t skewRed() {
  return strip.Color(rand() % 100 + 156, rand() % WIGGLE, rand() % WIGGLE);
}

// Get some ultra violet!
uint32_t skewViolet() {
  return strip.Color(rand() % 100 + 156, rand() % WIGGLE, rand() % 100 + 156);
}

// Some lovely daffodils?
uint32_t skewYellow() {
  return strip.Color(rand() % 100 + 156, rand() % 100 + 156, rand() % WIGGLE);
}

// Check if the switch is pressed and change to next mode if so
void readSwitch() {
  // Go to the next mode when the switch is pressed
  if (!digitalRead(SWITCH)) {
    // Cycle back to first mode if at the last mode
    if (colour_mode < 7) {
      colour_mode++;
    } else {
      colour_mode = 0;
    }

    // Indicate switch sense and prevent more detections
    strip.setBrightness(5);
    switch (colour_mode) {
    case 0:
      colourWash(255, 255, 255);
      break;
    case 1:
      colourWash(255, 0, 0);
      break;
    case 2:
      colourWash(255, 255, 0);
      break;
    case 3:
      colourWash(0, 255, 0);
      break;
    case 4:
      colourWash(0, 255, 255);
      break;
    case 5:
      colourWash(0, 0, 255);
      break;
    case 6:
      colourWash(255, 0, 255);
      break;
    case 7:
      colourWash(255, 255, 255);
      break;
    }
    strip.setBrightness(100);
  }
}

// Paint all the LEDs one colour
void colourWash(uint8_t r, uint8_t g, uint8_t b) {
  uint16_t pixel;
  uint32_t colour = strip.Color(r, g, b);

  // Make a bar fill effect
  for (pixel = 0; pixel < NUM_OF_PIXELS; pixel++) {

    // Special case for rainbow colour_mode, fill random colours
    if (colour_mode == 0) {
      strip.setPixelColor(pixel, skewRainbow());
    } else {
      strip.setPixelColor(pixel, colour);
    }
    delay(100);
    strip.show();
  }
}
