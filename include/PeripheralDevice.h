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
#include <CruxOSLog.h>
#include <MemoryManagement.h>

class PeripheralDevice {
public:
    static PeripheralDevice* get_instance();
    static void delete_instance();

    void init_compass();
    void get_compass_coordinates(float& x, float& y, float& z);
    std::string compass_to_string() const;

    void init_accelerometer();
    void get_accelerometer_coordinates(float& x, float& y, float& z) const;
    std::string accelerometer_to_string() const;
    DEVICE_ORIENTATION get_orientation() const;

    static void set_step_interrupt(bool new_int);
    static bool has_step_interrupt();
    static void handle_accel_interrupts();
    static void reset_peripherals();

protected:
    bool float_comparison(const double &magnitude, const double &gravity, const double &epsilon = 0.1) const;
    bool tilted_comparison(const double &magnitude, const double &gravity, const double &epsilon = 0.1) const;
    bool motion_comparison(const double &magnitude, const double &gravity, const double &epsilon = 0.1) const;

    double round_doubles(const double& input) const;

private:
    PeripheralDevice();
    ~PeripheralDevice();
    PeripheralDevice(const PeripheralDevice &) = delete;
    PeripheralDevice& operator=(const PeripheralDevice&) = delete;

    QMC5883LCompass m_compass;
    BMA400 m_accelerometer;
    static PeripheralDevice* m_instance;
    bool m_new_step_interrupt;

    mutable float m_accelerometer_x;
    mutable float m_accelerometer_y;
    mutable float m_accelerometer_z;
};


#endif