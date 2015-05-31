/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ENRAGEPETSCOMMAND_H_
#define ENRAGEPETSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/player/PlayerObject.h"

class EnragepetsCommand : public QueueCommand {
public:

	EnragepetsCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* player, const uint64& target, const UnicodeString& arguments) const {

		int cooldownMilli = 300000; // 5 min
		int durationSec =  60; // 1 min
		int mindCost = player->calculateCostAdjustment(CreatureAttribute::FOCUS, 100 );
		unsigned int buffCRC = STRING_HASHCODE("enragePet");

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
			player->sendSystemMessage("@pet/pet_menu:sys_fail_enrage"); // "You lack the mental focus to enrage your pets."
			return GENERALERROR;
		}

		// Loop over all active pets
		bool petEnraged = false;
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
				if ( pet->hasBuff(buffCRC) )
					continue;

				// Check cooldown
				if( pet->getCooldownTimerMap() == NULL || !pet->getCooldownTimerMap()->isPast("enragePetsCooldown") )
					continue;

				// Determine damage bonus (15% of average damage)
				int damageBonus = (int) ((((float)pet->getDamageMin() + (float)pet->getDamageMax())/2) * 0.15);

				// Determine damage susceptibility (half of damage bonus)
				int damageSusceptibility = damageBonus / 2;

				// Build buff
				ManagedReference<Buff*> buff = new Buff(pet, buffCRC, durationSec, BuffType::OTHER);

				Locker locker(buff);

				buff->setStartFlyText("combat_effects", "go_berserk", 0, 0xFF, 0);
				buff->setEndFlyText("combat_effects", "no_berserk", 0xFF, 0, 0);
				buff->setSkillModifier("private_damage_bonus", damageBonus);
				buff->setSkillModifier("private_damage_susceptibility", damageSusceptibility);

				pet->addBuff(buff);
				pet->getCooldownTimerMap()->updateToCurrentAndAddMili("enragePetsCooldown", cooldownMilli);
				petEnraged = true;

			} // end if creature
		} // end active pets loop

		// At least one pet was enraged
		if( petEnraged ){
			player->inflictDamage(player, CreatureAttribute::MIND, mindCost, false);
			player->sendSystemMessage("@pet/pet_menu:sys_enrage"); // "You drive your pets into a wild rage."
		}

		return SUCCESS;
	}

};

#endif //ENRAGEPETSCOMMAND_H_
