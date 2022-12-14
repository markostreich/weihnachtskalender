#include "Graphics.h"

#define AMOUNT_SNOWFLAKES 30

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
  uint8_t amount_top = 0;
  for (uint16_t i = 0; i < NUMPIXELS; ++i) {
    if (snow_land[i] >= SNOW_BORDER) {
      pixels.setPixelColor(i, pixels.Color(150, 150, 150));
      if (i > NUMPIXELS - size_x * 2 && ++amount_top > 5)
        clearSnowLand();
    }
  }
}

void printSnowLandPalm() {
  uint8_t amount_top = 0;
  for (uint16_t i = 0; i < NUMPIXELS; ++i) {
    if (snow_land[i] >= SNOW_BORDER) {
      if (i > 119)
        pixels.setPixelColor(i, pixels.Color(70, 70, 250));
      else
        pixels.setPixelColor(i, pixels.Color(0, 0, 150));
      if (i > NUMPIXELS - size_x && ++amount_top > 10)
        clearSnowLand();
    }
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
    drawPixel(snow_fall[i], snow_fall[i + 1], 250, 250, 250);
  }
}

void printSnowfallPalmInternal() {
  for (uint8_t i = 0; i < AMOUNT_SNOWFLAKES - 1; i += 2) {
    if (snow_fall[i + 1] == 0) {
      snow_fall[i] = random(40);
      snow_fall[i + 1] = random(20, 40);
    }
    snow_fall[i] = random(4) == 3 ? snow_fall[i] + 1 : snow_fall[i] - 1;
    snow_fall[i + 1] -= 1;
    drawPixel(snow_fall[i], snow_fall[i + 1], 70, 70, 250);
  }
}

void printSnowfallInternalLast() {
  for (uint8_t i = 0; i < AMOUNT_SNOWFLAKES - 1; i += 2) {
    drawPixel(snow_fall[i], snow_fall[i + 1], 250, 250, 250);
  }
}

void printSnowflakeInternal(const uint8_t snow_flake[],
                            const int8_t pos_x, const int8_t pos_y, const uint8_t size_x, const uint8_t size_y,
                            uint8_t red, uint8_t green, uint8_t blue) {
  for (uint8_t y = 0; y < size_y; ++y)
    for (uint8_t x = 0; x < size_x; ++x) {
      uint8_t color = snow_flake[x + size_x * (size_y - 1 - y)];
      switch (color) {
        case 1:
          drawPixel(pos_x + x, pos_y + y, red, green, blue);
          break;
        default:
          break;
      }
    }
}

struct Snowflake {
  uint8_t* snow_flake;
  int8_t pos_x;
  int8_t pos_y;
  uint8_t size_x;
  uint8_t size_y;
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t stateGlow = 0;
  unsigned long interval = 1000;
  unsigned long glowInterval = 15;
  unsigned long lastMillis = 0;
  unsigned long lastGlowMillis = 0;
  bool glowing = false;
  unsigned long moveInterval = 130;
  unsigned long lastMove = 0;
};

Snowflake snowflakeBig;
Snowflake snowflakeBig2;
Snowflake snowflake1;
Snowflake snowflake2;
Snowflake snowflake3;
Snowflake snowflake4;
Snowflake snowflakeNum5;
Snowflake snowflakeNum3;
Snowflake snowflakeNum1;
Snowflake snowflakeNum0;

