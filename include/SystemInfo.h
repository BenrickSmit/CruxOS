/**
 * \author Benrick Smit
 * \date Updated 21/12/2022
 * \brief The SystemInfo class provides the system information for the OS and Hardware components installed.
 * 
*/

#ifndef CRUXOS_SYSTEM_INFO_H
#define CRUXOS_SYSTEM_INFO_H

#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <string>
#include <sstream>
#include <cstdlib>

#include <cruxos_constants.h>

class SystemInfo
{
public:
    // ctor & dtor
    SystemInfo();
    ~SystemInfo();

    // Getters
    auto get_arduino_version() -> std::string;
    auto get_language_standard() -> std::string;
    auto get_chip_cores() -> u_int16_t;
    auto get_chip_model() -> std::string;
    auto get_chip_revision() -> u_int8_t;
    auto get_cpu_frequency() -> u_int16_t;
    auto get_cycle_count() -> u_int16_t;
    auto get_flash_chip_mode() -> std::string;
    auto get_flash_chip_speed() -> u_int16_t;
    auto get_flash_chip_size() -> u_int16_t;
    auto get_heap_free() -> u_int16_t;
    auto get_heap_size() -> u_int16_t;
    auto get_max_allocated_heap() -> u_int16_t;
    auto get_min_free_heap() -> u_int16_t;
    auto get_free_pseudo_sram() -> u_int16_t;
    auto get_pseudo_sram_size() -> u_int16_t;
    auto get_min_free_pseudo_sram() -> u_int16_t;
    auto get_max_allocated_pseudo_sram() -> u_int16_t;

    // Other
    void serial_print();

protected:
    std::string to_string(const char *input_data);

private:

};

#endif