#include "Graphics.h"

#define AMOUNT_SNOWFLAKES 50

#define SNOW_BORDER 4

int8_t snow_fall[AMOUNT_SNOWFLAKES];

uint8_t snow_land[NUMPIXELS];

void fillSnowFall() {
	for (uint8_t i = 0; i < AMOUNT_SNOWFLAKES - 1; i += 2) {
		snow_fall[i] = random(size_x + 20);
		snow_fall[i + 1] = random(size_y, size_y + 20);
	}
}

void clearSnowLand() {
	for (uint16_t i = 0; i < NUMPIXELS; ++i) {
		snow_land[i] = 0;
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
  for (uint16_t i = 0; i < NUMPIXELS; ++i) {
		if (snow_land[i] >= SNOW_BORDER) {
			pixels.setPixelColor(i, pixels.Color(150, 150, 150));
			if (i > NUMPIXELS - size_x)
				clearSnowLand();
		}
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