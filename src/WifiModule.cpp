#include "WifiModule.h"

WifiModule::WifiModule() {
    // Initialise a time ervers list that will hold the 40 most common time servers
    m_time_servers = {
    "time-a.nist.gov",
    "time-b.nist.gov",
    "time-c.nist.gov",
    "time-d.nist.gov",
    "time-nw.nist.gov",
    "nist1.aol-ca.truetime.com",
    "nist1.columbiacountyga.gov",
    "nist1-chi.ustiming.org",
    "nist1-lnk.binary.net",
    "nist1-ny.ustiming.org",
    "nist1-sj.ustiming.org",
    "nist1-wa.ustiming.org",
    "time.nist.gov",
    "time-a.nist.gov",
    "time-b.nist.gov",
    "time-c.nist.gov",
    "pool.ntp.org",
    "north-america.pool.ntp.org",
    "europe.pool.ntp.org",
    "asia.pool.ntp.org",
    "oceania.pool.ntp.org",
    "africa.pool.ntp.org",
    "south-america.pool.ntp.org",
    "time1.google.com",
    "time2.google.com",
    "time3.google.com",
    "time4.google.com",
    "time.apple.com",
    "time.windows.com",
    "time.cloudflare.com",
    "time.certum.pl",
    "time.euro.apple.com", "time.nist.gov"};
    m_wifi_counter = 0;
}

WifiModule::~WifiModule(){
}

void WifiModule::begin(const char* ssid, const char* password){
    WiFi.begin(ssid, password);
    while ((WiFi.status() != WL_CONNECTED) && (m_wifi_counter <= WIFI_TIMER_COUNTER)) {
        delay(TIME_UPDATE_COUNTER);
        CruxOSLog::Logging(__FUNCTION__, "Waiting For Wifi Connection.");
        m_wifi_counter ++;
    }
    m_wifi_counter = 0;
}

void WifiModule::stop(){
    m_client.stop();
}

void WifiModule::get_time(){
    //m_time_thread = std::thread([&](){
        read_time_server();
        //xTaskCreatePinnedToCore(WifiModule::read_time_server, "read_time_task", 8192, NULL, 1, NULL, 1);
    //});
    //m_time_thread.detach();
}

void WifiModule::get_city(){
    // This function will get an estimated location for you based on the IP address
    if(WiFi.status() == WL_CONNECTED){
        // Don't do anything if there is no internet connectivity
        std::string new_city_string = "Mississippi";
        std::string new_utc_offset = "9";

        // Get the City
        std::string ip = m_client.localIP().toString().c_str();

        // Send GET request to the "ipapi" service
        // Make a GET request to ipapi
        HTTPClient http_client;
        std::string format_str = "json";
        std::string call_request = "https://ipapi.co/"+ip+"/"+format_str.c_str()+"/";
        call_request = "https://ipapi.co/";
        call_request += format_str.c_str();
        call_request += "/";
/*
        //call_request = "https://ipapi.co/city/";
        //call_request = "GET https://ipapi.co/utc_offset/";
        m_client_secure.setInsecure(); // this line is necessary to ignore SSL certificate errors

        if (!m_client_secure.connect("ipapi.co", 443)) {
            // handle error
            return;
        }

        // send the HTTPS request
        m_client_secure.print(String("GET ") + "/json/" + " HTTP/1.1\r\n" +
                        "Host: ipapi.co\r\n" +
                        "User-Agent: ESP32\r\n" +
                        "Connection: close\r\n\r\n");

        // wait for the response from the server
        while (!m_client_secure.available()) {
            delay(1);
        }

        // read the response from the server
        String response = m_client_secure.readString();
        CruxOSLog::Logging(__FUNCTION__, response.c_str());*/

        // Write to the memory address
        MemoryManagement::modify_variable(CN_EST_LOCATION_UTC_OFFSET_VAR, new_utc_offset);
        MemoryManagement::modify_variable(CN_EST_LOCATION_VAR, new_city_string);
        new_city_string = "Updated City Information: " + new_city_string;
        CruxOSLog::Logging(__FUNCTION__, new_city_string.c_str());
    }else {
        CruxOSLog::Logging(__FUNCTION__, "No Internet Connectivity - Using Default City", LOG_ERROR);
    }
}

void WifiModule::get_weather(){
    // This function will connect to OpenWeatherAPI and obtain the weatherforecast if possible for the location specified on the device.
}

void WifiModule::read_time_server(){
    // This function will try as many of the time servers as possible to obtain the current time
    WiFiUDP ntp_udp;
    NTPClient time_client(ntp_udp);
    time_client.begin();
    time_client.update();
    time_client.setTimeOffset(9*3600);
    time_t now = time_client.getEpochTime();
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);

    int day = timeinfo.tm_mday;
    int month = timeinfo.tm_mon + 1;
    int year = timeinfo.tm_year + 1900;
    int hour = timeinfo.tm_hour;
    int minute = timeinfo.tm_min;
    int second = timeinfo.tm_sec;

    std::string TIME_STR = std::to_string(year)+":"+std::to_string(month)+":"+std::to_string(day)+":"+
                            std::to_string(hour)+":"+std::to_string(minute)+":"+std::to_string(second);
    // Write the Time to the Time Variable as Necessary
    MemoryManagement::modify_variable(CN_WIFI_TIME_VAR,TIME_STR.c_str());
    CruxOSLog::Logging(__FUNCTION__, ctime(&now));
}

int WifiModule::get_city_utc_offset(){
    // This function will take in a city name, and then get the UTC offset and return it.
    int offset = 9;
    std::string city_name = "yokohama";

    


    return offset;
}
