#include <Arduino.h>
#include <ESP32Time.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin not used

Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

ESP32Time rtc;
String timeStr;

void storeCurrentTime() {
  char buf[9];
  sprintf(buf, "%02d:%02d:%02d", rtc.getHour(), rtc.getMinute(), rtc.getSecond());
  timeStr = String(buf);

}


void displayClock() {
  Serial.begin(115200);
  Wire.begin(21, 20);  // SDA = 21, SCL = 20

  if (!display2.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Most SSD1306s use address 0x3C
      Serial.println(F("SSD1306 allocation failed"));
      while (true); // loop forever
  }
  display2.clearDisplay();
  display2.setTextColor(WHITE);
  display2.setTextSize(1);
  display2.setFont(NULL);
  display2.setCursor(32, 28);
  display2.println(timeStr);
  display2.display();
}