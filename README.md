# CruxOS: Camelia
This is an embedded OS for Paul's 3D Things ESP32 based smartwatch. It is written
in C++11 and could possibly work on other versions of the smartwatch, or even
different smartwatches.

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
```
   - Environmental Status
   - Simple Smart Home Integration (?)
   - Bluetooth Smartphone Control (Music, etc)
   - GPS Information
```


# How to Run
N/A Yet

# How to Run Unit Tests
N/A Yet

# Key Dependencies
This System in currently dependent on the following Arduino Libraries:
```  
   - Wifi
   - Adafruit GFX Library
   - Adafruit BusIO
   - ESP32 BLE
```


# Instructions
No instructions thus far

# Contribution
Any code contributions are welcome

# C++ Coding Style Guideline
The projects's style guide is based on the OpenCV style guide with a few 
differences.

To summarise the style guide:
    -   We do not use the Allman style for indentation - Curly braces do not have
        to go on separate lines
    -   We use tabs for indendation and not spaces
    -   Use Unix-style line endings (LF) and not Windows-style line endings (CRLF)
    -   Follow the Google C++ style guide:
        -   Do not use namespaces
        -   Do not use the 'const' keyword for function arguments unless 
            necessary.
        -   Do not use the 'explicit' keyword for single-argument constructors
    -   Do  use nullptr instead of NULL
    -   Use snake_case for functions, but CamelCase for Type names with the 
        first letter capitilised
    -   Use ALL_CAPS for macro names.
    -   Use descriptive names for functions, variables, and types
    -   Use 'const' wherever possible to make code easier to read and maintain
    -   Use 'inline' sparingly as this can increase file sizes for the already
        small memory of the smartwatch.


# LICENSE
This software is licensed under the [GPL 3.0 License](LICENSE)
