#include "PeripheralDevice.h"

PeripheralDevice* PeripheralDevice::m_peripheral_device_instance = nullptr;
PeripheralDevice* PeripheralDevice::get_instance(){
    if (!m_peripheral_device_instance){
        m_peripheral_device_instance = new PeripheralDevice();
    }
    return nullptr;
}

void PeripheralDevice::delete_instance(){
    delete m_peripheral_device_instance;
    m_peripheral_device_instance = nullptr;
}

DEVICE_ORIENTATION PeripheralDevice::get_device_orientation(){
    return DEVICE_ORIENTATION(0);
}

void PeripheralDevice::start_peripherals(){
    bma400.begin();
    qmc5883l.begin();
    bma400.
}

PeripheralDevice::PeripheralDevice(){
    start_peripherals();
}

PeripheralDevice::~PeripheralDevice(){
    // Do nothing
}