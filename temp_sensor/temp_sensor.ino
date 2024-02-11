
// Demonstrates use of the DHT11 temp & humidy sensor
// Created by Prof. Tallman 1/27/2024
// Inspired by various demos from Elegoo's User Guide

#include <SimpleDHT.h>

#define BUTTON_PIN    5
#define DHT11_PIN     7


SimpleDHT11 dht11(DHT11_PIN);


void setup() 
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("==================================");
}

void loop() 
{
  // When the button is pressed, display the current temperature & humidity
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    byte temperature = 0;
    byte humidity = 0;
    int err = dht11.read(&temperature, &humidity, NULL);
    if (err == SimpleDHTErrSuccess)
    {
      Serial.print((int)temperature);
      Serial.print(" °C, ");
      Serial.print((int)humidity);
      Serial.println(" %H");
    }
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
