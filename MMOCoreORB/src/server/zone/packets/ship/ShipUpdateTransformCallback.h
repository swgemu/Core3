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
#include "server/zone/objects/ship/ShipObject.h"

#include "server/zone/Zone.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/objects/area/ActiveArea.h"

class ShipUpdateTransformCallback : public MessageCallback {
	uint16 shipId;

	//PackedTransform dir is multiplied by 127, positions by 4.0958748
	uint8 dirX, dirY, dirZ, dirW;
	Vector3 position;
	PackedVelocity velocity;
	PackedRotationRate yawRate, pitchRate, rollRate;

	uint32 counter;

public:
	ShipUpdateTransformCallback(ZoneClientSession* client, ZoneProcessServer* server) : MessageCallback(client, server) {
	}

	void parse(Message* message) {
		shipId = message->parseShort();
		dirX = message->parseByte();
		dirY = message->parseByte();
		dirZ = message->parseByte();
		dirW = message->parseByte();

		PackedPosition pos;
		pos.parse(message);
		Vector3 loc(pos.get());

		position.setX(loc.getX());
		position.setZ(loc.getY());
		position.setY(loc.getZ());

		velocity.parse(message);

		yawRate.parse(message);
		pitchRate.parse(message);
		rollRate.parse(message);
		counter = message->parseInt();
	}

	void run() {
		Quaternion direction(dirW, dirX, dirY, dirZ);

		/*info(true) << "ShipUpdateTransformCallback::run";

		StringBuffer callMsg;
		callMsg << "Callback data: " << shipId << "\n";
		callMsg << "Dir W: " << dirW << "\n";
		callMsg << "Dir X: " << dirX << "\n";
		callMsg << "Dir Y: " << dirY << "\n";
		callMsg << "Dir Z: " << dirZ << "\n";

		callMsg << "Pos X: " << position.getX() << "\n";
		callMsg << "Pos Z: " << position.getZ() << "\n";
		callMsg << "Pos Y: " << position.getY() << "\n";

		callMsg << "Velocity: " << velocity.get().toString() << "\n";
		info(true) << callMsg.toString();*/

		if (position.getX() > 8000.0f || position.getX() < -8000.0f || position.getY() > 8000.0f || position.getY() < -8000.0f || position.getZ() < -8000.0f || position.getZ() > 8000.0f) {
			info(true) << "ShipUpdateTransformCallback -- FAIL 1";
			return;
		}

		const ManagedReference<CreatureObject*> pilot = client->getPlayer();

		if (pilot == nullptr) {
			info(true) << "ShipUpdateTransformCallback -- FAIL 2";
			return;
		}

		const Reference<PlayerObject*> ghost = pilot->getPlayerObject();

		if (ghost == nullptr || ghost->isTeleporting()) {
			info(true) << "ShipUpdateTransformCallback -- FAIL 3";
			return;
		}

		ShipObject* ship = dynamic_cast<ShipObject*>(pilot->getParent().get().get());

		if (ship == nullptr) {
			info(true) << "ShipUpdateTransformCallback -- FAIL 4";
			return;
		}

		if (ship->getSpaceZone() == nullptr) {
			info(true) << "ShipUpdateTransformCallback -- FAIL 5";
			return;
		}

		if (ship->isHyperspacing()) {
			info(true) << "ShipUpdateTransformCallback -- FAIL 6";
			return;
		}

		/*StringBuffer dirMsg;
		dirMsg << "Directions for: " + ship->getDisplayedName() << "\n";
		dirMsg << "Direction W: " << dirW << "\n";
		dirMsg << "Direction X: " << dirX << "\n";
		dirMsg << "Direction Y: " << dirY << "\n";
		dirMsg << "Direction Z: " << dirZ << "\n";

		dirMsg << "Position X: " << position.getX() << "\n";
		dirMsg << "Position Z: " << position.getZ() << "\n";
		dirMsg << "Position Y: " << position.getY() << "\n";
		dirMsg << "Velocity: " << velocity.get().toString() << "\n";
		info(true) << dirMsg.toString();
		*/

		if (pilot->getSpaceZone() == nullptr) {
			pilot->setSpaceZone(ship->getSpaceZone());
			error() << "ShipUpdateTransformCallback -- Pilot has a null space zone";
		}

		Locker slock(ship);
		Locker plock(pilot, ship);

		bool collision = CollisionManager::checkShipCollision(ship, position, position);

		if (collision) {
			ship->setDirection(direction);
			ship->setMovementCounter(counter);

			auto crash = new ShipUpdateTransformCollisionMessage(ship);
			ship->broadcastMessage(crash, true);

			auto effect = new PlayClientEffectObjectMessage(ship, "clienteffect/space_collision.cef", "");
			ship->broadcastMessage(effect, true);
		} else {
			// No Collision
			uint32 deltaTime = ghost->getServerMovementTimeDelta();
			bool lightUpdate = deltaTime < 500;

			//info(true) << "ShipUpdateTransformCallback -- Server Movement Time Delta = " << deltaTime << "  ShipUpdateTransformMessage called ";

			if (!lightUpdate) {
				ship->setDirection(direction);
				ship->setPosition(position.getX(), position.getZ(), position.getY());
			}
		}

		ship->updateZone(false, true);

		auto shipMessage = new ShipUpdateTransformMessage(ship, velocity, yawRate, pitchRate, rollRate);
		ship->broadcastMessage(shipMessage, false);
	}
};

#endif /* SHIPUPDATETRANSFORMCALLBACK_H_ */
