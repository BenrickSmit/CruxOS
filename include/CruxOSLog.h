#ifndef CRUXOSLOG_H
#define CRUXOSLOG_H

#include <ArduinoLog.h>

#include <fstream>
#include <string>

#include <cruxos_constants.h>

class CruxOSLog{
public:
    static void Logging(const std::string& caller = "MAIN", const std::string& message = "Basic Message", LOG_LEVEL priority = LOG_INFO);

private:
    static std::string get_priority_string(LOG_LEVEL priority);
};

#endif