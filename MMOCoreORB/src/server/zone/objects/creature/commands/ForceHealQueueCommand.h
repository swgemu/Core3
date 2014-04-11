/*
 * ForceHealQueueCommand.h
 *
 *  Created on: Mar 15, 2014
 *      Author: swgemu
 */

#ifndef FORCEHEALQUEUECOMMAND_H_
#define FORCEHEALQUEUECOMMAND_H_


#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "QueueCommand.h"

class ForceHealQueueCommand : public QueueCommand {
protected:
	float forceCost;

public:
	ForceHealQueueCommand(const String& name, ZoneProcessServer* server)
: QueueCommand(name, server) {
		forceCost = 0;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {

		if (creature == creatureTarget)
			creature->playEffect("clienteffect/pl_force_heal_self.cef", "");
		else
			creature->doCombatAnimation(creatureTarget,String("force_healing_1").hashCode(),0,0xFF);
	}

	bool isWarcried(CreatureObject* creature) {
		if (creature->hasAttackDelay()) {
			return true;
		}
		return false;
	}

	bool checkForceCost(CreatureObject* creature) {
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject != NULL) {
			if (playerObject->getForcePower() < forceCost) {
				return false;
			}
			return true;
		}
		return false;
	}

	void sendHealMessage(CreatureObject* object, CreatureObject* target, int healthDamage, int actionDamage, int mindDamage) {
		if (!object->isPlayerCreature())
			return;

		if (!target->isPlayerCreature())
			return;

		CreatureObject* creature = cast<CreatureObject*>( object);
		CreatureObject* creatureTarget = cast<CreatureObject*>( target);

		StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

		if (healthDamage > 0 && actionDamage > 0 && mindDamage > 0) {
			msgBody << healthDamage << " health, " << actionDamage << " action, and "  << mindDamage << " mind";
		} else if (healthDamage > 0) {
			msgBody << healthDamage << " health";
		} else if (actionDamage > 0) {
			msgBody << actionDamage << " action";
		} else if (mindDamage > 0) {
			msgBody << mindDamage << " mind";
		} else {
			creature->sendSystemMessage("@jedi_spam:no_damage_heal_other"); //Your target has no damage of that type to heal.
			return;
		}

		msgTail << " damage.";

			msgPlayer << "You heal " << creatureTarget->getFirstName() << " for " << msgBody.toString() << msgTail.toString(); // You heal %TT for %DI points of %TO.
			msgTarget << "You are healed for " << msgBody.toString() << " points of damage by " << creature->getFirstName(); // You are healed for %DI points of %TO by %TT.

			creature->sendSystemMessage(msgPlayer.toString());
			creatureTarget->sendSystemMessage(msgTarget.toString());

	}



	void sendWoundMessage(CreatureObject* creature, int healthWound, int actionWound, int mindWound, int strengthWound, int constitutionWound, int quicknessWound, int staminaWound, int focusWound, int willpowerWound) {

		StringBuffer msgPlayer, msgBody, msgTail;

		if (healthWound > 0 && strengthWound > 0 && constitutionWound > 0 && actionWound > 0 && quicknessWound > 0 && staminaWound > 0 && mindWound > 0 && focusWound > 0 && willpowerWound > 0) {
			msgBody << healthWound << " health, " << strengthWound << " strength, " << constitutionWound << " constitution " << actionWound << " action, " << quicknessWound << " quickness, " << staminaWound << " stamina " << mindWound << " mind, " << focusWound << " focus, and "  << willpowerWound << " willpower";;
		} else if (healthWound > 0) {
			msgBody << healthWound << " health";
		} else if (strengthWound > 0) {
			msgBody << strengthWound << " strength";
		} else if (constitutionWound > 0) {
			msgBody << constitutionWound << " constitution";
		} else if (actionWound > 0) {
			msgBody << actionWound << " action";
		} else if (quicknessWound > 0) {
			msgBody << quicknessWound << " quickness";
		} else if (staminaWound > 0) {
			msgBody << staminaWound << " stamina";
		} else if (mindWound > 0) {
			msgBody << mindWound << " mind";
		} else if (focusWound > 0) {
			msgBody << focusWound << " focus";
		} else if (willpowerWound > 0) {
			msgBody << willpowerWound << " willpower";
		} else {
			creature->sendSystemMessage("@healing_response:healing_response_67"); // You have no wounds of that type.
			return;
		}

		msgTail << " wounds.";

			msgPlayer << "You heal yourself for " << msgBody.toString() << msgTail.toString();
			creature->sendSystemMessage(msgPlayer.toString());

	}

	int healBattleFatigue(CreatureObject* creature, int damage){

		int currentValue = creature->getShockWounds();

		int healedValue = MIN(currentValue, damage);

		creature->addShockWounds(-healedValue);

		return healedValue;

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		return SUCCESS;
	}

	bool isForceHealCommand() {
		return true;
	}

	void setForceCost(int fpc) {
		forceCost = fpc;
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) {
		return defaultTime * getSpeedMultiplierMod();
	}

	int getSpeedMultiplierMod() {
		int value = 0;

		if (name.contains("healstatesself")) // HealStatesSelf = 4 sec
			value = 3;
		else
			value = 4; // Other healing commands = 6 seconds

		return value;

	}
};


#endif /* FORCEHEALQUEUECOMMAND_H_ */
