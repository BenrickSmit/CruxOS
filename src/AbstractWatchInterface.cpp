#include "AbstractWatchInterface.h"

AbstractWatchInterface::AbstractWatchInterface(TFT_eSPI *tft, TFT_eSprite *foreground_sprite) : 
    m_tft(tft), m_foreground_sprite(foreground_sprite) {
    m_foreground_sprite->setColorDepth(8);
    m_foreground_sprite->createSprite(SCREEN_WIDTH, SCREEN_HEIGHT);

    if(m_foreground_sprite->created()){
        CruxOSLog::Logging(__FUNCTION__, "Sprite Created", LOG_INFO);
    }else{
        CruxOSLog::Logging(__FUNCTION__, "Sprite NOT Created", LOG_ERROR);
    }
}

AbstractWatchInterface::~AbstractWatchInterface(){
    // Delete the pointers as necessary
    delete m_tft;
    delete m_foreground_sprite;

    m_tft = nullptr;
    m_foreground_sprite = nullptr;

    CruxOSLog::Logging(__FUNCTION__, "AbstractWathInterface Destructor");
}

void AbstractWatchInterface::begin(){
    // Basic TFT_eSPI settings
    m_tft->begin();
    m_tft->fillScreen(TFT_BLACK);
    m_tft->setCursor(0, 0);
    m_tft->setTextColor(TFT_WHITE, TFT_BLACK);
    m_tft->setTextDatum(MC_DATUM);
    m_tft->setTextSize(2);
    //m_tft->setFreeFont(&Roboto_Thin_24);
    CruxOSLog::Logging(__FUNCTION__, "Setup TFT_eSPI and TFT_eSprite settings");
}

TFT_eSprite *AbstractWatchInterface::get_sprite(){
    return m_foreground_sprite;
}

void AbstractWatchInterface::create_image(){
    get_sprite()->pushSprite(0, 0);
}
