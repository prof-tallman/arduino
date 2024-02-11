
// www.elegoo.com
// 2018.10.24

/*
  LED1 should be lit, showing power. LED2 indicates sound input, and the sensitivity is adjusted by potentiometer.
  There is a tiny screw on the blue potentiometer block that you can use for adjustment. Turning that
  clockwise lowers the potentiometer value, while counter-clockwise raises the potentiometer value.
  Use the potentiometer to adjust the Sound Sensor sensitivity. Turn the potentiometer
  several rotations until you see the LED2 extinguish (or just faintly blink). This might be slightly greater than
  500, if you are also watching Serial Monitor (inital adjustment), or, Serial Plotter (the latter is prefererd for observation).
  Special thanks to user CRomer, for his input and hard work!
*/

// Demonstrates use of the Sound Sensor
// Modified by Prof. Tallman 1/30/2024

#define SOUND_ANALOG_PIN  A0
#define SOUND_DIGITAL_PIN 4
int  analogValue = 0;         // Define variable to store the analog value coming from the Sound Sensor
int  digitalValue;            // Define variable to store the digital value coming from the Sound Sensor

void setup()
{
  Serial.begin(9600);
  pinMode(SOUND_DIGITAL_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  int value_a = analogRead(SOUND_ANALOG_PIN);
  int value_d = digitalRead(SOUND_DIGITAL_PIN);
  Serial.println(value_a);
  digitalWrite(LED_BUILTIN, value_d);
  delay(50);
}
