/**
 * \author Benrick Smit
 * \date Updated 2023/01/10
 * \brief The Display Manager Class takes care of the viewing of different faces for the CruxOS
 * 
*/

#ifndef InterfaceHelper_H
#define InterfaceHelper_H

//#include <Arduino_GFX.h>
//#include <Arduino_GFX_Library.h>
#include <TFT_eSPI.h>

//#include <Fonts/FreeSans12pt7b.h>
//#include <font/glcdfont.h>
//#include <Fonts/Custom/Orbitron_Light_24.h>

#include <string>
#include <cstring>
#include <array>

#include <cruxos_constants.h>
#include <ClockSync.h>
#include <CruxOSLog.h>

class InterfaceHelper{
public:
    /// @brief The default ctor
    InterfaceHelper();
    /// @brief The default dtor
    ~InterfaceHelper();

    // Widget Helper functions
    
    /// @brief This function draws thin lines on the screen representing the ticks on a normal clock face
    /// @param tft The TFT_eSprite to draw to
    /// @param x The centre x position
    /// @param y The centre y position
    /// @param radius The radius of the circle to be used
    /// @param steps How many ticks should be drawn
    /// @param line_length how long the ticks should be
    /// @param colour_fill The colour of the ticks
    static void draw_line_clock_ticks(TFT_eSprite* tft, int x, int y, int radius, int steps, int line_length, uint16_t colour_fill);
    /// @brief This function draws thick lines on the screen representing the ticks on a normal clock face 
    /// @param tft The TFT_eSprite to draw to
    /// @param x The centre x position
    /// @param y The centre y position
    /// @param radius The radius of the circle to be used
    /// @param steps How many ticks should be drawn
    /// @param line_width How wide the drawn lines should be
    /// @param line_length how long the ticks should be 
    /// @param colour_fill The colour of the ticks 
    static void draw_wide_line_clock_ticks(TFT_eSprite* tft, int x, int y, int radius, int steps, int line_width, int line_length, uint16_t colour_fill);
    /// @brief This function draws thick lines on the screen representing the ticks on a normal clock face 
    /// @param tft The TFT_eSprite to draw to
    /// @param x The centre x position
    /// @param y The centre y position
    /// @param radius The radius of the circle to be used
    /// @param steps How many ticks should be drawn
    /// @param colour_fill The colour of the ticks 
    static void draw_circle_clock_ticks(TFT_eSprite* tft, int x, int y, int radius, int steps, uint16_t colour_fill);
    /// @brief This function will draw a small rectangle that represents the battery power
    /// @param tft The TFT_eSprite to draw to
    /// @param x The starting x coordinate
    /// @param y The starting y coordinate
    /// @param progress The battery level out of 100%
    /// @param colour The border colour and possibly fill colour of the battery
    /// @param colour_bg The fill colour inside of the battery
    /// @param volatile_colours Change the colours based on battery level
    static void draw_battery_level(TFT_eSprite* tft, int x, int y, float progress, uint16_t colour, uint16_t colour_bg, bool volatile_colours = true);
    /// @brief This function draws a line that will indicate in colour the battery level. In descending order: Green, Light Green, Yellow, Orange, Red
    /// @param tft The TFT_eSprite to draw to
    /// @param x The starting x coordinate
    /// @param y The starting y coordinate
    /// @param line_width The length of the line
    /// @param progress a battery percentage out of 100
    static void draw_battery_line(TFT_eSprite* tft, int x, int y, int line_width, float progress);
    static void draw_circular_progress_bar(TFT_eSprite* tft, int x, int y, int radius, int bar_width, int percentage, uint16_t colour_fill, uint16_t colour_empty, uint16_t colour_bg);
    static void draw_progress_bar(TFT_eSprite* tft, int x, int y, int length, int width, int percentage, uint16_t colour_fill, uint16_t colour_empty);
    static void draw_vertical_progress_bar(TFT_eSprite* tft, int x, int y, int length, int width, int percentage, uint16_t colour_fill, uint16_t colour_empty);
    /// @brief This function will take in a max value and a specified value and return an angle based on that. useful for clock hands
    /// @param value the value to generate an angle from
    /// @param max_value The maximum possible value for it
    /// @return This angle to draw at
    static float convert_to_angle(int value, int max_value = 12);
    
    
    // Widget Watch Functions
    /// @brief This function will draw a clock arm starting at the centre position provided. It can have a customised length and starting offset
    /// @param tft The TFT_eSprite to draw to
    /// @param center_x The centre x coordinate
    /// @param center_y The centre y coordinate
    /// @param line_length The outward length of the line
    /// @param line_inner_offset The inner starting offset of the line
    /// @param angle The angle at which to draw the line
    /// @param colour The colour of the line
    static void draw_clock_hand(TFT_eSprite* tft, int center_x, int center_y, int line_inner_offset, int line_length, int angle, uint16_t colour);
    /// @brief This function will draw a clock arm starting at the centre position provided. It can have a customised length and starting offset
    /// @param tft The TFT_eSprite to draw to
    /// @param center_x The centre x coordinate
    /// @param center_y The centre y coordinate
    /// @param line_inner_offset The outward offset length of the line
    /// @param line_length The length of the line
    /// @param angle The angle at which to draw the line
    /// @param line_width how wide the line should be
    /// @param colour The colour of the line
    static void draw_clock_hand_wide(TFT_eSprite* tft, int center_x, int center_y, int line_inner_offset, int line_length, int angle, int line_width, uint16_t colour);
    /// @brief This function will draw a clock arm starting at the centre position provided. It can have a customised length and starting offset
    /// @param tft The TFT_eSprite to draw to
    /// @param center_x The centre x coordinate
    /// @param center_y The centre y coordinate
    /// @param line_inner_offset The outward offset length of the line
    /// @param line_length The length of the line
    /// @param angle The angle at which to draw the line
    /// @param line_width how wide the line should be
    /// @param colour The colour of the line
    static void draw_clock_hand_wedge(TFT_eSprite* tft, int center_x, int center_y, int line_inner_offset, int line_length, int angle, int line_width, uint16_t colour);
    /// @brief This function takes the input time and draws stylised clock hands based on it
    /// @param tft The TFT_eSprite to draw to
    /// @param center_x The centre x coordinate
    /// @param center_y The centre y coordinate
    /// @param length The outward length of the lines
    /// @param width How wide the lines should be
    /// @param hour The hours of the time
    /// @param minute The minutes of the time
    /// @param second The seconds of the time
    /// @param base_color The colour to use for all of the arms
    /// @param volatile_colours Use a colour scheme or one single style
    static void draw_stylised_clock_hands(TFT_eSprite* tft, int center_x, int center_y, int hour, int minute, int second, uint16_t base_colour, bool volatile_colours = false);
    /// @brief This function takes the input time and draws some stylised clock hands based on it
    /// @param tft The TFT_eSprite to draw to
    /// @param center_x The centre x coordinate
    /// @param center_y The centre y coordinate
    /// @param length The outward length of the lines
    /// @param width How wide the lines should be
    /// @param hour The hours of the time
    /// @param minute The minutes of the time
    /// @param second The seconds of the time
    /// @param base_color The colour to use for all of the arms
    /// @param volatile_colours Use a colour scheme or one single style 
    static void draw_wedged_clock_hands(TFT_eSprite* tft, int centre_x, int centre_y, int hour, int minute, int second, uint16_t base_colour, bool volatile_colours = false);
    /// @brief This function takes the input time and draws simple clock hands based on it
    /// @param tft The TFT_eSprite to draw to 
    /// @param center_x The centre x coordinate
    /// @param center_y The centre y coordinate
    /// @param hour The hours of the time
    /// @param minute The minutes of the time
    /// @param second The seconds of the time
    /// @param base_color The colour to use for all of the arms
    /// @param volatile_colours Use a colour scheme or one single style
    static void draw_clock_hands(TFT_eSprite* tft, int centre_x, int centre_y, int hour, int minute, int second, uint16_t base_colour, bool volatile_colours = false);
    /// @brief This function will use the draw_system_information function to draw the steps taken
    /// @param tft The TFT_eSprite to use
    /// @param x The starting x coordinate
    /// @param y The starting y coordinate
    /// @param steps The total number of steps
    /// @param colour_fill The colour of the text
    static void draw_steps_text(TFT_eSprite* tft, int x, int y, int steps, uint16_t colour_fill);
    /// @brief This function will draw the hours text in a normal font anywhere on the screen
    /// @param tft The TFT_eSprite to draw to
    /// @param x The starting x coordinate
    /// @param y The starting y coordinate
    /// @param colour_fill This is the colour of the text
    static void draw_hours_text(TFT_eSprite* tft, int x, int y, uint16_t colour_fill);
    /// @brief This function will draw the minutes text in a normal font anywhere on the screen
    /// @param tft The TFT_eSprite to draw to
    /// @param x The starting x coordinate
    /// @param y The starting y coordinate
    /// @param colour_fill This is the colour of the text
    static void draw_minutes_text(TFT_eSprite* tft, int x, int y, uint16_t colour_fill);
    /// @brief This function will draw the seconds text in a normal font anywhere on the screen
    /// @param tft The TFT_eSprite to draw to
    /// @param x The starting x coordinate
    /// @param y The starting y coordinate
    /// @param colour_fill This is the colour of the text
    static void draw_seconds_text(TFT_eSprite* tft, int x, int y, uint16_t colour_fill);
    /// @brief This function will draw the abbreviated or otherwise week day on the screen
    //// @param tft The TFT_eSprite to draw to
    /// @param x The x coordinate
    /// @param y The y coordinate
    /// @param colour_fill The font colour
    /// @param abbreviation to display Fri or Friday
    static void draw_weekday_text(TFT_eSprite* tft, int x, int y, uint16_t colour_fill, bool abbreviation = true);
    /// @brief This function draws the day of the month
    /// @param tft The TFT_eSprite to draw to
    /// @param x The x coordinate
    /// @param y The y coordinate
    /// @param colour_fill The font colour
    static void draw_day_text(TFT_eSprite* tft, int x, int y, uint16_t colour_fill);
    /// @brief This function draws the month abbreviated or otherwise
    /// @param tft The TFT_eSprite to draw to
    /// @param x The x coordinate
    /// @param y The y coordinate
    /// @param colour_fill The font colour
    /// @param abbreviation Whether to display Apr or April
    static void draw_month_text(TFT_eSprite* tft, int x, int y, uint16_t colour_fill, bool abbreviation = true);
    /// @brief This function draws the calories burned
    /// @param tft The TFT_eSprite to draw to
    /// @param x The x coordinate
    /// @param y The y coordinate
    /// @param calories The total calories burnt
    /// @param colour_fill The font colour
    static void draw_calories_text(TFT_eSprite* tft, int x, int y, int calories, uint16_t colour_fill);
    /// @brief This function draws your location 
    /// @param tft The TFT_eSprite to draw to
    /// @param x The x coordinate
    /// @param y The y coordinate
    /// @param location_text The location text
    /// @param colour_fill The font colour
    static void draw_location_text(TFT_eSprite* tft, int x, int y, std::string location_text, uint16_t colour_fill);
    /// @brief This function draws the current weather text
    /// @param tft The TFT_eSprite to draw to
    /// @param x The x coordinate
    /// @param y The y coordinate
    /// @param weather_text The weather condition
    /// @param colour_fill The font colour
    static void draw_weather_text(TFT_eSprite* tft, int x, int y, std::string weather_text, uint16_t colour_fill);
    /// @brief This function displays information in a bounding box
    /// @param tft The TFT_eSprite to draw to
    /// @param x The x coordinate
    /// @param y The y coordinate
    /// @param system_text The text to display
    /// @param colour_bg The background colour of the bounding box
    /// @param colour_border The border colour of the bounding box
    /// @param selected whether the bounding box has a lighter border and filled interior
    /// @param border Whether the bounding box's border shows.
    static void draw_system_information(TFT_eSprite* tft, int x, int y, std::string system_text, uint16_t colour_bg, uint16_t colour_border, bool selected = false, bool border = false);
    /// @brief This function displays information in a custom way
    /// @param tft The TFT_eSprite to draw to
    /// @param x The x coordinate
    /// @param y The y coordinate
    /// @param custom_text The text to display
    /// @param font_size The text font size
    /// @param colour_bg The background colour of the bounding box
    static void draw_custom_text(TFT_eSprite* tft, int x, int y, std::string custom_text, float font_size, uint16_t colour_bg);
    /// @brief This function displays information in an alignment pattern
    /// @param tft The TFT_eSprite to draw to
    /// @param x The x coordinate
    /// @param y The y coordinate
    /// @param text The text to display
    /// @param colour_bg The background colour of the bounding box
    /// @param font_size The text font size
    /// @param align_right The alignment value
    static void draw_defstyle_aligned(TFT_eSprite* tft, int x, int y, std::string text, uint16_t colour_bg, float font_size = 2, bool align_right = true);


