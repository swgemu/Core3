/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef HEALMINDWOUNDOTHER1COMMAND_H_
#define HEALMINDWOUNDOTHER1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "QueueCommand.h"

class HealMindWoundOther1Command : public QueueCommand {
protected:
	int forceCost;

	int mindWoundHealed;
	int focusWoundHealed;
	int willpowerWoundHealed;
	int heal;

	float speed;
	float range;
	String effectName;
public:
	HealMindWoundOther1Command(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		forceCost = 0;

		range = 32;

		mindWoundHealed = 0;
		focusWoundHealed = 0;
		willpowerWoundHealed = 0;

		heal = 150;

		speed = 3.0;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) const {
		if (creatureTarget == creature)
			creature->playEffect("clienteffect/pl_force_healing.cef", "");
		 else
			creature->doCombatAnimation(creatureTarget,String("force_healing_1").hashCode(),0,0xFF);
	}

	void sendWoundMessage(CreatureObject* object, CreatureObject* target, int mindWound, int focusWound, int willpowerWound) const {
		if (!object->isPlayerCreature())
			return;

		if (!target->isPlayerCreature())
			return;

		CreatureObject* creature = cast<CreatureObject*>( object);
		CreatureObject* creatureTarget = cast<CreatureObject*>( target);

		StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

		if (mindWound > 0 && focusWound > 0 && willpowerWound > 0) {
			msgBody << mindWound << " mind, " << focusWound << " focus, and "  << willpowerWound << " willpower";
		} else if (mindWound > 0) {
			msgBody << mindWound << " mind";
		} else if (focusWound > 0) {
			msgBody << focusWound << " focus";
		} else if (willpowerWound > 0) {
			msgBody << willpowerWound << " willpower";
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
		if (!creatureTarget->getWounds(CreatureAttribute::MIND) && !creatureTarget->getWounds(CreatureAttribute::FOCUS) && !creatureTarget->getWounds(CreatureAttribute::WILLPOWER)) {
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

		uint32 healedMindWound = creatureTarget->healWound(creature, CreatureAttribute::MIND, heal, true);
		uint32 healedFocusWound = creatureTarget->healWound(creature, CreatureAttribute::FOCUS, heal, true);
		uint32 healedWillpowerWound = creatureTarget->healWound(creature, CreatureAttribute::WILLPOWER, heal, true);

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject->getForcePower() <= 85) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //You do not have enough force to do that.
			return GENERALERROR;
		}

		float forceCost = MIN(((healedMindWound + healedFocusWound + healedWillpowerWound) / 15), 85);

		playerObject->setForcePower(playerObject->getForcePower() - forceCost); // Deduct force.

		sendWoundMessage(creature, creatureTarget, healedMindWound, healedFocusWound, healedWillpowerWound);

		doAnimations(creature, creatureTarget);

		checkForTef(creature, creatureTarget);

		return SUCCESS;
	}

};

#endif /* HEALMINDWOUNDOTHER1COMMAND_H_ */
