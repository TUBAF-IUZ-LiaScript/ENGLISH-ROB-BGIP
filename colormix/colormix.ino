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
