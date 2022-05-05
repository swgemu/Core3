/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef JEDIMINDTRICKCOMMAND_H_
#define JEDIMINDTRICKCOMMAND_H_

#include "ForcePowersQueueCommand.h"
#include "server/zone/objects/creature/events/JediMindTrickTask.h"

class JediMindTrickCommand : public ForcePowersQueueCommand {
public:

	JediMindTrickCommand(const String& name, ZoneProcessServer* server) : ForcePowersQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature))
			return NOJEDIARMOR;

		ZoneServer* zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> targetObject = zoneServer->getObject(target);

		if (targetObject == nullptr || !targetObject->isCreatureObject())
			return GENERALERROR;

		CreatureObject* tarCreo = targetObject->asCreatureObject();

		if (tarCreo == nullptr || !tarCreo->isAiAgent() || !tarCreo->isPet()) {
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

			StringIdChatParameter param;

			if (failCalc < 300) {
				Locker alock(agent, creature);

				agent->setCreatureBitmask(agent->getCreatureBitmask() & ~CreatureFlag::PET);
				agent->setFaction(Factions::FACTIONNEUTRAL);

				agent->setAITemplate();
				agent->broadcastPvpStatusBitmask();

				int time = 10 + System::random(15);
				time *= 1000;

				printf("Scheduling task to clear for %i\n", time);

				Reference<Task*> mindTrickTask = new JediMindTrickTask(agent);
				mindTrickTask->schedule(time);

				param.setStringId("@jedi_spam:mind_trick_success");
			} else {
				param.setStringId("@jedi_spam:mind_trick_fail");
			}
			creature->sendSystemMessage(param);
		}

		return result;
	}

};

#endif //JEDIMINDTRICKCOMMAND_H_
