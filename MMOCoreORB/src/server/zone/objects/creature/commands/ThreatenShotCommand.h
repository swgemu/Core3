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

			if (agent->getCreatureBitmask() & CreatureFlag::AGGRESSIVE)
				failCalc += 75;

			if (failCalc < 300) {
				Locker alock(agent, creature);
				ThreatMap* threatMap = agent->getThreatMap();

				if (threatMap != nullptr) {
					threatMap->removeAll();
				}

				agent->notifyObservers(ObserverEventType::FLEEING, creature);
				agent->setFollowState(AiAgent::FLEEING);

				Vector3 agentPosition = agent->getWorldPosition();
				Vector3 creaturePosition = creature->getWorldPosition();
				Vector3 runTrajectory((creaturePosition.getX() + System::random(20)) - (agentPosition.getX() + System::random(20)), (creaturePosition.getY() + System::random(20)) - (agentPosition.getY() + System::random(20)), 0);

				runTrajectory = runTrajectory * (10.f / runTrajectory.length());
				runTrajectory += agent->getPosition();

				agent->setFleeRange(15.f);
				agent->setNextPosition(runTrajectory.getX(), agent->getWorldZ(runTrajectory), runTrajectory.getY(), agent->getParent().get().castTo<CellObject*>());
			}
		}

		return result;
	}
};

#endif //THREATENSHOTCOMMAND_H_
