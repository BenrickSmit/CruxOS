#ifndef ABSTRACTWATCHINTERFACE_H
#define ABSTRACTWATCHINTERFACE_H

#include <TFT_eSPI.h>

#include <array>
#include <string>
#include <ctime>
#include <cstdlib>

#include <InterfaceHelper.h>
#include <CruxOSLog.h>

class AbstractWatchInterface {
public:
    AbstractWatchInterface(TFT_eSPI *tft, TFT_eSprite *foreground_sprite);
    ~AbstractWatchInterface();

    void begin();
    virtual void draw() = 0;
    TFT_eSprite* get_sprite();
    void create_image();

private:
    TFT_eSPI *m_tft;
    TFT_eSprite *m_foreground_sprite;
};

#endif