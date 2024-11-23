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
#include "server/zone/managers/ship/ShipManager.h"
#include "server/zone/objects/ship/ShipCollisionData.h"
#include "server/zone/packets/ui/CreateClientPathMessage.h"
#endif // SHIP_TRANSFORM_DEBUG

class ShipUpdateTransformCallback : public MessageCallback {
private:
	const static bool errorLog = false;

#ifdef SHIP_TRANSFORM_DEBUG
	const static bool sendText = true;
	const static bool sendPath = true;
	const static bool drawPathRadius = false;
#endif // SHIP_TRANSFORM_DEBUG

protected:
	const static constexpr float positionMod = 1.5f;
	const static constexpr float positionScale = 8000.f / 32767.f;
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

	long deltaTime;

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

		deltaTime= 0;
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
			return;
		}

		PlayerObject* ghost = pilot->getPlayerObject();

		if (ghost == nullptr) {
			return updateError(pilot, "!ghost", false);
		}

		if (ghost->isTeleporting()) {
			return updateError(pilot, "ghost-TP", false);
		}

		ManagedReference<SceneObject*> rootParent = pilot->getRootParent();

		if (rootParent == nullptr) {
			return updateError(pilot, "!rootParent", false);
		}

		ShipObject* ship = rootParent->asShipObject();

		if (ship == nullptr|| ship->isHyperspacing()) {
			return updateError(pilot, "!ship", false);
		}

		Zone* zone = ship->getZone();

		if (zone == nullptr || !zone->isSpaceZone()) {
			return updateError(pilot, "!zone", false);
		}

		Locker pLock(pilot);
		Locker cLock(ship, pilot);

		if (ghost->getClientLastMovementStamp() == 0 && counter != 0) {
			ghost->setClientLastMovementStamp(counter);
			return synchronize(ship, pilot);
		}

		deltaTime = (long)counter - (long)ghost->getClientLastMovementStamp();

		if (deltaTime < -Transform::SYNCDELTA) {
			return updateError(pilot, "!syncDelta", true);
		}

		if (deltaTime < Transform::MINDELTA) {
			return;
		}

		if (!isPositionValid()) {
			return updateError(pilot, "!isPositionValid", true);
		}

		pilot->setSyncStamp(counter);

		if (isPositionUpdate(ship)) {
			updatePosition(ship, pilot);
		} else if (isStaticUpdate(ship)) {
			updateStatic(ship, pilot);
		}

		ghost->setClientLastMovementStamp(counter);
	}

	bool isPositionValid() const {
		if (positionX > 8000.f || positionX < -8000.f || positionY > 8000.f || positionY < -8000.f || positionZ > 8000.f || positionZ < -8000.f) {
			return false;
		}

		return true;
	}

	bool isPositionUpdate(ShipObject* ship) const {
		const Vector3& position = ship->getPosition();

		if (positionX != position.getX() || positionY != position.getY() || positionZ != position.getZ()) {
			return true;
		}

		return false;
	}

	bool isStaticUpdate(ShipObject* ship) {
		const Quaternion* direction = ship->getDirection();

		if (directionW != direction->getW() || directionX != direction->getX() || directionY != direction->getY() || directionZ != direction->getZ()) {
			return true;
		}

		if (deltaTime > Transform::MAXDELTA) {
			return true;
		}

		return false;
	}

	void updateCollision(ShipObject* ship, CreatureObject* pilot, const Vector3& collisionPoint) {
#ifdef SHIP_TRANSFORM_DEBUG
		sendDebug(pilot, ship, "updateCollision", collisionPoint);
#endif // SHIP_TRANSFORM_DEBUG

		updateTransform(ship, pilot, collisionPoint, true);
		broadcastTransform(ship, pilot, collisionPoint);

		auto collide = new ShipUpdateTransformCollisionMessage(ship);
		ship->broadcastMessage(collide, false);

		auto effect = new PlayClientEffectObjectMessage(ship, "clienteffect/space_collision.cef", "");
		ship->broadcastMessage(effect, false);
	}

	void updatePosition(ShipObject* ship, CreatureObject* pilot) {
		Vector3 position(positionX, positionY, positionZ);
		/*Vector3 collisionPoint;

		if (CollisionManager::checkShipCollision(ship, position, collisionPoint)) {
			return updateCollision(ship, pilot, collisionPoint);
		}*/

		Vector3 nextPosition = (position - ship->getPosition()) + position;

#ifdef SHIP_TRANSFORM_DEBUG
		sendDebug(pilot, ship, "updatePosition", nextPosition);
#endif // SHIP_TRANSFORM_DEBUG

		updateTransform(ship, pilot, position, false);
		broadcastTransform(ship, pilot, nextPosition);
	}

	void updateStatic(ShipObject* ship, CreatureObject* pilot) {
		const Vector3& position = ship->getPosition();

#ifdef SHIP_TRANSFORM_DEBUG
		sendDebug(pilot, ship, "updateStatic", position);
#endif // SHIP_TRANSFORM_DEBUG

		updateTransform(ship, pilot, position, false);
		broadcastTransform(ship, pilot, position);
	}

	void synchronize(ShipObject* ship, CreatureObject* pilot) {
		const Vector3& position = ship->getPosition();

#ifdef SHIP_TRANSFORM_DEBUG
		sendDebug(pilot, ship, "synchronize", position);
#endif // SHIP_TRANSFORM_DEBUG

		updateTransform(ship, pilot, position, true);
	}

	void updateTransform(ShipObject* ship, CreatureObject* pilot, const Vector3& position, bool reorthonormalize) {
		Quaternion direction(directionW, directionX, directionY, directionZ);

		if (reorthonormalize) {
			direction.normalize();
		}

		if (ship->getDirectionW() != direction.getW() || ship->getDirectionX() != direction.getX() || ship->getDirectionY() != direction.getY() || ship->getDirectionZ() != direction.getZ()) {
			ship->setRotationMatrix(direction);
		}

		float speed = velocity.getSpeed();

		if (ship->getCurrentSpeed() != speed) {
			ship->setCurrentSpeed(speed);
			ship->updateSpeedRotationValues(true);
		}

		ship->setPosition(position.getX(), position.getZ(), position.getY());
		ship->setDirection(direction);

		bool lightUpdate = priority != 0x23;
		ship->updateZone(lightUpdate, false);

		if (reorthonormalize) {
			auto data = new DataTransform(ship);
			ship->sendMembersBaseMessage(data);
		}
	}

	void broadcastTransform(ShipObject* ship, CreatureObject* pilot, const Vector3& position) {
		auto shipCov = ship->getCloseObjects();

		if (shipCov == nullptr) {
			return;
		}

		SortedVector<ManagedReference<TreeEntry*> > closePlayers;
		shipCov->safeCopyReceiversTo(closePlayers, CloseObjectsVector::PLAYERTYPE);

		for (int i = 0; i < closePlayers.size(); ++i) {
			auto playerEntry = closePlayers.get(i).castTo<CreatureObject*>();

			if (playerEntry == nullptr) {
				continue;
			}

			uint32 syncStamp = playerEntry->getSyncStamp();

			if (velocity.getSpeed() > 0.f) {
				auto data = new ShipUpdateTransformMessage(ship, position, velocity, yawRate, pitchRate, rollRate, syncStamp);
				playerEntry->sendMessage(data);
			} else {
				auto data = new ShipUpdateTransformMessage(ship, syncStamp);
				playerEntry->sendMessage(data);
			}
		}
	}

	void updateError(CreatureObject* pilot, const String& message, bool bounceBack) {
		if (!message.isEmpty()) {
			if (message.beginsWith("@")) {
				pilot->sendSystemMessage(message);
			}

			if (errorLog && message.beginsWith("!")) {
				pilot->info(true) << " ShipUpdateTransformCallback: " << message;
			}
		}

		auto rootParent = pilot->getRootParent();

		if (rootParent == nullptr || !rootParent->isShipObject()) {
			return;
		}

		auto ship = rootParent->asShipObject();

		if (ship == nullptr) {
			return;
		}

#ifdef SHIP_TRANSFORM_DEBUG
		sendDebug(pilot, ship, "error: " + message, ship->getPosition());
#endif // SHIP_TRANSFORM_DEBUG

		if (bounceBack) {
			const Vector3& position = ship->getPosition();

			rootParent->teleport(position.getX(), position.getZ(), position.getY(), 0);
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

		msg << "Transform:  " << message << endl
			<< " ShipId:    " << shipId << endl
			<< " Position:  " << positionX  << ", " << positionZ  << ", " << positionY << endl
			<< " Direction: " << directionW  << ", " << directionX  << ", " << directionY << ", " << directionZ << endl
			<< " Velocity:  " << velocity.getSpeed() << "/" << ship->getActualMaxSpeed() << endl
			<< " yawRate:   " << yawRate.get() << endl
			<< " pitchRate: " << pitchRate.get() << endl
			<< " rollRate:  " << rollRate.get() << endl
			<< " syncStamp: " << ship->getSyncStamp() << endl
			<< " counter:   " << counter << endl
			<< "--------------------------------";

		pilot->sendSystemMessage(msg.toString());
	}

	void sendDebugPath(CreatureObject* pilot, ShipObject* ship, const Vector3& nextPosition) {
		Vector3 lastPosition = ship->getPosition();
		Vector3 thisPosition = Vector3(positionX, positionY, positionZ);

		auto path = new CreateClientPathMessage();
		path->addCoordinate(lastPosition);
		path->addCoordinate(thisPosition);

		auto targetData = ShipManager::instance()->getCollisionData(ship);
		if (targetData == nullptr) {
			return;
		}

		Matrix4 targetRotation;
		targetRotation.setRotationMatrix(ship->getDirection()->getConjugate().toMatrix3());

		float targetRadius = targetData->getBoundingSphere().getRadius();

		if (targetData->getVolumeType() == ShipCollisionData::CollisionVolumeType::MESH) {
			path->drawBoundingSphere(thisPosition, targetRotation, targetData->getBoundingSphere());
		}

		if (targetData->getVolumeType() == ShipCollisionData::CollisionVolumeType::BOX) {
			path->drawBoundingSphere(thisPosition, targetRotation, targetData->getBoundingSphere());
			path->drawBoundingBox(thisPosition, targetRotation, targetData->getChassisBox());
		}

		if (targetData->getVolumeType() == ShipCollisionData::CollisionVolumeType::RADIUS) {
			path->drawBoundingSphere(thisPosition, targetRotation, targetData->getBoundingSphere());
			path->drawBoundingSphere(thisPosition, targetRotation, targetData->getChassisSphere());
		}

		path->addCoordinate(thisPosition);
		path->addCoordinate(nextPosition);
		ship->broadcastMessage(path, false);
	}
#endif // SHIP_TRANSFORM_DEBUG
};

#endif /* SHIPUPDATETRANSFORMCALLBACK_H_ */