void initSnowFlakes() {
  /* snowflake big */
  snowflakeBig.snow_flake = snowflakeBig_1;
  snowflakeBig.pos_x = 1;
  snowflakeBig.pos_y = 0;
  snowflakeBig.size_x = 13;
  snowflakeBig.size_y = 14;
  snowflakeBig.red = 0;
  snowflakeBig.green = 200;
  snowflakeBig.blue = 150;
  snowflakeBig.interval = random(200, 1000);
  snowflakeBig.glowInterval = 0;
  snowflakeBig.moveInterval = random(10, 30);
  /* snowflake big */
  snowflakeBig2.snow_flake = snowflakeBig_2;
  snowflakeBig2.pos_x = 18;
  snowflakeBig2.pos_y = 7;
  snowflakeBig2.size_x = 11;
  snowflakeBig2.size_y = 13;
  snowflakeBig2.red = 0;
  snowflakeBig2.green = 50;
  snowflakeBig2.blue = 200;
  snowflakeBig2.interval = random(200, 1000);
  snowflakeBig2.glowInterval = 0;
  snowflakeBig2.moveInterval = random(10, 30);

  /* snowflake tiny 1 */
  snowflake1.snow_flake = snowflakeTiny_1;
  snowflake1.pos_x = random(27);
  snowflake1.pos_y = random(20, 80);
  snowflake1.size_x = 5;
  snowflake1.size_y = 5;
  snowflake1.red = random(40, 70);
  snowflake1.green = random(40, 70);
  snowflake1.blue = random(200, 250);
  snowflake1.interval = random(200, 1000);
  snowflake1.glowInterval = 15;
  snowflake1.moveInterval = random(70);

  /* snowflake tiny 2 */
  snowflake2.snow_flake = snowflakeTiny_2;
  snowflake2.pos_x = random(27);
  snowflake2.pos_y = random(20, 80);
  snowflake2.size_x = 3;
  snowflake2.size_y = 3;
  snowflake2.red = random(40, 70);
  snowflake2.green = random(40, 70);
  snowflake2.blue = random(200, 250);
  snowflake2.interval = random(200, 1000);
  snowflake2.glowInterval = 15;
  snowflake2.moveInterval = random(70);

  /* snowflake tiny 3 */
  snowflake3.snow_flake = snowflakeTiny_3;
  snowflake3.pos_x = random(27);
  snowflake3.pos_y = random(20, 80);
  snowflake3.size_x = 3;
  snowflake3.size_y = 3;
  snowflake3.red = random(40, 70);
  snowflake3.green = random(40, 70);
  snowflake3.blue = random(200, 250);
  snowflake3.interval = random(200, 1000);
  snowflake3.glowInterval = 15;
  snowflake3.moveInterval = random(70);

  /* snowflake tiny 4 */
  snowflake4.snow_flake = snowflakeTiny_4;
  snowflake4.pos_x = 13;
  snowflake4.pos_y = 8;
  //snowflake4.pos_x = random(27);
  //snowflake4.pos_y = random(20, 80);
  snowflake4.size_x = 5;
  snowflake4.size_y = 5;
  snowflake4.red = random(40, 70);
  snowflake4.green = random(40, 70);
  snowflake4.blue = random(200, 250);
  snowflake4.interval = random(200, 1000);
  snowflake4.glowInterval = 15;
  snowflake4.moveInterval = random(70);

  /* number 3 */
  snowflakeNum3.snow_flake = snowflake_3;
  snowflakeNum3.pos_x = 26;
  snowflakeNum3.pos_y = 0;
  snowflakeNum3.size_x = 4;
  snowflakeNum3.size_y = 7;
  snowflakeNum3.red = 200;
  snowflakeNum3.green = 70;
  snowflakeNum3.blue = 200;
  snowflakeNum3.interval = random(200, 1000);
  snowflakeNum3.glowInterval = 15;
  snowflakeNum3.moveInterval = random(70);

  /* number 5 */
  snowflakeNum5.snow_flake = snowflake_5;
  snowflakeNum5.pos_x = 26;
  snowflakeNum5.pos_y = 0;
  snowflakeNum5.size_x = 4;
  snowflakeNum5.size_y = 7;
  snowflakeNum5.red = 100;
  snowflakeNum5.green = 0;
  snowflakeNum5.blue = 20;
  snowflakeNum5.interval = random(200, 1000);
  snowflakeNum5.glowInterval = 15;
  snowflakeNum5.moveInterval = random(70);

  /* number 1 */
  snowflakeNum1.snow_flake = snowflake_1;
  snowflakeNum1.pos_x = 22;
  snowflakeNum1.pos_y = 0;
  snowflakeNum1.size_x = 4;
  snowflakeNum1.size_y = 7;
  snowflakeNum1.red = 100;
  snowflakeNum1.green = 0;
  snowflakeNum1.blue = 20;
  snowflakeNum1.interval = random(200, 1000);
  snowflakeNum1.glowInterval = 15;
  snowflakeNum1.moveInterval = random(70);

  /* number 0 */
  snowflakeNum0.snow_flake = snowflake_0;
  snowflakeNum0.pos_x = 23;
  snowflakeNum0.pos_y = 0;
  snowflakeNum0.size_x = 4;
  snowflakeNum0.size_y = 7;
  snowflakeNum0.red = 100;
  snowflakeNum0.green = 0;
  snowflakeNum0.blue = 20;
  snowflakeNum0.interval = random(200, 1000);
  snowflakeNum0.glowInterval = 15;
  snowflakeNum0.moveInterval = random(70);
}

