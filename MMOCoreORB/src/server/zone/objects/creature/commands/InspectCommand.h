/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSPECT_H_
#define INSPECT_H_

#include "QueueCommand.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "templates/params/ship/ShipFlags.h"

class InspectCommand : public QueueCommand {
public:
	InspectCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!checkSpaceStates(creature))
			return INVALIDSTATE;

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		StringTokenizer args(arguments.toString());

		ManagedReference<SceneObject*> object = zoneServer->getObject(target);

		if (object == nullptr)
			return INVALIDTARGET;

		String command;
		args.getStringToken(command);

		// for testing
		if (command.toLowerCase() == "shipfollow") {
			if (!object->isShipAiAgent())
				return INVALIDTARGET;

			auto ghost = creature->getPlayerObject();

			if (ghost == nullptr || !ghost->isPrivileged())
				return GENERALERROR;

			ShipAiAgent* shipAgent = object->asShipAiAgent();

			if (shipAgent == nullptr)
				return GENERALERROR;

			ManagedReference<SceneObject*> rootParent = creature->getRootParent();

			if (rootParent == nullptr || !rootParent->isShipObject()) {
				return GENERALERROR;
			}

			ShipObject* shipParent = rootParent->asShipObject();

			if (shipParent == nullptr)
				return GENERALERROR;

			Locker clocker(shipAgent, creature);

			shipAgent->addShipFlag(ShipFlag::ESCORT);
			shipAgent->setShipAiTemplate();

			shipAgent->setFollowShipObject(shipParent);

			return SUCCESS;
		}

		// Inspect ship here


		return SUCCESS;
	}
};

#endif // INSPECT_H_
