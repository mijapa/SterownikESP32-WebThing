#include <DHTesp.h>
#include <Ticker.h>
#include "dht.h"

DHTesp dht;
Ticker sampler;

void setupDHT() {
    dht.setup(DHTPIN, DHTesp::DHT22);
//    sampler.attach_ms(dht.getMinimumSamplingPeriod(), sample);
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

void readDHT(float *temperature, float *humidity) {
    Serial.println("Reading temperature and humidity...");
    *humidity = dht.getHumidity();
    *temperature = dht.getTemperature();
    Serial.println("Status\tHumidity (%)\tTemperature (C)\tHeatIndex (C)");
    Serial.print(dht.getStatusString());
    Serial.print("\t");
    Serial.print(*humidity, 1);
    Serial.print("\t\t");
    Serial.print(*temperature, 1);
    Serial.print("\t\t");
    Serial.print(dht.computeHeatIndex(*temperature, *humidity, false), 1);
    Serial.print("\n");
}

double readDHTtemp() {
//    Serial.println("Reading temperature...");
    double temperature = dht.getTemperature();
//    Serial.println("Status\tTemperature (C)");
//    Serial.print(dht.getStatusString());
//    Serial.print("\t\t");
//    Serial.print(temperature, 1);
//    Serial.print("\n");
    return temperature;
}

double readDHThumi() {
//    Serial.println("Reading humidity...");
    double humidity = dht.getHumidity();
//    Serial.println("Status\tHumidity (%)");
//    Serial.print(dht.getStatusString());
//    Serial.print("\t\t");
//    Serial.print(humidity, 1);
//    Serial.print("\n");
    return humidity;
}
