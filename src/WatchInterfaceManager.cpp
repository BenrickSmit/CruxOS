#include "WatchInterfaceManager.h"

WatchInterfaceManager::WatchInterfaceManager(TFT_eSPI *tft, TFT_eSprite *sprite){
    m_tft = tft;
    m_sprite = sprite;
    m_sprite->setColorDepth(8);
    m_sprite->createSprite(SCREEN_WIDTH, SCREEN_HEIGHT);

    draw_basic_screens();
}

WatchInterfaceManager::~WatchInterfaceManager(){
    // Delete all the pointers
    for (auto i = 0; i < m_screens.size(); i++){
        delete m_screens[i];
    }

    m_screens.clear();
    CruxOSLog::Logging(__FUNCTION__, "Delete Screens of Type AbstractWatchInterface");
}

void WatchInterfaceManager::add_screen(AbstractWatchInterface* screen) {
    m_screens.push_back(screen);
    CruxOSLog::Logging(__FUNCTION__, "Added A Screen");
}

void WatchInterfaceManager::init() {
    if (!m_screens.empty()) {
        m_screens[m_current_screen]->draw();
    }
    CruxOSLog::Logging(__FUNCTION__, "Initialised and Drew Current Screen");
}

void WatchInterfaceManager::begin(){
    m_tft->begin();
    m_tft->fillScreen(TFT_BLACK);
    m_tft->setCursor(0, 0);
    m_tft->setTextColor(TFT_WHITE, TFT_BLACK);
    m_tft->setTextDatum(MC_DATUM);
    m_tft->setTextSize(2);

    CruxOSLog::Logging(__FUNCTION__, "Setup TFT Beginning Settings");
}

void WatchInterfaceManager::draw_next_screen() {
    if (m_current_screen < m_screens.size() - 1) {
        m_current_screen++;
        m_screens[m_current_screen]->draw();
    }
    CruxOSLog::Logging(__FUNCTION__, "Drew Next Screen");
}

void WatchInterfaceManager::draw_prev_screen() {
    if (m_current_screen > 0) {
        m_current_screen--;
        m_screens[m_current_screen]->draw();
    }

    CruxOSLog::Logging(__FUNCTION__, "Drew Previous Screen");
}

void WatchInterfaceManager::draw_basic_screens(){
    add_screen(new watchface_digital(m_tft, m_sprite));
    add_screen(new watchface_hitman(m_tft, m_sprite));
    add_screen(new watchface_withings(m_tft, m_sprite));
    add_screen(new watchface_simple(m_tft, m_sprite));
    add_screen(new watchface_settings(m_tft, m_sprite));

    std::string display = "Created Basic Screens [" + std::to_string(m_screens.size()) + "].";
    CruxOSLog::Logging(__FUNCTION__, display.c_str());
}
