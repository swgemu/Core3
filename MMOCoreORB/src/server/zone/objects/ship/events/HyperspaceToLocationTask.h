//
// Created by g on 12/20/17.
//

#ifndef CORE3_HYPERSPACETOLOCATIONTASK_H
#define CORE3_HYPERSPACETOLOCATIONTASK_H

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/OrientForHyperspace.h"
#include "server/zone/packets/object/BeginHyperspace.h"
#include "server/zone/packets/object/Hyperspace.h"
#include "server/zone/packets/scene/SceneObjectDestroyMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

class HyperspaceToLocationTask : public Task {
    ManagedWeakReference<CreatureObject*> play;
    ManagedWeakReference<SceneObject*> ship;
    String zone;
    Vector3 location;
    int iteration;

public:
    HyperspaceToLocationTask(CreatureObject* pl, ShipObject* ship, const String& zone, const Vector3& location) : Task() {
        play = pl;
        this->zone = zone;
        this->location = location;
        this->ship = ship;
        iteration = 0;
    }

    void run() {
        Reference<CreatureObject*> creo = play.get();
        Reference<SceneObject*> scno = ship.get();
        if (creo == nullptr || scno == nullptr)
            return;

        int currentIter = iteration++;

        switch(currentIter) {
            case 0:
                creo->sendSystemMessage("@space/space_interaction:hyperspace_route_begin");
                reschedule(5000);
                return;
            case 1: // 25%
            case 2: // 50%
            case 3: // 75%
            {
                String strid = "@space/space_interaction:hyperspace_route_calculation_";
                strid += String::valueOf(currentIter);
                creo->sendSystemMessage(strid);
                reschedule(5000);
                return;
            }
            case 4: // 100%
                orientShip();
            case 5: // t-4
            case 6: // t-3
            case 7: // t-2
            case 8: // t-1
            {
                String strid = "@space/space_interaction:hyperspace_route_calculation_";
                strid += String::valueOf(currentIter);
                creo->sendSystemMessage(strid);
                reschedule(1000);
                return;
            }
            case 9:
                beginHyperspace();
                reschedule(6000);
                return;
            case 10:
            {
                ShipObject *shipObject = scno->asShipObject();
                if (shipObject == nullptr)
                    return;

                Locker locker(scno);
                Zone *newZone = shipObject->getZone();
                shipObject->setHyperspacing(true);
                shipObject->destroyObjectFromWorld(true);
                reschedule(1000);
                return;
            }
            case 11:
            {
                Zone *newZone = ServerCore::getZoneServer()->getZone(zone);
                if (newZone == nullptr)
                    return;

                Locker locker(scno);
                Locker zoneCross(newZone, scno);
                scno->initializePosition(location.getX(), location.getZ(), location.getY());
                newZone->transferObject(scno, -1, false);
                Logger::console.info("Creo Parent: " + String::valueOf((uint64)creo->getParent().get().get()), true);
                zoneCross.release();
                Locker creoCross(creo, scno);
                //scno->transferObject(creo, 5, false);
                //creo->setState(CreatureState::PILOTINGSHIP);
                creo->sendToOwner(true);
                return;
            }
        }
    }

    void orientShip() {
        Reference<CreatureObject*> creo = play.get();
        if (creo == nullptr)
            return;

        OrientForHyperspaceMessage *msg = new OrientForHyperspaceMessage(creo->getObjectID(), zone, location.getX(), location.getY(), location.getZ());
        creo->sendMessage(msg);
    }

    void beginHyperspace() {
        Reference<CreatureObject*> creo = play.get();
        if (creo == nullptr)
            return;

        BeginHyperspaceMessage *msg = new BeginHyperspaceMessage(creo->getObjectID(), zone, location.getX(), location.getY(), location.getZ());
        creo->sendMessage(msg);
    }
};

#endif //CORE3_HYPERSPACETOLOCATIONTASK_H
