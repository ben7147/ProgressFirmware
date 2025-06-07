#ifndef WIFI_ATKS_H
#define WIFI_ATKS_H

#include <Arduino.h>

/// Flood every detected AP with broadcast deauths.
/// @param reasonCode 802.11 deauth reason (default: 7).
void deauthFloodAll(uint16_t reasonCode = 7);

#endif // WIFI_ATKS_H
