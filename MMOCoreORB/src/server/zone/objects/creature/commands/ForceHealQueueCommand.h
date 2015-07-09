/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEHEALQUEUECOMMAND_H_
#define FORCEHEALQUEUECOMMAND_H_


#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "JediQueueCommand.h"


class ForceHealQueueCommand : public JediQueueCommand {
public:
	// Introducing our own enums since those will support being used in bitsets
	enum  {
		HEALTH = 1,
		STRENGTH = 2,
		CONSTITUTION = 4,
		ACTION = 8,
		QUICKNESS = 16,
		STAMINA = 32,
		MIND = 64,
		FOCUS = 128,
		WILLPOWER = 256
	};

	enum {
		STUN = 1,
		DIZZY = 2,
		BLIND = 4,
		INTIMIDATE = 8
	};

	enum {
		DISEASED = 1,
		POISONED = 2,
		BLEEDING = 4,
		ONFIRE   = 8
	};

	// these two enums are used for skills that allow healing on self and
	// others.
	enum {
		TARGET_AUTO = 0, // go by range !=0 for ranged / this is default
		TARGET_SELF = 1,
		TARGET_OTHER = 2
	};
protected:
	int speed;
	unsigned int allowedTarget;
	//int forceCost; // the inherited forceCost attribute describes the "maximum" force Cost.. this is to not attempt healing without the proper amount of force
	float forceCostDivisor; // reduces force cost.. FIXME: rename to forceCostDivisor
			       // if negtive all healed values (ham, wounds, bf) will be added up and used as FC
			       // if zero forceCost will be substracted
			       // if >0 the healed values will be summed up and divided by this value

	unsigned int healStates; // bitmask of states to heal (STUN | DIZZY | BLINDED | INITIMDATED )
	
	unsigned int healDisease; // > 0 heals given amount of dot damage
	unsigned int healPoison; // > 0 heals given amount of poison
	unsigned int healBleeding; // > 0 heals given amount of bleeds
	unsigned int healFire; // > 0 heals given amount of fire dot

	int healAttributes; // bitmask of which attributes to heal, HEALTH etc..
	int healWoundAttributes; // bistmask of which attributes to heal, HEALTH etc..
				// does implicitly include 2ndaries
	


	unsigned int healBattleFatigue; // amount of BF to heal
	unsigned int healAmount; // amount to heal (HAM pools)
	unsigned int healWoundAmount; // amount of wounds to heal
	
	int range; // range to heal up to, if <= 0 it heals the user

