#include "InterfaceHelper.h"

InterfaceHelper::InterfaceHelper(){
    ClockSync* cs = cs->get_instance();
}

InterfaceHelper::~InterfaceHelper(){
    // Do nothing for now
}

void InterfaceHelper::draw_wide_line_clock_ticks(TFT_eSprite* tft, int x, int y, int radius, int steps, int line_width,
                                                 int line_length, uint16_t colour_fill){
    float angle = 0;
    float angle_increment = 360.0 / steps;
    int inner_radius = radius - (radius/5 - line_length);
    for (int i = 0; i < steps; i++) {
        int tixk_x1 = x + (radius * cos(angle * PI / 180));
        int tick_y1 = y + (radius * sin(angle * PI / 180));
        int tick_x2 = x + (inner_radius * cos(angle * PI / 180));
        int tick_y2 = y + (inner_radius * sin(angle * PI / 180));
        tft->drawWideLine(tixk_x1, tick_y1, tick_x2, tick_y2, line_width, colour_fill);
        angle += angle_increment;
    }
}

void InterfaceHelper::draw_line_clock_ticks(TFT_eSprite* tft, int x, int y, int radius, int steps, int line_length,
                                              uint16_t colour_fill){
    float angle = 0;
    float angle_increment = 360.0 / steps;
    int inner_radius = radius - (radius/5 - line_length);
    for (int i = 0; i < steps; i++) {
        int tixk_x1 = x + (radius * cos(angle * PI / 180));
        int tick_y1 = y + (radius * sin(angle * PI / 180));
        int tick_x2 = x + (inner_radius * cos(angle * PI / 180));
        int tick_y2 = y + (inner_radius * sin(angle * PI / 180));
        tft->drawLine(tixk_x1, tick_y1, tick_x2, tick_y2, colour_fill);
        angle += angle_increment;
    }
}

void InterfaceHelper::draw_circle_clock_ticks(TFT_eSprite* tft, int x, int y, int radius, int steps, 
                                            uint16_t colour_fill) {
    float angle = 0;
    float angle_increment = 360.0 / steps;
    float small_radius = 4;
    for (int i = 0; i < steps; i++) {
        int tixk_x1 = x + (radius * cos(angle * PI / 180));
        int tick_y1 = y + (radius * sin(angle * PI / 180));
        tft->fillSmoothCircle(tixk_x1, tick_y1, small_radius, colour_fill);
        angle += angle_increment;
    }
}

void InterfaceHelper::draw_system_information(TFT_eSprite* tft, int x, int y, std::string system_text, uint16_t colour_bg,
                                              uint16_t colour_border, bool selected, bool border){
    /*/ Get the width and height of the text to be displayed
    int16_t txt_width = tft->textWidth(system_text.c_str());
    int16_t txt_height = tft->fontHeight();

    // Calculate the dimensions of the bounding box
    int16_t rect_width = txt_width + 4;
    int16_t rect_height = txt_height + 4;

    // Calculate the Border
    int border_width = 0;
    int border_roundness = 2;

    // If the selected flag is set, darken the border color
    if (selected) {
        colour_border = InterfaceHelper::darken_colour(colour_border);
    }

    // If the border flag is set, draw the rectangle border
    if (border) {
        border_width = 2;
    }

    // Fill the rectangle with the background color
    tft->drawSmoothRoundRect(x, y, border_roundness, border_roundness-border_width, rect_width, rect_height, colour_bg);
    */
    // Calculate the x and y position of the text
    /*
    int16_t text_x = x + (rect_width - txt_width) / 2;
    int16_t text_y = y + (rect_height - txt_height) / 2;
    */

    // Draw the text
    //InterfaceHelper::set_freestyle_text(tft, system_text, text_x, text_y, TFT_WHITE, 0.08);
    //InterfaceHelper::set_defstyle_text(tft, system_text, x, y, TFT_WHITE, 0.08);
    InterfaceHelper::set_defstyle_text(tft, system_text, x, y, colour_bg, 2);
}

int InterfaceHelper::get_hour()
{
    ClockSync* cs = cs->get_instance();
    return (ClockSync::get_int_hours());
}

int InterfaceHelper::get_minutes(){
    ClockSync* cs = cs->get_instance();
    return (ClockSync::get_int_minutes());
}

int InterfaceHelper::get_seconds(){
    ClockSync* cs = cs->get_instance();
    return (ClockSync::get_int_seconds());
}

std::string InterfaceHelper::get_hour_string(){
    return (ClockSync::get_hours());
}

std::string InterfaceHelper::get_minutes_string(){
    return (ClockSync::get_minutes());
}

std::string InterfaceHelper::get_seconds_string(){
    return (ClockSync::get_seconds());
}

std::string InterfaceHelper::get_week_day_string(bool abbreviation){
    return ClockSync::get_day_of_week_string(abbreviation);
}

std::string InterfaceHelper::get_day_string(){
    return ClockSync::get_day();
}

std::string InterfaceHelper::get_month_string(bool abbreviation){
    return ClockSync::get_month_string(abbreviation);
}

std::string InterfaceHelper::get_num_month_string(){
    return ClockSync::get_month();
}

std::string InterfaceHelper::get_year_string(bool abbreviation){
    return ClockSync::get_year(abbreviation);
}