unsigned long snowfallInterval = 40;
unsigned long snowfallLast = 0;

void printSnowflakeInternal(const Snowflake flake) {
  for (uint8_t y = 0; y < flake.size_y; ++y)
    for (uint8_t x = 0; x < flake.size_x; ++x) {
      uint8_t color = flake.snow_flake[x + flake.size_x * (flake.size_y - 1 - y)];
      switch (color) {
        case 1:
          drawPixel(flake.pos_x + x, flake.pos_y + y, flake.red, flake.green, flake.blue);
          break;
        default:
          break;
      }
    }
}

void printSnowflakeRotatedInternal(const Snowflake flake, float angle) {
  float angle_rad = angle * M_PI / 180.0;
  float cosTau = cos(angle_rad);
  float sinTau = sin(angle_rad);
  float rot_x = flake.pos_x + flake.size_x / 2;
  float rot_y = flake.pos_y + flake.size_y / 2;
  for (uint8_t y = 0; y < flake.size_y; ++y)
    for (uint8_t x = 0; x < flake.size_x; ++x) {
      uint8_t color = flake.snow_flake[x + flake.size_x * (flake.size_y - 1 - y)];
      switch (color) {
        case 1:
          drawRotatedPixel(flake.pos_x + x, flake.pos_y + y, rot_x, rot_y, cosTau, sinTau, flake.red, flake.green, flake.blue);
          break;
        default:
          break;
      }
    }
}

void glowSnowflake(Snowflake flake) {
  if (flake.stateGlow < flake.size_y) {
    uint8_t x = flake.size_x;
    for (uint8_t y = flake.size_y - 1 - flake.stateGlow; y < flake.size_y; ++y) {
      --x;
      uint8_t color = flake.snow_flake[x + flake.size_x * (flake.size_y - 1 - y)];
      switch (color) {
        case 1:
          drawPixel(flake.pos_x + x, flake.pos_y + y, flake.red + 150, flake.green + 150, flake.blue);
          break;
        default:
          break;
      }
    }
  } else {
    uint8_t y = 0;
    for (int8_t x = flake.size_x + flake.size_y - 1 - flake.stateGlow; x >= 0; --x) {

      uint8_t color = flake.snow_flake[x + flake.size_x * (flake.size_y - 1 - y)];
      switch (color) {
        case 1:
          drawPixel(flake.pos_x + x, flake.pos_y + y, flake.red + 150, flake.green + 150, flake.blue);
          //Serial.println(color);
          break;
        default:
          //drawPixel(flake.pos_x + x, flake.pos_y + y, flake.red + 50, flake.green + 50, flake.blue);
          break;
      }
      ++y;
    }
  }
}

void printMarioInternal(int8_t pos_x, int8_t pos_y) {
  for (uint8_t y = 0; y < 16; ++y)
    for (uint8_t x = 0; x < 16; ++x) {
      uint8_t color = mario[x + 16 * (15 - y)];
      switch (color) {
        case 1:
          drawPixel(pos_x + x, pos_y + y, 255, 0, 0);
          break;
        case 2:
          drawPixel(pos_x + x, pos_y + y, 255, 255, 255);
          break;
        case 3:
          drawPixel(pos_x + x, pos_y + y, 0, 125, 242);
          break;
        case 4:
          drawPixel(pos_x + x, pos_y + y, 186, 158, 111);
          break;
        case 5:
          //drawPixel(pos_x + x, pos_y + y, 76, 0, 49);
          //drawPixel(pos_x + x, pos_y + y, 0, 0, 40);
          break;
        case 0:
          //drawPixel(pos_x + x, pos_y + y, 76, 0, 49);
          drawPixel(pos_x + x, pos_y + y, 0, 0, 0);
          break;
        default:
          break;
      }
    }
}

