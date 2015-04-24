/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TAKECOVERCOMMAND_H_
#define TAKECOVERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "QueueCommand.h"
#include "server/zone/objects/creature/buffs/Buff.h"

class TakeCoverCommand : public QueueCommand {
public:

	TakeCoverCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		int actionCost = creature->calculateCostAdjustment(CreatureAttribute::QUICKNESS, 50);
		if (creature->getHAM(CreatureAttribute::ACTION)  < actionCost) {

			if (creature->isPlayerCreature())
				(creature)->sendSystemMessage("@cbt_spam:cover_fail_single"); // You fail to take cover.

			creature->sendStateCombatSpam("cbt_spam", "cover_fail", 0);
			return GENERALERROR;
		}

		if (creature->isInCombat()) {
			
			//TODO: chance = 10 + creature->getSkillMod("cover");
			//Correct system message
			int chance = 75;
			if (System::random(100)  > chance) {

				if (creature->isPlayerCreature())
					(creature)->sendSystemMessage("@cbt_spam:cover_fail_single"); // You fail to take cover.

				creature->sendStateCombatSpam("cbt_spam", "cover_fail", 0);
				return GENERALERROR;
			}
		}

		if (creature->isDizzied() && System::random(100) < 85) {
			creature->queueDizzyFallEvent();
		} else {
			creature->setCoverState();

			creature->inflictDamage(creature, CreatureAttribute::ACTION, actionCost, false);
			creature->sendStateCombatSpam("cbt_spam", "cover_success", 0);
		}

		return SUCCESS;
	}

};

#endif //TAKECOVERCOMMAND_H_
