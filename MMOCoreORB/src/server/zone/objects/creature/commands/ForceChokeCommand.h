/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCECHOKECOMMAND_H_
#define FORCECHOKECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"
#include "server/zone/objects/player/events/ForceChokeTickTask.h"

class ForceChokeCommand : public ForcePowersQueueCommand {
public:

	ForceChokeCommand(const String& name, ZoneProcessServer* server)
		: ForcePowersQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		if (targetObject == NULL || !targetObject->isCreatureObject()) {
			return INVALIDTARGET;
		}

		int res = doCombatAction(creature, target);

		//if (creature->isAiAgent()) { // If they are NPC, don't get past here.
		//	return SUCCESS;
		//}

		if (res == SUCCESS) {

			// Setup task, if choke attack was successful (5 tick amount.), AND if they don't already have one.

			ManagedReference<CreatureObject*> creatureTarget = targetObject.castTo<CreatureObject*>();

			if (creatureTarget == NULL)
				return GENERALERROR;

			Reference<ForceChokeTickTask*> chokeCheck = creatureTarget->getPendingTask("forceChokeTickTask").castTo<ForceChokeTickTask*>();

			if (chokeCheck != NULL) {
				return SUCCESS;
			}

			Reference<ForceChokeTickTask*> fctTask = new ForceChokeTickTask(creature, creatureTarget);
			creatureTarget->addPendingTask("forceChokeTickTask", fctTask, 6000);
		}

		return SUCCESS;
	}

};

#endif //FORCECHOKECOMMAND_H_
