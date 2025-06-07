#include <Arduino.h>
#include <ESP32Time.h>
#include "clock.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include "modules/wifi/connectWifi.h"
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#include "core/display.h"
String publicIP;

ESP32Time rtc;
String timeStr;

void storeCurrentTime() {
  char buf[9];
  
  tm timeinfo = rtc.getTimeStruct();
  sprintf(buf, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

  timeStr = String(buf);

}

void getPublicIp() {
  Serial.begin(115200);
  connectWifi();

  HTTPClient http;
  http.begin("http://api.ipify.org"); 

  int httpCode = http.GET();

  if (httpCode == 200) {
    publicIP = http.getString();
    Serial.print("Public IP: ");
    Serial.println(publicIP);
  } else {
    Serial.print("Failed to get IP, error code: ");
    Serial.println(httpCode);
    Serial.println(http.getString());
    publicIP = "";
  }

  http.end();
}



// void getTime() {
//   // Serial.begin(115200);
//   getPublicIp();

//   if (publicIP == "") {
//     Serial.println("No public IP available, skipping time sync.");
//     return;
//   }

//   WiFiClientSecure client;
//   client.setInsecure();


//   HTTPClient http;
//   String url = "https://timeapi.io/api/time/current/ip?ipAddress=" + publicIP;
//   Serial.println("Requesting time from: " + url);

//   http.begin(client, url);

//   int httpResponseCode = http.GET();

//   if (httpResponseCode == 200) {
//     String payload = http.getString();
//     Serial.println("Time API response:");
//     Serial.println(payload);

//     DynamicJsonDocument doc(1024);
//     DeserializationError error = deserializeJson(doc, payload);

//     if (!error) {
//       int hour = doc["hour"];
//       int minute = doc["minute"];
//       int seconds = doc["seconds"];
//       int day = doc["day"];
//       int month = doc["month"];
//       int year = doc["year"];

//       rtc.setTime(hour, minute, seconds, day, month, year);
//       Serial.println("RTC time set successfully.");
//     } else {
//       Serial.print("JSON parsing error: ");
//       Serial.println(error.c_str());
//     }
//   } else {
//     Serial.print("HTTP Error: ");
//     Serial.println(httpResponseCode);
//     Serial.println(http.getString());
//   }

//   http.end();
//   WiFi.disconnect();
//   delay(100);
// }


void getTime() {
  connectWifi();

  // Set timezone: Hungary (CET + DST)
  configTzTime("CET-1CEST,M3.5.0/2,M10.5.0/3", "pool.ntp.org");

  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    rtc.setTimeStruct(timeinfo);
    Serial.println("Time synced from NTP");
  } else {
    Serial.println("Failed to get time from NTP");
  }

  WiFi.disconnect();
}


