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

#include "JediQueueCommand.h"

class AvoidIncapacitationCommand : public JediQueueCommand {
public:

	AvoidIncapacitationCommand(const String& name, ZoneProcessServer* server)
: JediQueueCommand(name, server) {
		// since this is a special case buff, these CRC's aren't exclusive. Instead we will use this list to select whichever one is not active
		buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION);
		buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION_1);
		buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION_2);
		buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION_3);
		buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION_4);
		buffCRCs.add(BuffCRC::JEDI_AVOID_INCAPACITATION_5);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		// SPECIAL - For Avoid Incapacitation, it can be stacked up to 6 times for a new buff object, and needs a new crc.
		uint32 buffCRCUsed = -1;

		for (int i=0; i < buffCRCs.size(); i++) {
			if (!creature->hasBuff(buffCRCs.get(i))) {
				buffCRCUsed = buffCRCs.get(i);
				break;
			}
		}

		if (buffCRCUsed == -1)
			return GENERALERROR;

		// Avoid Incap is a special case since it stacks (whereas all other jedi buffs do not stack), so forego the
		// existing structure and build the buff manually

		int res = doCommonJediSelfChecks(creature);

		if (res != SUCCESS)
			return res;

		ManagedReference<Buff*> buff = new Buff(creature, buffCRCUsed, duration, BuffType::JEDI);
		buff->setSkillModifier("avoid_incapacitation", 1);
		creature->addBuff(buff);

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();
		playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		if (!clientEffect.isEmpty())
			creature->playEffect(clientEffect, "");

		return SUCCESS;
	}

};

#endif //AVOIDINCAPACITATIONCOMMAND_H_
