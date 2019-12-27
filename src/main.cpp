#include <Arduino.h>
#include "wifiManager.h"
#include "dht.h"
#include "webthings.h"
#include "ota.h"
#include "maxThermocouple.h"
#include "lcd.h"
#include "pid.h"
#include "touch.h"
#include "w5500.h"
#include "buzzer.h"
#include "loopAnalogRead.h"
#include "dallas.h"

void sample() {
    Serial.print("Czas na próbkę DHT");
}

void setup() {
    setupLCD();
    toneHello();
    setupDHT();

    Serial.begin(115200);
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, HIGH);

    setupW5500();
    setupWiFi();
    setupOTA();
    setupPID();
    setupWebThing();
    setupDallas();
}

void loop() {

    Serial.println("LOOP");

    handleOTA();
    Serial.println("OTA handled");

    updateWebThing(readDHTtemp(), readDHThumi(), readThermocouple());
    Serial.println("WebThing updated");

    Serial.print("\n\n");
    delay(1000);

//    displayTemp(analogRead2());


    tryConnectWiFi();

    printAllTouch();
//    loopW5500();
    loopAnalogRead();
    loopDallas();
    updatePID(readThermocouple(), readHeatIndex());
}
