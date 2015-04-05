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

#ifndef EMBOLDENPETSCOMMAND_H_
#define EMBOLDENPETSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/player/PlayerObject.h"

class EmboldenpetsCommand : public QueueCommand {
public:

	EmboldenpetsCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* player, const uint64& target, const UnicodeString& arguments) const {

		int cooldownMilli = 300000; // 5 min
		int durationSec =  60; // 1 min
		int mindCost = player->calculateCostAdjustment(CreatureAttribute::FOCUS, 100 );
		unsigned int buffCRC = String("emboldenPet").hashCode();

		if (!checkStateMask(player))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(player))
			return INVALIDLOCOMOTION;

		if (player->isDead() || player->isIncapacitated())
			return INVALIDSTATE;

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
		if( ghost == NULL )
			return GENERALERROR;

		// Check player mind
		if (player->getHAM(CreatureAttribute::MIND) <= mindCost) {
			player->sendSystemMessage("@pet/pet_menu:sys_fail_embolden"); // "You do not have enough mental focus to embolden."
			return GENERALERROR;
		}

		// Loop over all active pets
		bool petEmboldened = false;
		for (int i = 0; i < ghost->getActivePetsSize(); ++i) {

			ManagedReference<AiAgent*> pet = ghost->getActivePet(i);
			if(pet == NULL)
				continue;

			ManagedReference<PetControlDevice*> controlDevice = pet->getControlDevice().get().castTo<PetControlDevice*>();
			if( controlDevice == NULL )
				continue;

			// Creatures only
			if( controlDevice->getPetType() == PetManager::CREATUREPET ) {

				Locker plocker(pet, player);

				// Check states
				if( pet->isIncapacitated() || pet->isDead() )
					continue;

				// Check range
				if( !player->isInRange( pet, 50.0 ) )
					continue;

				// Check if pet already has buff
				if ( pet->hasBuff(buffCRC) ){
					pet->showFlyText("combat_effects","pet_embolden_no", 0, 153, 0); // "! Already Emboldened !"
					continue;
				}

				// Check cooldown
				if( pet->getCooldownTimerMap() == NULL || !pet->getCooldownTimerMap()->isPast("emboldenPetsCooldown") )
					continue;

				// Build 15% Health, Action, Mind buff
				ManagedReference<Buff*> buff = new Buff(pet, buffCRC, durationSec, BuffType::OTHER);
				int healthBuff = pet->getBaseHAM(CreatureAttribute::HEALTH) * 0.15;
				int actionBuff = pet->getBaseHAM(CreatureAttribute::ACTION) * 0.15;
				int mindBuff = pet->getBaseHAM(CreatureAttribute::MIND) * 0.15;
				buff->setAttributeModifier(CreatureAttribute::HEALTH, healthBuff);
				buff->setAttributeModifier(CreatureAttribute::ACTION, actionBuff);
				buff->setAttributeModifier(CreatureAttribute::MIND, mindBuff);

				// Apply buff
				if (buff != NULL){
					pet->addBuff(buff);
					pet->getCooldownTimerMap()->updateToCurrentAndAddMili("emboldenPetsCooldown", cooldownMilli);
					pet->showFlyText("combat_effects","pet_embolden", 0, 153, 0); // "! Embolden !"
					petEmboldened = true;
				}

			} // end if creature
		} // end active pets loop

		// At least one pet was emboldened
		if( petEmboldened ){
			player->inflictDamage(player, CreatureAttribute::MIND, mindCost, false);
			player->sendSystemMessage("@pet/pet_menu:sys_embolden"); // "Your pets fight with renewed vigor"
		}

		return SUCCESS;
	}

};

#endif //EMBOLDENPETSCOMMAND_H_
