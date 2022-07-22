/*
 * JtlShipListResponse.h
 *
 *  Created on: Apr 25, 2011
 *      Author: crush
 */

#ifndef JTLSHIPLISTRESPONSE_H_
#define JTLSHIPLISTRESPONSE_H_

#include "ObjectControllerMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/ship/ShipObject.h"

//TODO: This is very unsafe still...
class JtlShipListResponse : public ObjectControllerMessage {
public:
	JtlShipListResponse(CreatureObject* creo, SceneObject* terminal)
		: ObjectControllerMessage(creo->getObjectID(), 0x1B, 0x41D) {


			PlayerObject* ghost = creo->getPlayerObject();
			if (ghost == nullptr)
				return;

			int numShips = 0;
			Vector<Reference<ShipObject*>> ships;
			for (int i=0; i<ghost->getNumShips(); i++) {
				ManagedReference<ShipObject*> ship = ghost->getShip(i);
				if (ship)
					ships.add(ship);
			}

			insertInt(ships.size()+1); // Number of ships
			insertLong(terminal->getObjectID()); // Space Terminal ID
			String Current;

			if (terminal->getCityRegion().get() != nullptr)
				Current = creo->getCityRegion().get()->getRegionDisplayedName();
			else
				Current = creo->getZone()->getZoneName();

			insertAscii(Current); //Player Location

			for (auto &ship : ships) {
				insertLong(ship->getObjectID());
				String parked = ship->getStoredLocation();
				if (parked == "")
					ship->setStoredLocation(Current);
				insertAscii(parked);
			}
		}
};

#endif /* JTLSHIPLISTRESPONSE_H_ */
