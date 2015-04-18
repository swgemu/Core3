/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REGAINCONSCIOUSNESSCOMMAND_H_
#define REGAINCONSCIOUSNESSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/events/RegainConsciousnessRegenTask.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"

class RegainConsciousnessCommand : public QueueCommand {
public:

	RegainConsciousnessCommand(const String& name, ZoneProcessServer* server)
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

		// Force cost of skill.
		int forceCost = 1000;


		//Check for and deduct Force cost.

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();


		if (playerObject->getForcePower() <= forceCost) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to peform that action.
			return GENERALERROR;
		}

		// They should be dead...
		if (creature->isDead()){
			// Revive user by setting posture to standing.
			creature->setPosture(CreaturePosture::UPRIGHT);

			// Unsure if this was used in live?
			 creature->playEffect("clienteffect/pl_force_regain_consciousness_self.cef", "");

			// Do the 1 minute of grogginess suffering (no actions can be taken.)
			// TODO: Unsure how to do this.

			playerObject->setForcePower(playerObject->getForcePower() - forceCost);

			// Cut Force Regen in Half for 30 Minutes.

			playerObject->setForcePowerRegen(playerObject->getForcePowerRegen() / 2);

			// Jedi experience loss.
			PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
			playerManager->awardExperience(creature, "jedi_general", -50000, true);

			Reference<RegainConsciousnessRegenTask*> rcTask = new RegainConsciousnessRegenTask(creature, playerObject);
			creature->addPendingTask("regainConsciousnessRegenTask", rcTask, (1800 * 1000));

			return SUCCESS;
		}

		return GENERALERROR;

	}

};

#endif //REGAINCONSCIOUSNESSCOMMAND_H_
