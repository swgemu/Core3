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
		if (!creature->isInShipStation())
			return GENERALERROR;

		SceneObject* parent = creature->getParent().get();

		if (parent == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> cellParent = parent->getParent().get();

		if (cellParent == nullptr || !cellParent->isCellObject())
			return GENERALERROR;

		CellObject* cell = cast<CellObject*>(cellParent.get());

		if (cell == nullptr)
			return GENERALERROR;

		Vector3 position = parent->getPosition();

		creature->setPosition(position.getX(), position.getZ(), position.getY());

		if (!cell->transferObject(creature, -1, true)) {
			return GENERALERROR;
		}

		// Clear station state
		if (creature->hasState(CreatureState::PILOTINGPOBSHIP))
			creature->clearState(CreatureState::PILOTINGPOBSHIP);
		else if (creature->hasState(CreatureState::SHIPOPERATIONS))
			creature->clearState(CreatureState::SHIPOPERATIONS);
		else if (creature->hasState(CreatureState::SHIPGUNNER))
			creature->clearState(CreatureState::SHIPGUNNER);
		else if (creature->hasState(CreatureState::SHIPOPERATIONS))
			creature->clearState(CreatureState::SHIPOPERATIONS);

		return SUCCESS;
	}
};

#endif //LEAVESTATION_H_