void printMarioRotatedInternal(float angle, int8_t pos_x, int8_t pos_y) {
  float angle_rad = angle * M_PI / 180.0;
  float cosTau = cos(angle_rad);
  float sinTau = sin(angle_rad);
  //float rot_x = (float)pos_x + (float)16 / (float)2;
  //float rot_y = (float)pos_y + (float)16 / (float)2;
  float rot_x = pos_x + 16 / 2;
  float rot_y = pos_y + 16 / 2;
  for (uint8_t y = 0; y < 16; ++y)
    for (uint8_t x = 0; x < 16; ++x) {
      uint8_t color = mario[x + 16 * (16 - 1 - y)];
      switch (color) {
        case 1:
          drawRotatedPixel(pos_x + x, pos_y + y, rot_x, rot_y, cosTau, sinTau, 255, 0, 0);
          break;
        case 2:
          drawRotatedPixel(pos_x + x, pos_y + y, rot_x, rot_y, cosTau, sinTau, 255, 255, 255);
          break;
        case 3:
          drawRotatedPixel(pos_x + x, pos_y + y, rot_x, rot_y, cosTau, sinTau, 0, 125, 242);
          break;
        case 4:
          drawRotatedPixel(pos_x + x, pos_y + y, rot_x, rot_y, cosTau, sinTau, 186, 158, 111);
          break;
        case 5:
          break;
        case 0:
          drawRotatedPixel(pos_x + x, pos_y + y, rot_x, rot_y, cosTau, sinTau, 0, 0, 0);
          break;
        default:
          break;
      }
    }
}

void printSwordInternal(int8_t pos_x, int8_t pos_y) {
  for (uint8_t y = 0; y < 16; ++y)
    for (uint8_t x = 0; x < 16; ++x) {
      uint8_t color = sword[x + 16 * (15 - y)];
      switch (color) {
        case 1:
          drawPixel(pos_x + x, pos_y + y, 212, 191, 2);
          break;
        case 2:
          drawPixel(pos_x + x, pos_y + y, 247, 227, 42);
          break;
        case 3:
          drawPixel(pos_x + x, pos_y + y, 17, 118, 247);
          break;
        case 4:
          drawPixel(pos_x + x, pos_y + y, 158, 58, 24);
          break;
        case 5:
          drawPixel(pos_x + x, pos_y + y, 173, 48, 36);
          break;
        case 6:
          drawPixel(pos_x + x, pos_y + y, 178, 179, 177);
          break;
        case 7:
          drawPixel(pos_x + x, pos_y + y, 57, 157, 207);
          break;
        default:
          break;
      }
    }
}

void printSwordRotatedInternal(float angle, int8_t pos_x, int8_t pos_y, float rot_x, float rot_y) {
  float angle_rad = angle * M_PI / 180.0;
  float cosTau = cos(angle_rad);
  float sinTau = sin(angle_rad);
  for (uint8_t y = 0; y < 16; ++y)
    for (uint8_t x = 0; x < 16; ++x) {
      uint8_t color = sword[x + 16 * (16 - 1 - y)];
      switch (color) {
        case 1:
          drawRotatedPixel(pos_x + x, pos_y + y, rot_x, rot_y, cosTau, sinTau, 212, 191, 2);
          break;
        case 2:
          drawRotatedPixel(pos_x + x, pos_y + y, rot_x, rot_y, cosTau, sinTau, 247, 227, 42);
          break;
        case 3:
          drawRotatedPixel(pos_x + x, pos_y + y, rot_x, rot_y, cosTau, sinTau, 17, 118, 247);
          break;
        case 4:
          drawRotatedPixel(pos_x + x, pos_y + y, rot_x, rot_y, cosTau, sinTau, 158, 58, 24);
          break;
        case 5:
          drawRotatedPixel(pos_x + x, pos_y + y, rot_x, rot_y, cosTau, sinTau, 173, 48, 36);
          break;
        case 6:
          drawRotatedPixel(pos_x + x, pos_y + y, rot_x, rot_y, cosTau, sinTau, 178, 179, 177);
          break;
        case 7:
          drawRotatedPixel(pos_x + x, pos_y + y, rot_x, rot_y, cosTau, sinTau, 57, 157, 207);
          break;
        default:
          break;
      }
    }
}

