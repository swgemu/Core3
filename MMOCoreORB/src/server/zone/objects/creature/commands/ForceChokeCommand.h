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

		// Each tick's damage should be random amount in between 100-500 ??
		int damage = System::random(10);
		int tickDamage = 100 + (damage * 40);

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		if (targetObject == NULL || !targetObject->isCreatureObject()) {
			return INVALIDTARGET;
		}

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {

			targetObject->playEffect("clienteffect/pl_force_choke.cef", "");
			ManagedReference<CreatureObject*> creature = targetObject.castTo<CreatureObject*>();
			ManagedReference<CreatureObject*> creatureTarget = targetObject.castTo<CreatureObject*>();

			if (targetObject != NULL) {

				Locker locker(creature);

				ManagedReference<PrivateBuff*> choke = new PrivateBuff(creature, getNameCRC(), 35, BuffType::OTHER);
				creature->addBuff(choke);

				Reference<ForceChokeTickTask*> tickTask = new ForceChokeTickTask(creature, creatureTarget, tickDamage);
				creature->addPendingTask("forceChokeTickTask", tickTask, 6000);

			}

		}

		return res;

	}

};

#endif //FORCECHOKECOMMAND_H_
