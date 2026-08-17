#!/usr/bin/env python3

import sys
import mido

input_midi = mido.get_input_names()

if len(input_midi) == 0:
    sys.exit("Not found any midi inputs")

selected_input = 0

if len(input_midi) > 0:
    i = 0
    while i < len(input_midi):
        print(str(i + 1) + ". " + input_midi[i])
        i += 1
    print("Which select ?")
    selected_input = int(input("Enter your age: "))
    selected_input = selected_input - 1
    if selected_input >= len(input_midi):
        sys.exit("Could not select input")

port_name = input_midi[selected_input]

print(f"Listening on {port_name}...")

counter = 0
with mido.open_input(port_name) as in_port:
    for msg in in_port:
        print(msg)
        # Example of filtering for note-on events
        if msg.type == 'note_on':
            print(f"{counter} Note: {msg.note} | Velocity: {msg.velocity}")
            counter += 1
