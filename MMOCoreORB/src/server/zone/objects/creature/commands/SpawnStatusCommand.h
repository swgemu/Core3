/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SPAWNSTATUSCOMMAND_H_
#define SPAWNSTATUSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/CreatureObject.h"

class SpawnStatusCommand : public QueueCommand {
public:

	SpawnStatusCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		PlayerObject* ghost = creature->getPlayerObject();
		if (!ghost->isPrivileged())
			return INSUFFICIENTPERMISSION;

		ManagedReference<AiAgent*> targetObj = server->getZoneServer()->getObject(creature->getTargetID()).castTo<AiAgent*>();
		if (targetObj == NULL)
			return GENERALERROR;

		targetObj->outputLuaTimes(creature);

		return SUCCESS;
	}

};

#endif //SPAWNSTATUSCOMMAND_H_
