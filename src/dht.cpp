#include <DHTesp.h>
#include <Ticker.h>
#include "dht.h"

DHTesp dht;
Ticker sampler;

void setupDHT() {
    dht.setup(DHTPIN, DHTesp::DHT22);
    sampler.attach_ms(dht.getMinimumSamplingPeriod(), sample);
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
    Serial.println("Reading temperature...");
    double temperature = dht.getTemperature();
    Serial.println("Status\tTemperature (C)");
    Serial.print(dht.getStatusString());
    Serial.print("\t\t");
    Serial.print(temperature, 1);
    Serial.print("\n");
    return temperature;
}
