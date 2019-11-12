#include <Arduino.h>
#include <ArduinoOTA.h>
#include "wifi.h"
#include "dht.h"
#include "webthings.h"
#include "ota.h"
#include "maxThermocouple.h"

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
    Serial.println("LOOP");

    ArduinoOTA.handle();
    Serial.println("OTA handled");

    updateWebThing(readDHTtemp(), 0, readThermocouple());
    Serial.println("WebThing updated");

    Serial.print("\n\n");
    delay(1000);
}