void InterfaceHelper::draw_weather_status(TFT_eSprite* tft, int x, int y, std::string weather_type){
    // Weather Conditions: Clear Sky, few clouds, scattered clouds, broken clouds, shower rain, rain, thunderstorm, snow, mist
    if (InterfaceHelper::string_compare(weather_type, "clear sky")) {
        InterfaceHelper::draw_clear_sky_01(tft, x-1, y-1, 2);

    }else if(InterfaceHelper::string_compare(weather_type, "few clouds")) {
        InterfaceHelper::draw_few_clouds_02(tft, x, y, 2);
        
    }else if(InterfaceHelper::string_compare(weather_type, "rain")) {
        InterfaceHelper::draw_rain_10(tft, x, y, 2);

    }else if(InterfaceHelper::string_compare(weather_type, "snow")) {
        InterfaceHelper::draw_snow_13(tft, x, y, 2);

    }else if(InterfaceHelper::string_compare(weather_type, "thunderstorm")){
        InterfaceHelper::draw_thunderstorm_11(tft, x, y, 2);

    }else if(InterfaceHelper::string_compare(weather_type, "mist")){
        InterfaceHelper::draw_mist_50(tft, x-10, y-10, 2);
    
    }else if(InterfaceHelper::string_compare(weather_type, "shower rain")){
        InterfaceHelper::draw_shower_rain_09(tft, x, y, 2);

    }else if(InterfaceHelper::string_compare(weather_type, "broken clouds")){
        InterfaceHelper::draw_broken_clouds_04(tft, x, y, 2);

    }else if(InterfaceHelper::string_compare(weather_type, "scattered clouds")){
        InterfaceHelper::draw_scattered_clouds_03(tft, x, y, 2);
    }else {
        InterfaceHelper::draw_no_connection(tft, x, y, 2);
    }
}

std::string InterfaceHelper::get_weather_string(WEATHER_CODE weather_code){
    std::string to_return = "";
    switch (weather_code){
        case 0: {
            to_return = "clear sky";
            break;
        }case 1: {
            to_return = "few clouds";
            break;
        }case 2: {
            to_return = "scattered clouds";
            break;
        }case 3: {
            to_return = "broken clouds";
            break;
        }case 4: {
            to_return = "shower rain";
            break;
        }case 5: {
            to_return = "rain";
            break;
        }case 6: {
            to_return = "thunderstorm";
            break;
        }case 7: {
            to_return = "snow";
            break;
        }case 8: {
            to_return = "mist";
            break;
        }default: {
            to_return = "N/A";
        }
    }

    return to_return;
}

uint16_t InterfaceHelper::get_green(TFT_eSprite* tft){
    return tft->color565(84, 230, 60);
}

uint16_t InterfaceHelper::get_grey(TFT_eSprite* tft){
    return tft->color565(128, 128, 128);
}

uint16_t InterfaceHelper::get_red(TFT_eSprite* tft){
    return tft->color565(227, 2, 47);
}

uint16_t InterfaceHelper::get_orange(TFT_eSprite* tft){
    return tft->color565(245, 113, 24);
}

uint16_t InterfaceHelper::get_pink(TFT_eSprite* tft){
    return tft->color565(230, 0, 221);
}

uint16_t InterfaceHelper::get_blue(TFT_eSprite* tft){
    return tft->color565(51, 203, 245);
}

uint16_t InterfaceHelper::get_purple(TFT_eSprite* tft){
    return tft->color565(143, 25, 227);
}

uint16_t InterfaceHelper::get_yellow(TFT_eSprite* tft)
{
    return tft->color565(227, 191, 14);
}

uint16_t InterfaceHelper::get_white(TFT_eSprite* tft){
    return tft->color565(255, 255, 255);
}

uint16_t InterfaceHelper::get_black(TFT_eSprite* tft){
    return tft->color565(0, 0, 0);
}

uint16_t InterfaceHelper::darken_colour(uint16_t colour, int percentage){
    int r = (colour & 0xF800) >> 11;
    int g = (colour & 0x07E0) >> 5;
    int b = (colour & 0x001F);

    r = (r * (100 - percentage)) / 100;
    g = (g * (100 - percentage)) / 100;
    b = (b * (100 - percentage)) / 100;

    return (r << 11) | (g << 5) | b;
}

uint16_t InterfaceHelper::lighten_colour(uint16_t colour, int percentage) {
    uint8_t r = (colour >> 11) & 0x1F;
    uint8_t g = (colour >> 5) & 0x3F;
    uint8_t b = colour & 0x1F;

    r += (0x1F - r) * percentage / 100;
    g += (0x3F - g) * percentage / 100;
    b += (0x1F - b) * percentage / 100;

    return (r << 11) | (g << 5) | b;
}




