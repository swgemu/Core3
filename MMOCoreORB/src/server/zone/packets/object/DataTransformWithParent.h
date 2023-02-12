/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DATATRANSFORMWITHPARENT_H_
#define DATATRANSFORMWITHPARENT_H_

#include "server/zone/Zone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/building/BuildingObject.h"

#include "server/zone/packets/object/ObjectControllerMessageCallback.h"
#include "server/zone/packets/scene/LightUpdateTransformWithParentMessage.h"
#include "server/zone/packets/scene/UpdateTransformWithParentMessage.h"
#include "server/zone/packets/object/transform/Transform.h"

#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/collision/IntersectionResults.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

class DataTransformWithParent : public ObjectControllerMessage {
public:
	DataTransformWithParent(SceneObject* sceneO) : ObjectControllerMessage(sceneO->getObjectID(), 0x1B, 0xF1) {
		insertInt(sceneO->getMovementCounter());
		insertLong(sceneO->getParentID());

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

		sceneO->debug() << "DataTransformWithParent sent.";
	}
};

class DataTransformWithParentCallback : public MessageCallback {
	ObjectControllerMessageCallback* objectControllerMain;

	ValidatedPosition validPosition;
	Transform transform;

	long deltaTime;

public:
	DataTransformWithParentCallback (ObjectControllerMessageCallback* objectControllerCallback) :
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
		transform.parseDataTransformWithParent(message);

		debug() << "DataTransformWithParent parsed.";
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

		ManagedReference<SceneObject*> parent = server->getZoneServer()->getObject(transform.getParentID(), true);

		if (parent == nullptr || parent->getZone() == nullptr || !parent->isCellObject()) {
			return updateError(creO, "!parent");
		}

		if (ghost->isForcedTransform()) {
			validPosition = *ghost->getLastValidatedPosition();
		} else {
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

		if (ghost->isForcedTransform()) {
			ghost->setForcedTransform(false);
		}
	}

