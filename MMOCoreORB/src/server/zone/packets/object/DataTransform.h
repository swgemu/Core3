/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DATATRANSFORM_H_
#define DATATRANSFORM_H_

#include "server/zone/Zone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "server/zone/packets/object/ObjectControllerMessageCallback.h"
#include "server/zone/packets/scene/LightUpdateTransformMessage.h"
#include "server/zone/packets/scene/UpdateTransformMessage.h"
#include "server/zone/packets/object/transform/Transform.h"

#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/collision/IntersectionResults.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

class DataTransform : public ObjectControllerMessage {
public:
	DataTransform(SceneObject* creo) :
		ObjectControllerMessage(creo->getObjectID(), 0x1B, 0x71) {

		insertInt(creo->getMovementCounter());

		insertFloat(creo->getDirectionX());
		insertFloat(creo->getDirectionY());
		insertFloat(creo->getDirectionZ());
		insertFloat(creo->getDirectionW());

		insertFloat(creo->getPositionX());
		insertFloat(creo->getPositionZ());
		insertFloat(creo->getPositionY());

		insertInt(0);

		creo->debug() << "DataTransform sent.";
	}

	DataTransform(SceneObject* creo, const Vector3& position) :
		ObjectControllerMessage(creo->getObjectID(), 0x1B, 0x71) {
		insertInt(creo->getMovementCounter());

		insertFloat(creo->getDirectionX());
		insertFloat(creo->getDirectionY());
		insertFloat(creo->getDirectionZ());
		insertFloat(creo->getDirectionW());

		insertFloat(position.getX());
		insertFloat(position.getZ());
		insertFloat(position.getY());

		insertInt(0);

		creo->debug() << "DataTransform sent.";
	}
};

class DataTransformCallback : public MessageCallback {
	ObjectControllerMessageCallback* objectControllerMain;

	ValidatedPosition validPosition;
	Transform transform;

	int deltaTime;

public:
	DataTransformCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {
		objectControllerMain = objectControllerCallback;

		deltaTime = 0;

		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player != nullptr) {
			Zone* zone = player->getZone();

			if (zone != nullptr) {
				const String& zoneName = zone->getZoneName();

				setCustomTaskQueue(zoneName);
			}
		}
	}

	void parse(Message* message) {
		transform.parseDataTransform(message);
		
		debug() << "DataTransform parsed.";
	}

	void updateError(CreatureObject* object, const String& message, bool bounceBack = false) const {
		if (!message.isEmpty() && message.beginsWith("@")) {
			object->sendSystemMessage(message);
		}

#ifdef TRANSFORM_DEBUG
		String type = (bounceBack ? "error: " : (message.beginsWith("!") ? "warning: " : "info: "));
		transform.sendDebug(object, type + message, validPosition.getPosition(), deltaTime);
#endif // TRANSFORM_DEBUG

		if (bounceBack) {
			if (object->getCurrentSpeed() != 0.f) {
				object->setCurrentSpeed(0.f);
				object->updateLocomotion();
			}

			const Vector3& position = validPosition.getPosition();
			object->teleport(position.getX(), position.getZ(), position.getY(), validPosition.getParent());

			Reference<PlayerObject*> ghost = object->getPlayerObject();
			if (ghost == nullptr) {
				return;
			}

			ghost->setClientLastMovementStamp(transform.getTimeStamp());
		}
	}

	void run() {
		ManagedReference<CreatureObject*> object = client->getPlayer();
		if (object == nullptr || object->getZone() == nullptr) {
			return;
		}

		Reference<PlayerObject*> ghost = object->getPlayerObject();
		if (ghost == nullptr || ghost->isTeleporting()) {
			return updateError(object, "!ghost");
		}

		deltaTime = transform.getTimeStamp() - ghost->getClientLastMovementStamp();
		if (deltaTime < Transform::MINDELTA) {
			return updateError(object, "deltaTime");
		}

		ManagedReference<SceneObject*> parent = object->getParent().get();
		if (parent != nullptr && !parent->isMount() && !parent->isVehicleObject()) {
			parent = nullptr;
		}

		if (parent != nullptr) {
			parent->wlock(object);
		}

		if (ghost->isForcedTransform()) {
			validPosition = *ghost->getLastValidatedPosition();
		} else {
			validPosition.update(object);
		}

		try {

			if (validPosition.getParent() != transform.getParentID() || transform.get2dSquaredDistance(validPosition.getPosition()) >= 0.005625f) {
				updatePosition(object, parent);
			} else {
				updateStatic(object, parent);
			}

#ifdef TRANSFORM_DEBUG
		} catch (Exception& e) {
			error() << e.what();
			e.printStackTrace();
		}
#else
		} catch (...) {}
