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
const u_int8_t BUILTIN_BTN1_PIN = 0;
const u_int8_t BUILTIN_BTN2_PIN = 10;
const u_int8_t BUILTIN_BTN3_PIN = 13;
const u_int8_t BUILTIN_BATTERY_PIN = 25;
const u_int8_t BUILTIN_TFT_CS = 5;
const u_int8_t BUILTIN_TFT_DC = 12;
const u_int8_t BUILTIN_TFT_RST = 33;
const u_int8_t BUILTIN_TFT_SCK = 18;
const u_int8_t BUILTIN_TFT_MOSI = 23;
const u_int8_t BUILTIN_TFT_MISO = -1; // no data coming back
const u_int8_t BUILTIN_TFT_LED = 9;
const u_int8_t BUILTIN_GPS_RX = 14;
const u_int8_t BUILTIN_GPS_TX = 27;
const u_int8_t BUILTIN_GPS_FON = 26;
const u_int8_t BUILTIN_GPS_3D_FIX = 36;;
const u_int8_t BUILTIN_GPS_GEO_FENCE = 39;
const u_int8_t BUILTIN_RX1 = 27;
const u_int8_t BUILTIN_TX1 = 14;
const u_int8_t BUILTIN_ACCEL_INT1 = 34;
const u_int8_t BUILTIN_ACCEL_INT2 = 35;
const u_int8_t BUILTIN_ACCEL_INPUT = 0x01;
const u_int8_t BUILTIN_ACCEL_FAILLING = 0x02;
const u_int8_t BUILTIN_ACCEL_BME280_PIN = 118;

// Power Properties
const u_int32_t POWER_TIMER_NORMAL = 10 * 1000;                    // 10 seconds;
const u_int32_t POWER_TIMER_HIBERNATE = 5 * 1000000;                 // 5 seconds;
const u_int32_t POWER_TIMER_LOW = 5 * 1000;                        // 5 seconds;

// Peripheral Properties
enum DEVICE_ORIENTATION {DEVICE_FACE_UP = 0, DEVICE_IN_MOTION, DEVICE_STATIONARY, DEVICE_TILTED, DEVICE_ERROR = -1};
enum DEVICE_POWERSTATE {DEVICE_POWER_NORMAL = 0, DEVICE_POWER_LOW, DEVICE_POWER_HIBERNATE};
const u_int16_t PERIPHERAL_ORIENTATION_TIMER = 1000;

// Basic Properties
const u_int16_t TIME_UPDATE_COUNTER = 10;                // 10 seconds
const u_int16_t WIFI_CONN_COUNTER = 30*1000;               // 30 minutes
const u_int16_t ARDUINO_DELAY = 1000;
const u_int8_t BATTERY_CHARGING = 2;
const u_int8_t BATTERY_DRAINING = 1;
const u_int8_t BATTERY_FULL = 0;
const u_int8_t BATTERY_NOT_SET = -1;
const u_int16_t BATTERY_UPDATE_TIMER = 10*1000;          // Check every 10 second
constexpr float BUILTIN_GRAVITY_ACCELERATION = 1.0;         // roughly 9.81 m/s^2;
constexpr float BUILTIN_EPSILON = 0.02;

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
const std::string CN_MILLIS_SINCE_START = "MS_SINCE_BOOT";
const std::string CN_OS_NAME = "OPERATING_SYSTEM_NAME";
const std::string CN_OS_VER = "OPERATING_SYSTEM_VER";
const std::string CN_IP_ADDR = "NW_IP_ADDR";
const std::string CN_BUILTIN_ACCEL_PIN = "ACCELEROMETER_PIN_NUMBER";
const std::string CN_ = "";

#endif //CRUXOS_CONSTANTS_H