#include "Letter.h"
#include "Symbols.h"

#define DELAYVAL 100  // Time (in milliseconds) to pause between pixels

#define CHAR_WIDTH 5
#define CHAR_HEIGHT 5

void setup() {
  Serial.begin(9600);
  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();
  bright();
  pixels.show();
  fillSnowFall();
  clearSnowLand();
}

int8_t start_x = 30;
int8_t start_y = 6;
void loop() {

  printSnowfall();
  /*  printWeihnachten();
    pixels.clear();
  printKerze(0);
  printKerze(8);
  printKerze(16);
  printKerze(24);
  for (int8_t i = 0; i < 7; ++i) {
    printKerzeFlackern(0);
  }*/
  /*  for (uint8_t i = 0; i < 10; ++i) {
    int8_t x1 = random(-15, 15);
    int8_t x2 = random(-15, 15);
    int8_t x3 = random(-15, 15);
    int8_t x4 = random(-15, 15);
    uint8_t red = random(256);
    uint8_t green = random(256);
    uint8_t blue = random(256);
    int8_t y2 = random(-10, 3);
    int8_t y3 = random(-5, 5);
    int8_t y4 = random(-15, 15);
    for (int8_t y = -25; y < 25; ++y) {
    pixels.clear();
    printKelchHostie(x1, y, red, green, blue);
    printKelchHostie(x2, y + y2, red + 75, green -75, blue - 60);
    printKelchHostie(x3, y + y3, red + 50, green + 50, blue - 50);
    printKelchHostie(x4, y + y4, red + 50, green - 50, blue - 50);
    pixels.show();
    delay(110);
  }
  }
  delay(2000);
  printWeihnachten();
  printShip();*/
  /*printWeihnachten();
  printKelch();*/
}

void printKerze(const int8_t x_pos) {
  uint8_t red = 200;
  uint8_t green = 5;
  uint8_t blue = 0;
  for (int8_t y = 0; y < 14; ++y)
    for (int8_t x = x_pos; x < x_pos + 5; ++x)
      drawPixel(x, y, red, green, blue);
  red = 30;
  green = 10;
  blue = 0;
  drawPixel(x_pos + 2, 14, red, green, blue);
  drawPixel(x_pos + 2, 15, red, green, blue);
  red = 200;
  green = 200;
  blue = 0;
  /*drawPixel(x_pos + 2, 15, red, green, blue);
  for (int8_t x = x_pos + 1; x < x_pos + 4; ++x)
    drawPixel(x, 16, red, green, blue);
  drawPixel(x_pos + 2, 17, red, green, blue);
  drawPixel(x_pos + 3, 17, red, green, blue);
  drawPixel(x_pos + 2, 18, red, green, blue);*/
  bright();
  pixels.show();
}

void printSnowfall() {
  for (uint8_t i = 0; i < 10; ++i) {
    pixels.clear();
    printSnowfallStayInternal();
    printSnowLand();
    bright();
    pixels.show();
    delay(130);
  }
}

void printSnowfallInternal() {
  for (uint8_t i = 0; i < AMOUNT_SNOWFLAKES - 1; i += 2) {
    if (snow_fall[i + 1] == 0) {
      snow_fall[i] = random(40);
      snow_fall[i + 1] = random(20, 40);
    }
    snow_fall[i] = random(4) == 3 ? snow_fall[i] + 1 : snow_fall[i] - 1;
    snow_fall[i + 1] -= 1;
    drawPixel(snow_fall[i], snow_fall[i + 1], 150, 150, 150);
  }
}

void printSnowfallStayInternal() {
  for (uint8_t i = 0; i < AMOUNT_SNOWFLAKES - 1; i += 2) {
    if (snow_fall[i + 1] == 0) {
      snow_fall[i] = random(50);
      snow_fall[i + 1] = random(20, 40);
    }
    int8_t new_x = random(4) == 3 ? snow_fall[i] + 1 : snow_fall[i] - 1;
    int8_t new_y = snow_fall[i + 1] - 1;

    uint8_t value = getSnowLand(new_x, new_y);

    if (value >= SNOW_BORDER) {
      uint8_t value_old = getSnowLand(snow_fall[i], snow_fall[i + 1]);
      setSnowLand(snow_fall[i], snow_fall[i + 1], value_old + 1);
      setSnowLand(new_x, new_y - 1, SNOW_BORDER);
      setSnowLand(new_x - 1, new_y - 1, SNOW_BORDER);
      setSnowLand(new_x + 1, new_y - 1, SNOW_BORDER);
      new_x = random(50);
      new_y = random(20, 40);
    } else if (value > 0 || new_y == 0) {
      setSnowLand(new_x, new_y, value + 1);
    }
    snow_fall[i] = new_x;
    snow_fall[i + 1] = new_y;
    drawPixel(snow_fall[i], snow_fall[i + 1], 150, 150, 150);
  }
}

