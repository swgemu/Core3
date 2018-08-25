/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef DATATRANSFORMWITHPARENT_H_
#define DATATRANSFORMWITHPARENT_H_

#include "server/zone/objects/scene/WorldCoordinates.h"
#include "ObjectControllerMessage.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "ObjectControllerMessageCallback.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/collision/CollisionManager.h"

class DataTransformWithParent : public ObjectControllerMessage {
public:
	DataTransformWithParent(SceneObject* creo)
: ObjectControllerMessage(creo->getObjectID(), 0x1B, 0xF1) {

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
	}

};

class DataTransformWithParentCallback : public MessageCallback {
	uint32 movementStamp;
	uint32 movementCounter;
	uint64 parent;

	float directionX, directionY, directionZ, directionW;
	float positionX, positionZ, positionY;
	float parsedSpeed;

	ObjectControllerMessageCallback* objectControllerMain;
public:
	DataTransformWithParentCallback(ObjectControllerMessageCallback* objectControllerCallback) :
		MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()) {
		movementStamp = 0;
		movementCounter = 0;
		parent = 0;
		directionX = 0;
		directionY = 0;
		directionZ = 0;
		directionW = 0;
		positionX = 0;
		positionZ = 0;
		positionY = 0;
		parsedSpeed = 0;

		objectControllerMain = objectControllerCallback;

		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player != NULL) {
			Zone* zone = player->getZone();

			if (zone != NULL) {
				String zoneName = zone->getZoneName();

				setCustomTaskQueue(zoneName);
			}
		}
	}

	void parse(Message* message) {
		movementStamp = message->parseInt();
		movementCounter = message->parseInt();

		parent = message->parseLong();

		directionX = message->parseFloat();
		directionY = message->parseFloat();
		directionZ = message->parseFloat();
		directionW = message->parseFloat();

		positionX = message->parseFloat();
		positionZ = message->parseFloat();
		positionY = message->parseFloat();

		parsedSpeed = message->parseFloat();

		//info("datatransform with parent", true);
	}

	void bounceBack(CreatureObject* object, ValidatedPosition& pos) {
		Vector3 teleportPoint = pos.getPosition();
		uint64 teleportParentID = pos.getParent();

		object->teleport(teleportPoint.getX(), teleportPoint.getZ(), teleportPoint.getY(), teleportParentID);
	}

	void run() {
		ManagedReference<CreatureObject*> object = client->getPlayer().get();

		if (object == NULL)
			return;

		int posture = object->getPosture();

		//TODO: This should be derived from the locomotion table
		if (!object->hasDizzyEvent() && (posture == CreaturePosture::UPRIGHT || posture == CreaturePosture::PRONE || posture == CreaturePosture::CROUCHED
				|| posture == CreaturePosture::DRIVINGVEHICLE || posture == CreaturePosture::RIDINGCREATURE || posture == CreaturePosture::SKILLANIMATING) ) {

			updatePosition(object);
		} else {
			object->setCurrentSpeed(0);

			object->updateLocomotion();

			ValidatedPosition pos;
			pos.update(object);

			Vector3 currentPos = pos.getPosition();
			Vector3 newPos(positionX, positionY, positionZ);

			object->setDirection(directionW, directionX, directionY, directionZ);

			if (currentPos.squaredDistanceTo(newPos) > 0.01) {
				bounceBack(object, pos);
			} else {
				ManagedReference<SceneObject*> currentParent = object->getParent().get();
				bool light = objectControllerMain->getPriority() != 0x23;

				if (currentParent != NULL)
					object->updateZoneWithParent(currentParent, light);
				else
					object->updateZone(light);
			}
		}
	}

	void updatePosition(CreatureObject* object) {
		PlayerObject* ghost = object->getPlayerObject();

		if (ghost == NULL)
			return;

		if (std::isnan(positionX) || std::isnan(positionY) || std::isnan(positionZ))
			return;

		if (std::isinf(positionX) || std::isinf(positionY) || std::isinf(positionZ))
			return;

		if (ghost->isTeleporting())
			return;

		/*if (!object->isInQuadTree())
			return;*/

		if (positionX > 1024.0f || positionX < -1024.0f || positionY > 1024.0f || positionY < -1024.0f) {
			StringBuffer msg;
			msg << "position out of bounds cell:[" << parent << "]";
			object->error(msg.toString());

			return;
		}

		if (object->getZone() == NULL)
			return;

		if (object->isRidingMount()) {
			ZoneServer* zoneServer = server->getZoneServer();
			ObjectController* objectController = zoneServer->getObjectController();
			objectController->activateCommand(object, STRING_HASHCODE("dismount"), 0, 0, "");
			object->sendSystemMessage("@base_player:no_entry_while_mounted"); // "You cannot enter a structure while on your mount."
			return; // don't allow a dismount and parent update in the same frame, this looks better than bouncing their position
		}

		uint32 objectMovementCounter = object->getMovementCounter();

		/*if (objectMovementCounter > movementCounter) { // we already parsed a more updated movement counter
			StringBuffer msg;
			msg << "trying to parse movement update: 0x" << hex << movementCounter << " but we already parsed 0x" << hex << objectMovementCounter;
			object->info(msg.toString(), true);
			return;
		}*/

		ManagedReference<CellObject*> newParent = server->getZoneServer()->getObject(parent, true).castTo<CellObject*>();

		if (newParent == NULL)
			return;

		ManagedReference<SceneObject*> parentSceneObject = newParent->getParent().get();

		if (parentSceneObject == NULL)
			return;

		BuildingObject* building = parentSceneObject->asBuildingObject();

		if (building == NULL)
			return;

		ManagedReference<SceneObject*> par = object->getParent().get();

		if (par != NULL && par->isShipObject())
			return;

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		if (playerManager == NULL)
			return;

		ValidatedPosition pos;
		pos.update(object);

		if (!ghost->hasGodMode()) {
			SceneObject* inventory = object->getSlottedObject("inventory");

			if (inventory != NULL && inventory->getCountableObjectsRecursive() > inventory->getContainerVolumeLimit() + 1) {
				object->sendSystemMessage("Inventory Overloaded - Cannot Move");
				bounceBack(object, pos);
				return;
			} else if (object->isFrozen() || !building->isAllowedEntry(object)) {
				bounceBack(object, pos);
				return;
			}
		}

		if ( par != newParent) {
			CellObject* currentCell = par.castTo<CellObject*>();
			PortalLayout *layout = building->getObjectTemplate()->getPortalLayout();
			if (layout == NULL)
				return;

			const CellProperty *cellProperty = layout->getCellProperty(newParent->getCellNumber());
			if (!cellProperty->hasConnectedCell(currentCell != NULL ? currentCell->getCellNumber() : 0)) {
				StringBuffer buf;
				buf << object->getObjectID() << " Attempted to change parents to a cell not connected to the previous parent" << endl;
				buf << "X: " << positionX << "Y: " << positionY << "Z: " << positionZ << " parentID: " << parent;
//				for (int i : cellProperty->getConnectedCells()) {
//					buf << "ConnectedCell: " << i << endl;
//				}
				object->error(buf.toString());
				bounceBack(object, pos);
				return;
			}
		}

		CellObject* cell = newParent;

		Reference<Vector<float>* > collisionPoints = CollisionManager::getCellFloorCollision(positionX, positionY, cell);

		if (collisionPoints == NULL) {
			bounceBack(object, pos);
			return;
		}

		float minErr = 16384;

		for (int i = 0; i < collisionPoints->size(); ++i) {
			float val = collisionPoints->get(i);

			float err = fabs(val - positionZ);

			//printf("collision error %f\n value %f", err, val);

			if (err < minErr) {
				minErr = err;
			}
		}

		if (minErr > 0.25) {
			bounceBack(object, pos);

			return;
		}

		ContainerPermissions* perms = newParent->getContainerPermissions();

		if (!perms->hasInheritPermissionsFromParent()) {
			if (!newParent->checkContainerPermission(object, ContainerPermissions::WALKIN)) {
				bounceBack(object, pos);

				return;
			}
		}

		WorldCoordinates coords(Vector3(positionX, positionY, positionZ), cell);
		float distance = coords.getWorldPosition().squaredDistanceTo(object->getWorldPosition());
		if (distance > 21 * 21) {
			object->info("bouncing back with distance: " + String::valueOf(distance));
			bounceBack(object, pos);

			return;
		}

		if (playerManager->checkSpeedHackFirstTest(object, parsedSpeed, pos, 1.1f) != 0)
			return;

		if (playerManager->checkSpeedHackSecondTest(object, positionX, positionZ, positionY, movementStamp, newParent) != 0)
			return;

		object->setMovementCounter(movementCounter);
		object->setDirection(directionW, directionX, directionY, directionZ);
		object->setPosition(positionX, positionZ, positionY);
		ghost->setClientLastMovementStamp(movementStamp);

		object->setCurrentSpeed(parsedSpeed);
		object->updateLocomotion();

		if (objectControllerMain->getPriority() == 0x23)
			object->updateZoneWithParent(newParent, false);
		else
			object->updateZoneWithParent(newParent, true);
	}

};


#endif /*DATATRANSFORMWITHPARENT_H_*/
