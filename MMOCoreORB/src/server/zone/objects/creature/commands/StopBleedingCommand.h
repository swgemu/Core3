/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STOPBLEEDINGCOMMAND_H_
#define STOPBLEEDINGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/CombatAction.h"
#include "QueueCommand.h"

class StopBleedingCommand : public QueueCommand {
public:

	StopBleedingCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) const {
		if (creatureTarget == creature)
			creature->playEffect("clienteffect/pl_force_healing.cef", "");
		 else
			creature->doCombatAnimation(creatureTarget,STRING_HASHCODE("force_healing_1"),0,0xFF);
	}

	void sendCureMessage(CreatureObject* object, CreatureObject* target) const {
		if (!object->isPlayerCreature())
			return;

		if (!target->isPlayerCreature())
			return;

		CreatureObject* creature = cast<CreatureObject*>( object);
		CreatureObject* creatureTarget = cast<CreatureObject*>( target);
		StringBuffer msgTarget, msgPlayer;
			msgPlayer << creatureTarget->getFirstName() << " bleeding has slightly decreased.";
//			msgTarget << creature->getFirstName() << " bleeding has slightly decreased.";

		if (creature != creatureTarget)
			creature->sendSystemMessage(msgPlayer.toString());
//			creatureTarget->sendSystemMessage(msgTarget.toString());
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget) const {
		if (!creatureTarget->isBleeding()) {
			if (creature == creatureTarget)
				creature->sendSystemMessage("@healing_response:healing_response_78"); //You are not bleeding.
			else {
				StringIdChatParameter stringId("healing_response", "healing_response_80");
				stringId.setTT(creatureTarget->getObjectID());
				creature->sendSystemMessage(stringId); //%NT is not bleeding.
			}
			return false;
		}

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject->getForcePower() <= 75) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //You do not have enough force to do that.
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
				TangibleObject* tangibleObject = dynamic_cast<TangibleObject*>(object.get());

				if (tangibleObject != NULL && tangibleObject->isAttackableBy(creature)) {
					object = creature;
				} else {
					creature->sendSystemMessage("@jedi_spam:not_this_target"); //This command cannot be used on this target.
					return GENERALERROR;
				}
			}
		} else {
			object = creature;
		}

		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		Locker clocker(creatureTarget, creature);

		if (creatureTarget->isAiAgent() || creatureTarget->isDead() || creatureTarget->isRidingMount() || creatureTarget->isAttackableBy(creature))
			creatureTarget = creature;

		int range = 32;

		if (!creature->isInRange(creatureTarget, range + creatureTarget->getTemplateRadius() + creature->getTemplateRadius()))
			return TOOFAR;

		if (!canPerformSkill(creature, creatureTarget))
			return GENERALERROR;

		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help");
			return GENERALERROR;
		}

		PlayerObject* playerObject = creature->getPlayerObject().get();
		playerObject->setForcePower(playerObject->getForcePower() - 75); // Static amount.

		creatureTarget->healDot(CreatureState::BLEEDING, 30);

		sendCureMessage(creature, creatureTarget);

		doAnimations(creature, creatureTarget);

		checkForTef(creature, creatureTarget);

		return SUCCESS;
	}

};

#endif //STOPBLEEDINGCOMMAND_H_
