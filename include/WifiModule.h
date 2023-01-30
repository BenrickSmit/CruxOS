#ifndef WIFIMODULE_H
#define WIFIMODULE_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <NTPClient.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

#include <thread>
#include <vector>
#include <string>
#include <map>

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
    void get_location_data();
    void get_weather();
    
protected:
    /// @brief This function will use the NTPClient and WiFiClient libraries to get the EpochTime for this location.
    void read_time_server();
    /// @brief This function will take an input string as a json, and convert it to a map for browsing.
    /// @param input_string The json formatted string
    /// @return a map with the necessary values separated and searchable
    std::map<std::string, std::string> get_json_map(const std::string &input_string);
    int convert_utc_to_int(const std::string& input_offset);

private:
    std::thread m_time_thread;
    WiFiClient m_client;
    WiFiClientSecure m_client_secure;
    std::vector<std::string> m_time_servers;
    long m_wifi_counter;
};

#endif