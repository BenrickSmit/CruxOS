#include "watchface_settings.h"

watchface_settings::watchface_settings(TFT_eSPI* tft, TFT_eSprite* foreground_sprite): 
    AbstractWatchInterface(tft, foreground_sprite){
}

void watchface_settings::draw(){
    AbstractWatchInterface::get_sprite()->fillSprite(TFT_BLACK);

    if(get_sprite()->created()){
        CruxOSLog::Logging(__FUNCTION__, "m_foreground_sprite exists");
    }else {
        CruxOSLog::Logging(__FUNCTION__, "m_foreground_sprite doesn't exists");
    }

    SystemInfo info;
    std::string os_str = "OS:       " + MemoryManagement::get_instance()->get_value(CN_OS_NAME);
    os_str += " " + MemoryManagement::get_instance()->get_value(CN_OS_VER);
    std::string core_str = "Cores:    ";
    core_str += info.get_chip_cores();
    core_str += " ";
    core_str += std::to_string(info.get_cpu_frequency());
    std::string memory_str = "Chip Flash: ";
    memory_str += info.get_flash_chip_size();
    memory_str += "/";
    memory_str += info.get_flash_chip_speed();
    std::string sram_str = "SRAM:     ";
    sram_str += info.get_free_pseudo_sram();
    sram_str += "/";
    sram_str += info.get_pseudo_sram_size();
    std::string chip_str = "Chip Rev: ";
    chip_str += info.get_chip_revision();

    InterfaceHelper::draw_system_information(get_sprite(), 100, 40, os_str.c_str(), TFT_WHITE, TFT_WHITE);
    InterfaceHelper::draw_system_information(get_sprite(), 100, 60, core_str.c_str(), TFT_WHITE, TFT_WHITE);
    InterfaceHelper::draw_system_information(get_sprite(), 100, 80, chip_str.c_str(), TFT_WHITE, TFT_WHITE);
    InterfaceHelper::draw_system_information(get_sprite(), 100, 100, memory_str.c_str(), TFT_WHITE, TFT_WHITE);
    InterfaceHelper::draw_system_information(get_sprite(), 100, 120, sram_str.c_str(), TFT_WHITE, TFT_WHITE);
    
    
    AbstractWatchInterface::create_image();
}
