/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HARVESTERGETRESOURCEDATACOMMAND_H_
#define HARVESTERGETRESOURCEDATACOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"
#include "server/zone/packets/harvester/HarvesterResourceDataMessage.h"

class HarvesterGetResourceDataCommand : public QueueCommand {
public:

	HarvesterGetResourceDataCommand(const String& name, ZoneProcessServer* server)
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

		if (inso->getZone() == NULL)
			return GENERALERROR;

		/*if (!inso->isHarvesterObject())
			return GENERALERROR;*/

		try {
			Locker clocker(object, player);

			HarvesterResourceDataMessage* msg = new HarvesterResourceDataMessage(player, inso);
			player->sendMessage(msg);

		} catch (Exception& e) {
		}

		return SUCCESS;
	}

};

#endif //HARVESTERGETRESOURCEDATACOMMAND_H_
