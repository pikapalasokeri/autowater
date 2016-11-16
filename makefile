mainmake: main.cpp
	gcc -c -o iopi_helpers.o ABElectronics_C_Libraries/IOPi/ABE_helpers.c
	gcc -c -o iopi.o ABElectronics_C_Libraries/IOPi/ABE_IoPi.c
	ar rcs iopi.a iopi_helpers.o iopi.o
	g++ -std=c++11 ABElectronics_C_Libraries/IOPi/ABE_helpers.c ABElectronics_C_Libraries/IOPi/ABE_IoPi.c main.cpp -o autowatering
