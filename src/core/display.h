// display.h

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <Adafruit_SSD1306.h>

extern TwoWire myWire;
extern Adafruit_SSD1306 display;

void initDisplay();
void displayText(const String text);
void displayBigCenterStr(const String text);
void displayBigTopStr(const String text);
void displaySmallTopStr(const String text);
void displaySmallLeftTopStr(const String text);

#endif