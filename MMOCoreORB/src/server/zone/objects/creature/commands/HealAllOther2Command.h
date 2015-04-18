/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef HEALALLOTHER2COMMAND_H_
#define HEALALLOTHER2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/CombatAction.h"
#include "ForceHealQueueCommand.h"

class HealAllOther2Command : public ForceHealQueueCommand {
protected:

	int healthHealed;
	int actionHealed;
	int mindHealed;

	int heal;

	float speed;
	float range;
	String effectName;
public:
	HealAllOther2Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {

		range = 32;

		healthHealed = 0;
		actionHealed = 0;
		mindHealed = 0;

		heal = 1500;

		speed = 3.0;
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget) const {
		if (!creatureTarget->hasDamage(CreatureAttribute::HEALTH) && !creatureTarget->hasDamage(CreatureAttribute::ACTION) && !creatureTarget->hasDamage(CreatureAttribute::MIND)) {
			creature->sendSystemMessage("@jedi_spam:no_damage_heal_other"); //Your target has no damage of that type to heal.
			return false;
		}

		if (creature->isKnockedDown()) {
			return false;
		}

		if (creature != creatureTarget && !CollisionManager::checkLineOfSight(creature, creatureTarget)) {
			creature->sendSystemMessage("@container_error_message:container18");
			return false;
		}

		return true;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		if (isWearingArmor(creature))
			return NOJEDIARMOR;

		if (!checkForceCost(creature)) {
			creature->sendSystemMessage("@jedi_spam:no_force_power");
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL) {
			if (!object->isCreatureObject()) {
				creature->sendSystemMessage("@jedi_spam:not_this_target"); //This command cannot be used on this target.
				return GENERALERROR;
			}
		} else {
			object = creature;
		}

		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		Locker clocker(creatureTarget, creature);

		if (creatureTarget->isAiAgent() || creatureTarget->isDead() || creatureTarget->isRidingMount() || creatureTarget->isAttackableBy(creature))
			creatureTarget = creature;

		if (creatureTarget == creature) {
			return GENERALERROR;
		}

		if (!canPerformSkill(creature, creatureTarget))
			return GENERALERROR;

		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help");
			return GENERALERROR;
		}

		int healedHealth = creatureTarget->healDamage(creature, CreatureAttribute::HEALTH, heal, true);
		int healedAction = creatureTarget->healDamage(creature, CreatureAttribute::ACTION, heal, true);
		int healedMind = creatureTarget->healDamage(creature, CreatureAttribute::MIND, heal, true);

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		int forceCostDeducted = forceCost;

		forceCostDeducted = MIN(((healedHealth + healedAction + healedMind) / 9.5), forceCost);

		playerObject->setForcePower(playerObject->getForcePower() - forceCostDeducted); // Deduct force.

		sendHealMessage(creature, creatureTarget, healedHealth, healedAction, healedMind);

		doAnimations(creature, creatureTarget);

		checkForTef(creature, creatureTarget);

		return SUCCESS;
	}

};

#endif /* HEALALLOTHER2COMMAND_H_ */
