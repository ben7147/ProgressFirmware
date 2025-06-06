#include <Wire.h>
#include "modules/clock/clock.cpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin not used


void setup() {
    Serial.begin(115200);
    initDisplay();
    showText();

    storeCurrentTime();
    // ...
    // ...
}


void loop() {
 // ..
 //...
}