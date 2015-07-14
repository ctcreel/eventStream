#ifndef eventStream_h
#define eventStream_h

#include <TextFinder.h>
#include <Stream.h>
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
    Stream *stream;
    unsigned int myID;
  protected:
      void addHandler(eventHandler *r);
       
  public:

    unsigned int getID(void);
    eventStream(Stream *s, generatorDeviceID *idg);
    void removeHandlers(const unsigned int messageTypeID, const unsigned int deviceTypeID, const unsigned int deviceID = 0);
    unsigned int hasHandler(const unsigned int messageTypeID, const unsigned int deviceTypeID, const unsigned int deviceID = 0);
    boolean check(unsigned long timeToCheck = 0);    
  
    // Create an event Only respond to messages of type messageTypeID and from devices with deviceTypeID regardless of the specific device
    void createEvent(const char *payload, const unsigned int messageTypeID, const unsigned int deviceTypeID=0, const unsigned int deviceID = 0);
    void createEvent(const unsigned long payload, const unsigned int messageTypeID, const unsigned int deviceTypeID=0, const unsigned int deviceID = 0);
};

#endif
