/*
Copyright (C) 2010 <SWGEmu>

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
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/CreatureAttribute.h"

#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/BuffAttribute.h"

class ForceOfWillCommand : public QueueCommand {
public:

	ForceOfWillCommand(const String& name, ZoneProcessServerImplementation* server)
		: QueueCommand(name, server) {

	}

	void doCooldown(CreatureObject* player, String cooldownName, int duration){
		player->addCooldown(cooldownName, duration * 1000);
	}

	void doDowner(CreatureObject* player, int buffDownerValue, String buffName, float duration){
		String buffname = "skill.buff." + buffName;
		uint32 buffcrc = buffname.hashCode();
		ParameterizedStringId startMsg;

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
		buff->setStartMessage(startMsg);
		player->addBuff(buff);
	}

	void setRecovery(CreatureObject* player){
		player->setHAM(CreatureAttribute::HEALTH, 10, true);
		player->setHAM(CreatureAttribute::ACTION, 10, true);
		player->setHAM(CreatureAttribute::MIND, 10, true);
		player->setPosture(CreaturePosture::UPRIGHT, true);
		Reference<Task*> incapTask = player->getPendingTask("incapacitationRecovery");
		if (incapTask != NULL && incapTask->isScheduled()) {
			incapTask->cancel();
			player->removePendingTask("incapacitationRecovery");
		}
		doCooldown(player, "tkaForceOfWill", 3600);
		player->sendSystemMessage("teraskasi", "forceofwill");
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if(!creature->isIncapacitated()){
			creature->sendSystemMessage("teraskasi", "forceofwill_fail");
			return GENERALERROR;
		}else if(!checkInvalidPostures(creature) && creature->isIncapacitated())
			return INVALIDPOSTURE;
		if(!creature->checkCooldownRecovery("tkaForceOfWill")){
			creature->sendSystemMessage("teraskasi", "forceofwill_lost");
			return GENERALERROR;
		}
		PlayerCreature* player = (PlayerCreature*) creature;
		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();

		if(player == NULL || playerManager == NULL)
			return GENERALERROR;

		int roll = System::random(100);
		int meditateMod = player->getSkillMod("meditate");

		if(roll <= meditateMod){
			doCooldown(player, "tkaForceOfWill", 3600);
			setRecovery(player);
		}else if(roll > meditateMod){
			player->sendSystemMessage("teraskasi", "forceofwill_unsuccessful");
			doCooldown(player, "tkaForceOfWill", 3600);
		}else if(roll < 5){
			player->sendSystemMessage("teraskasi", "forceofwill_unsuccessful");
			doCooldown(player, "tkaForceOfWill", 3600);
		}else if(roll >= 5 && roll <= 10){
			player->addWounds(CreatureAttribute::HEALTH, 100, true);
			player->addWounds(CreatureAttribute::STRENGTH, 100, true);
			player->addWounds(CreatureAttribute::CONSTITUTION, 100, true);
			player->addWounds(CreatureAttribute::ACTION, 100, true);
			player->addWounds(CreatureAttribute::QUICKNESS, 100, true);
			player->addWounds(CreatureAttribute::STAMINA, 100, true);
			player->addWounds(CreatureAttribute::MIND, 100, true);
			player->addWounds(CreatureAttribute::FOCUS, 100, true);
			player->addWounds(CreatureAttribute::WILLPOWER, 100, true);
			player->addShockWounds(100, true);
			setRecovery(player);
		}else if(roll >= 10 && roll <= 40){
			player->addShockWounds(100, true);
			doDowner(player, 200, "forceofwill2", 300);
			setRecovery(player);
		}else if(roll >= 40 && roll <= 70){
			doDowner(player, 100, "forceofwill3", 120);
			setRecovery(player);
		}else if(roll >= 70 && roll <= 100){
			setRecovery(player);
		}

		return SUCCESS;
	}
};

#endif //FORCEOFWILLCOMMAND_H_
