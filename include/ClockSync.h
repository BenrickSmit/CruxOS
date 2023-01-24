/**
 * \author Benrick Smit
 * \date Updated 2023/01/24
 * \brief The ClockSync class ensures that the RTC clock is updated and checks the current time it has with the wifi time
 *          after a set amount of time for CruxOS.
 * 
*/

#ifndef CLOCKSYNC_H
#define CLOCKSYNC_H


#include <ctime>
#include <sstream>

#include <Arduino.h>
#include <SPI.h>
#include <RTClib.h>

#include <MemoryManagement.h>
#include <WifiModule.h>
#include <CruxOSLog.h>
#include <cruxos_constants.h>


class ClockSync{
public:
    /// @brief This function returns the static instance of the singleton class ClockSync
    ///        to ensure the variables stay until the end of the program's life.
    /// @return an instance of this class
    static ClockSync* get_instance();
    /// @brief This function deletes the instance of the singleton class ClockSync
    static void delete_instance();
    /// @brief This function will return a value that is the current class has stored
    /// @return This is a string that will be in the format HH:MM
    static std::string get_rtc_time();
    static std::string get_full_rtc_time();
    /// @brief This function will return an string representing the current hours the class has stored
    /// @return This is the hours returned as an string.
    static std::string get_hours();
    /// @brief This function will return an string representing the current minutes the class has stored
    /// @return This is the minutes returned as an string
    static std::string get_minutes();
    static std::string get_seconds();
    static std::string get_year(bool abbreviation_flag = true);
    static std::string get_month();
    static std::string get_month_string(bool abbreviation_flag = true);
    static std::string get_day();
    static std::string get_day_of_week();
    static std::string get_day_of_week_string(bool abbreviation_flag = true);
    
    
    static int get_int_year();
    static int get_int_month();
    static int get_int_day();
    static int get_int_day_of_week();
    static int get_int_hours();
    static int get_int_minutes();
    static int get_int_seconds();

    /// @brief This function sets the new class hours value
    /// @param new_hours This is the new hours value
    static void set_hours(int new_hours);
    
    /// @brief This function sets the new class minutes value
    /// @param new_minutes This is the new minutes value
    static void set_minutes(int new_minutes);
    static void set_seconds(int new_seconds);
    static void set_year(int new_year);
    static void set_month(int new_month);
    static void set_day(int new_day);

    /// @brief This function will return a string that has the current milliseconds since boot stored in it
    /// @return This is the milliseconds since boot returned as a string
    static std::string get_millis();

    /// @brief This function will use the WifiModule function Time variable and if the memory variable is not
    ///         empty will set it to the time found in the variable.
    static void get_wifi_time();

    /// @brief This function directly sets the RTC clock and the individual member variables
    /// @param year This is the year variable to set
    /// @param month This is the month variable to set
    /// @param day This is the day variable to set
    /// @param hour This is the hour variable to set
    /// @param minute This is the minute variable to set
    /// @param second This is the second variable to set
    static void set_rtc_clock(int year, int month, int day, int hour, int minute, int second);
    /// @brief This function will set the RTC Clock to 1933 November 23 at 04:30:00;
    static void reset_time();


    static time_t to_time_t(const DateTime& input_datetime);

    /// @brief This function creates a DateTime object to use for later
    /// @param year This is the year variable to set
    /// @param month This is the month variable to set
    /// @param day This is the day variable to set
    /// @param hour This is the hour variable to set
    /// @param minute This is the minute variable to set
    /// @param second This is the second variable to set
    static DateTime create_datetime(int year, int month, int day, int hour, int minute, int second);

protected:
    /// @brief This function takes in the month value and returns either an abbreviation or
    ///         the full month name based on a flag
    /// @param month This function represents the month, it's between 1 and 12
    /// @param abbreviation This flag represents whether the month returned should be an abbreviation
    /// @return a std::string with either an abbreviation or a full month name
    static std::string convert_month_to_string(int month, bool abbreviation = true);
    /// @brief This function takes in the day of the week value and returns either an
    ///         abbreviation or the full name based on a flag
    /// @param day_of_week This argument represents the day of the week, it's between 1 and 7
    /// @param abbreviation This flag represents whether the day of the week is returned as an abbreviation
    /// @return a std::string with either an abbreviation or a full day name.
    static std::string convert_day_of_week_to_string(int day_of_week, bool abbreviation);

private:
    ClockSync();
    ~ClockSync();
    ClockSync(ClockSync const&) = delete;
    void operator=(ClockSync const&) = delete;

    unsigned long m_prev_millis;  // Stores the last update time since boot
    unsigned long m_new_millis;   // Stores the current update time since boot

    time_t m_now;
    RTC_DS3231 m_rtc;
    WifiModule m_wifi;
    static ClockSync *m_instance;
};

#endif
