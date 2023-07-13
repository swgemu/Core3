//
// Created by vagrant on 8/23/17.
//

#ifndef ONSHIPHIT_H
#define ONSHIPHIT_H
#include "server/zone/packets/object/ObjectControllerMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

class OnShipHit : public ObjectControllerMessage {
public:
	OnShipHit(ShipObject* ship, const Vector3& hitDirection, int shipHitType, float newPercent, float oldPercent) : ObjectControllerMessage(ship->getObjectID(), 0x1B, 0x432) {
		writeFloat(hitDirection.getX());
		writeFloat(hitDirection.getZ());
		writeFloat(hitDirection.getY());
		writeInt(shipHitType);
		writeFloat(newPercent);
		writeFloat(oldPercent);
	}
};
#endif //ONSHIPHIT_H
