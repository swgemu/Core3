/*
 * ObjectControllerMessageCallback.cpp
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#include "server/zone/objects/scene/SceneObject.h"

#include "ObjectControllerMessageCallback.h"

ObjectFactory<MessageCallback* (ObjectControllerMessageCallback*), uint32>* ObjectControllerMessageCallback::objectMessageControllerFactory = NULL;

void ObjectControllerMessageCallback::parse(Message* message) {
	priority = message->parseInt();
	type = message->parseInt();

	/*StringBuffer priorityMsg;
	priorityMsg << "received objc with priority 0x" << hex << priority;
	client->getPlayer()->info(priorityMsg.toString(), true);*/

	objectID = message->parseLong();

	objectControllerCallback = objectMessageControllerFactory->createObject(type, this);

	if (objectControllerCallback == NULL) {
		StringBuffer msg;
		msg << "unregistered 0x" << hex << type << " object controller message received\n";

		SceneObject* player = client->getPlayer();
		player->error(msg.toString());
		return;
	}

	try {

		objectControllerCallback->parse(message);

	} catch (Exception& e) {
		System::out << "exception parsing ObjectControllerMessage" << e.getMessage();
		e.printStackTrace();

		delete objectControllerCallback;
		objectControllerCallback = NULL;
		throw;
	} catch (...) {
		System::out << "unknown exception caught in ObjectControllerMessageCallback::parse";
		delete objectControllerCallback;
		objectControllerCallback = NULL;
		throw;
	}

}

void ObjectControllerMessageCallback::run() {
	ManagedReference<SceneObject*> player = client->getPlayer();

	if (player == NULL)
		return;

	try {
		player->wlock();


		if (objectID != player->getObjectID()) {
			player->error("wrong object id in object controller message?");
			player->unlock();

			return;
		}

		if (objectControllerCallback != NULL)
			objectControllerCallback->run();

		player->unlock();

	} catch (Exception& e) {
		player->unlock();

		System::out << "exception executing ObjectControllerMessage" << e.getMessage();
		e.printStackTrace();
	} catch (...) {
		player->unlock();

		System::out << "unknown exception caught in ObjectControllerMessageCallback::execute";
	}
}
