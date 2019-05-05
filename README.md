# Anubis

## General description of the project 

Anubis is a simple 8 steps sequencer based on the [Punk Console](https://www.instructables.com/id/Arduino-Step-Sequencer/). It's a digital sequencer whose software is flashed on an arduino board and which parameters are controled by analog devices.

Anubis includes its own speaker.

The main features controled by big handy pots are the following:
* Tempo
* Note length
* Master volume

As described above, the musical phrase is an 8 steps sequences. Each note has its own individual controls:
* Pitch (skinny pot)
* Mute option (knob)
* 1 LED indicating the note status (ON if the note is played, else OFF)

In a future release, it will be possible to choose the device that produces the sound: built-in speaker or a jack output to an audio interface.

## Conception

The system is constituted with: 
- 10 analog inputs: 10 control knobs
- 10 digital outputs: 9 LEDs + 1 knob (master volume) 
- 9 digital inputs: 8 buttons + 1 switch

The only board that satisfies these specifications is the Arduino Mega
