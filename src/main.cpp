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
#include "w5500.h"

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

    setupW5500();
    setupWiFi();
    setupOTA();
    setupPID();
    setupWebThing();
}

void loop() {

    Serial.println("LOOP");

    ArduinoOTA.handle();
    Serial.println("OTA handled");

    updateWebThing(readDHTtemp(), readDHThumi(), readThermocouple());
    Serial.println("WebThing updated");

    updatePID(500);

    Serial.print("\n\n");
    delay(1000);

    displayTemp(readThermocouple());

    if (WiFi.status() != WL_CONNECTED) {
        tryConnectWiFi();
    }

    printAllTouch();
//    loopW5500();
}
