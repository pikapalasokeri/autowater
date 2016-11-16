
#include "ABElectronics_C_Libraries/IOPi/ABE_IoPi.h"

#include <iostream>
#include <unistd.h>

void
setAll(int value)
{
  for (int i = 0; i < 16; ++i)
    write_pin(0x21, i, value);
}

void
setAllPortDirections()
{
  for (int i = 0; i < 16; ++i)
    set_port_direction(0x21, i, 0x00);
}

int main()
{
  IOPi_init(0x21);

  setAllPortDirections();
  
  while (true)
  {
    setAll(0);
    usleep(1000000);
    setAll(1);
    usleep(1000000);
  }

  return 0;
}
