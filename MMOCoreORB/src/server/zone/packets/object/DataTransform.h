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
#include "server/zone/Zone.h"
#include "server/zone/SpaceZone.h"

class DataTransform : public ObjectControllerMessage {
public:
	DataTransform(SceneObject* sceneO) : ObjectControllerMessage(sceneO->getObjectID(), 0x1B, 0x71) {

		insertInt(sceneO->getMovementCounter());

		insertFloat(sceneO->getDirectionX());
		insertFloat(sceneO->getDirectionY());
		insertFloat(sceneO->getDirectionZ());
		insertFloat(sceneO->getDirectionW());

		insertFloat(sceneO->getPositionX());
		insertFloat(sceneO->getPositionZ());
		insertFloat(sceneO->getPositionY());

		float speed = 0;

		if (sceneO->isCreatureObject())
			speed = sceneO->asCreatureObject()->getCurrentSpeed();

		insertFloat(speed);

		/*if (sceneO->isPlayerCreature())
			sceneO->info(true) << "DataTransform sent 1 -- X: " << sceneO->getPositionX() << " Z: " << sceneO->getPositionZ() << " Y: " << sceneO->getPositionY();
		*/
	}

	DataTransform(SceneObject* sceneO, const Vector3& position) : ObjectControllerMessage(sceneO->getObjectID(), 0x1B, 0x71) {
		insertInt(sceneO->getMovementCounter());

		insertFloat(sceneO->getDirectionX());
		insertFloat(sceneO->getDirectionY());
		insertFloat(sceneO->getDirectionZ());
		insertFloat(sceneO->getDirectionW());

		insertFloat(position.getX());
		insertFloat(position.getZ());
		insertFloat(position.getY());

		float speed = 0;

		if (sceneO->isCreatureObject())
			speed = sceneO->asCreatureObject()->getCurrentSpeed();

		insertFloat(speed);

		/*if (sceneO->isPlayerCreature())
			sceneO->info(true) << "DataTransform sent 2.";
		*/
	}
};

class DataTransformCallback : public MessageCallback {
	ObjectControllerMessageCallback* objectControllerMain;

	ValidatedPosition validPosition;
	Transform transform;

