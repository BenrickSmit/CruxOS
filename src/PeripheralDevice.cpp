#include "PeripheralDevice.h"

PeripheralDevice* PeripheralDevice::m_instance = nullptr;

PeripheralDevice* PeripheralDevice::get_instance() {
  if(!m_instance){
    m_instance = new PeripheralDevice();
  }
  return m_instance;
}

void PeripheralDevice::delete_instance(){
    delete m_instance;
    m_instance = nullptr;
}

PeripheralDevice::PeripheralDevice() {}

PeripheralDevice::~PeripheralDevice() {
}

void PeripheralDevice::init_compass() {
  m_compass.init();
  
}


void PeripheralDevice::get_compass_coordinates(float& x, float& y, float& z) {
  m_compass.read();
  x = m_compass.getX();
  y = m_compass.getY();
  z = m_compass.getZ();
}

std::string PeripheralDevice::compass_to_string() const {
    PeripheralDevice *pd = PeripheralDevice::get_instance();
    std::stringstream ss;
    ss << "x: " << pd->m_compass.getX() << ", y: " << pd->m_compass.getY() << ", z: " << pd->m_compass.getY();
    return ss.str();
}

void PeripheralDevice::init_accelerometer(){
    Wire.begin(GPIO_NUM_21, GPIO_NUM_22, 400000);
    if (!m_accelerometer.Initialize()){
        CruxOSLog::Logging(__FUNCTION__, "BMA400 Not Initialised.", LOG_ERROR);
        while(1);
    } else{
        CruxOSLog::Logging(__FUNCTION__, "BMA400 Initialised.");
        m_accelerometer.Setup(
        BMA400::power_mode_t::NORMAL_LOW_NOISE,
        BMA400::output_data_rate_t::Filter2_100Hz,
        BMA400::acceleation_range_t::RANGE_8G);


        m_accelerometer.DisableInterrupts(); //reset interrupts

        m_accelerometer.ConfigureStepDetectorCounter(
                true,                              // Enable Single tap
                BMA400::interrupt_pin_t::INT_PIN_1 // Trigger on Interrupt Pin 1
        );

            m_accelerometer.ConfigureInterruptPinSettings(
                false, // Disable Latch
                false, // Interrupt Pin 1 active low
                false, // Interrupt Pin 1 in push-pull mode
                false, // Interrupt Pin 2 active low
                false  // Interrupt Pin 2 in push-pull mode
            );

            while (m_accelerometer.GetInterrupts()); // make sure there is no interrupt on the queue

            m_new_step_interrupt = false;
    }

}

void PeripheralDevice::get_accelerometer_coordinates(float& x, float& y, float& z) const{
    PeripheralDevice* pd = PeripheralDevice::get_instance();
    float acceleration[3] = {0};
    pd->m_accelerometer.ReadAcceleration(acceleration);
    m_accelerometer_x = acceleration[0];
    m_accelerometer_y = acceleration[1];
    m_accelerometer_z = acceleration[2];

    x = m_accelerometer_x;
    y = m_accelerometer_y;
    z = m_accelerometer_z;
}

std::string PeripheralDevice::accelerometer_to_string() const{
    PeripheralDevice *pd = PeripheralDevice::get_instance();
    std::stringstream ss;
    float acceleration[3] = {0};
    pd->m_accelerometer.ReadAcceleration(acceleration);
    uint16_t steps = pd->m_accelerometer.GetTotalSteps();
    ss << "x: " << acceleration[0] << ", y: " << acceleration[1] << ", z: " << acceleration[2] << " :: S: " << steps;
    return ss.str();
}

DEVICE_ORIENTATION PeripheralDevice::get_orientation() const{
    // Get the accelerometer coordinates
    float x, y, z;
    get_accelerometer_coordinates(x, y, z);

    // Calculate the magnitude of the accelerometer coordinates
    double magnitude = round_doubles(std::sqrt(round_doubles(x * x) + round_doubles(y * y) + round_doubles(z * z)));

    // Check if the magnitude is close to 1g (9.8 m/s^2)
    if (float_comparison(magnitude, BUILTIN_GRAVITY_ACCELERATION, BUILTIN_EPSILON)) {
        // The device is either face-up or face-down
        //printf("->face-up or face-down\n");
        return DEVICE_FACE_UP;
    } else if (tilted_comparison(magnitude, BUILTIN_GRAVITY_ACCELERATION, BUILTIN_EPSILON)) {
        // The device is tilted
        //printf("->tilted\n");
        return DEVICE_TILTED;
    } else {//if (motion_comparison(magnitude, BUILTIN_GRAVITY_ACCELERATION, BUILTIN_EPSILON)) {
        // The device is in motion
        //printf("->in motion\n");
        return DEVICE_IN_MOTION;
    //} else {
        // The device is stationary
        //printf("->stationary\n");
    }
    //printf("--> M: %f, G: %f, E: %f\n", magnitude, 9.8, 0.1);
    return (DEVICE_ORIENTATION());
}

void PeripheralDevice::set_step_interrupt(bool new_int){
    PeripheralDevice *pd = pd->get_instance();
    pd->m_new_step_interrupt = new_int;
}

bool PeripheralDevice::has_step_interrupt(){
    PeripheralDevice *pd = pd->get_instance();
    return pd->m_new_step_interrupt;
}

void PeripheralDevice::handle_accel_interrupts(){
    
    PeripheralDevice *pd = pd->get_instance();
    if (pd->has_step_interrupt()){
        CruxOSLog::Logging(__FUNCTION__, "Started Accelerometer Interrupt");
        BMA400::interrupt_source_t source = pd->m_accelerometer.GetInterrupts();
        if (source && BMA400::interrupt_source_t::ADV_STEP_DETECTOR_COUNTER){
            CruxOSLog::Logging(__FUNCTION__, "Single Step Detected");
        }else if (source && BMA400::interrupt_source_t::ADV_STEP_DETECTOR_COUNTER_DOUBLE_STEP){
            CruxOSLog::Logging(__FUNCTION__, "Double Step Detected");
        }

        pd->set_step_interrupt(false);
    }
    std::string steps = ">>>>>>Steps: "+std::to_string(pd->m_accelerometer.GetTotalSteps());
    CruxOSLog::Logging(__FUNCTION__, steps.c_str());
    MemoryManagement::modify_variable(CN_STEPS_SAVED, std::to_string(pd->m_accelerometer.GetTotalSteps()));
}

void PeripheralDevice::reset_peripherals(){
    PeripheralDevice *pd = pd->get_instance();
    pd->m_accelerometer.ResetStepCounter();
}

bool PeripheralDevice::float_comparison(const double& magnitude,const  double& gravity,const  double& epsilon) const{
    bool to_return = false;
    if(std::abs(magnitude - gravity) < (epsilon)){
        to_return = true;
    }
    return to_return;
}

bool PeripheralDevice::tilted_comparison(const double& magnitude,const  double& gravity,const  double& epsilon) const{
    bool to_return = false;
    if(std::abs(magnitude - gravity) > (epsilon*0.70)){//std::abs(gravity + epsilon-0.025) < magnitude ){
        to_return = true;
    }
    return to_return;
}

bool PeripheralDevice::motion_comparison(const double& magnitude,const  double& gravity,const  double& epsilon) const{
    bool to_return = false;
    if(std::abs(gravity - epsilon+0.01) > magnitude){
        to_return = true;
    }
    return to_return;
}

double PeripheralDevice::round_doubles(const double& input) const{
    return round(input * 10000) / 10000;
}
