/*
 * JediQueueCommand.h
 *
 *  Created on: Mar 15, 2014
 *      Author: swgemu
 */

#ifndef JEDIQUEUECOMMAND_H_
#define JEDIQUEUECOMMAND_H_


#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "QueueCommand.h"
#include "server/zone/objects/creature/buffs/SingleUseBuff.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/creature/buffs/BuffCRC.h"

class JediQueueCommand : public QueueCommand {
protected:
	float forceCost; // The Force Cost of the command.
	Vector<uint32> buffCRCs; // The buff CRC's. The first one is used, the remaining ones are used for checks.
	int duration; // The duration of the buff.
	String clientEffect; // The client effect if applicable.
	String animation; // The animation used from creature to target, if applicable.
	VectorMap<String, int> skillMods; // Skill Mods for buffs, key is skillMod, value is skillModValue.
	VectorMap<uint8, int> healAttributesDamage; // Damage healing, key is attribute, value is amount healed max.
	VectorMap<uint8, int> healAttributesWounds; // Wounds healing, key is attribute, value is amount healed max.
	Vector<uint64> healStates; // Healing States Vector.
	VectorMap<uint64, int> healDots; // Dot healing, Key is the state/dot, value is the max amount of potency healed per use.
	int healBF; // BF healing.

	// Specify what type of healing it is.
	int healingType;
	enum {
		SELFONLY, // 0
		TARGETONLY, // 1
		SELFORTARGET, // 2
		NEITHER // 3
	};

	// Specify the event buffs.
	int buffEventType;

public:
	JediQueueCommand(const String& name, ZoneProcessServer* server)
: QueueCommand(name, server) {
		forceCost = 0;
		duration = 0;
		clientEffect = "";
		animation = "";
		skillMods.setNoDuplicateInsertPlan();
		healAttributesDamage.setNoDuplicateInsertPlan();
		healAttributesWounds.setNoDuplicateInsertPlan();
		healDots.setNoDuplicateInsertPlan();
		healBF = 0;
		healingType = NEITHER;
		buffEventType = 0;

	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!clientEffect.isEmpty())
			creature->playEffect(clientEffect, "");

		if (!animation.isEmpty())
			creature->doCombatAnimation(creatureTarget, animation.hashCode(),0,0xFF);
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

