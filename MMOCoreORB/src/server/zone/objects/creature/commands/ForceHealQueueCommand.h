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
protected:
	int speed;
	float forceCost; // describes the "maximum" force Cost.. this is to not attempt healing without the proper amount of force
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
	ForceHealQueueCommand(const String& name, ZoneProcessServer* server)
: QueueCommand(name, server) {
		speed = 3;
		forceCost = 0;
		forceCostDivisor = 0;
		
		healStates = 0;

		healBleeding = 0;
		healPoison = 0;
		healBleeding = 0;
		healFire = 0;
		
		healAttributes = 0;
		healWoundAttributes = 0;

		healBattleFatigue = 0;
		healAmount = 0;
		healWoundAmount = 0;

		range = 0;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget, healedAttributes_t& attributes) const {

		if (creature == creatureTarget)
			creature->playEffect("clienteffect/pl_force_heal_self.cef", "");
		else
			creature->doCombatAnimation(creatureTarget,STRING_HASHCODE("force_healing_1"),0,0xFF);
	}

	int doHealBF(CreatureObject* creature, CreatureObject* target, healedAttributes_t& attrs) const {
		if (creature == NULL || target == NULL) return GENERALERROR;

		int currentValue = creature->getShockWounds();

		if (currentValue > 0) {
			int healedValue = MIN(currentValue, healBattleFatigue);

			target->addShockWounds(-healedValue, true, false);
			attrs.healedBF = healedValue;
		}

		return SUCCESS;
	}


	int checkWoundAttributes(CreatureObject* creature, CreatureObject* targetCreature) const {
		int retval = 0;
		if (targetCreature == NULL) return 0;
		creature->sendSystemMessage("healWoundAttributes: " + String::valueOf(healWoundAttributes));
		if (healWoundAttributes & CombatManager::HEALTH) {
			if (targetCreature->getWounds(CreatureAttribute::HEALTH) ||
			    targetCreature->getWounds(CreatureAttribute::CONSTITUTION) ||
			    targetCreature->getWounds(CreatureAttribute::STRENGTH)
			) {
				retval |= HEALTH;
			}
		}

		if (healWoundAttributes & CombatManager::ACTION) {
			if (targetCreature->getWounds(CreatureAttribute::ACTION) ||
			    targetCreature->getWounds(CreatureAttribute::QUICKNESS) ||
			    targetCreature->getWounds(CreatureAttribute::STAMINA)
			) {
				retval |= ACTION;
			}
		}

		if (healWoundAttributes & CombatManager::MIND) {
			if (targetCreature->getWounds(CreatureAttribute::MIND) ||
			    targetCreature->getWounds(CreatureAttribute::FOCUS) ||
			    targetCreature->getWounds(CreatureAttribute::WILLPOWER)
			) {
				retval |= MIND;
			}
		}
		creature->sendSystemMessage("healWoundAttributes result: " + String::valueOf(retval));
		return retval;
	}

	int doHealWounds(CreatureObject* creature, CreatureObject* targetCreature, int healableWounds, healedAttributes_t& attrs) const {
		if (targetCreature == NULL) return GENERALERROR;

		creature->sendSystemMessage("Healing wounds " + String::valueOf(healWoundAmount) + " " + String::valueOf(healableWounds));

		if (healableWounds & HEALTH) {
			attrs.healedHealthWounds = targetCreature->healWound(creature, CreatureAttribute::HEALTH, healWoundAmount, true);
			attrs.healedStrengthWounds = targetCreature->healWound(creature, CreatureAttribute::STRENGTH, healWoundAmount, true);
			attrs.healedConstitutionWounds = targetCreature->healWound(creature, CreatureAttribute::CONSTITUTION, healWoundAmount, true);
		}

		if (healableWounds & ACTION) {
			attrs.healedActionWounds = targetCreature->healWound(creature, CreatureAttribute::ACTION, healWoundAmount, true);
			attrs.healedQuicknessWounds = targetCreature->healWound(creature, CreatureAttribute::QUICKNESS, healWoundAmount, true);
			attrs.healedWillpowerWounds = targetCreature->healWound(creature, CreatureAttribute::WILLPOWER, healWoundAmount, true);
		}

		if (healableWounds & MIND) {
			attrs.healedMindWounds = targetCreature->healWound(creature, CreatureAttribute::MIND, healWoundAmount, true);
			attrs.healedFocusWounds = targetCreature->healWound(creature, CreatureAttribute::FOCUS, healWoundAmount, true);
			attrs.healedWillpowerWounds = targetCreature->healWound(creature, CreatureAttribute::WILLPOWER, healWoundAmount, true);
		}

		return SUCCESS;
	}
	
	int checkHAMAttributes(CreatureObject* creature, CreatureObject* targetCreature) const {
		int retval = 0;
		if (healAttributes == 0 || creature == NULL || targetCreature == NULL) return 0;
		creature->sendSystemMessage("healAttributes:" + String::valueOf(healAttributes)); 


		// check for the pools that shall be healed and if they are damaged
		// we also translate from CombatManager attributes to our own bitset
		if (healAttributes & CombatManager::HEALTH) {
			if (targetCreature->hasDamage(CreatureAttribute::HEALTH)) {
				retval |= HEALTH;
			}
		}

		if (healAttributes & CombatManager::ACTION) {
			if (targetCreature->hasDamage(CreatureAttribute::ACTION)) {
				retval |= ACTION;
			}
		}

		if (healAttributes & CombatManager::MIND) {
			if (targetCreature->hasDamage(CreatureAttribute::MIND)) {
				retval |= MIND;
			}
		}

		return retval;
	}

	int doHealHAM(CreatureObject* creature, CreatureObject* target, int healableHAM, healedAttributes_t& attrs) const {
		if (target == NULL) return GENERALERROR;
		creature->sendSystemMessage("Healable HAM:" + String::valueOf(healableHAM));
		if (healableHAM & HEALTH) {
			attrs.healedHealth = target->healDamage(creature, CreatureAttribute::HEALTH, healAmount);
		}

		if (healableHAM & ACTION) {
			attrs.healedAction = target->healDamage(creature, CreatureAttribute::ACTION, healAmount);
		}

		if (healableHAM & MIND) {
			attrs.healedMind = target->healDamage(creature, CreatureAttribute::MIND, healAmount);
		}

		return SUCCESS;
	}

	int checkStates(CreatureObject* creature, CreatureObject* target) const {
		int retval = 0;
		if (creature == NULL || target == NULL || healStates == 0) return 0;

		if (healStates & STUN) {
			if (target->hasState(CreatureState::STUNNED)) {
				retval |= STUN;
			}
		}

		if (healStates & DIZZY) {
			if (target->hasState(CreatureState::DIZZY)) {
				retval |= STUN;		
			}
		}

		if (healStates & BLIND) {
			if (target->hasState(CreatureState::BLINDED)) {
				retval |= BLIND;
			}
		}

		if (healStates & INTIMIDATE) {
			if (target->hasState(CreatureState::INTIMIDATED)) {
				retval |= INTIMIDATE;
			}
		}

		return retval;
	}

	int doHealStates(CreatureObject* creature, CreatureObject* target, int healableStates, healedAttributes_t& attrs) const {
		if (creature == NULL || target == NULL)
			return GENERALERROR;
	
		if (healableStates & STUN) {
			target->removeStateBuff(CreatureState::STUNNED);
			attrs.healedStates |= STUN;
		}

		if (healableStates & DIZZY) {
			target->removeStateBuff(CreatureState::DIZZY);
			attrs.healedStates |= DIZZY;
		}

		if (healableStates & BLIND) {
			target->removeStateBuff(CreatureState::BLINDED);
			attrs.healedStates |= BLIND;
		}

		if (healableStates & INTIMIDATE) {
			target->removeStateBuff(CreatureState::INTIMIDATED);
			attrs.healedStates |= INTIMIDATE;
		}

		return SUCCESS;
	}

	int doHealDots(CreatureObject* creature, CreatureObject* target, int healableDots, healedAttributes_t& attrs) const {
		if (creature == NULL || target == NULL)  return GENERALERROR;
		
		if (healableDots & DISEASED) {
			attrs.healedDisease = creature->healDot(CreatureState::DISEASED, healDisease); 
		}

		if (healableDots & POISONED) {
			attrs.healedPoison = creature->healDot(CreatureState::POISONED, healPoison);
		}

		if (healableDots & ONFIRE) {
			attrs.healedFire = creature->healDot(CreatureState::ONFIRE, healFire);
		}

		if (healableDots & BLEEDING) {
			attrs.healedBleeding = creature->healDot(CreatureState::BLEEDING, healBleeding);
		}

		return SUCCESS;
	}

	int checkDots(CreatureObject* creature, CreatureObject* target) const {
		int retval = 0;
		if (creature == NULL || target == NULL) return 0;

		if (healDisease > 0) {
			if (creature->isDiseased()) {
				retval |= DISEASED;		
			}
		}

		if (healPoison > 0) {
			if (creature->isPoisoned()) {
				retval |= POISONED;
			}
		}

		if (healBleeding > 0) {
			if (creature->isBleeding()) {
				retval |= BLEEDING;
			}
		}

		if (healFire > 0) {
			if (creature->isOnFire()) {
				retval |= ONFIRE;
			}
		}

		return retval;
	}



	int doForceCheck(CreatureObject* creature) const {
		if (!creature->isPlayerCreature()) return GENERALERROR;

		const int currentForcePower = creature->getPlayerObject()->getForcePower();
		if (currentForcePower < forceCost) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //You do not have enough force to do that.
			return GENERALERROR;
		}
		return SUCCESS;
	}

	int calculateForceCost(CreatureObject* creature, CreatureObject* targetCreature, healedAttributes_t& attrs) const {
		// we simply assume all attributes that we aren't supposed to have healed
		// are zero since we didn initialize the struct with zero...
		
		int calculatedForceCost = 0;

		if (forceCostDivisor != 0) { //forceCostDivisor < 0 || forceCostDivisor > 0
			
		
			// HAM
			int amountHealed = attrs.sumHAM(); 
			// Wounds
			amountHealed += attrs.sumWounds(); 
			// Dots
			amountHealed += attrs.sumDots();
			/*
			 * Is BF being charged for?
			 *
			amountHealed += attrs.healedBF;
			 */

			if (forceCostDivisor < 0)
				calculatedForceCost = amountHealed;
			else // forceCostDevisor > 0
				if (forceCostDivisor > 1)
					calculatedForceCost = amountHealed / forceCostDivisor;

			// if forceCost > 0 we will ensure the total costs are never above it
			if (forceCost > 0) {
				calculatedForceCost = MIN(calculatedForceCost, forceCost); 
			}

		} else { // forceCostDivisor == 0
			calculatedForceCost = forceCost;
		}

		// if someone figures out how to overflow this make sure they can't earn force with it
		if (calculatedForceCost < 0)
			calculatedForceCost = 0;

		return calculatedForceCost;

	}

	inline void sendHealBleedingMessage(CreatureObject* creature, CreatureObject* target, int attribute, int amount) {
		if (creature == NULL || amount <= 0) return;

		// TODO: get current bleeding and check if we did completly cure it off
		if (creature != target) {
			StringIdChatParameter message("jedi_spam", "staunch_bleeding_other");
			message.setTT(target->getFirstName());
			creature->sendSystemMessage(message);
			// TODO: string if for "Your bleeding has slightly decreased by ..."
		} else {
			// TODO: you slightly reduced your bleeding
		}
	}

	static bool setHealMessageTO(StringIdChatParameter& message, int type, const bool wounds = false) {

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
	static bool setWoundHealMessageTO(StringIdChatParameter& message, int type) {
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


	void sendHealMessage(CreatureObject* creature, CreatureObject* target, int attribute, const int amount, const bool wound = false) const {
		if (creature == NULL || target == NULL || amount <= 0) return;

		// store if we are healing ourselfs or not
		const bool isSame = creature == target;

		StringIdChatParameter message("jedi_spam", (isSame)?"heal_self": "heal_other_self");
		bool res = false;
		if (!wound)
			res = setHealMessageTO(message, attribute);
		else
			res = setWoundHealMessageTO(message, attribute);

		if (!res) {
			creature->error("Tried to send heal message for unknown attribute.");
			return;
		}

		if (!isSame)
			message.setTT(target->getFirstName());

		message.setDI(amount);
		creature->sendSystemMessage(message);

		if (!isSame) {
			// send the 'you've been healed by ...' messages

			StringIdChatParameter message("jedi_spam", "heal_other_other");
			res = false;
			if (!wound)
				res = setHealMessageTO(message, attribute);
			else
				res = setWoundHealMessageTO(message, attribute);

			if (!res) {
				creature->error("Tried to send heal message for unknown attribute.");
				return;
			}
			message.setTT(creature->getFirstName());
			message.setDI(amount);
		}

	}


	void sendSystemMessage(CreatureObject* creature, CreatureObject* target, healedAttributes_t& attrs) const {
		const bool didHealTarget = creature != target;
	
		// check if we did any healing at all, if not respond
		// with "No damage of that type"
		// FIXME: we could just reuse the bitmasks from before?!?
		const int dots = attrs.sumDots();
		const int ham = attrs.sumHAM();
		const int wounds = attrs.sumWounds();
	

		if (dots + ham + attrs.healedStates + attrs.healedBF == 0) {
			creature->sendSystemMessage("@jedi_spam:no_damage_heal_self");
			return;
		} else {
			if (ham != 0) {
				sendHealMessage(creature, target, CreatureAttribute::HEALTH, attrs.healedHealth);
				sendHealMessage(creature, target, CreatureAttribute::ACTION, attrs.healedAction);
				sendHealMessage(creature, target, CreatureAttribute::MIND, attrs.healedMind);
			}
			if (dots != 0) {
				if (attrs.healedBleeding) {
					//sendHealBleedMessage(creature, target, attrs.healedBleeding);
				}
			}

			if (wounds != 0) {
				sendHealMessage(creature, target, HEALTH, attrs.healedHealthWounds, true);
				sendHealMessage(creature, target, STRENGTH, attrs.healedStrengthWounds, true);
				sendHealMessage(creature, target, CONSTITUTION, attrs.healedConstitutionWounds, true);

				sendHealMessage(creature, target, ACTION, attrs.healedActionWounds, true);
				sendHealMessage(creature, target, QUICKNESS, attrs.healedActionWounds, true);
				sendHealMessage(creature, target, STAMINA, attrs.healedStaminaWounds, true);

				sendHealMessage(creature, target, MIND, attrs.healedMindWounds, true);
				sendHealMessage(creature, target, FOCUS, attrs.healedFocusWounds, true);
				sendHealMessage(creature, target, WILLPOWER, attrs.healedWillpowerWounds, true);
			}
		}	
	}

	// we use this to simplify the locking, so we only need one check before entrance
	// and one check after we left this function again.
	
	int runCommandWithTarget(CreatureObject* creature, CreatureObject* targetCreature) const {
		if (creature == targetCreature) // no self healing
			return GENERALERROR;

		Locker crossLocker(targetCreature, creature);

		if (creature->isKnockedDown()) {
			return GENERALERROR; 
		}

		if (!creature->isInRange(targetCreature, range + targetCreature->getTemplateRadius() + creature->getTemplateRadius())) {
			// out of range
			return TOOFAR;
		}

		if (!CollisionManager::checkLineOfSight(creature, targetCreature)) {
			creature->sendSystemMessage("@container_error_message:container18"); // not in sight?!?
			return GENERALERROR;	
		}

		if (!targetCreature->isHealableBy(creature)) {
			// TEF etc.? Do we need extra TEF checks?
			creature->sendSystemMessage("@healing:pvp_no_help");
			return GENERALERROR;
		}
		// continue with the common path
		return runCommand(creature, targetCreature);
	}

	int runCommand(CreatureObject* creature, CreatureObject* targetCreature) const {
		// keep the information about what will be healed and what has been healed so we can make the code a bit cleaner
		healedAttributes_t healedAttributes = {};
		bool didHeal = false;
		
		// check if the player fullfills the minimum force requirement.
		// An alternative approach might be to calculate force cost at each 
		// heal step and then check if we can proceed with further healing.
		// I am not sure how it was done back then...
		int forceCheckRetVal = doForceCheck(creature);
		if (forceCheckRetVal != SUCCESS) {
			return forceCheckRetVal;
		}

		if (healAttributes != 0 && healAmount != 0) {
			// create a bitset so we can probe which attributes need healing and are allowed to be healed
			const int healableHAMAttributes = checkHAMAttributes(creature, targetCreature);
			if (healableHAMAttributes != 0) {
				int retval = doHealHAM(creature, targetCreature, healableHAMAttributes, healedAttributes);
				if (retval != SUCCESS) {
					return retval;
				}
				didHeal = true;
			}
		}
		
		if (healWoundAttributes != 0 && healWoundAmount != 0) {
			const int healableWounds = checkWoundAttributes(creature, targetCreature);
			if (healableWounds != 0) {
				int retval = doHealWounds(creature, targetCreature, healableWounds, healedAttributes);
				if (retval != SUCCESS) {
					return retval;
				}
				didHeal = true;
			}
			
		}

		if (healStates != 0) {
			const int healableStates = checkStates(creature, targetCreature);
			if (healableStates != 0) {
				int retval = doHealStates(creature, targetCreature, healableStates, healedAttributes);
				if (retval != SUCCESS) {
					return retval;
				}
				didHeal = true;
			}
		}

		if (healDisease + healPoison + healFire + healBleeding > 0) {
			const bool healableDots = checkDots(creature, targetCreature);
			if (healableDots != 0) {
				int retval = doHealDots(creature, targetCreature, healableDots, healedAttributes);
				if (retval != SUCCESS) {
					return retval;
				}
				didHeal = true;
			}
		}

		if (healBattleFatigue > 0) {
			const int bf = targetCreature->getShockWounds();
			const bool hasBF = bf > 0;
			if (hasBF) {
				int retval = doHealBF(creature, targetCreature, healedAttributes);
				if (retval != SUCCESS) {
					return retval;
				}
				didHeal = true;
			}
		}

		if (didHeal) {
			int calculatedForceCost = calculateForceCost(creature, targetCreature, healedAttributes);
			applyForceCost(creature, calculatedForceCost);
			doAnimations(creature, targetCreature, healedAttributes);
			sendSystemMessage(creature, targetCreature, healedAttributes);
		} else {
			creature->sendSystemMessage("@jedi_spam:no_damage_heal_self");
			return GENERALERROR;
		}




		return SUCCESS;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (creature == NULL || !creature->isPlayerCreature())
			return GENERALERROR;
	
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject == NULL)
			return GENERALERROR;

		// do the common stuff
		int comResult = doCommonMedicalCommandChecks(creature);

		if (comResult != SUCCESS) {
			return comResult;
		}

#ifndef JEDI_HEALING_WITH_ARMOR
		// if the jedi is wearing armor he isn't allowed to heal 
		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}
#endif
		ManagedReference<CreatureObject*> targetCreature = creature;
		if (range > 0) {
			targetCreature = NULL;
			// we are healing someone else
			if (target != 0) {
				ManagedReference<SceneObject*> sceno = server->getZoneServer()->getObject(target);
				if (sceno != NULL && sceno->isCreatureObject()) {
					targetCreature = sceno.castTo<CreatureObject*>();
				}
			}
		}

		if (targetCreature == NULL) {
			// we couldn't find a valid target
			return GENERALERROR;
		}

		CreatureObject* targetC = targetCreature.get();

		int retval = GENERALERROR;
		// for of the execution in a path that does cross locking for player2player heals
		// and one for self-heals
		if (targetC != creature)
			retval = runCommandWithTarget(creature, targetC);
		else	
			retval = runCommand(creature, targetC);

		return retval;
	}

	void applyForceCost(CreatureObject* creature, int calculatedForceCost) const {
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject == NULL) return;

		int currentForce = playerObject->getForcePower();
		if (currentForce < calculatedForceCost) {
			// this sucks, we did all this healing and now he suddnely doesn't
			// have enough force? :(
			playerObject->setForcePower(0);
			creature->error("Does not have enough force to pay for the healing he did...");
		} else {
			playerObject->setForcePower(currentForce - calculatedForceCost);
		}
	}


	bool isForceHealCommand() {
		return true;
	}

	void setForceCost(int fpc) {
		forceCost = fpc;
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
		range = range;
	}

	void setSpeed(int s) {
		speed = s;
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * 3.0;
	}
};


#endif /* FORCEHEALQUEUECOMMAND_H_ */
