/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef WARNINGSHOTCOMMAND_H_
#define WARNINGSHOTCOMMAND_H_

#include "CombatQueueCommand.h"

class WarningShotCommand : public CombatQueueCommand {
public:
	WarningShotCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ZoneServer* zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> targetObject = zoneServer->getObject(target);

		if (targetObject == nullptr)
			return GENERALERROR;

		if (!targetObject->isCreatureObject()) {
			StringIdChatParameter param;
			param.setStringId("@error_message:target_not_creature");
			creature->sendSystemMessage(param);
			return GENERALERROR;
		}

		CreatureObject* tarCreo = targetObject->asCreatureObject();

		if (tarCreo == nullptr || !tarCreo->isAiAgent()) {
			return GENERALERROR;
		}

		AiAgent* agent = tarCreo->asAiAgent();

		if (agent == nullptr)
			return GENERALERROR;

		int result = doCombatAction(creature, target);

		if (result == SUCCESS) {
			int playerLevel = creature->getLevel() * 2;
			int targetLevel = tarCreo->getLevel();
			int failCalc = (targetLevel - playerLevel + System::random(250));

			if (agent->getCreatureBitmask() & ObjectFlag::AGGRESSIVE)
				failCalc += 75;

			if (failCalc < 300) {
				Locker alock(agent, creature);

				float aggroMod = 1.f;

				if (agent->peekBlackboard("aggroMod"))
					aggroMod = agent->readBlackboard("aggroMod").get<float>();

				int radius = agent->getAggroRadius();

				if (radius == 0)
					radius = AiAgent::DEFAULTAGGRORADIUS;

				Time* fleeDelay = agent->getFleeDelay();

				if (fleeDelay != nullptr) {
					fleeDelay->updateToCurrentTime();
					fleeDelay->addMiliTime(10 * 1000);
				}

				float distance = 100.f - radius * aggroMod;

				agent->writeBlackboard("fleeRange", distance);
				agent->runAway(creature, distance, false);

				agent->showFlyText("npc_reaction/flytext", "afraid", 0xFF, 0, 0);
			}
		}

		return result;
	}
};

#endif // WARNINGSHOTCOMMAND_H_
