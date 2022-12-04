#ifndef GRAPHICS_CALENDAR
#define GRAPHICS_CALENDAR

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define NUMPIXELS 600

/* LED Data Pin */
#define PIN 42
/* LED Potentiometer */
#define POT A8

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint16_t brightness = 0;

const boolean startLeft = true;
const uint8_t size_x = 30;
const uint8_t size_y = 20;

void drawPixel(int8_t x, int8_t y, uint8_t red, uint8_t green, uint8_t blue) {
  if (x >= size_x || y >= size_y || x < 0 || y < 0)
    return;
  int8_t pos_x;
  if (startLeft) {
    pos_x = y % 2 == 0 ? x : size_x - 1 - x;
  } else {
    pos_x = y % 2 == 1 ? x : size_x - 1 - x;
  }
  pixels.setPixelColor(pos_x + size_x * y, pixels.Color(red, green, blue));
}

void printLetter(byte letter[], int8_t x, int8_t y, uint8_t red, uint8_t green, uint8_t blue) {
  for (int letter_y = 0; letter_y < 7; ++letter_y) {
    for (int letter_x = 0; letter_x < 8; ++letter_x) {
      if (bitRead(letter[(6 - letter_y)], 7 - letter_x))
        drawPixel(x + letter_x, y + letter_y, red, green, blue);
    }
  }
}

void printObject(byte object[], int8_t height, int8_t x, int8_t y, uint8_t red, uint8_t green, uint8_t blue) {
  for (int8_t object_y = 0; object_y < size_y; ++object_y) {
    for (int8_t object_x = 0; object_x < 8; ++object_x) {
      if (bitRead(object[(6 - object_y)], 7 - object_x))
        drawPixel(x + object_x, y + object_y, red, green, blue);
    }
  }
}

void bright() {
  /* Set Brightness with potentiometer */
  uint16_t potentioVal = analogRead(POT);
  uint16_t brightnessNew = map(potentioVal, 0, 1023, 1, 255);
  //Serial.print("potentio: ");
  //Serial.println(brightnessNew);
  if (brightness - 1 > brightnessNew || brightness + 1 < brightnessNew) { //tolerate minmal differences
    brightness = brightnessNew;
    pixels.setBrightness(brightness);
    //Serial.println("show");
    pixels.show();
  }
}

void colorAll(uint8_t red, uint8_t green, uint8_t blue) {
  bright();
  for (int8_t y = 0; y < size_y; ++y)
    for (int8_t x = 0; x < size_x; ++x)
      drawPixel(x, y, red, green, blue);
}

void colorBackground() {
  uint8_t red = 5;
  uint8_t green = 5;
  uint8_t blue = 5;
  colorAll(red, green, blue);
}
#endif // GRAPHICS_CALENDAR