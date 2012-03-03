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
#include "ObjectControllerMessageCallback.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/ship/ShipObject.h"

//TODO: This is very unsafe still...
class JtlShipListResponse : public ObjectControllerMessage {
public:
	JtlShipListResponse(CreatureObject* creo, SceneObject* terminal)
		: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0x41D) {

		SceneObject* datapad = creo->getSlottedObject("datapad");

		int offs = getOffset();

		insertInt(2);
		insertLong(terminal->getObjectID());

		/* TODO: Better method of this.
		ManagedReference<ActiveArea*> region = terminal->getActiveRegion();

		if (region != NULL && region->isRegion())
			insertAscii(region->getDisplayedName());
		else
			insertAscii(terminal->getZone()->getZoneName());
		*/

		insertAscii("cRush Rocks");

		VectorMap<uint64, ManagedReference<SceneObject*> >* datapadObjects = datapad->getContainerObjects();

		for (int i = 0; i < datapadObjects->size(); ++i) {
			ManagedReference<SceneObject*> datapadObject = datapadObjects->get(i);

			if (datapadObject->getGameObjectType() == SceneObjectType::SHIPCONTROLDEVICE) {
				ManagedReference<ShipControlDevice*> shipControlDevice = cast<ShipControlDevice*>( datapadObject.get());

				if (shipControlDevice->getControlledObject() != NULL /*&& shipControlDevice->getControlledObject()->isShipObject()*/) {
					ManagedReference<ShipObject*> ship = cast<ShipObject*>( shipControlDevice->getControlledObject());

					insertLong(ship->getObjectID());
					insertAscii("cRush Rocks"); //TODO: Fix to retrieve ship->getParkedLocation();
				}
			}
		}
	}
};

#endif /* JTLSHIPLISTRESPONSE_H_ */
