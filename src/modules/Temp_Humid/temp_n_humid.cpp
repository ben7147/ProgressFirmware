#include <DHT.h>

#include "core/display.h"
#include <stdlib.h>
#include <string.h>

int gpioPinForDHT = 42;
// String DHTModel = "DHT22";

DHT dht(gpioPinForDHT, DHT11);

void setupDHT() {
    Serial.begin(115200);
    dht.begin();
}


void firstStartDHT() {
    setupDHT();
    // float temperature = dht.readTemperature();
    // float humidity = dht.readHumidity();
}



void DHTData() {
    firstStartDHT();

    float temperature = dht.readTemperature();

    displaySmallLeftTopStr(String(temperature, 1) + " C");


    // float humidity = dht.readHumidity();

    // delay(100);

    // float temperatureNew = dht.readTemperature();


    // while (temperature != temperatureNew) {
            
    //     displaySmallLeftTopStr(String(temperature));
    //     temperature = temperatureNew;
    //     // humidity = humidityNew;
    // }
}
