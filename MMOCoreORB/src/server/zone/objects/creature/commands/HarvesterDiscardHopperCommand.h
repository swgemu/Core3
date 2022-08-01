/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HARVESTERDISCARDHOPPERCOMMAND_H_
#define HARVESTERDISCARDHOPPERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"

class HarvesterDiscardHopperCommand : public QueueCommand {
public:

	HarvesterDiscardHopperCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		CreatureObject* player = cast<CreatureObject*>(creature);

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == nullptr || !object->isHarvesterObject())
			return GENERALERROR;

		HarvesterObject* harvester = cast<HarvesterObject*>(object.get());

		if (harvester == nullptr)
			return GENERALERROR;

		Locker clocker(harvester, player);

		if (!harvester->isOnAdminList(player) || harvester->isInRange(player, 20))
			return GENERALERROR;

		harvester->discardHopperContents();

		return SUCCESS;
	}

};

#endif //HARVESTERDISCARDHOPPERCOMMAND_H_
