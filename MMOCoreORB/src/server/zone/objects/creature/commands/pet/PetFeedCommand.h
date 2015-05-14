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
#include "server/zone/objects/tangible/consumable/Consumable.h"

class PetFeedCommand : public QueueCommand {
public:
	PetFeedCommand(const String& name, ZoneProcessServer* server)
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

		// Find food sceno (either provided in arguments or first food in inventory)
		Locker clocker(player, creature);
		ManagedReference<SceneObject*> foodSceno = NULL;
		StringTokenizer args(arguments.toString());
		if (!args.hasMoreTokens()){

			// Find food in player inventory
			ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
			if (inventory == NULL){
				player->sendSystemMessage("Player inventory not found");
				return GENERALERROR;
			}


			for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
				ManagedReference<SceneObject*> sceno = inventory->getContainerObject(i);
				if( sceno->getGameObjectType() == SceneObjectType::FOOD ){
					foodSceno = sceno;
					break;
				}
			}

		}
		else{
			uint64 targetObjectID = 0;

			try {
				targetObjectID = args.getLongToken();
			} catch (Exception& e) {
				error("could not get long token in " + arguments.toString());
				error(e.getMessage());
				return INVALIDPARAMETERS;
			}

			foodSceno = server->getZoneServer()->getObject(targetObjectID);

		}

		// Valid food not found
		if( foodSceno == NULL || foodSceno->getGameObjectType() != SceneObjectType::FOOD){
			pet->showFlyText("npc_reaction/flytext","nofood", 204, 0, 0); // "You don't have any food to give!"
			return GENERALERROR;
		}

		// Check cooldown
		if( !pet->getCooldownTimerMap()->isPast("feedCooldown") ){
			pet->showFlyText("npc_reaction/flytext","nothungry", 204, 0, 0); // "Your pet isn't hungry."
			return GENERALERROR;
		}

		// Food found
		ManagedReference<Consumable*> consumable = cast<Consumable*>(foodSceno.get());
		if( consumable == NULL ){
			player->sendSystemMessage("Error with consumable object");
			return GENERALERROR;
		}

		Locker locker(consumable);

		// Apply buff if this is a pet specific food
		if( consumable->getSpeciesRestriction() == "pets" ){

			unsigned int buffCRC = STRING_HASHCODE("petFoodBuff");

			// Check if pet already has buff
			if ( pet->hasBuff(buffCRC) ){
				player->sendSystemMessage("Your pet is still fortified from its last meal!");
				return SUCCESS;
			}
			else{
				ManagedReference<Buff*> buff = new Buff(pet, buffCRC, consumable->getDuration(), BuffType::FOOD);

				Locker blocker(buff);

				consumable->setModifiers(buff, false);
				pet->addBuff(buff);
				player->sendSystemMessage("Your pet is fortified by the food!");
			}

		}
		else{

			// Pet must have wounds to eat non-specific food
			int wounds = pet->getWounds( CreatureAttribute::HEALTH ) + 	pet->getWounds( CreatureAttribute::STRENGTH ) +
					     pet->getWounds( CreatureAttribute::CONSTITUTION ) + pet->getWounds( CreatureAttribute::ACTION ) +
					     pet->getWounds( CreatureAttribute::QUICKNESS ) + pet->getWounds( CreatureAttribute::STAMINA );
			if( wounds == 0 ){
				pet->showFlyText("npc_reaction/flytext","nothungry", 204, 0, 0); // "Your pet isn't hungry."
				return GENERALERROR;
			}

		}

		// Heal 10% of base in wounds
		int healthHeal = pet->getBaseHAM(CreatureAttribute::HEALTH) * 0.10;
		int strengthHeal = pet->getBaseHAM(CreatureAttribute::STRENGTH) * 0.10;
		int conHeal = pet->getBaseHAM(CreatureAttribute::CONSTITUTION) * 0.10;
		int actionHeal = pet->getBaseHAM(CreatureAttribute::ACTION) * 0.10;
		int quicknessHeal = pet->getBaseHAM(CreatureAttribute::QUICKNESS) * 0.10;
		int staminaHeal = pet->getBaseHAM(CreatureAttribute::STAMINA) * 0.10;

		pet->healWound(player, CreatureAttribute::HEALTH, healthHeal, true, false);
		pet->healWound(player, CreatureAttribute::STRENGTH, strengthHeal, true, false);
		pet->healWound(player, CreatureAttribute::CONSTITUTION, conHeal, true, false);
		pet->healWound(player, CreatureAttribute::ACTION, actionHeal, true, false);
		pet->healWound(player, CreatureAttribute::QUICKNESS, quicknessHeal, true, false);
		pet->healWound(player, CreatureAttribute::STAMINA, staminaHeal, true, false);

		// Perform eat animation and do fly text
		pet->doAnimation("eat");
		pet->showFlyText("npc_reaction/flytext","yum", 0, 153, 0); // "Yummy!"

		// Consume food
		consumable->decreaseUseCount();

		// Set cooldown
		pet->getCooldownTimerMap()->updateToCurrentAndAddMili("feedCooldown", 5000); // 5 sec

		return SUCCESS;
	}

};


#endif /* PETFEEDCOMMAND_H_ */
