#ifndef WIFIMODULE_H
#define WIFIMODULE_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

#include <thread>
#include <vector>
#include <string>

#include <cruxos_constants.h>

class WifiModule{
public:
    WifiModule();
    ~WifiModule();

    void begin(const char* ssid, const char* password);

    void get_time();
    
protected:
    void read_time_server();

private:
    std::thread m_time_thread;
    WiFiClient m_client;
    std::vector<std::string> m_time_servers;
};

#endif