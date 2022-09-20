/*
 * Test mit Arduino Mega2560
 * RP 22.03.2021
 * lib and code working
 */

#include <Arduino.h>
#include "src/RP_PremiumButton.h"

const uint8_t Ta = 7;         //Button input

uint32_t ms;
uint32_t cnt;

RP_PremiumButton Btn;



void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(Ta, INPUT_PULLUP);
  Serial.begin(115200);
  Btn.begin(true);          //-> true: button is inverted, e.g. pullup

}

void loop() {
  Btn.Update(true, true, digitalRead(Ta));

  digitalWrite(LED_BUILTIN, Btn.BtnFlipFlop());

  
  if(millis() - ms > 500){
    Serial.print("Cnt: ");
    Serial.println(cnt);
    Serial.print("Btn.FlipFlop: ");
    Serial.println(Btn.BtnFlipFlop());
    Serial.print("Btn.delayed: ");
    Serial.println(Btn.BtnDelayed());
    Serial.print("Btn.BtnLongPress: ");
    Serial.println(Btn.BtnLongPress());
    Serial.print("Btn.press_cnt: ");
    Serial.println(Btn.press_cnt);
    Serial.println();
    Serial.println();
    ms = millis();
    cnt++;
  }

}
