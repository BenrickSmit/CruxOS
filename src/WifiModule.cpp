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
    "nist1-wa.ustiming.org"};
}

WifiModule::~WifiModule(){

}

void WifiModule::begin(const char* ssid, const char* password){
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(TIME_UPDATE_COUNTER);
        printf(".");
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
        printf("\nConnection to (%s): Successful\n", server);
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
                        break;
                    } else {
                        printf("Empty Line\n");
                    }
                    printf("LINE: %s\n", line);
                //}while(line == "");
            }
        
        //Close the connection
        m_client.flush();
        m_client.stop();
        Serial.println("Connection closed");
        break;
    } else {
        printf("(%s): Unsuccessful.\n");
    }

    
  }
}
