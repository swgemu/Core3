/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FINDMYTRAINERCOMMAND_H_
#define FINDMYTRAINERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class FindMyTrainerCommand : public QueueCommand {
public:

	FindMyTrainerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		if (ghost->getJediState() < 2)
			return GENERALERROR;


		String planet = ghost->getTrainerZoneName();
		uint32 planetCRC = planet.hashCode();

		Vector3 coords = ghost->getTrainerCoordinates();

		String name = "@jedi_spam:trainer_waypoint_name";

		ManagedReference<WaypointObject*> obj = ( server->getZoneServer()->createObject(0xc456e788, 1)).castTo<WaypointObject*>();
		obj->setPlanetCRC(planetCRC);
		obj->setPosition(coords.getX(), 0, coords.getY());
		obj->setCustomObjectName(name, false);

		ghost->addWaypoint(obj, true, true);

		creature->sendSystemMessage("@jedi_spam:waypoint_created_to_trainer");

		return SUCCESS;
	}

};

#endif //FINDMYTRAINERCOMMAND_H_
