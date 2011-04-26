/*
 * JtlShipListResponse.h
 *
 *  Created on: Apr 25, 2011
 *      Author: crush
 */

#ifndef JTLSHIPLISTRESPONSE_H_
#define JTLSHIPLISTRESPONSE_H_

#include "ObjectControllerMessage.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "ObjectControllerMessageCallback.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"

//TODO: This is very unsafe still...
class JtlShipListResponse : public ObjectControllerMessage {
public:
	JtlShipListResponse(CreatureObject* creo, uint64 terminalObjectID = 0)
		: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0x41D) {

		SceneObject* datapad = creo->getSlottedObject("datapad");

		int offs = getOffset();

		insertInt(2);
		insertLong(terminalObjectID);
		insertAscii("Theed Spaceport");

		VectorMap<uint64, ManagedReference<SceneObject*> >* datapadObjects = datapad->getContainerObjects();

		for (int i = 0; i < datapadObjects->size(); ++i) {
			ManagedReference<SceneObject*> datapadObject = datapadObjects->get(i);

			if (datapadObject->getGameObjectType() == SceneObject::SHIPCONTROLDEVICE) {
				ManagedReference<ShipControlDevice*> shipControlDevice = (ShipControlDevice*) datapadObject.get();

				insertLong(shipControlDevice->getControlledObject()->getObjectID());
				insertAscii("Theed Spaceport");
			}
		}
	}
};

#endif /* JTLSHIPLISTRESPONSE_H_ */
