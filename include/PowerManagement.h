/**
 * \author Benrick Smit
 * \date Updated 2022/12/29
 * \brief The PowerManagement class will take input from the accellerometers and determine whether to work in low-power
 *          or an alternative power form
 * 
*/

#ifndef POWERMANAGEMENT_H
#define POWERMANAGEMENT_H

#include <Thread.h>
#include <thread>
#include <functional>

#include <Arduino.h>

#include <PowerState.h>
#include <PeripheralDevice.h>
#include <cruxos_constants.h>

class PowerManagement {
public:
     /// @brief This function allows the Singleton instance to run and avoids duplication
    /// @return This is the Singleton instance that is returned.
    PowerManagement* get_instance();
    /// @brief This function deletes the current instance of the Singleton and sets it to nullptr;
    void delete_instance();

    /// @brief This function will run once every few seconds and determine what kind of power management should occur
    static void power_assignment();
    /// @brief This function will ensure that the power functions execute in a loop and will not execute them again if they
    ///         are already running;
    static void power_optimisation();

protected:
    /// @brief This function will return the orientation of the device as an enum for later use.
    /// @return This is the enum that will return DEVICE_FACE_UP, DEVICE_IN_MOTION, DEVICE_STATIONARY, DEVICE_TILTED
    ///          or DEVICE_ERROR based on the accelerometer
    DEVICE_ORIENTATION get_orientation();

    static DEVICE_POWERSTATE get_powerstate();
    static void set_powerstate(DEVICE_POWERSTATE new_powerstate);

  private:
    PowerManagement();
    ~PowerManagement();
    PowerManagement(const PowerManagement&) = delete;               // Delete the copy ctor to avoid duplications
    PowerManagement* operator=(const PowerManagement&) = delete;    // Delete the assignment operator to avoid duplications

    static PowerManagement* m_power_management;

    DEVICE_ORIENTATION m_orientation;
    bool m_power_assignment;
    DEVICE_POWERSTATE m_power_state;
};

#endif