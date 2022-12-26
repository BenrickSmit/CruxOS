#include "ClockSync.h"

ClockSync *ClockSync::m_instance = nullptr;

ClockSync *ClockSync::get_instance(){
    if (!m_instance){
        m_instance = new ClockSync();
    }

    return m_instance;
}

void ClockSync::update_rtc(int hours, int mins, int secs){
    // This function simply sets & updates the hours and minutes as necessary - later will set dates as well, but requires different logic
    // Make sure to calculate the seconds, minutes, and hours as necessary
    ClockSync *cs = cs->get_instance();
    std::string get_value = get_seconds();
    auto old_seconds = MemoryManagement::to_int(get_value);
    get_value = get_minutes();
    auto old_minutes = MemoryManagement::to_int(get_value);
    get_value = get_hours();
    auto old_hours = MemoryManagement::to_int(get_value);


    cs->m_now = time(nullptr);
    // Convert the time_t value to a tm structure
    tm* time = localtime(&cs->m_now);

    // Add an arbitrary number of seconds, minutes, and hours to the current time
    time->tm_sec += secs;
    time->tm_min += mins;
    time->tm_hour += hours;

    // Convert the tm structure back to a time_t value
    cs->m_now = mktime(time);

    set_hours(time->tm_hour);
    set_minutes(time->tm_min);
    set_seconds(time->tm_sec);
}

void ClockSync::update_rtc(int millis){
    // This function will only convert the milliseconds to hours and minutes
    // Convert the milliseconds to a time structure
    time_t seconds = millis/1000.0;
    tm* time_calculator = localtime(&seconds);

    // Set the hours and minutes
    update_rtc(time_calculator->tm_hour, time_calculator->tm_min, time_calculator->tm_sec);
}

std::string ClockSync::get_rtc_time(){
    return get_hours()+":"+get_minutes()+":"+get_seconds();
}

void ClockSync::time_update_loop(){
    // This function is designed to be called continually
    // It will take the current milliseconds since boot, and the old stored one,
    // and calculate the difference to find the hours and minutes needed by which to update the values
    
    MemoryManagement *mm = mm->get_instance();
    ClockSync *cs = cs->get_instance();
    std::string value_millis = MemoryManagement::get_value(CN_MILLIS_SINCE_START);
    std::string string_millis = ClockSync::get_millis();
    unsigned long old_millis = MemoryManagement::to_long(value_millis);
    unsigned long new_millis = MemoryManagement::to_long(string_millis);
    unsigned long millis = new_millis - old_millis;
    update_rtc(millis);
    MemoryManagement::modify_variable(CN_MILLIS_SINCE_START, std::to_string(new_millis));   // Should be nonvolatile later

    
}

std::string ClockSync::get_hours(){
    std::string to_return = "";
    ClockSync *cs = cs->get_instance();

    if(cs->m_hour < 10){
        to_return += "0";
    }
    to_return += std::to_string(cs->m_hour);

    return to_return;
}

std::string ClockSync::get_minutes(){
    std::string to_return = "";
    ClockSync *cs = cs->get_instance();

    if(cs->m_min < 10){
        to_return += "0";
    }
    to_return += std::to_string(cs->m_min);

    return to_return;
}

std::string ClockSync::get_seconds(){
    std::string to_return = "";
    ClockSync *cs = cs->get_instance();

    if(cs->m_sec < 10){
        to_return += "0";
    }
    to_return += std::to_string(cs->m_sec);

    return to_return;
}

void ClockSync::set_minutes(int new_minutes){
    ClockSync *cs = cs->get_instance();
    cs->m_min = new_minutes;
}

void ClockSync::set_seconds(int new_seconds){
    ClockSync *cs = cs->get_instance();
    cs->m_sec = new_seconds;
}

std::string ClockSync::get_millis()
{
    return std::to_string(millis());
}

void ClockSync::set_hours(int new_hours){
    ClockSync *cs = cs->get_instance();
    cs->m_hour = new_hours;
}

ClockSync::ClockSync(){
    // Do Nothing For Now
}

ClockSync::~ClockSync(){
    // Do Nothing, Possibly
}