    /// @brief This function returns an integer representation of the hour
    /// @return The hour
    static int get_hour();
    /// @brief This function returns an integer representation of the minutes
    /// @return The minutes
    static int get_minutes();
    /// @brief This function returns an integer representation of the hour
    /// @return The seconds
    static int get_seconds();
    /// @brief This function returns the minutes as a string, but formatted to include 0 if below 10
    /// @return The hour
    static std::string get_hour_string();
    /// @brief This function returns the minutes as a string, but formatted to include 0 if below ten
    /// @return The seconds of the hour
    static std::string get_minutes_string();
    /// @brief This function returns the seconds as a string but formatted to include a 0 if below ten.
    /// @return This function returns the seconds of the hour
    static std::string get_seconds_string();
    /// @brief This function returns a string that is either the full day name or an abbreviation
    /// @param abbreviation A bool which returns either Fri if true, or Friday if false
    /// @return A string representing the day of the week
    static std::string get_week_day_string(bool abbreviation = true);
    /// @brief This function returns a number indicating the day of the month
    /// @return a string representing 0 to 31
    static std::string get_day_string();
    /// @brief This function returns the month as a string, either MMM or MM
    /// @param abbreviation This flag determines if only an abbreviation of the month is returned
    /// @return This function returns a string representing the month
    static std::string get_month_string(bool abbreviation = true);
    /// @brief This function returns a number indicating the month
    /// @return a string month number - 1 to 12
    static std::string get_num_month_string();
    /// @brief This function returns either yyyy or yy.
    /// @param abbreviation A bool to return only the last two digits of the year
    /// @return A string representing the year
    static std::string get_year_string(bool abbreviation = true);

