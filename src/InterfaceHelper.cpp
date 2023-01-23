#include "InterfaceHelper.h"

InterfaceHelper::InterfaceHelper(){
    ClockSync* cs = cs->get_instance();
}

InterfaceHelper::~InterfaceHelper(){
    // Do nothing for now
}

void InterfaceHelper::draw_circle_clock_ticks(TFT_eSprite* tft, int x, int y, int radius, int steps, uint16_t fill_color, uint16_t empty_color) {
    // Calculate the angle between each step
    float angle = 360.0 / steps;

    /*for (int i = 0; i < steps; i++) {
        // Calculate the x and y positions for the start and end of the arc
        int start_x = x + (radius * cos(degToRad(angle * i)));
        int start_y = y + (radius * sin(degToRad(angle * i)));
        int end_x = x + (radius * cos(degToRad(angle * (i + 1))));
        int end_y = y + (radius * sin(degToRad(angle * (i + 1))));

        // Draw the arc with the fill color
        tft->drawArc(start_x, start_y, end_x, end_y, x, y, radius, fill_color);

        // Draw the arc with the empty color (to create a ring effect)
        tft->drawArc(start_x, start_y, end_x, end_y, x, y, radius - 2, empty_color);
    }*/
}

int InterfaceHelper::get_hour(){
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
    return std::to_string(get_hour());
}

std::string InterfaceHelper::get_minutes_string(){
    return std::to_string(get_minutes());
}

std::string InterfaceHelper::get_seconds_string(){
    return std::to_string(get_seconds());
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
            to_return = "rain";
        }
    }

    return to_return;
}

uint16_t InterfaceHelper::get_green(TFT_eSprite* tft){
    return tft->color565(32, 181, 27);
}

uint16_t InterfaceHelper::get_grey(TFT_eSprite* tft){
    return tft->color565(128, 128, 128);
}

uint16_t InterfaceHelper::get_orange(TFT_eSprite* tft){
    return tft->color565(235, 110, 75);
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
    //tft->fillRoundRect(x+4, y+8, 12, 6, 2, InterfaceHelper::darken_colour(InterfaceHelper::get_grey(tft)));
    //tft->fillRoundRect(x+8, y+4, 4, 6, 2, InterfaceHelper::darken_colour(InterfaceHelper::get_grey(tft)));
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
    InterfaceHelper::draw_cloud(tft, x-2, y+3, scale*0.5, InterfaceHelper::darken_colour(InterfaceHelper::get_grey(tft), 0));
    // Cloud two
    InterfaceHelper::draw_cloud(tft, x+4, y+6, scale*0.4, InterfaceHelper::lighten_colour(InterfaceHelper::get_grey(tft), 80));

}

void InterfaceHelper::draw_thunderstorm_11(TFT_eSprite* tft, int x, int y, int scale){
    // Cloud one
    InterfaceHelper::draw_rain_10(tft, x, y, scale);
    // thunderstrike
    InterfaceHelper::draw_thunder(tft, x, y, 5, InterfaceHelper::get_orange(tft));
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
    int r = 2;
    float line1 = 0.7, line2 = 0.5, line3 = 0.96, line4 = 0.89, line5 = 0.4;


    // First Line
    tft->fillRoundRect(x+8, y+6, length*line1, width, r, InterfaceHelper::get_white(tft));

    // Second Series
    tft->fillRoundRect(x+2, y+12, length*line2, width, r, InterfaceHelper::get_white(tft));
    tft->fillRoundRect(x+16, y+12, length*line5, width, r, InterfaceHelper::get_white(tft));

    // Third
    tft->fillRoundRect(x+3, y+18, length*line3, width, r, InterfaceHelper::get_white(tft));

    // Fourth
    tft->fillRoundRect(x+4, y+24, length*line1*0.8, width, r, InterfaceHelper::get_white(tft));

    // Fifth
    tft->fillRoundRect(x+18, y+28, length*line5*0.8, width, r, InterfaceHelper::get_white(tft));
}

void InterfaceHelper::draw_snowflake(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour) {
    int x_base_offset = 5;
    int y_base_offset = 5;
    int offset_x = (10 - scale) / 2;
    int offset_y = (10 - scale) / 2;
    int line_length = 3*scale;

    x += x_base_offset;
    y += y_base_offset;

    InterfaceHelper::draw_angled_line(tft, x, y, line_length, 0, colour);
    InterfaceHelper::draw_angled_line(tft, x+(line_length/2)-4, y-(6), line_length, 45, colour);
    InterfaceHelper::draw_angled_line(tft, x+(line_length/2)-4, y+(6), line_length, -45, colour);
}




//template <typename TFT>
void InterfaceHelper::draw_circular_progress_bar(TFT_eSprite* tft, int x, int y, int radius, int bar_width, int percentage,
                                                 uint16_t colour_fill, uint16_t colour_empty, uint16_t colour_bg){
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
    InterfaceHelper::draw_angled_line(tft, x+offset_correction, y+offset_correction, length, angle, InterfaceHelper::get_white(tft));
    InterfaceHelper::draw_angled_line(tft, x+offset_correction+offset, y+offset_correction, length, angle, InterfaceHelper::get_white(tft));
    InterfaceHelper::draw_angled_line(tft, x+offset_correction, y+offset+offset_correction, length, angle, InterfaceHelper::get_white(tft));
    InterfaceHelper::draw_angled_line(tft, x+offset_correction+offset, y+offset_correction+offset, length, angle, InterfaceHelper::get_white(tft));

    InterfaceHelper::draw_angled_line(tft, x+offset_correction+offset_correction+offset+offset, y+offset_correction+offset, length, angle, InterfaceHelper::get_white(tft));
    InterfaceHelper::draw_angled_line(tft, x+offset_correction+offset+offset, y+offset_correction+offset, length, angle, InterfaceHelper::get_white(tft));
    InterfaceHelper::draw_angled_line(tft, x+offset_correction+offset, y+offset_correction+offset+offset, length, angle, InterfaceHelper::get_white(tft));
    InterfaceHelper::draw_angled_line(tft, x+offset_correction+offset+offset, y+offset_correction+offset+offset, length, angle, InterfaceHelper::get_white(tft));

}

void InterfaceHelper::draw_thunder(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour){
    int size = scale;
    float angle = 45;
    angle = angle * (3.14/180);
    int offsetx = 14;
    int offsety = 22;
    tft->drawLine(x+offsetx, y+offsety, x+offsetx - (size * cos(angle)), y+offsety + (size * sin(angle)), ORANGE);
    angle += 90;
    tft->drawLine(x+offsetx - (size * cos(angle)), y+offsetx + (size * sin(angle)), x+offsetx - (size * cos(angle + 45)), y+offsety + (size * sin(angle + 45)), ORANGE);
    angle += 45;
    tft->drawLine(x+offsetx - (size * cos(angle)), y+offsetx + (size * sin(angle)), x+offsetx, y+offsety, ORANGE);
}
