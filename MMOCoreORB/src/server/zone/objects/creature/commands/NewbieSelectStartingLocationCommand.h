/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NEWBIESELECTSTARTINGLOCATIONCOMMAND_H_
#define NEWBIESELECTSTARTINGLOCATIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/player/StartingLocation.h"
#include "server/zone/objects/player/PlayerObject.h"

class NewbieSelectStartingLocationCommand : public QueueCommand {
public:

	NewbieSelectStartingLocationCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		CreatureObject* player = cast<CreatureObject*>(creature);

		Zone* zone = player->getZone();

		if (zone == NULL || zone->getZoneName() != "tutorial")
			return GENERALERROR;

		ManagedReference<SceneObject*> cell = creature->getParent().get();

		if (cell == NULL)
			return GENERALERROR;

		ManagedReference<SceneObject*> tutorial = cell->getParent().get();

		String city = arguments.toString();

		StartingLocation* startingLocation = server->getPlayerManager()->getStartingLocation(city);

		if (startingLocation == NULL) {
			player->info("Attempted to start at invalid starting location: " + city + ".", true);
			return GENERALERROR;
		}

		zone = server->getZoneServer()->getZone(startingLocation->getZoneName());

		if (zone == NULL) {
			player->sendSystemMessage("This starting location is disabled, please select a different one");
			return GENERALERROR;
		}

		player->switchZone(startingLocation->getZoneName(), startingLocation->getX(), startingLocation->getZ(), startingLocation->getY(), startingLocation->getCell());
		player->setDirection(startingLocation->getHeading());

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost != NULL) {
			ghost->setCloningFacility(NULL);
			if (ghost->getBankLocation() != "")
				ghost->setBankLocation(startingLocation->getZoneName());
		}


		if (tutorial != NULL)
			StructureManager::instance()->destroyStructure(tutorial->asBuildingObject(), false);

		return SUCCESS;
	}

};

#endif //NEWBIESELECTSTARTINGLOCATIONCOMMAND_H_

