/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHOWDANCEVISUALSCOMMAND_H_
#define SHOWDANCEVISUALSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ShowDanceVisualsCommand : public QueueCommand {
public:

	ShowDanceVisualsCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //SHOWDANCEVISUALSCOMMAND_H_
