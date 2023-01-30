#include "ClockSync.h"

ClockSync *ClockSync::m_instance = nullptr;

ClockSync *ClockSync::get_instance(){
    if (!m_instance){
        m_instance = new ClockSync();
    }

    return m_instance;
}

void ClockSync::delete_instance(){
    delete m_instance;
    m_instance = nullptr;
}

std::string ClockSync::get_rtc_time(){
    return get_hours()+":"+get_minutes()+":"+get_seconds();
}

std::string ClockSync::get_full_rtc_time(){
    ClockSync *cs = cs->get_instance();
    DateTime date_time = cs->m_rtc.now();
    time_t rtc_clock_time = cs->to_time_t(date_time);
    std::string time_t_str = ctime(&rtc_clock_time);
    return time_t_str;
}

std::string ClockSync::get_hours(){
    std::string to_return = "";
    ClockSync *cs = cs->get_instance();

    if(cs->get_int_hours() < 10){
        to_return += "0";
    }
    to_return += std::to_string(cs->get_int_hours());

    return to_return;
}

std::string ClockSync::get_minutes(){
    std::string to_return = "";
    ClockSync *cs = cs->get_instance();

    if(cs->get_int_minutes() < 10){
        to_return += "0";
    }
    to_return += std::to_string(cs->get_int_minutes());

    return to_return;
}

std::string ClockSync::get_seconds(){
    std::string to_return = "";
    ClockSync *cs = cs->get_instance();

    if(cs->get_int_seconds() < 10){
        to_return += "0";
    }
    to_return += std::to_string(cs->get_int_seconds());

    return to_return;
}

std::string ClockSync::get_year(bool abbreviation_flag) {
    ClockSync *cs = cs->get_instance();
    std::string to_return = "";
    if(abbreviation_flag){
        // Return Abbreviated Year
        to_return = std::to_string(cs->get_int_year());
        to_return = to_return.substr(to_return.length()-2);
    } else {
        // Return full year.
        to_return = std::to_string(cs->get_int_year());
    }
    return to_return;
}

std::string ClockSync::get_month() {
    std::string to_return = "";
    ClockSync *cs = cs->get_instance();

    if(cs->get_int_month() < 10){
        to_return += "0";
    }
    to_return = std::to_string(cs->get_int_month());

    return to_return;
}

std::string ClockSync::get_month_string(bool abbreviation_flag){
    ClockSync *cs = cs->get_instance();

    return cs->convert_month_to_string(cs->get_int_month(), abbreviation_flag);
}

std::string ClockSync::get_day() {
    std::string to_return = "";
    ClockSync *cs = cs->get_instance();

    if(cs->get_int_day() < 10){
        to_return += "0";
    }
    to_return = std::to_string(cs->get_int_day());

    return to_return;
}

std::string ClockSync::get_day_of_week(){
    std::string to_return = "";
    ClockSync *cs = cs->get_instance();

    if(cs->get_int_day_of_week() < 10){
        to_return += "0";
    }
    to_return = std::to_string(cs->get_int_day_of_week());

    return to_return;
}

std::string ClockSync::get_day_of_week_string(bool abbreviation_flag){
    std::string to_return = "";
    ClockSync *cs = cs->get_instance();

    return cs->convert_day_of_week_to_string(cs->get_int_month(), abbreviation_flag);
}

int ClockSync::get_int_year(){
    ClockSync *cs = cs->get_instance();

    return cs->m_rtc.now().year();
}

int ClockSync::get_int_month(){
    ClockSync *cs = cs->get_instance();

    return cs->m_rtc.now().month();
}

int ClockSync::get_int_day(){
    ClockSync *cs = cs->get_instance();

    return cs->m_rtc.now().day();
}

int ClockSync::get_int_day_of_week(){
    ClockSync *cs = cs->get_instance();
    return cs->m_rtc.now().dayOfTheWeek();
}

int ClockSync::get_int_hours(){
    ClockSync *cs = cs->get_instance();

    return cs->m_rtc.now().hour();
}

int ClockSync::get_int_minutes(){
    ClockSync *cs = cs->get_instance();

    return cs->m_rtc.now().minute();
}

int ClockSync::get_int_seconds(){
    ClockSync *cs = cs->get_instance();

    return cs->m_rtc.now().second();
}

void ClockSync::set_hours(int new_hours){
    ClockSync *cs = cs->get_instance();
    cs->m_rtc.adjust(ClockSync::create_datetime(cs->get_int_year(), cs->get_int_month(), 
        cs->get_int_day(), new_hours, cs->get_int_minutes(), cs->get_int_seconds()));
}

void ClockSync::set_minutes(int new_minutes){
    ClockSync *cs = cs->get_instance();
    cs->m_rtc.adjust(ClockSync::create_datetime(cs->get_int_year(), cs->get_int_month(), 
        cs->get_int_day(), cs->get_int_hours(), new_minutes, cs->get_int_seconds()));
}

void ClockSync::set_seconds(int new_seconds){
    ClockSync *cs = cs->get_instance();
    cs->m_rtc.adjust(ClockSync::create_datetime(cs->get_int_year(), cs->get_int_month(), 
        cs->get_int_day(), cs->get_int_hours(), cs->get_int_minutes(), new_seconds));
}

void ClockSync::set_year(int new_year){
    ClockSync *cs = cs->get_instance();
    cs->m_rtc.adjust(ClockSync::create_datetime(new_year, cs->get_int_month(), 
        cs->get_int_day(), cs->get_int_hours(), cs->get_int_minutes(), cs->get_int_seconds()));
}

