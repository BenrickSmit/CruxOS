#ifndef UNIT_TEST

#include <Arduino.h>
#include <Wire.h>

#include <cruxos_constants.h>
#include <SystemInfo.h>
#include <MemoryManagement.h>
#include <ClockSync.h>
#include <BatteryInfo.h>

SystemInfo info;

void setup() {
  // put your setup code here, to run once:
  // Setup BAUD rate.
  Serial.begin(BAUD_RATE);

  // Memory Manager Instantiation.
  MemoryManagement *mm = mm->get_instance();
  ClockSync *cs = cs->get_instance();
  BatteryInfo *bi = bi->get_instance();
  MemoryManagement::create_variable(CN_TIME_VAR, "24:00");
  MemoryManagement::create_variable(CN_WEATHER_VAR, "Cloudy");
  MemoryManagement::create_variable(CN_WEATHER_TEMP_CURR_VAR, "77");
  MemoryManagement::create_variable(CN_EST_LOCATION_VAR, "New York");
  MemoryManagement::create_variable(CN_BLUETOOTH_CONNECTION_VAR, "Not-Connected");
  MemoryManagement::create_variable(CN_SSID_NAME_VAR, "Unknown");
  MemoryManagement::create_variable(CN_SSID_PASSWORD_VAR, "Unknown");
  MemoryManagement::create_variable(CN_IP_ADDR, "Unknown");
  MemoryManagement::create_variable(CN_MILLIS_SINCE_START, ClockSync::get_millis()); // Should be nonvolatile later
  MemoryManagement::create_variable(CN_OS_NAME, "CameliaOS"); // should be nonvolatile later
  MemoryManagement::create_variable(CN_OS_VER, "1.0.1"); // should be nonvolatile later

  // This function has to loop
  BatteryInfo::battery_loop();
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

  Serial.print("\nTime: ");
  Serial.println(ClockSync::get_rtc_time().c_str());
  ClockSync::time_update_loop();
  std::string battery = std::to_string(analogRead(BUILTIN_BAT_PIN)*3.3/4095.00);
  Serial.println(battery.c_str());


  BatteryInfo *bi = bi->get_instance();
  Serial.println(std::to_string(BatteryInfo::get_battery_percentage()).c_str());
}


#endif

