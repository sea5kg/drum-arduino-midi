#include <MIDIUSB.h>
#include <MIDIUSB_Defs.h>
#include <frequencyToNote.h>
#include <pitchToFrequency.h>
#include <pitchToNote.h>

void setup() {
  Serial.begin(115200);
  // Set MIDI baud rate:
}

const byte MIDI_CHANNEL = 0; // MIDI Channel 1 (0-15 map to 1-16)
const byte NOTE_NUMBER = 60; // 60 is Middle C (C4)
// 40 (E3/E2): Electric Snare (Electronic or tighter layered snare)
// 37 (C#3/C#2): Side Stick / Rimshot (Cross-stick sound)
const byte SNARE_NOTE = 38; // 38 (D3/D2): Acoustic Snare (Standard main snare hit)
const int SNARE_THRESHOLD = 42;
const byte NOTE_VELOCITY = 127; // Max volume/velocity
const int THRESHOLD = 42;

// Helper function to format and send a MIDI Note On message
void noteOn(byte pitch, byte velocity) {
  // 0x09 = Note On command header type
  // 0x90 = Note On status byte + channel
  midiEventPacket_t noteOn = {0x09, (byte)(0x90 | MIDI_CHANNEL), pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush(); // Send the packet immediately
}

// Helper function to format and send a MIDI Note Off message
void noteOff(byte pitch) {
  byte velocity = 0x0;
  // 0x08 = Note Off command header type
  // 0x80 = Note Off status byte + channel
  midiEventPacket_t noteOff = {0x08, (byte)(0x80 | MIDI_CHANNEL), pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush(); // Send the packet immediately
}

int readAnalogSensor_Snare() {
  return analogRead(A0);
}

int last_velocity_snare = 0;
bool note_on_snare = false;

void handleSnareDrum() {
  int sensorValue = readAnalogSensor_Snare();
  // Map analog reading (0-1023) to MIDI velocity range (0-127)
  byte velocity = map(sensorValue, 0, 1023, 0, 127);

  if (velocity < 2) {
    velocity = 0;
  }

  if (last_velocity_snare < velocity) {
    last_velocity_snare = velocity;
    return;
  }

  if (last_velocity_snare > velocity) {
    last_velocity_snare = velocity;
    if (note_on_snare) {
      note_on_snare = false;
      // noteOff(SNARE_NOTE);
    }
    return;
  }

  if (velocity > 0) {
    noteOn(SNARE_NOTE, velocity);
    note_on_snare = true;
  }
  last_velocity_snare = velocity;
}

// kickDrum
// hiHat
// cymbal

void loop() {
  while (true) {
    handleSnareDrum();
    delay(10);
  }
}
