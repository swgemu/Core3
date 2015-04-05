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

#ifndef REGAINCONSCIOUSNESSCOMMAND_H_
#define REGAINCONSCIOUSNESSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/events/RegainConsciousnessRegenTask.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"

class RegainConsciousnessCommand : public QueueCommand {
public:

	RegainConsciousnessCommand(const String& name, ZoneProcessServer* server)
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

		// Force cost of skill.
		int forceCost = 1000;


		//Check for and deduct Force cost.

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();


		if (playerObject->getForcePower() <= forceCost) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to peform that action.
			return GENERALERROR;
		}

		// They should be dead...
		if (creature->isDead()){
			// Revive user by setting posture to standing.
			creature->setPosture(CreaturePosture::UPRIGHT);

			// Unsure if this was used in live?
			 creature->playEffect("clienteffect/pl_force_regain_consciousness_self.cef", "");

			// Do the 1 minute of grogginess suffering (no actions can be taken.)
			// TODO: Unsure how to do this.

			playerObject->setForcePower(playerObject->getForcePower() - forceCost);

			// Cut Force Regen in Half for 30 Minutes.

			playerObject->setForcePowerRegen(playerObject->getForcePowerRegen() / 2);

			// Jedi experience loss.
			PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
			playerManager->awardExperience(creature, "jedi_general", -50000, true);

			Reference<RegainConsciousnessRegenTask*> rcTask = new RegainConsciousnessRegenTask(creature, playerObject);
			creature->addPendingTask("regainConsciousnessRegenTask", rcTask, (1800 * 1000));

			return SUCCESS;
		}

		return GENERALERROR;

	}

};

#endif //REGAINCONSCIOUSNESSCOMMAND_H_
