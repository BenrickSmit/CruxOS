/**
 * \author Benrick Smit
 * \date Updated 2022/12/27
 * \brief The Power State class sets the power state of the board no matter what kind of implementation it is running
 *          on.  
*/


#ifndef POWERSTATE_H
#define POWERSTATE_H

#include <Arduino.h>

// Import a power library should the platform be an ARDUINO
#ifdef ESP_PLATFORM
    #include <esp_sleep.h>
#elif defined(ARDUINO)
    #include <>
#endif

#include <cruxos_constants.h>


class PowerState
{
public:
    /// @brief This function creates an instance of the class if it doesn't exist and returns it enabling uniqueness
    /// @return This is the instance that is returned pointing at this one, to remove duplicates.
    static PowerState* get_instance();
    /// @brief This function deletes the Singleton instance of the class
    static void delete_instance();

    /// @brief This function chooses a platform independent way to put the device on a very low power consumption state
    static void set_power_low();
    /// @brief This function chooses a platform independent way to put the device into a hibernation-like state
    static void set_power_hibernate();
    /// @brief This function cancels all power-states and returns to new.
    static void set_power_normal();


private:
    PowerState();
    ~PowerState();
    PowerState(const PowerState&) = delete;             // Delete the copy constructor to remove duplicates
    PowerState* operator=(const PowerState&) = delete;  // Delete the assignment operator to remove duplicates

    static PowerState *m_state;
};

#endif