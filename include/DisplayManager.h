/**
 * \author Benrick Smit
 * \date Updated 21/12/2022
 * \brief The Display Manager Class takes care of the viewing of different faces for the CruxOS
 * 
*/


#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H


#include <Adafruit_GFX.h>
#include <Arduino_GFX_Library.h>
#include <Arduino_TFT.h>
#include <SPI.h>
#include <RTClib.h>
#include <TFT_eSPI.h>

#include <cstdlib>

#include <InterfaceHelper.h>
#include <cruxos_constants.h>
#include <CruxOSLog.h>

class DisplayManager {
public:
    static DisplayManager* get_instance();

    void begin();
    void flush();
    void update_display(const char* text);

protected:
    void circular_progress_bar(int x, int y, int percentage);

private:
    DisplayManager();
    DisplayManager(DisplayManager const&) = delete;
    void operator=(DisplayManager const&) = delete;

    
    Arduino_DataBus *m_bus;
    Arduino_GFX *m_gfx;

    TFT_eSPI m_tft;
    TFT_eSprite m_tft_image;

    static DisplayManager* m_instance;
};



#endif