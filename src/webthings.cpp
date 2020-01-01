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

const char *pidSensorTypes[] = {"Thermostat", "MultiLevelSensor", "TemperatureSensor", "Sensor", nullptr};
ThingDevice pidSensor("pid", "PID servo regulation", pidSensorTypes);
ThingProperty pidServoProperty("servo", "Servo regulation", NUMBER, "LevelProperty");
ThingProperty pidSetpointChimneyProperty("chimney_setpoint", "Chimney setpoint", NUMBER,
                                         "TemperatureProperty");
ThingProperty pidSetpointRoomProperty("room_setpoint", "Room setpoint", NUMBER, "TargetTemperatureProperty");

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
        humiditySensorProperty.unit = "percent";
        humiditySensorProperty.readOnly = "true";
        dhtSensor.addProperty(&humiditySensorProperty);
        adapter->addDevice(&dhtSensor);

        thermocoupleSensor.addProperty(&thermocoupleSensorProperty);
        adapter->addDevice(&thermocoupleSensor);

        pidServoProperty.unit = "percent";
        pidServoProperty.readOnly = "true";
        pidServoProperty.description = "Servo";
        pidSensor.addProperty(&pidServoProperty);
        pidSensor.addProperty(&pidSetpointChimneyProperty);
        pidSetpointRoomProperty.unit = "celsius";
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

double readSetpointRoomTempFromGateway() {
    if (!isAdapterPresent()) {
        return 0;
    }
    adapter->update();
    double setpointRoomTempFromGateway = pidSetpointRoomProperty.getValue().number;
    Serial.println(setpointRoomTempFromGateway);
    return setpointRoomTempFromGateway;
}