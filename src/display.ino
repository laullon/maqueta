#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define SEPARATION 18
#define WIDE 6
#define TOP 13

int y[3] = {64-(WIDE*7)-6, 64-(WIDE*4)-3, 64-WIDE};
int x[5] = {0, 15, 64, 64, 113};
int w[5] = {15, 49, 0, 49, 15};

void initDisplay() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  drawRails();
}

void updateDisplay() {
  drawRails();
}

void drawRails() {
  display.clearDisplay();

  if (((millis()/500)%2) == 0) {
    display.fillCircle(TOP/2, TOP/2, TOP/2, WHITE);
  } else {
    display.drawCircle(TOP/2, TOP/2, TOP/2, WHITE);
  }

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(TOP+10,0);
  display.println("1  2  3");

  // #1
  display.fillRect(x[0], y[0], w[0]+10, WIDE, 1);
  display.fillRect(x[2], y[0], w[2]+w[3]+w[3], WIDE, 1);

  // #2
  display.fillRect(x[0], y[1], w[0], WIDE, 1);
  display.fillRect(x[2]-10, y[1], w[2]+20, WIDE, 1);
  display.fillRect(x[4], y[1], w[4], WIDE, 1);

  // #3
  display.fillRect(x[0], y[2], w[0]+w[1]+w[2], WIDE, 1);
  display.fillRect(x[4]-10, y[2], w[4]+10, WIDE, 1);

  // A
  int sd = (positions[A] == STRAIGHT) ? 1 : (WIDE-1);
  int st = (positions[A] == DIVERGING) ? 1 : (WIDE-1);
  for (size_t s = 0; s < WIDE; s+=sd) {
    display.drawLine(x[1], y[0], x[2], y[0], 1);
    display.drawLine(x[1], y[0]+s, x[2], y[0]+s, 1);
    display.drawLine(x[1], y[1], x[2], y[1], 1);
    display.drawLine(x[1], y[1]+s, x[2], y[1]+s, 1);
  }
  for (size_t s = 0; s < WIDE; s+=st) {
    display.drawLine(x[1], y[1], x[2], y[0], 1);
    display.drawLine(x[1], y[1]+s, x[2], y[0]+s, 1);
  }

  // B
  sd = (positions[B] == STRAIGHT) ? 1 : (WIDE-1);
  st = (positions[B] == DIVERGING) ? 1 : (WIDE-1);
  for (size_t s = 0; s < WIDE; s+=sd) {
    display.drawLine(x[3], y[1], x[4], y[1], 1);
    display.drawLine(x[3], y[1]+s, x[4], y[1]+s, 1);
    display.drawLine(x[3], y[2], x[4], y[2], 1);
    display.drawLine(x[3], y[2]+s, x[4], y[2]+s, 1);
  }
  for (size_t s = 0; s < WIDE; s+=st) {
    display.drawLine(x[3], y[2], x[4], y[1], 1);
    display.drawLine(x[3], y[2]+s, x[4], y[1]+s, 1);
  }
  display.display();
}
