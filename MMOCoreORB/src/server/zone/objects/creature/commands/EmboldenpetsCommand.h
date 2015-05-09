/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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

				Locker locker(buff);

				int healthBuff = pet->getBaseHAM(CreatureAttribute::HEALTH) * 0.15;
				int actionBuff = pet->getBaseHAM(CreatureAttribute::ACTION) * 0.15;
				int mindBuff = pet->getBaseHAM(CreatureAttribute::MIND) * 0.15;
				buff->setAttributeModifier(CreatureAttribute::HEALTH, healthBuff);
				buff->setAttributeModifier(CreatureAttribute::ACTION, actionBuff);
				buff->setAttributeModifier(CreatureAttribute::MIND, mindBuff);

				pet->addBuff(buff);
				pet->getCooldownTimerMap()->updateToCurrentAndAddMili("emboldenPetsCooldown", cooldownMilli);
				pet->showFlyText("combat_effects","pet_embolden", 0, 153, 0); // "! Embolden !"
				petEmboldened = true;

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
