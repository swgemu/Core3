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

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		StringTokenizer tokenizer(arguments.toString());

		if (!tokenizer.hasMoreTokens())
			return GENERALERROR;

		uint64 shipID = tokenizer.hasMoreTokens() ? tokenizer.getLongToken() : 0;
		uint32 groupSize = tokenizer.hasMoreTokens() ? tokenizer.getIntToken() : 0;
		Vector<ManagedReference<CreatureObject*>> groupMembers;

		for (int i = 0; i < groupSize; i++) {
			uint64 memberID = tokenizer.getLongToken();
			ManagedReference<SceneObject*> memberScno = zoneServer->getObject(memberID).get();

			if (memberScno == nullptr || !memberScno->isPlayerCreature())
				continue;

			auto groupMember = memberScno->asCreatureObject();

			if (groupMember != nullptr)
				groupMembers.add(groupMember);
		}

		String arrivalPlanet = tokenizer.hasMoreTokens() ? tokenizer.getStringToken() : "";
		String arrivalPointName = tokenizer.hasMoreTokens() ? tokenizer.getStringToken().replaceAll("_", " ") : "";

		ManagedReference<SceneObject*> terminal = zoneServer->getObject(target);

		if (terminal == nullptr || terminal->getGameObjectType() != SceneObjectType::SPACETERMINAL) {
			return INVALIDSTATE;
		}

		ManagedReference<ShipControlDevice*> pcd = zoneServer->getObject(shipID).castTo<ShipControlDevice*>();

		if (pcd == nullptr) {
			return GENERALERROR;
		}

		ManagedReference<ShipObject*> ship = pcd->getControlledObject()->asShipObject();

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
				auto member = groupMembers.get(j);

				if (member == nullptr) {
					continue;
				}

				Locker memLock(member, creature);

				member->switchZone(arrivalPlanet, arrivalPosition.getX(),arrivalPosition.getY(),arrivalPosition.getZ(), 0);
			}

			creature->switchZone(arrivalPlanet, arrivalPosition.getX(),arrivalPosition.getY(),arrivalPosition.getZ(), 0);
			pcd->setStoredLocationData(creature);

		} else { // launch into space
			Zone* departureZone = creature->getZone();

			if (departureZone == nullptr) {
				return GENERALERROR;
			}

			PlanetManager* planetManager = departureZone->getPlanetManager();

			if (planetManager == nullptr) {
				return GENERALERROR;
			}

			String jtlZoneName = planetManager->getJtlZoneName();

			if (jtlZoneName == "") {
				return GENERALERROR;
			}

			SpaceZone* spaceZone = zoneServer->getSpaceZone(jtlZoneName);

			if (spaceZone == nullptr) {
				return GENERALERROR;
			}

			Vector3 randomPosition = Vector3(System::random(100.f), System::random(100.f), System::random(100.f));
			Vector3 launchPosition = planetManager->getJtlLaunchLocations() + randomPosition;

			Locker pLock(pcd, creature);

			pcd->launchShip(creature, jtlZoneName, launchPosition);
			pcd->insertPlayer(creature);

			for (int j = 0; j < groupMembers.size(); j++) {
				auto groupMember = groupMembers.get(j);

				if (groupMember != nullptr) {
					Locker memLock(groupMember, creature);
					pcd->launchGroupMember(groupMember);
				}
			}
		}

		return SUCCESS;
	}
};

#endif // LAUNCHINTOSPACECOMMAND_H_
