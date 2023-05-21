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
	JtlShipListResponse(CreatureObject* creo, SceneObject* terminal) : ObjectControllerMessage(creo->getObjectID(), 0x1B, 0x41D) {
		PlayerObject* ghost = creo->getPlayerObject();

		if (ghost == nullptr) {
			return;
		}

		auto datapad = creo->getSlottedObject("datapad");

		if (datapad == nullptr) {
			return;
		}

		auto zone = creo->getZone();

		if (zone == nullptr) {
			return;
		}

		auto planetManager = zone->getPlanetManager();

		if (planetManager == nullptr) {
			return;
		}

		auto travelPoint = planetManager->getNearestPlanetTravelPoint(creo->getWorldPosition(), FLT_MAX);

		if (travelPoint == nullptr) {
			return;
		}

		VectorMap<uint64, String> shipMap;

		for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
			ManagedReference<ShipControlDevice*> control = datapad->getContainerObject(i).castTo<ShipControlDevice*>();

			if (control == nullptr) {
				continue;
			}

			auto object = control->getControlledObject();

			if (object == nullptr || !object->isShipObject()) {
				continue;
			}

			if (control->getStoredCityName() == "") {
				Locker cLock(creo);
				control->setStoredLocationData(creo);
			}

			shipMap.put(object->getObjectID(), control->getStoredCityName());
		}

		auto travelPointName = travelPoint->getPointName();

		if (travelPointName == "") {
			travelPointName = zone->getZoneName();
		}

		insertInt(shipMap.size() + 1); // Number of ships
		insertLong(terminal->getObjectID()); // Space Terminal ID
		insertAscii(travelPointName); //Player Location

		for (int i = 0; i < shipMap.size(); ++i) {
			auto shipID = shipMap.elementAt(i).getKey();
			auto cityName = shipMap.elementAt(i).getValue();

			if (cityName == "") {
				cityName = travelPointName;
			}

			insertLong(shipID);
			insertAscii(cityName);
		}
	}
};

#endif /* JTLSHIPLISTRESPONSE_H_ */
