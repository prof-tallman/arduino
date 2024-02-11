/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
*/

// Modified by Prof. Tallman to play Star Wars The Imperial March and to be
// more musically minded (time signature, tempo, etc)

#include "pitches.h"

// handy macro to determine the number of elements in an array
#define LENGTH_OF(x)  sizeof(x) / sizeof(*x)

// musical constants
int bpm = 95;
int time_signature = 4;

// melody is stored in parallel arrays
int notes[] = 
{
  NOTE_A3, NOTE_A3, NOTE_A3, NOTE_F3, NOTE_C4, 
  NOTE_A3, NOTE_F3, NOTE_C4, NOTE_A3,
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_C4, 
  NOTE_GS3, NOTE_F3, NOTE_C4, NOTE_A3
};
int beats[] =
{
  4, 4, 4, 8, 8, 
  4, 8, 8, 2,
  4, 4, 4, 8, 8, 
  4, 8, 8, 2
};

void play_melody()
{
  // Error checking
  if (LENGTH_OF(notes) != LENGTH_OF(beats))
  {
    return;
  }

  // Play the melody one note at a time
  int measure_time = 60.0 / bpm * 1000 * time_signature;
  for (int idx = 0; idx < LENGTH_OF(notes); idx++) 
  {
    int note_time = 0.9 * measure_time / beats[idx];
    int rest_time = 0.1 * measure_time / beats[idx];
    tone(SPEAKER_PIN, notes[idx], note_time);
    delay(rest_time);
  }

  noTone(SPEAKER_PIN);
}

void setup()
{
  play_melody()
}

void loop()
{
  // no need to drive everyone crazy by repeating the melody.
}
