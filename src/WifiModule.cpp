#include "WifiModule.h"

WifiModule::WifiModule() {
    // Initialise a time ervers list that will hold the 40 most common time servers
    m_time_servers = {"time.nist.gov",
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
    "time.euro.apple.com"};
}

WifiModule::~WifiModule(){

}

void WifiModule::begin(const char* ssid, const char* password){
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(TIME_UPDATE_COUNTER);
        CruxOSLog::Logging(__FUNCTION__, "Waiting For Wifi Connection.");
    }
}

void WifiModule::get_time(){
    m_time_thread = std::thread([&](){
        read_time_server();
    });
    m_time_thread.detach();
}

void WifiModule::read_time_server(){
    // This function will try as many of the time servers as possible to obtain the current time
    for (const std::string& server : m_time_servers) {
    if (m_client.connect(server.c_str(), 13)) {
        // Connection successful
        CruxOSLog::Logging(__FUNCTION__, "Connection to "+server+": Successful");
        m_client.println("GET / HTTP/1.1");
        // Get a response from the time server but try until the response is not an empty line.
   
        while (m_client.connected()) {
            String line = "";
                //do {
                    line = m_client.readStringUntil('\n');
                    if (line.startsWith("5 ")) {
                        line.remove(0, 1);
                        struct tm timeinfo;
                        strptime(line.c_str(), "%s", &timeinfo);
                        setenv("TZ", "JST-9", 1);
                        tzset();
                        time_t now = mktime(&timeinfo);
                        printf("Time: %s\n",ctime(&now));
                        CruxOSLog::Logging(__FUNCTION__, "REC Time: " + std::string(ctime(&now)));

                        // Write the Time to the Time Variable as Necessary
                        MemoryManagement::modify_variable(CN_WIFI_TIME_VAR, std::to_string(timeinfo.tm_year) +":"+ 
                                        std::to_string(timeinfo.tm_mon) +":"+ std::to_string(timeinfo.tm_mday) +":"+ 
                                        std::to_string(timeinfo.tm_hour) +":"+ std::to_string(timeinfo.tm_min) +":"+ 
                                        std::to_string(timeinfo.tm_sec));
                        CruxOSLog::Logging(__FUNCTION__, "Wrote "+std::string(ctime(&now)) + "To WiFi Time Var.");

                        break;
                    } else {
                        CruxOSLog::Logging(__FUNCTION__, "Empty Line Received");
                    }
                    CruxOSLog::Logging(__FUNCTION__, "LINE: "+std::string(line.c_str()));
                //}while(line == "");
            }
        
        //Close the connection
        m_client.flush();
        m_client.stop();
        CruxOSLog::Logging(__FUNCTION__, "Connection Closed.");
        break;
    } else {
        CruxOSLog::Logging(__FUNCTION__, "Connection to "+server+ ": Unsuccessful");
    }

    
  }
}
