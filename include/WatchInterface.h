#ifndef WATCHINTERFACE_H
#define WATCHINTERFACE_H

#include <TFT_eSPI.h>

#include <array>
#include <string>
#include <ctime>
#include <cstdlib>

#include <InterfaceHelper.h>
#include <CruxOSLog.h>

class WatchInterface {
public:
    WatchInterface(TFT_eSPI *tft, TFT_eSprite *foreground_sprite);

    void begin();
    void draw(std::string text);

private:
    TFT_eSPI *m_tft;
    TFT_eSprite *m_foreground_sprite;
};




#endif