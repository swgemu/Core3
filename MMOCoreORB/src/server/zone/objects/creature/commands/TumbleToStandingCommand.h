/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TUMBLETOSTANDINGCOMMAND_H_
#define TUMBLETOSTANDINGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/events/AnimationTask.h"

class TumbleToStandingCommand : public QueueCommand {
public:

	TumbleToStandingCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}
	

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->checkDizzyDelay() && creature->isDizzied()) {
			creature->queueDizzyFallEvent();
		} else {
			//Check for and deduct HAM cost.
			int actionCost = creature->calculateCostAdjustment(CreatureAttribute::QUICKNESS, 100);
			if (creature->getHAM(CreatureAttribute::ACTION) <= actionCost)
				return INSUFFICIENTHAM;

			creature->inflictDamage(creature, CreatureAttribute::ACTION, actionCost, true);


			creature->setPosture(CreaturePosture::UPRIGHT, false);

			if (creature->isDizzied())
				creature->queueDizzyFallEvent();

			Reference<CreatureObject*> defender = server->getZoneServer()->getObject(target).castTo<CreatureObject*>();
			if (defender == NULL)
				creature->doCombatAnimation(creature,String("tumble").hashCode(),0,0xFF);
			else
				creature->doCombatAnimation(defender,String("tumble_facing").hashCode(),0,0xFF);

			Reference<StateBuff*> buff = new StateBuff(creature, CreatureState::TUMBLING, 1);

			buff->setSkillModifier("melee_defense", 50);
			buff->setSkillModifier("ranged_defense", 50);

			creature->addBuff(buff);

			CreatureObjectDeltaMessage3* pmsg = new CreatureObjectDeltaMessage3(creature);
			pmsg->updatePosture();
			pmsg->close();
			creature->broadcastMessage(pmsg, true);
			creature->sendStateCombatSpam("cbt_spam", "tum_standing", 0);
		}

		return SUCCESS;
	}

};

#endif //TUMBLETOSTANDINGCOMMAND_H_
