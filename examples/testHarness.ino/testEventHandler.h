#ifndef testEventHandler_h
#define testEventHandler_h

#include <eventStream.h>
#include <eventHandler.h>

class testEventHandler : private eventHandler {
  private:
    virtual bool handler(const char *payload, const unsigned int deviceTypeID, const unsigned int deviceID);
  public:
    testEventHandler(eventStream *r, const unsigned int messageTypeID, const unsigned int deviceTypeID, const unsigned int deviceID=0);
    testEventHandler(eventStream *r, const unsigned int messageTypeID);
};

#endif
