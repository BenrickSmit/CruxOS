/**
 * \author Benrick Smit
 * \date Updated 2022/12/29
 * \brief The Peripheral Device class will take care of managing the device's orientatation, gathering pedometer data
 *          and any other data that may be needed.
 * 
*/

#ifndef PERIPHERALDEVICE_H
#define PERIPHERALDEVICE_H

#include <cmath>
#include <string>
#include <sstream>

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BMA400.h>
#include <QMC5883LCompass.h>

#include <cruxos_constants.h>

class PeripheralDevice {
public:
    static PeripheralDevice* get_instance();

    void init_compass();
    void get_compass_coordinates(float& x, float& y, float& z);
    std::string compass_to_string() const;

    void init_accelerometer();
    void get_accelerometer_coordinates(float& x, float& y, float& z) const;
    std::string accelerometer_to_string() const;
    DEVICE_ORIENTATION get_orientation() const;

protected:
    bool float_comparison(const double &magnitude, const double &gravity, const double &epsilon = 0.1) const;
    bool tilted_comparison(const double &magnitude, const double &gravity, const double &epsilon = 0.1) const;
    bool motion_comparison(const double &magnitude, const double &gravity, const double &epsilon = 0.1) const;

    double round_doubles(const double& input) const;

private:
    PeripheralDevice();
    PeripheralDevice(const PeripheralDevice&) = delete;
    PeripheralDevice& operator=(const PeripheralDevice&) = delete;

    QMC5883LCompass m_compass;
    BMA400 m_accelerometer;
    static PeripheralDevice* m_instance;

    mutable float m_accelerometer_x;
    mutable float m_accelerometer_y;
    mutable float m_accelerometer_z;
};


#endif