/*
 * MakeMasterLooterCommand.h
 *
 *  Created on: Aug 26, 2011
 *      Author: da
 */

#ifndef MAKEMASTERLOOTERCOMMAND_H_
#define MAKEMASTERLOOTERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class MakeMasterLooterCommand : public QueueCommand {
public:

	MakeMasterLooterCommand(const String& name, ZoneProcessServer* server)
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




#endif /* MAKEMASTERLOOTERCOMMAND_H_ */
