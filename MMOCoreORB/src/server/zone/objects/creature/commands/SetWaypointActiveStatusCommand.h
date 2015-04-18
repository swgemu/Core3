/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETWAYPOINTACTIVESTATUSCOMMAND_H_
#define SETWAYPOINTACTIVESTATUSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetWaypointActiveStatusCommand : public QueueCommand {
public:

	SetWaypointActiveStatusCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> wp = server->getZoneServer()->getObject(target);

		if (wp == NULL || !wp->isWaypointObject())
			return INVALIDPARAMETERS;

		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		WaypointObject* waypoint = cast<WaypointObject*>( wp.get());

		if (!ghost->hasWaypoint(waypoint->getObjectID()))
			return GENERALERROR;

		waypoint->toggleStatus();

		ghost->updateWaypoint(waypoint->getObjectID());

		return SUCCESS;
	}

};

#endif //SETWAYPOINTACTIVESTATUSCOMMAND_H_
