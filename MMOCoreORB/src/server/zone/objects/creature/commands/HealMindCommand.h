/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALMINDCOMMAND_H_
#define HEALMINDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/collision/CollisionManager.h"

class HealMindCommand : public QueueCommand {
	float mindCost;
	float mindWoundCost;
	float range;
public:

	HealMindCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		
		mindCost = 250;
		mindWoundCost = 250;
		range = 5;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) const {
		creatureTarget->playEffect("clienteffect/healing_healenhance.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	void sendHealMessage(CreatureObject* creature, CreatureObject* creatureTarget, int mindDamage) const {
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);

		StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

		if (mindDamage > 0) {
			msgBody << mindDamage << " mind";
		} else {
			return; //No damage to heal.
		}

		msgTail << " damage.";

		if (creatureTarget->isPlayerCreature()) {
			msgPlayer << "You heal " << creatureTarget->getFirstName() << " for " << msgBody.toString() << msgTail.toString();
			msgTarget << player->getFirstName() << " heals you for " << msgBody.toString() << msgTail.toString();

			player->sendSystemMessage(msgPlayer.toString());
			creatureTarget->sendSystemMessage(msgTarget.toString());
		} else {
			msgPlayer << "You heal " << creatureTarget->getDisplayedName() << " for " << msgBody.toString() << msgTail.toString();
			player->sendSystemMessage(msgPlayer.toString());
		}
	}

	int calculateWound(int wound, int poolWounds, int poolMax) const {
		int maxWound = poolMax - poolWounds - 1;
		return (Math::max(0,Math::min(maxWound,wound)));
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL) {
			if (!object->isCreatureObject()) {
				TangibleObject* tangibleObject = dynamic_cast<TangibleObject*>(object.get());

				if (tangibleObject != NULL && tangibleObject->isAttackableBy(creature)) {
					object = creature;
				} else {
					creature->sendSystemMessage("@healing:heal_mind_invalid_target"); //Target must be a player or a creature pet in order to heal mind.
					return GENERALERROR;
				}
			}
		} else {
			object = creature;
		}

		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		Locker clocker(creatureTarget, creature);

		CreatureObject* player = cast<CreatureObject*>(creature);

		if (creatureTarget == creature) {
			creature->sendSystemMessage("@healing:no_heal_mind_self"); //You can not heal your own mind.
			return GENERALERROR;
		}		

		if (creatureTarget->isDead() || (creatureTarget->isAiAgent() && !creatureTarget->isPet()) || creatureTarget->isDroidObject()) {
			creature->sendSystemMessage("@healing:heal_mind_invalid_target"); // Target must be a player or a creature pet in order to heal mind.
			return GENERALERROR;
		}

		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help"); //It would be unwise to help such a patient.
			return GENERALERROR;
		}

		if (creature->getHAM(CreatureAttribute::MIND) < mindCost) {
			creature->sendSystemMessage("@healing_response:not_enough_mind"); //You do not have enough mind to do that.
			return GENERALERROR;
		}

		if (creatureTarget->getHAM(CreatureAttribute::MIND) == 0 || !(creatureTarget->hasDamage(CreatureAttribute::MIND))) {
			if (creatureTarget->isPlayerCreature()) {
				StringIdChatParameter stringId("healing", "no_mind_to_heal_target"); //%NT has no mind to heal.
				stringId.setTT(creatureTarget->getObjectID());
				creature->sendSystemMessage(stringId); 
			} else {
				StringBuffer message;
				message << creatureTarget->getDisplayedName() << " has no mind to heal.";
				creature->sendSystemMessage(message.toString());
			}
			return GENERALERROR;
		}

		if(!checkDistance(creature, creatureTarget, range))
			return TOOFAR;

		PlayerManager* playerManager = server->getPlayerManager();

		if (creature != creatureTarget && !CollisionManager::checkLineOfSight(creature, creatureTarget)) {
			creature->sendSystemMessage("@healing:no_line_of_sight"); // You cannot see your target.
			return GENERALERROR;
		}

		float modSkill = (float) creature->getSkillMod("combat_medic_effectiveness");
		int healPower = (int) (System::random(500)+800) * modSkill / 100;

		// Check BF
		healPower = (int) (healPower * creature->calculateBFRatio());

		int healedMind = creatureTarget->healDamage(creature, CreatureAttribute::MIND, healPower);

		if (creature->isPlayerCreature()) {
			playerManager->sendBattleFatigueMessage(creature, creatureTarget);
		}

		sendHealMessage(creature, creatureTarget, healedMind);
		int mindWound = (int) healedMind * .05; // 5% of mind healed in wounds

		creature->addWounds(CreatureAttribute::MIND, mindWound, true, false);
		creature->addWounds(CreatureAttribute::FOCUS, mindWound, true, false);
		creature->addWounds(CreatureAttribute::WILLPOWER, mindWound, true, false);

		creature->addShockWounds(mindWound); // 5% of mind healed in bf

		doAnimations(creature, creatureTarget);

		checkForTef(creature, creatureTarget);

		return SUCCESS;
	}

};

#endif //HEALMINDCOMMAND_H_
