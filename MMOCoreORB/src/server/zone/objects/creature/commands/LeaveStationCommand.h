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
		auto spaceZone = creature->getSpaceZone();
		if (spaceZone == nullptr) {
			return GENERALERROR;
		}

		auto station = creature->getParent().get();
		if (station == nullptr) {
			return GENERALERROR;
		}

		auto parent = station->getParent().get();
		if (parent == nullptr) {
			return GENERALERROR;
		}

		Locker clock(parent, creature);
		creature->destroyObjectFromWorld(false);
		creature->setMovementCounter(0);
		creature->clearSpaceStates();

		if (parent->transferObject(creature, -1, true)) {
			creature->setState(CreatureState::SHIPINTERIOR);
			creature->sendTo(creature, true);
			return SUCCESS;
		}

		return GENERALERROR;
	}
};

#endif //LEAVESTATION_H_
