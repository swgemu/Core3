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

		float speed = 0.f;

		if (sceneO->isCreatureObject()) {
			auto player = sceneO->asCreatureObject();

			if (player != nullptr) {
				speed = player->getCurrentSpeed();
			}
		}

		insertFloat(speed);
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

		float speed = 0.f;

		if (sceneO->isCreatureObject()) {
			auto player = sceneO->asCreatureObject();

			if (player != nullptr) {
				speed = player->getCurrentSpeed();
			}
		}

		insertFloat(speed);
	}
};

class DataTransformCallback : public MessageCallback {
	ObjectControllerMessageCallback* objectControllerMain;

	ValidatedPosition playerPosition;
	ValidatedPosition* validPosition = nullptr;

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

	void updateError(CreatureObject* creO, const String& message, bool bounceBack = false, float bounceDistance = 0.f) const {
		if (!message.isEmpty() && message.beginsWith("@")) {
			creO->sendSystemMessage(message);
		}

		if (bounceBack) {
			if (creO->getCurrentSpeed() != 0.f) {
				creO->setCurrentSpeed(0.f);
				creO->updateLocomotion();
			}

			Vector3 position = validPosition->getPosition();
			const uint64& parentID = validPosition->getParent();

			if (bounceDistance > 0.f) {
				float diffX = position.getX() - transform.getPositionX();
				float diffY = position.getY() - transform.getPositionY();

				float directionAngle = atan2(diffY, diffX);

				if (directionAngle < 0) {
					float a = M_PI + directionAngle;
					directionAngle = M_PI + a;
				}

				position.setX(position.getX() + (cos(directionAngle) * bounceDistance));
				position.setY(position.getY() + (sin(directionAngle) * bounceDistance));
			}

			creO->teleport(position.getX(), position.getZ(), position.getY(), parentID);

#ifdef TRANSFORM_DEBUG
			creO->info(true) << "DT -- Player position set by teleport in bounceBack - Position: " << position.toString();
#endif // TRANSFORM_DEBUG
		}

#ifdef TRANSFORM_DEBUG
		StringBuffer errorBuffer;
		errorBuffer << "DT ---- " << (bounceBack ? "error: " : (message.beginsWith("!") ? "warning: " : "info: ")) << message;
		transform.sendDebug(creO, errorBuffer.toString(), (validPosition != nullptr ? validPosition->getPosition() : Vector3(0,0,0)), deltaTime);
#endif // TRANSFORM_DEBUG
	}

