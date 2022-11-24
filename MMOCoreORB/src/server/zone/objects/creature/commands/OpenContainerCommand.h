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

		ManagedReference<SceneObject*> objectToOpen = nullptr;

		StringTokenizer args(arguments.toString());

		// creature->info(true) << "OpenContainerCommand called Target = " << target << " Args = " << arguments.toString();

		int counter = 0;
		if (args.hasMoreTokens())
			counter = args.getIntToken();

		objectToOpen = server->getZoneServer()->getObject(target);

		if (objectToOpen == nullptr) {
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> objectParent = objectToOpen->getParent().get();

		if (objectParent != nullptr && objectParent->isCraftingStation()) {
			if (!creature->isInRange(objectParent, 12.0f)) {
				StringIdChatParameter param;
				param.setStringId("@container_error_message:container09_prose"); // You are out of range of %TT.
				param.setTT(objectToOpen->getObjectName());
				creature->sendSystemMessage(param);

				return TOOFAR;
			}

			if (!CollisionManager::checkLineOfSight(objectParent, creature)) {
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
