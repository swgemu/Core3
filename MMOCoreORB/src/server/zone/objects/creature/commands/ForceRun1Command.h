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

#ifndef FORCERUN1COMMAND_H_
#define FORCERUN1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/buffs/Buff.h"

class ForceRun1Command : public QueueCommand {
public:

	ForceRun1Command(const String& name, ZoneProcessServer* server)
	: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		uint32 forceRun1CRC = BuffCRC::JEDI_FORCE_RUN_1;
		uint32 forceRun2CRC = BuffCRC::JEDI_FORCE_RUN_2;
		uint32 forceRun3CRC = BuffCRC::JEDI_FORCE_RUN_3;

		if(creature->hasBuff(forceRun1CRC) || creature->hasBuff(forceRun2CRC) || creature->hasBuff(forceRun3CRC)) {
			creature->sendSystemMessage("@jedi_spam:force_buff_present"); //"You already have a similar Force enhancement active."
			return GENERALERROR;
		}

		if (creature->hasBuff(String("burstrun").hashCode()) || creature->hasBuff(String("retreat").hashCode())) {
			creature->removeBuff(String("burstrun").hashCode());
			creature->removeBuff(String("retreat").hashCode());
		}

		// Force cost of skill.
		int forceCost = 200;

		//Check for and deduct Force cost.

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject->getForcePower() <= forceCost) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to peform that action.
			return GENERALERROR;
		}

		playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		StringIdChatParameter startStringId("jedi_spam", "apply_forcerun1");
		StringIdChatParameter endStringId("jedi_spam", "remove_forcerun1");

		int duration = 120;

		ManagedReference<Buff*> buff = new Buff(creature, forceRun1CRC, duration, BuffType::JEDI);
		buff->setSpeedMultiplierMod(1.5f);
		buff->setAccelerationMultiplierMod(1.5f);
		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);
		buff->setSkillModifier("force_run", 1);

		creature->addBuff(buff);
		creature->playEffect("clienteffect/pl_force_run_self.cef", "");

		return SUCCESS;
	}

};

#endif //FORCERUN1COMMAND_H_
