#include "Letter.h"
#include "Symbols.h"

#define DELAYVAL 100  // Time (in milliseconds) to pause between pixels

#define CHAR_WIDTH 5
#define CHAR_HEIGHT 5

void setup() {
  //Serial.begin(9600);
  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();
  bright();
  pixels.show();
  initSnowFlakes();
  fillSnowFall();
  clearSnowLand();
}

//int8_t start_x = 30;
//int8_t start_y = 6;

void loop() {
  //printSnowfall();
  //printSnowman();
  printSnowflakes();
  //  printAdventg();
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
  pixels.clear();
  printSnowLand();
  printNum(number_1, 11, 4, 200, 10, 10);
  printSnowfallStayInternal();
  bright();
  pixels.show();
  delay(130);
}

void printSnowman() {
  pixels.clear();
  printSnowmanInternal(3, 0);
  printSnowLand();
  printSnowfallStayInternal();
  printNum(number_2, 19, 2, 200, 50, 46);
  bright();
  pixels.show();
  delay(130);
}


void printSnowflakes() {
  unsigned long now = millis();
  pixels.clear();
  if (now - snowfallLast >= snowfallInterval) {
    printSnowfallInternal();
    snowfallLast = now;
  } else {
    printSnowfallInternalLast();
  }

  if (now - snowflakeBig.lastMove >= snowflakeBig.moveInterval) {
    snowflakeBig.lastMove = now;
    snowflakeBig.pos_x = random(4) == 3 ? snowflakeBig.pos_x + 1 : snowflakeBig.pos_x - 1;
    snowflakeBig.pos_y--;
    if (snowflakeBig.pos_y + snowflakeBig.size_y < 0) {
      snowflakeBig.pos_x = random(27);
      snowflakeBig.pos_y = random(20, 80);
      snowflakeBig.moveInterval = random(10, 30);
      snowflakeBig.red = random(40, 70);
      snowflakeBig.green = random(40, 70);
      snowflakeBig.blue = random(170, 250);
      snowflakeBig.interval = random(700, 1000);
    }
  }
  printSnowflakeInternal(snowflakeBig);
  if (!snowflakeBig.glowing && now - snowflakeBig.lastMillis >= snowflakeBig.interval) {
    snowflakeBig.glowing = true;
  }
  if (snowflakeBig.glowing) {
    if (now - snowflakeBig.lastGlowMillis >= snowflakeBig.glowInterval) {
      glowSnowflake(snowflakeBig);
      snowflakeBig.stateGlow++;
      snowflakeBig.lastGlowMillis = millis();
    }
    if (snowflakeBig.stateGlow >= snowflakeBig.size_x + snowflakeBig.size_y - 1) {
      snowflakeBig.stateGlow = 0;
      snowflakeBig.lastMillis = millis();
      snowflakeBig.glowing = false;
    } else {
      printSnowflakeInternal(snowflakeBig);
      glowSnowflake(snowflakeBig);
    }
  } else {
    printSnowflakeInternal(snowflakeBig);
  }


  if (now - snowflake1.lastMove >= snowflake1.moveInterval) {
    snowflake1.lastMove = now;
    snowflake1.pos_x = random(4) == 3 ? snowflake1.pos_x + 1 : snowflake1.pos_x - 1;
    snowflake1.pos_y--;
    if (snowflake1.pos_y + snowflake1.size_y < 0) {
      snowflake1.pos_x = random(27);
      snowflake1.pos_y = random(20, 80);
      snowflake1.moveInterval = random(30, 70);
      snowflake1.red = random(40, 70);
      snowflake1.green = random(40, 70);
      snowflake1.blue = random(200, 250);
      snowflake1.interval = random(200, 1000);
    }
  }
  if (!snowflake1.glowing && now - snowflake1.lastMillis >= snowflake1.interval) {
    snowflake1.glowing = true;
  }
  if (snowflake1.glowing) {
    if (now - snowflake1.lastGlowMillis >= snowflake1.glowInterval) {
      printSnowflakeInternal(snowflake1);
      glowSnowflake(snowflake1);
      snowflake1.stateGlow++;
      snowflake1.lastGlowMillis = millis();
    } else {
      printSnowflakeInternal(snowflake1);
      glowSnowflake(snowflake1);
    }
  } else {
    printSnowflakeInternal(snowflake1);
  }
  if (snowflake1.stateGlow >= snowflake1.size_x + snowflake1.size_y - 1) {
    snowflake1.stateGlow = 0;
    snowflake1.lastMillis = millis();
    snowflake1.glowing = false;
  }

  if (now - snowflake2.lastMove >= snowflake2.moveInterval) {
    snowflake2.lastMove = now;
    snowflake2.pos_x = random(4) == 3 ? snowflake2.pos_x + 1 : snowflake2.pos_x - 1;
    snowflake2.pos_y--;
    if (snowflake2.pos_y + snowflake2.size_y < 0) {
      snowflake2.pos_x = random(27);
      snowflake2.pos_y = random(20, 80);
      snowflake2.moveInterval = random(30, 70);
      snowflake2.red = random(40, 70);
      snowflake2.green = random(40, 70);
      snowflake2.blue = random(200, 250);
      snowflake2.interval = random(200, 1000);
    }
  }
  if (!snowflake2.glowing && now - snowflake2.lastMillis >= snowflake2.interval) {
    snowflake2.glowing = true;
  }
  if (snowflake2.glowing) {
    if (now - snowflake2.lastGlowMillis >= snowflake2.glowInterval) {
      printSnowflakeInternal(snowflake2);
      glowSnowflake(snowflake2);
      snowflake2.stateGlow++;
      snowflake2.lastGlowMillis = millis();
    } else {
      printSnowflakeInternal(snowflake2);
      glowSnowflake(snowflake2);
    }
  } else {
    printSnowflakeInternal(snowflake2);
  }
  if (snowflake2.stateGlow >= snowflake2.size_x + snowflake2.size_y - 1) {
    snowflake2.stateGlow = 0;
    snowflake2.lastMillis = millis();
    snowflake2.glowing = false;
  }

  if (now - snowflake3.lastMove >= snowflake3.moveInterval) {
    snowflake3.lastMove = now;
    snowflake3.pos_x = random(4) == 3 ? snowflake3.pos_x + 1 : snowflake3.pos_x - 1;
    snowflake3.pos_y--;
    if (snowflake3.pos_y + snowflake3.size_y < 0) {
      snowflake3.pos_x = random(27);
      snowflake3.pos_y = random(20, 80);
      snowflake3.moveInterval = random(30, 70);
      snowflake3.red = random(40, 70);
      snowflake3.green = random(40, 70);
      snowflake3.blue = random(200, 250);
      snowflake3.interval = random(200, 1000);
    }
  }
  if (!snowflake3.glowing && now - snowflake3.lastMillis >= snowflake3.interval) {
    snowflake3.glowing = true;
  }
  if (snowflake3.glowing) {
    if (now - snowflake3.lastGlowMillis >= snowflake3.glowInterval) {
      printSnowflakeInternal(snowflake3);
      glowSnowflake(snowflake3);
      snowflake3.stateGlow++;
      snowflake3.lastGlowMillis = millis();
    } else {
      printSnowflakeInternal(snowflake3);
      glowSnowflake(snowflake3);
    }
  } else {
    printSnowflakeInternal(snowflake3);
  }
  if (snowflake3.stateGlow >= snowflake3.size_x + snowflake3.size_y - 1) {
    snowflake3.stateGlow = 0;
    snowflake3.lastMillis = millis();
    snowflake3.glowing = false;
  }

  if (now - snowflake4.lastMove >= snowflake4.moveInterval) {
    snowflake4.lastMove = now;
    snowflake4.pos_x = random(4) == 3 ? snowflake4.pos_x + 1 : snowflake4.pos_x - 1;
    snowflake4.pos_y--;
    if (snowflake4.pos_y + snowflake4.size_y < 0) {
      snowflake4.pos_x = random(27);
      snowflake4.pos_y = random(20, 80);
      snowflake4.moveInterval = random(30, 70);
      snowflake4.red = random(40, 70);
      snowflake4.green = random(40, 70);
      snowflake4.blue = random(200, 250);
      snowflake4.interval = random(200, 1000);
    }
  }
  if (!snowflake4.glowing && now - snowflake4.lastMillis >= snowflake4.interval) {
    snowflake4.glowing = true;
  }
  if (snowflake4.glowing) {
    if (now - snowflake4.lastGlowMillis >= snowflake4.glowInterval) {
      printSnowflakeInternal(snowflake4);
      glowSnowflake(snowflake4);
      snowflake4.stateGlow++;
      snowflake4.lastGlowMillis = millis();
    } else {
      printSnowflakeInternal(snowflake4);
      glowSnowflake(snowflake4);
    }
  } else {
    printSnowflakeInternal(snowflake4);
  }
  if (snowflake4.stateGlow >= snowflake4.size_x + snowflake4.size_y - 1) {
    snowflake4.stateGlow = 0;
    snowflake4.lastMillis = millis();
    snowflake4.glowing = false;
  }

  if (now - snowflakeNum3.lastMove >= snowflakeNum3.moveInterval) {
    snowflakeNum3.lastMove = now;
    snowflakeNum3.pos_x = random(4) == 3 ? snowflakeNum3.pos_x + 1 : snowflakeNum3.pos_x - 1;
    snowflakeNum3.pos_y--;
    if (snowflakeNum3.pos_y + snowflakeNum3.size_y < 0) {
      snowflakeNum3.pos_x = random(27);
      snowflakeNum3.pos_y = random(20, 80);
      snowflakeNum3.moveInterval = random(30, 70);
      snowflakeNum3.interval = random(200, 1000);
    }
  }
  if (!snowflakeNum3.glowing && now - snowflakeNum3.lastMillis >= snowflakeNum3.interval) {
    snowflakeNum3.glowing = true;
  }
  if (snowflakeNum3.glowing) {
    if (now - snowflakeNum3.lastGlowMillis >= snowflakeNum3.glowInterval) {
      printSnowflakeInternal(snowflakeNum3);
      glowSnowflake(snowflakeNum3);
      snowflakeNum3.stateGlow++;
      snowflakeNum3.lastGlowMillis = millis();
    } else {
      printSnowflakeInternal(snowflakeNum3);
      glowSnowflake(snowflakeNum3);
    }
  } else {
    printSnowflakeInternal(snowflakeNum3);
  }
  if (snowflakeNum3.stateGlow >= snowflakeNum3.size_x + snowflakeNum3.size_y - 1) {
    snowflakeNum3.stateGlow = 0;
    snowflakeNum3.lastMillis = millis();
    snowflakeNum3.glowing = false;
  }
  bright();
  pixels.show();
  delay(2);
}

void printAdvent() {
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
    start_x--;
    bright();
    pixels.show();
    delay(DELAYVAL);
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
    printLetter(letter_W, start_x, start_y, 255, 0, 0);
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
