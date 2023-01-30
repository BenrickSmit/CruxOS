#include "SyncData.h"


SyncData* SyncData::m_instance = nullptr;

// Private constructor to enforce singleton design
SyncData::SyncData() {
    // Inits all the necessary variables
    ClockSync *cs = cs->get_instance();
    m_update_battery = false;
    m_timer = 6 * 1000;                // WIFI_CONN_COUNTER;
    //BatteryInfo *bi = bi->get_instance();
    //bi->battery_loop();

    // set the timer
    m_timer_millis = (2* m_timer);
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
        // The wifi module and the battery cannot be read at the same time.
        auto error = esp_wifi_start();

        // Use the stored location to get weather data

        

        // Get Wifi Information
        CruxOSLog::Logging(__FUNCTION__, ">>>Executed WiFi functions");
        update_time();

        // Stop WifiModule temporarily
        error = esp_wifi_stop();

        // Reset the timer values
        set_new_timer_millis(std::stol(ClockSync::get_millis().c_str()));
    }else{
        // Get The Battery Information
        BatteryInfo *bi = bi->get_instance();
        bi->battery_update();
        // Only modify the saved variable if it isn't 0
        if(bi->get_battery_percentage() > 0 && bi->get_battery_percentage() <= 100){
            MemoryManagement::modify_variable(CN_BATTERY_VAR, std::to_string(bi->get_battery_percentage()));
        }
        std::string output_str = "Exectuted Battery Functions: " + MemoryManagement::get_value(CN_BATTERY_VAR);
        CruxOSLog::Logging(__FUNCTION__, output_str);
    }
    std::string timer_str = "TIME ("+std::to_string(get_current_millis())+"): TIMER("+std::to_string(get_timer_millis())+")";
    CruxOSLog::Logging(__FUNCTION__, timer_str.c_str());

    // Update The Time
    //ClockSync::time_update_loop();

    // Update The Pedometer
    // If It's Midnight, then reset the pedometer
    if(ClockSync::get_int_hours() < 1 && ClockSync::get_int_minutes() <= 1){
        PeripheralDevice *pd = pd->get_instance();
        pd->reset_peripherals();
    }

    // Update The Display

    // Update The Compass

}

void SyncData::setup(){
    BatteryInfo *bi = bi->get_instance();
    bi->battery_loop();
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
    sd->m_wifi.get_location_data();
    sd->m_wifi.get_time();
    std::string output = MemoryManagement::get_value(CN_WIFI_TIME_VAR);
    CruxOSLog::Logging(__FUNCTION__, output.c_str());
    cs->get_wifi_time();
    sd->m_wifi.stop();
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
    sd->m_timer_millis += sd->m_timer*12*100;
}

long SyncData::get_current_millis(){
    return std::stol(ClockSync::get_millis().c_str());
}

long SyncData::get_timer_millis(){
    SyncData *sd = sd->get_instance();
    return sd->m_timer_millis;
}