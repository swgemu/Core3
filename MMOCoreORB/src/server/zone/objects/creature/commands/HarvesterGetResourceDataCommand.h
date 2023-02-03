/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HARVESTERGETRESOURCEDATACOMMAND_H_
#define HARVESTERGETRESOURCEDATACOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/harvester/HarvesterResourceDataMessage.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"

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

		if (object == nullptr || !object->isHarvesterObject())
			return GENERALERROR;

		HarvesterObject* harvester = cast<HarvesterObject*>( object.get());

		auto zone = harvester->getZone();

		if (zone == nullptr)
			return GENERALERROR;

		try {
			Locker clocker(object, player);

			HarvesterResourceDataMessage* msg = new HarvesterResourceDataMessage(player, harvester, zone);
			player->sendMessage(msg);

		} catch (Exception& e) {
		}

		return SUCCESS;
	}

};

#endif //HARVESTERGETRESOURCEDATACOMMAND_H_
