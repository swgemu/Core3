/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HARVESTERACTIVATECOMMAND_H_
#define HARVESTERACTIVATECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"
#include "server/zone/packets/harvester/HarvesterResourceDataMessage.h"


class HarvesterActivateCommand : public QueueCommand {
public:

	HarvesterActivateCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		CreatureObject* player = cast<CreatureObject*>(creature);

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL || !object->isInstallationObject())
			return GENERALERROR;

		InstallationObject* inso = cast<InstallationObject*>( object.get());

	/*	if (!inso->isHarvesterObject())
			return GENERALERROR;

		HarvesterObject* harvester = cast<HarvesterObject*>( inso);*/

		try {
			Locker clocker(inso, player);

			if (inso->isOnAdminList(player) && inso->isInRange(player, 20))
				inso->setOperating(true);
			else
				player->sendSystemMessage("You are too far.");


		} catch (Exception& e) {

		}


		return SUCCESS;
	}

};

#endif //HARVESTERACTIVATECOMMAND_H_
