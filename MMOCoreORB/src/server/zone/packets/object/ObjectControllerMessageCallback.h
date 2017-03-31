/*
 * ObjectControllerMessageCallback.h
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#ifndef OBJECTCONTROLLERMESSAGECALLBACK_H_
#define OBJECTCONTROLLERMESSAGECALLBACK_H_

#include "server/zone/MessageCallbackFactory.h"
#include "server/zone/packets/MessageCallback.h"

class ObjectControllerMessageCallback : public MessageCallback {
	uint32 priority;
	uint32 type;

	uint64 objectID;

	Reference<MessageCallback*> objectControllerCallback;
public:
	ObjectControllerMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server), priority(0), type(0), objectID(0) {

		objectControllerCallback = NULL;
	}

	static MessageCallbackFactory<MessageCallback* (ObjectControllerMessageCallback*), uint32>* objectMessageControllerFactory;

	const char* getTaskName();

	void parse(Message* message);

	void run();

	inline uint32 getPriority() {
		return priority;
	}

	inline uint32 getType() {
		return type;
	}

	inline uint64 getObjectID() {
		return objectID;
	}

};


#endif /* OBJECTCONTROLLERMESSAGECALLBACK_H_ */
