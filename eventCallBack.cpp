#include "eventCallBack.h"
#include "eventStream.h"

bool eventOutgoing::handler(const char *payload, const unsigned int deviceTypeID, const unsigned int deviceID) {
	char buffer[20];
	sprintf(buffer,"%l",broadcast());
	stream->createEvent(buffer,outgoingMessageID,0,0);
}

eventOutgoing::eventOutgoing(
	eventStream *r, 
	const unsigned long (*f)(void), 
	const unsigned int ogm,
	const unsigned int m, 
	const unsigned int dt, 
	const unsigned int d) : 
	eventHandler(r,m,dt,d) {
		outgoingMessageID = ogm;
		broadcast = f;
}

eventOutgoing::eventOutgoing(
	eventStream *r, 
	const unsigned long (*f)(void),
	unsigned int ogm, 
	unsigned int m) : 
	eventHandler(r,m) {
		outgoingMessageID = ogm;
		broadcast = f;
}

bool eventIncoming::handler(const char *payload, const unsigned int deviceTypeID, const unsigned int deviceID) {
	respond(atol(payload));	
}

eventIncoming::eventIncoming(
	eventStream *r, 
	void (*f)(unsigned long),
	const unsigned int m, 
	const unsigned int dt, 
	const unsigned int d) : 
	eventHandler(r,m,dt,d) {
		respond = f;
}

eventIncoming::eventIncoming(
	eventStream *r, 
	void (*f)(unsigned long), 
	const unsigned int m) :
	eventHandler(r,m) {
		respond = f;
}