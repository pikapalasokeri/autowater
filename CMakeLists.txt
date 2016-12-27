cmake_minimum_required(VERSION 2.6)

add_library(
abe
ABElectronics_C_Libraries/IOPi/ABE_helpers.c
ABElectronics_C_Libraries/IOPi/ABE_IoPi.c
ABElectronics_C_Libraries/ADCPi/ABE_ADCPi.c)

add_library(
core
AnalogInPin.cpp
DigitalOutPin.cpp
PinHandler.cpp
WateringUnit.cpp
WateringUnitManager.cpp)

add_executable(autowatering main.cpp)
target_link_libraries(autowatering core abe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
