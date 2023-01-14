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
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		SceneObject* rootParent = creature->getRootParent();

		if (rootParent == nullptr)
			return GENERALERROR;

		Locker clock(rootParent, creature);

		rootParent->transferObject(creature, -1, true);

		//TODO: MODIFY? - H
		if (creature->hasState(CreatureState::PILOTINGPOBSHIP))
			creature->clearState(CreatureState::PILOTINGPOBSHIP);
		if (creature->hasState(CreatureState::PILOTINGSHIP))
			creature->clearState(CreatureState::PILOTINGSHIP);
		if (creature->hasState(CreatureState::SHIPOPERATIONS))
			creature->clearState(CreatureState::SHIPOPERATIONS);
		if (creature->hasState(CreatureState::SHIPOPERATIONS))
			creature->clearState(CreatureState::SHIPOPERATIONS);
		if (creature->hasState(CreatureState::SHIPGUNNER))
			creature->clearState(CreatureState::SHIPGUNNER);

		return SUCCESS;
	}
};

#endif //LEAVESTATION_H_
