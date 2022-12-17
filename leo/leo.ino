#include "Graphics.h"
#include "images.h"

/*
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

Snowflake snowflakeBig2;
void initSnowFlakes() {
  // snowflake big
  snowflakeBig2.snow_flake = snowflakeBig_2;
  snowflakeBig2.pos_x = 2;
  snowflakeBig2.pos_y = 2;
  snowflakeBig2.size_x = 11;
  snowflakeBig2.size_y = 13;
  snowflakeBig2.red = 200;
  snowflakeBig2.green = 250;
  snowflakeBig2.blue = 0;
  snowflakeBig2.interval = random(200, 1000);
  snowflakeBig2.glowInterval = 0;
  snowflakeBig2.moveInterval = random(10, 30);
}

void printSnowflakeRotation() {
  for (uint8_t n = 0; n < 3; ++n) {
    for (float i = 0.0; i < 361; i += 11.0) {
      pixels.clear();
      printSnowflakeRotatedInternal(snowflakeBig2, i);
      bright();
      pixels.show();
      delay(70);
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
}*/

void setup() {
  pixels.begin();
  pixels.clear();
  //initSnowFlakes();
}

void loop() {
  printMario();
  printSword();
  printAlien();
  printDino();
  printSchaedel();

  //printSnowflakeRotation();
}

void printMario() {
  pixels.clear();
  colorAll(0, 0, 40);
  printMarioInternal(0, 0);
  bright();
  pixels.show();
  delay(5000);
  for (float i = 0.0; i < 361; i += 33.0) {
    pixels.clear();
    colorAll(0, 0, 40);
    printMarioRotatedInternal(i, 0, 0);
    bright();
    pixels.show();
    delay(40);
  }
  pixels.clear();
  colorAll(0, 0, 40);
  printMarioInternal(0, 0);
  bright();
  pixels.show();
  delay(5000);
}

void printSword() {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  for (uint8_t n = 0; n < 1; ++n) {
    float a = -45.0;
    for (int8_t i = -15; i < 1; ++i) {
      pixels.clear();
      colorAll(r, g, b);
      printSwordRotatedInternal(a, i, 0, i + 4, 4);
      bright();
      pixels.show();
      delay(30);
    }
    for (; a < 90.0; a += 11.0) {
      pixels.clear();
      colorAll(r, g, b);
      printSwordRotatedInternal(a, 0, 0, 4,4);
      bright();
      pixels.show();
      delay(10);
    }
    for (; a >= -30.0; a -= 11.0) {
      pixels.clear();
      colorAll(r, g, b);
      printSwordRotatedInternal(a, 0, 0,4,4);
      bright();
      pixels.show();
      delay(30);
    }
    for (; a <= 0.0; a += 11.0) {
      pixels.clear();
      colorAll(r, g, b);
      printSwordRotatedInternal(a, 0, 0,4,4);
      bright();
      pixels.show();
      delay(30);
    }
    pixels.clear();
    colorAll(r, g, b);
    printSwordInternal(0, 0);
    bright();
    pixels.show();
    delay(5000);
    for (int8_t i = 0; i > -17; --i) {
      pixels.clear();
      colorAll(r, g, b);
      printSwordInternal(0, i);
      bright();
      pixels.show();
      delay(30);
    }
    delay(1000);
  }
}

