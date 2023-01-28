#ifndef WATCHFACE_HITMAN_H
#define WATCHFACE_HITMAN_H

#include <Arduino.h>

#include <AbstractWatchInterface.h>

class watchface_hitman : public AbstractWatchInterface {
public:
    watchface_hitman(TFT_eSPI* tft, TFT_eSprite* foreground_sprite);

    void draw();

private:

};

#endif