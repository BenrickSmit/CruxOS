#include <Arduino.h>
#include <Wire.h>

#include <cruxos_constants.h>
#include <SystemInfo.h>
#include <MemoryManagement.h>

SystemInfo info;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);
}

void counter() {
  int32_t result = 0;
  for(int16_t i = 0; i < 10; i++){
    result = result * i;
  }

  Serial.println("Result Value: " + String(result));
}

void loop() {
  //This is the loopable code
  delay(1000);
  info.serial_print();

}


//Definitions

