#include "eventStream.h"
#include "eventHandler.h"

unsigned int eventHandler::getMessageTypeID(void) {return messageTypeID;}
unsigned int eventHandler::getDeviceTypeID(void) {return deviceTypeID;}
unsigned int eventHandler::getDeviceID(void) {return deviceID;}

boolean eventHandler::handler(const char *payload, const unsigned int deviceTypeID, const unsigned int deviceID) {
  return false;
}

boolean eventHandler::canHandleEvent(const unsigned long m, const unsigned int r, const unsigned int d) {
  return (m == messageTypeID) && ((r == deviceTypeID) || deviceTypeID == 0) && ((d == deviceID) || deviceID == 0);
}

eventHandler::eventHandler(eventStream *r, const unsigned int m, const unsigned int dt, const unsigned int did) {
  stream = r;
  r->addHandler(this);
  messageTypeID = m;
  deviceTypeID = dt;
  deviceID = did;
}

eventHandler::eventHandler(eventStream *r, const unsigned int m) {
  stream = r;
  r->addHandler(this);
  messageTypeID = m;
  deviceTypeID = 0;
  deviceID = 0;
}

boolean eventHandler::handleEvent(const char *p, const unsigned long m, const unsigned int r, const unsigned int d) {
  Serial.println("Message handler ID is "+String(messageTypeID) + " and incoming message is ID "+String(m));
  if(canHandleEvent(m,r,d)) {
      return this->handler(p, r, d);
    } else {
      return false;
    }
}
