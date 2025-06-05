#include <Arduino.h>
#include <ESP32Time.h>


ESP32Time rtc;
String timeStr;

void storeCurrentTime() {
  char buf[9];
  sprintf(buf, "%02d:%02d:%02d", rtc.getHour(), rtc.getMinute(), rtc.getSecond());
  timeStr = String(buf);
}
