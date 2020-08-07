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
				ManagedReference<ShipObject*> ship = ghost->getShip(i).get();
				if (ship != nullptr)
					ships.add(ship);
			}

			insertInt(ships.size()+1); // size
			Logger::console.info("Outgoing Terminal ID: " + String::valueOf(terminal->getObjectID()), true);
			insertLong(terminal->getObjectID());
			insertAscii("tatooine");
			for (auto &ship : ships) {
				Logger::console.info("Outgoing ship ID: " + String::valueOf(ship->getObjectID()), true);
				insertLong(ship->getObjectID());
				insertAscii("tatooine");
			}
		}
};

#endif /* JTLSHIPLISTRESPONSE_H_ */
