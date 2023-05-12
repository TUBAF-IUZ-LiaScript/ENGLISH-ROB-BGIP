<!--

author:   Björn Schnabel, Marvin Ohlmeyer
email:    
version:  0.1.0
language: EN
narrator: US English Female Female

-->

[![LiaScript](https://raw.githubusercontent.com/LiaScript/LiaScript/master/badges/course.svg)](https://liascript.github.io/course/?https://raw.github.com/Kerbaltec-Solutions/ENGLISH-ROB-BGIP/colormix/colormix.md)

# Simulation

## Explanation

The file colormix is a simple programm, that uses two different colors to create a mixed color. 

The two colors are filled in from the left and the right side.
The values of these colors are randomly chosen by random8, a function that creates pseudorandom 8bit values.

These values are the hue in the HSV colorspectrum, 
which determines the random colors. Once the colors are filled in from the left and the right side and they touch in the middle, 

the mixed color is determined through average mixing. 

Then the fill color fills the LEDs outwards from the middle and the LED strip resets once it's fully filled. Then the code will loop indefinetly.  

## Video

!?[video](https://youtu.be/PGe-OgqjDAM)

## Working simulation

<div id="matrix-experiment">
<wokwi-neopixel-matrix pin="6" cols="9" rows="1"></wokwi-neopixel-matrix>
<span id="simulation-time"></span>
</div>

```cpp             Automata
#include "FastLED.h"
#define DATA_PIN 6
#define BRIGHTNESS 180
#define NUM_LEDS 12

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

CRGB random_color() {
  return CHSV(random8(), 255, 255);
}

void fill_leds_simultaneously(CRGB color_left, CRGB color_right, int delay_ms) {
  for (int i = 0; i < NUM_LEDS / 2; i++) {
    leds[i] = color_left;
    leds[NUM_LEDS - 1 - i] = color_right;
    FastLED.show();
    delay(delay_ms);
  }
}

CRGB average_mix(CRGB color1, CRGB color2) {
  CRGB combined_color;
  combined_color.r = (color1.r + color2.r) / 2;
  combined_color.g = (color1.g + color2.g) / 2;
  combined_color.b = (color1.b + color2.b) / 2;
  return combined_color;
}

void fill_combined_color(CRGB color_left, CRGB color_right, int delay_ms) {
  CRGB combined_color = average_mix(color_left, color_right);
  for (int i = 0; i < NUM_LEDS / 2; i++) {
    leds[NUM_LEDS / 2 - i - 1] = combined_color;
    leds[NUM_LEDS / 2 + i] = combined_color;
    FastLED.show();
    delay(delay_ms);
  }
}

void loop() {
  CRGB color_left = random_color();
  CRGB color_right = random_color();
  
  fill_leds_simultaneously(color_left, color_right, 250);
  fill_combined_color(color_left, color_right, 250);
  
  FastLED.clear();
  FastLED.show();
  delay(1000);
}

```
@AVR8js.sketch(matrix-experiment)
