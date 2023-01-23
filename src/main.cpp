#ifndef UNIT_TEST

#include <Arduino.h>
#include <Wire.h>
#include <TFT_eSPI.h>
#include "esp_task_wdt.h"


#include <cruxos_constants.h>
#include <SystemInfo.h>
#include <MemoryManagement.h>
#include <PeripheralDevice.h>
#include <PowerManagement.h>
#include <DisplayManager.h>
#include <ClockSync.h>
#include <BatteryInfo.h>
#include <WifiModule.h>
#include <SyncData.h>
#include <WatchInterface.h>
#include <CruxOSLog.h>

#include <QMC5883LCompass.h>

#include <RTClib.h>
//RTC_DS3231 rtc;

SystemInfo info;

QMC5883LCompass compass;

TFT_eSPI tft; 
TFT_eSprite sprite = TFT_eSprite(&tft);
WatchInterface watch(&tft, &sprite);

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
  //DisplayManager *dm = dm->get_instance();
  //dm->begin();
  //dm->update_display("24:00");

  

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
  MemoryManagement::create_variable(CN_WIFI_TIME_VAR, "");  // Set Wifi Time to empty

  compass.init();
  compass.setSmoothing(10, true);
  //compass.read();


  ClockSync::reset_time();
  ClockSync::set_rtc_clock(2022, 7, 24, 9, 30, 55);
  watch.begin();
}


void loop() {
    //This is the loopable code
    Serial.flush();
    delay(1000);

    //ClockSync::time_update_loop();

    std::string time_str = "RTC: "+ClockSync::get_day_of_week_string(true)+" "+ClockSync::get_year()+"/"+ClockSync::get_month()+"/"+ClockSync::get_day()+" - "+ ClockSync::get_hours() + ":" + ClockSync::get_minutes() + ":" + ClockSync::get_seconds();
    CruxOSLog::Logging(__FUNCTION__, time_str.c_str());
    CruxOSLog::Logging(__FUNCTION__, ClockSync::get_full_rtc_time().c_str());
    PeripheralDevice::get_instance()->get_orientation();
    int hour = ClockSync::get_int_hours();
    int minute = ClockSync::get_int_minutes();
    int seconds = ClockSync::get_int_seconds();
    watch.draw(ClockSync::get_rtc_time());
    //SyncData::get_instance()->sync();
} 


#endif

