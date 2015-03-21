/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef FORCEOFWILLCOMMAND_H_
#define FORCEOFWILLCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"

#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/BuffAttribute.h"

class ForceOfWillCommand : public QueueCommand {

	void doDowner(CreatureObject* player, int buffDownerValue, float duration) {
			String buffname = "skill.buff.forceofwill";
			uint32 buffcrc = buffname.hashCode();
			//StringIdChatParameter startMsg;

			Reference<Buff*> buff = new Buff(player, buffname.hashCode(), duration, BuffType::SKILL);
			buff->setAttributeModifier(CreatureAttribute::HEALTH, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::STRENGTH, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::CONSTITUTION, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::ACTION, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::QUICKNESS, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::STAMINA, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::MIND, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::FOCUS, -buffDownerValue);
			buff->setAttributeModifier(CreatureAttribute::WILLPOWER, -buffDownerValue);
			//buff->setStartMessage(startMsg);
			player->addBuff(buff);
		}

public:

	ForceOfWillCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
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
