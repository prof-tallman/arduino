//www.elegoo.com
//2016.12.9

// Demonstrates use of the IR Receiver and Remote Control
// Modified by Prof. Tallman 1/30/2024

#include "IRremote.h"
#define IR_RECV_PIN 8
IRrecv ir_obj(IR_RECV_PIN);

#define IR_POWER_CODE     0xFFA25D
#define IR_FN_STOP_CODE   0xFFE21D
#define IR_VOL_MORE_CODE  0xFF629D
#define IR_SKIP_BACK_CODE 0xFF22DD
#define IR_PAUSE_CODE     0xFF02FD
#define IR_SKIP_FWRD_CODE 0xFFC23D
#define IR_ARROW_DN_CODE  0xFFE01F
#define IR_VOL_LESS_CODE  0xFFA857
#define IR_ARROW_UP_CODE  0xFF906F
#define IR_EQ_CODE        0xFF9867
#define IR_ST_REPT_CODE   0xFFB04F
#define IR_NUM_0_CODE     0xFF6897
#define IR_NUM_1_CODE     0xFF30CF
#define IR_NUM_2_CODE     0xFF18E7
#define IR_NUM_3_CODE     0xFF7A85
#define IR_NUM_4_CODE     0xFF10EF
#define IR_NUM_5_CODE     0xFF38C7
#define IR_NUM_6_CODE     0xFF5AA5
#define IR_NUM_7_CODE     0xFF42BD
#define IR_NUM_8_CODE     0xFF4AB5
#define IR_NUM_9_CODE     0xFF52AD
#define IR_REPEAT_CODE    0xFFFFFFFF

void translateIR(decode_results ir_value)
{
  switch(ir_value.value)
  {
    case IR_POWER_CODE:     Serial.println("POWER");     break;
    case IR_FN_STOP_CODE:   Serial.println("FUNC/STOP"); break;
    case IR_VOL_MORE_CODE:  Serial.println("VOL+");      break;
    case IR_SKIP_BACK_CODE: Serial.println("FAST REV");  break;
    case IR_PAUSE_CODE:     Serial.println("PAUSE");     break;
    case IR_SKIP_FWRD_CODE: Serial.println("FAST FWD");  break;
    case IR_ARROW_DN_CODE:  Serial.println("DOWN");      break;
    case IR_VOL_LESS_CODE:  Serial.println("VOL-");      break;
    case IR_ARROW_UP_CODE:  Serial.println("UP");        break;
    case IR_EQ_CODE:        Serial.println("EQ");        break;
    case IR_ST_REPT_CODE:   Serial.println("ST/REPT");   break;
    case IR_NUM_0_CODE:     Serial.println("0");         break;
    case IR_NUM_1_CODE:     Serial.println("1");         break;
    case IR_NUM_2_CODE:     Serial.println("2");         break;
    case IR_NUM_3_CODE:     Serial.println("3");         break;
    case IR_NUM_4_CODE:     Serial.println("4");         break;
    case IR_NUM_5_CODE:     Serial.println("5");         break;
    case IR_NUM_6_CODE:     Serial.println("6");         break;
    case IR_NUM_7_CODE:     Serial.println("7");         break;
    case IR_NUM_8_CODE:     Serial.println("8");         break;
    case IR_NUM_9_CODE:     Serial.println("9");         break;
    case IR_REPEAT_CODE:    Serial.println("REPEAT");    break;  
    default: Serial.println("UNK");                      break;
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  ir_obj.enableIRIn();
}

void loop()
{
  decode_results ir_value;
  if (ir_obj.decode(&ir_value))
  {
    translateIR(ir_value); 
    ir_obj.resume();
  }  
  delay(500);
}


