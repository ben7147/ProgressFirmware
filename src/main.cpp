#include <Wire.h>
#include "modules/clock/clock.h"
#include "core/display.h"
#include "modules/Temp_Humid/temp_n_humid.h"

String currentTime;
void setup() {
    Serial.begin(115200);
    // rtc.setTime(0, 0, 0, 1, 1, 2025);
    getTime();
    firstStartDHT();
    initDisplay();
    // displaySmallLeftTopStr("30.1 C");
    // ...
    // ...
}


void loop() {
    storeCurrentTime();
    displayBigCenterStr(timeStr);
    // delay(100);
    DHTData();
    display.display();
    delay(500);
    display.clearDisplay();
}