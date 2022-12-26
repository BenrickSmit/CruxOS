/**
 * \author Benrick Smit
 * \date Updated 25/12/2022
 * \brief The ClockSync class ensures that the RTC clock is updated and checks the current time it has with the wifi time
 *          after a set amount of time for CruxOS.
 * 
*/

#ifndef CLOCKSYNC_H
#define CLOCKSYNC_H

#include <Arduino.h>
#include <SPI.h>
#include <ctime>
#include <MemoryManagement.h>
#include <cruxos_constants.h>


class ClockSync
{
public:
    /// @brief This function returns the static instance of the singleton class ClockSync
    ///        to ensure the variables stay until the end of the program's life.
    /// @return an instance of this class
    static ClockSync* get_instance();
    /// @brief This function will update the stored values to the ones outlined in the variables
    /// @param hours This is the new hours value to use
    /// @param mins This is the new minutes value to use
    static void update_rtc(int hours, int minutes, int seconds);
    /// @brief This function converts millisecond values and converts it into hours and minutes respectively to update
    ///         the rtc.
    /// @param millis This is the difference in update time from the past stored value since boot and the current one
    static void update_rtc(int millis);
    /// @brief This function will return a value that is the current class has stored
    /// @return This is a string that will be in the format HH:MM
    static std::string get_rtc_time();
    /// @brief This function should is callable and will update the time every TIME_UPDATE_COUNTER - a CruxOS constant 
    static void time_update_loop();
    /// @brief This function will return an string representing the current hours the class has stored
    /// @return This is the hours returned as an string.
    static std::string get_hours();
    /// @brief This function will return an string representing the current minutes the class has stored
    /// @return This is the minutes returned as an string
    static std::string get_minutes();
    static std::string get_seconds();
    /// @brief This function sets the new class hours value
    /// @param new_hours This is the new hours value
    static void set_hours(int new_hours);
    /// @brief This function sets the new class minutes value
    /// @param new_minutes This is the new minutes value
    static void set_minutes(int new_minutes);
    static void set_seconds(int new_seconds);

    /// @brief This function will return a string that has the current milliseconds since boot stored in it
    /// @return This is the milliseconds since boot returned as a string
    static std::string get_millis();

protected:
    

private:
    ClockSync();
    ~ClockSync();
    ClockSync(ClockSync const&) = delete;
    void operator=(ClockSync const&) = delete;

    unsigned long m_prev_millis;  // Stores the last update time since boot
    unsigned long m_new_millis;   // Stores the current update time since boot

    int m_hour;
    int m_min;
    int m_sec;
    time_t m_now;
    static ClockSync *m_instance;
};

#endif
