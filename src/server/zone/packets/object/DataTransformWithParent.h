/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef DATATRANSFORMWITHPARENT_H_
#define DATATRANSFORMWITHPARENT_H_

#include "ObjectControllerMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"

class DataTransformWithParent : public ObjectControllerMessage {
public:
	DataTransformWithParent(CreatureObject* creo)
			: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0xF1) {

		insertInt(creo->getMovementCounter());

		insertLong(creo->getParentID());

		insertFloat(creo->getDirectionX());
		insertFloat(creo->getDirectionY());
		insertFloat(creo->getDirectionZ());
		insertFloat(creo->getDirectionW());

		insertFloat(creo->getPositionX());
		insertFloat(creo->getPositionZ());
		insertFloat(creo->getPositionY());

		insertInt(0);
	}

};

class DataTransformWithParentCallback : public MessageCallback {
	uint32 movementStamp;
	uint32 movementCounter;
	uint64 parent;

	float directionX, directionY, directionZ, directionW;
	float positionX, positionZ, positionY;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	DataTransformWithParentCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
	}

	void parse(Message* message) {
		movementStamp = message->parseInt();
		movementCounter = message->parseInt();

		parent = message->parseLong();

		directionW = message->parseFloat();
		directionX = message->parseFloat();
		directionY = message->parseFloat();
		directionZ = message->parseFloat();

		positionX = message->parseFloat();
		positionZ = message->parseFloat();
		positionY = message->parseFloat();
	}

	void run() {
		PlayerCreature* object = (PlayerCreature*) client->getPlayer();

		if (positionX > 1024.0f || positionX < -1024.0f || positionY > 1024.0f || positionY < -1024.0f) {
			StringBuffer msg;
			msg << "position out of bounds cell:[" << parent << "]";
			object->error(msg.toString());
		}

		if (object->getZone() == NULL)
			return;

		/*StringBuffer movementMsg;
		movementMsg << "received movement update 0x:" << hex << movementCounter;
		object->info(movementMsg.toString(), true);

		uint32 objectMovementCounter = object->getMovementCounter();

		if (objectMovementCounter > movementCounter) { // we already parsed an more updated movement counter
			StringBuffer msg;
			msg << "trying to parse movement update: 0x" << hex << movementCounter << " but we already parsed 0x" << hex << objectMovementCounter;
			object->info(msg.toString(), true);
			return;
		}*/

		/*if (object->isMounted())
				object->dismount(true, true);*/

		ManagedReference<SceneObject*> newParent = server->getZoneServer()->getObject(parent, true);

		if (newParent == NULL)
			return;

		if (!newParent->isCellObject())
			return;

		object->setMovementCounter(movementCounter);
		object->setDirection(directionW, directionX, directionY, directionZ);
		object->setPosition(positionX, positionZ, positionY);

		//TODO: add improved Speed Hack checks

		if (objectControllerMain->getPriority() == 0x23)
			object->updateZoneWithParent(newParent, false);
		else
			object->updateZoneWithParent(newParent, true);

	}
};


#endif /*DATATRANSFORMWITHPARENT_H_*/
