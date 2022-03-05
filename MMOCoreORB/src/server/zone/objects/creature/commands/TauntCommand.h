/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TAUNTCOMMAND_H_
#define TAUNTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"

class TauntCommand : public CombatQueueCommand {
public:
	TauntCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> targetObject = creature->getZoneServer()->getObject(target);

		if (targetObject == nullptr || !targetObject->isCreatureObject() || targetObject->isPlayerCreature())
			return INVALIDTARGET;

		CreatureObject* targetCreature = cast<CreatureObject*>(targetObject.get());

		if (targetCreature == nullptr)
			return INVALIDTARGET;

		if (!targetCreature->isAttackableBy(creature))
			return INVALIDTARGET;

		AiAgent* agent = targetCreature->asAiAgent();

		if (agent == nullptr)
			return INVALIDTARGET;

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {
			Locker clocker(targetCreature, creature);

			if (!agent->isTauntable()) {
				creature->sendSystemMessage("@cbt_spam:taunt_fail_single");
				return res;
			}

			ThreatMap* threatMap = targetCreature->getThreatMap();

			if (threatMap != nullptr) {
				int tauntMod = creature->getSkillMod("taunt");
				int levelCombine = targetCreature->getLevel() + creature->getLevel();

				if (System::random(levelCombine + tauntMod) >= System::random(levelCombine - tauntMod)) {
					threatMap->setThreatState(creature, ThreatStates::TAUNTED, (uint64)tauntMod * 1000, (uint64)tauntMod * 1000);
					threatMap->addAggro(creature, tauntMod * 10, (uint64)tauntMod * 1000);

					creature->doCombatAnimation(creature, STRING_HASHCODE("taunt"), 0, 0xFF);
					creature->doAnimation("taunt");

					if (creature->isPlayerCreature())
						creature->sendSystemMessage("@cbt_spam:taunt_success_single");
				} else {
					if (creature->isPlayerCreature())
						creature->sendSystemMessage("@cbt_spam:taunt_fail_single");
				}
			}
		}

		return res;
	}
};

#endif // TAUNTCOMMAND_H_
