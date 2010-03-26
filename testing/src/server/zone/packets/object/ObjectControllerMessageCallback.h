/*
 * ObjectControllerMessageCallback.h
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#ifndef OBJECTCONTROLLERMESSAGECALLBACK_H_
#define OBJECTCONTROLLERMESSAGECALLBACK_H_

#include "engine/util/ObjectFactory.h"

#include "../MessageCallback.h"

#include "server/zone/managers/objectcontroller/ObjectController.h"

class ObjectControllerMessageCallback : public MessageCallback {
	uint32 priority;
	uint32 type;

	uint64 objectID;

	MessageCallback* objectControllerCallback;
public:
	ObjectControllerMessageCallback(ZoneClientSession* client, ZoneProcessServerImplementation* server) :
		MessageCallback(client, server) {

		objectControllerCallback = NULL;
	}

	static ObjectFactory<MessageCallback* (ObjectControllerMessageCallback*), uint32>* objectMessageControllerFactory;

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
