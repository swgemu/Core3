/*
 * ShipUpdateTransformCallback.h
 *
 *  Created on: 01/09/2011
 *      Author: TheAnswer
 */

#ifndef SHIPUPDATETRANSFORMCALLBACK_H_
#define SHIPUPDATETRANSFORMCALLBACK_H_

//#define SHIP_TRANSFORM_DEBUG

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/packets/MessageCallback.h"
#include "server/zone/packets/object/PlayClientEffectObjectMessage.h"
#include "server/zone/packets/ship/ShipUpdateTransformCollisionMessage.h"
#include "server/zone/packets/ship/ShipUpdateTransformMessage.h"
#include "server/zone/packets/ship/PackedVelocity.h"
#include "server/zone/packets/ship/PackedRotationRate.h"

#ifdef SHIP_TRANSFORM_DEBUG
#include "server/zone/packets/ui/CreateClientPathMessage.h"
#include "server/zone/packets/object/ShowFlyText.h"
#endif // SHIP_TRANSFORM_DEBUG

class ShipUpdateTransformCallback : public MessageCallback {
private:
	const static bool errorLog = false;

#ifdef SHIP_TRANSFORM_DEBUG
	const static bool sendText = true;
	const static bool sendPath = true;
#endif // SHIP_TRANSFORM_DEBUG

protected:
	const static constexpr float positionScale = 8000.f / 32768.f;
	const static constexpr float directionScale = 1.f / 127.f;

	uint16 shipId;

	int8 dirX;
	int8 dirY;
	int8 dirZ;
	int8 dirW;

	int16 posX;
	int16 posZ;
	int16 posY;

	PackedVelocity velocity;
	PackedRotationRate yawRate;
	PackedRotationRate pitchRate;
	PackedRotationRate rollRate;

	uint32 counter;

	float positionX;
	float positionY;
	float positionZ;

	float directionX;
	float directionY;
	float directionZ;
	float directionW;

public:
	ShipUpdateTransformCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server) {
		shipId = 0;

		dirX = 0;
		dirY = 0;
		dirZ = 0;
		dirW = 0;

		posX = 0;
		posZ = 0;
		posY = 0;

		counter = 0;

		positionX = 0;
		positionZ = 0;
		positionY = 0;

		directionX = 0;
		directionY = 0;
		directionZ = 0;
		directionW = 0;
	}

	void parse(Message* message) {
		shipId = message->parseShort();

		dirW = message->parseSignedByte();
		dirX = message->parseSignedByte();
		dirY = message->parseSignedByte();
		dirZ = message->parseSignedByte();

		directionW = dirW * directionScale;
		directionX = dirX * directionScale;
		directionY = dirY * directionScale;
		directionZ = dirZ * directionScale;

		posX = message->parseSignedShort();
		posZ = message->parseSignedShort();
		posY = message->parseSignedShort();

		positionX = posX * positionScale;
		positionY = posY * positionScale;
		positionZ = posZ * positionScale;

		velocity.parse(message);
		yawRate.parse(message);
		pitchRate.parse(message);
		rollRate.parse(message);

		counter = message->parseInt();
	}

	void run() {
		ManagedReference<CreatureObject*> pilot = client->getPlayer();
		if (pilot == nullptr) {
			return sendError("!pilot");
		}

		PlayerObject* ghost = pilot->getPlayerObject();
		if (ghost == nullptr || ghost->isTeleporting()) {
			return sendError("!ghost");
		}

		ManagedReference<SceneObject*> parent = pilot->getParent().get();
		if (parent == nullptr) {
			return sendError("!parent");
		}

		ShipObject* ship = parent->asShipObject();
		if (ship == nullptr|| ship->isHyperspacing()) {
			return sendError("!ship");
		}

		SpaceZone* zone = ship->getSpaceZone();
		if (zone == nullptr) {
			return sendError("!zone");
		}

		if (!isPositionValid()) {
			return sendError("!isPositionValid");
		}

		Locker pLock(pilot);
		Locker cLock(ship, pilot);

		if (ship->getMovementCounter() == 0) {
			return synchronize(ship, pilot);
		}

		Vector3 targetPosition = Vector3(positionX, positionY, positionZ);
		Vector3 collisionPoint;

		if (CollisionManager::checkShipCollision(ship, targetPosition, collisionPoint)) {
			return updateCollision(ship, pilot);
		}

		updatePosition(ship, pilot);
	}

	bool isPositionValid() const {
		if (positionX > 8000.f || positionX < -8000.f || positionY > 8000.f || positionY < -8000.f || positionZ > 8000.f || positionZ < -8000.f) {
			return false;
		}

		return true;
	}

	void updatePosition(ShipObject* ship, CreatureObject* pilot) {
#ifdef SHIP_TRANSFORM_DEBUG
		sendDebug(pilot, ship, "updatePosition", Vector3(positionX, positionY, positionZ));
#endif // SHIP_TRANSFORM_DEBUG

		Quaternion direction(directionW, directionX, directionY, directionZ);

		ship->setPosition(positionX, positionZ, positionY);
		ship->setMovementCounter(counter);
		ship->setDirection(direction);
		ship->updateZone(true, false);

		if (velocity.speed != 0.f) {
			auto data = new ShipUpdateTransformMessage(ship, velocity, yawRate, pitchRate, rollRate);
			ship->broadcastMessage(data, false);
		} else {
			auto data = new ShipUpdateTransformMessage(ship);
			ship->broadcastMessage(data, false);
		}

		auto ghost = pilot->getPlayerObject();
		if (ghost == nullptr) {
			return;
		}

		ghost->setClientLastMovementStamp(counter);
	}

	void synchronize(ShipObject* ship, CreatureObject* pilot) {
#ifdef SHIP_TRANSFORM_DEBUG
		sendDebug(pilot, ship, "synchronize", Vector3(positionX, positionY, positionZ));
#endif // SHIP_TRANSFORM_DEBUG

		if (pilot->getSpaceZone() == nullptr && ship->getSpaceZone() != nullptr) {
			pilot->setSpaceZone(ship->getSpaceZone());
		}

		Quaternion direction = *ship->getDirection();
		direction.normalize();

		ship->setMovementCounter(counter);
		ship->setDirection(direction);

		auto data = new DataTransform(ship);
		pilot->sendMessage(data);
	}

	void updateCollision(ShipObject* ship, CreatureObject* pilot) {
#ifdef SHIP_TRANSFORM_DEBUG
		sendDebug(pilot, ship, "updateCollision", Vector3(positionX, positionY, positionZ));
#endif // SHIP_TRANSFORM_DEBUG

		Quaternion direction(directionW, directionX, directionY, directionZ);
		direction.normalize();

		ship->setMovementCounter(counter);
		ship->setDirection(direction);

		auto collide = new ShipUpdateTransformCollisionMessage(ship);
		pilot->broadcastMessage(collide, true);

		auto effect = new PlayClientEffectObjectMessage(ship, "clienteffect/space_collision.cef", "");
		pilot->broadcastMessage(effect, true);
	}

	void sendError(const String& message) {
		if (errorLog) {
			info(true) << "ShipUpdateTransformCallback: " << message;
		}
	}

