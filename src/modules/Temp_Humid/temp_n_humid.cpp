#include <DHT.h>

#include "core/display.h"
#include <stdlib.h>
#include <string.h>

int gpioPinForDHT = 47;
// String DHTModel = "DHT22";

DHT dht(gpioPinForDHT, DHT11);

void setupDHT() {
    Serial.begin(115200);
    dht.begin();
}


void firstStart() {
    setupDHT();
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    displaySmallLeftStr(temperarure);
}



void DHTData3() {
    firstStart();
    while (true) {
        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();

        for (int i = 0; i < 10000; ++i) {
            delay(1);
            if (check(PrevPress)) return;
        }

        // check temperature and humidity again
        // if not the same, then refresh screen with new value
        float temperatureNew = dht.readTemperature();
        float humidityNew = dht.readHumidity();

        if (check(PrevPress)) return;

        while (temperature != temperatureNew or humidity != humidityNew) {
               
displaySmallLeftStr(temperarure);


            temperature = temperatureNew;
            humidity = humidityNew;
        }
    }
}