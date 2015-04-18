/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/*
 * LogoutServerCommand.h
 *
 *  Created on: Aug 26, 2011
 *      Author: da
 *  Updated on: Sat Oct  8 11:00:07 EDT 2011 by lordkator
 */

#ifndef LOGOUTSERVERCOMMAND_H_
#define LOGOUTSERVERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/events/LogoutTask.h"

class LogoutServerCommand : public QueueCommand {
public:

	LogoutServerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->isInCombat()) {
			StringIdChatParameter notincombatMsg("client", "you_cannot_log_out_while_in_combat");
			creature->sendSystemMessage(notincombatMsg); // You cannot log out while in combat.

			return INVALIDSTATE;
		}

		Reference<Task*> logoutTask = creature->getPendingTask("logout");

		if (logoutTask != NULL) {
			creature->error("WARNING: LogoutServer command called while logout task already pending!");
			return GENERALERROR;
		}

		// Initiate new LogoutTask
		creature->addPendingTask("logout", new LogoutTask(creature), 5000);

		// Register to see POSTURECHANGE events
		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		creature->registerObserver(ObserverEventType::POSTURECHANGED, playerManager);

		return SUCCESS;
	}
};

#endif /* LOGOUTSERVERCOMMAND_H_ */
