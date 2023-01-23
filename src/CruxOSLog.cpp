#include "CruxOSLog.h"

void CruxOSLog::Logging(const std::string& caller, const std::string& message, LOG_LEVEL priority){
    // Output To A File
    std::ofstream out("log.txt");//, std::ios::app);
        out << "[" << caller << "]: (" << CruxOSLog::get_priority_string(priority) << "):> " << message << "\n";
        out.close();

    // Output to Terminal using ArduinoLog
    Serial.begin(BAUD_RATE);
    //logger.add(Serial, DEBUG_LEVEL_VERBOSE);
    std::string output = "[" + caller + "] " + message +"\n";
    Log.begin(LOG_LEVEL_VERBOSE, &Serial); //.log(priority, "[%s] %s", caller.c_str(), message.c_str());
    if(priority == LOG_INFO){   // INFO
        Log.notice("[%s] %s\n", caller.c_str(), message.c_str());
        //printI(F(output.c_str()));
    }else if (priority == LOG_WARNING){ // WARNING
        Log.warning("[%s] %s\n", caller.c_str(), message.c_str());
        //printW(F(output.c_str()));
    }else {
        Log.error("[%s] %s\n", caller.c_str(), message.c_str());
        //printE(F(output.c_str()));
    }
    
}

std::string CruxOSLog::get_priority_string(LOG_LEVEL priority){
    if (priority == LOG_INFO){
        return std::string("INFO");
    }else if (priority == LOG_WARNING){
        return std::string("WARNING");
    }else {
        return std::string("ERROR");
    }
    return std::string();
}