    /// @brief This function will take an input text and draw the weather code as an icon
    /// @param tft The TFT_eSprite to draw to
    /// @param x The starting x position of a 30px by 30px box
    /// @param y The starting y position of a 30px by 30px box
    /// @param weather_type The weather string that indicates the weather
    static void draw_weather_status(TFT_eSprite* tft, int x, int y, std::string weather_type);
    /// @brief This function takes in a number and returns the corresponding weather code
    /// @param weather_code a number between 0 and 9
    /// @return a string used to determine the weather forecast text
    static std::string get_weather_string(WEATHER_CODE weather_code);

    // Colour Functions
    /// @brief This function returns a black colour which fits the overall palette
    /// @param tft The object to use for the colour generation
    /// @return a black colour which roughly fits the overall palette
    static uint16_t get_black(TFT_eSprite* tft);
    /// @brief This function returns a white colour which fits the overall palette
    /// @param tft The object to use for the colour generation
    /// @return a white colour which roughly fits the overall palette
    static uint16_t get_white(TFT_eSprite* tft);
    /// @brief This function returns a red colour which fits the overall palette
    /// @param tft The object to use for the colour generation
    /// @return a red colour which roughly fits the overall palette
    static uint16_t get_red(TFT_eSprite* tft);
    /// @brief This function returns a green colour which fits the overall palette
    /// @param tft The object to use for the colour generation
    /// @return a green colour which roughly fits the overall palette
    static uint16_t get_green(TFT_eSprite* tft);
    /// @brief This function returns a blue colour which fits the overall palette
    /// @param tft The object to use for the colour generation
    /// @return a blue colour which roughly fits the overall palette
    static uint16_t get_blue(TFT_eSprite* tft);
    /// @brief This function returns a purple colour which fits the overall palette
    /// @param tft The object to use for the colour generation
    /// @return a purple colour which roughly fits the overall palette
    static uint16_t get_purple(TFT_eSprite* tft);
    /// @brief This function returns a yellow colour which fits the overall palette
    /// @param tft The object to use for the colour generation
    /// @return a yellow colour which roughly fits the overall palette
    static uint16_t get_yellow(TFT_eSprite* tft);
    /// @brief This function returns a grty colour which fits the overall palette
    /// @param tft The object to use for the colour generation
    /// @return a grey colour which roughly fits the overall palette
    static uint16_t get_grey(TFT_eSprite* tft);
    /// @brief This function returns an orange colour which fits the overall palette
    /// @param tft The object to use for the colour generation
    /// @return an orange colour which roughly fits the overall palette
    static uint16_t get_orange(TFT_eSprite* tft);
    /// @brief This function returns a pink colour which fits the overall palette
    /// @param tft The object to use for the colour generation
    /// @return a pink colour which roughly fits the overall palette
    static uint16_t get_pink(TFT_eSprite* tft);
    /// @brief This function returns a colour based on the current battery level
    /// @param tft The object to use for the colour generation
    /// @param percentage the battery level
    /// @return one of 5 different colours that signify the battery level
    static uint16_t get_battery_colour(TFT_eSprite *tft, int percentage);
    
