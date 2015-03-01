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
	bool isSelfHeal; // True = it's self healing only, false = it can be used on self or target.
	bool isTargetHeal; // True = it's target healing only, not for self, false it's a self heal.

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
		isSelfHeal = false;
		isTargetHeal = false;

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

	// States and Dots are taken care of by their respective methods.
	void sendHealSystemMessage(CreatureObject* creature, CreatureObject* target, uint8 attribute, int damageHealed = 0, int woundsHealed = 0, int bfHealed = 0) {

		if (target != creature && creature != target)
			creature = target;


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

		if (isWarcried(creature)) {
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
			return GENERALERROR;

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

			if (isSelfHeal && !isTargetHeal) {
				return GENERALERROR;
			}
		}

		if (creatureTarget == NULL && isSelfHeal) {
			creatureTarget = creature;
		} else if (creatureTarget == NULL && isTargetHeal && !isSelfHeal) {
			return GENERALERROR;
		}

		// Heal Damage.
		int healedDamage = 0;

		for (int i = 0; i < healAttributesDamage.size(); ++i) {
			healedDamage += creature->healDamage(creatureTarget, healAttributesDamage.elementAt(i).getKey(), healAttributesDamage.elementAt(i).getValue());
			sendHealSystemMessage(creature, creatureTarget, healAttributesDamage.elementAt(i).getKey(), healedDamage);
		}

		forceCost += healedDamage / 20;


		// Heal Wounds.
		int healedWounds = 0;

		for (int i = 0; i < healAttributesWounds.size(); ++i) {
			healedWounds += creature->healWound(creatureTarget, healAttributesWounds.elementAt(i).getKey(), healAttributesWounds.elementAt(i).getValue());
			sendHealSystemMessage(creature, creatureTarget, healAttributesWounds.elementAt(i).getKey(), 0, healedWounds);
		}

		forceCost += healedWounds / 20;


		// Heal States.
		for (int i = 0; i < healStates.size(); ++i) {
			creatureTarget->clearState(healStates.get(i), true);
		}


		// Heal Dots, by DoT type, then reduction.
		for (int i = 0; i < healDots.size(); ++i) {
			creatureTarget->healDot(healDots.elementAt(i).getKey(), healDots.elementAt(i).getValue());
		}

		// Heal BF
		if (healBF != 0) {
			int currentValue = creatureTarget->getShockWounds();

			int healedValue = MIN(currentValue, healBF);

			creatureTarget->addShockWounds(-healedValue);
			sendHealSystemMessage(creature, creatureTarget, 0, 0, 0, healedValue);
		}

		// Animations / CE's.
		doAnimations(creature, creatureTarget);

		// Deduct Force cost.
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject != NULL)
			playerObject->setForcePower(playerObject->getForcePower() - forceCost);

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
			return GENERALERROR;


		StringIdChatParameter startStringId("jedi_spam", "apply_" + name);
		StringIdChatParameter endStringId("jedi_spam", "remove_" + name);
		Vector<unsigned int> eventTypes;
		eventTypes.add(ObserverEventType::FORCEBUFFHIT);

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);
		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		ManagedReference<SingleUseBuff*> buff = new SingleUseBuff(creature, buffCRCs.get(0), duration, BuffType::JEDI, getNameCRC());
		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);
		buff->init(&eventTypes);

		for (int i=0; i < skillMods.size(); ++i) {
			buff->setSkillModifier(skillMods.elementAt(0).getKey(),skillMods.elementAt(0).getValue());
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
