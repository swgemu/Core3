/*
 * PetFeedCommand.h
 *
 *  Created on: Jan 19, 2014
 *      Author: Klivian
 */

#ifndef PETFEEDCOMMAND_H_
#define PETFEEDCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/AiAgent.h"

class PetFeedCommand : public QueueCommand {
public:
	PetFeedCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().castTo<PetControlDevice*>();
		if (controlDevice == NULL)
			return GENERALERROR;

		// Creature specific command
		if( controlDevice->getPetType() != PetManager::CREATUREPET )
			return GENERALERROR;

		if (!creature->isAiAgent())
			return GENERALERROR;

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);
		if( pet == NULL )
			return GENERALERROR;

		ManagedReference< CreatureObject*> player = pet->getLinkedCreature().get();
		if( player == NULL )
			return GENERALERROR;

		if( pet->getCooldownTimerMap() == NULL )
			return GENERALERROR;

		// Check pet states
		if( pet->isInCombat() || pet->isDead() || pet->isIncapacitated() )
			return GENERALERROR;

		// Check cooldown
		if( !pet->getCooldownTimerMap()->isPast("feedCooldown") )
			return GENERALERROR;

		// Find food in player inventory
		Locker clocker(player, creature);
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		if (inventory == NULL){
			player->sendSystemMessage("Player inventory not found");
			return 0;
		}

		ManagedReference<SceneObject*> foodSceno = NULL;
		for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
			ManagedReference<SceneObject*> sceno = inventory->getContainerObject(i);
			if( sceno->getGameObjectType() == SceneObjectType::FOOD ){
				foodSceno = sceno;
				break;
			}
		}

		// Food not found
		if( foodSceno == NULL ){
			pet->showFlyText("npc_reaction/flytext","nofood", 204, 0, 0); // "You don't have any food to give!"
			return 0;
		}

		// Food found
		ManagedReference<TangibleObject*> foodTano = cast<TangibleObject*>(foodSceno.get());
		if( foodTano == NULL ){
			player->sendSystemMessage("Error with food object");
			return 0;
		}

		// Heal 10% of base in wounds
		int healthHeal = pet->getBaseHAM(CreatureAttribute::HEALTH) * 0.10;
		int strengthHeal = pet->getBaseHAM(CreatureAttribute::STRENGTH) * 0.10;
		int conHeal = pet->getBaseHAM(CreatureAttribute::CONSTITUTION) * 0.10;
		int actionHeal = pet->getBaseHAM(CreatureAttribute::ACTION) * 0.10;
		int quicknessHeal = pet->getBaseHAM(CreatureAttribute::QUICKNESS) * 0.10;
		int staminaHeal = pet->getBaseHAM(CreatureAttribute::STAMINA) * 0.10;

		pet->addWounds(CreatureAttribute::HEALTH, -healthHeal);
		pet->addWounds(CreatureAttribute::STRENGTH, -strengthHeal);
		pet->addWounds(CreatureAttribute::CONSTITUTION, -conHeal);
		pet->addWounds(CreatureAttribute::ACTION, -actionHeal);
		pet->addWounds(CreatureAttribute::QUICKNESS, -quicknessHeal);
		pet->addWounds(CreatureAttribute::STAMINA, -staminaHeal);

		// Perform eat animation and do fly text
		pet->doAnimation("eat");
		pet->showFlyText("npc_reaction/flytext","yum", 0, 153, 0); // "Yummy!"

		// Consume food
		foodTano->decreaseUseCount();

		// Set cooldown
		pet->getCooldownTimerMap()->updateToCurrentAndAddMili("feedCooldown", 5000); // 5 sec

		return SUCCESS;
	}

};


#endif /* PETFEEDCOMMAND_H_ */
