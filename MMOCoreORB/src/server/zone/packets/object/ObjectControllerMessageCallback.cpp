/*
 * ObjectControllerMessageCallback.cpp
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#include "server/zone/objects/creature/CreatureObject.h"

#include "ObjectControllerMessageCallback.h"

UniqueReference<MessageCallbackFactory<MessageCallback* (ObjectControllerMessageCallback*), uint32>*> ObjectControllerMessageCallback::objectMessageControllerFactory;

void ObjectControllerMessageCallback::parse(Message* message) {
	priority = message->parseInt();
	type = message->parseInt();

	client->debug() << "received objc with priority 0x" << hex << priority;

	objectID = message->parseLong();

	// info(true) << "Object controller message - Priority: " << priority << " Type: " << type << " ObjectID: " << objectID;

	if (client != nullptr) {
		client->debug() << "parsing objc type 0x" << hex << type;
	}

	objectControllerCallback = objectMessageControllerFactory->createObject(type, this);

	if (objectControllerCallback == nullptr) {
		client->error() << "unregistered 0x" << hex << type << " object controller message received";

		return;
	}

	const auto& newTaskQueue = objectControllerCallback->getCustomTaskQueue();

	if (!newTaskQueue.isEmpty()) {
		setCustomTaskQueue(newTaskQueue);
	}

	try {
		objectControllerCallback->parse(message);

	} catch (const Exception& e) {
		System::out << "exception parsing ObjectControllerMessage" << e.getMessage();
		e.printStackTrace();

		throw;
	}
}

void ObjectControllerMessageCallback::run() {
	if (client == nullptr)
		return;

	ManagedReference<CreatureObject*> player = client->getPlayer();

	if (player == nullptr || objectControllerCallback == nullptr)
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
	if (objectControllerCallback != nullptr && (objectControllerCallback != this)) {
		return objectControllerCallback->getTaskName();
	} else {
		return Task::getTaskName();
	}
}
