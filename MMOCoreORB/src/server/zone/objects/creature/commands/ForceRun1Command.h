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
#include "JediQueueCommand.h"

class ForceRun1Command : public JediQueueCommand {
public:

	ForceRun1Command(const String& name, ZoneProcessServer* server)
: JediQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		// Do checks first.
		int res = doCommonJediSelfChecks(creature);

		if (res != SUCCESS)
			return res;


		// Construct buffs.
		Vector<uint32> buffCRCs;

		// BuffCRC's, first one is used.
		buffCRCs.add(BuffCRC::JEDI_FORCE_RUN_1);
		buffCRCs.add(BuffCRC::JEDI_FORCE_RUN_2);
		buffCRCs.add(BuffCRC::JEDI_FORCE_RUN_3);

		// Construct Skillmods.
		VectorMap<String, int> skillMods;

		// Skill mods.
		skillMods.put("force_run", 1);

		//Check for and deduct Force cost.
		float fc = forceCost;

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject && playerObject->getForcePower() <= fc) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to peform that action.
			return GENERALERROR;
		}

		// Grab LUA vars.
		int dur = duration;
		float speed = speedMod;
		String cEffect = clientEffect;

		ManagedReference<Buff*> buff = doJediSelfBuff(creature, dur, buffCRCs, skillMods, speed);

		// Add buff if it's valid.
		if (buff != NULL) {
			// SPECIAL - For Force Run.
			if (creature->hasBuff(String("burstrun").hashCode()) || creature->hasBuff(String("retreat").hashCode())) {
				creature->removeBuff(String("burstrun").hashCode());
				creature->removeBuff(String("retreat").hashCode());
			}

			// Add it.
			creature->addBuff(buff);
		}


		// Client Effect.
		if (!cEffect.isEmpty()) {
			creature->playEffect(cEffect, "");
		}

		// No Animation for this command.

		// Return.
		return SUCCESS;
	}

};

#endif //FORCERUN1COMMAND_H_