void printSwords() {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  for (uint8_t n = 0; n < 3; ++n) {
    float a0 = -45.0;
    float a1 = -45.0;
    for (int8_t i = -15; i < 1; ++i) {
      pixels.clear();
      colorAll(r, g, b);
      printSwordRotatedInternal(a0, i, 0, i + 4, 4);
      printSwordRotatedInternal(a1, 20 - i, 0, 20 - i + 4, 4);
      bright();
      pixels.show();
      delay(30);
    }
    for (uint8_t i = 0; i < 5; ++i) {
      uint8_t dx0 = randomOne();
      uint8_t dy0 = randomOne();
      uint8_t dx1 = randomOne();
      uint8_t dy1 = randomOne();
      for (; a0 < 45.0; a0 += random(11.0, 22.0)) {
        a1 -= random(11.0, 22.0);
        pixels.clear();
        colorAll(r, g, b);
        printSwordRotatedInternal(a0, 0 + dx0, 0 + dy0, 4, 4);
        printSwordRotatedInternal(a1, 20 + dx1, 0 + dy1, 24, 4);
        bright();
        pixels.show();
        delay(10);
      }
      for (; a0 >= -30.0 || a1 <= -30.0; a0 -= 11.0) {
        a1 += 11.0;
        pixels.clear();
        colorAll(r, g, b);
        printSwordRotatedInternal(a0, 0, 0, 4, 4);
        printSwordRotatedInternal(a1, 20, 0, 24, 4);
        bright();
        pixels.show();
        delay(30);
      }
    }
    for (; a0 <= 0.0; a0 += 11.0) {
      a1 -= 11.0;
      pixels.clear();
      colorAll(r, g, b);
      printSwordRotatedInternal(a0, 0, 0, 4, 4);
      printSwordRotatedInternal(a1, 20, 0, 24, 4);
      bright();
      pixels.show();
      delay(30);
    }
    pixels.clear();
    colorAll(r, g, b);
    printSwordRotatedInternal(a0, 0, 0, 4, 4);
    printSwordRotatedInternal(a1, 20, 0, 24, 4);
    bright();
    pixels.show();
    delay(1000);
    for (int8_t i = 0; i > -25; i -= 2) {
      pixels.clear();
      colorAll(r, g, b);
      printSwordRotatedInternal(a0, 0, i, 4, i + 4);
      printSwordRotatedInternal(a1, 20, i, 24, i + 4);
      bright();
      pixels.show();
      delay(30);
    }
    delay(1000);
  }
}