    /// @brief This function takes and input colour and uses bitwise operations to lighten it
    /// @param colour The input colour to lighten
    /// @param percentage The amount by which to lighten it. 0 to 100
    /// @return a new uint16_t colour that is percentage lighten than the input
    static uint16_t lighten_colour(uint16_t colour, int percentage = 20);
    /// @brief This function takes and input colour and uses bitwise operations to darken it
    /// @param colour The input colour to darken
    /// @param percentage The amount by which to darken it. 0 to 100
    /// @return a new uint16_t colour that is percentage darker than the input
    static uint16_t darken_colour(uint16_t colour, int percentage = 20);

    /// @brief This function will use the input colour and create 5 colours that fit it using the Analagous Complementary Theorem
    /// @param input_colour The colour which will act as a base for the colour palette
    /// @return an std::array containing 5 elements which fit the colour palette
    static std::array<uint16_t, 5> get_analagous_complementary_colours(uint16_t input_colour);
    /// @brief This function will use the input colour and create 5 colours that fit it using the split complementary Theorem
    /// @param input_colour The colour which will act as a base for the colour palette
    /// @return an std::array containing 5 elements which fit the colour palette
    static std::array<uint16_t, 5> get_split_complementary_colours(uint16_t input_colour);
    /// @brief This function will use the input colour and create 5 colours that fit it using the Triadic Colour Theorem
    /// @param input_colour The colour which will act as a base for the colour palette
    /// @return an std::array containing 5 elements which fit the colour palette
    static std::array<uint16_t, 5> get_triadic_colours(uint16_t input_colour);
    /// @brief This function will use the input colour and create 5 colours that fit it using the Tetratic Colour Theorem
    /// @param input_colour The colour which will act as a base for the colour palette
    /// @return an std::array containing 5 elements which fit the colour palette
    static std::array<uint16_t, 5> get_tetradic_colours(uint16_t input_colour);
    /// @brief This function averages out the input colour to convert it to a greyscale colour
    /// @param input_colour The colour to convert to the greyscale specturm
    /// @return A colour that should represent the input colour in a greyscale
    static uint16_t get_greyscale(uint16_t input_colour);