std::array<uint16_t, 5> InterfaceHelper::get_analagous_complementary_colours(uint16_t input_colour) {
    std::array<uint16_t, 5> analagous_complementary_colours;
    uint8_t r, g, b;
    r = (input_colour >> 11) & 0x1F;
    g = (input_colour >> 5) & 0x3F;
    b = input_colour & 0x1F;
    analagous_complementary_colours[0] = input_colour;
    analagous_complementary_colours[1] = ((r << 11) & (g << 5) & b) | (((r + 0x1F/6) % 0x1F) << 11) | (((g + 0x3F/6) % 0x3F) << 5) | (((b + 0x1F/6) % 0x1F));
    analagous_complementary_colours[2] = ((r << 11) & (g << 5) & b) | (((r - 0x1F/6) % 0x1F) << 11) | (((g - 0x3F/6) % 0x3F) << 5) | (((b - 0x1F/6) % 0x1F));
    analagous_complementary_colours[3] = ((r << 11) & (g << 5) & b) | (((r + 0x1F/6*2) % 0x1F) << 11) | (((g + 0x3F/6*2) % 0x3F) << 5) | (((b + 0x1F/6*2) % 0x1F));
    analagous_complementary_colours[4] = ((r << 11) & (g << 5) & b) | (((r - 0x1F/6*2) % 0x1F) << 11) | (((g - 0x3F/6*2) % 0x3F) << 5) | (((b - 0x1F/6*2) % 0x1F));
    return analagous_complementary_colours;
}

std::array<uint16_t, 5> InterfaceHelper::get_split_complementary_colours(uint16_t input_colour) {
    std::array<uint16_t, 5> split_complementary_colours;
    uint8_t r, g, b;
    r = (input_colour >> 11) & 0x1F;
    g = (input_colour >> 5) & 0x3F;
    b = input_colour & 0x1F;
    split_complementary_colours[0] = input_colour;
    split_complementary_colours[1] = ((r << 11) & (g << 5) & b) | (((r + 0x1F/3*2) % 0x1F) << 11) | (((g + 0x3F/3*2) % 0x3F) << 5) | (((b + 0x1F/3*2) % 0x1F));
    split_complementary_colours[2] = ((r << 11) & (g << 5) & b) | (((r + 0x1F/3*2 + 0x1F/6) % 0x1F) << 11) | (((g + 0x3F/3*2 + 0x3F/6) % 0x3F) << 5) | (((b + 0x1F/3*2 + 0x1F/6) % 0x1F));
    split_complementary_colours[3] = ((r << 11) & (g << 5) & b) | (((r + 0x1F/3*2 - 0x1F/6) % 0x1F) << 11) | (((g + 0x3F/3*2 - 0x3F/6) % 0x3F) << 5) | (((b + 0x1F/3*2 - 0x1F/6) % 0x1F));
    split_complementary_colours[4] = ((r << 11) & (g << 5) & b) | (((r + 0x1F/3) % 0x1F) << 11) | (((g + 0x3F/3) % 0x3F) << 5) | (((b + 0x1F/3) % 0x1F));
    return split_complementary_colours;
}

std::array<uint16_t, 5> InterfaceHelper::get_triadic_colours(uint16_t input_colour) {
    std::array<uint16_t, 5> triadic_colours;
    uint8_t r, g, b;
    r = (input_colour >> 11) & 0x1F;
    g = (input_colour >> 5) & 0x3F;
    b = input_colour & 0x1F;
    triadic_colours[0] = input_colour;
    triadic_colours[1] = ((r << 11) & (g << 5) & b) | (((r + 0x1F/3) % 0x1F) << 11) | (((g + 0x3F/3) % 0x3F) << 5) | (((b + 0x1F/3) % 0x1F));
    triadic_colours[2] = ((r << 11) & (g << 5) & b) | (((r + 0x1F/3*2) % 0x1F) << 11) | (((g + 0x3F/3*2) % 0x3F) << 5) | (((b + 0x1F/3*2) % 0x1F));
    triadic_colours[3] = ((r << 11) & (g << 5) & b) | (((r + 0x1F/5*3) % 0x1F) << 11) | (((g + 0x3F/5*3) % 0x3F) << 5) | (((b + 0x1F/5*3) % 0x1F));
    triadic_colours[4] = ((r << 11) & (g << 5) & b) | (((r + 0x1F/5*4) % 0x1F) << 11) | (((g + 0x3F/5*4) % 0x3F) << 5) | (((b + 0x1F/5*4) % 0x1F));
    return triadic_colours;
}

std::array<uint16_t, 5> InterfaceHelper::get_tetradic_colours(uint16_t input_colour) {
    std::array<uint16_t, 5> tetradic_colours;
    uint8_t r, g, b;
    r = (input_colour >> 11) & 0x1F;
    g = (input_colour >> 5) & 0x3F;
    b = input_colour & 0x1F;
    tetradic_colours[0] = input_colour;
    tetradic_colours[1] = ((r << 11) & (g << 5) & b) | (((r + 0x1F/4) % 0x1F) << 11) | (((g + 0x3F/4) % 0x3F) << 5) | (((b + 0x1F/4) % 0x1F));
    tetradic_colours[2] = ((r << 11) & (g << 5) & b) | (((r + 0x1F/4*2) % 0x1F) << 11) | (((g + 0x3F/4*2) % 0x3F) << 5) | (((b + 0x1F/4*2) % 0x1F));
    tetradic_colours[3] = ((r << 11) & (g << 5) & b) | (((r + 0x1F/4*3) % 0x1F) << 11) | (((g + 0x3F/4*3) % 0x3F) << 5) | (((b + 0x1F/4*3) % 0x1F));
    tetradic_colours[4] = ((r << 11) & (g << 5) & b) | (((r + 0x1F/4*4) % 0x1F) << 11) | (((g + 0x3F/4*4) % 0x3F) << 5) | (((b + 0x1F/4*4) % 0x1F));
    return tetradic_colours;
}

