/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNINSTALLSHIPCOMPONENTCOMMAND_H_
#define UNINSTALLSHIPCOMPONENTCOMMAND_H_

#include "server/zone/objects/ship/ShipObject.h"

class UninstallShipComponentCommand : public QueueCommand {
public:

	UninstallShipComponentCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer tokenizer(arguments.toString());
		long shipId = tokenizer.getLongToken();
		int slot = tokenizer.getIntToken();

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> shipSceneO = zoneServer->getObject(shipId);

		if (shipSceneO == nullptr)
			return GENERALERROR;

		ManagedReference<ShipObject*> ship = shipSceneO.castTo<ShipObject*>();

		if (ship == nullptr)
			return GENERALERROR;

		Locker locker(ship);

		ship->uninstall(creature, slot, true);

		return SUCCESS;
	}

};

#endif //UNINSTALLSHIPCOMPONENTCOMMAND_H_
