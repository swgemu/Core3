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

class EquilibriumCommand: public QueueCommand {
public:

	EquilibriumCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getSpecies() != CreatureObject::ZABRAK)
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*>(creature);

		// Check to see if "innate_equilibrium" Cooldown isPast();
		if (!player->checkCooldownRecovery("innate_equilibrium")) {
			StringIdChatParameter stringId;

			Time* cdTime = player->getCooldownTime("innate_equilibrium");

			// Returns -time. Multiple by -1 to return positive.
			int timeLeft = floor((float)cdTime->miliDifference() / 1000) *-1;

			stringId.setStringId("@innate:equil_wait"); // You are still recovering from your last equilization. Command available in %DI seconds.
			stringId.setDI(timeLeft);
			player->sendSystemMessage(stringId);
			return GENERALERROR;
		}

		int health = player->getHAM(CreatureAttribute::HEALTH);
		int action = player->getHAM(CreatureAttribute::ACTION);
		int mind = player->getHAM(CreatureAttribute::MIND);

		// All pools Balanced to the same Value.
		int balValue = (health + action + mind) / 3;

		// Get the difference between current HEALTH and the balValue.
		int diffHealth = MAX(health, balValue) - MIN(health, balValue);
		int diffAction = MAX(action, balValue) - MIN(action, balValue);
		int diffMind = MAX(mind, balValue) - MIN(mind, balValue);

		// Check rather to Heal or inflict damage to the player.
		if (health < balValue) {
			player->healDamage(player,CreatureAttribute::HEALTH, diffHealth, true);

		} else {
			player->inflictDamage(player, CreatureAttribute::HEALTH, diffHealth, true);

		}

		if (action < balValue) {
			player->healDamage(player,CreatureAttribute::ACTION, diffAction, true);

		} else {
			player->inflictDamage(player, CreatureAttribute::ACTION, diffAction, true);

		}

		if (mind < balValue) {
			player->healDamage(player,CreatureAttribute::MIND, diffMind, true);

		} else {
			player->inflictDamage(player, CreatureAttribute::MIND, diffMind, true);

		}

		player->sendSystemMessage("@innate:equil_active"); // Through sheer willpower, you force yourself into a state of equilibrium.
		player->showFlyText("combat_effects", "innate_equilibrium", 0, 255, 0); // +Equilibrium+

		player->addCooldown("innate_equilibrium", 3600 * 1000);

		return SUCCESS;
	}

};

#endif //EQUILIBRIUMCOMMAND_H_
