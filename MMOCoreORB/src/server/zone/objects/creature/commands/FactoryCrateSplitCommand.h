/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FACTORYCRATESPLITCOMMAND_H_
#define FACTORYCRATESPLITCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class FactoryCrateSplitCommand : public QueueCommand {
public:

	FactoryCrateSplitCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer tokenizer(arguments.toString());
		int newStackSize = tokenizer.getIntToken();

		if (newStackSize < 1)
			return GENERALERROR;

		ManagedReference<FactoryCrate* > factoryCrate = server->getZoneServer()->getObject(target).castTo<FactoryCrate*>();

		if (factoryCrate == NULL || !creature->isPlayerCreature())
			return INVALIDTARGET;

		if(!factoryCrate->isASubChildOf(creature)) {
			creature->sendSystemMessage("@container_error_message:container08");
			return INVALIDTARGET;
		}

		Locker locker(factoryCrate, creature);

		ManagedReference<SceneObject*> objectsParent = factoryCrate->getParent();


		if(objectsParent == NULL)
			return GENERALERROR;

		if (objectsParent->isCellObject()) {

			ManagedReference<BuildingObject*> building = cast<BuildingObject*>( objectsParent->getParent().get().get());

			if (!building->isOnAdminList(creature)) {
				return GENERALERROR;
			}
		}

		if(objectsParent->getContainerVolumeLimit() - objectsParent->getContainerObjectsSize() < 1){
			creature->sendSystemMessage("@treasure_map/treasure_map:sys_inventory_full");
			return GENERALERROR;
		}

		factoryCrate->split(newStackSize);

		return SUCCESS;
	}

};

#endif //FACTORYCRATESPLITCOMMAND_H_
