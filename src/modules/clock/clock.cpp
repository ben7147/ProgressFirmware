#include <Arduino.h>
#include <ESP32Time.h>
#include "clock.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include "modules/wifi/connectWifi.h"
#include <ArduinoJson.h>
String publicIP;

ESP32Time rtc;
String timeStr;

void storeCurrentTime() {
  char buf[9];
  sprintf(buf, "%02d:%02d:%02d", rtc.getHour(), rtc.getMinute(), rtc.getSecond());
  timeStr = String(buf);

}

void getPublicIp() {
  connectWifi();
  HTTPClient http;
  http.begin("http://api.ipify.org");
  int httpCode = http.GET();

  if (httpCode > 0) {
    publicIP = http.getString();
    Serial.print("Public IP: ");
    Serial.println(publicIP);
  } else {
    Serial.print("Failed to get IP, error: ");
    Serial.println(http.errorToString(httpCode).c_str());
  }
}


void getTime() {
  getPublicIp();

  HTTPClient http;
  String url = "https://timeapi.io/api/time/current/ip?ipAddress=" + publicIP;

  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode == 200) {
    String payload = http.getString();

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, payload);

    if (!error) {
      int hour = doc["hour"];
      int minute = doc["minute"];
      int seconds = doc["seconds"];
      int day = doc["day"];
      int month = doc["month"];
      int year = doc["year"];

      rtc.setTime(hour, minute, seconds, day, month, year);
    }
  }

  http.end();
}


