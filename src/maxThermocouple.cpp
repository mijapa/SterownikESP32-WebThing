#include "maxThermocouple.h"
#include <max6675.h>

MAX6675 thermocouple(THERMO_CLK_PIN, THERMO_CS_PIN, THERMO_DO_PIN);

double lastTemp = 20;

double readThermocouple() {
    double temp = thermocouple.readCelsius();
    if (temp < -30 || temp > 800 || isnan(temp) || abs(temp -lastTemp) > TEMP_THRESHOLD) {
        Serial.println("FAILED TO READ THERMOCOUPLE!!");
        return 999; //returning high temperature to prevent overheat
    }
    lastTemp = temp;
    return temp;
}
