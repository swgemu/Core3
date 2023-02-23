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

		if (!checkStateMask(creature)) {
			return INVALIDSTATE;
		}

		if (!checkInvalidLocomotions(creature)) {
			return INVALIDLOCOMOTION;
		}

		try {

			StringTokenizer tokens(arguments.toString());

			long shipId = tokens.hasMoreTokens() ? tokens.getLongToken() : 0;
			int slot = tokens.hasMoreTokens() ? tokens.getIntToken() : -1;

			if (shipId == 0 || slot == -1) {
				return GENERALERROR;
			}

			ZoneServer* zoneServer = server->getZoneServer();

			if (zoneServer == nullptr) {
				return GENERALERROR;
			}

			ManagedReference<SceneObject*> sceneO = zoneServer->getObject(shipId);

			if (sceneO == nullptr) {
				return GENERALERROR;
			}

			ManagedReference<ShipObject*> ship = sceneO->asShipObject();

			if (ship == nullptr) {
				return GENERALERROR;
			}

			Locker locker(ship);
			ship->uninstall(creature, slot, true);

		} catch (Exception& e) {
			error() << "UninstallShipComponentCommand exception: " << e.what();
		}

		return SUCCESS;
	}

};

#endif //UNINSTALLSHIPCOMPONENTCOMMAND_H_
