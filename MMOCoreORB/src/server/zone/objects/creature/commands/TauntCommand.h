/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TAUNTCOMMAND_H_
#define TAUNTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class TauntCommand : public CombatQueueCommand {
public:

	TauntCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> targetObject = creature->getZoneServer()->getObject(target);

		if (targetObject == NULL || !targetObject->isCreatureObject() || targetObject->isPlayerCreature())
			return INVALIDTARGET;

		CreatureObject* targetCreature = cast<CreatureObject*>(targetObject.get());

		if (targetCreature == NULL)
			return INVALIDTARGET;

		if (!targetCreature->isAttackableBy(creature))
			return INVALIDTARGET;

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {
			Locker clocker(targetCreature, creature);

			targetCreature->getThreatMap()->addAggro(creature, creature->getSkillMod("taunt") * 10, 0);
			targetCreature->getThreatMap()->setThreatState(creature, ThreatStates::TAUNTED,(uint64)creature->getSkillMod("taunt") / 10, (uint64)creature->getSkillMod("taunt") / 10);
			//creature->doCombatAnimation(creature,STRING_HASHCODE("taunt"),0,0xFF);
			creature->doAnimation("taunt");

			if (creature->isPlayerCreature())
				creature->sendSystemMessage("@cbt_spam:taunt_success_single");

		} else {

			if (creature->isPlayerCreature())
				creature->sendSystemMessage("@cbt_spam:taunt_fail_single");
		}

		return res;
	}

	void sendAttackCombatSpam(TangibleObject* attacker, TangibleObject* defender, int attackResult, int damage, const CreatureAttackData& data) const {
		if (attacker == NULL)
			return;

		Zone* zone = attacker->getZone();
		if (zone == NULL)
			return;

		String stringName = data.getCombatSpam();
		byte color = 1;

		switch (attackResult) {
		case CombatManager::HIT:
			stringName += "_success";
			break;
		case CombatManager::MISS:
		case CombatManager::DODGE:
		case CombatManager::COUNTER:
		case CombatManager::BLOCK:
		case CombatManager::RICOCHET:
			stringName += "_fail";
			color = 0;
			break;
		default:
			break;
		}

		CombatManager::instance()->broadcastCombatSpam(attacker, NULL, NULL, damage, "cbt_spam", stringName, color);

	}

};

#endif //TAUNTCOMMAND_H_
