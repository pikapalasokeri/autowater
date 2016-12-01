mainmake: main.cpp
	g++ -std=c++11 ABElectronics_C_Libraries/IOPi/ABE_helpers.c ABElectronics_C_Libraries/IOPi/ABE_IoPi.c ABElectronics_C_Libraries/ADCPi/ABE_ADCPi.c DigitalOutPin.cpp AnalogInPin.cpp PinHandler.cpp WateringUnit.cpp main.cpp -o autowatering
