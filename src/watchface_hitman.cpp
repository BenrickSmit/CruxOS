#include "watchface_hitman.h"

watchface_hitman::watchface_hitman(TFT_eSPI* tft, TFT_eSprite* foreground_sprite):
    AbstractWatchInterface(tft, foreground_sprite){
}

void watchface_hitman::draw(){
    AbstractWatchInterface::get_sprite()->fillSprite(TFT_BLACK);

    if(get_sprite()->created()){
        CruxOSLog::Logging(__FUNCTION__, "m_foreground_sprite exists");
    }else {
        CruxOSLog::Logging(__FUNCTION__, "m_foreground_sprite doesn't exists");
    }

    uint16_t bg_colour = InterfaceHelper::lighten_colour(InterfaceHelper::get_grey(get_sprite()), 60);
    uint16_t text_colour = InterfaceHelper::get_black(get_sprite());

    get_sprite()->fillSprite(bg_colour);
    InterfaceHelper::draw_progress_bar(get_sprite(), 25, 80, 80, 10, 100, InterfaceHelper::get_orange(get_sprite()), InterfaceHelper::get_orange(get_sprite()));
    InterfaceHelper::draw_progress_bar(get_sprite(), 25, 160, 80, 10, 100, InterfaceHelper::get_orange(get_sprite()), InterfaceHelper::get_orange(get_sprite()));
    
    InterfaceHelper::draw_progress_bar(get_sprite(), 130, 80, 80, 10, 100, InterfaceHelper::get_orange(get_sprite()), InterfaceHelper::get_orange(get_sprite()));
    InterfaceHelper::draw_progress_bar(get_sprite(), 130, 160, 80, 10, 100, InterfaceHelper::get_orange(get_sprite()), InterfaceHelper::get_orange(get_sprite()));
    

    InterfaceHelper::draw_hours_text(get_sprite(), 70, 100, text_colour);
    InterfaceHelper::draw_minutes_text(get_sprite(), 174, 100, text_colour);
    InterfaceHelper::draw_location_text(get_sprite(), 124, 100, ":", text_colour);

    //Add in the extra detail
    // Steps
    InterfaceHelper::draw_steps_text(get_sprite(), 170, 190, 10800, text_colour);
    // Days
    std::string display = InterfaceHelper::get_month_string(true) + "-" + InterfaceHelper::get_day_string();
    InterfaceHelper::draw_system_information(get_sprite(), 65, 60, display, text_colour, bg_colour);
    // Week day
    InterfaceHelper::draw_weekday_text(get_sprite(), 170, 60, text_colour, true);
    // Weather
    std::string weather_information = MemoryManagement::get_value(CN_WEATHER_VAR);
    std::string weather_curr_temp = MemoryManagement::get_value(CN_WEATHER_TEMP_CURR_VAR);
    std::string weather_min_temp = MemoryManagement::get_value(CN_WEATHER_TEMP_MIN_VAR);
    std::string weather_max_temp = MemoryManagement::get_value(CN_WEATHER_TEMP_MAX_VAR);
    bool display_weather_data = (weather_information != "N/A" ? true: false);

    if(display_weather_data){
        // Only display the weather information if it can get the relevant data
        InterfaceHelper::draw_weather_status(get_sprite(), 48, 190, weather_information.c_str());
    }
    

    // Battery
    std::string battery_level_str = MemoryManagement::get_value(CN_BATTERY_VAR.c_str());
    int battery_level = MemoryManagement::to_int(battery_level_str);
    InterfaceHelper::draw_battery_line(get_sprite(), 45, 178, 150, battery_level);


    AbstractWatchInterface::create_image();
}
