/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DATATRANSFORM_H_
#define DATATRANSFORM_H_

#include "ObjectControllerMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "ObjectControllerMessageCallback.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/collision/IntersectionResults.h"
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
		movementStamp = 0;
		movementCounter = 0;
		directionX = 0;
		directionY = 0;
		directionZ = 0;
		directionW = 0;
		positionX = 0;
		positionZ = 0;
		positionY = 0;
		parsedSpeed = 0;

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

	void bounceBack(SceneObject* object, ValidatedPosition& pos) {
		Vector3 teleportPoint = pos.getPosition();
		uint64 teleportParentID = pos.getParent();

		object->teleport(teleportPoint.getX(), teleportPoint.getZ(), teleportPoint.getY(), teleportParentID);
	}

	void run() {
		ManagedReference<CreatureObject*> object = cast<CreatureObject*>(client->getPlayer().get().get());
		
		if (object == NULL)
			return;

		if (object->getZone() == NULL)
			return;



		int posture = object->getPosture();

		if (!object->hasDizzyEvent() && (posture == CreaturePosture::UPRIGHT || posture == CreaturePosture::PRONE
				|| posture == CreaturePosture::DRIVINGVEHICLE || posture == CreaturePosture::RIDINGCREATURE || posture == CreaturePosture::SKILLANIMATING) ) {

			updatePosition(object);
		} else {
			object->setCurrentSpeed(0);

			object->updateLocomotion();

			ValidatedPosition pos;
			pos.update(object);

			Vector3 currentPos = pos.getPosition();
			Vector3 newPos(positionX, positionY, positionZ);

			object->setDirection(directionW, directionX, directionY, directionZ);

			if (currentPos.squaredDistanceTo(newPos) > 0.01) {
				bounceBack(object, pos);
			} else {
				ManagedReference<SceneObject*> currentParent = object->getParent();
				bool light = objectControllerMain->getPriority() != 0x23;

				if (currentParent != NULL)
					object->updateZoneWithParent(currentParent, light);
				else
					object->updateZone(light);
			}
		}

	}

	void updatePosition(CreatureObject* object) {
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

		IntersectionResults intersections;

		CollisionManager::getWorldFloorCollisions(positionX, positionY, object->getZone(), &intersections, (CloseObjectsVector*) object->getCloseObjects());

		float z = planetManager->findClosestWorldFloor(positionX, positionY, positionZ, object->getSwimHeight(), &intersections, (CloseObjectsVector*) object->getCloseObjects());

		if (z != positionZ) {
			positionZ = z;
		}

		ValidatedPosition pos;
		pos.update(object);

		if (!ghost->isPrivileged()) {
			SceneObject* inventory = object->getSlottedObject("inventory");

			if (inventory != NULL && inventory->getCountableObjectsRecursive() > inventory->getContainerVolumeLimit() + 1) {
				object->sendSystemMessage("Inventory Overloaded - Cannot Move");
				bounceBack(object, pos);
				return;
			} else if (object->isFrozen()) {
				bounceBack(object, pos);
				return;
			}
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
		bject->info(msg.toString(), true);
		return;
		}*/

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		if (playerManager == NULL)
			return;

		if (playerManager->checkSpeedHackFirstTest(object, parsedSpeed, pos, 1.1f) != 0)
			return;

		if (playerManager->checkSpeedHackSecondTest(object, positionX, positionZ, positionY, movementStamp, NULL) != 0)
			return;

		playerManager->updateSwimmingState(object, positionZ, &intersections, (CloseObjectsVector*) object->getCloseObjects());

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

		object->setCurrentSpeed(parsedSpeed);
		object->updateLocomotion();

		if (objectControllerMain->getPriority() == 0x23)
			object->updateZone(false);
		else
			object->updateZone(true);

	}
};

#endif /*DATATRANSFORM_H_*/