	void run() {
		ManagedReference<CreatureObject*> creO = client->getPlayer();

		if (creO == nullptr) {
			return;
		}

		auto zone = creO->getZone();

		if (zone == nullptr) {
			return updateError(creO, "!zone");
		}

		uint32 timeStamp = transform.getTimeStamp();

#ifdef TRANSFORM_DEBUG
		std::cout << "\n\n";
		creO->info(true) << "DT ---- Transform Start - Transform Timestamp: " << timeStamp;
#endif // TRANSFORM_DEBUG

		auto ghost = creO->getPlayerObject();

		if (ghost == nullptr) {
			return updateError(creO, "!ghost");
		}

		validPosition = ghost->getLastValidatedPosition();

		if (validPosition == nullptr) {
			// Cannot bounch back here, validPosition is null
			return updateError(creO, "!validPosition", false);
		}

		if (ghost->isTeleporting()) {
			return updateError(creO, "!teleporting");
		}

		deltaTime = timeStamp - ghost->getClientLastMovementStamp();

		if (deltaTime < -Transform::SYNC_DELTA) {
			return updateError(creO, "syncDelta", true);
		}

		if (deltaTime < Transform::MIN_DELTA) {
			return updateError(creO, "deltaTime", false);
		}

		ManagedReference<SceneObject*> parent = creO->getParent().get();

		if (parent != nullptr && !parent->isMount() && !parent->isVehicleObject()) {
			parent = nullptr;
		}

		if (parent != nullptr) {
			parent->wlock(creO);
		}

		if (ghost->isForcedTransform()) {
			playerPosition = *validPosition;
		} else {
			// Update Stored Player Position
			playerPosition.update(creO);
		}

		try {
			if (playerPosition.getParent() != transform.getParentID() || transform.get2dSquaredDistance(playerPosition.getPosition()) >= Transform::UPDATE_THRESHOLD) {
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

		auto ghost = creO->getPlayerObject();

		if (ghost == nullptr) {
			return updateError(creO, "!ghost");
		}

		auto zoneServer = creO->getZoneServer();

		if (zoneServer == nullptr) {
			return updateError(creO, "!zoneServer");
		}

		if (!ghost->isForcedTransform()) {
			if (!transform.isPostureValid(creO->getPosture())) {
				return updateError(creO, "!posture", true);
			}

			if (deltaTime < Transform::MID_DELTA && !transform.isInertiaUpdate(creO->getPosition(), creO->getDirection(), creO->getCurrentSpeed())) {
				return updateError(creO, "inertia");
			}
		}

		bool privilegedPlayer = ghost->isPrivileged();

		if (!privilegedPlayer) {
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

		auto zone = creO->getZone();

		if (zone == nullptr) {
			return updateError(creO, "!zone");
		}

		if (!creO->isMovementAllowed()) {
			return updateError(creO, "!animationLock", true);
		}

		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

		if (planetManager == nullptr) {
			return updateError(creO, "!planetManager");
		}

		auto playerManager = zoneServer->getPlayerManager();

		if (playerManager == nullptr) {
			return updateError(creO, "!playerManager");
		}

		IntersectionResults intersections;
		CloseObjectsVector* closeObjects = creO->getCloseObjects();

		CollisionManager::getWorldFloorCollisions(transform.getPositionX(), transform.getPositionY() , zone, &intersections, closeObjects);

		float positionZ = planetManager->findClosestWorldFloor(transform.getPositionX(), transform.getPositionY() ,transform.getPositionZ(), creO->getSwimHeight(), &intersections, closeObjects);

		// Final Checks for Speed
		int movementValidation = playerManager->checkSpeedHackTests(creO, ghost, validPosition, transform.getPosition(), transform.getTimeStamp(), positionZ, nullptr);

		if (movementValidation == Transform::INVALID_POSITION) {
			return updateError(creO, "!DT_checkSpeedHackTests_POS", true);
		}

		// Determine if we should attempt to predict position due to velocity
		Vector3 position = transform.predictPosition(creO->getPosition(), creO->getDirection(), deltaTime);
		float transformSpeed = transform.getSpeed();

		/*
		// Last validated world position
		Vector3 lastValidatedWorldPosition = validPosition->getWorldPosition(zoneServer);
		float validWorldZ = lastValidatedWorldPosition.getZ();

		if (!privilegedPlayer && ((parent == nullptr && validPosition->getParent() == 0) || (parent != nullptr && (parent->isVehicleObject() || parent->isMount()))) &&
			!CollisionManager::checkMovementCollision(creO, closeObjects, zone, Vector3(lastValidatedWorldPosition.getX(), lastValidatedWorldPosition.getY(), validWorldZ), Vector3(position.getX(), position.getY(), positionZ))) {

			return updateError(creO, "!DT-checkCollision", true, (transformSpeed < 3.f ? 3.f : transformSpeed));
		}
		*/

		// Update the the players position on the server
		creO->setPosition(transform.getPositionX(), positionZ, transform.getPositionY());
		creO->setDirection(transform.getDirection());
		creO->setCurrentSpeed(transformSpeed);

		// Check for swimming state update after the players position has been changed
		playerManager->updateSwimmingState(creO, positionZ, &intersections, closeObjects);

		// Update the validated position
		if (movementValidation == Transform::FULL_VALIDATED) {
#ifdef TRANSFORM_DEBUG
			creO->info(true) << "DT --- Transform::FULL_VALIDATED -- Setting New Validated Position: (x:" << transform.getPositionX() << ", y:" << transform.getPositionY() << ", z:" << positionZ << ")";
#endif // TRANSFORM_DEBUG

			validPosition->setPosition(transform.getPositionX(), positionZ, transform.getPositionY());
			validPosition->setParent(0);

			ghost->updateServerLastMovementStamp();
		}

		// Send the transform update
		updateTransform(creO, parent, position);

#ifdef TRANSFORM_DEBUG
		StringBuffer finalMsg;
		finalMsg << "DT ---- Transform Complete -- " << (transform.getPosition() != position ? "prediction" : "position");
		transform.sendDebug(creO, finalMsg.toString(), position, deltaTime);
#endif // TRANSFORM_DEBUG
	}

	void updateStatic(CreatureObject* creO, SceneObject* parent) {
		bool synchronize = transform.isSynchronizeUpdate(creO->getDirection(), creO->getCurrentSpeed());

		if (synchronize && deltaTime < Transform::SYNC_DELTA) {
			return updateError(creO, "inertUpdate");
		}

		Quaternion direction = transform.getDirection();

		if (synchronize) {
			direction.normalize();
		}

		auto ghost = creO->getPlayerObject();

		if (ghost == nullptr) {
			return updateError(creO, "!ghost");
		}

		auto zoneServer = creO->getZoneServer();

		if (zoneServer == nullptr) {
			return updateError(creO, "!zoneServer");
		}

		creO->setDirection(direction);
		creO->setCurrentSpeed(0.f);

		updateTransform(creO, parent, creO->getPosition());

		if (synchronize) {
			auto data = new DataTransform(creO, transform.getPosition());
			creO->sendMessage(data);
		}

#ifdef TRANSFORM_DEBUG
			StringBuffer syncMsg;
			syncMsg << "DT ---- updateStatic COMPLETE -- " << (synchronize ? "synchronize" : "static");
			transform.sendDebug(creO, syncMsg.toString(), creO->getPosition(), deltaTime);
#endif // TRANSFORM_DEBUG
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
		bool sendPackets = deltaTime > Transform::SYNC_DELTA || creature->getParentID() == 0;

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
