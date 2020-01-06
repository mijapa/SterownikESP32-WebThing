#include <DHTesp.h>
#include "dht.h"

DHTesp dht;

void setupDHT() {
    dht.setup(DHTPIN, DHTesp::DHT22);
}

int readDhtHeatIndex(double *heatIndex) {
    if (dht.getStatus() == 0) {
        dht.values = dht.getTempAndHumidity();
        if (dht.values.humidity != nanf("") && dht.values.temperature != nanf("")) {
            if (dht.values.humidity > 0 && dht.values.humidity < 100 && dht.values.temperature > -30 &&
                dht.values.temperature < 30)
                *heatIndex = dht.computeHeatIndex(dht.values.temperature, dht.values.humidity);
            return 1;
        }
    }
    Serial.println("FAILED TO READ DHT HEAT INDEX!!");
    return 0;
}

double readDHTtemp() {
    double temperature = dht.getTemperature();
    return temperature;
}

double readDHThumi() {
    double humidity = dht.getHumidity();
    return humidity;
}
