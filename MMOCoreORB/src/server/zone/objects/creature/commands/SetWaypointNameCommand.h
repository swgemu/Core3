/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETWAYPOINTNAMECOMMAND_H_
#define SETWAYPOINTNAMECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetWaypointNameCommand : public QueueCommand {
public:

	SetWaypointNameCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* playerCreature = cast<CreatureObject*>( creature);
		PlayerObject* ghost = playerCreature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL || !object->isWaypointObject())
			return INVALIDTARGET;

		if (arguments.isEmpty() || arguments.length() > 150)
			return GENERALERROR;

		WaypointObject* waypoint = cast<WaypointObject*>( object.get());

		if (!ghost->hasWaypoint(waypoint->getObjectID()))
			return GENERALERROR;

		Locker clocker(waypoint, creature);

		if (waypoint->getSpecialTypeID() != 0)
			waypoint->setSpecialTypeID(0);

		waypoint->setCustomObjectName(arguments, false);

		ghost->updateWaypoint(waypoint->getObjectID());

		return SUCCESS;
	}

};

#endif //SETWAYPOINTNAMECOMMAND_H_
