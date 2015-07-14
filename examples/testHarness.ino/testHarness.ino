#include <eventStream.h>
#include <generatorDeviceID.h>
#include "testEventHandler.h"
#include <TextFinder.h>
#include <SoftwareSerial.h>
#include <MemoryFree.h>

eventStream *eventStreamOne;
generatorDeviceID gID;
unsigned int count;

#define EVENT_ONE 1
#define EVENT_TWO 2
#define EVENT_THREE 3
#define DEVICE_TYPE_ONE 1
#define DEVICE_TYPE_TWO 2
#define DEVICE_TYPE_THREE 3

void setup() {
  Serial.begin(9600);
  Serial.flush();
  unsigned long previousMemory;
  
  /* message ID | sender type ID | sender ID | message payload */
  eventStreamOne = new eventStream(11,10,115200,&gID);
  previousMemory = freeMemory();
  
  Serial.println("Starting Memory - "+ String(previousMemory));
  unsigned int m, dt, d, i;
  const unsigned int maxHandlers = 4;
  for(unsigned int i = 0; i < 1000; i++) {  
    for(m = 1; m <= maxHandlers; m++) {
      for(dt = 1; dt <= maxHandlers; dt++) {
        for(d = 1; d <= maxHandlers; d++) {
          new testEventHandler(eventStreamOne,(rand() % 3)+1,rand() % 3+1, rand() % 3+1);
        }
      }
    }
    
    for(m = 1; m <= maxHandlers+1; m++) {
      for(dt = 1; dt <= maxHandlers; dt++) {
        for(d = 1; d <= maxHandlers; d++) {
          eventStreamOne->removeHandlers(m,dt,d);
        }
      }
    }
    while((previousMemory - freeMemory()));
    if(!(i%100)) Serial.print(".");
  }
  Serial.println("");
  Serial.println("Ending memory - "+ String(freeMemory()));
  
  Serial.println("Testing communication... press any key to continue...");
  while(!Serial.available());
  Serial.flush();
  Serial.println("Handlers for messageTypeID 1 - " + String(eventStreamOne->hasHandler(1,0,0)));
  new testEventHandler(eventStreamOne,1,0,0);
  Serial.println("Handlers for messageTypeID 2 - " + String(eventStreamOne->hasHandler(2,0,0)));
  new testEventHandler(eventStreamOne,2,0,0);
  eventStreamOne->createEvent("testing1",1,0,0);
  count = 0;
}

void loop() {
  if(!eventStreamOne->check()) {
    eventStreamOne->createEvent("testing1",1,0,0);
    delay(100);
  }
}
