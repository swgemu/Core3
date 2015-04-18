/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HARVESTERSELECTRESOURCECOMMAND_H_
#define HARVESTERSELECTRESOURCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"
#include "server/zone/packets/harvester/HarvesterResourceDataMessage.h"


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

		if (object == NULL || !object->isInstallationObject())
			return GENERALERROR;

		InstallationObject* inso = cast<InstallationObject*>( object.get());

		/*if (!inso->isHarvesterObject())
			return GENERALERROR;*/

		uint64 spawnId = Long::valueOf(arguments.toString());

		try {
			Locker clocker(object, player);

		//	HarvesterObject* harvester = cast<HarvesterObject*>( inso);

			if (inso->isOnAdminList(player) && inso->isInRange(player, 20))
				inso->changeActiveResourceID(spawnId);
			else
				player->sendSystemMessage("You are too far.");

		} catch (Exception& e) {
		}


		return SUCCESS;
	}

};

#endif //HARVESTERSELECTRESOURCECOMMAND_H_
