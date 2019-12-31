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

const char *pidSensorTypes[] = {"MultiLevelSensor", "Sensor", nullptr};
ThingDevice pidSensor("pid", "PID servo regulation", pidSensorTypes);
ThingProperty pidServoProperty("servo", "Servo regulating stove air inlet", NUMBER, "LevelProperty");
ThingProperty pidSetpointChimneyProperty("chimney_setpoint", "Chimney temperature set point", NUMBER,
                                         "TemperatureProperty");
ThingProperty pidSetpointRoomProperty("room_setpoint", "Room temperature set point", NUMBER, "TemperatureProperty");

int isAdapterPresent() {
    if (!adapter) {
        Serial.println("No WebThing adapter, resetup");
        setupWebThing();
        return 0;
    }
    return 1;
}

void updateWebThing(double temp, double hum, double thermocouple) {
    if (!isAdapterPresent()) {
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

void setupWebThing() {
    if (WiFi.localIP()) {
        adapter = new WebThingAdapter("ESP32", WiFi.localIP());

        dhtSensor.addProperty(&tempSensorProperty);
        dhtSensor.addProperty(&humiditySensorProperty);
        adapter->addDevice(&dhtSensor);

        thermocoupleSensor.addProperty(&thermocoupleSensorProperty);
        adapter->addDevice(&thermocoupleSensor);

        pidSensor.addProperty(&pidServoProperty);
        pidSensor.addProperty(&pidSetpointChimneyProperty);
        pidSensor.addProperty(&pidSetpointRoomProperty);
        adapter->addDevice(&pidSensor);

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

void updatePIDWebThing(double servo, double setpointChimney, double setpointRoom) {
    if (!isAdapterPresent()) {
        return;
    }
    ThingPropertyValue value;
    value.number = servo;
    pidServoProperty.setValue(value);
    value.number = setpointChimney;
    pidSetpointChimneyProperty.setValue(value);
    value.number = setpointRoom;
    pidSetpointRoomProperty.setValue(value);
    adapter->update();
}