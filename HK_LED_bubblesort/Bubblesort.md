# Bubblesort on a Strip of 12 LEDs
## The Programm
1. It fills the strip randomly with 5 different colors
2. Starts the Bubblesort and orders the colors according to values assingend to them
3. In the end the strip shows the color in order and starts all over again

## The Code
<div id="matrix-experiment">
<wokwi-neopixel-matrix pin="6" cols="9" rows="1"></wokwi-neopixel-matrix>
<span id="simulation-time"></span>
</div>

``´HK_LED_bubblesort.cpp             Automata
#include <Arduino.h>
#include "FastLED.h"
#define DATA_PIN 6
#define BRIGHTNESS 180
#define NUM_LEDS 12
#define NUM_COLORS 6
int i = 0;
CRGB leds[NUM_LEDS];
CRGB colors[] = {CRGB:: Black, CRGB::Purple, CRGB::Blue , CRGB::Green,  CRGB::Yellow , CRGB::Red};
int sort[NUM_LEDS];

void led_colorval(int* array, CRGB* colors ){
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = colors[sort[i]];
  }
}

void bubbleSort (int* array, int leng){
    int j = 0;
    int swapped = 0;
    for(int fertig = 0; fertig< leng; fertig ++){
        for(int i = leng-1; i> fertig; i--){
            if(array[i-1]> array[i]){
                int tmp = array[i];
                array[i]=array[i-1];
                array[i-1]= tmp;
                swapped = 1;
                delay(250); 
                led_colorval(array, colors);
                FastLED.show(); 

            }
        }
        delay(300);
        if(!swapped) return;
        swapped = 0;
    }
}

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  for(int i = 0; i<NUM_LEDS; i++){
    sort[i] = rand() % (NUM_COLORS -1) +1;
  }
  led_colorval(sort, colors);
  FastLED.show();
  delay(1500);

  bubbleSort( sort, NUM_LEDS);

  delay(2000);

}
```
@AVR8js.sketch(matrix-experiment)
