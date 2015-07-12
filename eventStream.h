#ifndef eventStream_h
#define eventStream_h

#include <TextFinder.h>
#include <SoftwareSerial.h>
#include "generatorDeviceID.h"
#include "eventHandler.h"

class eventStream {

  friend eventHandler;
  
  private:
    struct handlers {
      eventHandler *handler;
      handlers *next;
    } *events;
    
    TextFinder *finder;
    SoftwareSerial *stream;
    unsigned int myID;
  protected:
      void addHandler(eventHandler *r);
       
  public:

    unsigned int getID(void);
    eventStream(byte rxPin, byte txPin, unsigned long baudRate, generatorDeviceID *idg);
    void removeHandlers(const unsigned int messageTypeID, const unsigned int deviceTypeID, const unsigned int deviceID = 0);
    unsigned int hasHandler(const unsigned int messageTypeID, const unsigned int deviceTypeID, const unsigned int deviceID = 0);
    boolean check();    
  
    // Create an event Only respond to messages of type messageTypeID and from devices with deviceTypeID regardless of the specific device
    void createEvent(const char *payload, const unsigned int messageTypeID, const unsigned int deviceTypeID=0, const unsigned int deviceID = 0);
};

#endif
