#include "watchface_digital.h"

watchface_digital::watchface_digital(TFT_eSPI* tft, TFT_eSprite* foreground_sprite): 
    AbstractWatchInterface(tft, foreground_sprite){
}

void watchface_digital::draw(){
    AbstractWatchInterface::get_sprite()->fillSprite(TFT_BLACK);

    if(get_sprite()->created()){
        CruxOSLog::Logging(__FUNCTION__, "m_foreground_sprite exists");
    }else {
        CruxOSLog::Logging(__FUNCTION__, "m_foreground_sprite doesn't exists");
    }

    std::string battery_level_str = MemoryManagement::get_value(CN_BATTERY_VAR.c_str());
    int battery_level = MemoryManagement::to_int(battery_level_str);
    InterfaceHelper::draw_battery_line(get_sprite(), 40, 120, 160, battery_level);
    InterfaceHelper::draw_hours_text(get_sprite(), 120, 60, InterfaceHelper::get_orange(get_sprite()));
    InterfaceHelper::draw_minutes_text(get_sprite(), 120, 135,  InterfaceHelper::get_white(get_sprite()));

    CruxOSLog::Logging(__FUNCTION__, "Watchface Digital Draw Called");
    
    AbstractWatchInterface::create_image();
}
