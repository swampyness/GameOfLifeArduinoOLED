
// Modified oled version of https://rosettacode.org/wiki/Conway%27s_Game_of_Life#C_for_Arduino

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SWIDTH      128
#define SHEIGHT     32
#define OLED_RESET  -1
Adafruit_SSD1306 display(SWIDTH, SHEIGHT, &Wire, OLED_RESET);

void setup() {
  randomSeed(analogRead(0));
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.drawPixel(0, 0, SSD1306_WHITE);
  display.display();
}

void show(void *u, int w, int h){
  int (*univ)[w] = u;
  int c;
  for (int y = 0; y < h; y++){
    for (int x = 0; x < w; x++){
      bool sh=(univ[y][x]==1);
      if (sh) {
        c = SSD1306_WHITE;
      } else {
        c = SSD1306_BLACK;
      }
      //display.drawPixel(x, y, c);
      display.fillRect(x * 2, y * 2, 2, 2, c);
    }
  }
  display.display();
}
 
void evolve(void *u, int w, int h){
  unsigned (*univ)[w] = u;
  unsigned newar[h][w];
  for (int y = 0; y < h; y++){
    for (int x = 0; x < w; x++){
      int n = 0;
      for (int y1 = y - 1; y1 <= y + 1; y1++)
        for (int x1 = x - 1; x1 <= x + 1; x1++)
          if (univ[(y1 + h) % h][(x1 + w) % w])
            n++;
 
      if (univ[y][x]) n--;
      newar[y][x] = (n == 3 || (n == 2 && univ[y][x]));
 
    }
  } 
  for (int y = 0; y < h; y++){
    for (int x = 0; x < w; x++){
      univ[y][x] = newar[y][x];
    }
  }
}
 
void game(int w, int h) {
  unsigned univ[h][w];
  for (int x = 0; x < w; x++){
    for (int y = 0; y < h; y++){
      univ[y][x] = random(0, 100) > 65 ? 1 : 0;
    }
  }
  int sc=0;
  while (1) {
    show(univ, w, h);
    evolve(univ, w, h);
    sc++;
    if (sc > 300) break;
  }
}

void loop() {
  game(64, 16);
}
