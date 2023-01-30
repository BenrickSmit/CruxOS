/**
 * \author Benrick Smit
 * \date Updated 2022/12/27
 * \brief The Memory Management Class takes care of the creation, deletion, and manipulation of variables for CruxOS
 * 
*/

#ifndef BATTERYINFO_H
#define BATTERYINFO_H

#include <Arduino.h>

#include <CruxOSLog.h>
#include <cruxos_constants.h>

class BatteryInfo {
public:
    static BatteryInfo* get_instance();

    static void destroy_instance();

    /// @brief This function will get the currently saved battery voltage and return it
    /// @return This is the last battery voltage gotten and saved. It should be a value between 0 and 5V.
    static int get_battery_voltage();
    /// @brief This function will calculate the percentage of the battery that is left and return it.
    /// @return This function will return a value between 0 and 100, but may return -1 if it is unsure.
    static int get_battery_percentage();
    /// @brief This function returns the previous battery voltage that was saved in the class
    /// @return This is a value between 0 and 5V in most situations
    static int get_battery_value_history();
    /// @brief This function returns the current battery voltage that has not yet been saved in the class
    /// @return This is a value between 0 and 5v in most situations
    static int get_battery_change();
    /// @brief This function returns the total battery voltage possible and is normally a value between 0 and 5V
    /// @return This is the max value possible for the battery and is only found after a charge
    static int get_battery_capacity();
    /// @brief This function returns the pin where the battery is connected for use.
    /// @return This should be a small integer number, if not then the correct pin may not have been identified yet
    static int get_pin();

    /// @brief This function is a function that will update all the information about the battery every 
    ///     BATTERY_UPDATE_TIMER seconds
    static void battery_loop();
    /// @brief This function will call the battery information once
    static void battery_update();

protected:
    /// @brief This function sets the battery voltage to be saved
    /// @param voltage This is the value to be saved
    static void set_battery_voltage(int voltage);
    /// @brief This function sets the battery percentage left to be saved
    /// @param percentage This is the value to be saved
    static void set_battery_percentage(int percentage);
    /// @brief This function sets the battery's previous capacity for saving
    /// @param prevValue This is the value to be saved
    static void set_battery_value_history(int prevValue);
    /// @brief This function sets the battery's current capacity for saving
    /// @param newValue This is the value to be saved
    static void set_battery_change(int newValue);
    /// @brief This function sets the battery percentage that represents the max possible for saving
    /// @param capacity This is the value to be saved
    static void set_battery_capacity(int capacity);
    /// @brief This function sets the battery pin that is used for getting the battery information
    /// @param pin This is the value to be saved
    static void set_battery_pin(int pin);

    /// @brief This function will get the immediate
    static void update_battery_info(void* arg);
    /// @brief This function will fire every few milliseconds and determine whether the battery is CHARGE, FULL
    ///         or DRAIN
    static void determine_battery_status();

    
    /// @brief This function will return the status of the battery CHARGE, FULL, or DRAIN
    static int get_battery_status();
    /// @brief This function sets the battery status as needed based on observational results
    /// @param STATUS This value is -1 for not set, 0 for FULL, 1 for DRAINING, and 2 for CHARGING.
    static void set_battery_status(int STATUS);
    
    /// @brief This function will run and try a set of at least 100 pins and return a possible input pin for the battery
    /// @return This number represents the pin number for the battery
    static int get_battery_pin();

    /// @brief This function calculates the voltage of the battery
    /// @param input This is the analog input
    /// @return This should return the voltage of the battery as a float
    static float get_voltage(float input);
    

private:
    // Private constructor to prevent instantiation of the BatteryInfo class
    BatteryInfo();
    ~BatteryInfo();
    
    // Private copy constructor and assignment operator to prevent copy and assignment
    BatteryInfo(const BatteryInfo&) = delete;
    BatteryInfo& operator=(const BatteryInfo&) = delete;

    // Private static member variable to store the singleton instance of the BatteryInfo class
    static BatteryInfo* m_instance;

    // Private member variables
    int m_battery_voltage;                      // Contains the current voltage
    int m_battery_perc;                         // Contains the current battery percentage
    int m_battery_prev_value;                   // Used to determine if there were any changes in the battery voltage
    int m_batter_new_value;                     // Used to determine if there were any changes in the battery voltage
    int m_battery_capacity;                     // Contains the battery's capacity
    int m_battery_status;                       // Determines whether the battery's status

    unsigned long m_millis_stored;              // This will store the last milliseconds for checking purposes
    int m_battery_pin;                          // This is the pin on this hip connected tothe battery
};


#endif