/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TUMBLETOKNEELINGCOMMAND_H_
#define TUMBLETOKNEELINGCOMMAND_H_

#include "server/zone/objects/creature/buffs/StateBuff.h"

class TumbleToKneelingCommand : public QueueCommand {
public:

	TumbleToKneelingCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->hasAttackDelay() || !creature->checkPostureChangeDelay())
			return GENERALERROR;

		if (creature->isDizzied() && System::random(100) < 85) {
			creature->queueDizzyFallEvent();
		} else {
			//Check for and deduct HAM cost.
			int actionCost = creature->calculateCostAdjustment(CreatureAttribute::QUICKNESS, 100);
			if (creature->getHAM(CreatureAttribute::ACTION) <= actionCost)
				return INSUFFICIENTHAM;

			creature->inflictDamage(creature, CreatureAttribute::ACTION, actionCost, true);

			creature->setPosture(CreaturePosture::CROUCHED, false, true);

			Reference<CreatureObject*> defender = server->getZoneServer()->getObject(target).castTo<CreatureObject*>();
			if (defender == NULL)
				creature->doCombatAnimation(creature,STRING_HASHCODE("tumble"),0,0xFF);
			else
				creature->doCombatAnimation(defender,STRING_HASHCODE("tumble_facing"),0,0xFF);

			Reference<StateBuff*> buff = new StateBuff(creature, CreatureState::TUMBLING, 1);

			Locker locker(buff);

			buff->setSkillModifier("melee_defense", 50);
			buff->setSkillModifier("ranged_defense", 50);

			creature->addBuff(buff);

			locker.release();

			creature->sendStateCombatSpam("cbt_spam", "tum_kneel", 0);
		}

		return SUCCESS;
	}

};

#endif //TUMBLETOKNEELINGCOMMAND_H_