void printSchaedelInternal(uint8_t n, int8_t x, int8_t y, uint8_t red, uint8_t green, uint8_t blue) {
  for (int letter_y = 0; letter_y < 12; ++letter_y) {
    for (int letter_x = 0; letter_x < 13; ++letter_x) {
      if (letter_x < 8) {
        if (bitRead(schaedel[n][(23 - letter_y * 2 - 1)], 7 - letter_x))
          drawPixel(x + letter_x, y + letter_y, red, green, blue);
      } else {
        if (bitRead(schaedel[n][(23 - letter_y * 2)], 15 - letter_x))
          drawPixel(x + letter_x, y + letter_y, red, green, blue);
      }
    }
  }
}

void printSantaInternal(int8_t pos_x, int8_t pos_y) {
  for (uint8_t y = 0; y < 14; ++y)
    for (uint8_t x = 0; x < 10; ++x) {
      uint8_t color = santa[x + 10 * (13 - y)];
      switch (color) {
        case 1:
          drawPixel(pos_x + x, pos_y + y, 78, 12, 21);
          break;
        case 2:
          drawPixel(pos_x + x, pos_y + y, 62, 20, 8);
          break;
        case 3:
          drawPixel(pos_x + x, pos_y + y, 86, 65, 44);
          break;
        case 4:
          drawPixel(pos_x + x, pos_y + y, 254, 13, 11);
          break;
        case 5:
          drawPixel(pos_x + x, pos_y + y, 201, 7, 28);
          break;
        case 6:
          drawPixel(pos_x + x, pos_y + y, 229, 82, 93);
          break;
        case 7:
          drawPixel(pos_x + x, pos_y + y, 192, 192, 192);
          break;
        case 8:
          drawPixel(pos_x + x, pos_y + y, 238, 238, 238);
          break;
        case 9:
          drawPixel(pos_x + x, pos_y + y, 205, 116, 102);
          break;
        case 10:
          drawPixel(pos_x + x, pos_y + y, 224, 185, 172);
          break;
        case 11:
          drawPixel(pos_x + x, pos_y + y, 142, 131, 118);
          break;
        case 12:
          drawPixel(pos_x + x, pos_y + y, 248, 155, 126);
          break;
        case 13:
          drawPixel(pos_x + x, pos_y + y, 179, 123, 129);
          break;
        default:
          break;
      }
    }
}

void printSnowmanInternal(int8_t pos_x, int8_t pos_y) {
  for (uint8_t y = 0; y < 13; ++y)
    for (uint8_t x = 0; x < 11; ++x) {
      uint8_t color = snowman[x + 11 * (12 - y)];
      switch (color) {
        case 1:
          drawPixel(pos_x + x, pos_y + y, 40, 40, 250);
          break;
        case 2:
          drawPixel(pos_x + x, pos_y + y, 40, 40, 250);
          break;
        case 3:
          drawPixel(pos_x + x, pos_y + y, 100, 40, 100);
          break;
        case 4:
          drawPixel(pos_x + x, pos_y + y, 200, 100, 40);
          break;
        case 5:
          drawPixel(pos_x + x, pos_y + y, 200, 200, 200);
          break;
        case 6:
          drawPixel(pos_x + x, pos_y + y, 0, 0, 0);
          break;
        default:
          break;
      }
    }
}

