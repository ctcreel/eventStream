#include "eventStream.h"
#include "eventHandler.h"

unsigned int eventStream::getID(void) {
  return myID;
}

eventStream::eventStream(byte rxPin, byte txPin, unsigned long baudRate, generatorDeviceID *idg) {
  stream = new SoftwareSerial(rxPin, txPin);
  stream->begin(baudRate);
  stream->flush();
  finder = new TextFinder(*stream);
  myID = idg->getID();
  events = 0;
}

void eventStream::addHandler(eventHandler *r) {
  handlers *n = new handlers;
  n->handler = r;
  n->next = events;
  events = n;
}

void eventStream::removeHandlers(const unsigned int m, const unsigned int dt, const unsigned int d) {
  boolean foundOne;
  handlers *current;
  handlers *previous = 0;
  do{
    current = events;
    previous = 0;
    foundOne = false;
    while(current != 0 && !foundOne) {
      if(current->handler->canHandleEvent(m,dt,d)) {
        if(current->next == 0) { // tail
          if(previous == 0) { // only one element
            events = 0;
          } else { // Deleting tail
            previous->next = 0;
          }
        } else if(previous == 0) { // head
          events = events->next;
        } else { // middle
          previous->next = current->next;
        }
        foundOne = true;
        delete current->handler;
        delete current;
      } else {
         previous = current;
         current = current->next;
      }
    }
  } while(foundOne);
}

unsigned int eventStream::hasHandler(const unsigned int m, const unsigned int dt, const unsigned int d) {
  handlers *n = events;
  unsigned int result = 0;
  while(n) {
    if(n->handler->canHandleEvent(m,dt,d)) {
      result++;
      n = n->next;
    } else {
      n = n->next;
    }
  }
  return result;
}

boolean eventStream::check() {
  unsigned int messageID;
  unsigned int deviceTypeID;
  unsigned int deviceID;
  char payload[100];
  char message[100];
  boolean finalResult = false;
  while(stream->available() && finder->getString("@","#",message, 99)) {
    sscanf(message,"%u|%u|%u|%99[0-9a-zA-Z ]",&messageID,&deviceTypeID,&deviceID, payload);
    handlers *n = events;
    while(n) {
      finalResult = finalResult | n->handler->handleEvent(payload,messageID,deviceTypeID,deviceID);
      n = n->next;
    }
  }
  return finalResult;
}

void eventStream::createEvent(const char *p, const unsigned int m, const unsigned int dt, const unsigned int d) {
  char message[100];
  sprintf(message,"@%u|%u|%u|%s#",m,dt,d,p);
  stream->print(message);
}


