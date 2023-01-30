#ifndef WIFIMODULE_H
#define WIFIMODULE_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
//#include <WiFiClientSecure.h>
#include <NTPClient.h>
#include <HTTPClient.h>

#include <thread>
#include <vector>
#include <string>

#include <cruxos_constants.h>
#include <CruxOSLog.h>
#include <MemoryManagement.h>

class WifiModule{
public:
    WifiModule();
    ~WifiModule();

    void begin(const char* ssid, const char* password);
    void stop();
    void get_time();
    void get_city();
    void get_weather();
    
protected:
    void read_time_server();
    int get_city_utc_offset();

private:
    std::thread m_time_thread;
    WiFiClient m_client;
    //WiFiClientSecure m_client_secure;
    std::vector<std::string> m_time_servers;
    long m_wifi_counter;
};

#endif