#include "PowerState.h"

PowerState* PowerState::m_state = nullptr;

PowerState* PowerState::get_instance(){
    if (!m_state){
        m_state = new PowerState;
    }
    return nullptr;
}

void PowerState::delete_instance(){
    delete m_state;
    m_state = nullptr;
}

void PowerState::set_power_low(){
// This function will do nothing if it doesn't run on either an ARDUINO or ESP32 board
// Determine if it's either an ESP32 or ARDUINO board and set the power to
#ifdef ESP_PLATFORM
    // What to do if it is an ESP32 module
    // Wakeup the device from a light sleep after the POWER_TIMER_LOW reaches zero
    esp_sleep_enable_timer_wakeup(POWER_TIMER_LOW);
    esp_light_sleep_start();

#elif defined(ARDUINO)
    // What to do if it is an ARDUINO module
#endif
}

void PowerState::set_power_hibernate(){
    // This function will do nothing if it doesn't run on either an ARDUINO or ESP32 board
    // Determine if it's either an ESP32 or ARDUINO board and set the power to 
    #ifdef ESP_PLATFORM
        // What to do if it is an ESP32 module
        // Wakeup the device from hibernation after the POWER_TIMER_HIBERNATE reaches 0
        esp_sleep_enable_timer_wakeup(ESP_SLEEP_WAKEUP_TIMER);
        esp_deep_sleep(POWER_TIMER_HIBERNATE);

    #elif defined(ARDUINO)
        // What to do if it is an ARDUINO module
    #endif 
}

void PowerState::set_power_normal(){
    // This function will do nothing if it doesn't run on either an ARDUINO or ESP32 board
    // Determine if it's either an ESP32 or ARDUINO board and set the power to 
    #ifdef ESP_PLATFORM
        // What to do if it is an ESP32 module
        // Wake up the device depending on the type of sleep it was in
        if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER) {
            // exit light sleep mode
            //esp_light_sleep_stop();
        } else {
            // exit deep sleep mode
            esp_deep_sleep_disable_rom_logging();
        }
        Serial.begin(BAUD_RATE);
        Serial.print("PowerState:: ");
        Serial.print("<Reason> ");
        
        esp_sleep_wakeup_cause_t wakeup_reason;

        wakeup_reason = esp_sleep_get_wakeup_cause();

        switch(wakeup_reason){
            case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
            case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
            case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
            case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
            case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
            default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
        }

    #elif defined(ARDUINO)
        // What to do if it is an ARDUINO module
    #endif 
}



PowerState::PowerState(){
    // Do Nothing
}

PowerState::~PowerState(){
    // Do Nothing
}