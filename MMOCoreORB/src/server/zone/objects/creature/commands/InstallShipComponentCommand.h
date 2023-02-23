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

		if (!checkStateMask(creature)) {
			return INVALIDSTATE;
		}

		if (!checkInvalidLocomotions(creature)) {
			return INVALIDLOCOMOTION;
		}

		try {

			StringTokenizer tokens(arguments.toString());

			unsigned long shipId = tokens.hasMoreTokens() ? tokens.getLongToken() : 0;
			unsigned int slot = tokens.hasMoreTokens() ? tokens.getIntToken() : -1;
			unsigned long compId = tokens.hasMoreTokens() ? tokens.getLongToken() : 0;

			if (shipId == 0 || slot == -1 || compId == 0) {
				return GENERALERROR;
			}

			ZoneServer* zoneServer = server->getZoneServer();

			if (zoneServer == nullptr) {
				return GENERALERROR;
			}

			ManagedReference<SceneObject*> component = zoneServer->getObject(compId);

			if (component == nullptr) {
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
			ship->install(creature, component, slot, true);

		} catch (Exception& e) {
			error() << "UninstallShipComponentCommand exception: " << e.what();
		}

		return SUCCESS;
	}

};

#endif //INSTALLSHIPCOMPONENTCOMMAND_H_
