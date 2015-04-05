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

#ifndef AVOIDINCAPACITATIONCOMMAND_H_
#define AVOIDINCAPACITATIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class AvoidIncapacitationCommand : public QueueCommand {
public:

	AvoidIncapacitationCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		uint32 buffcrc;

		uint32 buffcrc1 = BuffCRC::JEDI_AVOID_INCAPACITATION;
		uint32 buffcrc2 = BuffCRC::JEDI_AVOID_INCAPACITATION_1;
		uint32 buffcrc3 = BuffCRC::JEDI_AVOID_INCAPACITATION_2;
		uint32 buffcrc4 = BuffCRC::JEDI_AVOID_INCAPACITATION_3;
		uint32 buffcrc5 = BuffCRC::JEDI_AVOID_INCAPACITATION_4;
		uint32 buffcrc6 = BuffCRC::JEDI_AVOID_INCAPACITATION_5;

		if(creature->hasBuff(buffcrc1)) {
;			buffcrc = buffcrc2;
		}

		else if (creature->hasBuff(buffcrc2)) {
			buffcrc = buffcrc3;
		}


		else if (creature->hasBuff(buffcrc3)) {
			buffcrc = buffcrc4;
		}

		else if (creature->hasBuff(buffcrc4)) {
			buffcrc = buffcrc5;
		}

		else if (creature->hasBuff(buffcrc5)) {
			buffcrc = buffcrc6;
		}

		else buffcrc = buffcrc1;


		// Force cost of skill.
		int forceCost = 750;


		//Check for and deduct Force cost.

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();


		if (playerObject->getForcePower() <= forceCost) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to peform that action.

			return GENERALERROR;
		}

		playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		StringIdChatParameter startStringId("jedi_spam", "apply_avoidincapacitation");
		StringIdChatParameter endStringId("jedi_spam", "remove_avoidincapacitation");

		int duration = 30;

		ManagedReference<Buff*> buff = new Buff(creature, buffcrc, duration, BuffType::JEDI);
		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);
		buff->setSkillModifier("avoid_incapacitation", 1);

		creature->addBuff(buff);
		creature->playEffect("clienteffect/pl_force_avoid_incap_self.cef", "");


		return SUCCESS;
	}

};

#endif //AVOIDINCAPACITATIONCOMMAND_H_
