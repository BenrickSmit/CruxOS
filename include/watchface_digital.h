#ifndef WATCHFACE_DIGITAL_H
#define WATCHFACE_DIGITAL_H

#include <Arduino.h>

#include <AbstractWatchInterface.h>

class watchface_digital : public AbstractWatchInterface {
public:
    watchface_digital(TFT_eSPI* tft, TFT_eSprite* foreground_sprite);

    void draw();

private:

};

#endif