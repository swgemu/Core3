/*
 * TendCommand.h
 *
 *  Created on: 13/08/2010
 *      Author: victor
 */

#ifndef TENDCOMMAND_H_
#define TENDCOMMAND_H_


#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/pharmaceutical/CurePack.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/events/InjuryTreatmentTask.h"
#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/BuffAttribute.h"
#include "server/zone/objects/creature/buffs/DelayedBuff.h"
#include "server/zone/packets/object/CombatAction.h"
#include "QueueCommand.h"

class TendCommand : public QueueCommand {
protected:
	int mindCost;
	int mindWoundCost;

	int healthHealed;
	int actionHealed;
	int mindHealed;

	uint8 woundPool;
	int woundsHealed;

	bool tendDamage;
	bool tendWound;

	float speed;
	float range;
	String effectName;

public:
	TendCommand(const String& name, ZoneProcessServer* server)
	: QueueCommand(name, server) {
		mindCost = 0;
		mindWoundCost = 0;

		range = 0;

		healthHealed = 0;
		actionHealed = 0;
		mindHealed = 0;

		woundPool = 0;
		woundsHealed = 0;

		tendDamage = false;
		tendWound = false;

		speed = 0.0f;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!effectName.isEmpty())
			creatureTarget->playEffect(effectName, "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	void sendHealMessage(CreatureObject* creature, CreatureObject* creatureTarget, int healthDamage, int actionDamage) {
		if (!creature->isPlayerCreature() || !creatureTarget->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);
		CreatureObject* playerTarget = cast<CreatureObject*>( creatureTarget);

		StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

		if (healthDamage > 0 && actionDamage > 0) {
			msgBody << healthDamage << " health and " << actionDamage << " action";
		} else if (healthDamage > 0) {
			msgBody << healthDamage << " health";
		} else if (actionDamage > 0) {
			msgBody << actionDamage << " action";
		} else {
			return; //No damage to heal.
		}

		msgTail << " damage.";

		if (creature == creatureTarget) {
			msgPlayer << "You heal yourself for " << msgBody.toString() << msgTail.toString();
			player->sendSystemMessage(msgPlayer.toString());
		} else {
			msgPlayer << "You heal " << playerTarget->getFirstName() << " for " << msgBody.toString() << msgTail.toString();
			msgTarget << player->getFirstName() << " heals you for " << msgBody.toString() << msgTail.toString();

			player->sendSystemMessage(msgPlayer.toString());
			playerTarget->sendSystemMessage(msgTarget.toString());
		}
	}

	void sendWoundMessage(CreatureObject* creature, CreatureObject* creatureTarget, int poolAffected, int woundsHealed) {
		if (!creature->isPlayerCreature() || !creatureTarget->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);
		CreatureObject* playerTarget = cast<CreatureObject*>( creatureTarget);

		String creatureName = player->getFirstName();
		String creatureTargetName = playerTarget->getFirstName();

		String poolName = CreatureAttribute::getName(poolAffected);

		StringBuffer msgPlayer, msgTarget, msgTail;

		if (creature == creatureTarget) {
			msgTarget << "You heal yourself for ";
		} else {
			msgPlayer << "You heal " << creatureTargetName << " for ";
			msgTarget << creatureName << " heals you for ";
		}

		msgTail << woundsHealed << " " << poolName << " wound damage.";

		msgTarget << msgTail.toString();
		creatureTarget->sendSystemMessage(msgTarget.toString());

		if (creature != creatureTarget) {
			msgPlayer << msgTail.toString();
			creature->sendSystemMessage(msgPlayer.toString());
		}
	}

	void awardXp(CreatureObject* creature, const String& type, int power) {
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);

		int amount = (int) round((float) power * 1.0f);

