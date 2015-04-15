/*
 * PetTrickCommand.h
 *
 *  Created on: Dec 18, 2013
 *      Author: TheAnswer
 */

#ifndef PETTRICKCOMMAND_H_
#define PETTRICKCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/AiAgent.h"

class PetTrickCommand : public QueueCommand {
public:
	PetTrickCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().castTo<PetControlDevice*>();

		if (controlDevice == NULL)
			return GENERALERROR;

		// Creature specific command
		if( controlDevice->getPetType() != PetManager::CREATUREPET )
			return GENERALERROR;

		if (!creature->isAiAgent())
			return GENERALERROR;

		// Target is the player commanding pet to perform the trick
		ManagedReference<SceneObject*> commandTarget = server->getZoneServer()->getObject(target);
		if (commandTarget == NULL || !commandTarget->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(commandTarget.get());
		if( player == NULL )
			return GENERALERROR;

		StringTokenizer tokenizer(arguments.toString());

		if (!tokenizer.hasMoreTokens())
			return GENERALERROR;

		int trickNumber = tokenizer.getIntToken();

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);
		if( pet == NULL )
			return GENERALERROR;

		if( pet->getCooldownTimerMap() == NULL )
			return GENERALERROR;

		// Check pet states
		if( pet->isInCombat() || pet->isDead() || pet->isIncapacitated() ){
			player->sendSystemMessage("@pet/pet_menu:sys_cant_trick"); // "You can't have your pet perform a trick right now."
			return GENERALERROR;
		}

		// Check cooldown (single cooldown for both tricks as we can't animate both at once)
		if( !pet->getCooldownTimerMap()->isPast("trickCooldown") ){
			player->sendSystemMessage("@pet/pet_menu:sys_cant_trick"); // "You can't have your pet perform a trick right now."
			return GENERALERROR;
		}

		Locker locker(player, pet);

		// Check player HAM
		int actionCost = player->calculateCostAdjustment(CreatureAttribute::QUICKNESS, 50 * trickNumber );
		int mindCost = player->calculateCostAdjustment(CreatureAttribute::FOCUS, 50 * trickNumber );
		if (player->getHAM(CreatureAttribute::ACTION) <= actionCost || player->getHAM(CreatureAttribute::MIND) <= mindCost) {
			player->sendSystemMessage("@pet/pet_menu:cant_trick"); // "You need to rest before you can have your pet perform a trick."
			return INSUFFICIENTHAM;
		}

		// Heal 20% or 40% of base in wounds and damage
		int mindHeal = pet->getBaseHAM(CreatureAttribute::MIND) * 0.20 * trickNumber;
		int focusHeal = pet->getBaseHAM(CreatureAttribute::FOCUS) * 0.20 * trickNumber;
		int willHeal = pet->getBaseHAM(CreatureAttribute::WILLPOWER) * 0.20 * trickNumber;
		int shockHeal = 100 * trickNumber;

		// Heal wounds
		pet->healWound(player, CreatureAttribute::MIND, mindHeal, true, false);
		pet->healWound(player, CreatureAttribute::FOCUS, focusHeal, true, false);
		pet->healWound(player, CreatureAttribute::WILLPOWER, willHeal, true, false);

		// Heal battle fatigue
		pet->addShockWounds(-shockHeal, true, false);

		// Heal damage
		mindHeal = MIN( mindHeal, pet->getMaxHAM(CreatureAttribute::MIND) - pet->getHAM(CreatureAttribute::MIND) );
		pet->inflictDamage(pet, CreatureAttribute::MIND, -mindHeal, false);

		// Perform trick animation
		String animation = "trick_" + String::valueOf(trickNumber);
		pet->doAnimation(animation);

		// Set cooldown
		pet->getCooldownTimerMap()->updateToCurrentAndAddMili("trickCooldown", 5000); // 5 sec

		// Reduce player HAM
		player->inflictDamage(player, CreatureAttribute::ACTION, actionCost, false);
		player->inflictDamage(player, CreatureAttribute::MIND, mindCost, false);

		return SUCCESS;
	}

};


#endif /* PETTRICKCOMMAND_H_ */
