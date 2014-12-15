/*
 * JediSelfQueueCommand.h
 *
 *  Created on: Mar 15, 2014
 *      Author: swgemu
 */

#ifndef JEDISELFQUEUECOMMAND_H_
#define JEDISELFQUEUECOMMAND_H_


#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "QueueCommand.h"
#include "server/zone/objects/creature/buffs/SingleUseBuff.h"

class JediSelfQueueCommand : public QueueCommand {
protected:
	float forceCost;
	uint32 buffCRC;
	uint32 buffCRC2;
	int duration;
	String clientEffect;
	String animation;
	String skillMod;
	int skillModAmount;
	uint8 healAttribute1;
	uint8 healAttribute2;
	uint8 healAttribute3;
	int healAttributeSize;
	int healAmount;

public:
	JediSelfQueueCommand(const String& name, ZoneProcessServer* server)
: QueueCommand(name, server) {
		forceCost = 0;
		buffCRC = 0;
		duration = 0;
		buffCRC2 = 0;
		clientEffect = "";
		animation = "";
		skillMod = "";
		skillModAmount = 0;
		healAttribute1 = 0;
		healAttribute2 = 0;
		healAttribute3 = 0;
		healAttributeSize = 0;
		healAmount = 0;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!clientEffect.isEmpty())
			creature->playEffect(clientEffect, "");

		if (!animation.isEmpty())
			creature->doCombatAnimation(creatureTarget, animation.hashCode(),0,0xFF);
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

	void sendHealSystemMessage(CreatureObject* creature, CreatureObject* target, int damageHealedHealth = 0, int damageHealedAction = 0, int damageHealedMind = 0) {

		if (target != creature && creature != target)
			creature = target;


		if (damageHealedHealth > 0){
			if (creature != target) {
				StringIdChatParameter message("jedi_spam", "heal_self");
				message.setDI(damageHealedHealth);
				message.setTO("@jedi_spam:health_damage");
				creature->sendSystemMessage(message);
			}
			else {
				StringIdChatParameter message("jedi_spam", "heal_other_self");
				message.setTT(target->getDisplayedName());
				message.setDI(damageHealedHealth);
				message.setTO("@jedi_spam:health_damage");
				creature->sendSystemMessage(message);

				StringIdChatParameter messageOther("jedi_spam", "heal_other_other");
				messageOther.setDI(damageHealedHealth);
				messageOther.setTO("@jedi_spam:health_damage");
				target->sendSystemMessage(messageOther);
			}

		}

		if (damageHealedAction > 0){
			if (creature != target) {
				StringIdChatParameter message("jedi_spam", "heal_self");
				message.setDI(damageHealedAction);
				message.setTO("@jedi_spam:action_damage");
				creature->sendSystemMessage(message);
			}
			else {
				StringIdChatParameter message("jedi_spam", "heal_other_self");
				message.setTT(target->getDisplayedName());
				message.setDI(damageHealedAction);
				message.setTO("@jedi_spam:action_damage");
				creature->sendSystemMessage(message);

				StringIdChatParameter messageOther("jedi_spam", "heal_other_other");
				messageOther.setDI(damageHealedAction);
				messageOther.setTO("@jedi_spam:action_damage");
				target->sendSystemMessage(messageOther);
			}

		}

		if (damageHealedMind > 0){
			if (creature != target) {
				StringIdChatParameter message("jedi_spam", "heal_self");
				message.setDI(damageHealedMind);
				message.setTO("@jedi_spam:mind_damage");
				creature->sendSystemMessage(message);
			}
			else {
				StringIdChatParameter message("jedi_spam", "heal_other_self");
				message.setTT(target->getDisplayedName());
				message.setDI(damageHealedMind);
				message.setTO("@jedi_spam:mind_damage");
				creature->sendSystemMessage(message);

				StringIdChatParameter messageOther("jedi_spam", "heal_other_other");
				messageOther.setDI(damageHealedMind);
				messageOther.setTO("@jedi_spam:mind_damage");
				target->sendSystemMessage(messageOther);
			}

		}

	}

	int healBattleFatigue(CreatureObject* creature, int damage){

		int currentValue = creature->getShockWounds();

		int healedValue = MIN(currentValue, damage);

		creature->addShockWounds(-healedValue);

		return healedValue;

	}

	bool canPerformSelfHeal(CreatureObject* creature) {
			if (!creature->hasDamage(healAttribute1) && !creature->hasDamage(healAttribute2) && !creature->hasDamage(healAttribute3)) {
				return false;
			}
		return true;
	}

	int doJediSelfChecks(CreatureObject* creature) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		if (isWarcried(creature)) {
			return GENERALERROR;
		}

		if (!checkForceCost(creature)) {
			creature->sendSystemMessage("@jedi_spam:no_force_power");
			return GENERALERROR;
		}

		return SUCCESS;
	}

	int doJediSelfHealCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		int res = doJediSelfChecks(creature);

		if (res != SUCCESS)
			return GENERALERROR;

		if (!canPerformSelfHeal(creature)) {
			creature->sendSystemMessage("@jedi_spam:no_damage_heal_self"); // You have no damage of that type.
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);
		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());


		uint32 healDmg1 = creature->healDamage(creature, healAttribute1, healAmount);
		uint32 healDmg2 = creature->healDamage(creature, healAttribute2, healAmount);
		uint32 healDmg3 = creature->healDamage(creature, healAttribute3, healAmount);

		forceCost += (healDmg1 / 20) + (healDmg2 / 20) + (healDmg3 / 20);

		doAnimations(creature, creatureTarget);

		// Deduct Force cost.
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject != NULL)
			playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		sendHealSystemMessage(creature, creatureTarget, healDmg1, healDmg2, healDmg3);
	}

	int doJediBuffCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if(creature->hasBuff(buffCRC) || creature->hasBuff(buffCRC2)) {
			creature->sendSystemMessage("@jedi_spam:force_buff_present");
			return GENERALERROR;
		}

		int res = doJediSelfChecks(creature);

		if (res != SUCCESS)
			return GENERALERROR;

		// Deduct Force cost.
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject != NULL)
			playerObject->setForcePower(playerObject->getForcePower() - forceCost);


		StringIdChatParameter startStringId("jedi_spam", "apply_" + name);
		StringIdChatParameter endStringId("jedi_spam", "remove_" + name);
		Vector<unsigned int> eventTypes;
		eventTypes.add(ObserverEventType::FORCEBUFFHIT);

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);
		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		ManagedReference<SingleUseBuff*> buff = new SingleUseBuff(creature, buffCRC, duration, BuffType::JEDI, getNameCRC());
		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);
		buff->init(&eventTypes);

		if (!skillMod.isEmpty() && skillModAmount != 0)
			buff->setSkillModifier(skillMod, skillModAmount);

		creature->addBuff(buff);

		doAnimations(creature, creatureTarget);

		return SUCCESS;
	}

	bool isJediSelfCommand() {
		return true;
	}

	void setForceCost(int fpc) {
		forceCost = fpc;
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) {
		return defaultTime * 3.0;
	}
};


#endif /* JEDISELFQUEUECOMMAND_H_ */
