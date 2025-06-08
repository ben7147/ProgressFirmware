#include <WiFi.h>
#include <esp_wifi.h>
#include "types.h"
#include "web_interface.h"
#include "deauther.h"
#include "definitions.h"
#include "core/buttons.h"

int curr_channel = 1;

void setupDeauth() {
    #ifdef SERIAL_DEBUG
    Serial.begin(115200);
    #endif
    #ifdef LED
    pinMode(LED, OUTPUT);
    #endif

    WiFi.mode(WIFI_MODE_AP);
    WiFi.softAP(AP_SSID, AP_PASS);

    start_web_interface();
}

void deauthLoop() {
    while (true) {
        if (deauth_type == DEAUTH_TYPE_ALL) {
            if (curr_channel > CHANNEL_MAX) curr_channel = 1;
            esp_wifi_set_channel(curr_channel, WIFI_SECOND_CHAN_NONE);
            curr_channel++;
            delay(10);
            if (check (selPress)) return;
        } else {
            web_interface_handle_client();
            if (check (selPress)) return;
        }
        if (check (selPress)) return;
    }
}