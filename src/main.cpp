#include <Wire.h>
#include "modules/clock/clock.h"
#include "core/display.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin not used

String currentTime;
void setup() {
    Serial.begin(115200);
    rtc.setTime(0, 0, 0, 1, 1, 2025);
    initDisplay();
    getTime();
    // displaySmallLeftTopStr("30.1 C");
    // ...
    // ...
}


void loop() {
    storeCurrentTime();
    displayBigCenterStr(timeStr);
    //delay(10000);
 //...
}