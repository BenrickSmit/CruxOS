/** This file will handle all the function and class tests for the SystemInfo class
 *  Updated: 27/09/2022**/
#include <gtest/gtest.h>

#include <regex>

#include <SystemInfo.h>


// Write Test Functions
TEST (SystemInfo_Test, test_arduino_info_is_valid) {
    SystemInfo sys;
    std::string arduino_version = sys.get_arduino_version();
    bool is_valid = std::regex_match(arduino_version, std::regex("\\[0-9][0-9].\\[0-9][0-9].\\[0-9][0-9]"));

    ASSERT_TRUE(is_valid);
}

TEST (SystemInfo_Test, test_cpu_core_value_valid) {
    SystemInfo sys;
    int core_value = sys.get_chip_cores();
    bool is_valid = std::regex_match(std::to_string(core_value), std::regex("[0-9]*"));

    ASSERT_TRUE(is_valid);
}





