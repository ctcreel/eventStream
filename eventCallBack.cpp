#include "eventCallBack.h"
#include "eventStream.h"

bool eventOutgoing::handler(const char *payload, const unsigned int deviceTypeID, const unsigned int deviceID) {
	char buffer[20];
	unsigned long v = broadcast();
	sprintf(buffer,"%lu",v);
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
	unsigned long p;
	p = atol(payload);
	Serial.print("payload is ");
	Serial.print(payload);
	Serial.print(" | ");
	Serial.println(p);
	respond(p);	
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