#ifndef WATCHINTERFACEMANAGER_H
#define WATCHINTERFACEMANAGER_H

#include <Arduino.h>

#include <AbstractWatchInterface.h>
#include <watchface_simple.h>
#include <watchface_digital.h>
#include <watchface_settings.h>
#include <watchface_hitman.h>
#include <watchface_withings.h>

#include <vector>

class WatchInterfaceManager {
public:
    WatchInterfaceManager(TFT_eSPI *tft, TFT_eSprite *sprite);
    ~WatchInterfaceManager();

    void add_screen(AbstractWatchInterface* screen);
    void init();
    void begin();
    void draw_next_screen();
    void draw_prev_screen();


    void draw_basic_screens();
protected:
    

private:
    std::vector<AbstractWatchInterface*> m_screens;
    int m_current_screen = 0;

    TFT_eSPI *m_tft;
    TFT_eSprite *m_sprite;
};

#endif