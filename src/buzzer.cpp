#include <HardwareSerial.h>
#include <ESP32Tone.h>
#include "buzzer.h"

#define BUZZER_PIN 33 //switched witch 32 on the board description

void toneHello() {
    int freq = 2000;
    int channel = 15;
    int resolution = 8;

    Serial.println("Tone Hello");
//    tone(BUZZER_PIN, 2500, 2500);
    ledcSetup(channel, freq, resolution);
    ledcAttachPin(BUZZER_PIN, channel);

    ledcWrite(channel, 100);
    ledcWriteTone(channel, 4000);
    delay(50);
    //todo change delay to timer
    ledcWrite(channel, 0);
//    ledcDetachPin(BUZZER_PIN);
//    digitalWrite(BUZZER_PIN, LOW);

}
