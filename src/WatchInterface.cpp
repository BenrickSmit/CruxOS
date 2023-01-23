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
    m_tft->setFreeFont(&Roboto_Thin_24);;
}

//#include <Fonts/GFXFF/>

void WatchInterface::draw(std::string text){
    m_foreground_sprite->fillSprite(TFT_BLACK);
    InterfaceHelper::draw_circular_progress_bar(m_foreground_sprite,120, 120, 120, 10, (InterfaceHelper::get_seconds()/60.0)*100.0, TFT_ORANGE, TFT_BLACK, TFT_BLACK);
    //InterfaceHelper::draw_progress_bar(m_foreground_sprite, 40, 160, 160, 10, (InterfaceHelper::get_seconds()/60.0)*100.0, TFT_ORANGE, TFT_BLACK);
    
    InterfaceHelper::draw_progress_bar(m_foreground_sprite, 40, 160-20, 24, 10, (InterfaceHelper::get_hour()/24.0)*100.0, TFT_ORANGE, TFT_BLACK);
    InterfaceHelper::draw_progress_bar(m_foreground_sprite, 40, 170-20, 60, 10, (InterfaceHelper::get_minutes()/60.0)*100.0, TFT_ORANGE, TFT_BLACK);
    InterfaceHelper::draw_progress_bar(m_foreground_sprite, 40, 180-20, 60, 10, (InterfaceHelper::get_seconds()/60.0)*100.0, TFT_ORANGE, TFT_BLACK);

    m_foreground_sprite->setFreeFont(&Roboto_Thin_24);
    m_foreground_sprite->setTextSize(2);
    m_foreground_sprite->setTextWrap(false);
    m_foreground_sprite->setCursor(SCREEN_WIDTH/8, SCREEN_HEIGHT/2);
    m_foreground_sprite->setTextColor(TFT_WHITE, TFT_BLACK);
    m_foreground_sprite->setTextDatum(MC_DATUM);
    m_foreground_sprite->print(text.c_str());


    int x = 50, y = 50, length = 8, angle = 65, offset = 8, box_size = 30;
    
    srand(time(0));
    int random_number = rand() % 10;
    InterfaceHelper::draw_weather_status(m_foreground_sprite, x, y, InterfaceHelper::get_weather_string(WEATHER_CODE(random_number)));//FEW_CLOUDS));
    m_foreground_sprite->drawRect(x, y, box_size, box_size, TFT_ORANGE);

    m_foreground_sprite->pushSprite(0, 0);
}
