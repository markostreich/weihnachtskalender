#ifndef GRAPHICS_LEO
#define GRAPHICS_LEO

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

#define NUMPIXELS 256

/* LED Data Pin */
#define PIN 6

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint16_t brightness = 10;

const boolean startLeft = true;
const uint8_t size_x = 16;
const uint8_t size_y = 16;
const uint8_t size_x_h = size_x / 2;
const uint8_t size_y_h = size_y / 2;

  void drawPixel(int8_t x, int8_t y, uint8_t red, uint8_t green, uint8_t blue) {
    if (x >= size_x || y >= size_y || x < 0 || y < 0)
      return;
    int8_t delta_x = x > size_x_h - 1 ? size_x_h * size_y_h : 0;
    int8_t delta_y = y > size_y_h - 1 ? size_x_h * size_y_h - 8 : 0;
    pixels.setPixelColor(size_y_h * x + y + delta_x + delta_y, pixels.Color(red, green, blue));
  }

  void drawRotatedPixel(int8_t x, int8_t y, float rot_x, float rot_y, float cosTau, float sinTau, uint8_t red, uint8_t green, uint8_t blue) {
    float new_x = rot_x + cosTau * ((float)x - rot_x) + sinTau * ((float)y - rot_y);
    float new_y = rot_y - sinTau * ((float)x - rot_x) + cosTau * ((float)y - rot_y);
    drawPixel((int8_t)(new_x + 0.5), (int8_t)(new_y + 0.5), red, green, blue);
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

  void colorAll(uint8_t red, uint8_t green, uint8_t blue) {
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

void bright() {
  pixels.setBrightness(brightness);
}
#endif  // GRAPHICS_LEO