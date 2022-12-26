#include "BatteryInfo.h"


// Initialize the static member variable to nullptr
BatteryInfo* BatteryInfo::m_instance = nullptr;
BatteryInfo::BatteryInfo(): m_battery_voltage(-1), m_battery_perc(-1), m_battery_prev_value(-1), m_batter_new_value(-1),
 m_battery_capacity(-1) , m_battery_status(-1), m_millis_stored(-1) , m_battery_pin(-1) {
    // Do nothing, for now
}

BatteryInfo::~BatteryInfo(){
    // Do nothing, for now
}

void BatteryInfo::destroy_instance() {
  delete m_instance;
  m_instance = nullptr;
}

BatteryInfo* BatteryInfo::get_instance() {
  if (!m_instance) {
    m_instance = new BatteryInfo;
  }
  return m_instance;
}

void BatteryInfo::set_battery_voltage(int voltage){
    BatteryInfo *bi = bi->get_instance();
    bi->m_battery_voltage = voltage; 
}

void BatteryInfo::set_battery_percentage(int percentage){
    BatteryInfo *bi = bi->get_instance();
    bi->m_battery_perc = percentage; 
}

void BatteryInfo::set_battery_value_history(int prevValue){
    BatteryInfo *bi = bi->get_instance();
    bi->m_battery_prev_value = prevValue; 
}

void BatteryInfo::set_battery_change(int newValue){
    BatteryInfo *bi = bi->get_instance();
    bi->m_batter_new_value = newValue; 
}

void BatteryInfo::set_battery_capacity(int capacity){
    BatteryInfo *bi = bi->get_instance();
    bi->m_battery_capacity = capacity; 
}

void BatteryInfo::set_battery_pin(int pin){
    BatteryInfo *bi = bi->get_instance();
    bi->m_battery_pin = pin; 
}

void BatteryInfo::update_battery_info(void* arg){
    // This function is meant to get the all the battery information and set the relevant information as necessary.
    
    // Get the necessary Battery Pin
    if (BatteryInfo::get_pin() == -1){
        BatteryInfo::set_battery_pin(BatteryInfo::get_battery_pin());
    }

    // Get the voltage
    set_battery_voltage(analogRead(get_pin()));
    set_battery_change(get_battery_voltage());

    // Get the capacity
    // This can only be found if the battery if fully charged
    if (get_battery_status() == BATTERY_FULL){
        // This will store the full capacity of the battery only if the battery is full meaning it can be used
        // in percentage calculations
        set_battery_capacity((get_battery_voltage())); // * 1000) / 3.7);   // This gives the answer in mAh
    }
    
    set_battery_percentage(-1);
    if (get_battery_capacity() != -1){
        set_battery_percentage(get_battery_voltage()/get_battery_capacity());
    }
}

void BatteryInfo::determine_battery_status(){
    // This function will determine whether the battery has been constant signalling fully charged
    // read the battery voltage
    const int MAX_VOLTAGE = 4.2;
    int voltage = get_battery_voltage();

    // check if the battery voltage has increased since the last check
    if (voltage > get_battery_value_history()) {
        // battery voltage has increased
        set_battery_status(BATTERY_CHARGING);
    } else if (voltage < get_battery_value_history()) {
        // battery voltage has decreased
        set_battery_status(BATTERY_DRAINING);
    } else {
        // battery voltage has not changed
        set_battery_status(BATTERY_FULL);
    }

    // store the current battery voltage as the previous value
    set_battery_value_history(voltage);
}



int BatteryInfo::get_battery_status(){
    BatteryInfo::determine_battery_status();
    BatteryInfo *bi = bi->get_instance();
    return bi->m_battery_status;
}

void BatteryInfo::set_battery_status(int STATUS){
    BatteryInfo *bi = bi->get_instance();
    bi->m_battery_status = STATUS; 
}

int BatteryInfo::get_battery_pin(){
    //Cycle through a 1000 pins until the first one which gives a relatively plausible answer and use that one.
    Serial.begin(BAUD_RATE);

    unsigned int counter = 0, MAX_VALUE = 100;
    float capacity = -1;
    int pin = -1;
    const float MIN_CAP = 0.00, MAX_CAP = 4.2; // maximum voltage of the battery
    int CURRENT_SENSE_PIN = -1; // pin for the current sense resistor
    const float CURRENT_SENSE_RESISTOR = 0.1; // value of the current sense resistor, in ohms

    for (counter = 0; counter < 100; counter++) {
        // read the voltage of the battery
        int analog_value = analogRead(counter);
        float voltage = get_voltage(analog_value);

        // check if this pin is the current sensing pin
        if (voltage > 0 && voltage <= 0.1) {
            CURRENT_SENSE_PIN = counter;
            continue; // skip the rest of this iteration
        }

        // read the current being drawn from the battery, if the current sensing pin has been found
        if (CURRENT_SENSE_PIN != -1) {
            int current_sense_value = analogRead(CURRENT_SENSE_PIN);
            float current = get_voltage(current_sense_value)/ CURRENT_SENSE_RESISTOR;

            // calculate the battery capacity
            float capacity = voltage / current;

            // check if the battery capacity is plausible
            if (capacity > MIN_CAP && capacity <= MAX_CAP) {
                // print the pin number and battery capacity to the serial console
                //Serial.print("Pin ");
                //Serial.print(counter);
                //Serial.print(": ");
                //Serial.println(capacity);

                pin = counter;
            }
        }
    }

    return pin;
}

float BatteryInfo::get_voltage(float input){
    return (((input * 3.3)/4095));
}

int BatteryInfo::get_battery_voltage() {
    BatteryInfo *bi = bi->get_instance();
    return bi->m_battery_voltage;
}

int BatteryInfo::get_battery_percentage() {
    BatteryInfo *bi = bi->get_instance();
    return bi->m_battery_perc; 
}

int BatteryInfo::get_battery_value_history() {
    BatteryInfo *bi = bi->get_instance();
    return bi->m_battery_prev_value; 
}

int BatteryInfo::get_battery_change() {
    BatteryInfo *bi = bi->get_instance();
    return bi->m_batter_new_value; 
}

int BatteryInfo::get_battery_capacity(){
    BatteryInfo *bi = bi->get_instance();
    return bi->m_battery_capacity; 
}

int BatteryInfo::get_pin(){
    BatteryInfo *bi = bi->get_instance();
    return bi->m_battery_pin; 
}

void BatteryInfo::battery_loop(){
    // set up the timer
    esp_timer_handle_t timer_handle;
    esp_timer_create_args_t timer_args;
    timer_args.callback = &update_battery_info;
    timer_args.arg = NULL;
    timer_args.dispatch_method = ESP_TIMER_TASK;
    timer_args.name = "BATTERY_UPDATE_TIMER";
    esp_timer_create(&timer_args, &timer_handle);

    // start the timer
    esp_timer_start_periodic(timer_handle, BATTERY_UPDATE_TIMER); // check every 10 seconds
}
