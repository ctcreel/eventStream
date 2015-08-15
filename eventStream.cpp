#include "eventStream.h"
#include "eventHandler.h"
#include "DEBUG.h"
#include <Time.h>
#include <TimeAlarms.h>

unsigned int eventStream::getID(void) {
  return myID;
}

unsigned int eventStream::addStream(Stream *s) {
	eventStreams *e = new eventStreams;
	e->stream = s;
	e->finder = new TextFinder(*s);
	e->next = streams;
	e->ID = streamIDs++;
	streams = e;
    s->flush();
}

eventStream::eventStream(Stream *s, generatorDeviceID *idg) {
	streamIDs = 1;
	addStream(s);
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

boolean eventStream::check(unsigned long i) {
  boolean finalResult = false;
  unsigned long t = now();
  eventStreams *s = streams;
  do {
	checkStream(s);
  	if(s->next) {
  		s = s->next;
  	} else {
  		s = streams;
  	}
  } while((now() - t) < i);
  return finalResult;
}

boolean eventStream::checkStream(eventStreams *s) {
	unsigned int messageID;
	unsigned int deviceTypeID;
	unsigned int deviceID;
  	char payload[50];
	char message[50];
	boolean finalResult = false;
	while(s->stream->available() && s->finder->getString("@","#",message, 99)) {
		sscanf(message,"%u|%u|%u|%99[0-9a-zA-Z ]",&messageID,&deviceTypeID,&deviceID, payload);
		Serial.print("Message received - ");
		Serial.println(message);
		handlers *n = events;
		while(n) {
		  finalResult = finalResult | n->handler->handleEvent(payload,messageID,deviceTypeID,deviceID);
		  n = n->next;
		}
	  }
	return finalResult;
}

void eventStream::createEvent(const char *p, const unsigned int m, const unsigned int id, const unsigned int dt, const unsigned int d) {
  	char message[100];
  	sprintf(message,"@%u|%u|%u|%s#",m,dt,d,p);
  	Serial.print("Message sent - ");
  	Serial.println(message);
  	eventStreams *s = streams;
  	do {
  		if(id == 0) { // 0 = broadcast message
	  		s->stream->print(message);
	  		s = s->next;
	  	} else if(s->ID == id) {
	  		s->stream->print(message);
	  		s = 0;
	  	} else {
	  		s = s->next;
	  	}
  	} while(s);
}

void eventStream::createEvent(const unsigned long p, const unsigned int m, const unsigned int id, const unsigned int dt, const unsigned int d) {
	char b[20];
    sprintf( b, "%lu", p);
    createEvent(b,m,dt,d);
}

