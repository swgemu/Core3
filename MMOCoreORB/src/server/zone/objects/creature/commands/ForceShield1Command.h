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

#ifndef FORCESHIELD1COMMAND_H_
#define FORCESHIELD1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/buffs/SingleUseBuff.h"

class ForceShield1Command : public QueueCommand {
public:

	ForceShield1Command(const String& name, ZoneProcessServer* server)
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

		uint32 buffcrc1 = BuffCRC::JEDI_FORCE_SHIELD_1;
		uint32 buffcrc2 = BuffCRC::JEDI_FORCE_SHIELD_2;

		if(creature->hasBuff(buffcrc1) || creature->hasBuff(buffcrc2)) {
			creature->sendSystemMessage("@jedi_spam:force_buff_present");
			return GENERALERROR;
		}


		// Force cost of skill.
		int forceCost = 75;


		//Check for and deduct Force cost.

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();


		if (playerObject->getForcePower() <= forceCost) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to peform that action.

			return GENERALERROR;
		}

		playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		StringIdChatParameter startStringId("jedi_spam", "apply_forceshield1");
		StringIdChatParameter endStringId("jedi_spam", "remove_forceshield1");

		int duration = 900;

		Vector<unsigned int> eventTypes;
		eventTypes.add(ObserverEventType::FORCEBUFFHIT);

		ManagedReference<SingleUseBuff*> buff = new SingleUseBuff(creature, buffcrc1, duration, BuffType::JEDI, getNameCRC());
		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);
		buff->setSkillModifier("force_shield", 25);
		buff->init(&eventTypes);

		creature->addBuff(buff);
		creature->playEffect("clienteffect/pl_force_shield_self.cef", "");

		return SUCCESS;
	}

	void handleBuff(SceneObject* creature, ManagedObject* object, int64 param) {

		ManagedReference<CreatureObject*> creo = cast<CreatureObject*>( creature);

		ManagedReference<PlayerObject*> playerObject = creo->getPlayerObject();

		if (playerObject != NULL) { // TODO: Force Rank modifiers.

			// Client Effect upon hit (needed)
			creo->playEffect("clienteffect/pl_force_shield_hit.cef", "");

			int fP = playerObject->getForcePower();
			int forceCost = param * 0.3;

			if (fP <= forceCost){ // Remove buff if not enough force.
				SingleUseBuff* buff = cast<SingleUseBuff*>( creo->getBuff(BuffCRC::JEDI_FORCE_SHIELD_1));

				if (buff != NULL)
					creo->removeBuff(buff);
			}

			else playerObject->setForcePower(playerObject->getForcePower() - forceCost);
		}
	}

};

#endif //FORCESHIELD1COMMAND_H_
