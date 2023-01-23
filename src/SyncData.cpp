#include "SyncData.h"


SyncData* SyncData::m_instance = nullptr;

// Private constructor to enforce singleton design
SyncData::SyncData() {
    // Inits all the necessary variables
    ClockSync *cs = cs->get_instance();
    m_update_battery = false;
    m_timer = 60;// * 1000;                // WIFI_CONN_COUNTER;

}

// Get the instance of the SyncData singleton
SyncData* SyncData::get_instance() {
    if (!m_instance) {
    m_instance = new SyncData();
    }
    return m_instance;
}

void SyncData::sync(){
    // Can only either use WiFi or update battery value, so use them exclusively
    if (get_current_millis() >= get_timer_millis()){
        // Based on Internet/ Bluetooth connectivity find the location and store it
        // Use the stored location to set up timezone
        // Use the stored location to get weather data

        // Get Wifi Information
        update_time();

        // Reset the timer values
        set_new_timer_millis(std::stol(ClockSync::get_millis().c_str()));
    }else{
        // Get The Battery Information
    }


    // Update The Time
    //ClockSync::time_update_loop();

    // Update The Pedometer

    // Update The Display

    // Update The Compass

}

void SyncData::update_time(){
    // This function should update the time in the ClockSync class based on whether it
    // received a new time that is different from the one stored in ClockSync.

    ClockSync *cs = cs->get_instance();
    SyncData *sd = sd->get_instance();

    // Get the time from the wifi server and then call the clock sync function which
    // will update the RTC clock accordingly
    std::string str_SSID = MemoryManagement::get_value(CN_SSID_NAME_VAR);
    std::string str_PASS = MemoryManagement::get_value(CN_SSID_PASSWORD_VAR);
    sd->m_wifi.begin(str_SSID.c_str(), str_PASS.c_str());
    sd->m_wifi.get_time();
    cs->get_wifi_time();
}

void SyncData::update_pedometer(){
}

void SyncData::update_memory(){
}

void SyncData::update_accelerometer(){
}

void SyncData::update_weather(){
}

void SyncData::set_new_timer_millis(long input_milliseconds){
    // This function will take an input of a long value for the current milliseconds
    // and then add the required time stored in the class to it.
    SyncData *sd = sd->get_instance();
    sd->m_timer_millis += sd->m_timer;
}

long SyncData::get_current_millis(){
    return std::stol(ClockSync::get_millis().c_str());
}

long SyncData::get_timer_millis(){
    SyncData *sd = sd->get_instance();
    return sd->m_timer_millis;
}