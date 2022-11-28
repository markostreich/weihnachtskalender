#include <Adafruit_NeoPixel.h>
#include "Letter.h"
#include "Symbols.h"
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define NUMPIXELS 600

/* LED Data Pin */
#define PIN 42
/* LED Potentiometer */
#define POT A8

#define DELAYVAL 100 // Time (in milliseconds) to pause between pixels

#define CHAR_WIDTH 5
#define CHAR_HEIGHT 5

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint16_t brightness = 0;

const boolean startLeft = true;
const uint8_t size_x = 30;
const uint8_t size_y = 20;


void setup() {
  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
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
    printSnowLand();
    printSnowfallInternal();
    bright();
    pixels.show();
    delay(150);
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
      snow_fall[i] = random(40);
		  snow_fall[i + 1] = random(20, 40);
    }
    int8_t new_x = random(4) == 3 ? snow_fall[i] + 1 : snow_fall[i] - 1;
    int8_t new_y = snow_fall[i + 1] - 1;

    uint8_t value = getSnowLand(new_x, new_y);
    if (value > 0 || new_y == 0) {
      setSnowLand(new_x, new_y, value + 1);
    }
    if (value + 1 < 2) {
      snow_fall[i] = new_x;
		  snow_fall[i + 1] = new_y;
		  drawPixel(snow_fall[i], snow_fall[i + 1], 150, 150, 150);
    }
	}
}

uint8_t getSnowLand(const int8_t x, const int8_t y) {
  if (x >= size_x || y >= size_y || x < 0 || y < 0)
    return 0;
  int8_t pos_x;
  if (startLeft) {
    pos_x = y % 2 == 0 ? x : size_x - 1 - x;
  } else {
    pos_x = y % 2 == 1 ? x : size_x - 1 - x;
  }
  return snow_land[pos_x + size_x * y];
}

void setSnowLand(const int8_t x, const int8_t y, int8_t value) {
  if (x >= size_x || y >= size_y || x < 0 || y < 0)
    return;
  int8_t pos_x;
  if (startLeft) {
    pos_x = y % 2 == 0 ? x : size_x - 1 - x;
  } else {
    pos_x = y % 2 == 1 ? x : size_x - 1 - x;
  }
  snow_land[pos_x + size_x * y] = value;
}

void printSnowLand() {
  for (uint16_t i = 0; i < 600 - 1; i += 2) {
		if (snow_land[i] >= 5)
      pixels.setPixelColor(i, pixels.Color(150, 150, 150));
	}
}

void printKerzeFlackern(const int8_t x_pos) {
  int8_t red = 200;
  int8_t green = 200;
  int8_t blue = 0;
  uint16_t delayVal = 500;

  drawPixel(x_pos + 2, 15, red, green, blue);
  for (int8_t x = x_pos + 1; x < x_pos + 4; ++x)
    drawPixel(x, 16, red, green, blue);
  drawPixel(x_pos + 2, 17, red, green, blue);
  drawPixel(x_pos + 3, 17, red, green, blue);
  drawPixel(x_pos + 2, 18, red, green, blue);
  drawPixel(x_pos + 1, 18, 0, 0, 0);
  drawPixel(x_pos + 1, 17, 0, 0, 0);
  drawPixel(x_pos + 3, 18, 0, 0, 0);
    bright();
  pixels.show();
  delay(delayVal);
  drawPixel(x_pos + 1, 16, 0, 0, 0);
  drawPixel(x_pos + 2, 18, 0, 0, 0);
  drawPixel(x_pos + 3, 18, red, green, blue);
    bright();
  pixels.show();
  delay(delayVal * 2);
  drawPixel(x_pos + 2, 15, red, green, blue);
  for (int8_t x = x_pos + 1; x < x_pos + 4; ++x)
    drawPixel(x, 16, red, green, blue);
  drawPixel(x_pos + 2, 17, red, green, blue);
  drawPixel(x_pos + 3, 17, red, green, blue);
  drawPixel(x_pos + 2, 18, red, green, blue);
  drawPixel(x_pos + 3, 18, 0, 0, 0);
    bright();
  pixels.show();
  delay(delayVal);
  drawPixel(x_pos + 3, 17, 0, 0, 0);
  drawPixel(x_pos + 3, 16, 0, 0, 0);
  drawPixel(x_pos + 2, 18, 0, 0, 0);
  drawPixel(x_pos + 1, 18, red, green, blue);
  drawPixel(x_pos + 1, 17, red, green, blue);
  drawPixel(x_pos + 1, 16, red, green, blue);
    bright();
  pixels.show();
  delay(delayVal * 2);
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
  printLetter(letter_Herz, 0, -2,  red, green, blue);
  printLetter(letter_Herz, 23, -2, red, green, blue);
}

