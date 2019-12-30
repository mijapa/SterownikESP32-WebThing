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
#include "servo.h"

void setup() {
    setupLCD();
    set_servo_at_begining();
    toneHello();
    setupDHT();

    Serial.begin(115200);
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, HIGH);

    setupW5500();
    setupWiFi();
    setupOTA();
    handleOTA();
    setupPID();
    setupWebThing();
    setupDallas();
    setupTouch();
}

void loop() {
    Serial.println("LOOP");

    updateWebThing(readDHTtemp(), readDHThumi(), readThermocouple());

    Serial.print("\n\n");
    delay(1000);

    tryConnectWiFi();
    printAllTouch();
    loopAnalogRead();
    loopDallas();
    updatePID(readThermocouple(), readHeatIndex());
}
