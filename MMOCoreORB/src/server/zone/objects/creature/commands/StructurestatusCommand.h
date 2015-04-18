/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STRUCTURESTATUSCOMMAND_H_
#define STRUCTURESTATUSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/structure/StructureManager.h"

class StructurestatusCommand : public QueueCommand {
public:

	StructurestatusCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();
		ManagedReference<SceneObject*> obj = playerManager->getInRangeStructureWithAdminRights(creature, creature->getTargetID());

		if (obj == NULL || !obj->isStructureObject() || obj->getZone() == NULL) {
			creature->sendSystemMessage("@player_structure:no_building"); //you must be in a building, be near an installation, or have one targeted to do that.
			return INVALIDTARGET;
		}

		StructureObject* structure = cast<StructureObject*>( obj.get());

		StructureManager::instance()->reportStructureStatus(creature, structure);

		return SUCCESS;
	}

};

#endif //STRUCTURESTATUSCOMMAND_H_
