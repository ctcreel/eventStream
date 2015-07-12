#ifndef eventHandler_h
#define eventHandler_h

#include <Arduino.h>

class eventStream;

class eventHandler {
  friend eventStream;
  
  private:
    unsigned int messageTypeID;
    unsigned int deviceTypeID;
    unsigned int deviceID;

  protected:
    unsigned int getMessageTypeID(void);
    unsigned int getDeviceTypeID(void);
    unsigned int getDeviceID(void);
    eventStream *stream;
    virtual bool handler(const char *payload, const unsigned int deviceTypeID, const unsigned int deviceID);
    boolean handleEvent(const char *payload, const unsigned long messageID, const unsigned int deviceTypeID, const unsigned int deviceID);

    
  public:
    boolean canHandleEvent(const unsigned long messageID, const unsigned int deviceTypeID, const unsigned int deviceID);
    // Handle messages of a certain type, from a specific type of devices, and potentially from a specific device
    eventHandler(eventStream *r, const unsigned int messageTypeID, const unsigned int deviceTypeID, const unsigned int deviceID=0);
    // Handle messages of a certain type regardless of the device type or specific device
    eventHandler(eventStream *r, const unsigned int messageTypeID);
};

#endif