uint8_t randomOne() {
  return random(2) == 1 ? random(2) == 1 ? 2 : -2 : 0;
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

void printSwordRotatedInternal(float angle, int8_t pos_x, int8_t pos_y) {
  float angle_rad = angle * M_PI / 180.0;
  float cosTau = cos(angle_rad);
  float sinTau = sin(angle_rad);
  float rot_x = 5;
  float rot_y = 5;
  for (uint8_t y = 0; y < 16; ++y)
    for (uint8_t x = 0; x < size_x; ++x) {
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
  float rot_x = (float)pos_x + (float)16 / (float)2;
  float rot_y = (float)pos_y + (float)16 / (float)2;
  for (uint8_t y = 0; y < 16; ++y)
    for (uint8_t x = 0; x < size_x; ++x) {
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

void printSpiral() {
  for (uint8_t n = 0; n < 3; ++n) {
    for (float i = 315.0; i >= 0.0; i -= 45.0) {
      pixels.clear();
      printSpiralInternal(i, 0, 0, 0, 0, 200);
      bright();
      pixels.show();
      delay(200);
    }
  }
}

void printSpiralInternal(float angle, int8_t pos_x, int8_t pos_y, uint8_t red, uint8_t green, uint8_t blue) {
  float angle_rad = angle * M_PI / 180.0;
  float cosTau = cos(angle_rad);
  float sinTau = sin(angle_rad);
  float rot_x = 7.5;
  float rot_y = 7.5;
  for (int letter_y = 0; letter_y < 16; ++letter_y) {
    for (int letter_x = 0; letter_x < 16; ++letter_x) {
      if (letter_x < 8) {
        if (bitRead(spiral[(31 - letter_y * 2 - 1)], 7 - letter_x))
          drawRotatedPixel(pos_x + letter_x, pos_y + letter_y, rot_x, rot_y, cosTau, sinTau, red, green, blue);
      } else {
        if (bitRead(spiral[(31 - letter_y * 2)], 15 - letter_x))
          drawRotatedPixel(pos_x + letter_x, pos_y + letter_y, rot_x, rot_y, cosTau, sinTau, red, green, blue);
      }
    }
  }
}

void printSchaedel() {
  for (uint8_t i = 0; i < 4; ++i) {
    pixels.clear();
    printSchaedelInternal(0, 1, 2, 155, 155, 155);
    bright();
    pixels.show();
    delay(2000);
    for (uint8_t n = 0; n < 8; ++n) {
      pixels.clear();
      printSchaedelInternal(n, 1, 2, 155, 155, 155);
      bright();
      pixels.show();
      delay(150);
    }
    pixels.clear();
    printSchaedelInternal(0, 1, 2, 155, 155, 155);
    bright();
    pixels.show();
    delay(2000);
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

void printAlien() {
  for (uint8_t i = 0; i < 4; ++i) {
    pixels.clear();
    printAlienInternal(0, 2, 1);
    bright();
    pixels.show();
    delay(4000);
    pixels.clear();
    printAlienInternal(1, 2, 1);
    bright();
    pixels.show();
    delay(500);
  }
  pixels.clear();
  printAlienInternal(0, 2, 1);
  bright();
  pixels.show();
  delay(4000);
}

void printAlienInternal(uint8_t n, int8_t x, int8_t y) {
  printAlienInternal(0, x, y, 0, 50, 0);
  switch (n) {
    case 0:
      printAlienInternal(1, x, y, 61, 222, 40);
      break;
    default:
      printAlienInternal(2, x, y, 61, 222, 40);
      break;
  }
}

void printAlienInternal(uint8_t n, int8_t x, int8_t y, uint8_t red, uint8_t green, uint8_t blue) {
  for (int letter_y = 0; letter_y < 14; ++letter_y) {
    for (int letter_x = 0; letter_x < 11; ++letter_x) {
      if (letter_x < 8) {
        if (bitRead(alien[n][(27 - letter_y * 2 - 1)], 7 - letter_x))
          drawPixel(x + letter_x, y + letter_y, red, green, blue);
      } else {
        if (bitRead(alien[n][(27 - letter_y * 2)], 15 - letter_x))
          drawPixel(x + letter_x, y + letter_y, red, green, blue);
      }
    }
  }
}

void printDino() {
  for (int8_t i = -13; i < 16; ++i) {
    pixels.clear();
    printDinoInternal(i, 0);
    bright();
    pixels.show();
    delay(200);
  }
  for (int8_t i = -13; i < 2; ++i) {
    pixels.clear();
    printDinoInternal(i, 0);
    bright();
    pixels.show();
    delay(200);
  }
  for (int8_t i = 0; i < 3; ++i) {
    pixels.clear();
    printDinoShutMouthInternal(1, 0);
    bright();
    pixels.show();
    delay(300);
    pixels.clear();
    printDinoOpenMouthInternal(1, 0);
    bright();
    pixels.show();
    delay(300);
  }
  for (int8_t i = 1; i < 17; ++i) {
    pixels.clear();
    printDinoInternal(i, 0);
    bright();
    pixels.show();
    delay(200);
  }
  delay(1000);
}


bool dino_state = 0;

void printDinoShutMouthInternal(int8_t x, int8_t y) {
  printDinoInternal(dino_state + 2, x, y, 0, 150, 0);
}

void printDinoOpenMouthInternal(int8_t x, int8_t y) {
  printDinoInternal(dino_state, x, y, 0, 150, 0);
}

void printDinoInternal(int8_t x, int8_t y) {
  printDinoInternal(dino_state, x, y, 0, 150, 0);
  dino_state = !dino_state;
}

void printDinoInternal(uint8_t n, int8_t x, int8_t y, uint8_t red, uint8_t green, uint8_t blue) {
  for (int letter_y = 0; letter_y < 14; ++letter_y) {
    for (int letter_x = 0; letter_x < 13; ++letter_x) {
      if (letter_x < 8) {
        if (bitRead(dino[n][(27 - letter_y * 2 - 1)], 7 - letter_x))
          drawPixel(x + letter_x, y + letter_y, red, green, blue);
      } else {
        if (bitRead(dino[n][(27 - letter_y * 2)], 15 - letter_x))
          drawPixel(x + letter_x, y + letter_y, red, green, blue);
      }
    }
  }
  drawPixel(x + 8, y + 12, 100, 100, 100);
}