void printKreuz() {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint16_t delayVal = 75;
  pixels.clear();
  for (int8_t i = 0; i < 6; ++i) {
    switch (i) {
      case 0:
        red = 255;
        green = 0;
        blue = 0;
        break;
      case 1:
        red = 250;
        green = 51;
        blue = 0;
        break;
      case 2:
        red = 250;
        green = 127;
        blue = 0;
        break;
      case 3:
        red = 0;
        green = 255;
        blue = 0;
        break;
      case 4:
        red = 0;
        green = 0;
        blue = 255;
        break;
      case 5:
        red = 70;
        green = 0;
        blue = 255;
        break;
      default:
        red = 255;
        green = 0;
        blue = 0;
        break;
    }
    for (int8_t y = 0; y < 10; ++y) {
      for (int8_t x = 14; x < 18; ++x)
        drawPixel(x, y, red, green, blue);
    bright();
      pixels.show();
      delay(delayVal);
    }
    for (int8_t y = 10; y < 14; ++y) {
      for (int8_t x = 10; x < 22; ++x)
        drawPixel(x, y, red, green, blue);
    bright();
      pixels.show();
      delay(delayVal);
    }
    for (int8_t y = 14; y < 18; ++y) {
      for (int8_t x = 14; x < 18; ++x)
        drawPixel(x, y, red, green, blue);
    bright();
      pixels.show();
      delay(delayVal);
    }
    delay(500);
  }
  /* lila */
  red = 72;
  green = 0;
  blue = 255;
  for (int8_t y = 0; y < 3; ++y) {
    for (int8_t x = 14; x < 18; ++x)
      drawPixel(x, y, red, green, blue);
    bright();
    pixels.show();
    delay(delayVal);
  }
  /* blau */
  red = 0;
  green = 0;
  blue = 255;
  for (int8_t y = 3; y < 6; ++y) {
    for (int8_t x = 14; x < 18; ++x)
      drawPixel(x, y, red, green, blue);
    bright();
    pixels.show();
    delay(delayVal);
  }
  /* gruen */
  red = 0;
  green = 255;
  blue = 0;
  for (int8_t y = 6; y < 9; ++y) {
    for (int8_t x = 14; x < 18; ++x)
      drawPixel(x, y, red, green, blue);
    bright();
    pixels.show();
    delay(delayVal);
  }
  /* gelb */
  red = 250;
  green = 127;
  blue = 0;
  for (int8_t x = 14; x < 18; ++x)
    drawPixel(x, 9, red, green, blue);
    bright();
  pixels.show();
  delay(delayVal);
  for (int8_t y = 10; y < 12; ++y) {
    for (int8_t x = 10; x < 22; ++x)
      drawPixel(x, y, red, green, blue);
    bright();
    pixels.show();
    delay(delayVal);
  }
  /* orange */
  red = 250;
  green = 51;
  blue = 0;
  for (int8_t y = 12; y < 14; ++y) {
    for (int8_t x = 10; x < 22; ++x)
      drawPixel(x, y, red, green, blue);
    bright();
    pixels.show();
    delay(delayVal);
  }
  for (int8_t x = 14; x < 18; ++x)
    drawPixel(x, 14, red, green, blue);
    bright();
  pixels.show();
  delay(delayVal);
  /* rot */
  red = 255;
  green = 0;
  blue = 0;
  for (int8_t y = 15; y < 18; ++y) {
    for (int8_t x = 14; x < 18; ++x)
      drawPixel(x, y, red, green, blue);
    bright();
    pixels.show();
    delay(delayVal);
  }
  delay(3000);
}

void printKelch() {
  pixels.clear();
  /* Hostie */
  for (int8_t y = 19; y > 7; --y) {
    pixels.clear();
//    printKelchHostie(y);
    pixels.show();
    delay(70);
  }
    bright();
  pixels.show();
  delay(1000);
  /* Kelch */
  for (int8_t y = -9; y < 2; ++y) {
    pixels.clear();
//    printKelchHostie(8);
    printKelchKelch(y);
    bright();
    pixels.show();
    delay(70);
  }
  delay(1000);
  /* Kreuz */
  printKelchKreuz();
    bright();
  pixels.show();

  delay(4000);
}

