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
#include <RtcDS3234.h>


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
    static void update_rtc(int hours, int mins);
    /// @brief This function will return a value that is the current class has stored
    /// @return This is a string that will be in the format HH:MM
    static std::string get_rtc_time();
    /// @brief This function should is callable and will update the time every TIME_UPDATE_COUNTER - a CruxOS constant 
    static void time_update_loop();
    /// @brief This function will return an integer representing the current hours the class has stored
    /// @return This is the hours returned as an integer.
    static int get_hours();
    /// @brief This function will return an integer representing the current minutes the class has stored
    /// @return This is the minutes returned as an integer
    static int get_minutes();

private:
    ClockSync();
    ~ClockSync();
    ClockSync(ClockSync const&) = delete;
    void operator=(ClockSync const&) = delete;

    int m_hour;
    int m_min;
    std::string m_time_string;
    //RtcDS3234 m_rtc;
};

#endif
