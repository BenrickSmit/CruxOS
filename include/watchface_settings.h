#ifndef WATCHFACE_SETTINGS_H
#define WATCHFACE_SETTINGS_H

#include <Arduino.h>

#include <AbstractWatchInterface.h>

#include <SystemInfo.h>
#include <MemoryManagement.h>

class watchface_settings : public AbstractWatchInterface {
public:
    watchface_settings(TFT_eSPI* tft, TFT_eSprite* foreground_sprite);

    void draw();

private:
    SystemInfo m_info;
};

#endif