uint16_t InterfaceHelper::get_greyscale(uint16_t input_colour){
    int red = (input_colour >> 11) & 0x1F;
    int green = (input_colour >> 5) & 0x3F;
    int blue = input_colour & 0x1F;
    int average = (red + green + blue) / 3;
    return (average << 11) | (average << 5) | average;
}


bool InterfaceHelper::string_compare(std::string str_one, std::string str_two){
    // make both sentences lowercase
    str_one = to_lowercase(str_one);
    str_two = to_lowercase(str_two);

    bool to_return = false;

    if (str_one == str_two) {
        to_return = true;
    }

    return to_return;
}

std::string InterfaceHelper::to_lowercase(std::string input_string){
    std::string to_return = "";

    for (auto i = 0; i < input_string.length(); i++){
        to_return += std::tolower(input_string[i]);
    }

    return to_return;
}

void InterfaceHelper::set_freestyle_text(TFT_eSprite* tft, std::string text, int x, int y, uint16_t colour,
                                         float font_size){
    tft->setFreeFont(&Orbitron_Light_24);
    tft->setTextSize(font_size);
    tft->setTextColor(colour);
    tft->setCursor(x, y);
    tft->print(text.c_str());

    // Unload the font
    tft->setFreeFont(NULL);
}

void InterfaceHelper::set_defstyle_text(TFT_eSprite* tft, std::string text, int x, int y, uint16_t color, float font_size) {
    tft->setTextDatum(TC_DATUM);
    tft->setTextColor(color);
    tft->setTextFont(1);
    tft->setTextSize(font_size);
    tft->drawString(text.c_str(), x, y);

    // unload the font.
    tft->setTextFont(NULL);
}

void InterfaceHelper::draw_clear_sky_01(TFT_eSprite* tft, int x, int y, int scale){
    // Sun
    int radius = 10;
    int offset = 15;
    InterfaceHelper::draw_sized_circle(tft, x+offset, y+offset, radius, InterfaceHelper::get_orange(tft));
}

void InterfaceHelper::draw_few_clouds_02(TFT_eSprite* tft, int x, int y, int scale){
    // Sun
    int radius = 8;
    int offset = 15;
    InterfaceHelper::draw_sized_circle(tft, x+offset+offset*0.5, y+offset*0.7, radius, InterfaceHelper::get_orange(tft));

    // Cloud one
    InterfaceHelper::draw_cloud(tft, x-2, y+5, scale*0.5, InterfaceHelper::darken_colour(InterfaceHelper::get_grey(tft), 0));
    // Cloud two
    InterfaceHelper::draw_cloud(tft, x+4, y+8, scale*0.4, InterfaceHelper::lighten_colour(InterfaceHelper::get_grey(tft), 80));
}

void InterfaceHelper::draw_scattered_clouds_03(TFT_eSprite* tft, int x, int y, int scale){
    // Cloud one
    InterfaceHelper::draw_cloud(tft, x-3, y+6, scale*0.5, InterfaceHelper::lighten_colour(InterfaceHelper::get_white(tft), 40));
}

void InterfaceHelper::draw_broken_clouds_04(TFT_eSprite* tft, int x, int y, int scale){
    // Cloud one
    InterfaceHelper::draw_cloud(tft, x-2, y+5, scale*0.5, InterfaceHelper::darken_colour(InterfaceHelper::get_grey(tft), 0));
    // Cloud two
    InterfaceHelper::draw_cloud(tft, x+4, y+8, scale*0.4, InterfaceHelper::lighten_colour(InterfaceHelper::get_grey(tft), 80));
}

void InterfaceHelper::draw_shower_rain_09(TFT_eSprite* tft, int x, int y, int scale){
    // Individual Rain Strands
    InterfaceHelper::draw_rain(tft, x-2, y+2, scale, InterfaceHelper::get_white(tft));
}

void InterfaceHelper::draw_rain_10(TFT_eSprite* tft, int x, int y, int scale){
    // Rain
    InterfaceHelper::draw_rain(tft, x-4, y+6, scale* 0.4, InterfaceHelper::get_white(tft));

    // Cloud one
    InterfaceHelper::draw_cloud(tft, x-2, y+1, scale*0.5, InterfaceHelper::darken_colour(InterfaceHelper::get_grey(tft), 0));
    // Cloud two
    InterfaceHelper::draw_cloud(tft, x+4, y+4, scale*0.4, InterfaceHelper::lighten_colour(InterfaceHelper::get_grey(tft), 80));

}

void InterfaceHelper::draw_thunderstorm_11(TFT_eSprite* tft, int x, int y, int scale){
    // Cloud one
    InterfaceHelper::draw_rain_10(tft, x, y, scale);
    // thunderstrike
    InterfaceHelper::draw_thunder(tft, x, y-2, 5, InterfaceHelper::get_orange(tft));
}