void printChristmasTreeInternal(int8_t pos_x, int8_t pos_y, bool first) {
  for (uint8_t y = 0; y < 16; ++y)
    for (uint8_t x = 0; x < 15; ++x) {
      uint8_t color = christmastree[x + 15 * (15 - y)];
      switch (color) {
        case 1:
          drawPixel(pos_x + x, pos_y + y, 29, 184, 0);
          break;
        case 2:
          drawPixel(pos_x + x, pos_y + y, 0, 0, 0);
          //drawPixel(pos_x + x, pos_y + y, 15, 84, 51);
          break;
        case 3:
          drawPixel(pos_x + x, pos_y + y, 22, 135, 73);
          break;
        case 4:
          if (first)
            drawPixel(pos_x + x, pos_y + y, 255, 255, 0);
          else
            drawPixel(pos_x + x, pos_y + y, 255, 0, 0);
          break;
        case 5:
          if (first)
            drawPixel(pos_x + x, pos_y + y, 0, 0, 255);
          else
            drawPixel(pos_x + x, pos_y + y, 255, 255, 0);
          break;
        case 6:
          if (first)
            drawPixel(pos_x + x, pos_y + y, 255, 0, 0);
          else
            drawPixel(pos_x + x, pos_y + y, 0, 0, 255);
          break;
        case 7:
          drawPixel(pos_x + x, pos_y + y, 173, 116, 17);
          break;
        default:
          break;
      }
    }
}

void printPalmInternal(int8_t pos_x, int8_t pos_y) {
  for (uint8_t y = 0; y < 16; ++y)
    for (uint8_t x = 0; x < 16; ++x) {
      uint8_t color = palm[x + 16 * (15 - y)];
      switch (color) {
        case 2:
          drawPixel(pos_x + x, pos_y + y, 255, 131, 101);
          break;
        case 1:
          //drawPixel(pos_x + x, pos_y + y, 163, 131, 101);
          //break;
        case 3:
          //drawPixel(pos_x + x, pos_y + y, 135, 106, 78);
          //break;
          drawPixel(pos_x + x, pos_y + y, 228, 89, 52);
          break;
        case 4:
        case 5:
          drawPixel(pos_x + x, pos_y + y, 79, 52, 27);
          break;
        case 6:
          drawPixel(pos_x + x, pos_y + y, 25, 243, 1);
          break;
        case 7:
          drawPixel(pos_x + x, pos_y + y, 62, 255, 41);
          break;
        case 8:
          //drawPixel(pos_x + x, pos_y + y, 35, 90, 45);
          break;
        case 9:
          drawPixel(pos_x + x, pos_y + y, 97, 1, 10);
          break;
        case 10:
          drawPixel(pos_x + x, pos_y + y, 34, 37, 22);
          break;
        case 11:
          //drawPixel(pos_x + x, pos_y + y, 22, 32, 15);
          break;
        case 12:
          drawPixel(pos_x + x, pos_y + y, 13, 37, 14);
          break;
        case 13:
        case 14:
        case 15:
        case 16:
          drawPixel(pos_x + x, pos_y + y, 255, 252, 10);
          //drawPixel(pos_x + x, pos_y + y, 222, 214, 158);
          break;
        default:
          break;
      }
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
    drawPixel(snow_fall[i], snow_fall[i + 1], 250, 250, 250);
  }
}

void printSnowfallStayPalmInternal() {
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
    drawPixel(snow_fall[i], snow_fall[i + 1], 70, 70, 250);
  }
}

void printNum(byte num[], int8_t x, int8_t y, uint8_t red, uint8_t green, uint8_t blue) {
  for (int num_y = 0; num_y < 10; ++num_y) {
    for (int num_x = 0; num_x < 8; ++num_x) {
      if (bitRead(num[(9 - num_y)], 7 - num_x) && getSnowLand(x + num_x, y + num_y) >= SNOW_BORDER)
        drawPixel(x + num_x, y + num_y, red, green, blue);
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
          drawPixel(x + j + 1, y + i, 0, 250, 25);
        }
      y = size_y - 2;
      for (int8_t i = 0; i < 5; ++i)
        for (int8_t j = 0; j < i * 2; j += 2) {
          drawPixel(x + j, y - i, 0, 250, 25);
          drawPixel(x + j + 1, y - i, 0, 250, 25);
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

void printHerzen(uint8_t red, uint8_t green, uint8_t blue) {
  printLetter(letter_Herz, 0, 12, red, green, blue);
  printLetter(letter_Herz, 23, 12, red, green, blue);
  printLetter(letter_Herz, 0, -2, red, green, blue);
  printLetter(letter_Herz, 23, -2, red, green, blue);
}