    /// @brief This function uses the drawLine function and rotates it around a given centre dot and angle
    /// @param tft The TFT_eSprite to draw to
    /// @param x The starting x coordinate
    /// @param y The starting y coordinate
    /// @param length The length of the line
    /// @param angle The angle by which the line should be rotated
    /// @param colour The colour of the line
    static void draw_angled_line(TFT_eSprite *tft, int x, int y, int length, int angle, uint16_t colour);
    /// @brief This function uses the drawWideLine function and rotates it around a given centre dot and angle
    /// @param tft The TFT_eSprite to draw to
    /// @param x The starting x coordinate
    /// @param y The starting y coordinate
    /// @param length The length of the line
    /// @param angle The angle by which the line should be rotated
    /// @param size The thickness of the drawn line
    /// @param colour The colour of the line
    static void draw_wide_angled_line(TFT_eSprite* tft, int x, int y, int length, int angle, float size, uint16_t colour);
    /// @brief This function uses the drawWedgeLine function and rotates it around a given centre dot and angle
    /// @param tft The TFT_eSprite to draw to
    /// @param x The starting x coordinate
    /// @param y The starting y coordinate
    /// @param length The length of the line
    /// @param angle The angle by which the line should be rotated
    /// @param size The thickness of the drawn line
    /// @param colour The colour of the line
    static void draw_wedge_angled_line(TFT_eSprite* tft, int x, int y, int length, int angle, float size, uint16_t colour);
    /// @brief This function simplifies the circle command in some ways for consistent use
    /// @param tft The TFT_eSprite to draw to
    /// @param x The starting x coordinate
    /// @param y The starting y coordinate
    /// @param scale The size of the object 1 is 15px by 15px
    /// @param colour The colour of the circle
    static void draw_sized_circle(TFT_eSprite* tft, int x, int y, int scale, uint16_t colour);
    /// @brief This function uses a number of circles to draw a single cloud in an area
    /// @param tft The TFT_eSprite to draw to
    /// @param x The starting x coordinate
    /// @param y The starting y coordinate
    /// @param scale The size of the object 1 is 15px by 15px
    /// @param colour The circle colour
    static void draw_cloud(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour);
    /// @brief This function draws a number of lines indicating rain in a given area
    /// @param tft The TFT_eSprite to draw to
    /// @param x The starting x coordinate
    /// @param y The starting y coordinate
    /// @param scale The size of the object 1 is 15px by 15px
    /// @param colour The line colour
    static void draw_rain(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour);
    /// @brief This function draws a thunderstrike on the screen in a given area
    /// @param tft The TFT_eSprite to draw to
    /// @param x The starting x coordinate
    /// @param y The starting y coordinate
    /// @param scale The size of the object 1 is 15px by 15px
    /// @param colour The line colour
    static void draw_thunder(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour);

protected:
  /// @brief This function compares two strings and if equal returns true
  /// @param str_one The first string to compare
  /// @param str_two The second string to compare
  /// @return True if they are the same, False otherwise
  static bool string_compare(std::string str_one, std::string str_two);
  /// @brief This function converts the entire input string into lowercase
  /// @param input_string The string to convert
  /// @return a string identical to input_string but all in lowercase
  static std::string to_lowercase(std::string input_string);
  /// @brief This function is a default function that will output text in a given area without changing the global text settings. It will however use a different font
  /// @param tft The TFT_eSprite to draw to
  /// @param x The starting x coordinate
  /// @param y The starting y coordinate
  /// @param scale The size of the object 1 is 15px by 15px
  /// @param colour The colour of the text
  /// @param font_size The size of the font
  static void set_freestyle_text(TFT_eSprite* tft, std::string text, int x, int y, uint16_t color = TFT_WHITE, float font_size = 2);
  /// @brief This function is a default function that will output text in a given area without changing the global text settings
  /// @param tft The TFT_eSprite to draw to
  /// @param x The starting x coordinate
  /// @param y The starting y coordinate
  /// @param scale The size of the object 1 is 15px by 15px
  /// @param colour The colour of the text
  /// @param font_size The size of the font
  static void set_defstyle_text(TFT_eSprite* tft, std::string text, int x, int y, uint16_t color = TFT_WHITE, float font_size = 2);

