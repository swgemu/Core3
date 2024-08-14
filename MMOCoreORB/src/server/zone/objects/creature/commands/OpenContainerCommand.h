/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef OPENCONTAINERCOMMAND_H_
#define OPENCONTAINERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/Container.h"
#include "server/zone/objects/tangible/RelockLootContainerEvent.h"

class OpenContainerCommand : public QueueCommand {
public:
	OpenContainerCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> objectToOpen = zoneServer->getObject(target);

		if (objectToOpen == nullptr) {
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> objectsParent = objectToOpen->getParent();
		bool craftingStation = objectsParent != nullptr && objectsParent->isCraftingStation();

		bool playerItem = objectToOpen->getParentRecursively(SceneObjectType::PLAYERCREATURE) != nullptr;

		ManagedReference<SceneObject*> rootParent = objectToOpen->getRootParent();
		bool clientObject = rootParent != nullptr && rootParent->isClientObject();

		if (craftingStation) {
			if (!creature->isInRange(objectsParent, 12.0f)) {
				StringIdChatParameter param;
				param.setStringId("@container_error_message:container09_prose"); // You are out of range of %TT.
				param.setTT(objectsParent->getObjectName());
				creature->sendSystemMessage(param);
				return TOOFAR;
			}

			if (!CollisionManager::checkLineOfSight(objectsParent, creature)) {
				StringIdChatParameter msgParam;
				msgParam.setStringId("@container_error_message:container18_prose"); // You can't see %TT. You may have to move closer to it.
				msgParam.setTT(objectsParent->getObjectName());
				creature->sendSystemMessage(msgParam);
				return GENERALERROR;
			}
		} else if (objectToOpen->isTurret() || (!playerItem && (objectsParent == nullptr || clientObject))) { //Perform checks if not player item and outside, or inside in clientObject structure
			if (!creature->isInRange(objectToOpen, 7.0f)) {
				StringIdChatParameter param;
				param.setStringId("@container_error_message:container09_prose"); // You are out of range of %TT.
				param.setTT(objectToOpen->getObjectName());
				creature->sendSystemMessage(param);
				return TOOFAR;
			}

			if (!CollisionManager::checkLineOfSight(objectToOpen, creature)) {
				StringIdChatParameter msgParam;
				msgParam.setStringId("@container_error_message:container18_prose"); // You can't see %TT. You may have to move closer to it.
				msgParam.setTT(objectToOpen->getObjectName());
				creature->sendSystemMessage(msgParam);
				return GENERALERROR;
			}
		}

		Locker clocker(objectToOpen, creature);

		/*
		ManagedReference<SceneObject*> objectsParent = objectToOpen->getParent();

		if (objectsParent != nullptr && objectsParent->isCellObject()) {
			ManagedReference<BuildingObject*> building = cast<BuildingObject*>( objectsParent->getParent());

			if (!building->isOnAdminList(creature->getFirstName())) {
				// info("not on admin list", true);
				return GENERALERROR;
			}
		} else if (!objectToOpen->isASubChildOf(creature)) {
			return GENERALERROR;
		}*/

		/* if (objectToOpen->isContainerObject()) {
			ManagedReference<Container*> container = cast<Container*>(objectToOpen.get());
			Zone* zone = creature->getZone();
			if (zone->getZoneName() != "tutorial" && (container->checkPermission(creature) == 0))
				return GENERALERROR;
		}*/

		ManagedReference<Container*> container = objectToOpen.castTo<Container*>();

		if (container != nullptr && container->isContainerLocked()) {
			creature->sendSystemMessage("@slicing/slicing:locked");
			return SUCCESS;
		}

		if (objectToOpen->checkContainerPermission(creature, ContainerPermissions::OPEN)) {
			if (objectToOpen->getGameObjectType() == SceneObjectType::STATICLOOTCONTAINER) {
				if (container != nullptr && container->isRelocking() == false) {
					Reference<RelockLootContainerEvent*> relockEvent = new RelockLootContainerEvent(container);
					relockEvent->schedule(container->getLockTime());
				}
			}

			objectToOpen->openContainerTo(creature);

			objectToOpen->notifyObservers(ObserverEventType::OPENCONTAINER, creature);
		} else {
			// You do not have permission to access this container.
			creature->sendSystemMessage("@error_message:perm_no_open");
		}

		return SUCCESS;
	}
};

#endif // OPENCONTAINERCOMMAND_H_
