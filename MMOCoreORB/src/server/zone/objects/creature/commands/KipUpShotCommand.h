/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef KIPUPSHOTCOMMAND_H_
#define KIPUPSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class KipUpShotCommand : public CombatQueueCommand {
public:

	KipUpShotCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<WeaponObject*> weapon = creature->getWeapon();

		if (!weapon->isPistolWeapon()) {
			return INVALIDWEAPON;
		}

		int ret = doCombatAction(creature, target);

		if (ret != SUCCESS)
			return ret;

		if (!creature->checkDizzyDelay() && creature->isDizzied()) {
			creature->queueDizzyFallEvent();
		} else {
			creature->setPosture(CreaturePosture::UPRIGHT, false);

			if (creature->isDizzied())
				creature->queueDizzyFallEvent();

			CreatureObjectDeltaMessage3* pmsg = new CreatureObjectDeltaMessage3(creature);
			pmsg->updatePosture();
			pmsg->close();
			creature->broadcastMessage(pmsg, true);
		}

		return SUCCESS;
	}

};

#endif //KIPUPSHOTCOMMAND_H_
