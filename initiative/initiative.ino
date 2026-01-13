#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

// Dip switches to configure 'hot' wires
#define DIP_PIN1 7
#define DIP_PIN2 8
#define DIP_PIN3 9
#define DIP_PIN4 10
#define DIP_PIN5 11
#define DIP_PIN6 12
#define DIP_COUNT 6

// Pins going to wires that can be cut
#define WIRE_PIN1 28
#define WIRE_PIN2 30 
#define WIRE_PIN3 32
#define WIRE_PIN4 34
#define WIRE_PIN5 36
#define WIRE_PIN6 38
#define WIRE_COUNT 6

#define DOT_MASK 0b01000000
#define ONE_SECOND_MS 1000
uint8_t all_leds_on[] = { 0xff, 0xff, 0xff, 0xff };

bool dip_switches[6];
bool cut_wires[6];

TM1637Display display(CLK, DIO);
unsigned long now_ms;
unsigned long last_ms;
unsigned int display_time;
unsigned int minutes;
unsigned int seconds;

void setup()
{
  // Debug output
  Serial.begin(9600);
  delay(1000);
  Serial.println();

  // Initialize internal variables and the timer
  now_ms = 0;
  last_ms = 0;
  display.setBrightness(0x0f);

  // Show 10:00 minutes
  minutes = 10;
  seconds = 00;
  display_time = minutes * 100 + seconds;
  display.showNumberDecEx(display_time, DOT_MASK);

  // Initialize input wires
  pinMode(DIP_PIN1, INPUT_PULLUP);
  pinMode(DIP_PIN2, INPUT_PULLUP);
  pinMode(DIP_PIN3, INPUT_PULLUP);
  pinMode(DIP_PIN4, INPUT_PULLUP);
  pinMode(DIP_PIN5, INPUT_PULLUP);
  pinMode(DIP_PIN6, INPUT_PULLUP);
  pinMode(WIRE_PIN1, INPUT_PULLUP);
  pinMode(WIRE_PIN2, INPUT_PULLUP);
  pinMode(WIRE_PIN3, INPUT_PULLUP);
  pinMode(WIRE_PIN4, INPUT_PULLUP);
  pinMode(WIRE_PIN5, INPUT_PULLUP);
  pinMode(WIRE_PIN6, INPUT_PULLUP);

  // Read DIP switches that configure the wires-to-cut
  // One DIP should be 0 (diffuse) and all the rest 1s (explode)
  for(int i = 0; i < DIP_COUNT; i++)
  {
    int current_pin = DIP_PIN1 + i;
    dip_switches[i] = digitalRead(current_pin);
    Serial.println("PIN #" + String(i) + ": " + String(dip_switches[i]));
  }

  // Debug LED to show an explosion
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void flashDisplay1000ms()
{
      display.setSegments(all_leds_on);
      delay(500);
      display.clear();
      delay(500);
}

void loop()
{
  // Determine if the 'defuse' wire or any of the 'hot wires' have been cut
  for(int i = 0; i < WIRE_COUNT; i++)
  {
    // These wires skip every other pin number 28, 30, 32, ...
    int current_wire = WIRE_PIN1 + (2 * i);
    cut_wires[i] = digitalRead(current_wire);

    // WIRE LOW and DIP LOW  means countdown timer is intact - do nothing
    // WIRE LOW and DIP HIGH means countdown timer is intact - do nothing
    ;
    
    // WIRE HIGH and DIP HIGH means the bomb 'explodes'
    if (cut_wires[i] == HIGH && dip_switches[i] == HIGH)
    {
      Serial.println("WIRE #" + String(i) + ": BOOM!");
      // Bomb explodes!
      digitalWrite(LED_BUILTIN, HIGH);
      while(1)
      {
        flashDisplay1000ms();
      }
    }
    
    // WIRE HIGH and DIP LOW means bomb is diffused
    if (cut_wires[i] == HIGH && dip_switches[i] == LOW)
    {
      Serial.println("WIRE #" + String(i) + ": PHEW");
      display.clear();
      while(1);
    }
  }

  // Decrement the clock until it reaches 0:00
  now_ms = millis();
  if (now_ms - last_ms >= ONE_SECOND_MS)
  {
    last_ms = now_ms;

    // reached minute :00 so switch to minute-1 :59 
    if (seconds == 0)
    {
      minutes -= 1;
      seconds = 60;
    }
    seconds -= 1;

    // Convert minutes:seconds to a 4 digit number
    if (minutes >= 1)
    {
      display_time = minutes * 100 + seconds;
      display.showNumberDecEx(display_time, DOT_MASK);
    }
    else
    {
      display.showNumberDec(seconds);
    }
  }

  if (minutes == 0 && seconds == 0)
  {
    // Counter reaches 0:00 and time is up
    // Bomb explodes!
    digitalWrite(LED_BUILTIN, HIGH);
    while(1)
    {
      flashDisplay1000ms();
    }
  }
}