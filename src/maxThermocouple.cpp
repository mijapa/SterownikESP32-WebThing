#include "maxThermocouple.h"
#include <max6675.h>

#define THERMO_DO_PIN 4
#define THERMO_CS_PIN 17
#define THERMO_CLK_PIN 2

#define TEMP_THRESHOLD 30

MAX6675 thermocouple(THERMO_CLK_PIN, THERMO_CS_PIN, THERMO_DO_PIN);

double lastTemp = 20;

double readThermocouple() {
    double temp = thermocouple.readCelsius();
    if (temp < -30 || temp > 800 || isnan(temp) || abs(temp -lastTemp) > TEMP_THRESHOLD) {
        Serial.println("FAILED TO READ THERMOCOUPLE!!");
        return 999; //returning high temperature to prevent overheat
    }
    Serial.print("Termocouple: ");
    Serial.println(temp);
    lastTemp = temp;
    return temp;
}
