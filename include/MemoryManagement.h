/**
 * \author Benrick Smit
 * \date Updated 2022/12/27
 * \brief The Memory Management Class takes care of the creation, deletion, and manipulation of variables for CruxOS
 * 
*/

#ifndef MEMORYMANAGEMENT_H
#define MEMORYMANAGEMENT_H

#include <map>
#include <string>
#include <memory>
#include <sstream>
#include <cassert>
#include <fstream>
#include <limits>
#include <Arduino.h>

/** MemoryManagement Error Codes:
 * MM_VAR_FIND_ISSUE - Cannot find the variable in question
*/

class MemoryManagement
{
public:
    /// @brief This function returns the static instance of the singleton class Memory Management
    ///        to ensure the variables stay until the end of the program's life.
    /// @return an instance of this class
    static MemoryManagement* get_instance();
    /// @brief This function is responsible for the deletion of the instance of Memory Management.
    static void destroy_instance();

    /// @brief This function is responsible for the creation of the variables that can be used later
    /// @param variable_name This is the unique name you would like to give the variable.
    /// @param pointer_value This is the value of the variable you'd like to give in string format
    static void create_variable(const std::string& variable_name, const std::string& pointer_value = "");
    /// @brief 
    /// @param variable_name 
    /// @param new_value 
    static void modify_variable(const std::string& variable_name, const std::string& new_value = "");
    /// @brief This function returns the pointer with a specific variable name
    /// @param variable_name This is the name of the variable to return
    /// @return This is the value returned as a unique pointer
    static std::string get_value(const std::string& variable_name);
    /// @brief This function deletes the pointer mentioned. Deletes nothing should it not exist.
    /// @param variable_name This is the variable to delete
    static void delete_variable(const std::string& variable_name);
    /// @brief This function uses cout to display a list of variables available.
    static void display_variables();
    /// @brief This function returns the total number of created variables.
    /// @return This number is the total number of variables contained in the class
    static int count_variables();

    /// @brief This function takes a string and converts it to a float for use in the system
    /// @param input This is the string that should preferably not have any whitespace and only a single float. 
    /// @return This is the created float value from the input string
    static float to_float(std::string& input);
    /// @brief This function takes a string and converts it to an integer for use in the system
    /// @param input This is a string that should preferably not have any whitespace and only a single integer.
    /// @return This is the created integer value from the input string.
    static int to_int(std::string& input);
    /// @brief This function takes a string and converts it to an long long for use in the system
    /// @param input This is a string that should preferably not have any whitespace and only a single long long.
    /// @return This is the created long value from the input string.
    static long long to_long(std::string& input);

    static void create_nonvolatile_variable(std::string& variable_name, std::string value = "");
    static std::string get_nonvolatile_varible(std::string& variable_name);
    static void modify_nonvolatile_variable(std::string& variable_name, std::string new_value = "");

protected:
    /// @brief This function converts the input string into a lowercase version for case insensitive matching
    /// @param input This is the string to convert to lowercase
    /// @return This is the input variable in lowercase.
    static std::string lowercase(std::string& input);
    /// @brief This function determines whether an input string has any whitespace whatsoever
    /// @param input This is the string which may or may not contain whitespace
    /// @return This function returns true should the string contain any whitespace at all.
    static bool has_whitespace(std::string& input);
    /// @brief This function determines whether an input string has any alphabetical characters at all
    /// @param input This is the string which may or may not contain whitespace
    /// @return This function returns true should the string contain any whitespace at all.
    static bool has_alpha(std::string& input);

    /// @brief This function cleans the input strings by separating all spaced values and comma separated values
    ///          and only returning up until the first value.
    /// @param input This is the input string that potentially contains a space or a comma
    /// @return return a cleaned string for later use.
    static std::string clean_string(std::string& input);

private:
    /// @brief This is the default constructor for a singleton
    MemoryManagement() {m_instance = NULL; Serial.begin(921600);};
    /// @brief This is the default copy constructor for a singleton
    /// @param MemoryManagement is the const MemoryManagement& object for a singleton
    MemoryManagement(const MemoryManagement&) = delete;
    /// @brief The basic destructor for a singleton
    ~MemoryManagement() {};
    /// @brief This is the overloaded assignment operator for a singleton
    /// @param  
    /// @return 
    MemoryManagement& operator=(const MemoryManagement&) = delete; //Assignment Operator does nothing - yet

    // Normally I'd have to delete these pointers manually but the unique_ptr takes care of this for me
    std::map<std::string, std::shared_ptr<std::string>> m_pointer_map_data;    // This map stores the names to the pointers that will be used for data storage.
    static MemoryManagement* m_instance;
};

#endif