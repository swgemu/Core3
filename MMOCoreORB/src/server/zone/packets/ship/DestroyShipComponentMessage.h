#ifndef DESTROYSHIPCOMPONENTMESSAGE_H
#define DESTROYSHIPCOMPONENTMESSAGE_H

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

class DestroyShipComponentMessage : public BaseMessage {
public:
	DestroyShipComponentMessage(ShipObject* ship, int slot, float scale) : BaseMessage() {
		insertShort(0x12);
		insertInt(String::hashCode("DestroyShipComponentMessage"));
		insertLong(ship->getObjectID());
		insertInt(slot);
		insertFloat(scale);
	}
};

#endif // DESTROYSHIPCOMPONENTMESSAGE_H
