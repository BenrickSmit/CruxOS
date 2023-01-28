#include "WatchInterface.h"

WatchInterface::WatchInterface(TFT_eSPI* tft, TFT_eSprite* foreground_sprite) : 
    m_tft(tft), m_foreground_sprite(foreground_sprite) {
    m_foreground_sprite->setColorDepth(8);
    m_foreground_sprite->createSprite(SCREEN_WIDTH, SCREEN_HEIGHT);

    if(m_foreground_sprite->created()){
        CruxOSLog::Logging(__FUNCTION__, "Sprite Created", LOG_ERROR);
    }else{
        CruxOSLog::Logging(__FUNCTION__, "Sprite NOT Created", LOG_ERROR);
    }
}

void WatchInterface::begin()
{
    m_tft->begin();
    m_tft->fillScreen(TFT_BLACK);
    m_tft->setCursor(0, 0);
    m_tft->setTextColor(TFT_WHITE, TFT_BLACK);
    m_tft->setTextDatum(MC_DATUM);
    m_tft->setTextSize(2);
    m_tft->setFreeFont(&Roboto_Thin_24);
}

//#include <Fonts/GFXFF/>

void WatchInterface::draw(std::string text){
    m_foreground_sprite->fillSprite(TFT_BLACK);
    InterfaceHelper::draw_circular_progress_bar(m_foreground_sprite,120, 120, 110, 10, (InterfaceHelper::get_seconds()/60.0)*100.0, InterfaceHelper::get_orange(m_foreground_sprite), InterfaceHelper::darken_colour(InterfaceHelper::get_orange(m_foreground_sprite), 70), TFT_BLACK);
    //InterfaceHelper::draw_progress_bar(m_foreground_sprite, 40, 160, 160, 10, (InterfaceHelper::get_seconds()/60.0)*100.0, TFT_ORANGE, TFT_BLACK);
    InterfaceHelper::draw_wide_line_clock_ticks(m_foreground_sprite, 120, 120, 120, 12, 2, 4, InterfaceHelper::get_orange(m_foreground_sprite));
    InterfaceHelper::draw_stylised_clock_hands(m_foreground_sprite, 120, 120, InterfaceHelper::get_hour(), InterfaceHelper::get_minutes(), InterfaceHelper::get_seconds(), InterfaceHelper::get_blue(m_foreground_sprite), true);

    InterfaceHelper::draw_hours_text(m_foreground_sprite, 120, 60, InterfaceHelper::get_orange(m_foreground_sprite));
    InterfaceHelper::draw_minutes_text(m_foreground_sprite, 120, 140,  InterfaceHelper::get_white(m_foreground_sprite));


    int x = 50, y = 50, length = 8, angle = 65, offset = 8, box_size = 30;
    
    srand(time(0));
    int random_number = rand() % 11;
    InterfaceHelper::draw_weather_status(m_foreground_sprite, (x*2)+5, y, InterfaceHelper::get_weather_string(WEATHER_CODE(random_number)));
    InterfaceHelper::draw_battery_line(m_foreground_sprite, 30, 140, 180, random_number*10);
    InterfaceHelper::draw_battery_level(m_foreground_sprite, 110, 160, random_number*10, TFT_WHITE, TFT_BLACK, true);
    InterfaceHelper::draw_steps_text(m_foreground_sprite, 110, 180, random_number*100, TFT_WHITE);
    //InterfaceHelper::draw_system_information(m_foreground_sprite, x+40, y+4, InterfaceHelper::get_weather_string(WEATHER_CODE(random_number)), InterfaceHelper::get_orange(m_foreground_sprite), InterfaceHelper::darken_colour(InterfaceHelper::get_orange(m_foreground_sprite)), true, true);
    //m_foreground_sprite->drawRect((x*2)+5, y, box_size, box_size, TFT_ORANGE);

    m_foreground_sprite->pushSprite(0, 0);
}
