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
#include <WatchInterfaceManager.h>

#include <QMC5883LCompass.h>

#include <RTClib.h>
//RTC_DS3231 rtc;

SystemInfo info;

QMC5883LCompass compass;

TFT_eSPI tft; 
TFT_eSprite sprite = TFT_eSprite(&tft);
//WatchInterface watch(&tft, &sprite);
WatchInterfaceManager face_manager(&tft, &sprite);

// Variables to keep track of button state
bool button1Pressed = false;
bool button2Pressed = false;
bool button3Pressed = false;

// Interrupt service routines
void IRAM_ATTR button1Interrupt() {
  button1Pressed = true;
}

void IRAM_ATTR button2Interrupt() {
  button2Pressed = true;
}

void IRAM_ATTR button3Interrupt() {
  button3Pressed = true;
}

void  display_next_screen(){
  face_manager.draw_next_screen();
  CruxOSLog::Logging(__FUNCTION__, "DISPLAY NEXT SCREEN");
}

void  display_previous_screen(){
  face_manager.draw_prev_screen();
  CruxOSLog::Logging(__FUNCTION__, "DISPLAY PREVIOUS SCREEN");
}

void  display_on_off_screen(){
  CruxOSLog::Logging(__FUNCTION__, "DISPLAY ON/OFF SCREEN");
}


void particle_animation_thread(int block_size, int x_start) {
  //while (true) {
    for (int i = 0; i < 100; i++) {
      int x = random(x_start, x_start + block_size);
      int y = random(0, block_size);
      sprite.fillCircle(x, y, 2, TFT_WHITE);
      delay(100);
      sprite.fillCircle(x, y, 2, TFT_BLACK);
    }
  //}
}

void animation_thread()
{
    while (true)
    {
        // Clear the sprite
        sprite.fillSprite(TFT_BLACK);

        // Draw the particles
        // ...
        particle_animation_thread(120, 240);

        // Update the sprite
        sprite.pushSprite(0, 0);

        // Wait for a specified time interval before redrawing the particles
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        CruxOSLog::Logging(__FUNCTION__, "Animation excuting");
    }
}



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

  // For Battery
  pinMode(BUILTIN_BATTERY_PIN, OUTPUT);
  

  //PowerManagement::power_optimisation();
  MemoryManagement::create_variable(CN_BATTERY_VAR, "25");
  MemoryManagement::create_variable(CN_TIME_VAR, "24:00");
  MemoryManagement::create_variable(CN_WEATHER_VAR, "broken clouds");
  MemoryManagement::create_variable(CN_WEATHER_TEMP_CURR_VAR, "77");
  MemoryManagement::create_variable(CN_WEATHER_TEMP_MAX_VAR, "78");
  MemoryManagement::create_variable(CN_WEATHER_TEMP_MIN_VAR, "76");
  MemoryManagement::create_variable(CN_EST_LOCATION_VAR, "Tokyo");
  MemoryManagement::create_variable(CN_EST_LOCATION_UTC_OFFSET_VAR, "9");  // Set Wifi Time to empty
  MemoryManagement::create_variable(CN_BLUETOOTH_CONNECTION_VAR, "Not-Connected");
  MemoryManagement::create_variable(CN_SSID_NAME_VAR, "Unknown");
  MemoryManagement::create_variable(CN_SSID_PASSWORD_VAR, "Unknown");
  MemoryManagement::create_variable(CN_IP_ADDR, "Unknown");
  MemoryManagement::create_variable(CN_MILLIS_SINCE_START, ClockSync::get_millis()); // Should be nonvolatile later
  MemoryManagement::create_variable(CN_OS_NAME, "Crux:CameliaOS"); // should be nonvolatile later
  MemoryManagement::create_variable(CN_OS_VER, "1.0.1"); // should be nonvolatile later
  MemoryManagement::create_variable(CN_WIFI_TIME_VAR, "");  // Set Wifi Time to empty

  // Location Informa
  //MemoryManagement::create_variable(CN_, "");

  compass.init();
  compass.setSmoothing(10, true);
  //compass.read();



  ClockSync::reset_time();
  ClockSync::set_rtc_clock(2022, 7, 24, 9, 30, 55);
  //watch.begin();
  face_manager.begin();
  //face_manager.init();

  //pinMode(BUILTIN_BTN2_PIN, INPUT_PULLUP);
  //SyncData::button_setup();

  pinMode(BUILTIN_BTN1_PIN, INPUT_PULLUP);
  attachInterrupt(BUILTIN_BTN1_PIN, &button1Interrupt, FALLING);

  pinMode(BUILTIN_BTN2_PIN, INPUT_PULLUP);
  attachInterrupt(BUILTIN_BTN2_PIN, &button2Interrupt, CHANGE);

  pinMode(BUILTIN_BTN3_PIN, INPUT_PULLUP);
  attachInterrupt(BUILTIN_BTN3_PIN, &button3Interrupt, CHANGE);

  //std::thread animation(animation_thread);
  //animation.detach();
}

//int lastState = HIGH; // the previous state from the input pin
//int currentState;     // the current reading from the input pin


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
    //watch.draw(ClockSync::get_rtc_time());
    
    SyncData::get_instance()->sync();

    //currentState = digitalRead(BUILTIN_BTN2_PIN);
    //digitalRead(BUILTIN_BTN1_PIN);
    //digitalRead(BUILTIN_BTN2_PIN);
    //digitalRead(BUILTIN_BTN3_PIN);

    //if(lastState == LOW && currentState == HIGH)
    //  Serial.println("The state changed from LOW to HIGH");

    // save the last state
    //lastState = currentState;
    //SyncData::button_update();

  if (button1Pressed) {
    // Execute code for button 1 press
    display_on_off_screen();
    button1Pressed = false;
  }
  
  if (button2Pressed) {
    // Execute code for button 2 press
    display_next_screen();
    button2Pressed = false;
  }
  
  if (button3Pressed) {
    // Execute code for button 3 press
    display_previous_screen();
    button3Pressed = false;
  }

  face_manager.init();
} 


#endif

