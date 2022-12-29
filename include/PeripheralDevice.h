/**
 * \author Benrick Smit
 * \date Updated 2022/12/29
 * \brief The Peripheral Device class will take care of managing the device's orientatation, gathering pedometer data
 *          and any other data that may be needed.
 * 
*/

#ifndef PERIPHERALDEVICE_H
#define PERIPHERALDEVICE_H

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BMA400.h>
#include <QMC5883LCompass.h>

#include <cruxos_constants.h>

class PeripheralDevice{
public:
    /// @brief This function creates an instance of the class if it doesn't exist or returns the instance if it has
    ///         already been created once
    /// @return This is the instance that has to be returned
    PeripheralDevice* get_instance();
    /// @brief This function deletes the current instance of the device
    void delete_instance();

    /// @brief This function will take into account accelerometer data and determine the orientation of the device
    /// @return This is a value of DEVICE_FACE_UP, DEVICE_IN_MOTION, DEVICE_STATIONARY, DEVICE_TILTED, or DEVICE_ERROR
    static DEVICE_ORIENTATION get_device_orientation();

protected:
    /// @brief This function starts the required components
    void start_peripherals();

private:
    PeripheralDevice();                                                         // Prevents individual instances
    ~PeripheralDevice();                                                        // Prevents calling the dtor
    PeripheralDevice(const PeripheralDevice&) = delete;                         // delete the copy ctor
    PeripheralDevice* operator=(const PeripheralDevice&) = delete;              // Delete the assignment operator

    static PeripheralDevice* m_peripheral_device_instance;
    QMC5883LCompass qmc5883l;
    BMA400 bma400;
    Adafruit_BME280 bma280;
};

#endif