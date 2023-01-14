/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LAUNCHINTOSPACECOMMAND_H_
#define LAUNCHINTOSPACECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/managers/space/SpaceManager.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/packets/scene/UpdateTransformMessage.h"

class LaunchIntoSpaceCommand : public QueueCommand {
public:
	LaunchIntoSpaceCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer tokenizer(arguments.toString());

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		Reference<SceneObject*> terminal = server->getZoneServer()->getObject(target);

		if (terminal == nullptr || terminal->getGameObjectType() != SceneObjectType::SPACETERMINAL)
			return INVALIDSTATE;

		uint64 shipID = tokenizer.getLongToken();
		ManagedReference<ShipControlDevice*> pcd = zoneServer->getObject(shipID).castTo<ShipControlDevice*>();

		if (pcd == nullptr) {
			creature->error("Error retrieving ship");
			return GENERALERROR;
		}

		ManagedReference<ShipObject*> ship = cast<ShipObject*>(pcd->getControlledObject());

		if (ship == nullptr) {
			creature->error("Error retrieving ship");
			return GENERALERROR;
		}

		if (ship->getOwner() != creature) {
			creature->error("Attempting to launch another players ship: " + String::valueOf(shipID));
			return GENERALERROR;
		}

		Vector<ManagedReference<SceneObject*>> groupMembers;
		int numGroupMembers = tokenizer.getIntToken();

		for (int i = 0; i < numGroupMembers; i++) {
			ManagedReference<SceneObject*> member = zoneServer->getObject(tokenizer.getLongToken());

			if (member != nullptr)
				groupMembers.add(member);
		}

		// JTL Fast Travel
		if (tokenizer.hasMoreTokens()) {
			String arrivalPlanet;
			String arrivalPointName;
			tokenizer.getStringToken(arrivalPlanet);
			tokenizer.getStringToken(arrivalPointName);
			arrivalPointName = arrivalPointName.replaceAll("_", " ");

			ManagedReference<Zone*> arrivalZone = server->getZoneServer()->getZone(arrivalPlanet);

			if (arrivalZone == nullptr) {
				creature->sendSystemMessage("@travel:route_not_available"); // This ticket's route is no longer available.
				return GENERALERROR;
			}

			PlanetManager* planetMan = arrivalZone->getPlanetManager();

			if (planetMan == nullptr)
				return GENERALERROR;

			if (!planetMan->hasJtlTravelDestination(arrivalPointName)) {
				creature->sendSystemMessage("@travel:route_not_available"); // This ticket's route is no longer available.
				return GENERALERROR;
			}

			Vector3 dest = planetMan->getJtlTravelDestination(arrivalPointName);
			creature->switchZone(arrivalPlanet, dest.getX(), dest.getY(), dest.getZ(), 0);
		} else { // launch into space
			Zone* zone = creature->getZone();

			if (zone == nullptr) {
				error("nullptr Zone in LaunchIntoSpaceCommand");
				return GENERALERROR;
			}

			PlanetManager* planetMan = zone->getPlanetManager();

			if (planetMan == nullptr)
				return GENERALERROR;

			String jtlZoneName = planetMan->getJtlZoneName();

			if (jtlZoneName == "") {
				error("No JTL Zone Name for Zone: " + zone->getZoneName());
				return GENERALERROR;
			}

			SpaceZone* spaceZone = zoneServer->getSpaceZone(jtlZoneName);

			if (spaceZone == nullptr)
				return GENERALERROR;

			Vector3 position = planetMan->getJtlLaunchLocations();
			Locker creoCross(ship, creature);

			Locker zoneLock(spaceZone, ship);
			ship->initializePosition(position.getX(), position.getZ(), position.getY());
			spaceZone->transferObject(ship, -1, true);
			zoneLock.release();

			ship->setFaction(creature->getFaction());
			ship->setFactionStatus(creature->getFactionStatus());

			uint64 parentID = ship->getObjectID();

			// POB Ship
			if (ship->getContainerObjectsSize() > 0) {
				auto cockpit = ship->getCell(0);

				if (cockpit != nullptr) {
					parentID = cockpit->getObjectID();
				}
			} else {
				creature->setState(CreatureState::PILOTINGSHIP);
			}

			creature->switchZone(jtlZoneName, position.getX(), position.getZ(), position.getY(), parentID);

			creature->synchronizeCloseObjects();
		}

		return SUCCESS;
	}
};

#endif // LAUNCHINTOSPACECOMMAND_H_
