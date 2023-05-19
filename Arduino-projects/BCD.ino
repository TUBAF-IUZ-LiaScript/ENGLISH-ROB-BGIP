#include "FastLED.h"
#define DATA_PIN 6
#define BRIGHTNESS 180
#define NUM_LEDS 12
uint8_t num = 0;

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void writeLeds(uint32_t input) {
    memset(leds, 0x0, sizeof(CRGB) * NUM_LEDS);
    for (int i = 0; i < NUM_LEDS; i++) {
        if(input & (1 << (NUM_LEDS - i - 1))) {
            leds[i] = CRGB::White;
        };
    }
    FastLED.show();
}

void dabble(uint32_t* input, int offset) {
    uint32_t temp = *input >> offset;
    temp &= 15;

    if(temp > 4) temp += 3;

    *input &= ~(15 << offset);
    *input |= temp << offset;
}

void loop() {
    num += 31415962 / num;
    uint32_t workingVar = num;
    
    writeLeds(workingVar);
    delay(5000);

    workingVar = workingVar << 1;
    for(int i = 0; i < 7; i++) {
        // dabble
        dabble(&workingVar, 8);
        dabble(&workingVar, 12);
        dabble(&workingVar, 16);

        // display 1
        writeLeds(workingVar >> 8);
        delay(500);

        // double
        workingVar = workingVar << 1;

        // display 2
        writeLeds(workingVar >> 8);
        delay(500);
    }

    for(int i = 0; i < NUM_LEDS; i++) {
        if(leds[i] != CRGB::Black) {
            if( i < 4)     leds[i] = CRGB::Red;
            else if(i > 7) leds[i] = CRGB::Blue;
            else           leds[i] = CRGB::Green;
        }
    }
    FastLED.show();
    delay(10000);
}
