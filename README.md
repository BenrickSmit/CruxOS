# CruxOS
This is an Open Source Operating System for smart watches based on the TTGO Micro-32 arduino processor for the OpenSmartwatch designed by "Paul's 3D Things".

# Description
CruxOS is designed with microprocessors in mind. Not only will it make sure that the OS can expand based on the available resources of the processor, but it will make sure to use it to its fullest to do everything programmatically, sytematically, and as quickly as possible. Even if it'll need some additional "compatibility layers".

CruxOS is meant to be the smallest OS possible, while still being able to be run on different microprocessors and not dependent on the available peripherals. Expandability will likely come in second or third revisions but is ultimately a goal.

There is some additional executables and documentation which may or may not work at this point in time. These include:
<code>init_documentation.sh</code> is used to create the documentation automatically
<code>run_all.sh</code> is used to run all tests and program execution, as well as to create the necessary documentation and profile information
<code>run_application.sh</code> is used to run only the application
<code>run_tests.sh</code> is used to run only the tests
<code>run_profile.sh</code> is used to run only the profiler

<code>build_info</code> contains the build_name, build_version, and build_cxx_standard text files.
<code>build_name</code> contains the project name. 
<code>build_version</code> contains the project version number. 
<code>build_cxx_standard</code> contains the CXX standard used, it's default is 11

Find the project [here](https://github.com/BenrickSmit/CruxOS), if you did not find this project on my github.

# Features
CruxOS will provide the following features at the moment of completion.
```
   - Read and Write Wifi Access
   - Read and Write "RAM" Access
   - Read and Write "Storage" Access
   - Read and Write Bluetooth Access
   - Read Pedometer
   - Read Gryoscope
   - Read Battery Percentage
    
   - Custom Variable Allocation
   - Custom Variable Read
   - Possible Mutex Data
    
   - Time Faces (Classic, Digital, Minimalist)
   - Settings (System & Personal)
   - Historical Data (as far as possible)
   - Weather Data (as much as possible)
   - About CruxOS
    
   - Wifi Position (if possible)
   - Wifi Weather Data (if possible)
   - Day and Week Step Counter
   - Button Navigation
   - Personal Data for recovery
   - Bluetooth connection to smartphones
   - Navigatible Keyboard for Use (Varing Implementation may be possible.)
```
  
  

# Future Changes
CruxOS future versions will likely contain the following features:
  <code> - Environmental Status</code>
  <code> - Simple Smart Home Integration (?)</code>
  <code> - Bluetooth Smartphone Control (Music, etc)</code>
  <code> - GPS Information</code>


# How to Run
N/A Yet

# How to Run Unit Tests
N/A Yet

# Key Dependencies
This System in currently dependent on the following Arduino Libraries:
  <code> - Wifi</code>
  <code> - Adafruit GFX Library</code>
  <code> - Adafruit BusIO</code>
  <code> - </code>
  <code> - ESP32 BLE</code>


# How to contribute
This project will follow most of the OpenCV rules for coding best practices while keeping to the Arduino code variation where necessary. 
For more information on the coding style, go to [OpenCV](https://github.com/opencv/opencv/wiki/Coding_Style_Guide).

As for contributions, please feel free to contribute via branches, bug reports, and eventually possibly buying me a coffee.

# License
This states the [licence](LICENSE)

