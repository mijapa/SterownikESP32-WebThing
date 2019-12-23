#include <HardwareSerial.h>
#include <ESP32Tone.h>
#include "buzzer.h"

#define BUZZER_PIN 33 //switched witch 32 on the board description

void toneHello() {
    int freq = 2000;
    int channel = 0;
    int resolution = 8;

    Serial.println("Tone Hello");
//    tone(BUZZER_PIN, 2500, 2500);
    ledcSetup(channel, freq, resolution);
    ledcAttachPin(BUZZER_PIN, channel);

    ledcWrite(channel, 200);
    ledcWriteTone(channel, 4000);
    delay(50);
    //todo change delay to timer

    ledcDetachPin(BUZZER_PIN);

//    for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle=dutyCycle+10){
//
//        Serial.println(dutyCycle);
//
//        ledcWrite(channel, dutyCycle);
//        delay(1000);
//    }
//
//    ledcWrite(channel, 125);
//
//    for (int freq = 255; freq < 10000; freq = freq + 250){
//
//        Serial.println(freq);
//
//        ledcWriteTone(channel, freq);
//        delay(1000);
//    }



//    //melody
//    int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};  // notes in the melody:
//    int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};// note durations: 4 = quarter note, 8 = eighth note, etc.:
//
//    for (int thisNote = 0; thisNote < 8; thisNote++) {// iterate over the notes of the melody:
//        // to calculate the note duration, take one second
//        // divided by the note type.
//        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
//        int noteDuration = 1000 / noteDurations[thisNote];
//        tone(BUZZER_PIN, melody[thisNote], noteDuration); //(pin, frequency, duration)
//
//        // to distinguish the notes, set a minimum time between them.
//        // the note's duration + 30% seems to work well:
//        int pauseBetweenNotes = noteDuration * 1.30;
//        delay(pauseBetweenNotes);
//        // stop the tone playing:
//        noTone(BUZZER_PIN);
//        //Serial.println("zagralo");//sprawdzenie na SERIAL czy instrukcja została wykonana
//    }
}
