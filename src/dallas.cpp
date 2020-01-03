#include "dallas.h"
#include "webthings.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HardwareSerial.h>
#include <Ticker.h>

#define ONE_WIRE_BUS 3

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)

OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

Ticker updateTicker;

/*
 * The setup function. We only start the sensors here
 */
uint8_t findDevices(OneWire ow, int pin) {
    Serial.println("Looking for OneWire devices");
    uint8_t address[8];
    uint8_t count = 0;

    if (!ow.search(address)) {
        Serial.println(" No more addresses.");
        Serial.println();
        ow.reset_search();
        delay(250);
    } else {
        Serial.print(" ROM =");
        for (int i = 0; i < 8; i++) {
            Serial.write(' ');
            Serial.print(address[i], HEX);
        }
    }
    return count;
}

void update(){
    sensors.requestTemperatures();
    updateDallasWebThing(sensors.getTempCByIndex(0));
}

void setupDallas() {
    Serial.println("Dallas Temperature IC Setup");
    // Start up the library
    sensors.begin();
    updateTicker.attach_ms(500, update);
}

void printDallasTemp() {
//    Serial.println(digitalRead(ONE_WIRE_BUS));
//    findDevices(oneWire, ONE_WIRE_BUS);
//    delay(2000);
    // call sensors.requestTemperatures() to issue a global temperature
    // request to all devices on the bus
//    Serial.print("Requesting temperatures...");
    sensors.requestTemperatures(); // Send the command to get temperatures
//    Serial.println("DONE");
    // After we got the temperatures, we can print them here.
    // We use the function ByIndex, and as an example get the temperature from the first sensor only.
    Serial.print("Dallas temperature is: ");
    Serial.println(sensors.getTempCByIndex(0));
}