  /// @brief This function draws a sun in the middle of a given area
  /// @param tft The TFT_eSprite to draw to
  /// @param x The starting x coordinate
  /// @param y The starting y coordinate
  /// @param scale The size of the object 1 is 15px by 15px
  static void draw_clear_sky_01(TFT_eSprite* tft, int x, int y, int scale = 1);
  /// @brief This function draws a number of clouds in the centre of a given area
  /// @param tft The TFT_eSprite to draw to
  /// @param x The starting x coordinate
  /// @param y The starting y coordinate
  /// @param scale The size of the object 1 is 15px by 15px
  static void draw_few_clouds_02(TFT_eSprite* tft, int x, int y, int scale = 1);
  /// @brief This function draws a single cloud in a the centre of a given area
  /// @param tft The TFT_eSprite to draw to
  /// @param x The starting x coordinate
  /// @param y The starting y coordinate
  /// @param scale The size of the object 1 is 15px by 15px
  static void draw_scattered_clouds_03(TFT_eSprite* tft, int x, int y, int scale = 1);
  /// @brief This function uses the draw_cloud function to draw a number of clouds in a given area
  /// @param tft The TFT_eSprite to draw to
  /// @param x The starting x coordinate
  /// @param y The starting y coordinate
  /// @param scale The size of the object 1 is 15px by 15px
  static void draw_broken_clouds_04(TFT_eSprite* tft, int x, int y, int scale = 1);
  /// @brief This function draws a number angled lines and clouds to indicate rain in a given area
  /// @param tft The TFT_eSprite to draw to
  /// @param x The starting x coordinate
  /// @param y The starting y coordinate
  /// @param scale The size of the object 1 is 15px by 15px
  static void draw_shower_rain_09(TFT_eSprite* tft, int x, int y, int scale = 1);
  /// @brief This function draws a number of angled lines indicating rain in a given area
  /// @param tft The TFT_eSprite to draw to
  /// @param x The starting x coordinate
  /// @param y The starting y coordinate
  /// @param scale The size of the object 1 is 15px by 15px
  static void draw_rain_10(TFT_eSprite* tft, int x, int y, int scale = 1);
  /// @brief This function draws clouds and lightning on the screen in a given area
  /// @param tft The TFT_eSprite to draw to
  /// @param x The starting x coordinate
  /// @param y The starting y coordinate
  /// @param scale The size of the object 1 is 15px by 15px
  static void draw_thunderstorm_11(TFT_eSprite* tft, int x, int y, int scale = 1);
  /// @brief This function uses the draw_snowflake function to draw a number of snowflakes in a given area
  /// @param tft The TFT_eSprite to draw to
  /// @param x The starting x coordinate
  /// @param y The starting y coordinate
  /// @param scale The size of the object 1 is 15px by 15px
  static void draw_snow_13(TFT_eSprite* tft, int x, int y, int scale = 1);
  /// @brief This function draws a number of lines to indicate mist
  /// @param tft The TFT_eSprite to draw to
  /// @param x The starting x coordinate
  /// @param y The starting y coordinate
  /// @param scale The size of the object 1 is 15px by 15px
  static void draw_mist_50(TFT_eSprite* tft, int x, int y, int scale = 1);
  /// @brief This function draws an individual snow flake cross at the x and y position specified
  /// @param tft The TFT_eSprite to draw to
  /// @param x The starting x coordinate
  /// @param y The starting y coordinate
  /// @param scale The size of the object 1 is 15px by 15px
  /// @param colour The line colour
  static void draw_snowflake(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour);
  /// @brief This function draws a cloud with a red line through it, indicating no connection
  /// @param tft The TFT_eSprite to draw to
  /// @param x The starting x coordinate
  /// @param y The starting y coordinate
  /// @param scale The size of the object 1 is 15px by 15px
  /// @param colour The line colour
  static void draw_no_connection(TFT_eSprite* tft, int x, int y, float scale, uint16_t colour = TFT_RED);


private:

};

#endif