	// to keep track of what we did heal at each invocation we will pass a struct per ref
	typedef struct {
		int healedHealth;
		int healedAction;
		int healedMind;

		int healedHealthWounds;
		int healedStrengthWounds;
		int healedConstitutionWounds;

		int healedActionWounds;
		int healedQuicknessWounds;
		int healedStaminaWounds;

		int healedMindWounds;
		int healedFocusWounds;
		int healedWillpowerWounds;

		int healedBF;

		int healedDisease;
		int healedPoison;
		int healedFire;
		int healedBleeding;

		int healedStates;

		inline int sumWounds() const {
			int sum = healedHealthWounds;
			sum += healedStrengthWounds;
			sum += healedConstitutionWounds;
			sum += healedActionWounds;
			sum += healedQuicknessWounds;
			sum += healedStaminaWounds;
			sum += healedMindWounds;
			sum += healedFocusWounds;
			sum += healedWillpowerWounds;

			return sum;
		}
		inline int sumHAM() const {
			return healedHealth + healedAction + healedMind;
		}
		inline int sumDots() const {
			return healedDisease + healedPoison + healedFire + healedBleeding;
		}
	} healedAttributes_t;

public:
	ForceHealQueueCommand(const String& name, ZoneProcessServer* server);
	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget, healedAttributes_t& attributes) const;

	int doHealBF(CreatureObject* creature, CreatureObject* target, healedAttributes_t& attrs) const; 


	int checkWoundAttributes(CreatureObject* creature, CreatureObject* targetCreature) const;

	int doHealWounds(CreatureObject* creature, CreatureObject* targetCreature, int healableWounds, healedAttributes_t& attrs) const;

	int checkHAMAttributes(CreatureObject* creature, CreatureObject* targetCreature) const;
	int doHealHAM(CreatureObject* creature, CreatureObject* target, int healableHAM, healedAttributes_t& attrs) const; 

	int checkStates(CreatureObject* creature, CreatureObject* target) const;

	int doHealStates(CreatureObject* creature, CreatureObject* target, int healableStates, healedAttributes_t& attrs) const;

	int doHealDots(CreatureObject* creature, CreatureObject* target, int healableDots, healedAttributes_t& attrs) const;

	int checkDots(CreatureObject* creature, CreatureObject* target) const; 

	int doForceCheck(CreatureObject* creature) const;

	int calculateForceCost(CreatureObject* creature, CreatureObject* targetCreature, healedAttributes_t& attrs) const; 
	void applyForceCost(CreatureObject* creature, int calculatedForceCost) const;

	/**
	 * Sends a dot heal message to the user (the healing guy)
	 * The only case where this is useful is when you are healing someone else,
	 * otherwise the DamageOverTimeList already sends the messages out.
	 *
	 * @param creature: the creature that heals
	 * @param target: the creature that is healed
	 * @param amount: the amount the creature was healed for
	 * @param stopped: the jedi_spam stf entry for the stopped case
	 * @param staunch: the jedi_spam stf entry for the staunch case
	 * @param attribute: the CreatureState enum value for the attribute that we are after
	 */
	static inline void sendHealDotMessage(CreatureObject* creature, CreatureObject* target, int amount, const char* stopped, const char* staunch, uint64 attribute) {
		if (creature == NULL || creature == target || amount <= 0) return;
		
		const int dotRemaining = creature->getDamageOverTimeList()->getStrength(0xFF, attribute);
		StringIdChatParameter message("jedi_spam", (dotRemaining > 0) ? staunch : stopped);
		message.setTT(target->getFirstName());
		creature->sendSystemMessage(message);
	}


	/**
	 * sets the TO attribute of the given StringIdChatParameter according to the type passed into it
	 * I can be run for wounds or normal HAM damage
	 * @param message: a ref to the message that should be modified
	 * @param type: the type of damage (from our own enums)
	 * @param wounds: if it should use the wound strings or not (defaults to damage)
	 */
	static inline bool setHealMessageTO(StringIdChatParameter& message, int type, const bool wounds = false) {

		switch (type) {
			case HEALTH:
				if (!wounds) 
					message.setTO("@jedi_spam:health_damage");
				else
					message.setTO("@jedi_spam:health_wounds");
				break;
			case ACTION:
				if (!wounds)
					message.setTO("@jedi_spam:action_damage");
				else
					message.setTO("@jedi_spam:action_wounds");
				break;
			case MIND:
				if (!wounds)
					message.setTO("@jedi_spam:mind_damage");
				else
					message.setTO("@jedi_spam:mind_wounds");
				break;
			default:
				return false;
		}

		return true;
	}

	/**
	 * Same as setHealMessage to besides that it does 2ndaries and only wounds.
	 */
	static inline bool setWoundHealMessageTO(StringIdChatParameter& message, int type) {
		if (!setHealMessageTO(message, type, true)) {
			switch(type) {
				case STRENGTH:
					message.setTO("@jedi_spam:strength_wounds");
					break;
				case CONSTITUTION:
					message.setTO("@jedi_spam:constitution_wounds");
					break;
				case QUICKNESS:
					message.setTO("@jedi_spam:quickness_wounds");
					break;
				case STAMINA:
					message.setTO("@jedi_spam:stamina_wounds");
					break;
				case FOCUS:
					message.setTO("@jedi_spam:focus_wounds");
					break;
				case WILLPOWER:
					message.setTO("@jedi_spam:willpower_wounds");
					break;
				default:
					return false;
			}
		}
		return true;
	}


	/**
	 * sends the damage & wound heal messages to a target and the healer
	 */
	void sendHealMessage(CreatureObject* creature, CreatureObject* target, int attribute, const int amount, const bool wound = false) const; 


	/**
	 * Send the healing system messages
	 * Dispatches each messages depending on the actual healing done
	 */
	void sendSystemMessage(CreatureObject* creature, CreatureObject* target, healedAttributes_t& attrs) const;

	int runCommandWithTarget(CreatureObject* creature, CreatureObject* targetCreature) const; 

	int runCommand(CreatureObject* creature, CreatureObject* targetCreature) const;

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const; 

	bool isForceHealCommand() {
		return true;
	}

	void setForceCostDivisor(float fcd) {
		forceCostDivisor = fcd;
	}

	void setHealStates(unsigned int states) {
		healStates = states;
	}

	void setHealDisease(int disease) {
		healDisease = disease;
	}

	void setHealPoison(int poison) {
		healPoison = poison;
	}

	void setHealBleeding(int bleeding) {
		healBleeding = bleeding;
	}

	void setHealFire(int fire) {
		healFire = fire;
	}

	void setHealAttributes(unsigned int attributes) {
		healAttributes = attributes;
	}

	void setHealWoundAttributes(unsigned int attributes) {
		healWoundAttributes = attributes;
	}

	void setHealBattleFatigue(unsigned int amount) {
		healBattleFatigue = amount;	
	}

	void setHealAmount(unsigned int amount ) {
		healAmount = amount;
	}

	void setHealWoundAmount(unsigned int amount) {
		healWoundAmount = amount;
	}

	void setRange(int r) {
		range = r;
	}

	void setSpeed(int s) {
		speed = s;
	}

	void setAllowedTarget(unsigned int t) {
		allowedTarget = t;
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * 3.0;
	}
};


#endif /* FORCEHEALQUEUECOMMAND_H_ */
