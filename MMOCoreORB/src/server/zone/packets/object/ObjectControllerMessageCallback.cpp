/*
 * ObjectControllerMessageCallback.cpp
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#include "server/zone/objects/creature/CreatureObject.h"

#include "ObjectControllerMessageCallback.h"

MessageCallbackFactory<MessageCallback* (ObjectControllerMessageCallback*), uint32>* ObjectControllerMessageCallback::objectMessageControllerFactory = NULL;

void ObjectControllerMessageCallback::parse(Message* message) {
	priority = message->parseInt();
	type = message->parseInt();

	/*StringBuffer priorityMsg;
	priorityMsg << "received objc with priority 0x" << hex << priority;
	client->getPlayer()->info(priorityMsg.toString(), true);*/

	objectID = message->parseLong();

	if (client != NULL) {
		StringBuffer objectCtrl;
		objectCtrl << "parsing objc type 0x" << hex << type;
		client->debug(objectCtrl.toString());
	}

	objectControllerCallback = objectMessageControllerFactory->createObject(type, this);

	if (objectControllerCallback == NULL) {
		StringBuffer msg;
		msg << "unregistered 0x" << hex << type << " object controller message received";

		//CreatureObject* player = client->getPlayer();
		client->error(msg.toString());
		return;
	}
	
	const auto& newTaskQueue = objectControllerCallback->getCustomTaskQueue();
	
	if (newTaskQueue.length()) {
		setCustomTaskQueue(newTaskQueue);
	}
	
	try {

		/*StringBuffer objectCtrl;
		objectCtrl << "parsing objc type 0x" << hex << type;
		client->getPlayer()->info(objectCtrl.toString(), true);*/

		objectControllerCallback->parse(message);

	} catch (Exception& e) {
		System::out << "exception parsing ObjectControllerMessage" << e.getMessage();
		e.printStackTrace();

		throw;
	}
}

void ObjectControllerMessageCallback::run() {
	if (client == NULL)
		return;

	ManagedReference<CreatureObject*> player = client->getPlayer();

	if (player == NULL || objectControllerCallback == NULL)
		return;

	Locker _locker(player);

	if (objectID != player->getObjectID()) {
		if (player->getParentID() != objectID) {
			//player->error("wrong object id in object controller message?");

			return;
		}
	}

	objectControllerCallback->run();
}

const char* ObjectControllerMessageCallback::getTaskName() {
	if (objectControllerCallback != NULL && (objectControllerCallback != this)) {
		return objectControllerCallback->getTaskName();
	} else {
		return Task::getTaskName();
	}
}
