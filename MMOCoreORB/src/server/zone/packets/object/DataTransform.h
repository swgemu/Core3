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

#ifndef DATATRANSFORM_H_
#define DATATRANSFORM_H_

#include "ObjectControllerMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "ObjectControllerMessageCallback.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/Zone.h"

class DataTransform : public ObjectControllerMessage {
public:
	DataTransform(SceneObject* creo)
			: ObjectControllerMessage(creo->getObjectID(), 0x1B, 0x71) {

		insertInt(creo->getMovementCounter());

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

class DataTransformCallback : public MessageCallback {
	uint32 movementStamp;
	uint32 movementCounter;

	float directionX, directionY, directionZ, directionW;
	float positionX, positionZ, positionY;
	float parsedSpeed;

	ObjectControllerMessageCallback* objectControllerMain;
	
//	taskqueue = 3;
public:
	DataTransformCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {

		objectControllerMain = objectControllerCallback;
		
		taskqueue = 3;
		
		ManagedReference<SceneObject*> player = client->getPlayer();
		
		if (player != NULL) {
			Zone* zone = player->getLocalZone();
			
			if (zone != NULL) {
				String zoneName = zone->getZoneName();
			
				if (zoneName == "corellia")
					taskqueue = 4;
				else if (zoneName == "tatooine")
					taskqueue = 5;
				else if (zoneName == "naboo")
					taskqueue = 6;
			}
		}
	}

	void parse(Message* message) {
		movementStamp = message->parseInt();
		movementCounter = message->parseInt();

		directionX = message->parseFloat();
		directionY = message->parseFloat();
		directionZ = message->parseFloat();
		directionW = message->parseFloat();

		positionX = message->parseFloat();
		positionZ = message->parseFloat();
		positionY = message->parseFloat();

		parsedSpeed = message->parseFloat();

		//client->info(message->toStringData(), true);

		//info("datatransform", true);
	}

	void run() {
		ManagedReference<CreatureObject*> object = cast<CreatureObject*>(client->getPlayer().get().get());
		
		if (object == NULL)
			return;

		if (object->getZone() == NULL)
			return;

		PlayerObject* ghost = object->getPlayerObject();

		if (isnan(positionX) || isnan(positionY) || isnan(positionZ))
			return;

		if (isinf(positionX) || isinf(positionY) || isinf(positionZ))
			return;

		if (ghost->isTeleporting())
			return;

		/*if (!object->isInQuadTree())
			return;*/

		if (positionX > 7680.0f || positionX < -7680.0f || positionY > 7680.0f || positionY < -7680.0f) {
			StringBuffer msg;
			msg << "position out of bounds";
			object->error(msg.toString());

			return;
		}	

		/*float floorHeight = CollisionManager::instance()->getWorldFloorCollision(positionX, positionY, object->getZone(), true);

		printf("received height: %f calculated height: %f\n", positionZ, floorHeight); */

		ManagedReference<PlanetManager*> planetManager = object->getZone()->getPlanetManager();

		if (planetManager == NULL)
			return;

		float z = planetManager->findClosestWorldFloor(positionX, positionY, positionZ);

		if (z != positionZ) {
			positionZ = z;
		}

		ValidatedPosition pos;
		pos.update(object);

		if (object->isFrozen()) {
			Vector3 teleportPoint = pos.getPosition();
			uint64 teleportParentID = pos.getParent();

			object->teleport(teleportPoint.getX(), teleportPoint.getZ(), teleportPoint.getY(), teleportParentID);

			return;
		}

		/*

		if (CollisionManager::instance()->checkMovementCollision(object, positionX, positionZ, positionY, object->getZone())) {
			Vector3 teleportPoint = pos.getPosition();
			uint64 teleportParentID = pos.getParent();

			object->teleport(teleportPoint.getX(), teleportPoint.getZ(), teleportPoint.getY(), teleportParentID);

			object->info("position update inside mesh detected pos[" + String::valueOf(positionX)
				+ ", " + String::valueOf(positionZ) + ", " + String::valueOf(positionY) + "]", true);
			return;
		}

		*/
		uint32 objectMovementCounter = object->getMovementCounter();

		/*if (objectMovementCounter > movementCounter) { // we already parsed an more updated movement counter
			StringBuffer msg;
			msg << "trying to parse movement update: 0x" << hex << movementCounter << " but we already parsed 0x" << hex << objectMovementCounter;
			object->info(msg.toString(), true);
			return;
		}*/

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		if (playerManager == NULL)
			return;

		if (playerManager->checkSpeedHackFirstTest(object, parsedSpeed, pos, 1.1f) != 0)
			return;

		if (playerManager->checkSpeedHackSecondTest(object, positionX, positionZ, positionY, movementStamp, NULL) != 0)
			return;

		playerManager->updateSwimmingState(object, positionZ);

		object->setMovementCounter(movementCounter);
		//object->setDirection(directionW, directionX, directionY, directionZ);
		
		float oldX = object->getPositionX();
		float oldY = object->getPositionY();
		float oldZ = object->getPositionZ();
		
		float dirw = object->getDirectionW();
		float dirz = object->getDirectionZ();
		float diry = object->getDirectionY();
		float dirx = object->getDirectionX();
		
		ghost->setClientLastMovementStamp(movementStamp);
		
		if (oldX == positionX && oldY == positionY && oldZ == positionZ && 
			dirw == directionW && dirz == directionZ && dirx == directionX && diry == directionY) {
			
			return;
		}

		/*StringBuffer degrees;
		degrees << "angle: " << object->getDirectionAngle();
		degrees << " special angle: " << object->getSpecialDirectionAngle();
		object->info(degrees.toString(), true);*/

		object->setPosition(positionX, positionZ, positionY);
//		ghost->setClientLastMovementStamp(movementStamp);
		
		object->setDirection(directionW, directionX, directionY, directionZ);

		/*StringBuffer posMsg;
		posMsg << "setting position: " << positionX << " " << positionZ << " " << positionY;
		object->info(posMsg.toString(), true);*/

		if (objectControllerMain->getPriority() == 0x23)
			object->updateZone(false);
		else
			object->updateZone(true);

	}
};

#endif /*DATATRANSFORM_H_*/
