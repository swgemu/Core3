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
#include "server/zone/objects/intangible/ShipControlDevice.h"

class JtlShipListResponse: public ObjectControllerMessage {
public:
	JtlShipListResponse(CreatureObject* player, SceneObject* terminal) : ObjectControllerMessage(player->getObjectID(), 0x1B, 0x41D) {
		if (player == nullptr)
			return;

		PlayerObject* ghost = player->getPlayerObject();

		if (ghost == nullptr) {
			return;
		}

		auto datapad = player->getSlottedObject("datapad");

		if (datapad == nullptr) {
			return;
		}

		auto zone = player->getZone();

		if (zone == nullptr) {
			return;
		}

		auto planetManager = zone->getPlanetManager();

		if (planetManager == nullptr) {
			return;
		}

		auto travelPoint = planetManager->getNearestPlanetTravelPoint(player->getWorldPosition(), 128.f);

		// If this is a blank string it will just show the ships not at this location
		auto travelPointName = travelPoint != nullptr ? travelPoint->getPointName() : "";

		VectorMap<uint64, String> shipMap;
		int datapadSize = datapad->getContainerObjectsSize();

		for (int i = 0; i < datapadSize; i++) {
			ManagedReference<SceneObject*> sceneO = datapad->getContainerObject(i);

			if (sceneO == nullptr || !sceneO->isShipControlDevice()) {
				continue;
			}

			ShipControlDevice* shipDevice = sceneO.castTo<ShipControlDevice*>();

			if (shipDevice == nullptr)
				continue;

			auto object = shipDevice->getControlledObject();

			if (object == nullptr || !object->isShipObject()) {
				continue;
			}

			if (shipDevice->getParkingLocation().isEmpty()) {
				Locker cLock(shipDevice, player);
				shipDevice->setParkingLocation(travelPointName);
			}

			shipMap.put(object->getObjectID(), shipDevice->getParkingLocation());
		}

		insertInt(shipMap.size() +1); // Number of ships
		insertLong(terminal->getObjectID()); // Space Terminal ID
		insertAscii(travelPointName); //Player Location

		for (int i = 0; i < shipMap.size(); i++) {
			auto shipID = shipMap.elementAt(i).getKey();
			auto cityName = shipMap.elementAt(i).getValue();

			insertLong(shipID);
			insertAscii(cityName);
		}
	}
};

#endif /* JTLSHIPLISTRESPONSE_H_ */