#ifdef SHIP_TRANSFORM_DEBUG
	void sendDebug(CreatureObject* pilot, ShipObject* ship, const String& message, const Vector3& position) {
		if (sendText) {
			sendDebugMessage(pilot, ship, message, position);
		}

		if (sendPath) {
			sendDebugPath(pilot, ship, position);
		}
	}

	void sendDebugMessage(CreatureObject* pilot, ShipObject* ship, const String& message, const Vector3& position) {
		StringBuffer msg;

		msg << "Transform:   " << message << endl
			<< " ShipId:     " << shipId << endl
			<< " Position:   " << positionX  << ", " << positionZ  << ", " << positionY << endl
			<< " Direction:  " << directionW  << ", " << directionX  << ", " << directionY << ", " << directionZ << endl
			<< " Velocity:   " << velocity.get().getX() << ", " << velocity.get().getY() << ", " << velocity.get().getZ() << endl
			<< " yawRate:    " << yawRate.get() << endl
			<< " pitchRate:  " << pitchRate.get() << endl
			<< " rollRate:   " << rollRate.get() << endl
			<< " syncStamp:  " << counter << endl
			<< "--------------------------------";

		pilot->sendSystemMessage(msg.toString());
	}

	void sendDebugPath(CreatureObject* pilot, ShipObject* ship, const Vector3& newPosition) {
		Vector3 shipPosition = ship->getPosition();

		auto path = new CreateClientPathMessage();
		path->addCoordinate(shipPosition.getX(), shipPosition.getZ(), shipPosition.getY());
		path->addCoordinate(positionX, positionZ, positionY);
		path->addCoordinate(newPosition.getX(), newPosition.getZ(), newPosition.getY());

		pilot->sendMessage(path);
	}
#endif // SHIP_TRANSFORM_DEBUG
};

#endif /* SHIPUPDATETRANSFORMCALLBACK_H_ */
