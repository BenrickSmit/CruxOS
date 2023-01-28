#include "watchface_simple.h"

watchface_simple::watchface_simple(TFT_eSPI* tft, TFT_eSprite* foreground_sprite): 
    AbstractWatchInterface(tft, foreground_sprite){
}

void watchface_simple::draw(){
    AbstractWatchInterface::get_sprite()->fillSprite(TFT_BLACK);

    if(get_sprite()->created()){
        CruxOSLog::Logging(__FUNCTION__, "m_foreground_sprite exists");
    }else {
        CruxOSLog::Logging(__FUNCTION__, "m_foreground_sprite doesn't exists");
    }

    //InterfaceHelper::draw_circular_progress_bar(get_sprite(),120, 120, 110, 10, (InterfaceHelper::get_seconds()/60.0)*100.0, InterfaceHelper::get_orange(get_sprite()), InterfaceHelper::darken_colour(InterfaceHelper::get_orange(get_sprite()), 70), TFT_BLACK);
    InterfaceHelper::draw_wide_line_clock_ticks(get_sprite(), 120, 120, 120, 12, 2, 4, InterfaceHelper::get_orange(get_sprite()));
    InterfaceHelper::draw_stylised_clock_hands(get_sprite(), 120, 120, InterfaceHelper::get_hour(), InterfaceHelper::get_minutes(), InterfaceHelper::get_seconds(), InterfaceHelper::get_blue(get_sprite()), true);
    
    
    std::string battery_level_str = MemoryManagement::get_value(CN_BATTERY_VAR.c_str());
    int battery_level = MemoryManagement::to_int(battery_level_str);
    InterfaceHelper::draw_battery_level(get_sprite(), 110, 40, battery_level, TFT_WHITE, TFT_BLACK, true);

    //InterfaceHelper::draw_battery_line(get_sprite(), 40, 120, 80, 85);
    //InterfaceHelper::draw_hours_text(get_sprite(), 120, 60, InterfaceHelper::get_orange(get_sprite()));
    //InterfaceHelper::draw_minutes_text(get_sprite(), 120, 140,  InterfaceHelper::get_white(get_sprite()));

    CruxOSLog::Logging(__FUNCTION__, "Watchface Simple Draw Called");
    
    AbstractWatchInterface::create_image();
}
