#ifndef UNIT_TEST

#include <Arduino.h>
#include <Wire.h>
#include "esp_task_wdt.h"


#include <cruxos_constants.h>
#include <SystemInfo.h>
#include <MemoryManagement.h>
#include <PeripheralDevice.h>
#include <PowerManagement.h>
#include <ClockSync.h>
#include <BatteryInfo.h>
#include <WifiModule.h>

#include <QMC5883LCompass.h>

#include <RTClib.h>
RTC_DS3231 rtc;

SystemInfo info;
WifiModule wifi;

QMC5883LCompass compass;

void setup() {
  // put your setup code here, to run once:
  // Setup BAUD rate.
  Serial.begin(BAUD_RATE);

  // Memory Manager Instantiation.
  MemoryManagement *mm = mm->get_instance();
  ClockSync *cs = cs->get_instance();
  BatteryInfo *bi = bi->get_instance();
  PeripheralDevice::get_instance()->init_compass();
  PeripheralDevice::get_instance()->init_accelerometer();
  PowerManagement* pm = pm->get_instance();
  //PowerManagement::power_optimisation();
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

  compass.init();
  compass.setSmoothing(10, true);
  //compass.read();

  rtc.begin();
  //rtc.adjust(DateTime(2020, 1, 1, 15, 30, 0));
  //wifi.begin("SSID", "PASSWORD");
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
  //info.serial_print();

  Serial.print("\nTime: ");
  Serial.println(ClockSync::get_rtc_time().c_str());
  ClockSync::time_update_loop();

  /*
  BatteryInfo *bi = bi->get_instance();
  Serial.print("%: ");
  Serial.println(std::to_string(BatteryInfo::get_battery_percentage()).c_str());
  Serial.print("Cap: ");
  Serial.println(std::to_string(BatteryInfo::get_battery_capacity()).c_str());
  Serial.print("V: ");
  Serial.println(std::to_string(BatteryInfo::get_battery_voltage()).c_str());
  */
  // This function has to loop
  //BatteryInfo::battery_loop();

  //PeripheralDevice::get_device_orientation();
  //PeripheralDevice::get_compass();
  
  //printf("Compass: [%d,%d,%d], {%d}\n", compass.getX(), compass.getY(), compass.getZ(), compass.getAzimuth());
  //compass.read();
  //printf("Compass Data:\n%s\n", PeripheralDevice::get_instance()->compass_to_string().c_str());
  DateTime now = DateTime(rtc.now());
  printf("RTC: %d:%d:%d\n", now.hour(),now.minute(),now.second());
  //printf("BMA400: %s\n", PeripheralDevice::get_instance()->accelerometer_to_string().c_str());
  PeripheralDevice::get_instance()->get_orientation();
  wifi.get_time();
}


#endif

