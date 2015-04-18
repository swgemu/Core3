/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BERSERK2COMMAND_H_
#define BERSERK2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class Berserk2Command : public QueueCommand {
public:

	Berserk2Command(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<WeaponObject*> weapon = creature->getWeapon();

		if (!weapon->isMeleeWeapon() && !weapon->isUnarmedWeapon()) {
			if (creature->isPlayerCreature())
				(cast<CreatureObject*>(creature))->sendSystemMessage("@cbt_spam:berserk_fail_single");

			creature->sendStateCombatSpam("cbt_spam", "berserk_fail", 0);
			return INVALIDWEAPON;
		}

		if (!creature->isInCombat()) {
			if (creature->isPlayerCreature())
				(cast<CreatureObject*>(creature))->sendSystemMessage("@cbt_spam:berserk_fail_single");

			creature->sendStateCombatSpam("cbt_spam", "berserk_fail", 0);
			return GENERALERROR;
		}

		int actionCost = creature->calculateCostAdjustment(CreatureAttribute::QUICKNESS, 50);

		if (creature->getHAM(CreatureAttribute::ACTION) <= actionCost) {
			if (creature->isPlayerCreature())
				(cast<CreatureObject*>(creature))->sendSystemMessage("@cbt_spam:berserk_fail_single");

			creature->sendStateCombatSpam("cbt_spam", "berserk_fail", 0);
			return GENERALERROR;
		}

		creature->inflictDamage(creature, CreatureAttribute::ACTION, actionCost, true);

		creature->setBerserkedState(40);
		//creature->setBerserkDamage(25);

		if (creature->isPlayerCreature())
			(cast<CreatureObject*>(creature))->sendSystemMessage("@cbt_spam:berserk_success_single");


		creature->sendStateCombatSpam("cbt_spam", "berserk_success", 0);
		return SUCCESS;
	}

};

#endif //BERSERK2COMMAND_H_
