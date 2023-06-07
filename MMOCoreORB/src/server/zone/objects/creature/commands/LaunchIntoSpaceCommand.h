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
#include "server/zone/objects/intangible/tasks/LaunchShipTask.h"

class LaunchIntoSpaceCommand : public QueueCommand {
public:
	LaunchIntoSpaceCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		StringTokenizer tokenizer(arguments.toString());

		if (!tokenizer.hasMoreTokens())
			return GENERALERROR;

		uint64 scdID = tokenizer.hasMoreTokens() ? tokenizer.getLongToken() : 0;
		uint32 groupSize = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0;
		Vector<uint64> groupMembers;

		for (int i = 0; i < groupSize; i++) {
			uint64 memberID = tokenizer.getLongToken();
			groupMembers.add(memberID);
		}

		String arrivalPlanet = tokenizer.hasMoreTokens() ? tokenizer.getStringToken() : "";
		String arrivalPointName = tokenizer.hasMoreTokens() ? tokenizer.getStringToken().replaceAll("_", " ") : "";

		ManagedReference<SceneObject*> terminal = zoneServer->getObject(target);

		if (terminal == nullptr || terminal->getGameObjectType() != SceneObjectType::SPACETERMINAL) {
			return INVALIDSTATE;
		}

		ManagedReference<ShipControlDevice*> shipDevice = zoneServer->getObject(scdID).castTo<ShipControlDevice*>();

		if (shipDevice == nullptr) {
			return GENERALERROR;
		}

		ManagedReference<ShipObject*> ship = shipDevice->getControlledObject()->asShipObject();

		if (ship == nullptr || ship->getOwner().get() != creature) {
			return GENERALERROR;
		}

		// JTL Fast Travel
		if (arrivalPlanet != "") {
			Zone* arrivalZone = zoneServer->getZone(arrivalPlanet);

			if (arrivalZone == nullptr) {
				creature->sendSystemMessage("@travel:route_not_available"); // This ticket's route is no longer available.
				return QueueCommand::GENERALERROR;
			}

			PlanetManager* planetManager = arrivalZone->getPlanetManager();

			if (planetManager == nullptr || !planetManager->hasJtlTravelDestination(arrivalPointName)) {
				creature->sendSystemMessage("@travel:route_not_available"); // This ticket's route is no longer available.
				return QueueCommand::GENERALERROR;
			}

			Vector3 arrivalPosition = planetManager->getJtlTravelDestination(arrivalPointName);

			for (int j = 0; j < groupMembers.size(); j++) {
				auto memberID = groupMembers.get(j);
				auto memberScno = zoneServer->getObject(memberID);

				if (memberScno == nullptr || !memberScno->isPlayerCreature())
					continue;

				auto groupMember = memberScno->asCreatureObject();

				if (groupMember == nullptr)
					continue;

				Locker memLock(memberScno, creature);

				groupMember->switchZone(arrivalPlanet, arrivalPosition.getX(),arrivalPosition.getY(),arrivalPosition.getZ(), 0);
			}

			creature->switchZone(arrivalPlanet, arrivalPosition.getX(),arrivalPosition.getY(),arrivalPosition.getZ(), 0);

			Locker cLock(shipDevice, creature);
			shipDevice->setStoredLocationData(creature);
		 // launch into space
		} else {
			LaunchShipTask* launchTask = new LaunchShipTask(creature, shipDevice, groupMembers);

			if (launchTask != nullptr) {
				launchTask->schedule(100);
			}
		}

		return SUCCESS;
	}
};

#endif // LAUNCHINTOSPACECOMMAND_H_