#endif // TRANSFORM_DEBUG

		if (parent != nullptr) {
			parent->unlock();
		}

		if (ghost->isForcedTransform()) {
			ghost->setForcedTransform(false);
		}
	}

	void updatePosition(CreatureObject* object, SceneObject* parent) {
		if (!transform.isPositionValid()) {
			return updateError(object, "!isPositionValid", true);
		}

		Reference<PlayerObject*> ghost = object->getPlayerObject();
		if (ghost == nullptr) {
			return updateError(object, "!ghost");
		}

		if (!ghost->isForcedTransform()) {
			if (!transform.isPostureValid(object->getPosture())) {
				return updateError(object, "!posture", true);
			}

			if (deltaTime < Transform::MIDDELTA && transform.getSpeed() == object->getCurrentSpeed() && !transform.isYawUpdate(object->getDirection())) {
				return updateError(object, "inertia");
			}
		}

		if (!ghost->hasGodMode()) {
			if (object->isFrozen()) {
				return updateError(object, "isFrozen", true);
			}

			Reference<SceneObject*> inventory = object->getSlottedObject("inventory");
			if (inventory == nullptr) {
				return updateError(object, "!inventory");
			}

			if (inventory->getCountableObjectsRecursive() > inventory->getContainerVolumeLimit() + 1) {
				object->setState(CreatureState::FROZEN, true);
				return updateError(object, "@system_msg:move_fail_inventory_overloaded", true);
			}
		}

		Zone* zone = object->getZone();
		if (zone == nullptr) {
			return updateError(object, "!zone");
		}

		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();
		if (planetManager == nullptr) {
			return updateError(object, "!planetManager");
		}

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();
		if (playerManager == nullptr) {
			return updateError(object, "!playerManager");
		}

		IntersectionResults intersections;
		CloseObjectsVector* closeObjects = object->getCloseObjects();
		CollisionManager::getWorldFloorCollisions(transform.getPositionX(), transform.getPositionY() , zone, &intersections, closeObjects);

		float positionZ = planetManager->findClosestWorldFloor(transform.getPositionX(), transform.getPositionY() ,transform.getPositionZ() , object->getSwimHeight(), &intersections, closeObjects);

		if (playerManager->checkSpeedHackFirstTest(object, transform.getSpeed() , validPosition, 1.1f) != 0) {
			return updateError(object, "!checkSpeedHackFirstTest");
		}

		if (playerManager->checkSpeedHackSecondTest(object, transform.getPositionX(), positionZ, transform.getPositionY(), transform.getTimeStamp(), nullptr) != 0) {
			return updateError(object, "!checkSpeedHackSecondTest");
		}

		playerManager->updateSwimmingState(object, positionZ, &intersections, closeObjects);

		Vector3 position = transform.predictPosition(object->getPosition(), object->getDirection(), deltaTime);

#ifdef TRANSFORM_DEBUG
		String type = transform.getPosition() != position ? "prediction" : "position";
		transform.sendDebug(object, type, position, deltaTime);
#endif // TRANSFORM_DEBUG

		object->setPosition(transform.getPositionX(), positionZ, transform.getPositionY());
		object->setDirection(transform.getDirection());
		object->setCurrentSpeed(transform.getSpeed());

		updateTransform(object, parent, position);
	}

	void updateStatic(CreatureObject* object, SceneObject* parent) {
		bool synchronize = object->getCurrentSpeed() == 0.f && transform.getSpeed() == 0.f && !transform.isYawUpdate(object->getDirection());
		if (synchronize && deltaTime < 10000u) {
			return updateError(object, "inertUpdate");
		}

#ifdef TRANSFORM_DEBUG
		String type = synchronize ? "synchronize" : "static";
		transform.sendDebug(object, type, object->getPosition(), deltaTime);
#endif // TRANSFORM_DEBUG

		Quaternion direction = transform.getDirection();
		if (synchronize) {
			direction.normalize();
		}

		object->setDirection(direction);
		object->setCurrentSpeed(0.f);

		updateTransform(object, parent, object->getPosition());

		if (synchronize) {
			auto data = new DataTransform(object, transform.getPosition());
			object->sendMessage(data);
		}
	}

	void updateTransform(CreatureObject* object, SceneObject* parent, const Vector3& position) const {
		Reference<PlayerObject*> ghost = object->getPlayerObject();
		if (ghost == nullptr) {
			return updateError(object, "!ghost");
		}

		ghost->setClientLastMovementStamp(transform.getTimeStamp());

		bool lightUpdate = objectControllerMain->getPriority() != 0x23;

		object->setMovementCounter(transform.getMoveCount());
		object->updateZone(lightUpdate, false);
		object->updateLocomotion();

		CreatureObject* creature = nullptr;
		if (parent != nullptr && parent->isCreatureObject()) {
			parent->incrementMovementCounter();
			creature = parent->asCreatureObject();
		} else {
			creature = object;
		}

		if (creature == nullptr || creature->isInvisible()) {
			return updateError(object, "!creature");
		}

		if (lightUpdate) {
			auto update = new LightUpdateTransformMessage(creature, position.getX(), position.getZ(), position.getY());
			creature->broadcastMessage(update, false);
		} else {
			auto update = new UpdateTransformMessage(creature, position.getX(), position.getZ(), position.getY());
			creature->broadcastMessage(update, false);
		}
	}
};

#endif // DATATRANSFORM_H_
