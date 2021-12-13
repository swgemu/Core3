/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ANIMALATTACKCOMMAND_H_
#define ANIMALATTACKCOMMAND_H_

#include "ForcePowersQueueCommand.h"

class AnimalAttackCommand : public ForcePowersQueueCommand {
public:

	AnimalAttackCommand(const String& name, ZoneProcessServer* server)
		: ForcePowersQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		ZoneServer* zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> targetObject = zoneServer->getObject(target);

		StringIdChatParameter param;
		param.setStringId("@error_message:target_not_creature");

		if (targetObject == nullptr)
			return GENERALERROR;

		if (!targetObject->isCreatureObject()) {
			creature->sendSystemMessage(param);
			return GENERALERROR;
		}

		// Command Target - Creature that will attack look players main defender
		CreatureObject* tarCreo = targetObject->asCreatureObject();

		if (tarCreo == nullptr || !tarCreo->isAiAgent() || tarCreo->isNonPlayerCreatureObject()) {
			creature->sendSystemMessage(param);
			return GENERALERROR;
		}

		// Target to be attacked by the command target
		SceneObject* attackedScno = creature->getMainDefender();

		if (attackedScno == nullptr || !attackedScno->isCreatureObject())
			return GENERALERROR;

		CreatureObject* attackedCreo = attackedScno->asCreatureObject();
		AiAgent* agent = tarCreo->asAiAgent();

		if (agent == nullptr || attackedCreo == nullptr)
			return GENERALERROR;

		int result = doCombatAction(creature, target);

		if (result == SUCCESS) {
			int failChance = System::random(100);

			if (failChance < 75) {
				Locker alock(agent, creature);

				agent->setDefender(attackedScno);

				param.setStringId("@jedi_spam:animal_attack_success");
			} else {
				param.setStringId("@jedi_spam:animal_attack_fail");
			}

			creature->sendSystemMessage(param);
		}

		return result;
	}
};

#endif //ANIMALATTACKCOMMAND_H_