void InterfaceHelper::draw_snow_13(TFT_eSprite* tft, int x, int y, int scale){
    draw_snowflake(tft, x+2, y+2, 4, TFT_WHITE);
    draw_snowflake(tft, x+10, y+11, 4, TFT_WHITE);
    draw_snowflake(tft, x-3, y+16, 4, TFT_WHITE);
}

void InterfaceHelper::draw_mist_50(TFT_eSprite* tft, int x, int y, int scale){
    x += 10; y += 8;
    int length = 12*scale;
    int width = 1*scale;
    float r = 1.6*scale;
    float line1 = 0.7, line2 = 0.5, line3 = 0.96, line4 = 0.89, line5 = 0.4;

    /*
    // First Line
    tft->drawRoundRect(x+8, y+6, x+(length*line1), y+width, r, InterfaceHelper::get_white(tft));

    // Second Series
    tft->drawRoundRect(x+2, y+12, x+(length*line2), y+width, r, InterfaceHelper::get_white(tft));
    tft->drawRoundRect(x+16, y+12, x+(length*line5), y+width, r, InterfaceHelper::get_white(tft));

    // Third
    tft->drawRoundRect(x+3, y+18, x+(length*line3), y+width, r, InterfaceHelper::get_white(tft));

    // Fourth
    tft->drawRoundRect(x+4, y+24, x+(length*line1*0.68), y+width, r, InterfaceHelper::get_white(tft));

    // Fifth
    tft->drawRoundRect(x+18, y+28, x+(length*line5*0.8), y+width, r, InterfaceHelper::get_white(tft));
     */
   // First Line
    tft->drawWideLine(x+8, y+6, x+(length*line1), y+6, r, InterfaceHelper::get_white(tft));

    // Second Series
    tft->drawWideLine(x+2, y+12, x+(length*line2), y+12, r, InterfaceHelper::get_white(tft));
    tft->drawWideLine(x+16, y+12, x+16+(length*line5), y+12, r, InterfaceHelper::get_white(tft));

    // Third
    tft->drawWideLine(x+3, y+18, x+(length*line3), y+18, r, InterfaceHelper::get_white(tft));

    // Fourth
    tft->drawWideLine(x+14, y+24, x+14+(length*line1*0.68), y+24, r, InterfaceHelper::get_white(tft));

    // Fifth
    tft->drawWideLine(x+18, y+28, x+(length*line5*0.8), y+28, r, InterfaceHelper::get_white(tft));
    
}

void InterfaceHelper::draw_snowflake(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour) {
    int x_base_offset = 5;
    int y_base_offset = 5;
    int offset_x = (10 - scale) / 2;
    int offset_y = (10 - scale) / 2;
    int line_length = 3*scale;
    int line_width = 0.5 * scale;

    x += x_base_offset;
    y += y_base_offset;

    InterfaceHelper::draw_wide_angled_line(tft, x, y, line_length, 0, 2, colour);
    InterfaceHelper::draw_wide_angled_line(tft, x+(line_length/2)-4, y-(6), line_length, 45, line_width, colour);
    InterfaceHelper::draw_wide_angled_line(tft, x+(line_length/2)-4, y+(6), line_length, -45, line_width, colour);
}

void InterfaceHelper::draw_no_connection(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour){
    // Draw a Cloud and a Red Line Across it.
    InterfaceHelper::draw_cloud(tft, x-3, y+6, scale*0.5, InterfaceHelper::lighten_colour(InterfaceHelper::get_white(tft), 40));
    tft->drawWideLine(x+3, y+3, x+24, y+24, 2, colour);
}

void InterfaceHelper::draw_battery_level(TFT_eSprite* tft, int x, int y, float progress, uint16_t colour, 
                                        uint16_t bg_colour, bool volatile_colours){
    int width = 18;
    int height = 10;
    int radius = 2;
    int padding = 2;
    int battery_width = ((width - 2 * padding) * progress) / 100;//(width * progress) / 100;
    int progress_int = static_cast<int>(progress);
    auto battery_border_colour = colour;
    auto battery_fill_colour = colour;
    auto battery_bg_colour = bg_colour;

    if(volatile_colours) {
        switch(progress_int){
            case 0 ... 20 : {
                battery_fill_colour = InterfaceHelper::get_red(tft);
                break;
            }case 21 ... 40 : {
                battery_fill_colour = InterfaceHelper::get_orange(tft);
                break;
            }case 41 ... 60 : {
                battery_fill_colour = InterfaceHelper::get_yellow(tft);
                break;
            }case 61 ... 80 :{
                battery_fill_colour = InterfaceHelper::lighten_colour(InterfaceHelper::get_green(tft), 40);
                break;
            }case 81 ... 100 :{
                battery_fill_colour = InterfaceHelper::get_green(tft);
                break;
            }
            default: {
                battery_fill_colour = InterfaceHelper::get_white(tft);
            }
        }
    }

    tft->fillRoundRect(x, y, width, height, 2, battery_bg_colour);
    tft->fillRoundRect(x + padding, y + padding, battery_width, height - 2 * padding, 2, colour);
    tft->drawRoundRect(x, y, width, height, 2, battery_border_colour);
    tft->drawLine(x + width, y + height / 2, x + width + 2, y + height / 2, battery_border_colour);
}

