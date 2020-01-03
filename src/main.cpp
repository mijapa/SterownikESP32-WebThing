#include <Arduino.h>
#include <Ticker.h>
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
#include "servo.h"

Ticker printTicker;

void print(){
    printAllTouch();
    printAnalogReads();
    printDallasTemp();
    printAllPid();
    Serial.println("\n");
}

void setup() {
    Serial.begin(115200);
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, HIGH);

    set_servo_at_begining();

    setupLCD();
    toneHello();
    setupDHT();
    setupW5500();
    setupWiFi();
    setupOTA();
    setupWebThing();
    setupPIDs();
    setupDallas();
    setupTouch();
    printTicker.attach(5, print);
}

void loop() {
    handleOTA();

    updateWebThing(readDHTtemp(), readDHThumi(), readThermocouple());
    delay(500);

    tryConnectWiFi();

    calculatePIDs();
}
