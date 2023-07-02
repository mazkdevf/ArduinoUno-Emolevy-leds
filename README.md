# ArduinoUno-Emolevy-leds

```cpp
#include <Adafruit_NeoPixel.h>
#ifdef AVR
#include <avr/power.h>
#endif

#define PIN 2
#define NUMPIXELS 10
Adafruit_NeoPixel pikselit(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
#if defined(AVR_ATtiny85) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pikselit.begin();
}

#define SIIRTYMISAIKA 1200

void loop()
{
  static unsigned long siirtymisenAlkuaika = 0;
  static int nykyinenPikseli = 0;
  static bool onkoSiirtymassa = false;

  if (!onkoSiirtymassa)
  {
    pikselit.clear();
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pikselit.setPixelColor(i, pikselit.Color(255, 255, 255));
    }
    pikselit.show();

    if (millis() - siirtymisenAlkuaika >= SIIRTYMISAIKA)
    {
      siirtymisenAlkuaika = millis();
      nykyinenPikseli = 2;
      onkoSiirtymassa = true;
    }
  }
  else
  {
    int punainen = 255;
    int vihreä = map(millis() - siirtymisenAlkuaika, 255, SIIRTYMISAIKA, 255, 0);
    int sininen = 0;

    pikselit.setPixelColor(nykyinenPikseli, pikselit.Color(punainen, vihreä, sininen));
    pikselit.show();

    if (millis() - siirtymisenAlkuaika >= SIIRTYMISAIKA)
    {
      nykyinenPikseli++;
      if (nykyinenPikseli >= NUMPIXELS)
      {
        onkoSiirtymassa = false;
      }
      else
      {
        siirtymisenAlkuaika = millis();
      }
    }
  }
}
```

![image](https://github.com/mazkdevf/ArduinoUno-Emolevy-leds/assets/79049205/39425a57-bf8e-421b-af54-f8b208f2c3da)