void InterfaceHelper::draw_battery_line(TFT_eSprite* tft, int x, int y, int line_width, float progress)
{
    uint16_t colour_fill = InterfaceHelper::get_green(tft);
    int line_size = 2;
    int progress_int = static_cast<int>(progress);
    switch(progress_int){
        case 0 ... 20 : {
            colour_fill = InterfaceHelper::get_red(tft);
            break;
        }case 21 ... 40 : {
            colour_fill = InterfaceHelper::get_orange(tft);
            break;
        }case 41 ... 60 : {
            colour_fill = InterfaceHelper::get_yellow(tft);
            break;
        }case 61 ... 80 :{
            colour_fill = InterfaceHelper::lighten_colour(InterfaceHelper::get_green(tft), 40);
            break;
        }case 81 ... 100 :{
            colour_fill = InterfaceHelper::get_green(tft);
            break;
        }
        default: {
            colour_fill = InterfaceHelper::get_white(tft);
        }
    }

    tft->drawWideLine(x, y, x+line_width, y, line_size, colour_fill);
}

void InterfaceHelper::draw_circular_progress_bar(TFT_eSprite* tft, int x, int y, int radius, int bar_width,
                                                 int percentage, uint16_t colour_fill, uint16_t colour_empty,
                                                 uint16_t colour_bg)
{
    // Calculate the angles for the start and end of the arc
    float start_angle = 0; // Start at 12 o'clock position
    float end_angle = (start_angle + (percentage / 100.0) * 360);

    //Draw Empty Bar
    tft->drawSmoothArc(x, y, radius, radius-bar_width, 0, 360, (colour_empty), colour_bg, true);
    //Draw Filled Bar
    tft->drawSmoothArc(x, y, radius, radius-bar_width, start_angle, end_angle, (colour_fill), colour_bg, true);
}

void InterfaceHelper::draw_vertical_progress_bar(TFT_eSprite* tft, int x, int y, int length, int width, int percentage, uint16_t colour_fill, uint16_t colour_empty){
    // Calculate the width of the filled portion of the bar
    int filled_width = (percentage * length) / 100;
    // Draw the empty portion of the bar
    tft->fillSmoothRoundRect(x, y, width, length, 2, colour_empty);
    // Draw the filled portion of the bar on top of the empty portion
    tft->fillSmoothRoundRect(x, y, width, filled_width, 2, colour_fill);
}

float InterfaceHelper::convert_to_angle(int value, int max_value) {
    return (value / (max_value*1.0)) * 360.0;
}

void InterfaceHelper::draw_clock_hand(TFT_eSprite *tft, int centre_x, int centre_y, int line_length, int line_inner_length, int angle, uint16_t colour) {
    /*// Convert angle from degrees to radians
    double radians = angle * (M_PI / 180);

    // Calculate the x and y coordinates of the end of the line
    int x_end = center_x + (cos(radians) * line_inner_length);
    int y_end = center_y + (sin(radians) * line_inner_length);

    // Draw the line
    tft->drawLine(center_x, center_y, x_end, y_end, colour);*/
    auto radians = (angle * M_PI)/180.0;

    // Positions
    int x1 = centre_x + (line_inner_length+line_length) * cos(radians);
    int y1 = centre_y + (line_inner_length+line_length) * sin(radians);
    int x2 = centre_x + line_length * cos(radians);
    int y2 = centre_y + line_length * sin(radians);
    tft->drawLine(x1, y1, x2, y2, colour);
}

void InterfaceHelper::draw_clock_hand_wide(TFT_eSprite *tft, int centre_x, int centre_y, int line_length,
                                           int line_inner_length, int angle, int line_width, uint16_t colour){
    auto radians = (angle * M_PI)/180.0;

    // Positions
    int x1 = centre_x + (line_inner_length+line_length) * cos(radians);
    int y1 = centre_y + (line_inner_length+line_length) * sin(radians);
    int x2 = centre_x + line_length * cos(radians);
    int y2 = centre_y + line_length * sin(radians);
    tft->drawWideLine(x1, y1, x2, y2, line_width, colour);
}

void InterfaceHelper::draw_progress_bar(TFT_eSprite* tft, int x, int y, int length, int width, int percentage, uint16_t colour_fill, uint16_t colour_empty){
    // Calculate the width of the filled portion of the bar
    int filled_width = (percentage * length) / 100;
    // Draw the empty portion of the bar
    tft->fillSmoothRoundRect(x, y, length, width, 2, colour_empty);
    // Draw the filled portion of the bar on top of the empty portion
    tft->fillSmoothRoundRect(x, y, filled_width, width, 2, colour_fill);
}

void InterfaceHelper::draw_angled_line(TFT_eSprite* tft, int x, int y, int length, int angle, uint16_t colour){
    int x2 = x + (length * cos(angle));
    int y2 = y + (length * sin(angle));
    tft->drawLine(x, y, x2, y2, colour);
}

void InterfaceHelper::draw_wide_angled_line(TFT_eSprite* tft, int x, int y, int length, int angle, float size, uint16_t colour){
    int x2 = x + (length * cos(angle));
    int y2 = y + (length * sin(angle));
    tft->drawWideLine(x, y, x2, y2, size, colour);
}

void InterfaceHelper::draw_sized_circle(TFT_eSprite* tft, int x, int y, int size, uint16_t colour){
    tft->fillSmoothCircle(x, y, size, colour);
}

