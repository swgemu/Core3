/*
 * ShipUpdateTransformCallback.h
 *
 *  Created on: 01/09/2011
 *      Author: TheAnswer
 */

#ifndef SHIPUPDATETRANSFORMCALLBACK_H_
#define SHIPUPDATETRANSFORMCALLBACK_H_

#include "server/zone/packets/MessageCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "ShipUpdateTransformCollisionMessage.h"
#include "ShipUpdateTransformMessage.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "PackedVelocity.h"
#include "PackedRotationRate.h"
#include "PackedPosition.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/scene/UpdateTransformMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

#include "server/zone/Zone.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/objects/area/ActiveArea.h"

class ShipUpdateTransformCallback : public MessageCallback {
	uint16 shipId;

	//PackedTransform dir is multiplied by 127, positions by 4.0958748
	uint8 dirX, dirY, dirZ, dirW;
	int16 posX, posZ, posY;

	PackedPosition pos;

	//PackedVelocity
	//int16 velocitySpeed, velocityDirection;
	PackedVelocity velocity;

	//3 PackedRotationRate
	PackedRotationRate yawRate, pitchRate, rollRate;

	uint32 counter;

public:
	ShipUpdateTransformCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server), shipId(0), dirX(0), dirY(0), dirZ(0), dirW(0),
		posX(0), posZ(0), posY(0), counter(0) {
	}

	void parse(Message* message) {
		//info(message->toStringData(), true);
		shipId = message->parseShort();
		dirX = message->parseByte();
		dirY = message->parseByte();
		dirZ = message->parseByte();
		dirW = message->parseByte();
		posX = message->parseSignedShort();
		posY = message->parseSignedShort();
		posZ = message->parseSignedShort();
		velocity.parse(message); //Short velocity
		yawRate.parse(message); // int8 rate
		pitchRate.parse(message); //int8 rate
		rollRate.parse(message); //int8 rate
		counter = message->parseInt(); //int32
	}

	void run() {
		float positionMultiplier = 4.0958748f;
		float positionX = posX / positionMultiplier;
		float positionY = posY / positionMultiplier;
		float positionZ = posZ / positionMultiplier;;

		float directionX = dirX <= 127.f ? dirX / 127.f : (dirX - 255) / 127.f;
		float directionY = dirY <= 127.f ? dirY / 127.f : (dirY - 255) / 127.f;
		float directionZ = dirZ <= 127.f ? dirZ / 127.f : (dirZ - 255) / 127.f;
		float directionW = dirW <= 127.f ? dirW / 127.f : (dirW - 255) / 127.f;

		if (positionX > 8000.0f || positionX < -8000.0f || positionY > 8000.0f || positionY < -8000.0f || positionZ < -8000.0f || positionZ > 8000.0f) {
			return;
		}

		const ManagedReference<CreatureObject*> pilot = client->getPlayer();
		if (pilot == nullptr) {
			return;
		}


		const Reference<PlayerObject*> ghost = pilot->getPlayerObject();
		if (ghost == nullptr || ghost->isTeleporting()) {
			return;
		}

		ShipObject* ship = dynamic_cast<ShipObject*>(pilot->getParent().get().get());
		if (ship == nullptr || ship->getSpaceZone() == nullptr || ship->isHyperspacing()) {
			return;
		}
/*
		Logger::console.info("Directions for: " + ship->getDisplayedName(), true);
		Logger::console.info("Direction X: " + String::valueOf(dirX), true);
		Logger::console.info("Direction Y: " + String::valueOf(dirY), true);
		Logger::console.info("Direction Z: " + String::valueOf(dirZ), true);
		Logger::console.info("Direction W: " + String::valueOf(dirW), true);
		Logger::console.info("End Directions", true);
*/
		if (pilot->getSpaceZone() == nullptr) {
			pilot->setSpaceZone(ship->getSpaceZone());
		}
		Locker pLock(pilot);
		Locker cLock(ship, pilot);
//
		Vector3 collisionPoint(positionX, positionY, positionZ);
		bool collision = CollisionManager::checkShipCollision(ship, collisionPoint, collisionPoint);
//
		Quaternion direction(directionW, directionX, directionZ, directionY);
		direction.normalize();

		if (collision) {
			ship->setDirection(direction);
			ship->setMovementCounter(counter);

			auto crash = new ShipUpdateTransformCollisionMessage(ship);
			ship->broadcastMessage(crash, true);

			auto effect = new PlayClientEffectObjectMessage(ship, "clienteffect/space_collision.cef", "");
			ship->broadcastMessage(effect, true);
		} else {
			// No Collision
			ship->setMovementCounter(counter);
			bool lightUpdate = ghost->getServerMovementTimeDelta() < 3000U;

			//Logger::console.info("positionX = " + String::valueOf(positionX), true);
			auto shipMessage = new ShipUpdateTransformMessage(ship, direction.getX(), direction.getY(), direction.getZ(), direction.getW(), positionX, positionZ, positionY, velocity, yawRate, pitchRate, rollRate);
			ship->broadcastMessage(shipMessage, false);

			if (!lightUpdate) {
				ship->setDirection(direction);
				pilot->setDirection(direction);
				pilot->setPosition(positionX, positionZ, positionY);
				ship->setPosition(positionX, positionZ, positionY);
				pilot->updateZone(false);
				ghost->updateServerLastMovementStamp();
			}
			else
				pilot->updateZone(true, false);
		}
		cLock.release();
	}
};

#endif /* SHIPUPDATETRANSFORMCALLBACK_H_ */
