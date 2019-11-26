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

void sample() {
    Serial.print("Czas na próbkę DHT");
}

void setup() {
    setupServo();
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, HIGH);
    Serial.begin(115200);
    setupWiFi();
    setupOTA();
    setupDHT();
    setupLCD();
    setupWebThing();
    setupPID();
}

void loop() {
    Serial.println("LOOP");

    ArduinoOTA.handle();
    Serial.println("OTA handled");

    updateWebThing(readDHTtemp(), 0, readThermocouple());
    Serial.println("WebThing updated");

    updatePID(50);

    Serial.print("\n\n");
    delay(1000);

    loopLCD();
}