#ifndef eventCallBack_h
#define eventCallBack_h

#include "eventHandler.h"

class eventOutgoing : private eventHandler {
  private:
    const unsigned long (*broadcast)(void);
    unsigned int outgoingMessageID;
    virtual bool handler(const char *payload, const unsigned int deviceTypeID, const unsigned int deviceID);
  public:
    eventOutgoing(
       	eventStream *r, 
    	const unsigned long (*f)(void),
    	const unsigned int outgoingMessageID,
    	const unsigned int messageTypeID, 
    	const unsigned int deviceTypeID, 
    	const unsigned int deviceID=0);
    	
    eventOutgoing(
       	eventStream *r, 
    	const unsigned long (*f)(void), 
    	const unsigned int outgoingMessageID,
    	const unsigned int messageTypeID);
};

class eventIncoming : private eventHandler {
  private:
    void (*respond)(unsigned long);
    virtual bool handler(const char *payload, const unsigned int deviceTypeID, const unsigned int deviceID);
  public:
    eventIncoming(
	    eventStream *r, 
    	void (*f)(unsigned long), 
    	const unsigned int messageTypeID, 
    	const unsigned int deviceTypeID, 
    	const unsigned int deviceID=0);
    	
    eventIncoming(
    	eventStream *r,
    	void (*f)(unsigned long),
    	const unsigned int messageTypeID);
};

#endif