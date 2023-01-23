/**
 * \author Benrick Smit
 * \date Updated 2023/01/10
 * \brief The Display Manager Class takes care of the viewing of different faces for the CruxOS
 * 
*/

#ifndef InterfaceHelper_H
#define InterfaceHelper_H

#include <Arduino_GFX.h>
#include <Arduino_GFX_Library.h>
#include <TFT_eSPI.h>

//#include <Fonts/FreeSans12pt7b.h>

#include <string>
#include <cstring>
#include <array>

#include <cruxos_constants.h>
#include <ClockSync.h>
#include <CruxOSLog.h>

class InterfaceHelper{
public:
    InterfaceHelper();
    ~InterfaceHelper();

    // Widget Functions
    static void draw_line_clock_ticks(TFT_eSPI &tft, int x, int y, int radius, uint16_t colour_fill);
    static void draw_circle_clock_ticks(TFT_eSprite* tft, int x, int y, int radius, int steps, uint16_t fill_color, uint16_t empty_color);
    static void draw_battery_level(TFT_eSPI &tft, int x, int y, float progress, uint16_t color, bool volatile_colours = true);
    static void draw_battery_line(TFT_eSPI &tft, int x, int y, float progress);
    static void draw_circular_progress_bar(TFT_eSprite* tft, int x, int y, int radius, int bar_width, int percentage, uint16_t colour_fill, uint16_t colour_empty, uint16_t colour_bg);
    static void draw_progress_bar(TFT_eSprite* tft, int x, int y, int length, int width, int percentage, uint16_t colour_fill, uint16_t colour_empty);
    static void draw_vertical_progress_bar(TFT_eSprite* tft, int x, int y, int length, int width, int percentage, uint16_t colour_fill, uint16_t colour_empty);
    static void draw_clock_arms(TFT_eSPI &tft, int center_x, int center_y, int length, int width, int hour, int minute, int second, uint16_t base_color, bool volatile_colours = false);
    static void draw_steps_text();
    static void draw_hours_text();
    static void draw_minutes_text();
    static void draw_day_text();
    static void draw_month_text();
    static void draw_calories_text();
    static void draw_location_text();
    static void draw_weather_text();
    static void draw_weather_icon();

    static void set_global_font();

    static int get_hour();
    static int get_minutes();
    static int get_seconds();
    static std::string get_hour_string();
    static std::string get_minutes_string();
    static std::string get_seconds_string();

    static void draw_weather_status(TFT_eSprite* tft, int x, int y, std::string weather_type);
    static std::string get_weather_string(WEATHER_CODE weather_code);

    // Colour Functions
    static uint16_t get_green(TFT_eSprite* tft);
    static uint16_t get_orange(TFT_eSprite* tft);
    static uint16_t get_grey(TFT_eSprite* tft);
    static uint16_t get_red(TFT_eSprite* tft);
    static uint16_t get_blue(TFT_eSprite* tft);
    static uint16_t get_white(TFT_eSprite* tft);
    static uint16_t get_black(TFT_eSprite* tft);
    static uint16_t lighten_colour(uint16_t colour, int percentage = 20);
    static uint16_t darken_colour(uint16_t colour, int percentage = 20);

    static std::array<uint16_t, 5> get_analagous_complementary_colours(uint16_t input_colour);
    static std::array<uint16_t, 5> get_split_complementary_colours(uint16_t input_colour);
    static std::array<uint16_t, 5> get_triadic_colours(uint16_t input_colour);
    static std::array<uint16_t, 5> get_tetradic_colours(uint16_t input_colour);
    static uint16_t get_greyscale(uint16_t input_colour);

    static void draw_circle_clock_ticks(TFT_eSprite *tft, int x, int y, int radius, uint16_t colour_fill);
    static void draw_angled_line(TFT_eSprite *tft, int x, int y, int length, int angle, uint16_t colour);
    static void draw_sized_circle(TFT_eSprite* tft, int x, int y, int scale, uint16_t colour);
    static void draw_cloud(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour);
    static void draw_rain(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour);
    static void draw_thunder(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour);

protected:
  static bool string_compare(std::string str_one, std::string str_two);
  static std::string to_lowercase(std::string input_string);

  static void draw_clear_sky_01(TFT_eSprite* tft, int x, int y, int scale = 1);
  static void draw_few_clouds_02(TFT_eSprite* tft, int x, int y, int scale = 1);
  static void draw_scattered_clouds_03(TFT_eSprite* tft, int x, int y, int scale = 1);
  static void draw_broken_clouds_04(TFT_eSprite* tft, int x, int y, int scale = 1);
  static void draw_shower_rain_09(TFT_eSprite* tft, int x, int y, int scale = 1);
  static void draw_rain_10(TFT_eSprite* tft, int x, int y, int scale = 1);
  static void draw_thunderstorm_11(TFT_eSprite* tft, int x, int y, int scale = 1);
  static void draw_snow_13(TFT_eSprite* tft, int x, int y, int scale = 1);
  static void draw_mist_50(TFT_eSprite* tft, int x, int y, int scale = 1);
  static void draw_snowflake(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour);


private:

};

#endif