		if (amount <= 0)
			return;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->awardExperience(player, type, amount, true);
	}

	uint8 findAttribute(CreatureObject* creature, uint8 startAttribute = 0) {
		for (int i = startAttribute; i < 9; ++i) {
			int wounds = creature->getWounds(i);

			if (wounds != 0)
				return i;
		}

		return CreatureAttribute::UNKNOWN;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL) {
			if (!object->isCreatureObject()) {
				TangibleObject* tangibleObject = dynamic_cast<TangibleObject*>(object.get());

				if (tangibleObject != NULL && tangibleObject->isAttackableBy(creature)) {
					object = creature;
				} else
					return INVALIDTARGET;
			}
		} else
			object = creature;

		CreatureObject* creatureTarget = cast<CreatureObject*>(object.get());

		if (creatureTarget == NULL /*|| (!creatureTarget->isPlayer() && !creatureTarget->isNonPlayerCreature())*/) {
			creature->sendSystemMessage("@healing_response:healing_response_a1"); //Target must be a player or a creature pet in order to tend damage.
			return INVALIDTARGET;
		}

		Locker clocker(creatureTarget, creature);

		if (creatureTarget->isAiAgent() || creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted() || creatureTarget->isAttackableBy(creature))
			creatureTarget = creature;

		if (!creatureTarget->isInRange(creature, range))
			return TOOFAR;

		uint8 attribute = findAttribute(creatureTarget);

		if (creature->isProne()) {
			creature->sendSystemMessage("You cannot do that while prone.");
			return INVALIDLOCOMOTION;
		}

		if (creature->isMeditating()) {
			creature->sendSystemMessage("You cannot do that while Meditating.");
			return INVALIDSTATE;
		}

		if (creature->isRidingCreature()) {
			creature->sendSystemMessage("You cannot do that while Riding a Creature.");
			return INVALIDLOCOMOTION;
		}

		if (creature->isMounted()) {
			creature->sendSystemMessage("You cannot do that while Driving a Vehicle.");
			return INVALIDLOCOMOTION;
		}

		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help");
			return INVALIDTARGET;
		}

		if (creature->getHAM(CreatureAttribute::MIND) < mindCost) {
			creature->sendSystemMessage("@healing_response:not_enough_mind"); //You do not have enough mind to do that.
			return INSUFFICIENTHAM;
		}

		float bfScale = 1 - creatureTarget->calculateBFRatio();

		if (tendDamage) {
			if (!creatureTarget->hasDamage(CreatureAttribute::HEALTH) && !creatureTarget->hasDamage(CreatureAttribute::ACTION)) {
				if (creatureTarget == creature)
					creature->sendSystemMessage("@healing_response:healing_response_61"); //You have no damage to heal.
				else {
					StringIdChatParameter stringId("healing_response", "healing_response_63"); //%NT has no damage to heal.
					stringId.setTT(creatureTarget->getObjectID());
					creature->sendSystemMessage(stringId);
				}

				return GENERALERROR;
			}

			int healPower = round(((float)creature->getSkillMod("healing_injury_treatment") / 3.f + 20.f) * bfScale);

			int healedHealth = creatureTarget->healDamage(creature, CreatureAttribute::HEALTH, healPower);
			int healedAction = creatureTarget->healDamage(creature, CreatureAttribute::ACTION, healPower, true, false);

			sendHealMessage(creature, creatureTarget, healedHealth, healedAction);
		} else if (tendWound) {
			if (attribute >= CreatureAttribute::MIND)
				attribute = CreatureAttribute::UNKNOWN;

			if (attribute == CreatureAttribute::UNKNOWN || creatureTarget->getWounds(attribute) == 0) {
				if (creatureTarget == creature)
					creature->sendSystemMessage("@healing_response:healing_response_67");
				else if (creatureTarget->isPlayerCreature()){
					creature->sendSystemMessage(creatureTarget->getFirstName() + " has no wounds of that type to heal.");
				}

				return GENERALERROR;
			}

			int healPower = round(((float)creature->getSkillMod("healing_wound_treatment") / 3.f + 20.f) * bfScale);

			int healedWounds = creatureTarget->healWound(creature, attribute, healPower);

			sendWoundMessage(creature, creatureTarget, attribute, -healedWounds);
		} else
			return GENERALERROR;

		if (creature->isPlayerCreature() && creatureTarget->isPlayerCreature()) {
			PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
			playerManager->sendBattleFatigueMessage(creature, creatureTarget);
		}

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCost, false);
		creature->addWounds(CreatureAttribute::FOCUS, mindWoundCost);
		creature->addWounds(CreatureAttribute::WILLPOWER, mindWoundCost);
		//creature->changeWillpowerWoundsBar(mindWoundCost);
		creature->addShockWounds(2);

		if (creatureTarget != creature && tendWound)
			awardXp(creature, "medical", 100);

		doAnimations(creature, creatureTarget);

		return SUCCESS;
	}

};

#endif /* TENDCOMMAND_H_ */