void printKelchKelch(int8_t y) {
  uint8_t red = 200;
  uint8_t green = 51;
  uint8_t blue = 0;
  for (int8_t x = 10; x < 21; ++x)
    drawPixel(x, y, red, green, blue);
  for (int8_t x = 11; x < 20; ++x)
    drawPixel(x, y + 1, red, green, blue);
  for (int8_t x = 12; x < 19; ++x)
    drawPixel(x, y + 2, red, green, blue);
  for (int8_t x = 13; x < 18; ++x) {
    drawPixel(x, y + 3, red, green, blue);
    drawPixel(x, y + 4, red, green, blue);
  }
  for (int8_t x = 12; x < 19; ++x)
    drawPixel(x, y + 5, red, green, blue);
  for (int8_t x = 10; x < 21; ++x)
    drawPixel(x, y + 6, red, green, blue);
  for (int8_t x = 9; x < 22; ++x) {
    drawPixel(x, y + 7, red, green, blue);
    drawPixel(x, y + 8, red, green, blue);
    drawPixel(x, y + 9, red, green, blue);
    drawPixel(x, y + 10, red, green, blue);
  }
    bright();
}

void printKelchKreuz() {
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 100;
  for (int8_t y = 4; y < 11; ++y)
    drawPixel(15, y, red, green, blue);
  for (int8_t x = 13; x < 18; ++x)
    drawPixel(x, 8, red, green, blue);
  bright();
}

void printKelchHostie(int x_pos, int8_t y, uint8_t red, uint8_t green, uint8_t blue) {
  
  for (int8_t x = 14; x < 17; ++x)
    drawPixel(x + x_pos, y + 7, red, green, blue);
  for (int8_t x = 13; x < 18; ++x)
    drawPixel(x + x_pos, y + 6, red, green, blue);
  for (int8_t x = 12; x < 19; ++x) {
    drawPixel(x + x_pos, y + 5, red, green, blue);
    drawPixel(x + x_pos, y + 4, red, green, blue);
    drawPixel(x + x_pos, y + 3, red, green, blue);
    drawPixel(x + x_pos, y + 2, red, green, blue);
    for (int8_t x = 13; x < 18; ++x)
      drawPixel(x + x_pos, y + 1, red, green, blue);
    for (int8_t x = 14; x < 17; ++x)
      drawPixel(x + x_pos, y, red, green, blue);
  }
  drawPixel(15 + x_pos, y - 1, 100, 50, 50);
  drawPixel(15 + x_pos, y - 2, 100, 50, 50);
  drawPixel(15 + x_pos, y - 3, 100, 50, 50);
  drawPixel(14 + x_pos, y - 4, 100, 50, 50);
  drawPixel(14 + x_pos, y - 5, 100, 50, 50);
    bright();
}

void printKerzeKreuz() {
  uint8_t red = 255;
  uint8_t green = 0;
  uint8_t blue = 0;
  uint16_t delayVal = 100;
  /* rot */
  for (int8_t y = 13; y > 10; --y) {
    for (int8_t x = 12; x < 19; ++x)
      drawPixel(x, y, red, green, blue);
    bright();
    pixels.show();
    delay(delayVal);
  }
  /* orange */
  red = 250;
  green = 51;
  blue = 0;
  for (int8_t y = 10; y > 7; --y) {
    for (int8_t x = 12; x < 19; ++x)
      drawPixel(x, y, red, green, blue);
      bright();
    pixels.show();
    delay(delayVal);
  }
  /* gelb */
  red = 250;
  green = 127;
  blue = 0;
  for (int8_t y = 7; y > 5; --y) {
    for (int8_t x = 12; x < 19; ++x)
      drawPixel(x, y, red, green, blue);
      bright();
    pixels.show();
    delay(delayVal);
  }
  /* gruen */
  red = 0;
  green = 250;
  blue = 0;
  for (int8_t y = 5; y > 3; --y) {
    for (int8_t x = 12; x < 19; ++x)
      drawPixel(x, y, red, green, blue);
      bright();
    pixels.show();
    delay(delayVal);
  }
  /* blau */
  red = 0;
  green = 0;
  blue = 250;
  for (int8_t y = 3; y > 1; --y) {
    for (int8_t x = 12; x < 19; ++x)
      drawPixel(x, y, red, green, blue);
      bright();
    pixels.show();
    delay(delayVal);
  }
  /* lila  */
  red = 70;
  green = 0;
  blue = 70;
  for (int8_t y = 1; y >= 0; --y) {
    for (int8_t x = 12; x < 19; ++x)
      drawPixel(x, y, red, green, blue);
      bright();
    pixels.show();
    delay(delayVal);
  }
  delay(1000);
  /* Pflanzen */
  delayVal = 175;
  red = 70;
  green = 35;
  blue = 10;
  drawPixel(18, 0, red, green, blue);
  drawPixel(18, 4, red, green, blue);
    bright();
  pixels.show();
  delay(delayVal);
  drawPixel(17, 1, red, green, blue);
  drawPixel(17, 5, red, green, blue);
    bright();
  pixels.show();
  delay(delayVal);
  drawPixel(16, 1, red, green, blue);
  drawPixel(17, 6, red, green, blue);
    bright();
  pixels.show();
  delay(delayVal);
  drawPixel(15, 2, red, green, blue);
  drawPixel(15, 1, red, green, blue);
  drawPixel(15, 1, red, green, blue);
  drawPixel(17, 2, 0, 50, 0);
  drawPixel(16, 7, red, green, blue);
  drawPixel(17, 7, 0, 50, 0);
    bright();
  pixels.show();
  delay(delayVal);
  drawPixel(14, 1, red, green, blue);
  drawPixel(14, 3, red, green, blue);
  drawPixel(15, 3, 0, 50, 0);
  drawPixel(15, 7, red, green, blue);
    bright();
  pixels.show();
  delay(delayVal);
  drawPixel(13, 1, 255, 0, 0);
  drawPixel(13, 4, red, green, blue);
  drawPixel(14, 4, red, green, blue);
  drawPixel(14, 7, red, green, blue);
  drawPixel(14, 8, red, green, blue);
  drawPixel(15, 8, 0, 50, 0);
    bright();
  pixels.show();
  delay(delayVal);
  drawPixel(12, 5, red, green, blue);
  drawPixel(14, 5, 255, 0, 0);
  drawPixel(14, 9, red, green, blue);
  drawPixel(13, 8, 255, 0, 0);
    bright();
  pixels.show();
  delay(delayVal);
  drawPixel(12, 6, 0, 50, 0);
  drawPixel(13, 10, red, green, blue);
  drawPixel(13, 9, 0, 50, 0);
    bright();
  pixels.show();
  delay(delayVal);
  drawPixel(14, 11, red, green, blue);
    bright();
  pixels.show();
  delay(delayVal);
  drawPixel(13, 12, red, green, blue);
  drawPixel(15, 11, 0, 50, 0);
    bright();
  pixels.show();
  delay(delayVal);
  drawPixel(12, 13, red, green, blue);
  drawPixel(12, 11, 0, 50, 0);
    bright();
  pixels.show();
  delay(delayVal);
  drawPixel(13, 13, 0, 50, 0);
    bright();
  pixels.show();
  delay(delayVal);

}

