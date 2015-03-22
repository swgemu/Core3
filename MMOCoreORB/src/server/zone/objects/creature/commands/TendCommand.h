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
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);

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
		} else if (creatureTarget->isPlayerCreature()) {
			msgPlayer << "You heal " << creatureTarget->getFirstName() << " for " << msgBody.toString() << msgTail.toString();
			msgTarget << player->getFirstName() << " heals you for " << msgBody.toString() << msgTail.toString();

			player->sendSystemMessage(msgPlayer.toString());
			creatureTarget->sendSystemMessage(msgTarget.toString());
		} else {
			msgPlayer << "You heal " << creatureTarget->getDisplayedName() << " for " << msgBody.toString() << msgTail.toString();
			player->sendSystemMessage(msgPlayer.toString());
		}
	}

	void sendWoundMessage(CreatureObject* creature, CreatureObject* creatureTarget, int poolAffected, int woundsHealed) {
		if (!creature->isPlayerCreature())
			return;

		String poolName = CreatureAttribute::getName(poolAffected);

		StringBuffer msgPlayer, msgTarget, msgTail;

		msgTail << woundsHealed << " " << poolName << " wound damage.";

		if (creature == creatureTarget) {
			msgTarget << "You heal yourself for " << msgTail.toString();
			creatureTarget->sendSystemMessage(msgTarget.toString());
		} else if (creatureTarget->isPlayerCreature()){
			msgPlayer << "You heal " << creatureTarget->getFirstName() << " for "  << msgTail.toString();
			msgTarget << creature->getFirstName() << " heals you for "  << msgTail.toString();

			creature->sendSystemMessage(msgPlayer.toString());
			creatureTarget->sendSystemMessage(msgTarget.toString());
		} else {
			msgPlayer << "You heal " << creatureTarget->getDisplayedName() << " for " << msgTail.toString();
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

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL) {
			if (!object->isCreatureObject()) {
				TangibleObject* tangibleObject = dynamic_cast<TangibleObject*>(object.get());

				if (tangibleObject != NULL && tangibleObject->isAttackableBy(creature)) {
					object = creature;
				} else {
					creature->sendSystemMessage("@healing_response:healing_response_a1"); //Target must be a player or a creature pet in order to tend damage
					return GENERALERROR;
				}
			}
		} else
			object = creature;

		CreatureObject* creatureTarget = cast<CreatureObject*>(object.get());

		Locker clocker(creatureTarget, creature);

		if ((creatureTarget->isAiAgent() && !creatureTarget->isPet()) || creatureTarget->isDroidObject() || creatureTarget->isVehicleObject() || creatureTarget->isDead() || creatureTarget->isRidingMount() || creatureTarget->isAttackableBy(creature))
			creatureTarget = creature;

		if (!creatureTarget->isInRange(creature, range + creatureTarget->getTemplateRadius() + creature->getTemplateRadius()))
			return TOOFAR;

		uint8 attribute = findAttribute(creatureTarget);
		
		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help");  //It would be unwise to help such a patient.
			return GENERALERROR;
		}

		if (creature->getHAM(CreatureAttribute::MIND) < mindCost) {
			creature->sendSystemMessage("@healing_response:not_enough_mind"); //You do not have enough mind to do that.
			return GENERALERROR;
		}

		float bfScale = 1 - creatureTarget->calculateBFRatio();

		if (tendDamage) {
			if (!creatureTarget->hasDamage(CreatureAttribute::HEALTH) && !creatureTarget->hasDamage(CreatureAttribute::ACTION)) {
				if (creatureTarget == creature)
					creature->sendSystemMessage("@healing_response:healing_response_61"); //You have no damage to heal.
				else if (creatureTarget->isPlayerCreature()) {
					StringIdChatParameter stringId("healing_response", "healing_response_63"); //%NT has no damage to heal.
					stringId.setTT(creatureTarget->getObjectID());
					creature->sendSystemMessage(stringId);
				} else {
					StringBuffer message;
					message << creatureTarget->getDisplayedName() << " has no damage to heal.";
					creature->sendSystemMessage(message.toString());
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
					creature->sendSystemMessage("@healing_response:healing_response_67"); //You have no wounds of that type to heal.
				else if (creatureTarget->isPlayerCreature()){
					creature->sendSystemMessage(creatureTarget->getFirstName() + " has no wounds of that type to heal.");
				} else {
					creature->sendSystemMessage(creatureTarget->getDisplayedName() + " has no wounds of that type to heal.");
				}

				return GENERALERROR;
			}

			int healPower = round(((float)creature->getSkillMod("healing_wound_treatment") / 3.f + 20.f) * bfScale);

			int healedWounds = creatureTarget->healWound(creature, attribute, healPower);

			sendWoundMessage(creature, creatureTarget, attribute, healedWounds);

			if (creatureTarget != creature && healedWounds > 0)
				awardXp(creature, "medical", round(healedWounds * 2.5f));
		} else
			return GENERALERROR;

		if (creature->isPlayerCreature()) {
			PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
			playerManager->sendBattleFatigueMessage(creature, creatureTarget);
		}

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCost, false);
		creature->addWounds(CreatureAttribute::FOCUS, mindWoundCost);
		creature->addWounds(CreatureAttribute::WILLPOWER, mindWoundCost);

		doAnimations(creature, creatureTarget);

		return SUCCESS;
	}

};

#endif /* TENDCOMMAND_H_ */
