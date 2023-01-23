#include "PeripheralDevice.h"

PeripheralDevice* PeripheralDevice::m_instance = nullptr;

PeripheralDevice* PeripheralDevice::get_instance() {
  if(!m_instance){
    m_instance = new PeripheralDevice();
  }
  return m_instance;
}

PeripheralDevice::PeripheralDevice() {}

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
