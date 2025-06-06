#include <WiFi.h>
#include "core/config.h"

void connectWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // while (WiFi.status() != WL_CONNECTED) {  
    //     Serial.print('.');
    //     delay(1000);
    // }
}

