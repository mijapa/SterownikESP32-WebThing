#include "dallas.h"
#include "webthings.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HardwareSerial.h>
#include <Ticker.h>

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)

OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

Ticker updateDallasTicker;

double lastDallasTemp = 0;
bool updateDallas = false;

double getDallasTemp(){
    sensors.requestTemperatures();
    double temp = sensors.getTempCByIndex(0);
    if (temp < -40){
        Serial.println("FAILURE TO READ DALLAS");
        return lastDallasTemp;
    }
    lastDallasTemp = temp;
    return temp;
}

void dallasReady(){
    updateDallas = true;
}

void loopDallas(){
    if(updateDallas){
        updateDallas = false;
        updateDallasWebThing(getDallasTemp());
    }
}

void setupDallas() {
    Serial.println("Dallas Temperature IC Setup");
    sensors.begin();
    updateDallasTicker.attach_ms(500, dallasReady);
}

void printDallasTemp() {
    sensors.requestTemperatures(); // Send the command to get temperatures
    Serial.print("Dallas temperature is: ");
    Serial.println(getDallasTemp());
}