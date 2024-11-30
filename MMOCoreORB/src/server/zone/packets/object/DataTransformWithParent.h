/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DATATRANSFORMWITHPARENT_H_
#define DATATRANSFORMWITHPARENT_H_

#include "server/zone/Zone.h"
#include "server/zone/SpaceZone.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/ship/PobShipObject.h"
#include "server/zone/packets/object/ObjectControllerMessageCallback.h"
#include "server/zone/packets/scene/LightUpdateTransformWithParentMessage.h"
#include "server/zone/packets/scene/UpdateTransformWithParentMessage.h"
#include "server/zone/packets/object/transform/Transform.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/cell/CellObject.h"
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

		float speed = 0.f;

		if (sceneO->isCreatureObject()) {
			auto creatureObject = sceneO->asCreatureObject();

			if (creatureObject != nullptr) {
				speed = creatureObject->getCurrentSpeed();
			}
		}

		insertFloat(speed);
	}
};
class DataTransformWithParentCallback : public MessageCallback {
	ObjectControllerMessageCallback* objectControllerMain;

	ValidatedPosition validPosition;
	Transform transform;

	long deltaTime;

public:
	DataTransformWithParentCallback(ObjectControllerMessageCallback* objectControllerCallback) : MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {
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

		if (creO == nullptr) {
			return;
		}

		auto zone = creO->getZone();

		if (zone == nullptr) {
			return updateError(creO, "!zone");
		}

		bool spaceZone = zone->isSpaceZone();

		auto ghost = creO->getPlayerObject();

		if (ghost == nullptr || ghost->isTeleporting()) {
			return updateError(creO, "!ghost");
		}

		deltaTime = transform.getTimeStamp() - ghost->getClientLastMovementStamp();

		if (deltaTime < -Transform::SYNCDELTA) {
			validPosition.update(creO);
			return updateError(creO, "syncDelta", true);
		}

		uint64 parentID = transform.getParentID();

		// Ensures datatransform is ran with the parent is changing, regardless of deltaTime
		if (deltaTime < Transform::MINDELTA && parentID > 0 && parentID != creO->getParentID()) {
			return updateError(creO, "deltaTime");
		}

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr) {
			return updateError(creO, "!zoneServer");
		}

		ManagedReference<SceneObject*> parent = zoneServer->getObject(parentID, true);

		if (parent == nullptr || !transform.isValidParentType(parent) || parent->getZone() == nullptr) {
			return updateError(creO, "!parent");
		}

		if (ghost->isForcedTransform()) {
			validPosition = *ghost->getLastValidatedPosition();
		} else {
			validPosition.update(creO);
		}

		try {
			if (validPosition.getParent() != transform.getParentID() || (!spaceZone && transform.get2dSquaredDistance(validPosition.getPosition()) > 0.015625f) ||
				(spaceZone && transform.get3dSquaredDistance(validPosition.getPosition()) > 0.015625f)) {

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
		} catch (...) {
		}
#endif // TRANSFORM_DEBUG

		if (ghost->isForcedTransform()) {
			ghost->setForcedTransform(false);
		}
	}

