/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef THREATENSHOTCOMMAND_H_
#define THREATENSHOTCOMMAND_H_

class ThreatenShotCommand : public CombatQueueCommand {
public:

	ThreatenShotCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {

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

				agent->writeBlackboard("fleeRange", 15.f);
				agent->runAway(creature, 15.f, true);
			}
		}

		return result;
	}
};

#endif //THREATENSHOTCOMMAND_H_
