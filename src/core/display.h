// display.h

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <Adafruit_SSD1306.h>

extern TwoWire myWire;
extern Adafruit_SSD1306 display;

void initDisplay();
void showText(const char* text);

#endif // DISPLAY_H