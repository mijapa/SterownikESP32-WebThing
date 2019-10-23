#include <Arduino.h>
#include <ArduinoOTA.h>
#include "wifi.h"
#include "dht.h"
#include "webthings.h"
#include "ota.h"

void sample() {
    Serial.print("Czas na próbkę DHT");
}

void setup() {
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, HIGH);
    Serial.begin(115200);
    setupWiFi();
    setupOTA();
    setupDHT();
    setupWebThing();
}

void loop() {
    ArduinoOTA.handle();
    adapter->update();
    delay(1000);
    float temp = 0;
    float hum = 0;
    readDHT(&temp, &hum);
}