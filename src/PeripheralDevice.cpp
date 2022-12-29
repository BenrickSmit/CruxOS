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
    Serial.begin(BAUD_RATE);
    if (! bma280.begin(0x76, &Wire)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }

    qmc5883l.init();
    qmc5883l.setSmoothing(10, true);
    Serial.println("Peripheral Devices Finished Initialising");
}

PeripheralDevice::PeripheralDevice(){
    start_peripherals();
}

PeripheralDevice::~PeripheralDevice(){
    // Do nothing
}