	void updatePosition(CreatureObject* creO, SceneObject* parent) {
		if (!transform.isPositionValid()) {
			return updateError(creO, "!isPositionValid", true);
		}

		auto zoneServer = creO->getZoneServer();

		if (zoneServer == nullptr) {
			return updateError(creO, "!zoneServer");
		}

		if (creO->isRidingMount()) {
			ObjectController* objectController = zoneServer->getObjectController();

			if (objectController == nullptr) {
				return updateError(creO, "!objectController");
			}

			objectController->activateCommand(creO, STRING_HASHCODE("dismount"), 0, 0, "");

			return updateError(creO, "@base_player:no_entry_while_mounted", true);
		}

		auto zone = creO->getZone();

		if (zone == nullptr) {
			return updateError(creO, "!zoneNull");
		}

		bool spaceZone = zone->isSpaceZone();

		auto ghost = creO->getPlayerObject();

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

			if (!creO->isMovementAllowed()) {
				return updateError(creO, "animationLock", true);
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

		ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

		if (playerManager == nullptr) {
			return updateError(creO, "!playerManager");
		}

		CellObject* newCell = nullptr;
		bool newParentIsCell = false;

		if (parent->isCellObject()) {
			newCell = cast<CellObject*>(parent);

			if (newCell == nullptr) {
				return updateError(creO, "!newCell");
			}

			newParentIsCell = true;
		}

		SceneObject* oldParent = creO->getParent().get();

		if (oldParent != parent) {
			SceneObject* newRootParent = parent->getParent().get();

			if (newRootParent == nullptr) {
				return updateError(creO, "!newRootParent1");
			}

			// Checks for building and building entry
			if (newRootParent->isBuildingObject()) {
				auto building = newRootParent->asBuildingObject();

				if (building == nullptr) {
					return updateError(creO, "!building");
				}

				if (!privilegedPlayer && !building->isAllowedEntry(creO)) {
					return updateError(creO, "!isAllowedEntry", true);
				}
			// Checks for POB Ship
			} else if (newRootParent->isPobShip()) {
				auto pobShip = newRootParent->asPobShip();

				if (pobShip == nullptr) {
					return updateError(creO, "!pobShip");
				}
			} else {
				return updateError(creO, "!newRootParent2");
			}

			if (oldParent != nullptr) {
				// If the old parent is valid parent type
				if (!transform.isValidParentType(oldParent)) {
					return updateError(creO, "!oldParent");
				}

				if (oldParent->isCellObject()) {
					CellObject* currentCell = cast<CellObject*>(oldParent);

					if (currentCell == nullptr) {
						return updateError(creO, "!currentCell");
					}

					const auto objectTemplate = newRootParent->getObjectTemplate();

					if (objectTemplate != nullptr) {
						const PortalLayout* layout = objectTemplate->getPortalLayout();

						if (layout == nullptr) {
							return updateError(creO, "!portalLayout");
						}

						const CellProperty* cellProperty = layout->getCellProperty(currentCell->getCellNumber());

						if (newCell != nullptr) {
							if (!cellProperty->hasConnectedCell(newCell->getCellNumber())) {
								return updateError(creO, "!hasConnectedCell", true);
							}

							UniqueReference<Vector<float>*> collisionPoints(CollisionManager::getCellFloorCollision(transform.getPositionX(), transform.getPositionY(), newCell));

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
						}
					}
				}
			} else {
				const float covDist = newRootParent->getOutOfRangeDistance();
				const float sqrCovDist = covDist * covDist;

				// Use the object out of range distance
				if (spaceZone) {
					if (transform.get3dSquaredDistance(newRootParent->getPosition()) > sqrCovDist) {
						CloseObjectsVector* closeObjects = creO->getCloseObjects();

						if (!closeObjects->contains(newRootParent)) {
							return updateError(creO, "!newRootInCov", true);
						}
					}
				} else {
					if (transform.get2dSquaredDistance(newRootParent->getPosition()) > sqrCovDist) {
						CloseObjectsVector* closeObjects = creO->getCloseObjects();

						if (!closeObjects->contains(newRootParent)) {
							return updateError(creO, "!newRootInCov", true);
						}
					}
				}
			}
		}

		const ContainerPermissions* perms = parent->getContainerPermissions();

		if (perms == nullptr) {
			return updateError(creO, "!containerPermissions");
		}

		if (newParentIsCell && !perms->hasInheritPermissionsFromParent() && !parent->checkContainerPermission(creO, ContainerPermissions::WALKIN)) {
			return updateError(creO, "!checkContainerPermission", true);
		}

		WorldCoordinates coords(transform.getPosition(), newCell);

		if (spaceZone) {
			float spaceDistance = coords.getWorldPosition().squaredDistanceTo(creO->getWorldPosition());

			if (spaceDistance > (21 * 21)) {
				return updateError(creO, "!spaceDistance", true);
			}
		} else {
			float worldDistance = coords.getWorldPosition().squaredDistanceTo2d(creO->getWorldPosition());

			if (worldDistance > (21 * 21)) {
				return updateError(creO, "!worldDistance", true);
			}
		}

		Vector3 lastValidatedWorldPosition = validPosition.getWorldPosition(zoneServer);
		lastValidatedWorldPosition.setZ(0.f);

		if (!playerManager->checkSpeedHackTests(creO, ghost, lastValidatedWorldPosition, transform.getPosition(), transform.getTimeStamp(), transform.getPositionZ(), parent)) {
			return updateError(creO, "!DTWP_checkSpeedHackTests_POS");
		}

		Vector3 position = transform.predictPosition(creO->getPosition(), creO->getDirection(), deltaTime);

		// Update Speed and locomotion
		creO->setCurrentSpeed(transform.getSpeed());
		creO->updateLocomotion();

		bool lightUpdate = objectControllerMain->getPriority() != 0x23;

		// Set the players new position in the cell
		creO->setPosition(transform.getPositionX(), transform.getPositionZ(), transform.getPositionY());

#ifdef TRANSFORM_DEBUG
		String type = transform.getPosition() != position ? "prediction" : "position";
		transform.sendDebug(creO, type, position, deltaTime);
#endif // TRANSFORM_DEBUG

		// Update the players parent
		creO->updateZoneWithParent(parent, lightUpdate, false);

		// Update the players direction
		creO->setDirection(transform.getDirection());

		// Broadcast the position move
		broadcastTransform(creO, parent, position, lightUpdate);
	}

	void updateStatic(CreatureObject* creO, SceneObject* parent) {
		bool synchronize = transform.isSynchronizeUpdate(creO->getDirection(), creO->getCurrentSpeed());

		if (synchronize && deltaTime < Transform::SYNCDELTA) {
			return updateError(creO, "inertUpdate");
		}

		auto ghost = creO->getPlayerObject();

		if (ghost == nullptr) {
			return updateError(creO, "!ghost");
		}

		auto zoneServer = creO->getZoneServer();

		if (zoneServer == nullptr) {
			return updateError(creO, "!zoneServer");
		}

		auto playerManager = zoneServer->getPlayerManager();

		if (playerManager == nullptr) {
			return updateError(creO, "!playerManager");
		}

#ifdef TRANSFORM_DEBUG
		String type = synchronize ? "synchronize" : "static";
		transform.sendDebug(creO, type, creO->getPosition(), deltaTime);
#endif // TRANSFORM_DEBUG

		Vector3 lastValidatedWorldPosition = validPosition.getWorldPosition(zoneServer);
		lastValidatedWorldPosition.setZ(0.f);

		if (!playerManager->checkSpeedHackTests(creO, ghost, lastValidatedWorldPosition, transform.getPosition(), transform.getTimeStamp(), transform.getPositionZ(), parent)) {
			return updateError(creO, "!DTWP_checkSpeedHackTests_STAT");
		}

		Quaternion direction = transform.getDirection();

		if (synchronize) {
			direction.normalize();
		}

		creO->setDirection(direction);

		if (creO->getCurrentSpeed() != 0.f) {
			creO->setCurrentSpeed(0.f);
			creO->updateLocomotion();
		}

		bool lightUpdate = objectControllerMain->getPriority() != 0x23;

		broadcastTransform(creO, parent, creO->getPosition(), lightUpdate);

		if (synchronize) {
			auto data = new DataTransformWithParent(creO);
			creO->sendMessage(data);
		}
	}

	void broadcastTransform(CreatureObject* creO, SceneObject* parent, const Vector3& position, bool lightUpdate) const {
		auto ghost = creO->getPlayerObject();

		if (ghost == nullptr) {
			return updateError(creO, "!ghost");
		}

		ghost->setClientLastMovementStamp(transform.getTimeStamp());

		bool sendPackets = deltaTime > Transform::SYNCDELTA || creO->getParentID() != 0;

		creO->setMovementCounter(transform.getMoveCount());
		creO->setSyncStamp(transform.getTimeStamp());

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
