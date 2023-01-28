#ifndef WATCHFACE_SIMPLE_H
#define WATCHFACE_SIMPLE_H

#include <Arduino.h>

#include <AbstractWatchInterface.h>

class watchface_simple : public AbstractWatchInterface {
public:
    watchface_simple(TFT_eSPI* tft, TFT_eSprite* foreground_sprite);

    void draw();

private:

};

#endif