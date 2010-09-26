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

#ifndef EQUILIBRIUMCOMMAND_H_
#define EQUILIBRIUMCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/creature/variables/CooldownTimerMap.h"
#include "server/zone/objects/scene/variables/ParameterizedStringId.h"

class EquilibriumCommand: public QueueCommand {
public:

	EquilibriumCommand(const String& name, ZoneProcessServerImplementation* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		PlayerCreature* player = (PlayerCreature*) creature;

		// Check to see if "innate_quilibrium" Cooldown isPast();
		if (!player->checkCooldownRecovery("innate_equilibrium")) {
			ParameterizedStringId stringId;

			Time* cdTime = player->getCooldownTime("innate_equilibrium");

			// Returns -time. Multiple by -1 to return postive.
			int timeLeft = floor(cdTime->miliDifference() / 1000) *-1;

			stringId.setStringId("@innate:equil_wait"); // You are still recovering from your last equilization. Command available in %DI seconds.
			stringId.setDI(timeLeft);
			player->sendSystemMessage(stringId);
			return GENERALERROR;
		}

		int health = player->getMaxHAM(CreatureAttribute::HEALTH);
		int action = player->getMaxHAM(CreatureAttribute::ACTION);
		int mind = player->getMaxHAM(CreatureAttribute::MIND);

		int newVal = (MAX(health, MAX(action, mind))) * 0.65;

		player->setHAM(CreatureAttribute::HEALTH, newVal);
		player->setHAM(CreatureAttribute::ACTION, newVal);
		player->setHAM(CreatureAttribute::MIND, newVal);

		player->sendSystemMessage("@innate:equil_active"); // Through sheer willpower, you force yourself into a state of equilibruim.
		player->showFlyText("combat_effects", "innate_equilibrium", 0, 255, 0); // +Equilibruim+

		player->addCooldown("innate_equilibrium", 600 * 1000);

		return SUCCESS;
	}

};

#endif //EQUILIBRIUMCOMMAND_H_
