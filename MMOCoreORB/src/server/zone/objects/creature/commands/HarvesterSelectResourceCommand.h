/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HARVESTERSELECTRESOURCECOMMAND_H_
#define HARVESTERSELECTRESOURCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"

class HarvesterSelectResourceCommand : public QueueCommand {
public:

	HarvesterSelectResourceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*>(creature);

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == nullptr || !object->isHarvesterObject())
			return GENERALERROR;

		HarvesterObject* harvester = cast<HarvesterObject*>(object.get());

		uint64 spawnId = Long::valueOf(arguments.toString());

		Locker clocker(harvester, player);

		if (!harvester->isOnAdminList(player) || harvester->isInRange(player, 20))
			return GENERALERROR;

		harvester->selectResource(spawnId, player);

		return SUCCESS;
	}

};

#endif //HARVESTERSELECTRESOURCECOMMAND_H_