void printWeihnachten() {
  int8_t start_x = 30;
  int8_t start_y = 6;
  uint8_t red = random(256);
  uint8_t green = random(256);
  uint8_t blue = random(256);
  while (start_x > -90) {
    pixels.clear();
    //printHerzen(red, green, blue);
    printLetter(letter_S, start_x, start_y, 255, 0, 0);
    printLetter(letter_c, start_x + 6, start_y, 0, 255, 0);
    printLetter(letter_h, start_x + 12, start_y, 255, 255, 255);
    printLetter(letter_oe, start_x + 18, start_y, 255, 0, 0);
    printLetter(letter_n, start_x + 24, start_y, 0, 255, 0);
    printLetter(letter_e, start_x + 30, start_y, 255, 255, 255);
    printLetter(letter_n, start_x + 36, start_y, 255, 0, 0);
    printLetter(letter_1_Punkt, start_x + 44, start_y, 0, 255, 0);
    printLetter(letter_A, start_x + 52, start_y, 255, 255, 255);
    printLetter(letter_d, start_x + 58, start_y, 255, 0, 0);
    printLetter(letter_v, start_x + 64, start_y, 0, 255, 0);
    printLetter(letter_e, start_x + 70, start_y, 255, 255, 255);
    printLetter(letter_n, start_x + 76, start_y, 255, 0, 0);
    printLetter(letter_t, start_x + 81, start_y, 0, 255, 0);

    /*printLetter(letter_W, start_x, start_y, 255, 0, 0);
    printLetter(letter_e, start_x + 8, start_y, 250, 51, 0);
    printLetter(letter_i, start_x + 10, start_y, 250, 127, 0);
    printLetter(letter_h, start_x + 16, start_y, 0, 250, 0);
    printLetter(letter_n, start_x + 22, start_y, 250, 127, 0);
    printLetter(letter_a, start_x + 28, start_y, 250, 51, 0);
    printLetter(letter_c, start_x + 34, start_y, 250, 51, 0);
    printLetter(letter_h, start_x + 40, start_y, 0, 250, 0);
    printLetter(letter_t, start_x + 45, start_y, 0, 250, 0);
    printLetter(letter_e, start_x + 51, start_y, 250, 51, 0);
    printLetter(letter_n, start_x + 57, start_y, 250, 127, 0);
    printLetter(letter_y, start_x + 24, start_y, 0, 0, 250 );
    printLetter(letter_B, start_x + 36, start_y, 255, 0, 0);
    printLetter(letter_i, start_x + 42, start_y, 250, 51, 0);
    printLetter(letter_r, start_x + 48, start_y, 250, 127, 0);
    printLetter(letter_t, start_x + 54, start_y, 0, 250, 0);
    printLetter(letter_h, start_x + 60, start_y, 0, 0, 250 );
    printLetter(letter_d, start_x + 66, start_y, 70, 0, 250);
    printLetter(letter_a, start_x + 72, start_y, 70, 0, 250);
    printLetter(letter_y, start_x + 78, start_y, 70, 0, 250);
    printLetter(letter_Komma, start_x + 84, start_y, 70, 0, 250);
    printLetter(letter_H, start_x + 90, start_y, 255, 0, 0);
    printLetter(letter_a, start_x + 96, start_y, 250, 51, 0);
    printLetter(letter_n, start_x + 102, start_y, 250, 127, 0);
    printLetter(letter_n, start_x + 108, start_y, 0, 250, 0);
    printLetter(letter_a, start_x + 114, start_y, 0, 0, 250 );
    printLetter(letter_h, start_x + 120, start_y, 70, 0, 250);*/
    start_x--;
    bright();
    pixels.show();
    delay(DELAYVAL);
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

void printHerzen(uint8_t red, uint8_t green, uint8_t blue) {
  printLetter(letter_Herz, 0, 12, red, green, blue);
  printLetter(letter_Herz, 23, 12, red, green, blue);
  printLetter(letter_Herz, 0, -2, red, green, blue);
  printLetter(letter_Herz, 23, -2, red, green, blue);
}
