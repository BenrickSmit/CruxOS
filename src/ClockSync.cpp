#include "ClockSync.h"

ClockSync *ClockSync::m_instance = nullptr;

ClockSync *ClockSync::get_instance(){
    if (!m_instance){
        m_instance = new ClockSync();
    }

    return m_instance;
}

void ClockSync::update_rtc(int hours, int mins){
    // This function simply sets the hours and minutes as necessary - later will set dates as well, but requires different logic
    set_hours(time_calculator.Hour);
    set_minutes(time_calculator.Minute);
}

void ClockSync::update_rtc(int millis){
    // This function will only convert the milliseconds to hours and minutes
    // Convert the milliseconds to a time structure
    tmElements_t time_calculator;
    Time.millisToTime(millis, time_calculator);

    // Set the hours and minutes
    update_rtc(time_calculator.Hour, time_calculator.Minute)
}

std::string ClockSync::get_rtc_time(){
    return std::to_string(get_hours())+""+std::to_string(get_minutes());
}

void ClockSync::time_update_loop(){
    // This function is designed to be called continually
    // It will take the current milliseconds since boot, and the old stored one,
    // and calculate the difference to find the hours and minutes needed by which to update the values
    
    MemoryManagement *mm = mm->get_instance();
    unsigned long old_millis = MemoryManagement::to_long(MemoryManagement::get_value(CN_MILLIS_SINCE_START));
    unsigned long new_millis = millis();
    unsigned long millis = new_millis - old_millis;
    update_rtc(millis);
    MemoryManagement::modify_variable(CN_MILLIS_SINCE_START, std::to_string(new_millis));   // Should be nonvolatile later
}

std::string ClockSync::get_hours(){
    std::string to_return = "";

    if(m_hours < 10){
        to_return += "0";
    }
    to_return += std::to_string(m_hours);

    return to_return;
}

std::string ClockSync::get_minutes(){
    std::string to_return = "";

    if(m_minutes < 10){
        to_return += "0";
    }
    to_return += std::to_string(m_minutes);

    return to_return;
}

void ClockSync::set_minutes(int new_minutes){
    m_minutes = new_minute;
}

std::string ClockSync::get_millis()
{
    return std::to_string(millis());
}

void ClockSync::set_hours(int new_hours){
    m_hours = new_hour;
}

ClockSync::ClockSync(){
    // Do Nothing For Now
}

ClockSync::~ClockSync(){
    // Do Nothing, Possibly
}