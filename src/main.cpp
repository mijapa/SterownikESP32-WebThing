#include <Arduino.h>
#include <ArduinoOTA.h>
#include "wifi.h"
#include "dht.h"
#include "webthings.h"
#include "ota.h"
#include "maxThermocouple.h"
#include "lcd.h"
#include "servo.h"
#include "pid.h"
#include "touch.h"

void sample() {
    Serial.print("Czas na próbkę DHT");
}

void setup() {
    setupServo();
    setupDHT();
    setupLCD();

    Serial.begin(115200);
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, HIGH);

    setupWiFi();
    setupWebThing();
    setupOTA();
    setupPID();
}

void loop() {
    Serial.println("LOOP");

    ArduinoOTA.handle();
    Serial.println("OTA handled");

    updateWebThing(readDHTtemp(), readDHThumi(), readThermocouple());
    Serial.println("WebThing updated");

    updatePID(500);

    Serial.print("\n\n");
    delay(3000);

    displayTemp(readDHTtemp());

    if (WiFi.status() == WL_DISCONNECTED) {
        tryConnectWiFi();
    }

    printAllTouch();
}
