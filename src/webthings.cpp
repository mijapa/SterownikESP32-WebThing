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

const char *touchSensorTypes[] = {"OnOffSwitch", "Sensor", nullptr};
ThingDevice touchSensor("touch", "Touch Sensor", touchSensorTypes);
ThingProperty UPtouchProperty("up_touch", "UP", BOOLEAN, "OnOffSwitch");
ThingProperty DOWNtouchProperty("down_touch", "DOWN", BOOLEAN, "OnOffSwitch");
ThingProperty LEFTtouchProperty("left_touch", "LEFT", BOOLEAN, "OnOffSwitch");
ThingProperty RIGHTtouchProperty("right_touch", "RIGHT", BOOLEAN, "OnOffSwitch");
ThingProperty MIDDLEtouchProperty("middle_touch", "MIDDLE", BOOLEAN, "OnOffSwitch");

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
        pidSetpointRoomProperty.minimum = 18;
        pidSetpointRoomProperty.maximum = 22;
        pidSetpointRoomProperty.title = "Room Temperature Setpoint";
        pidSensor.addProperty(&pidSetpointRoomProperty);

        ThingPropertyValue value;
        value.string = &mode;
        pidHeatingCoolingProperty.setValue(value);
        pidHeatingCoolingProperty.title = "Driver Mode";
        pidSensor.addProperty(&pidHeatingCoolingProperty);

        pidChimneyTempProperty.title = "Chimney Temperature";
        pidSensor.addProperty(&pidChimneyTempProperty);

        pidSetpointChimneyProperty.title = "Chimney Temperature Setpoint";
        pidSensor.addProperty(&pidSetpointChimneyProperty);

        pidServoProperty.unit = "percent";
        pidServoProperty.readOnly = "true";
        pidServoProperty.multipleOf = 0.1;
        pidServoProperty.title = "Air inlet";
        pidSensor.addProperty(&pidServoProperty);

        adapter->addDevice(&pidSensor);

        dallasProperty.multipleOf = 0.1;
        dallasProperty.title = "Inside temperature";
        dallasSensor.addProperty(&dallasProperty);

        adapter->addDevice(&dallasSensor);

        UPtouchProperty.readOnly = true;
        UPtouchProperty.title = "UP";
        touchSensor.addProperty(&UPtouchProperty);
        DOWNtouchProperty.readOnly = true;
        DOWNtouchProperty.title = "DOWN";
        touchSensor.addProperty(&DOWNtouchProperty);
        LEFTtouchProperty.readOnly = true;
        LEFTtouchProperty.title = "LEFT";
        touchSensor.addProperty(&LEFTtouchProperty);
        RIGHTtouchProperty.readOnly = true;
        RIGHTtouchProperty.title = "RIGHT";
        touchSensor.addProperty(&RIGHTtouchProperty);
        MIDDLEtouchProperty.readOnly = true;
        MIDDLEtouchProperty.title = "MIDDLE";
        touchSensor.addProperty(&MIDDLEtouchProperty);
        adapter->addDevice(&touchSensor);

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

void updateTouchWebThing(bool up, bool down, bool left, bool right, bool middle){
    ThingPropertyValue value;
    value.boolean = up;
    UPtouchProperty.setValue(value);
    adapter->update();
    value.boolean = down;
    DOWNtouchProperty.setValue(value);
    adapter->update();
    value.boolean = left;
    LEFTtouchProperty.setValue(value);
    adapter->update();
    value.boolean = right;
    RIGHTtouchProperty.setValue(value);
    adapter->update();
    value.boolean = middle;
    MIDDLEtouchProperty.setValue(value);
    adapter->update();
}

void setWebThingRoomSetpoint(double setpointRoom){
    ThingPropertyValue value;
    value.number = setpointRoom;
    pidSetpointRoomProperty.setValue(value);
    adapter->update();
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
    value.number = tempChimney;
    pidChimneyTempProperty.setValue(value);
    adapter->update();
    value.number = tempRoom;
    pidRoomTemperatureProperty.setValue(value);
    adapter->update();
}

void updateDallasWebThing(double temp){
    ThingPropertyValue value;
    value.number = temp;
    dallasProperty.setValue(value);
    adapter->update();
}

double readSetpointRoomTempFromGateway() {
    if (!isAdapterPresent()) {
        return 0;
    }
    adapter->update();
    double setpointRoomTempFromGateway = pidSetpointRoomProperty.getValue().number;
    return setpointRoomTempFromGateway;
}