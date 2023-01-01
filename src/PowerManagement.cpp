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
    PowerManagement* pm = pm->get_instance();
    Serial.begin(BAUD_RATE);
    while (true){
            if (pm->get_orientation() == DEVICE_FACE_UP){
                // Set components to normal power usage since watch is in use
                if (PowerState::get_powerstate() != DEVICE_POWERSTATE::DEVICE_POWER_NORMAL){
                    PowerState::set_power_normal();
                    PowerState::set_powerstate(DEVICE_POWERSTATE::DEVICE_POWER_NORMAL);
                }
                Serial.println("DO::FACE_UP");
            } else if (pm->get_orientation() == DEVICE_IN_MOTION){
                // Set components to minimal power usage since only peripherals need to work
                if (PowerState::get_powerstate() != DEVICE_POWERSTATE::DEVICE_POWER_LOW){
                    PowerState::set_power_normal();
                    PowerState::set_powerstate(DEVICE_POWERSTATE::DEVICE_POWER_LOW);
                }
                Serial.println("DO::IN_MOTION");
            } else if (pm->get_orientation() == DEVICE_TILTED){
                // Set components to low power usage as the device isn't being used
                // Enter sleep mode
                //PowerState::set_power_low();
                if (PowerState::get_powerstate() != DEVICE_POWERSTATE::DEVICE_POWER_LOW){
                    PowerState::set_power_normal();
                    PowerState::set_powerstate(DEVICE_POWERSTATE::DEVICE_POWER_LOW);
                }
                Serial.println("DO::TILTED");
            } else{
                // If some kind of error has occurred, it's best to go back to normal power
                PowerState::set_power_normal();
                PowerState::set_powerstate(DEVICE_POWERSTATE::DEVICE_POWER_NORMAL);
                Serial.println("DO::ERROR?");
            }

            // Check power state every few seconds
            delay(PERIPHERAL_ORIENTATION_TIMER);
        }
}

DEVICE_ORIENTATION PowerManagement::get_orientation(){

        // Create an instance of the Peripheral Devices
        PeripheralDevice *pd = pd->get_instance();
        
        return pd->get_orientation();
}


PowerManagement::PowerManagement(){
        // Do nothing
}

PowerManagement::~PowerManagement(){
    // Do nothing
}