/*
 * LogoutServerCommand.h
 *
 *  Created on: Aug 26, 2011
 *      Author: da
 */

#ifndef LOGOUTSERVERCOMMAND_H_
#define LOGOUTSERVERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class LogoutServerCommand : public QueueCommand {
public:

	LogoutServerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif /* LOGOUTSERVERCOMMAND_H_ */
