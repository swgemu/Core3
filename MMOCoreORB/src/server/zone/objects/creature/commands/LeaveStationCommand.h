/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LEAVESTATION_H_
#define LEAVESTATION_H_

#include "QueueCommand.h"
#include "server/zone/objects/cell/CellObject.h"

class LeaveStationCommand : public QueueCommand {
public:

	LeaveStationCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!creature->isInShipStation()) {
			return GENERALERROR;
		}

		SceneObject* parent = creature->getParent().get();

		if (parent == nullptr) {
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> cellParent = parent->getParent().get();

		if (cellParent == nullptr || !cellParent->isCellObject()) {
			return GENERALERROR;
		}

		CellObject* cell = cast<CellObject*>(cellParent.get());

		if (cell == nullptr) {
			return GENERALERROR;
		}

		// Clear Station State
		creature->clearSpaceStates();

		// Set Ship Interior State
		creature->setState(CreatureState::SHIPINTERIOR);

		if (parent->isPilotChair() || parent->isOperationsChair()) {
			creature->setPosition(parent->getPositionX(), parent->getPositionZ(), parent->getPositionY());
		}

		// Reset player movement counter
		creature->setMovementCounter(0);

		if (!cell->transferObject(creature, -1, true)) {
			return GENERALERROR;
		}

		return SUCCESS;
	}
};

#endif //LEAVESTATION_H_
