mainmake: main.cpp
	g++ -std=c++11 ABElectronics_C_Libraries/IOPi/ABE_helpers.c ABElectronics_C_Libraries/IOPi/ABE_IoPi.c OutPin.cpp PinHandler.cpp main.cpp -o autowatering
