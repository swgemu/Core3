//
// Created by vagrant on 8/23/17.
//

#ifndef CORE3_ONSHIPHIT_H
#define CORE3_ONSHIPHIT_H
#include "server/zone/packets/object/StandaloneObjectControllerMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

class OnShipHit : public StandaloneObjectControllerMessage {
public:
    OnShipHit(ShipObject* ship, const Vector3& hitDirection, const Vector3& hitPosition, int type, float health, float prev) : StandaloneObjectControllerMessage(ship->getObjectID(), 0x1B, 0x433) {
        writeFloat(hitDirection[0]);
        writeFloat(hitDirection[1]);
        writeFloat(hitDirection[2]);
        writeFloat(hitPosition[0]);
        writeFloat(hitPosition[1]);
        writeFloat(hitPosition[2]);
        writeInt(type);
        writeFloat(health);
        writeFloat(prev);
    }
};
#endif //CORE3_ONSHIPHIT_H
