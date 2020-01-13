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
bool timeToPrint = false;

void printReady(){
    timeToPrint = true;
}

void loopPrint(){
    if(timeToPrint){
        timeToPrint = false;
        printAllTouch();
        printAnalogReads();
        printDallasTemp();
        printAllPid();
        Serial.println("\n");
    }
}


void setup() {
    setupLCD();

    Serial.begin(115200);
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, HIGH);

    set_servo_at_begining();

    toneHello();
    setupDHT();
    setupW5500();
    setupWiFi();
    setupOTA();
    setupWebThing();
    setupPIDs();
    setupDallas();
    setupTouch();
    poweringSetup();
    setupAnalogReads();
    printTicker.attach(5, printReady);
}

void loop() {
    handleOTA();
    loopDallas();
    loopAnalogReads();
    loopTouch();
    loopPrint();
    loopWebThing();

    tryConnectWiFi();

    loopPID();
}
