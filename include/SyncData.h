/**
 * \author Benrick Smit
 * \date Updated 2023/01/10
 * \brief The Sync Data Class takes care of timed wifi requests for specific data, such as time and possibly other data
 * 
*/


#ifndef SYNC_DATA_H
#define SYNC_DATA_H

#include <Arduino.h>
#include <esp_wifi.h>

#include <thread>

#include <ClockSync.h>
#include <MemoryManagement.h>
#include <WifiModule.h>
#include <BatteryInfo.h>
#include <cruxos_constants.h>


class SyncData {
public:
    // Get the instance of the SyncData singleton
    static SyncData* get_instance();

    void sync();
    void setup();

protected:

    void update_time();
    void update_pedometer();
    void update_memory();
    void update_accelerometer();
    void update_weather();

    void set_new_timer_millis(long input_time);
    long get_current_millis();
    long get_timer_millis();

private:
    SyncData();
    SyncData(const SyncData&) = delete;
    SyncData& operator=(const SyncData&) = delete;

    WifiModule m_wifi;

    bool m_update_battery;
    long m_timer;
    long m_timer_millis;

    static SyncData* m_instance;

    // Buttons
    int m_button1_state = HIGH;
    int m_button2_state = HIGH;
    int m_button3_state = HIGH;

    int m_button1_curr_state = LOW;
    int m_button2_curr_state = LOW;
    int m_button3_curr_state = LOW;
};

#endif // SYNC_DATA_H