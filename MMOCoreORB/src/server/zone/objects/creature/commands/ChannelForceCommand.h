/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHANNELFORCECOMMAND_H_
#define CHANNELFORCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/events/ChannelForceRegenTask.h"

class ChannelForceCommand : public QueueCommand {
public:

	ChannelForceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}


		// Bonus is inbetween 200-300.
		int rand = System::random(10);
		int forceBonus = 200 + (rand * 10); // Needs to be divisible by amount of ticks.

		if ((creature->getMaxHAM(CreatureAttribute::HEALTH) <= forceBonus) || (creature->getMaxHAM(CreatureAttribute::ACTION) <= forceBonus) || (creature->getMaxHAM(CreatureAttribute::MIND) <= forceBonus)) {
			creature->sendSystemMessage("@jedi_spam:channel_ham_too_low"); // Your body is too weakened to perform that action.
			return GENERALERROR;
		}

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject == NULL)
			return GENERALERROR;

		// Do not execute if the player's force bar is full.
		if (playerObject->getForcePower() >= playerObject->getForcePowerMax())
			return GENERALERROR;

		// To keep it from going over max...
		if ((playerObject->getForcePowerMax() - playerObject->getForcePower()) < forceBonus)
			forceBonus = (playerObject->getForcePowerMax() - playerObject->getForcePower());


		// Give Force, and subtract HAM.

		playerObject->setForcePower(playerObject->getForcePower() + forceBonus);

		int maxHealth = creature->getMaxHAM(CreatureAttribute::HEALTH);
		int maxAction = creature->getMaxHAM(CreatureAttribute::ACTION);
		int maxMind = creature->getMaxHAM(CreatureAttribute::MIND);

		creature->setMaxHAM(CreatureAttribute::HEALTH, maxHealth - forceBonus, true);
		creature->setMaxHAM(CreatureAttribute::ACTION, maxAction - forceBonus, true);
		creature->setMaxHAM(CreatureAttribute::MIND, maxMind - forceBonus, true);


		// Setup task.
		Reference<ChannelForceRegenTask*> cfTask = new ChannelForceRegenTask(creature, forceBonus);
		creature->addPendingTask("channelForceRegenTask", cfTask, 6000);


		return SUCCESS;
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * 3.0;
	}

};

#endif //CHANNELFORCECOMMAND_H_
