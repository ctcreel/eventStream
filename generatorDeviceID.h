#ifndef generatorDeviceID_h
#define generatorDeviceID_h

#include <generatorDeviceID.h>

class generatorDeviceID {
  private:
    static unsigned int ID;
  public:
    unsigned int getID(void) {return ID++;}
};

#endif
