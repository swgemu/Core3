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

	OpenContainerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		//creature->info("OpenContainerCommand", true);

		ManagedReference<SceneObject*> objectToOpen = NULL;

		StringTokenizer args(arguments.toString());

		int counter = 0;
		if(args.hasMoreTokens())
			counter = args.getIntToken();

		objectToOpen = server->getZoneServer()->getObject(target);

		if (objectToOpen == NULL)
			return GENERALERROR;

		/// This is weird, when you select a schematic and the crafting station has a
		/// Hopper the client requests to open the hopper container to the player
		/// Which isn't supposed to happen
		if(objectToOpen->getParent() != NULL && objectToOpen->getParent().get()->isCraftingStation())
			return GENERALERROR;

		Locker clocker(objectToOpen, creature);

/*
		ManagedReference<SceneObject*> objectsParent = objectToOpen->getParent();

		if (objectsParent != NULL && objectsParent->isCellObject()) {
			ManagedReference<BuildingObject*> building = cast<BuildingObject*>( objectsParent->getParent());

			if (!building->isOnAdminList(creature->getFirstName())) {
				//info("not on admin list", true);
				return GENERALERROR;
			}
		} else if (!objectToOpen->isASubChildOf(creature)) {
			return GENERALERROR;
		}*/

	/*	if (objectToOpen->isContainerObject()) {
			ManagedReference<Container*> container = cast<Container*>(objectToOpen.get());
			Zone* zone = creature->getZone();
			if (zone->getZoneName() != "tutorial" && (container->checkPermission(creature) == 0))
				return GENERALERROR;
		}

*/

		ManagedReference<Container*> container = objectToOpen.castTo<Container*>();
		if(container != NULL && container->isContainerLocked()) {
			creature->sendSystemMessage("@slicing/slicing:locked");
			return SUCCESS;
		}


		if (objectToOpen->checkContainerPermission(creature, ContainerPermissions::OPEN)) {

			if(objectToOpen->getGameObjectType() == SceneObjectType::STATICLOOTCONTAINER) {
				if(container != NULL && container->isRelocking() == false) {
					Reference<RelockLootContainerEvent*> relockEvent = new RelockLootContainerEvent(container);
					relockEvent->schedule(container->getLockTime());
				}
			}

			objectToOpen->openContainerTo(creature);

			objectToOpen->notifyObservers(ObserverEventType::OPENCONTAINER, creature);
		} else {
			//You do not have permission to access this container.
			creature->sendSystemMessage("@error_message:perm_no_open");
		}

		return SUCCESS;
	}

};

#endif //OPENCONTAINERCOMMAND_H_
