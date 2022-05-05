/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef JEDIMINDTRICKCOMMAND_H_
#define JEDIMINDTRICKCOMMAND_H_

#include "ForcePowersQueueCommand.h"
#include "server/zone/objects/creature/events/JediMindTrickRemovalTask.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/intangible/PetControlDevice.h"

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

		if (agent == nullptr || agent->isDroid() || agent->isVehicleType())
			return GENERALERROR;

		CreatureObject* owner = agent->getLinkedCreature().get();

		if (owner == nullptr)
			return GENERALERROR;

		auto creatureTemplate = agent->getCreatureTemplate();

		if (creatureTemplate == nullptr)
			return GENERALERROR;

		int result = doCombatAction(creature, target);

		if (result == SUCCESS) {
			int playerLevel = creature->getLevel();
			int targetLevel = tarCreo->getLevel();
			int failCalc = (targetLevel - playerLevel + System::random(100));

			StringIdChatParameter param;

			if (failCalc < 75) {
				Locker alock(agent, creature);

				ManagedReference<PetControlDevice*> controlDevice = agent->getControlDevice().get().castTo<PetControlDevice*>();

				if (controlDevice != nullptr && controlDevice->getPetType() == PetManager::FACTIONPET) {
					agent->removeCreatureFlag(CreatureFlag::FACTION_PET);
				} else {
					agent->removeCreatureFlag(CreatureFlag::PET);
				}

				agent->setMindTricked(true);
				agent->setCreatureLink(nullptr);

				agent->setFaction(creatureTemplate->getFaction().hashCode());
				agent->setFactionStatus(FactionStatus::ONLEAVE);
				agent->setPvpStatusBitmask(creatureTemplate->getPvpBitmask());

				agent->setFollowObject(nullptr);
				agent->storeFollowObject();
				agent->setMovementState(AiAgent::PATROLLING);
				agent->setAITemplate();

				CombatManager::instance()->forcePeace(agent);

				int time = 10 + System::random(25);
				time *= 1000;

				Reference<Task*> mindTrickTask = new JediMindTrickRemovalTask(agent, owner);
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
