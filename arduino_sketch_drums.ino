/*
  MIDI note player

  This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note data.
  If this circuit is connected to a MIDI synth, it will play the notes
  F#-0 (0x1E) to F#-5 (0x5A) in sequence.

  The circuit:
  - digital in 1 connected to MIDI jack pin 5
  - MIDI jack pin 2 connected to ground
  - MIDI jack pin 4 connected to +5V through 220 ohm resistor
  - Attach a MIDI cable to the jack, then to a MIDI synth, and play music.

  created 13 Jun 2006
  modified 13 Aug 2012
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Midi
*/

/*

Modified by Evgenii Sopov

*/

#include <pitchToFrequency.h>
#include <MIDIUSB_Defs.h>
#include <frequencyToNote.h>
#include <pitchToNote.h>
#include <MIDIUSB.h>

void setup() {
  // Set MIDI baud rate:
  Serial.begin(31250);
}

//
// Send a short, 3-byte MIDI message
//
//void MidiSend(byte cmd, byte data1, byte data2)
//{
//  Serial.write(cmd | CHANNEL) ;
//  Serial.write(data1) ; 
//  Serial.write(data2) ; 
//}

//
// MIDI note ON message
//
//void MidiNoteOn(byte note, byte velocity)
//{
//  MidiSend(0x90, note, velocity) ; 
//}

//
// MIDI note OFF message
//
//void MidiNoteOff(byte note)
//{
//  // MidiSend(0x80, note, 0) ; 
//  MidiSend(0x90, note, 0) ; 
//}


const int threshold = 100;

void loop() {
  // play notes from F#-0 (0x1E) to F#-5 (0x5A):
//  Serial.write(144);
//  Serial.write(0x1E);
//  Serial.write(0x45);
  int sensorReading = analogRead(A0);
  int note0 = 0x1E;
  int playing = 0;
  int counter = 0;
  while (true) {
      int sensorReading = analogRead(A0);
      
      if (sensorReading > threshold) {
        if (playing) {
          Serial.write(0x80);
          Serial.write(note0);
          Serial.write(0x00);
          playing = 0;
        }
        Serial.write(0x90);
        Serial.write(note0);
        Serial.write(0x45);
        counter = 0;
        playing = 1;
      }
      counter ++;
      if (counter > 1000) {
        Serial.write(0x80);
        Serial.write(note0);
        Serial.write(0x00);
        playing = 0;
      }
      delay(1);

//    for (int note = 0x1E; note < 0x5A; note++) {
//      int sensorReading = analogRead(A0);
//      int note0 = note;
//      if (sensorReading > threshold) {
//        note0 = 0x1E;
//        Serial.println("Knock!");
//      }
//      Serial.write(0x90);
//      Serial.write(note0);
//      Serial.write(0x45);
//      delay(100);
//      Serial.write(0x80);
//      Serial.write(note0);
//      Serial.write(0x0);
//      delay(100);
//    }
  }
}

// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}