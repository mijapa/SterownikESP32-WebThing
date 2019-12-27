#include "dallas.h"
// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HardwareSerial.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 3

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/*
 * The setup function. We only start the sensors here
 */
uint8_t findDevices(OneWire ow, int pin) {
    uint8_t address[8];
    uint8_t count = 0;


    if (ow.search(address)) {
        Serial.print("\nuint8_t pin");
        Serial.print(pin, DEC);
        Serial.println("[][8] = {");
        do {
            count++;
            Serial.println("  {");
            for (uint8_t i = 0; i < 8; i++) {
                Serial.print("0x");
                if (address[i] < 0x10) Serial.print("0");
                Serial.print(address[i], HEX);
                if (i < 7) Serial.print(", ");
            }
            Serial.println("  },");
        } while (ow.search(address));

        Serial.println("};");
        Serial.print("// nr devices found: ");
        Serial.println(count);
    }

    return count;
}

void setupDallas() {
    // start serial port
    Serial.println("Dallas Temperature IC Control Library Demo");
    findDevices(oneWire, ONE_WIRE_BUS);

    // Start up the library
    sensors.begin();
}

void loopDallas() {
    // call sensors.requestTemperatures() to issue a global temperature
    // request to all devices on the bus
    Serial.print("Requesting temperatures...");
    sensors.requestTemperatures(); // Send the command to get temperatures
    Serial.println("DONE");
    // After we got the temperatures, we can print them here.
    // We use the function ByIndex, and as an example get the temperature from the first sensor only.
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(sensors.getTempCByIndex(0));
}

