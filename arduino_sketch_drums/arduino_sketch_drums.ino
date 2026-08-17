/*
  MIDI note player

  This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note
  data. If this circuit is connected to a MIDI synth, it will play the notes
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

#include <MIDIUSB.h>
#include <MIDIUSB_Defs.h>
#include <frequencyToNote.h>
#include <pitchToFrequency.h>
#include <pitchToNote.h>

void setup() {
  // Set MIDI baud rate:
  // Serial.begin(31250);
}

//
// Send a short, 3-byte MIDI message
//
// void MidiSend(byte cmd, byte data1, byte data2)
//{
//  Serial.write(cmd | CHANNEL) ;
//  Serial.write(data1) ;
//  Serial.write(data2) ;
//}

//
// MIDI note ON message
//
// void MidiNoteOn(byte note, byte velocity)
//{
//  MidiSend(0x90, note, velocity) ;
//}

//
// MIDI note OFF message
//
// void MidiNoteOff(byte note)
//{
//  // MidiSend(0x80, note, 0) ;
//  MidiSend(0x90, note, 0) ;
//}

const byte MIDI_CHANNEL = 0; // MIDI Channel 1 (0-15 map to 1-16)
const byte NOTE_NUMBER  = 60; // 60 is Middle C (C4)
const byte NOTE_VELOCITY = 127; // Max volume/velocity
const int THRESHOLD = 40;

// Helper function to format and send a MIDI Note On message
void noteOn(byte channel, byte pitch, byte velocity) {
  // 0x09 = Note On command header type
  // 0x90 = Note On status byte + channel
  midiEventPacket_t noteOn = {0x09, (byte)(0x90 | channel), pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush(); // Send the packet immediately
}

// Helper function to format and send a MIDI Note Off message
void noteOff(byte channel, byte pitch, byte velocity) {
  // 0x08 = Note Off command header type
  // 0x80 = Note Off status byte + channel
  midiEventPacket_t noteOff = {0x08, (byte)(0x80 | channel), pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush(); // Send the packet immediately
}


// kickDrum

// void snareDrum(int cmd, int pitch, int velocity) {
//   const int snareNote = 0x1E;
//   Serial.write(0x90);
//   Serial.write(snareNote);
//   Serial.write(velocity);
// }

void loop() {
  // play notes from F#-0 (0x1E) to F#-5 (0x5A):
  //  Serial.write(144);
  //  Serial.write(0x1E);
  //  Serial.write(0x45);
  int sensorReading = analogRead(A0);
  int note0 = 0x1E;
  int zero = 0x0;
  int playing = 0;
  int counter = 0;
  while (true) {
    int sensorReading = analogRead(A0);

    if (sensorReading > THRESHOLD) {
      noteOn(MIDI_CHANNEL, NOTE_NUMBER, NOTE_VELOCITY);
      delay(50);
      noteOff(MIDI_CHANNEL, NOTE_NUMBER, NOTE_VELOCITY);
      delay(50);
    }

    // if (sensorReading > threshold) {
    //   if (playing) {
    //     Serial.write(0x80);
    //     Serial.write(note0);
    //     Serial.write(zero);
    //     playing = 0;
    //   }
    //   Serial.write(0x90);
    //   Serial.write(note0);
    //   Serial.write(0x45);
    //   counter = 0;
    //   playing = 1;
    // }
    // counter++;
    // if (counter > 1000) {
    //   Serial.write(0x80);
    //   Serial.write(note0);
    //   Serial.write(zero);
    //   playing = 0;
    // }
    // delay(1);

    // for (int note = 0x1E; note < 0x5A; note++) {
    //   int sensorReading = analogRead(A0);
    //   int note0 = note;
    //   if (sensorReading > threshold) {
    //     note0 = 0x1E;
    //     Serial.println("Knock!");
    //   }
    //   Serial.write(0x90);
    //   Serial.write(note0);
    //   Serial.write(0x45);
    //   delay(100);
    //   Serial.write(0x80);
    //   Serial.write(note0);
    //   Serial.write(zero);
    //   delay(100);
    // }
  }
}

// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
