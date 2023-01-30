#include "watchface_settings.h"

watchface_settings::watchface_settings(TFT_eSPI* tft, TFT_eSprite* foreground_sprite): 
    AbstractWatchInterface(tft, foreground_sprite){
        m_info = SystemInfo();
}

void watchface_settings::draw(){
    AbstractWatchInterface::get_sprite()->fillSprite(TFT_BLACK);

    if(get_sprite()->created()){
        CruxOSLog::Logging(__FUNCTION__, "m_foreground_sprite exists");
    }else {
        CruxOSLog::Logging(__FUNCTION__, "m_foreground_sprite doesn't exists");
    }

    
    std::string os_str = "OS:         " + MemoryManagement::get_instance()->get_value(CN_OS_NAME);
    std::string os_ver_str = "OS Ver:     " + MemoryManagement::get_instance()->get_value(CN_OS_VER);
    std::string core_str = "Cores:      ";
    core_str += std::to_string(m_info.get_chip_cores());
    core_str += " x ";
    core_str += std::to_string(m_info.get_cpu_frequency());
    core_str += " Mhz";
    std::string memory_str = "Chip Flash: ";
    memory_str += std::to_string(m_info.get_flash_chip_size());
    memory_str += "/";
    memory_str += std::to_string(m_info.get_flash_chip_speed());
    std::string sram_str = "SRAM:       ";
    sram_str += std::to_string(m_info.get_free_pseudo_sram());
    sram_str += "/";
    sram_str += std::to_string(m_info.get_pseudo_sram_size());
    std::string chip_str = "Chip Rev:   ";
    chip_str += std::to_string(m_info.get_chip_revision());
    std::string bat_lev = "Battery Lvl:";
    bat_lev += MemoryManagement::get_value(CN_BATTERY_VAR);
    bat_lev += " %";
    MemoryManagement::modify_variable(CN_MILLIS_SINCE_START, std::to_string(millis()));
    std::string boot_time = MemoryManagement::get_value(CN_MILLIS_SINCE_START);
    unsigned long long elapsed_time = MemoryManagement::to_long(boot_time);
    unsigned long seconds = (elapsed_time / 1000) % 60;
    unsigned long minutes = (elapsed_time / (1000 * 60)) % 60;
    unsigned long hours = (elapsed_time / (1000 * 60 * 60)) % 24;
    boot_time = "Boot Time:  " +std::to_string(hours) + "h" + std::to_string(minutes) + "m" + std::to_string(seconds) + "s";

    int x_column = 40;
    int font_size = 1;

    // Draw Border
    get_sprite()->drawSmoothRoundRect(32, 32, 2, 1, 168, 178, TFT_WHITE);

    InterfaceHelper::draw_defstyle_aligned(get_sprite(), 40, 40, os_str.c_str(), TFT_WHITE, font_size);
    InterfaceHelper::draw_defstyle_aligned(get_sprite(), 40, 60, os_ver_str.c_str(), TFT_WHITE, font_size);
    InterfaceHelper::draw_defstyle_aligned(get_sprite(), 40, 80, core_str.c_str(), TFT_WHITE, font_size);
    InterfaceHelper::draw_defstyle_aligned(get_sprite(), 40, 100, chip_str.c_str(), TFT_WHITE, font_size);
    InterfaceHelper::draw_defstyle_aligned(get_sprite(), 40, 120, memory_str.c_str(), TFT_WHITE, font_size);
    InterfaceHelper::draw_defstyle_aligned(get_sprite(), 40, 140, sram_str.c_str(), TFT_WHITE, font_size);
    InterfaceHelper::draw_defstyle_aligned(get_sprite(), 40, 160, bat_lev.c_str(), TFT_WHITE, font_size);
    InterfaceHelper::draw_defstyle_aligned(get_sprite(), 40, 180, boot_time.c_str(), TFT_WHITE, font_size);

    AbstractWatchInterface::create_image();
}
