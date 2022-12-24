#ifndef UNIT_TEST

#include <Arduino.h>
#include <Wire.h>

#include <cruxos_constants.h>
#include <SystemInfo.h>
#include <MemoryManagement.h>

SystemInfo info;

void setup() {
  // put your setup code here, to run once:
  // Setup BAUD rate.
  Serial.begin(BAUD_RATE);

  // Memory Manager Instantiation.
  MemoryManagement *mm = mm->get_instance();
  MemoryManagement::create_variable(CN_TIME_VAR, "24:00");
  MemoryManagement::create_variable(CN_WEATHER_VAR, "Cloudy");
  MemoryManagement::create_variable(CN_WEATHER_TEMP_CURR_VAR, "77");
  MemoryManagement::create_variable(CN_EST_LOCATION_VAR, "New York");
  MemoryManagement::create_variable(CN_BLUETOOTH_CONNECTION_VAR, "Not-Connected");
  MemoryManagement::create_variable(CN_SSID_NAME_VAR, "Unknown");
  MemoryManagement::create_variable(CN_SSID_PASSWORD_VAR, "Unknown");
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

  Serial.print("Var Count: ");
  Serial.println(MemoryManagement::count_variables());
  MemoryManagement::modify_variable("Time", "14:00");
  Serial.print("Time: ");
  Serial.println(MemoryManagement::get_value("Time").c_str());
  MemoryManagement::modify_variable("Time", "44:00");
  Serial.print("Time: ");
  Serial.println(MemoryManagement::get_value("Time").c_str());

}


#endif