	void updatePosition(CreatureObject* creO, SceneObject* parent) {
		if (!transform.isPositionValid()) {
			return updateError(creO, "!isPositionValid", true);
		}

		if (creO->isRidingMount()) {
			ZoneServer* zoneServer = creO->getZoneServer();

			if (zoneServer == nullptr) {
				return updateError(creO, "!zoneServer");
			}

			ObjectController* objectController = zoneServer->getObjectController();

			if (objectController == nullptr) {
				return updateError(creO, "!objectController");
			}

			objectController->activateCommand(creO, STRING_HASHCODE("dismount"), 0, 0, "");

			return updateError(creO, "@base_player:no_entry_while_mounted", true);
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

		CellObject* newCell = cast<CellObject*>(parent);

		if (newCell == nullptr) {
			return updateError(creO, "!newCell");
		}

		SceneObject* oldParent = creO->getParent().get();

		if (oldParent != nullptr && !oldParent->isCellObject()) {
			return updateError(creO, "!oldParent");
		}

		if (oldParent != parent) {
			SceneObject* cellParent = parent->getParent().get();

			if (cellParent == nullptr || !cellParent->isBuildingObject()) {
				return updateError(creO, "!cellParent");
			}

			BuildingObject* building = cellParent->asBuildingObject();

			if (building == nullptr) {
				return updateError(creO, "!building");
			}

			if (!ghost->isPrivileged() && !building->isAllowedEntry(creO)) {
				return updateError(creO, "!isAllowedEntry", true);
			}

			if (oldParent != nullptr) {
				CellObject* currentCell = cast<CellObject*>(oldParent);

				if (currentCell == nullptr) {
					return updateError(creO, "!currentCell");
				}

				const PortalLayout* layout = building->getObjectTemplate()->getPortalLayout();

				if (layout == nullptr) {
					return updateError(creO, "!portalLayout");
				}

				const CellProperty* cellProperty = layout->getCellProperty(currentCell->getCellNumber());

				if (!cellProperty->hasConnectedCell(newCell->getCellNumber())) {
					return updateError(creO, "!hasConnectedCell", true);
				}
			} else {
				float sqrCovDist = ZoneServer::CLOSEOBJECTRANGE * ZoneServer::CLOSEOBJECTRANGE;

				if (transform.get2dSquaredDistance(building->getPosition()) > sqrCovDist) {
					CloseObjectsVector* closeObjects = creO->getCloseObjects();

					if (!closeObjects->contains(building)) {
						return updateError(creO, "!buildingInCov", true);
					}
				}
			}
		}

		UniqueReference<Vector<float>*> collisionPoints(CollisionManager::getCellFloorCollision(transform.getPositionX(), transform.getPositionY() , newCell));

		if (collisionPoints == nullptr) {
			return updateError(creO, "!collisionPoints");
		}

		float error = 16384.f;

		for (int i = 0; i < collisionPoints->size(); ++i) {
			float value = fabs(collisionPoints->get(i) - transform.getPositionZ());

			if (error > value) {
				error = value;
			}
		}

		if (error > 0.25f) {
			return updateError(creO, "!collisionPoint", true);
		}

		const ContainerPermissions* perms = parent->getContainerPermissions();

		if (perms == nullptr) {
			return updateError(creO, "!containerPermissions");
		}

		if (!perms->hasInheritPermissionsFromParent() && !parent->checkContainerPermission(creO, ContainerPermissions::WALKIN)) {
			return updateError(creO, "!checkContainerPermission", true);
		}

		WorldCoordinates coords(transform.getPosition(), newCell);

		float worldDistance = coords.getWorldPosition().squaredDistanceTo(creO->getWorldPosition());

		if (worldDistance > 441) { // 21m
			return updateError(creO, "!worldDistance", true);
		}

		if (!creO->isMovementAllowed()) {
			return updateError(creO, "animationLock", true);
		}

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		if (playerManager == nullptr) {
			return updateError(creO, "!playerManager");
		}

		if (playerManager->checkSpeedHackFirstTest(creO, transform.getSpeed() , validPosition, 1.1f) != 0) {
			return updateError(creO, "!checkSpeedHackFirstTest");
		}

		if (playerManager->checkSpeedHackSecondTest(creO, transform.getPositionX(), transform.getPositionZ(), transform.getPositionY(), transform.getTimeStamp(), parent) != 0) {
			return updateError(creO, "!checkSpeedHackSecondTest");
		}

		Vector3 position = transform.predictPosition(creO->getPosition(), creO->getDirection(), deltaTime);

#ifdef TRANSFORM_DEBUG
		String type = transform.getPosition() != position ? "prediction" : "position";
		transform.sendDebug(creO, type, position, deltaTime);
#endif // TRANSFORM_DEBUG

		creO->setPosition(transform.getPositionX(), transform.getPositionZ(), transform.getPositionY());
		creO->setDirection(transform.getDirection());
		creO->setCurrentSpeed(transform.getSpeed());

		broadcastTransform(creO, parent, position);
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

		creO->setDirection(direction);
		creO->setCurrentSpeed(0.f);

		broadcastTransform(creO, parent, creO->getPosition());

		if (synchronize) {
			auto data = new DataTransformWithParent(creO);
			creO->sendMessage(data);
		}
	}

	void broadcastTransform(CreatureObject* creO, SceneObject* parent, const Vector3& position) const {
		PlayerObject* ghost = creO->getPlayerObject();

		if (ghost == nullptr) {
			return updateError(creO, "!ghost");
		}

		ghost->setClientLastMovementStamp(transform.getTimeStamp());

		bool lightUpdate = objectControllerMain->getPriority() != 0x23;
		bool sendPackets = deltaTime > Transform::SYNCDELTA || creO->getParentID() != 0;

		creO->setMovementCounter(transform.getMoveCount());
		creO->updateZoneWithParent(parent, lightUpdate, false);
		creO->updateLocomotion();

		if (!sendPackets || creO->isInvisible()) {
			return updateError(creO, "!sendPackets");
		}

		if (lightUpdate) {
			auto update = new LightUpdateTransformWithParentMessage(creO, position.getX(), position.getZ(), position.getY(), creO->getParentID());
			creO->broadcastMessage(update, false);
		} else {
			auto update = new UpdateTransformWithParentMessage(creO, position.getX(), position.getZ(), position.getY(), creO->getParentID());
			creO->broadcastMessage(update, false);
		}
	}
};

#endif // DATATRANSFORMWITHPARENT_H_
