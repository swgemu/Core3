/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef HEALACTIONWOUNDOTHER1COMMAND_H_
#define HEALACTIONWOUNDOTHER1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "QueueCommand.h"

class HealActionWoundOther1Command : public QueueCommand {
protected:
	int forceCost;

	int actionWoundHealed;
	int quicknessWoundHealed;
	int staminaWoundHealed;
	int heal;

	float speed;
	float range;
	String effectName;
public:
	HealActionWoundOther1Command(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		forceCost = 0;

		range = 32;

		actionWoundHealed = 0;
		quicknessWoundHealed = 0;
		staminaWoundHealed = 0;

		heal = 150;

		speed = 3.0;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) const {
		if (creatureTarget == creature)
			creature->playEffect("clienteffect/pl_force_healing.cef", "");
		else
			creature->doCombatAnimation(creatureTarget,String("force_healing_1").hashCode(),0,0xFF);
	}

	void sendWoundMessage(CreatureObject* object, CreatureObject* target, int actionWound, int quicknessWound, int staminaWound) const {
		if (!object->isPlayerCreature())
			return;

		if (!target->isPlayerCreature())
			return;

		CreatureObject* creature = cast<CreatureObject*>( object);
		CreatureObject* creatureTarget = cast<CreatureObject*>( target);

		StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

		if (actionWound > 0 && quicknessWound > 0 && staminaWound > 0) {
			msgBody << actionWound << " action, " << quicknessWound << " quickness, and "  << staminaWound << " stamina";
		} else if (actionWound > 0) {
			msgBody << actionWound << " action";
		} else if (quicknessWound > 0) {
			msgBody << quicknessWound << " quickness";
		} else if (staminaWound > 0) {
			msgBody << staminaWound << " stamina";
		} else {
			creature->sendSystemMessage("Your target has no wounds of that type to heal."); //%NT has no wounds of that type to heal.
			return;
		}

		msgTail << " wounds.";

		msgPlayer << "You heal " << creatureTarget->getFirstName() << " for " << msgBody.toString() << msgTail.toString();
		msgTarget << creature->getFirstName() << " heals you for " << msgBody.toString() << msgTail.toString();

		creature->sendSystemMessage(msgPlayer.toString());
		creatureTarget->sendSystemMessage(msgTarget.toString());
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget) const {
		if (!creatureTarget->getWounds(CreatureAttribute::ACTION) && !creatureTarget->getWounds(CreatureAttribute::QUICKNESS) && !creatureTarget->getWounds(CreatureAttribute::STAMINA)) {
			creature->sendSystemMessage("Your target has no wounds of that type to heal."); //%NT has no wounds of that type to heal.
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

		uint32 healedActionWound = creatureTarget->healWound(creature, CreatureAttribute::ACTION, heal, true);
		uint32 healedQuicknessWound = creatureTarget->healWound(creature, CreatureAttribute::QUICKNESS, heal, true);
		uint32 healedStaminaWound = creatureTarget->healWound(creature, CreatureAttribute::STAMINA, heal, true);

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject->getForcePower() <= 85) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //You do not have enough force to do that.
			return GENERALERROR;
		}

		float forceCost = MIN(((healedActionWound + healedQuicknessWound + healedStaminaWound) / 15), 85);

		playerObject->setForcePower(playerObject->getForcePower() - forceCost); // Deduct force.

		sendWoundMessage(creature, creatureTarget, healedActionWound, healedQuicknessWound, healedStaminaWound);

		doAnimations(creature, creatureTarget);

		checkForTef(creature, creatureTarget);

		return SUCCESS;
	}

};

#endif /* HEALACTIONWOUNDOTHER1COMMAND_H_ */
