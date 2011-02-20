/*
 * ObjectControllerMessageCallback.cpp
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#include "server/zone/objects/scene/SceneObject.h"

#include "ObjectControllerMessageCallback.h"

MessageCallbackFactory<MessageCallback* (ObjectControllerMessageCallback*), uint32>* ObjectControllerMessageCallback::objectMessageControllerFactory = NULL;

void ObjectControllerMessageCallback::parse(Message* message) {
	priority = message->parseInt();
	type = message->parseInt();

	/*StringBuffer priorityMsg;
	priorityMsg << "received objc with priority 0x" << hex << priority;
	client->getPlayer()->info(priorityMsg.toString(), true);*/

	objectID = message->parseLong();

	StringBuffer objectCtrl;
	objectCtrl << "parsing objc type 0x" << hex << type;
	client->info(objectCtrl.toString());

	objectControllerCallback = objectMessageControllerFactory->createObject(type, this);

	if (objectControllerCallback == NULL) {
		StringBuffer msg;
		msg << "unregistered 0x" << hex << type << " object controller message received";

		//SceneObject* player = client->getPlayer();
		client->error(msg.toString());
		return;
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
	} catch (...) {
		System::out << "unknown exception caught in ObjectControllerMessageCallback::parse";
		throw;
	}

}

void ObjectControllerMessageCallback::run() {
	ManagedReference<SceneObject*> player = client->getPlayer();

	if (player == NULL || objectControllerCallback == NULL)
		return;

	try {
		Locker _locker(player);

		if (objectID != player->getObjectID()) {
			player->error("wrong object id in object controller message?");

			return;
		}

		objectControllerCallback->run();

	} catch (Exception& e) {

		System::out << "exception executing ObjectControllerMessage" << e.getMessage();
		e.printStackTrace();
	} catch (...) {

		System::out << "unknown exception caught in ObjectControllerMessageCallback::execute";
	}
}
