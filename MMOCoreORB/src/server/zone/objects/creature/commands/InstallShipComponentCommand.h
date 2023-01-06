/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSTALLSHIPCOMPONENTCOMMAND_H_
#define INSTALLSHIPCOMPONENTCOMMAND_H_

#include "server/zone/objects/ship/ShipObject.h"

class InstallShipComponentCommand : public QueueCommand {
public:

	InstallShipComponentCommand(const String& name, ZoneProcessServer* server)
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
		long componentId = tokenizer.getLongToken();

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> component = zoneServer->getObject(componentId);
		ManagedReference<SceneObject*> shipSceneO = zoneServer->getObject(shipId);

		if (component == nullptr || shipSceneO == nullptr)
			return GENERALERROR;

		ManagedReference<ShipObject*> ship = shipSceneO.castTo<ShipObject*>();

		if (ship == nullptr)
			return GENERALERROR;

		Locker locker(ship);
		//info("Attempting to install component(" + String::valueOf((int64)componentId) + ") at slot: " + String::valueOf(slot), true);
		ship->install(creature, component, slot);

		return SUCCESS;
	}

};

#endif //INSTALLSHIPCOMPONENTCOMMAND_H_
