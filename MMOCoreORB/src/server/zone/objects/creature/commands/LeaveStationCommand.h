/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LEAVESTATION_H_
#define LEAVESTATION_H_

#include "QueueCommand.h"

class LeaveStationCommand : public QueueCommand {
public:

	LeaveStationCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!creature->isInShipStation())
			return GENERALERROR;

		ManagedReference<SceneObject*> cellParent = creature->getParentRecursively(SceneObjectType::CELLOBJECT);

		if (cellParent == nullptr)
			return GENERALERROR;

		if (!cellParent->transferObject(creature, -1, true)) {
			return GENERALERROR;
		}

		// Clear their state from the station they were in
		creature->clearSpaceStates();

		// Must have proper interior state to be able to move properly in the ship
		creature->setState(CreatureState::SHIPINTERIOR);

		return SUCCESS;
	}
};

#endif //LEAVESTATION_H_
