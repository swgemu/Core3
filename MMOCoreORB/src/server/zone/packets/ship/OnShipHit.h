//
// Created by vagrant on 8/23/17.
//

#ifndef CORE3_ONSHIPHIT_H
#define CORE3_ONSHIPHIT_H
#include "server/zone/packets/object/ObjectControllerMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

class OnShipHit : public ObjectControllerMessage {
public:
    OnShipHit(ShipObject* ship, const Vector3& hitDirection, int type, float health, float prev) : ObjectControllerMessage(ship->getObjectID(), 0x1B, 0x432) {
        writeFloat(hitDirection[0]);
        writeFloat(hitDirection[1]);
        writeFloat(hitDirection[2]);
        writeInt(type);
        writeFloat(health);
        writeFloat(prev);
    }
};
#endif //CORE3_ONSHIPHIT_H
