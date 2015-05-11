/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEOFWILLCOMMAND_H_
#define FORCEOFWILLCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"

#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/BuffAttribute.h"

class ForceOfWillCommand : public QueueCommand {

	void doDowner(CreatureObject* player, int buffDownerValue, float duration) const {
			String buffname = "skill.buff.forceofwill";
			uint32 buffcrc = buffname.hashCode();

			Reference<Buff*> buff = new Buff(player, buffname.hashCode(), duration, BuffType::SKILL);

			Locker locker(buff);

			buff->setAttributeModifier(CreatureAttribute::HEALTH, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::STRENGTH, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::CONSTITUTION, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::ACTION, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::QUICKNESS, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::STAMINA, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::MIND, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::FOCUS, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::WILLPOWER, -buffDownerValue);
			player->addBuff(buff);
		}

public:

	ForceOfWillCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*>(creature);

		Reference<Task*> incapTask = player->getPendingTask("incapacitationRecovery");

		if (!creature->isIncapacitated() || incapTask == NULL || !incapTask->isScheduled()) {
			creature->sendSystemMessage("@teraskasi:forceofwill_fail"); //You must be incapacitated to perform that command.
			return GENERALERROR;
		}

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!player->checkCooldownRecovery("tkaForceOfWill")) {
			player->sendSystemMessage("@teraskasi:forceofwill_lost"); //You have already expired your opportunity for forced recapacitation.
			return GENERALERROR;
		}

		int meditateMod = player->getSkillMod("meditate");
		int roll = System::random(100);
		int deltaRoll = meditateMod - roll;

		//Handle our failures.
		if (roll < 5 || roll > meditateMod) {
			player->sendSystemMessage("@teraskasi:forceofwill_unsuccessful"); //You are unable to keep yourself centered, and become lost in unconsciousness.
			Time nextExecutionTime;
			Core::getTaskManager()->getNextExecutionTime(incapTask, nextExecutionTime);
			player->addCooldown("tkaForceOfWill", nextExecutionTime.miliDifference()); //Disable the command until the current incapacitation is up.

			return GENERALERROR;
		}

		//Handle successes.
		if (deltaRoll < 10) {
			player->addWounds(CreatureAttribute::HEALTH, 100, true, false);
			player->addWounds(CreatureAttribute::STRENGTH, 100, true, false);
			player->addWounds(CreatureAttribute::CONSTITUTION, 100, true, false);
			player->addWounds(CreatureAttribute::ACTION, 100, true, false);
			player->addWounds(CreatureAttribute::QUICKNESS, 100, true, false);
			player->addWounds(CreatureAttribute::STAMINA, 100, true, false);
			player->addWounds(CreatureAttribute::MIND, 100, true, false);
			player->addWounds(CreatureAttribute::FOCUS, 100, true, false);
			player->addWounds(CreatureAttribute::WILLPOWER, 100, true, false);
			player->addShockWounds(100, true);

			player->sendSystemMessage("@teraskasi:forceofwill_crit_fail"); //You strain to bring yourself back to consciousness.
		} else if (deltaRoll < 40) {
			player->addShockWounds(100, true);
			doDowner(player, 200, 300);
			player->sendSystemMessage("@teraskasi:forceofwill_marginal"); //A strong sense of fatigue overcomes you as you return to consciousness.
		} else if (deltaRoll < 70) {
			doDowner(player, 100, 120);
			player->sendSystemMessage("@teraskasi:forceofwill_normal"); //You recapacitate with a marginal groginess.
		} else {
			player->sendSystemMessage("@teraskasi:forceofwill_exceptional"); //Through precise focus and concentration, you recapacitate with nominal side effects.
		}

		player->setPosture(CreaturePosture::UPRIGHT, true);
		incapTask->cancel();
		player->removePendingTask("incapacitationRecovery");
		player->addCooldown("tkaForceOfWill", 3600 * 1000);

		return SUCCESS;
	}
};

#endif //FORCEOFWILLCOMMAND_H_
