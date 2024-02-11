
// Demonstrates use of buttons with a pull-up resistor
// Created by Prof. Tallman 1/20/2024

#define BUTTON_PIN 5

void setup() 
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() 
{
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    Serial.println("Button Pressed");
  }
  delay(10);
}
