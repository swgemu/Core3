/*
 * ObjectController.cpp
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#include "ObjectController.h"

#include "../../Zone.h"
#include "zone/objects/scene/SceneObject.h"

#include "../../../../server/zone/packets/object/ObjectControllerMessage.h"

ObjectController::ObjectController(Zone* zn) {
	zone = zn;
}


void ObjectController::handleObjectController(SceneObject* object, uint32 header1, uint32 header2, Message* pack) {
	switch (header2) {
	case 0xF4:
		handleSpatialChat(object, pack);
		break;

	default:
		break;
	}
}

void ObjectController::handleSpatialChat(SceneObject* object, Message* pack) {
	uint64 sender = pack->parseLong();
	uint64 target = pack->parseLong();

	UnicodeString message;
	pack->parseUnicode(message);

	SceneObject* senderObject = zone->getObject(sender);

	if (senderObject != NULL)
		senderObject->info("says " + message.toString(), true);
}

bool ObjectController::doCommand(uint32 crc, const UnicodeString& arguments) {
	switch (crc) {
	case 0x6bc77878: // String("say").hashCode();
		doSayCommand(arguments);
		break;

	default:
		doEnqueueCommand(crc, arguments);

		return true;
	}

	return true;
}

void ObjectController::doEnqueueCommand(uint32 command, const UnicodeString& arguments) {
	PlayerCreature* object = zone->getSelfPlayer();

	Locker _locker(object);

	BaseMessage* message = new ObjectControllerMessage(object->getObjectID(), 0x23, 0x116);

	message->insertInt(object->getNewActionCount());
	message->insertInt(command);
	message->insertLong(0);
	message->insertUnicode(arguments);

	object->getClient()->sendMessage(message);
}

void ObjectController::doSayCommand(const UnicodeString& msg) {
	PlayerCreature* object = zone->getSelfPlayer();

	Locker _locker(object);

	StringBuffer full;
	full << "0 " << "0 " << "0 " << "0 " << "0 " << msg.toString();

	BaseMessage* message = new ObjectControllerMessage(object->getObjectID(), 0x23, 0x116);

	message->insertInt(object->getNewActionCount());
	message->insertInt(String("spatialchatinternal").hashCode());
	message->insertLong(0);
	message->insertUnicode(full.toString());

	object->getClient()->sendMessage(message);
}

