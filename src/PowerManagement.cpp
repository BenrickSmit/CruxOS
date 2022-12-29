#include "PowerManagement.h"

PowerManagement* PowerManagement::m_power_management = nullptr;

PowerManagement* PowerManagement::get_instance(){
    if (!m_power_management){
        m_power_management = new PowerManagement();
    }

    return m_power_management;
}

void PowerManagement::delete_instance(){
    delete m_power_management;
    m_power_management = nullptr;
}

void PowerManagement::power_assignment(){
    PowerState* ps = ps->get_instance();
    Serial.begin(BAUD_RATE);
    while (true){
            if (get_orientation() == DEVICE_FACE_UP){
                // Set components to normal power usage since watch is in use
                //PowerState::set_power_normal();
                Serial.println("DO::FACE_UP");
            } else if (get_orientation() == DEVICE_IN_MOTION){
                // Set components to minimal power usage since only peripherals need to work
                //PowerState::set_power_low();
                Serial.println("DO::IN_MOTION");
            } else if (get_orientation() == DEVICE_STATIONARY){
                // Set components to low power usage as the device isn't being used
                // Enter sleep mode
                //PowerState::set_power_hibernate();
                Serial.println("DO::STATIONARY");
            } else{
                // Either an error occurred or the watch is tilted and in that case just normal power for now
                //PowerState::set_power_normal();
                Serial.println("DO::ERROR?");
            }

            // Check power state every few seconds
            delay(PERIPHERAL_ORIENTATION_TIMER);
        }
}

DEVICE_ORIENTATION PowerManagement::get_orientation(){

        // Create an instance of the Peripheral Devices
        PeripheralDevice* pd = pd->get_instance();
        return PeripheralDevice::get_device_orientation();
}

PowerManagement::PowerManagement()
{
        // Do nothing
}

PowerManagement::~PowerManagement(){
    // Do nothing
}