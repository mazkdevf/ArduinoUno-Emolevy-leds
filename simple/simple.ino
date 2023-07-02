// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 2  // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 10  // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// NeoPixel brightness, 0 (min) to 255 (max)
/* #define BRIGHTNESS 30  // Set BRIGHTNESS to about 1/5 (max = 255) */

#define DELAYVAL 3000  // Time (in milliseconds) to pause between pixels

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
}    

/* void loop() {
  pixels.clear();

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 255)); 
    pixels.show();
  }


  for (int i = 0; i < NUMPIXELS; i++) {
    delay(300);
    pixels.setPixelColor(i, pixels.Color(255, 0, 0)); 
    pixels.show();

    delay(200); 
  }
}
 */

#define TRANSITION_TIME 750 // 1200 mazkin favo

void loop() {
  static unsigned long transitionStartTime = 0;
  static int currentPixel = 0;
  static bool isTransitioning = false;

  if (!isTransitioning) {
    pixels.clear();
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 255, 255));
    }
    pixels.show();


    if (millis() - transitionStartTime >= TRANSITION_TIME) {
      transitionStartTime = millis();
      currentPixel = 2;
      isTransitioning = true;
    }
  } else {
    /*     int red = map(millis() - transitionStartTime, 255, TRANSITION_TIME, 255, 0);
    int green = 0;
    int blue = 255; */

    int red = 255;
    int green = map(millis() - transitionStartTime, 255, TRANSITION_TIME, 255, 0);
    int blue = 0;

    pixels.setPixelColor(currentPixel, pixels.Color(red, green, blue));
    pixels.show();

    if (millis() - transitionStartTime >= TRANSITION_TIME) {
      currentPixel++;
      if (currentPixel >= NUMPIXELS) {
        isTransitioning = false;
      } else {
        transitionStartTime = millis();
      }
    }
  }
}
