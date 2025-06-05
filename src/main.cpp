#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "modules/clock/clock.cpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin not used

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
    Serial.begin(115200);
    Wire.begin(21, 20);  // SDA = 21, SCL = 20

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Most SSD1306s use address 0x3C
        Serial.println(F("SSD1306 allocation failed"));
        while (true); // loop forever
  }

    display.clearDisplay();

    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setFont(NULL);
    display.setCursor(32, 28);
    display.println("Booting...");
    display.display();

    storeCurrentTime();
    // ...
    // ...
}


void loop() {
 // ..
 //...
}