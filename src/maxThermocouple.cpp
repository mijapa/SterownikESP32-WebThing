#include "maxThermocouple.h"
#include <max6675.h>

#define THERMO_DO_PIN 4
#define THERMO_CS_PIN 17
#define THERMO_CLK_PIN 2

MAX6675 thermocouple(THERMO_CLK_PIN, THERMO_CS_PIN, THERMO_DO_PIN);

double readThermocouple() {
    double temp = thermocouple.readCelsius();
    Serial.print("Termocouple: ");
    Serial.println(temp);
    return temp;
}
