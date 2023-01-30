#ifndef WATCHFACE_WITHINGS_H
#define WATCHFACE_WITHINGS_H

#include <Arduino.h>

#include <AbstractWatchInterface.h>
#include <MemoryManagement.h>
#include <cruxos_constants.h>

class watchface_withings : public AbstractWatchInterface {
public:
    watchface_withings(TFT_eSPI* tft, TFT_eSprite* foreground_sprite);

    void draw();

private:
unsigned long m_start_time;
unsigned long m_display_duration;

};

#endif