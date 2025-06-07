// display.cpp

#include "display.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

TwoWire myWire = TwoWire(0);
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &myWire, -1);


void initDisplay() {
    myWire.begin(21, 20);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.clearDisplay();
    display.display();
}

void displayText(const String text) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(text);
    display.display();
}

void displayBigCenterStr(const String text) {
    //display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);
    // display.setFont(NULL);
    display.setCursor(15, 22);
    display.println(text);
    // display.display();
}

void displayBigTopStr(const String text) {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    // display.setFont(NULL);
    display.setCursor(15, 2);
    display.println(text);
    display.display();
}

void displaySmallTopStr(const String text) {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    // display.setFont(NULL);
    display.setCursor(38, 2);
    display.println(text);
    display.display();
}

void displaySmallLeftTopStr(const String text) {
    //display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    // display.setFont(NULL);
    display.setCursor(2, 2);
    display.println(text);
    //display.display();
}

void displaySmallRightTopStr(const String text) {
    // display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setFont(NULL);
    display.setCursor(106, 2);
    display.println("48%");
    // display.display();
}