/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LAUNCHINTOSPACECOMMAND_H_
#define LAUNCHINTOSPACECOMMAND_H_
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/ship/ShipObject.h"

class LaunchIntoSpaceCommand : public QueueCommand {
public:
	LaunchIntoSpaceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

        StringTokenizer tokenizer(arguments.toString());

        ZoneServer* zoneServer = server->getZoneServer();

        info(arguments.toString(), true);
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
        for (int i=0; i<numGroupMembers; i++) {
            ManagedReference<SceneObject*> member = zoneServer->getObject(tokenizer.getLongToken());
            if (member != nullptr)
                groupMembers.add(member);
        }

        if (tokenizer.hasMoreTokens()) { // fast travel
            String arrivalPlanet;
            String arrivalPointName;
            tokenizer.getStringToken(arrivalPlanet);
            tokenizer.getStringToken(arrivalPointName);
            arrivalPointName = arrivalPointName.replaceAll("_", " ");


            ManagedReference<Zone*> arrivalZone = server->getZoneServer()->getZone(arrivalPlanet);
            if (arrivalZone == nullptr) {
                creature->sendSystemMessage("@travel:route_not_available"); //This ticket's route is no longer available.
                return GENERALERROR;
            }

            if (!arrivalZone->getPlanetManager()->hasJTLTravelDestination(arrivalPointName)) {
                creature->sendSystemMessage("@travel:route_not_available"); //This ticket's route is no longer available.
                return GENERALERROR;
            }

            Vector3 dest = arrivalZone->getPlanetManager()->getJTLTravelDestination(arrivalPointName);
            creature->switchZone(arrivalPlanet, dest.getX(), dest.getY(), dest.getZ(), 0);
        } else { // launch into space
            Zone *zone = creature->getZone();
            if (zone == nullptr) {
                error("NULL Zone in LaunchIntoSpaceCommand");
                return GENERALERROR;
            }

            String zoneName = zone->getPlanetManager()->getJTLZoneName();
            const Vector3 position = zone->getPlanetManager()->getJTLLaunchLocation();
            info("Zone: " + zoneName + " Pos: " + position.toString(), true);
           // if (ship->getContainerObjectsSize() == 0) {
                creature->switchZone(zoneName, position.getX(), position.getY(), position.getZ(), 0);
            //}
            Reference<Zone*> newZone = creature->getZone();
            Reference<CreatureObject*> strongCreo = creature;

            Core::getTaskManager()->executeTask([newZone, ship, strongCreo, position]{
                Locker locker(ship);
                Locker cross(ship, newZone);
                ship->initializePosition(position.getX(), position.getY(), position.getZ());

                newZone->transferObject(ship, -1, true);

                cross.release();

                Locker creoCross(ship, strongCreo);
                if (ship->getContainerObjectsSize() > 0) {
                    ManagedReference<CellObject*> cockpit = ship->getCell("cockpit");
                    Core::getTaskManager()->executeTask([cockpit, strongCreo, newZone] {
                        Locker locker(strongCreo);
                        Locker cross(cockpit, strongCreo);
                        cross.release();
                        //strongCreo->destroyObjectFromWorld(true);
                        cockpit->transferObject(strongCreo, -1, false);
                        //strongCreo->switchZone(newZone->getZoneName(), 13.43, 0.14, 12.88, cockpit->getObjectID());
                        strongCreo->initializePosition(13.43,0.14,12.88);
                        strongCreo->sendToOwner(true);

                        PlayerObject *player = strongCreo->getPlayerObject();
                        player->notifySceneReady();
                    }, "cockpit_transfer");
                } else {
                    Locker creoCross(strongCreo, ship);
                    ship->transferObject(strongCreo, 5, true);
                    strongCreo->setState(CreatureState::PILOTINGSHIP);
                }

                PlayerObject* ghost = strongCreo->getPlayerObject();

                if (ghost != nullptr)
                    ghost->setTeleporting(true);
            }, "Transfer Ship Task");

        }



		return SUCCESS;
	}

};

#endif //LAUNCHINTOSPACECOMMAND_H_

