#include "SystemInfo.h"

SystemInfo::SystemInfo(){
    // Default ctor
}

SystemInfo::~SystemInfo(){
    // Default dtor
}

auto SystemInfo::get_arduino_version() -> std::string{
    return std::to_string(ESP_ARDUINO_VERSION_MAJOR)+"."+std::to_string(ESP_ARDUINO_VERSION_MINOR)+"."+std::to_string(ESP_ARDUINO_VERSION_PATCH);    
}

auto SystemInfo::get_language_standard() -> std::string {
    return to_string(""+__cplusplus);
}

auto SystemInfo::get_chip_cores() -> u_int16_t {
    return ESP.getChipCores();
}

auto SystemInfo::get_chip_model() -> std::string{
    return to_string(ESP.getChipModel());
}

auto SystemInfo::get_chip_revision() -> u_int8_t {
    return (ESP.getChipRevision());
}

auto SystemInfo::get_cpu_frequency() -> u_int16_t {
    return ESP.getCpuFreqMHz();
}

auto SystemInfo::get_cycle_count() -> u_int16_t {
    return ESP.getCycleCount();
}

auto SystemInfo::get_flash_chip_mode() -> std::string {
    return "1";//static_cast<std::string>(ESP.getFlashChipMode());
}

auto SystemInfo::get_flash_chip_speed() -> u_int16_t {
    return ESP.getFlashChipSpeed();
}

auto SystemInfo::get_flash_chip_size() -> u_int16_t {
    return ESP.getFlashChipSize();
}

auto SystemInfo::get_heap_free() -> u_int16_t {
    return ESP.getFreeHeap();
}

auto SystemInfo::get_heap_size() -> u_int16_t {
    return ESP.getHeapSize();
}

auto SystemInfo::get_max_allocated_heap() -> u_int16_t {
    return ESP.getMaxAllocHeap();
}

auto SystemInfo::get_min_free_heap() -> u_int16_t {
    return ESP.getMinFreeHeap();
}

auto SystemInfo::get_free_pseudo_sram() -> u_int16_t {
    return ESP.getFreePsram();
}

auto SystemInfo::get_pseudo_sram_size() -> u_int16_t {
    return ESP.getPsramSize();
}

auto SystemInfo::get_min_free_pseudo_sram() -> u_int16_t {
    return ESP.getMinFreePsram();
}

auto SystemInfo::get_max_allocated_pseudo_sram() -> u_int16_t {
    return ESP.getMaxAllocPsram();
}

void SystemInfo::serial_print() {
    std::string output_string = "";
    output_string = output_string + (("\n******************** \n"));
    output_string = output_string + (("Arduino Version: "+(get_arduino_version())+'\n'));
    
    
    Serial.print(String(output_string.c_str()));
    
    output_string = "";
    //output_string = output_string + (("C++ Version: "+(get_language_standard())+'\n'));
    output_string = output_string + (("Cores: "+std::to_string(get_chip_cores())+'\n'));
    output_string = output_string + (("Chip Model: "+(get_chip_model()+'\n')));
    
    
    Serial.print(String(output_string.c_str()));
    
    output_string = "";
    //output_string = output_string + (("Chip Rev: "+std::to_string(get_chip_revision())+"\n"));
    output_string = output_string + (("CPU Freq: "+std::to_string(get_cpu_frequency()) + " MHz"+'\n'));
    
    
    Serial.print(String(output_string.c_str()));
    
    output_string = "";
    output_string = output_string + (("Pseudo SRAM: "+std::to_string(get_free_pseudo_sram())+ "/" + std::to_string(get_pseudo_sram_size())+'\n'));
    output_string = output_string + (("Heap: "+std::to_string(get_heap_free()) +"/"+ std::to_string(get_max_allocated_heap())+'\n'));
    output_string = output_string + (("********************"));

    
    Serial.print(String(output_string.c_str()));
    Serial.println("\nActive Core: " + String(xPortGetCoreID()));
}

std::string SystemInfo::to_string(const char *input_data) {
    //Convert the input data into string values
    std::stringstream ss("");
    std::string temp_string = "";
    ss << input_data << '\n';

    std::getline(ss, temp_string, '\n');

    return temp_string;
}

