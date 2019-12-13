#include <WebThingAdapter.h>
#include "webthings.h"

WebThingAdapter *adapter;
const char *dhtSensorTypes[] = {"TemperatureSensor", "MultiLevelSensor", "Sensor", nullptr};
ThingDevice dhtSensor("dht22", "DHT22 Temperature & Humidity sensor", dhtSensorTypes);
ThingProperty tempSensorProperty("temperature", "Temperature", NUMBER, "TemperatureProperty");
ThingProperty humiditySensorProperty("humidity", "Humidity", NUMBER, "LevelProperty");

const char *thermocoupleSensorTypes[] = {"TemperatureSensor", "Sensor", nullptr};
ThingDevice thermocoupleSensor("thermo", "MAX6675 Temperature sensor", thermocoupleSensorTypes);
ThingProperty thermocoupleSensorProperty("temperature", "Temperature", NUMBER, "TemperatureProperty");

void setupWebThing() {
    if (WiFi.localIP()) {
        adapter = new WebThingAdapter("ESP32", WiFi.localIP());

        dhtSensor.addProperty(&tempSensorProperty);
        dhtSensor.addProperty(&humiditySensorProperty);
        adapter->addDevice(&dhtSensor);

        thermocoupleSensor.addProperty(&thermocoupleSensorProperty);
        adapter->addDevice(&thermocoupleSensor);

        adapter->begin();
        Serial.println("HTTP server started");
        Serial.print("http://");
        Serial.print(WiFi.localIP());
        Serial.print("/things/");
        Serial.println(dhtSensor.id);
    } else {
        Serial.println("No local IP");
    }
}

void updateWebThing(double temp, double hum, double thermocouple) {
    if (!adapter) {
        Serial.println("No WebThing adapter, resetup");
        setupWebThing();
        return;
    }
    ThingPropertyValue value;
    value.number = temp;
    tempSensorProperty.setValue(value);
    value.number = hum;
    humiditySensorProperty.setValue(value);

    value.number = thermocouple;
    thermocoupleSensorProperty.setValue(value);

    adapter->update();
}