	// States and Dots are taken care of by their respective methods.
	void sendHealSystemMessage(CreatureObject* creature, CreatureObject* target, uint8 attribute, int damageHealed = 0, int woundsHealed = 0, int bfHealed = 0) {


		if (damageHealed > 0){
			if (target == creature) {
				StringIdChatParameter message("jedi_spam", "heal_self");
				message.setDI(damageHealed);
				message.setTO("@jedi_spam:" + CreatureAttribute::getName(attribute) + "_damage");
				creature->sendSystemMessage(message);
			}
			else {
				StringIdChatParameter message("jedi_spam", "heal_other_self");
				message.setTT(target->getDisplayedName());
				message.setDI(damageHealed);
				message.setTO("@jedi_spam:" + CreatureAttribute::getName(attribute) + "_damage");
				creature->sendSystemMessage(message);

				StringIdChatParameter messageOther("jedi_spam", "heal_other_other");
				messageOther.setDI(damageHealed);
				message.setTO("@jedi_spam:" + CreatureAttribute::getName(attribute) + "_damage");
				target->sendSystemMessage(messageOther);
			}
		}


		if (woundsHealed > 0){
			if (target == creature) {
				StringIdChatParameter message("jedi_spam", "heal_self");
				message.setDI(woundsHealed);
				message.setTO("@jedi_spam:" + CreatureAttribute::getName(attribute) + "_wounds");

				creature->sendSystemMessage(message);
			}
			else {
				StringIdChatParameter message("jedi_spam", "heal_other_self");
				message.setTT(target->getDisplayedName());
				message.setDI(woundsHealed);
				message.setTO("@jedi_spam:" + CreatureAttribute::getName(attribute) + "_wounds");
				creature->sendSystemMessage(message);

				StringIdChatParameter messageOther("jedi_spam", "heal_other_other");
				messageOther.setDI(woundsHealed);
				message.setTO("@jedi_spam:" + CreatureAttribute::getName(attribute) + "_wounds");
				target->sendSystemMessage(messageOther);
			}
		}

		if (bfHealed > 0) {
			if (target == creature) {
				StringIdChatParameter message("jedi_spam", "heal_self");
				message.setDI(bfHealed);
				message.setTO("@jedi_spam:battle_fatigue");

				creature->sendSystemMessage(message);
			}
			else {
				StringIdChatParameter message("jedi_spam", "heal_other_self");
				message.setTT(target->getDisplayedName());
				message.setDI(bfHealed);
				message.setTO("@jedi_spam:battle_fatigue");
				creature->sendSystemMessage(message);

				StringIdChatParameter messageOther("jedi_spam", "heal_other_other");
				messageOther.setDI(bfHealed);
				messageOther.setTO("@jedi_spam:battle_fatigue");
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

	bool canPerformHeal(CreatureObject* creature) {
		for (int i = 0; i < healAttributesDamage.size(); ++i) {
			if (creature->hasDamage(healAttributesDamage.elementAt(i).getKey())) {
				return true;
			}
		}

		for (int i = 0; i < healAttributesWounds.size(); ++i) {
			if (creature->getWounds(healAttributesWounds.elementAt(i).getKey()) != 0) {
				return true;
			}
		}

		for (int i = 0; i < healStates.size(); ++i) {
			if (creature->hasState(healStates.get(i))) {
				return true;
			}
		}

		for (int i = 0; i < healDots.size(); ++i) {
			if (creature->hasState(healDots.get(i))) {
				return true;
			}
		}

		return false;
	}

	int doJediSelfChecks(CreatureObject* creature) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		if (creature->hasAttackDelay()) {
			return GENERALERROR;
		}

		if (!checkForceCost(creature)) {
			creature->sendSystemMessage("@jedi_spam:no_force_power");
			return GENERALERROR;
		}

		return SUCCESS;
	}

	int doJediHealCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		int res = doJediSelfChecks(creature);

		if (res != SUCCESS)
			return res;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);
		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		if (!canPerformHeal(creature)) {
			creature->sendSystemMessage("@jedi_spam:no_damage_heal_self"); // You have no damage of that type.
			return GENERALERROR;
		}


		if (creatureTarget != NULL && creatureTarget != creature) {
			if (!canPerformHeal(creatureTarget)) {
				creature->sendSystemMessage("@jedi_spam:no_damage_heal_other"); // Your target has no damage of that type to heal.
				return GENERALERROR;
			}

			if (healingType == SELFONLY) {
				return GENERALERROR;
			}

			if (!creatureTarget->isHealableBy(creature)) {
				creature->sendSystemMessage("@jedi_spam:no_help_target"); // You are not permitted to help that target.
				return GENERALERROR;
			}
		}

		if (creatureTarget == NULL && healingType == TARGETONLY) {
			return GENERALERROR;
		}

		// Heal Damage.
		int healedDamage = 0;

		for (int i = 0; i < healAttributesDamage.size(); ++i) {
			healedDamage += creature->healDamage(creatureTarget, healAttributesDamage.elementAt(i).getKey(), healAttributesDamage.elementAt(i).getValue());
			sendHealSystemMessage(creature, creatureTarget, healAttributesDamage.elementAt(i).getKey(), healedDamage);
		}

		int forceCostDeducted = forceCost;

		forceCostDeducted += (healedDamage / 20);


		// Heal Wounds.
		int healedWounds = 0;

		for (int i = 0; i < healAttributesWounds.size(); ++i) {
			healedWounds += creature->healWound(creatureTarget, healAttributesWounds.elementAt(i).getKey(), healAttributesWounds.elementAt(i).getValue());
			sendHealSystemMessage(creature, creatureTarget, healAttributesWounds.elementAt(i).getKey(), 0, healedWounds);
		}

		forceCostDeducted += healedWounds / 20;


		// Heal States.
		for (int i = 0; i < healStates.size(); ++i) {
			creatureTarget->clearState(healStates.get(i), true);
			forceCostDeducted += 10;
		}


		// Heal Dots, by DoT type, then reduction.
		for (int i = 0; i < healDots.size(); ++i) {
			creatureTarget->healDot(healDots.elementAt(i).getKey(), healDots.elementAt(i).getValue());
			forceCostDeducted += 20;
		}

		// Heal BF
		if (healBF != 0) {
			int currentValue = creatureTarget->getShockWounds();

			int healedValue = MIN(currentValue, healBF);

			creatureTarget->addShockWounds(-healedValue);
			sendHealSystemMessage(creature, creatureTarget, 0, 0, 0, healedValue);

			forceCostDeducted += healBF / 5;
		}

		// Animations / CE's.
		doAnimations(creature, creatureTarget);

		// Deduct Force cost.
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject != NULL)
			playerObject->setForcePower(playerObject->getForcePower() - forceCostDeducted);

		return SUCCESS;
	}

	int doJediBuffCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		for (int i=0; i < buffCRCs.size(); ++i) {
			if (creature->hasBuff(buffCRCs.get(i))) {
				creature->sendSystemMessage("@jedi_spam:force_buff_present");
				return GENERALERROR;
			}
		}

		int res = doJediSelfChecks(creature);

		if (res != SUCCESS)
			return res;


		StringIdChatParameter startStringId("jedi_spam", "apply_" + name);
		StringIdChatParameter endStringId("jedi_spam", "remove_" + name);

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);
		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		// Need first buff (0) for the buff, the others are checks.
		ManagedReference<SingleUseBuff*> buff = new SingleUseBuff(creature, buffCRCs.get(0), duration, BuffType::JEDI, getNameCRC());
		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);


		if (buffEventType != 0) {
			Vector<unsigned int> eventTypes;
			eventTypes.add(buffEventType);
			buff->init(&eventTypes);
		}

		for (int i=0; i < skillMods.size(); ++i) {
			buff->setSkillModifier(skillMods.elementAt(i).getKey(),skillMods.elementAt(i).getValue());
		}
		creature->addBuff(buff);

		doAnimations(creature, creatureTarget);

		// Deduct Force cost.
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject != NULL)
			playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		return SUCCESS;
	}

	void setForceCost(int fpc) {
		forceCost = fpc;
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) {
		return defaultTime * 3.0;
	}
};


#endif /* JEDIQUEUECOMMAND_H_ */