void InterfaceHelper::draw_cloud(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour){
    int offset_correction = 7;
    int radius1 = scale * 4;
    int radius2 = scale * 6;
    int radius3 = scale * 6;
    int radius4 = scale * 8;
    int offset = scale * 7;
    int yoffset = scale * 2;

    InterfaceHelper::draw_sized_circle(tft, x+offset_correction, y+offset_correction+yoffset, radius1, colour);
    InterfaceHelper::draw_sized_circle(tft, x+offset_correction + offset, y+offset_correction, radius4, colour);
    InterfaceHelper::draw_sized_circle(tft, x+offset_correction + offset * 2, y+offset_correction, radius3, colour);
    InterfaceHelper::draw_sized_circle(tft, x+offset_correction + offset * 3, y+offset_correction+yoffset, radius1, colour);
}

void InterfaceHelper::draw_rain(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour){
    int offset_correction = 6;
    int offset = 8;
    int length = 6;
    int angle = -45;
    float line_width = 1.8;
    InterfaceHelper::draw_wide_angled_line(tft, x+offset_correction, y+offset_correction, length, angle, line_width, InterfaceHelper::get_white(tft));
    InterfaceHelper::draw_wide_angled_line(tft, x+offset_correction+offset, y+offset_correction, length, angle, line_width,  InterfaceHelper::get_white(tft));
    InterfaceHelper::draw_wide_angled_line(tft, x+offset_correction, y+offset+offset_correction, length, angle, line_width,  InterfaceHelper::get_white(tft));
    InterfaceHelper::draw_wide_angled_line(tft, x+offset_correction+offset, y+offset_correction+offset, length, angle, line_width,  InterfaceHelper::get_white(tft));

    InterfaceHelper::draw_wide_angled_line(tft, x+offset_correction+offset_correction+offset+offset, y+offset_correction+offset, length, angle, line_width,  InterfaceHelper::get_white(tft));
    InterfaceHelper::draw_wide_angled_line(tft, x+offset_correction+offset+offset, y+offset_correction+offset, length, angle, line_width,  InterfaceHelper::get_white(tft));
    InterfaceHelper::draw_wide_angled_line(tft, x+offset_correction+offset, y+offset_correction+offset+offset, length, angle, line_width,  InterfaceHelper::get_white(tft));
    InterfaceHelper::draw_wide_angled_line(tft, x+offset_correction+offset+offset, y+offset_correction+offset+offset, length, angle, line_width,  InterfaceHelper::get_white(tft));

}

void InterfaceHelper::draw_thunder(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour){
    int size = scale;
    float angle = 45;
    angle = angle * (3.14/180);
    int offsetx = 14;
    int offsety = 22;
    float line_width = 1.8;
    tft->drawWideLine(x+offsetx, y+offsety, x+offsetx - (size * cos(angle)), y+offsety + (size * sin(angle)), line_width, InterfaceHelper::darken_colour(InterfaceHelper::get_orange(tft), 1));
    angle += 90;
    tft->drawWideLine(x+offsetx - (size * cos(angle)), y+offsetx + (size * sin(angle)), x+offsetx - (size * cos(angle + 45)), y+offsety + (size * sin(angle + 45)), line_width,  InterfaceHelper::darken_colour(InterfaceHelper::get_orange(tft), 1));
    angle += 45;
    tft->drawWideLine(x+offsetx - (size * cos(angle)), y+offsetx + (size * sin(angle)), x+offsetx, y+offsety, line_width,  InterfaceHelper::darken_colour(InterfaceHelper::get_orange(tft), 1));
}

void InterfaceHelper::draw_stylised_clock_hands(TFT_eSprite* tft, int centre_x, int centre_y,
                                                int hour, int minute, int second, uint16_t base_colour,
                                                bool volatile_colours){
    // Get the angles
    int hour_angle = InterfaceHelper::convert_to_angle(hour, 12);
    int minute_angle = InterfaceHelper::convert_to_angle(minute, 60);
    int second_angle = InterfaceHelper::convert_to_angle(second, 60);
    // Flip the angles
    int offset = 90;
    hour_angle -= offset;
    minute_angle -= offset;
    second_angle -= offset;
    // Set the colour
    auto hour_colour = base_colour;
    auto minute_colour = base_colour;
    auto second_colour = base_colour;
    auto extra_colour = base_colour;

    if (volatile_colours){
        minute_colour = InterfaceHelper::get_split_complementary_colours(base_colour).at(1);
        second_colour = InterfaceHelper::get_split_complementary_colours(base_colour).at(2);
        extra_colour = InterfaceHelper::get_split_complementary_colours(base_colour).at(3);
    }

    // Draw the thin arms
    InterfaceHelper::draw_clock_hand(tft, centre_x, centre_y, 0, SCREEN_WIDTH_CENTRE*0.5, hour_angle, hour_colour);
    InterfaceHelper::draw_clock_hand(tft, centre_x, centre_y, 0, SCREEN_WIDTH_CENTRE*0.7, minute_angle, minute_colour);
    InterfaceHelper::draw_clock_hand(tft, centre_x, centre_y, 0, SCREEN_WIDTH_CENTRE*0.6, second_angle, second_colour);

    // Draw the thick arms
    InterfaceHelper::draw_clock_hand_wide(tft, centre_x, centre_y, SCREEN_WIDTH_CENTRE*0.2, SCREEN_WIDTH_CENTRE*0.4, hour_angle, 6, hour_colour);
    InterfaceHelper::draw_clock_hand_wide(tft, centre_x, centre_y, SCREEN_WIDTH_CENTRE*0.2, SCREEN_WIDTH_CENTRE*0.6, minute_angle, 4, minute_colour);
    InterfaceHelper::draw_clock_hand_wide(tft, centre_x, centre_y, SCREEN_WIDTH_CENTRE*0.2, SCREEN_WIDTH_CENTRE*0.5, second_angle, 2, second_colour);

    // Draw a small circle in the middle
    tft->fillCircle(centre_x, centre_y, 4, extra_colour);
}

