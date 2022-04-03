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
	DataTransformWithParent(SceneObject* creo) :
		ObjectControllerMessage(creo->getObjectID(), 0x1B, 0xF1) {
		insertInt(creo->getMovementCounter());
		insertLong(creo->getParentID());

		insertFloat(creo->getDirectionX());
		insertFloat(creo->getDirectionY());
		insertFloat(creo->getDirectionZ());
		insertFloat(creo->getDirectionW());

		insertFloat(creo->getPositionX());
		insertFloat(creo->getPositionZ());
		insertFloat(creo->getPositionY());

		insertInt(0);

		creo->debug() << "DataTransformWithParent sent.";
	}
};

class DataTransformWithParentCallback : public MessageCallback {
	ObjectControllerMessageCallback* objectControllerMain;

	ValidatedPosition validPosition;
	Transform transform;

	int deltaTime;

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

		ManagedReference<SceneObject*> parent = server->getZoneServer()->getObject(transform.getParentID(), true);
		if (parent == nullptr || parent->getZone() == nullptr || !parent->isCellObject()) {
			return updateError(object, "!parent");
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

		if (ghost->isForcedTransform()) {
			ghost->setForcedTransform(false);
		}
	}

	void updatePosition(CreatureObject* object, SceneObject* parent) {
		if (!transform.isPositionValid()) {
			return updateError(object, "!isPositionValid", true);
		}

		if (object->isRidingMount()) {
			ZoneServer* zoneServer = object->getZoneServer();
			if (zoneServer == nullptr) {
				return updateError(object, "!zoneServer");
			}

			ObjectController* objectController = zoneServer->getObjectController();
			if (objectController == nullptr) {
				return updateError(object, "!objectController");
			}

			objectController->activateCommand(object, STRING_HASHCODE("dismount"), 0, 0, "");
			return updateError(object, "@base_player:no_entry_while_mounted", true);
		}

		Reference<PlayerObject*> ghost = object->getPlayerObject();
		if (ghost == nullptr) {
			return updateError(object, "!ghost");
		}

		if (!ghost->isForcedTransform()) {
			if (!transform.isPostureValid(object->getPosture())) {
				return updateError(object, "!posture", true);
			}

			if (deltaTime < Transform::MIDDELTA  && transform.getSpeed() == object->getCurrentSpeed() && !transform.isYawUpdate(object->getDirection())) {
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

		CellObject* newCell = cast<CellObject*>(parent);
		if (newCell == nullptr) {
			return updateError(object, "!newCell");
		}

		Reference<SceneObject*> oldParent = object->getParent().get();
		if (oldParent != nullptr && !oldParent->isCellObject()) {
			return updateError(object, "!oldParent");
		}

		if (oldParent != parent) {
			Reference<SceneObject*> cellParent = parent->getParent().get();
			if (cellParent == nullptr || !cellParent->isBuildingObject()) {
				return updateError(object, "!cellParent");
			}

			BuildingObject* building = cellParent->asBuildingObject();
			if (building == nullptr) {
				return updateError(object, "!building");
			}

			if (!ghost->hasGodMode() && !building->isAllowedEntry(object)) {
				return updateError(object, "!isAllowedEntry", true);
			}

			if (oldParent != nullptr) {
				CellObject* currentCell = oldParent.castTo<CellObject*>();
				if (currentCell == nullptr) {
					return updateError(object, "!currentCell");
				}

				const PortalLayout* layout = building->getObjectTemplate()->getPortalLayout();
				if (layout == nullptr) {
					return updateError(object, "!portalLayout");
				}

				const CellProperty* cellProperty = layout->getCellProperty(currentCell->getCellNumber());
				if (!cellProperty->hasConnectedCell(newCell->getCellNumber())) {
					return updateError(object, "!hasConnectedCell", true);
				}
			} else {
				float sqrCovDist = ZoneServer::CLOSEOBJECTRANGE * ZoneServer::CLOSEOBJECTRANGE;

				if (transform.get2dSquaredDistance(building->getPosition()) > sqrCovDist) {
					CloseObjectsVector* closeObjects = object->getCloseObjects();

					if (!closeObjects->contains(building)) {
						return updateError(object, "!buildingInCov", true);
					}
				}
			}
		}

		UniqueReference<Vector<float>*> collisionPoints(CollisionManager::getCellFloorCollision(transform.getPositionX(), transform.getPositionY() , newCell));
		if (collisionPoints == nullptr) {
			return updateError(object, "!collisionPoints");
		}

		float error = 16384.f;

		for (int i = 0; i < collisionPoints->size(); ++i) {
			float value = fabs(collisionPoints->get(i) - transform.getPositionZ());

			if (error > value) {
				error = value;
			}
		}

		if (error > 0.25f) {
			return updateError(object, "!collisionPoint", true);
		}

		const ContainerPermissions* perms = parent->getContainerPermissions();
		if (perms == nullptr) {
			return updateError(object, "!containerPermissions");
		}

		if (!perms->hasInheritPermissionsFromParent() && !parent->checkContainerPermission(object, ContainerPermissions::WALKIN)) {
			return updateError(object, "!checkContainerPermission", true);
		}

		WorldCoordinates coords(transform.getPosition(), newCell);
		float worldDistance = coords.getWorldPosition().squaredDistanceTo(object->getWorldPosition());
		if (worldDistance > 441) { // 21m
			return updateError(object, "!worldDistance", true);
		}

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();
		if (playerManager == nullptr) {
			return updateError(object, "!playerManager");
		}

		if (playerManager->checkSpeedHackFirstTest(object, transform.getSpeed() , validPosition, 1.1f) != 0) {
			return updateError(object, "!checkSpeedHackFirstTest");
		}

		if (playerManager->checkSpeedHackSecondTest(object, transform.getPositionX(), transform.getPositionZ(), transform.getPositionY(), transform.getTimeStamp(), parent) != 0) {
			return updateError(object, "!checkSpeedHackSecondTest");
		}

		Vector3 position = transform.predictPosition(object->getPosition(), object->getDirection(), deltaTime);

#ifdef TRANSFORM_DEBUG
		String type = transform.getPosition() != position ? "prediction" : "position";
		transform.sendDebug(object, type, position, deltaTime);
#endif // TRANSFORM_DEBUG

		object->setPosition(transform.getPositionX(), transform.getPositionZ(), transform.getPositionY());
		object->setDirection(transform.getDirection());
		object->setCurrentSpeed(transform.getSpeed());

		broadcastTransform(object, parent, position);
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

		broadcastTransform(object, parent, object->getPosition());

		if (synchronize) {
			auto data = new DataTransformWithParent(object);
			object->sendMessage(data);
		}
	}

	void broadcastTransform(CreatureObject* object, SceneObject* parent, const Vector3& position) const {
		Reference<PlayerObject*> ghost = object->getPlayerObject();
		if (ghost == nullptr) {
			return updateError(object, "!ghost");
		}

		ghost->setClientLastMovementStamp(transform.getTimeStamp());

		bool lightUpdate = objectControllerMain->getPriority() != 0x23;

		object->setMovementCounter(transform.getMoveCount());
		object->updateZoneWithParent(parent, lightUpdate, false);
		object->updateLocomotion();

		if (object->isInvisible()) {
			return updateError(object, "isInvisible");
		}

		if (lightUpdate) {
			auto update = new LightUpdateTransformWithParentMessage(object, position.getX(), position.getZ(), position.getY(), object->getParentID());
			object->broadcastMessage(update, false);
		} else {
			auto update = new UpdateTransformWithParentMessage(object, position.getX(), position.getZ(), position.getY(), object->getParentID());
			object->broadcastMessage(update, false);
		}
	}
};

#endif // DATATRANSFORMWITHPARENT_H_
