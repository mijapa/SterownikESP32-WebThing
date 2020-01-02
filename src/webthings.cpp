#include <WebThingAdapter.h>
#include <Ticker.h>
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
ThingProperty pidRoomTemperatureProperty("room_temp", "Room Temperature", NUMBER,
                                         "TemperatureProperty");
ThingProperty pidSetpointRoomProperty("room_setpoint", "Room Setpoint", NUMBER, "TargetTemperatureProperty");
ThingProperty pidHeatingCoolingProperty("on_off", "Fire", STRING, "HeatingCoolingProperty");
const char *heatingCoolingSuportStates[] = {"off", "heating"};
String mode = "heating";
ThingProperty pidSetpointChimneyProperty("chimney_setpoint", "Chimney Setpoint", NUMBER,
                                         "TemperatureProperty");
ThingProperty pidChimneyTempProperty("chimney_temp", "Chimney Temperature", NUMBER,
                                     "TemperatureProperty");

const char *dallasSensorTypes[] = {"TemperatureSensor", "Sensor", nullptr};
ThingDevice dallasSensor("dallas", "Dallas Temperature sensor", dallasSensorTypes);
ThingProperty dallasProperty("dallas", "Dallas temperature", NUMBER, "TemperatureProperty");

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
    adapter->update();
    value.number = hum;
    humiditySensorProperty.setValue(value);
    adapter->update();

    value.number = thermocouple;
    thermocoupleSensorProperty.setValue(value);
    adapter->update();
}

void setupWebThing() {
    if (WiFi.localIP()) {
        adapter = new WebThingAdapter("ESP32", WiFi.localIP());

        tempSensorProperty.multipleOf = 0.1;
        dhtSensor.addProperty(&tempSensorProperty);
        humiditySensorProperty.unit = "percent";
        humiditySensorProperty.readOnly = "true";
        humiditySensorProperty.multipleOf = 0.1;
        humiditySensorProperty.title = "Humidity";
        dhtSensor.addProperty(&humiditySensorProperty);

        adapter->addDevice(&dhtSensor);


        thermocoupleSensor.addProperty(&thermocoupleSensorProperty);

        adapter->addDevice(&thermocoupleSensor);


        pidRoomTemperatureProperty.title = "Room Temperature";
        pidRoomTemperatureProperty.multipleOf = 0.1;
        pidSensor.addProperty(&pidRoomTemperatureProperty);

        pidSetpointRoomProperty.unit = "celsius";
        pidSetpointRoomProperty.multipleOf = 0.1;
        pidSetpointRoomProperty.title = "Room Temperature Setpoint";
        pidSensor.addProperty(&pidSetpointRoomProperty);

        ThingPropertyValue value;
        value.string = &mode;
        pidHeatingCoolingProperty.setValue(value);
//        pidHeatingCoolingProperty.propertyEnum = heatingCoolingSuportStates;
        pidHeatingCoolingProperty.title = "Driver Mode";
        pidSensor.addProperty(&pidHeatingCoolingProperty);

        pidChimneyTempProperty.title = "Chimney Temperature";
        pidChimneyTempProperty.multipleOf = 0.1;
        pidSensor.addProperty(&pidChimneyTempProperty);

        pidSetpointChimneyProperty.title = "Chimney Temperature Setpoint";
        pidSensor.addProperty(&pidSetpointChimneyProperty);

        pidServoProperty.unit = "percent";
        pidServoProperty.readOnly = "true";
        pidServoProperty.multipleOf = 0.1;
        pidServoProperty.title = "Air inlet";
        pidSensor.addProperty(&pidServoProperty);

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

void updatePIDWebThing(double servo, double setpointChimney, double setpointRoom, double tempChimney, double tempRoom) {
    if (!isAdapterPresent()) {
        return;
    }
    ThingPropertyValue value;
    value.number = servo;
    pidServoProperty.setValue(value);
    adapter->update();
    value.number = setpointChimney;
    pidSetpointChimneyProperty.setValue(value);
    adapter->update();
    value.number = setpointRoom;
    pidSetpointRoomProperty.setValue(value);
    adapter->update();
    value.number = tempChimney;
    pidChimneyTempProperty.setValue(value);
    adapter->update();
    value.number = tempRoom;
    pidRoomTemperatureProperty.setValue(value);
    adapter->update();
}

double readSetpointRoomTempFromGateway() {
    if (!isAdapterPresent()) {
        return 0;
    }
    double setpointRoomTempFromGateway = pidSetpointRoomProperty.getValue().number;
    return setpointRoomTempFromGateway;
}