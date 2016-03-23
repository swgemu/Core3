/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCECHOKECOMMAND_H_
#define FORCECHOKECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
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

		// Each tick's damage should be random amount in between 175-375
		float damageMultiplier = System::random(9);
		int tickDamage = 175 + (damageMultiplier * 25);

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		if (targetObject == NULL || !targetObject->isCreatureObject()) {
			return INVALIDTARGET;
		}

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {

			ManagedReference<CreatureObject*> creature = targetObject.castTo<CreatureObject*>();
			ManagedReference<CreatureObject*> creatureTarget = targetObject.castTo<CreatureObject*>();

			Reference<ForceChokeTickTask*> chokeCheck = creatureTarget.get()->getPendingTask("forceChokeTickTask").castTo<ForceChokeTickTask*>();

			if (targetObject != NULL) {
				Locker locker(creatureTarget);
				Reference<ForceChokeTickTask*> tickTask = new ForceChokeTickTask(creatureTarget, creature, tickDamage);

				if (chokeCheck == NULL) {
					creatureTarget->addPendingTask("forceChokeTickTask", tickTask, 5000);
				}
				else {
					// How can we decipher whether or not the CURRENT choke tick is higher damage than new one?
					creatureTarget->removePendingTask("forceChokeTickTask");
				}

			}

		}

		return res;
	}

};

#endif //FORCECHOKECOMMAND_H_
