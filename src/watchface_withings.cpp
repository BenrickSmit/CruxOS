#include "watchface_withings.h"

watchface_withings::watchface_withings(TFT_eSPI* tft, TFT_eSprite* foreground_sprite) : 
    AbstractWatchInterface(tft, foreground_sprite){
        m_display_duration = 12*1000;  // 1 seconds
        m_start_time = millis();
}

void watchface_withings::draw(){
    AbstractWatchInterface::get_sprite()->fillSprite(TFT_BLACK);

    if(get_sprite()->created()){
        CruxOSLog::Logging(__FUNCTION__, "m_foreground_sprite exists");
    }else {
        CruxOSLog::Logging(__FUNCTION__, "m_foreground_sprite doesn't exists");
    }

    // Battery Information
    std::string battery_level_str = MemoryManagement::get_value(CN_BATTERY_VAR.c_str());
    int battery_level = MemoryManagement::to_int(battery_level_str);

    // Colours
    uint16_t bg_colour = InterfaceHelper::get_black(get_sprite());//InterfaceHelper::lighten_colour(InterfaceHelper::get_grey(get_sprite()), 60);
    uint16_t text_colour = InterfaceHelper::get_white(get_sprite());
    uint16_t main_colour = InterfaceHelper::get_orange(get_sprite());
    uint16_t main_colour_dark = InterfaceHelper::darken_colour(main_colour, 70);
    uint16_t main_arm_colour = InterfaceHelper::lighten_colour(InterfaceHelper::get_grey(get_sprite()), 24);//InterfaceHelper::get_triadic_colours(main_colour).at(1);
    uint16_t battery_colour =  InterfaceHelper::get_battery_colour(get_sprite(), battery_level);
    uint16_t comp_colour_1 = InterfaceHelper::get_analagous_complementary_colours(main_colour).at(1);
    uint16_t comp_colour_2 = InterfaceHelper::get_analagous_complementary_colours(main_colour).at(2);
    uint16_t comp_colour_3 = InterfaceHelper::get_analagous_complementary_colours(main_colour).at(3);
    uint16_t comp_colour_4 = InterfaceHelper::get_analagous_complementary_colours(main_colour).at(4);

    // Background
    get_sprite()->fillSprite(bg_colour);

    // Circles For Information
    int circle_radius = 22;
    // Weather Info & temp
    std::string weather_information = MemoryManagement::get_value(CN_WEATHER_VAR);
    std::string weather_curr_temp = MemoryManagement::get_value(CN_WEATHER_TEMP_CURR_VAR);
    std::string weather_min_temp = MemoryManagement::get_value(CN_WEATHER_TEMP_MIN_VAR);
    std::string weather_max_temp = MemoryManagement::get_value(CN_WEATHER_TEMP_MAX_VAR);
    bool display_weather_data = (weather_information != "N/A" ? true: false);


    unsigned long current_millis = millis();
    if(display_weather_data){
        // Only display the weather information if it can get the relevant data
        if (current_millis - m_start_time < m_display_duration) {
            // draw first image here
            get_sprite()->fillSmoothCircle(120, 80, circle_radius, main_colour_dark);
            InterfaceHelper::draw_weather_status(get_sprite(), 105, 65, weather_information.c_str());
            
        } else {
            // draw second image here
            get_sprite()->fillSmoothCircle(120, 80, circle_radius, main_colour_dark);
            InterfaceHelper::draw_weather_text(get_sprite(), 120, 74, weather_curr_temp, text_colour);
            m_start_time = millis();
        } 
    }
    // Steps
    int steps_total = std::stoi(MemoryManagement::get_value(CN_STEPS_SAVED));
    if(steps_total > -1) {
        get_sprite()->fillSmoothCircle(120, 180, circle_radius, main_colour_dark);
        InterfaceHelper::draw_steps_text(get_sprite(), 120, 174, steps_total, text_colour);
    }

    // Date
    // Change between the date and the year
    std::string text = "";
        if (current_millis - m_start_time < m_display_duration) {
            // draw first image here
            get_sprite()->fillSmoothCircle(70, 160, circle_radius, main_colour_dark);
            text = InterfaceHelper::get_month_string(true) +"-"+InterfaceHelper::get_day_string();
            InterfaceHelper::draw_custom_text(get_sprite(), 70, 158, text, 1.5, text_colour);
            
        } else {
            // draw second image here
            get_sprite()->fillSmoothCircle(70, 160, circle_radius, main_colour_dark);
            text = InterfaceHelper::get_year_string(false);
            InterfaceHelper::draw_custom_text(get_sprite(), 70, 158, text, 1.5, text_colour);
        } 

    // Day
    get_sprite()->fillSmoothCircle(170, 160, circle_radius, main_colour_dark);
    text = InterfaceHelper::get_week_day_string(true);
    InterfaceHelper::draw_custom_text(get_sprite(), 170, 154, text, 2, text_colour);

    // Clock Hands
    InterfaceHelper::draw_circular_progress_bar(get_sprite(), 120, 120, 120, 8, 100, main_colour_dark, bg_colour, bg_colour);
    InterfaceHelper::draw_wide_line_clock_ticks(get_sprite(), 120, 120, 120, 12, 3, 2, main_colour);
    
    InterfaceHelper::draw_clock_hands(get_sprite(), 120, 120, InterfaceHelper::get_hour(), InterfaceHelper::get_minutes(), InterfaceHelper::get_seconds(), main_arm_colour, true);
    InterfaceHelper::draw_wedged_clock_hands(get_sprite(), 120, 120, InterfaceHelper::get_hour(), InterfaceHelper::get_minutes(), InterfaceHelper::get_seconds(), main_arm_colour, true);

    InterfaceHelper::draw_clock_hand_wedge(get_sprite(), 120, 120, SCREEN_WIDTH_CENTRE*0.32, SCREEN_WIDTH_CENTRE*0.22, InterfaceHelper::convert_to_angle(InterfaceHelper::get_hour(),12)-90, 2, battery_colour);
    InterfaceHelper::draw_clock_hand_wedge(get_sprite(), 120, 120, SCREEN_WIDTH_CENTRE*0.52, SCREEN_WIDTH_CENTRE*0.22, InterfaceHelper::convert_to_angle(InterfaceHelper::get_minutes(),60)-90, 1, battery_colour);
    

    AbstractWatchInterface::create_image();
}