void InterfaceHelper::draw_clock_hands(TFT_eSprite* tft, int centre_x, int centre_y, int hour, int minute, int second,
                                       uint16_t base_colour, bool volatile_colours){
    // Get the angles
    int hour_angle = InterfaceHelper::convert_to_angle(hour, 12);
    int minute_angle = InterfaceHelper::convert_to_angle(minute, 60);
    int second_angle = InterfaceHelper::convert_to_angle(second, 60);
    // Flip the angles
    int offset = 90;
    hour_angle -= offset;
    minute_angle -= offset;
    second_angle -= offset;
    // Set the colour
    auto hour_colour = base_colour;
    auto minute_colour = base_colour;
    auto second_colour = base_colour;
    auto extra_colour = base_colour;

    if (volatile_colours){
        minute_colour = InterfaceHelper::get_split_complementary_colours(base_colour).at(1);
        second_colour = InterfaceHelper::get_split_complementary_colours(base_colour).at(2);
        extra_colour = InterfaceHelper::get_split_complementary_colours(base_colour).at(3);
    }

    // Draw the thin arms
    InterfaceHelper::draw_clock_hand(tft, centre_x, centre_y, 0, SCREEN_WIDTH_CENTRE*0.4, hour_angle, hour_colour);
    InterfaceHelper::draw_clock_hand(tft, centre_x, centre_y, 0, SCREEN_WIDTH_CENTRE*0.8, minute_angle, minute_colour);
    InterfaceHelper::draw_clock_hand(tft, centre_x, centre_y, 0, SCREEN_WIDTH_CENTRE*0.6, second_angle, second_colour);

    // Draw a small circle in the middle
    tft->fillCircle(centre_x, centre_y, 4, extra_colour);
}

void InterfaceHelper::draw_steps_text(TFT_eSprite* tft, int x, int y, int steps, uint16_t colour_fill){
    std::string steps_string = std::to_string(steps);
    std::string output = "Total Steps Output: "+steps_string;
    CruxOSLog::Logging(__FUNCTION__, output);
    set_defstyle_text(tft, steps_string.c_str(), x, y, colour_fill, 2); 

}

void InterfaceHelper::draw_hours_text(TFT_eSprite* tft, int x, int y, uint16_t colour_fill){
    // Simply draw the text as required
    set_defstyle_text(tft, InterfaceHelper::get_hour_string(), x, y, colour_fill, 14);
}

void InterfaceHelper::draw_minutes_text(TFT_eSprite* tft, int x, int y, uint16_t colour_fill){
    // Simply draw the text as required
    set_defstyle_text(tft, InterfaceHelper::get_minutes_string(), x, y, colour_fill, 14);
}

void InterfaceHelper::draw_seconds_text(TFT_eSprite* tft, int x, int y, uint16_t colour_fill){
    set_defstyle_text(tft, InterfaceHelper::get_seconds_string(), x, y, colour_fill, 14);
}

void InterfaceHelper::draw_weekday_text(TFT_eSprite* tft, int x, int y, uint16_t colour_fill, bool abbreviation){
    set_defstyle_text(tft, InterfaceHelper::get_week_day_string(abbreviation), x, y, colour_fill, 2);
}

void InterfaceHelper::draw_day_text(TFT_eSprite* tft, int x, int y, uint16_t colour_fill){
    set_defstyle_text(tft, InterfaceHelper::get_day_string(), x, y, colour_fill, 14);
}

void InterfaceHelper::draw_month_text(TFT_eSprite* tft, int x, int y, uint16_t colour_fill, bool abbreviation){
    set_defstyle_text(tft, InterfaceHelper::get_month_string(abbreviation), x, y, colour_fill, 14);
}

void InterfaceHelper::draw_calories_text(TFT_eSprite* tft, int x, int y, int calories, uint16_t colour_fill){
    set_defstyle_text(tft, std::to_string(calories).c_str(), x, y, colour_fill, 14);
}

void InterfaceHelper::draw_location_text(TFT_eSprite* tft, int x, int y, std::string location_text,
                                         uint16_t colour_fill){
    set_defstyle_text(tft, location_text.c_str(), x, y, colour_fill, 14);
}

void InterfaceHelper::draw_weather_text(TFT_eSprite* tft, int x, int y, std::string weather_text, uint16_t colour_fill){
    set_defstyle_text(tft, weather_text, x, y, colour_fill, 14);
}
