/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEINTIMIDATE2COMMAND_H_
#define FORCEINTIMIDATE2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"
#include "server/zone/objects/creature/events/ForceIntimidateTask.h"

class ForceIntimidate2Command : public ForcePowersQueueCommand {
public:

	ForceIntimidate2Command(const String& name, ZoneProcessServer* server)
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

		CreatureObject *tarCreo = targetObject->asCreatureObject();

		int res = doCombatAction(creature, target);

		if(res == SUCCESS) {
			CreatureAttackData data = CreatureAttackData("", this, target);
			Reference<SortedVector<ManagedReference<TangibleObject*> >* > targets = CombatManager::instance()->getAreaTargets(creature, creature->getWeapon(), tarCreo, data);
			if(targets->size() != 0) {
				ForceIntimidateTask *task = new ForceIntimidateTask(tarCreo, targets, this);
				task->schedule(100);
			}
		}

		return res;
	}

};

#endif //FORCEINTIMIDATE2COMMAND_H_
