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
    // This function will check to see the orientation of the device and set the power level accordingly, but only
    // if the new power state is not the same as the old power state.
    PowerState* ps = ps->get_instance();
    PowerManagement* pm = pm->get_instance();
    Serial.begin(BAUD_RATE);

    while (true){//(counter < 0){
            if (pm->get_orientation() == DEVICE_FACE_UP){
                // Set components to normal power usage since watch is in use
                if (PowerManagement::get_powerstate() != DEVICE_POWERSTATE::DEVICE_POWER_NORMAL){
                    PowerState::set_power_normal();
                    PowerManagement::set_powerstate(DEVICE_POWERSTATE::DEVICE_POWER_NORMAL);
                }
                Serial.println("DO::FACE_UP");
            } else if (pm->get_orientation() == DEVICE_IN_MOTION){
                // Set components to minimal power usage since only peripherals need to work
                if (PowerManagement::get_powerstate() != DEVICE_POWERSTATE::DEVICE_POWER_LOW){
                    PowerState::set_power_low();
                    PowerManagement::set_powerstate(DEVICE_POWERSTATE::DEVICE_POWER_LOW);
                }
                Serial.println("DO::IN_MOTION");
            } else if (pm->get_orientation() == DEVICE_TILTED){
                // Set components to low power usage as the device isn't being used
                // Enter sleep mode
                //PowerState::set_power_low();
                if (PowerManagement::get_powerstate() != DEVICE_POWERSTATE::DEVICE_POWER_LOW){
                    PowerState::set_power_low();
                    PowerManagement::set_powerstate(DEVICE_POWERSTATE::DEVICE_POWER_LOW);
                }
                Serial.println("DO::TILTED");
            } else{
                // If some kind of error has occurred, it's best to go back to normal power
                PowerState::set_power_normal();
                PowerManagement::set_powerstate(DEVICE_POWERSTATE::DEVICE_POWER_NORMAL);
                Serial.println("DO::ERROR?");
            }
            
            delay(PERIPHERAL_ORIENTATION_TIMER);
        }

}

void PowerManagement::power_optimisation(){
    // This function will determine if the power optimisation has started already,
    // but if not will start it.
    PowerManagement *pm = pm->get_instance();
    std::thread power_optimisation_thread(&PowerManagement::power_assignment);
    power_optimisation_thread.detach();
}

DEVICE_ORIENTATION PowerManagement::get_orientation(){

        // Create an instance of the Peripheral Devices
        PeripheralDevice *pd = pd->get_instance();
        
        return pd->get_orientation();
}



DEVICE_POWERSTATE PowerManagement::get_powerstate(){
    PowerManagement *pm = pm->get_instance();
    return pm->m_power_state;
}

void PowerManagement::set_powerstate(DEVICE_POWERSTATE new_powerstate){
    PowerManagement *pm = pm->get_instance();
    pm->m_power_state = new_powerstate;
}



PowerManagement::PowerManagement(){
    m_power_assignment = false;
    //m_power_optimise_thread = Thread();
    //m_power_optimise_thread.onRun(PowerManagement::power_assignment);
	//m_power_optimise_thread.setInterval(PERIPHERAL_ORIENTATION_TIMER);
}

PowerManagement::~PowerManagement(){
    // Do nothing
}

