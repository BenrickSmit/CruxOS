#include "DisplayManager.h"

DisplayManager* DisplayManager::m_instance = nullptr;

DisplayManager* DisplayManager::get_instance(){
    if(!m_instance){
        m_instance = new DisplayManager();
        CruxOSLog::Logging("DisplayManager::get_instance()", "Create Display Manager Instance");
    }
    return m_instance;
}

void DisplayManager::begin(){
    //DisplayManager::get_instance()->m_gfx->begin();//4000000);

    /*
    DisplayManager::get_instance()->m_tft->begin(); // Initialize the display
    DisplayManager::get_instance()->m_tft->fillScreen(TFT_BLACK); // Clear the screen with a black background
    DisplayManager::get_instance()->m_tft->setTextSize(8); // Set the text size to 2
    DisplayManager::get_instance()->m_tft->setTextColor(TFT_WHITE); // Set the text color to white
    */
    DisplayManager::get_instance()->m_tft.fillScreen(TFT_BLACK);
    DisplayManager::get_instance()->m_tft_image.createSprite(SCREEN_WIDTH,SCREEN_HEIGHT); // Create a sprite with a width of 32 pixels and a height of 32 pixels
    DisplayManager::get_instance()->m_tft_image.fillSprite(TFT_RED); // Fill the sprite with the color red
    DisplayManager::get_instance()->m_tft_image.setCursor(SCREEN_WIDTH_CENTRE, SCREEN_HEIGHT_CENTRE);
    DisplayManager::get_instance()->m_tft_image.print("Hello World");
    DisplayManager::get_instance()->m_tft_image.pushSprite(0,0); // Draw the sprite on the display at the position (64, 64)

    CruxOSLog::Logging(__FUNCTION__, "Initialise Screen: Triggered");
}

void DisplayManager::flush(){
    DisplayManager::get_instance()->m_gfx->flush();
    CruxOSLog::Logging(__FUNCTION__, "Flush Screen Buffer: Triggered");
}

void DisplayManager::update_display(const char* text){
    std::string string_condition = "";
    srand(time(0));
    int random_value = rand() % 9;
    switch(random_value){
        case 0: { string_condition = "Clear Sky"; break;}
        case 1: { string_condition = "few clouds"; break;}
        case 2: { string_condition = "scattered clouds"; break;}
        case 3: { string_condition = "broken clouds"; break;}
        case 4: { string_condition = "shower rain"; break;}
        case 5: { string_condition = "rain"; break;}
        case 6: { string_condition = "thunderstorm"; break;}
        case 7: { string_condition = "snow"; break;}
        case 8: { string_condition = "mist"; break;}
        default: string_condition = "Clear Sky";
    }

    /*
    DisplayManager::get_instance()->m_tft->setCursor((DisplayManager::get_instance()->m_tft->width() - (DisplayManager::get_instance()->m_tft->textWidth("Hello World") / 2)) / 2, (DisplayManager::get_instance()->m_tft->height() - 16) / 2); // set the cursor position to the middle of the screen
    DisplayManager::get_instance()->m_tft->println("Hello World");
    DisplayManager::get_instance()->m_tft->fillScreen(TFT_BLACK); // Clear the screen with a black 
    
    /*
    InterfaceHelper::draw_circular_progress_bar(DisplayManager::get_instance()->m_gfx, 120, 120, 100, ((InterfaceHelper::get_seconds()/60.0) * 100), InterfaceHelper::get_green(DisplayManager::get_instance()->m_gfx));
    InterfaceHelper::draw_ticks(DisplayManager::get_instance()->m_gfx ,120 , 120, 120, InterfaceHelper::get_light_green(DisplayManager::get_instance()->m_gfx));
    InterfaceHelper::draw_clock_arms(DisplayManager::get_instance()->m_gfx, 120, 120, 110, 100, InterfaceHelper::get_hour(), 
                                                        InterfaceHelper::get_minutes(), InterfaceHelper::get_seconds(), 1);
    InterfaceHelper::draw_weather_status(DisplayManager::get_instance()->m_gfx ,120 , 60, string_condition);

    DisplayManager::get_instance()->m_gfx->setCursor(SCREEN_WIDTH_CENTRE-80, SCREEN_HEIGHT_CENTRE-10);
    DisplayManager::get_instance()->m_gfx->setTextSize(4);
    DisplayManager::get_instance()->m_gfx->setTextColor(BLUE);
    DisplayManager::get_instance()->m_gfx->println(text);
    */

    //DisplayManager::get_instance()->m_gfx->flush();
    CruxOSLog::Logging(__FUNCTION__, "Update Display: Triggered");
    //DisplayManager::get_instance()->m_gfx->flush();
}


DisplayManager::DisplayManager():m_tft(), m_tft_image(&m_tft){
    // Basic Screen Setup
    //m_bus = new Arduino_HWSPI(BUILTIN_TFT_DC /*DC*/, BUILTIN_TFT_CS /*CS*/, BUILTIN_TFT_SCK, BUILTIN_TFT_MOSI, BUILTIN_TFT_MISO);//16 /* DC */, 5 /* CS */);
    //m_gfx = new Arduino_GC9A01(m_bus, BUILTIN_TFT_RST /*RST*/, 0, true);
    //m_gfx = new Arduino_GC9A01(m_bus, BUILTIN_TFT_RST /*RST*/);//m_bus, 17 /* RST */);

    m_tft.begin();
    m_tft.fillScreen(TFT_BLACK);
    m_tft_image.createSprite(SCREEN_WIDTH, SCREEN_HEIGHT);
    CruxOSLog::Logging(__FUNCTION__, "Constructor: Triggered");
}
