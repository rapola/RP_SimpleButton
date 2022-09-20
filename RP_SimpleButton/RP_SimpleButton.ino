/*
 * Test mit Arduino Uno
 * RP 20.09.2022
 */

#include <Arduino.h>
#include "src/RP_SimpleButton.h"

const uint8_t Ta = 7;               //Button input

uint32_t ms;

RP_SimpleButton Btn;                //Button object



void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(Ta, INPUT_PULLUP);
  Serial.begin(115200);
  Btn.begin(true);                  //-> true: button is inverted, e.g. pullup

}

void loop() {
  Btn.Update(digitalRead(Ta));      //call every main loop

  digitalWrite(LED_BUILTIN, Btn.BtnState());

  
  if(millis() - ms > 500){
    Serial.print("BtnState: ");
    Serial.println(Btn.BtnState());
    Serial.println();
  }

}