void printShip() {
  for (int8_t main_x = -25; main_x < 28; ++main_x) {
    for (int i = 0; i < 2; ++i) {
      pixels.clear();
      /* Shiffsrumpf */
      int8_t y = 5;
      for (int8_t i = 0; i < 7; ++i)
        for (int8_t x = main_x + 4 + i; x < main_x + 26 - i; ++x)
          drawPixel(x, y - i, 200, 10, 0);
      /* Mast */
      uint8_t red = 0;
      uint8_t green = 0;
      uint8_t blue = 250;
      for (y = 6; y < 18; ++y) {
        drawPixel(main_x + 14, y, red, green, blue);
        drawPixel(main_x + 15, y, red, green, blue);
      }
      /* Segel */
      int8_t x = main_x + 16;
      y = 8;
      for (int8_t i = 0; i < (size_y - y) / 2; ++i)
        for (int8_t j = 0; j < i * 2; j += 2) {
          drawPixel(x + j, y + i, 0, 250, 25);
          drawPixel(x + j + 1 , y + i, 0, 250, 25);
        }
      y = size_y - 2;
      for (int8_t i = 0; i < 5; ++i)
        for (int8_t j = 0; j < i * 2; j += 2) {
          drawPixel(x + j, y - i, 0, 250, 25);
          drawPixel(x + j + 1 , y - i, 0, 250, 25);
        }
      printWaves(i % 2);
        bright();
      pixels.show();
      delay(200);
    }
  }
}

void printWaves(const boolean wave) {
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t lightgreen = 100;
  uint8_t blue = 100;
  boolean tictoc = wave;
  for (int8_t x = -3; x < 30; ++x) {
    if (x % 3 == 0)
      tictoc = !tictoc;
    if (tictoc)
      drawPixel(x, 0, red, lightgreen, blue);
    else {
      drawPixel(x, 0, red, green, blue);
      drawPixel(x + 1, 1, red, lightgreen, blue);
      if (x % 3 == 0) {
        drawPixel(x + 4, 2, red, green, blue);
        drawPixel(x + 3, 2, red, green, blue);
        drawPixel(x + 2, 2, red, green, blue);
      }
    }
  }
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

void bright() {
  /* Set Brightness with potentiometer */
  uint16_t potentioVal = analogRead(POT);
  uint16_t brightnessNew = map(potentioVal, 0, 1023, 1, 255);
  Serial.print("potentio: ");
  Serial.println(brightnessNew);
  if (brightness - 1 > brightnessNew || brightness + 1 < brightnessNew) { //tolerate minmal differences
    brightness = brightnessNew;
    pixels.setBrightness(brightness);
    Serial.println("show");
    pixels.show();
  }
}
