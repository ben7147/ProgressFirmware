#ifndef DEAUTH_START_H
#define DEAUTH_START_H

#include <WiFi.h>
#include <esp_wifi.h>
#include "types.h"
#include "web_interface.h"
#include "deauther.h"
#include "definitions.h"

// Current Wi-Fi channel being used
extern int curr_channel;

// Setup function to initialize the system
void setupDeauth();

// Main loop function for runtime logic
void deauthLoop();

#endif // MAIN_H
