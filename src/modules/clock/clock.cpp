#include <Arduino.h>
#include <ESP32Time.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin not used


ESP32Time rtc;
String timeStr;

void storeCurrentTime() {
  char buf[9];
  sprintf(buf, "%02d:%02d:%02d", rtc.getHour(), rtc.getMinute(), rtc.getSecond());
  timeStr = String(buf);

}

