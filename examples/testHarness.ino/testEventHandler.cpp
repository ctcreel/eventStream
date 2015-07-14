#include "testEventHandler.h"

bool testEventHandler::handler(const char *payload, const unsigned int deviceTypeID, const unsigned int deviceID) {
  Serial.print("Test handler received payload - ");
  Serial.println(payload);
  if(getMessageTypeID() == 1) {
    stream->createEvent("testing2",2,0,0);
    return true;
  } else if(getMessageTypeID() == 2,0,0) {
    stream->createEvent("testing1",1,0,0);
    return true;
  }
  return false;
}

testEventHandler::testEventHandler(eventStream *r, const unsigned int messageTypeID, const unsigned int deviceTypeID, const unsigned int deviceID) :
eventHandler(r,messageTypeID,deviceTypeID,deviceID) {}

testEventHandler::testEventHandler(eventStream *r, const unsigned int messageTypeID) :
eventHandler(r,messageTypeID) {}
