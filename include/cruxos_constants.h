/**
 * \author Benrick Smit
 * \date Updated 21/12/2022
 * \brief The cruxos_constants file contains all the constants used in the CruxOS system
 * 
*/

#ifndef CRUXOS_CONSTANTS_H
#define CRUXOS_CONSTANTS_H

#include <Arduino.h>

// Basic Data Properties
const u_int32_t BAUD_RATE = 9600;//9600;//9600;921600;

// Basic Board Properties
const u_int8_t BUILTIN_LED_PIN = 17;
const u_int8_t BUILTIN_BTN2_PIN = 18;
const u_int8_t BUILTIN_BTN3_PIN = 16;

// Basic Properties
const u_int16_t TIME_UPDATE_COUNTER = 10;                // 10 seconds
const u_int16_t WIFI_CONN_COUNTER = 30000;               // 30 minutes

// Variables to Create at Runtime
const std::string CN_TIME_VAR = "CURRENT_TIME";
const std::string CN_WEATHER_ICON_VAR = "CURRENT_WEATHER_ICON";
const std::string CN_WEATHER_VAR = "CURRENT_WEATHER_CONDITION";
const std::string CN_WEATHER_TEMP_MAX_VAR = "MAX_WEATHER_TEMP";
const std::string CN_WEATHER_TEMP_MIN_VAR = "CURRENT_WEATHER_TEMP";
const std::string CN_WEATHER_TEMP_CURR_VAR = "CURRENT_WEATHER_TEMP";
const std::string CN_SSID_CONNECTION_STATUS_VAR = "SSID_CONNECTION_STATUS";
const std::string CN_SSID_PASSWORD_VAR = "SSID_PASSWORD_SAVED";
const std::string CN_SSID_NAME_VAR = "SSID_NAME_SAVED";
const std::string CN_TOTAL_STEPS_VAR = "PEDOMETER_STEPS_COUNT";
const std::string CN_EST_LOCATION_VAR = "ESTIMATED_LOCATION";
const std::string CN_BLUETOOTH_DATA_VAR = "BLUETOOTH_DATA_RECEIVED";
const std::string CN_BLUETOOTH_CONNECTION_VAR = "BT_STATUS";
const std::string CN_WIFI_USE_TIMER = "WIFI_USE_TIMER";
const std::string CN_BLUETOOTH_USE_TIMER = "BT_USE_TIMER";
const std::string CN_ = "";

#endif //CRUXOS_CONSTANTS_H