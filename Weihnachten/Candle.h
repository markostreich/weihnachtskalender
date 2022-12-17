#include "Graphics.h"

struct Candle {
  int8_t pos_x;
  int8_t pos_y = 0;
  unsigned long fireInterval = random(50, 70);
  unsigned long fireLast = 0;
  uint8_t fireState = 0;
  uint8_t state = 0;
};

uint8_t candle[80] {
  0, 0, 6, 0, 0,
  0, 5, 6, 5, 0,
  5, 5, 5, 3, 3,
  1, 1, 2, 3, 4,
  1, 1, 2, 3, 4,
  1, 1, 2, 3, 4,
  1, 1, 2, 3, 4,
  1, 1, 2, 3, 4,
  1, 1, 2, 3, 4,
  1, 1, 2, 3, 4,
  1, 1, 2, 3, 4,
  1, 1, 2, 3, 4,
  1, 1, 2, 3, 4,
  1, 1, 2, 3, 4,
  1, 1, 2, 3, 4
};

uint8_t fire_0[30] {
  0, 3, 0, 0, 0,
  0, 0, 3, 3, 0,
  0, 3, 3, 3, 3,
  0, 3, 4, 2, 3,
  0, 3, 2, 2, 3,
  0, 0, 1, 4, 0,
};

uint8_t fire_1[30] {
  0, 0, 3, 3, 0,
  0, 3, 3, 3, 0,
  4, 3, 1, 3, 0,
  4, 3, 2, 3, 0,
  0, 3, 2, 3, 3,
  0, 0, 1, 2, 0,
};

uint8_t fire_2[30] {
  0, 0, 0, 3, 0,
  0, 3, 3, 3, 0,
  0, 3, 3, 3, 3,
  0, 3, 2, 2, 3,
  0, 3, 1, 2, 3,
  0, 0, 1, 2, 3,
};

uint8_t fire_3[30] {
  0, 3, 0, 0, 0,
  0, 3, 3, 0, 0,
  3, 3, 3, 3, 0,
  3, 3, 3, 3, 0,
  0, 3, 1, 3, 0,
  0, 0, 1, 3, 0,
};

uint8_t fire_4[30] {
  0, 0, 0, 3, 0,
  0, 0, 3, 3, 0,
  0, 3, 3, 3, 3,
  0, 3, 3, 1, 3,
  0, 3, 1, 1, 3,
  0, 0, 1, 3, 0,
};

Candle candle_1;
Candle candle_2;
Candle candle_3;

void initCandles() {
  candle_1.pos_x = 25;
  candle_1.state = 2;
  candle_2.pos_x = 17;
  candle_2.state = 1;
  candle_3.pos_x = 9;
}

void printFireInternal(int8_t fire[], int8_t pos_x, int8_t pos_y) {
  for (uint8_t y = 0; y < 6; ++y)
    for (uint8_t x = 0; x < 5; ++x) {
      uint8_t color = fire[x + 5 * (5 - y)];
      switch (color) {
        case 1:
          drawPixel(pos_x + x, pos_y + y, 252, 190, 20);
          break;
        case 2:
          drawPixel(pos_x + x, pos_y + y, 252, 221, 20);
          break;
        case 3:
          drawPixel(pos_x + x, pos_y + y, 252, 97, 20);
          break;
        case 4:
          drawPixel(pos_x + x, pos_y + y, 252, 179, 20);
          break;
        default:
          break;
      }
    }
}

void printCandleInternal(int8_t candle[], int8_t pos_x, int8_t pos_y) {
  for (uint8_t y = 0; y < 15; ++y)
    for (uint8_t x = 0; x < 5; ++x) {
      uint8_t color = candle[x + 5 * (14 - y)];
      switch (color) {
        case 1:
          drawPixel(pos_x + x, pos_y + y, 240, 18, 18);
          break;
        case 2:
          drawPixel(pos_x + x, pos_y + y, 147, 17, 17);
          break;
        case 3:
          drawPixel(pos_x + x, pos_y + y, 136, 15, 15);
          break;
        case 4:
          drawPixel(pos_x + x, pos_y + y, 101, 4, 4);
          break;
        case 5:
          drawPixel(pos_x + x, pos_y + y, 230, 204, 209);
          break;
        case 6:
          drawPixel(pos_x + x, pos_y + y, 20, 10, 12);
          break;
        default:
          break;
      }
    }
}

void printCandle(Candle* candleS, unsigned long now) {
  int8_t firePos_y = 14 - candleS->state * 14 / 4;
  printCandleInternal(candle, candleS->pos_x, - candleS->state * 14 / 4);
  //printFireInternal(fire_0, candleS.pos_x, firePos_y);
  if (now - candleS->fireLast >= candleS->fireInterval) {
    candleS->fireState++;
    candleS->fireLast = now;
    //candleS->fireInterval = 30;
  }
  if (candleS->fireState > 4)
    candleS->fireState = 0;
  switch(candleS->fireState) {
    case 0:
      printFireInternal(fire_0, candleS->pos_x, firePos_y);
      break;
    case 1:
      printFireInternal(fire_1, candleS->pos_x, firePos_y);
      break;
    case 2:
      printFireInternal(fire_2, candleS->pos_x, firePos_y);
      break;
    case 3:
      printFireInternal(fire_3, candleS->pos_x, firePos_y);
      break;
    case 4:
      printFireInternal(fire_4, candleS->pos_x, firePos_y);
      break;
    default:
      break;
  }
}