	long deltaTime;

public:
	DataTransformCallback(ObjectControllerMessageCallback* objectControllerCallback) : MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {
		objectControllerMain = objectControllerCallback;

		deltaTime = 0;

		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player != nullptr) {
			Zone* zone = player->getZone();

			if (zone == nullptr)
				return;

			const String& zoneName = zone->getZoneName();
			setCustomTaskQueue(zoneName);
		}
	}

	void parse(Message* message) {
		transform.parseDataTransform(message);

		debug() << "DataTransform parsed - X: " << transform.getPositionX() << " Z: " << transform.getPositionZ() << " Y: " << transform.getPositionY();
	}

	void updateError(CreatureObject* creO, const String& message, bool bounceBack = false) const {
		if (!message.isEmpty() && message.beginsWith("@")) {
			creO->sendSystemMessage(message);
		}

#ifdef TRANSFORM_DEBUG
		String type = (bounceBack ? "error: " : (message.beginsWith("!") ? "warning: " : "info: "));
		transform.sendDebug(creO, type + message, validPosition.getPosition(), deltaTime);
#endif // TRANSFORM_DEBUG

		if (bounceBack) {
			if (creO->getCurrentSpeed() != 0.f) {
				creO->setCurrentSpeed(0.f);
				creO->updateLocomotion();
			}

			const Vector3& position = validPosition.getPosition();
			const uint64& parentID = validPosition.getParent();

			creO->teleport(position.getX(), position.getZ(), position.getY(), parentID);
		}
	}

	void run() {
		ManagedReference<CreatureObject*> creO = client->getPlayer();

		if (creO == nullptr || creO->getZone() == nullptr) {
			return;
		}

		PlayerObject* ghost = creO->getPlayerObject();

		if (ghost == nullptr || ghost->isTeleporting()) {
			return updateError(creO, "!ghost");
		}

		deltaTime = transform.getTimeStamp() - ghost->getClientLastMovementStamp();

		if (deltaTime < -Transform::SYNCDELTA) {
			validPosition.update(creO);
			return updateError(creO, "syncDelta", true);
		}

		if (deltaTime < Transform::MINDELTA) {
			return updateError(creO, "deltaTime");
		}

		ManagedReference<SceneObject*> parent = creO->getParent().get();

		if (parent != nullptr && !parent->isMount() && !parent->isVehicleObject()) {
			parent = nullptr;
		}

		if (parent != nullptr) {
			parent->wlock(creO);
		}

		if (ghost->isForcedTransform()) {
			validPosition = *ghost->getLastValidatedPosition();
		} else {
			// Update Valid Position
			validPosition.update(creO);
		}

		try {
			if (validPosition.getParent() != transform.getParentID() || transform.get2dSquaredDistance(validPosition.getPosition()) >= 0.015625f) {
				updatePosition(creO, parent);
			} else {
				updateStatic(creO, parent);
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

	void updatePosition(CreatureObject* creO, SceneObject* parent) {
		if (!transform.isPositionValid()) {
			return updateError(creO, "!isPositionValid", true);
		}

		PlayerObject* ghost = creO->getPlayerObject();

		if (ghost == nullptr) {
			return updateError(creO, "!ghost");
		}

		if (!ghost->isForcedTransform()) {
			if (!transform.isPostureValid(creO->getPosture())) {
				return updateError(creO, "!posture", true);
			}

			if (deltaTime < Transform::MIDDELTA && !transform.isInertiaUpdate(creO->getPosition(), creO->getDirection(), creO->getCurrentSpeed())) {
				return updateError(creO, "inertia");
			}
		}

		if (!ghost->isPrivileged()) {
			if (creO->isFrozen()) {
				creO->sendSystemMessage("You are frozen and cannot move.");
				return updateError(creO, "isFrozen", true);
			}

			SceneObject* inventory = creO->getSlottedObject("inventory");

			if (inventory == nullptr) {
				return updateError(creO, "!inventory");
			}

			if (inventory->getCountableObjectsRecursive() > inventory->getContainerVolumeLimit() + 1) {
				creO->sendSystemMessage("@ui_inv:inventory_full");
				return updateError(creO, "@system_msg:move_fail_inventory_overloaded", true);
			}
		}

		Zone* zone = creO->getZone();

		if (zone == nullptr) {
			return updateError(creO, "!zone");
		}

		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

		if (planetManager == nullptr) {
			return updateError(creO, "!planetManager");
		}

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		if (playerManager == nullptr) {
			return updateError(creO, "!playerManager");
		}

		IntersectionResults intersections;
		CloseObjectsVector* closeObjects = creO->getCloseObjects();
		CollisionManager::getWorldFloorCollisions(transform.getPositionX(), transform.getPositionY() , zone, &intersections, closeObjects);

		float positionZ = planetManager->findClosestWorldFloor(transform.getPositionX(), transform.getPositionY() ,transform.getPositionZ() , creO->getSwimHeight(), &intersections, closeObjects);

		if (!creO->isMovementAllowed()) {
			return updateError(creO, "animationLock", true);
		}

		float transformSpeed = transform.getSpeed();

		if (playerManager->checkSpeedHackFirstTest(creO, transformSpeed, validPosition, 1.1f) != 0) {
			return updateError(creO, "!checkSpeedHackFirstTest", true);
		}

		if (playerManager->checkSpeedHackSecondTest(creO, transform.getPositionX(), positionZ, transform.getPositionY(), transform.getTimeStamp(), nullptr) != 0) {
			return updateError(creO, "!checkSpeedHackSecondTest", true);
		}

		const auto playerPosition = (transform.getParentID() > 0) ? creO->getPosition() : creO->getWorldPosition();
		const auto transformPosition = transform.getPosition();

		float sqDistance = playerPosition.squaredDistanceTo(transformPosition);

		StringBuffer msg;
		msg <<  "Next Position Dist Sq: " << sqDistance << " Player Position: " << playerPosition.toString() << " Speed: " << transformSpeed;

		creO->info(true) << msg.toString();

		if (sqDistance > (20.f * 20.f)) {
			return updateError(creO, "!updateMovementDist", true);
		}

		playerManager->updateSwimmingState(creO, positionZ, &intersections, closeObjects);

		Vector3 position = transform.predictPosition(creO->getPosition(), creO->getDirection(), deltaTime);

#ifdef TRANSFORM_DEBUG
		String type = transform.getPosition() != position ? "prediction" : "position";
		transform.sendDebug(creO, type, position, deltaTime);
#endif // TRANSFORM_DEBUG

		creO->setPosition(transform.getPositionX(), positionZ, transform.getPositionY());
		creO->setDirection(transform.getDirection());
		creO->setCurrentSpeed(transform.getSpeed());

		updateTransform(creO, parent, position);
	}

	void updateStatic(CreatureObject* creO, SceneObject* parent) {
		bool synchronize = transform.isSynchronizeUpdate(creO->getDirection(), creO->getCurrentSpeed());

		if (synchronize && deltaTime < Transform::SYNCDELTA) {
			return updateError(creO, "inertUpdate");
		}

#ifdef TRANSFORM_DEBUG
		String type = synchronize ? "synchronize" : "static";
		transform.sendDebug(creO, type, creO->getPosition(), deltaTime);
#endif // TRANSFORM_DEBUG

		Quaternion direction = transform.getDirection();

		if (synchronize) {
			direction.normalize();
		}

		float transformSpeed = transform.getSpeed();

		const auto playerPosition = (transform.getParentID() > 0) ? creO->getPosition() : creO->getWorldPosition();
		const auto transformPosition = transform.getPosition();

		float sqDistance = playerPosition.squaredDistanceTo(transformPosition);

		StringBuffer msg;
		msg <<  "Next Position Dist Sq: " << sqDistance << " Player Position: " << playerPosition.toString() << " Speed: " << transformSpeed;

		creO->info(true) << msg.toString();

		if (sqDistance > (2.f * 2.f)) {
			return updateError(creO, "!staticMovementDist", true);
		}

		creO->setDirection(direction);
		creO->setCurrentSpeed(0.f);

		updateTransform(creO, parent, creO->getPosition());

		if (synchronize) {
			auto data = new DataTransform(creO, transformPosition);
			creO->sendMessage(data);
		}
	}

	void updateTransform(CreatureObject* creO, SceneObject* parent, const Vector3& position) const {
		PlayerObject* ghost = creO->getPlayerObject();

		if (ghost == nullptr) {
			return updateError(creO, "!ghost");
		}

		ghost->setClientLastMovementStamp(transform.getTimeStamp());

		CreatureObject* creature = nullptr;

		if (parent != nullptr && parent->isCreatureObject()) {
			parent->incrementMovementCounter();
			creature = parent->asCreatureObject();
		} else {
			creature = creO;
		}

		if (creature == nullptr) {
			return updateError(creO, "!creature");
		}

		bool lightUpdate = objectControllerMain->getPriority() != 0x23;
		bool sendPackets = deltaTime > Transform::SYNCDELTA || creature->getParentID() == 0;

		creO->setMovementCounter(transform.getMoveCount());
		creO->setSyncStamp(transform.getTimeStamp());

		creO->updateZone(lightUpdate, false);
		creO->updateLocomotion();

		if (!sendPackets || creature->isInvisible()) {
			return updateError(creO, "!sendPackets");
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