void ClockSync::set_month(int new_month){
    ClockSync *cs = cs->get_instance();
    cs->m_rtc.adjust(ClockSync::create_datetime(cs->get_int_year(), new_month, 
        cs->get_int_month(), cs->get_int_hours(), cs->get_int_minutes(), cs->get_int_seconds()));
}

void ClockSync::set_day(int new_day){
    ClockSync *cs = cs->get_instance();
    cs->m_rtc.adjust(ClockSync::create_datetime(cs->get_int_year(), cs->get_int_month(), 
        new_day, cs->get_int_hours(), cs->get_int_minutes(), cs->get_int_seconds()));
}

std::string ClockSync::get_millis(){
    return std::to_string(millis());
}

void ClockSync::get_wifi_time(){
    // This function will use the Wifi class to get the current time from one of the available time servers.
    // This will update the variable in memory for the wifi time should it exist and is not empty

    std::string str_SSID, str_PASS;
    std::string wifi_time = "";
    int year, month, day, hour, minute, second;
    char delimiter;

    //while(wifi_time.empty()){
        wifi_time = MemoryManagement::get_value(CN_WIFI_TIME_VAR);
    //}

    // If You got a WIFI time in Memory set the current time to it
    if (!wifi_time.empty()) {
        std::stringstream stream(wifi_time);
        stream >> year >> delimiter >> month >> delimiter >> day >> delimiter >> 
                    hour >> delimiter >> minute >> delimiter >> second;

        // Set the new time
        set_year(year);
        set_month(month);
        set_day(day);
        set_hours(hour);
        set_minutes(minute);
        set_seconds(second);

        // Reset the variable
        MemoryManagement::modify_variable(CN_WIFI_TIME_VAR, "");
        CruxOSLog::Logging(__FUNCTION__, "wifi_time used to set new time");
    }else{
        CruxOSLog::Logging(__FUNCTION__, "wifi_time variable is empty", LOG_ERROR);
    }
    
    CruxOSLog::Logging(__FUNCTION__, "Triggered And Executed");
}

time_t ClockSync::to_time_t(const DateTime &input_datetime) {
    struct tm timeinfo;
    timeinfo.tm_year = input_datetime.year() - 1900;
    timeinfo.tm_mon = input_datetime.month() - 1;
    timeinfo.tm_mday = input_datetime.day();
    timeinfo.tm_hour = input_datetime.hour();
    timeinfo.tm_min = input_datetime.minute();
    timeinfo.tm_sec = input_datetime.second();
    return mktime(&timeinfo);

    CruxOSLog::Logging(__FUNCTION__, "Converted DateTime to time_t");
}

void ClockSync::save_time_to_memory(){
    ClockSync *cs = cs->get_instance();
    time_t now = ClockSync::to_time_t(cs->m_rtc.now());
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
    MemoryManagement::modify_variable(CN_WIFI_TIME_VAR, TIME_STR);
}

DateTime ClockSync::create_datetime(int year, int month, int day, int hour, int minute, int second){
    return DateTime(year, month, day, hour, minute, second);
    CruxOSLog::Logging(__FUNCTION__, "Created a DateTime Object and Returned it");
}

std::string ClockSync::convert_month_to_string(int month, bool abbreviation) {
    if (month < 1 || month > 12) {
        return "N/A";
    }

    // Should the values be valid
    static std::string months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    static std::string full_months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", 
        "October", "November", "December" };

    CruxOSLog::Logging(__FUNCTION__, "Converting Month to String or Abbreviated String");

    return abbreviation ? months[month - 1] : full_months[month - 1];
}

std::string ClockSync::convert_day_of_week_to_string(int day_of_week, bool abbreviation){
    if(day_of_week < 1 || day_of_week > 7){
        return "N/A";
    }

    // Should the values be valid
    static std::string days[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    static std::string full_days[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    CruxOSLog::Logging(__FUNCTION__, "Converting Day of Week to String or Abbreviated String");

    return abbreviation ? days[day_of_week - 1] : full_days[day_of_week - 1];
}


void ClockSync::reset_time(){
    ClockSync *cs = cs->get_instance();
    cs->m_rtc.begin();
    cs->m_rtc.adjust(DateTime(1933, 11, 23, 4, 30, 0));

    std::string display = "RTC Reset:"+std::to_string(cs->m_rtc.now().hour())+":"+std::to_string(cs->m_rtc.now().minute())+":"+std::to_string(cs->m_rtc.now().second());
    CruxOSLog::Logging(__FUNCTION__, display.c_str());
}

void ClockSync::set_rtc_clock(int year, int month, int day, int hour, int minute, int second) {
    // Get the input
    ClockSync *cs = cs->get_instance();
    
    // Set the time of the RTC Component
    CruxOSLog::Logging(__FUNCTION__, "RTC Time Before Update: " + cs->get_full_rtc_time());

    cs->m_rtc.adjust(DateTime(year, month, day, hour, minute, second));
    cs->m_rtc.begin();

    CruxOSLog::Logging(__FUNCTION__, "RTC Time After Update: " + cs->get_full_rtc_time());

    // This is completely unnecessary but doing it for necessity's sake.
    // Set the variables
    cs->set_year(year);
    cs->set_month(month);
    cs->set_day(day);
    cs->set_hours(hour);
    cs->set_minutes(minute);
    cs->set_seconds(second);

    CruxOSLog::Logging(__FUNCTION__, "Updated RTC Time");
}

ClockSync::ClockSync(){
    // Do Nothing For Now
    m_rtc.begin();
    m_rtc.adjust(DateTime(1933, 11, 23, 4, 30, 0));

    //delete time;
}

ClockSync::~ClockSync(){
    // Do Nothing, Possibly
}