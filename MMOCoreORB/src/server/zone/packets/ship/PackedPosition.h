/*
 * PackedPosition.h
 *
 *  Created on: Aug 22, 2017
 *      Author: TheAnswer
 */

#ifndef SRC_SERVER_ZONE_PACKETS_SHIP_PACKEDPOSITION_H_
#define SRC_SERVER_ZONE_PACKETS_SHIP_PACKEDPOSITION_H_

#include "PackedUnitVector.h"
#include "engine/util/u3d/Vector3.h"

class PackedPosition {
    float x, y, z;

public:
    PackedPosition() {

    }

    PackedPosition(const Vector3& vector) {
        set(vector);
    }

    void parse(Message* message) {
        x = message->readSignedShort();
        y = message->readSignedShort();
        z = message->readSignedShort();
    }

    void write(Message* message) {
        message->writeShort(x);
        message->writeShort(y);
        message->writeShort(z);
    }

    void set(const Vector3& v) {
        x = static_cast<int16>(clamp(-8000.0f, v.getX(), 8000.f)*(32767.f / 8000.f));
        y = static_cast<int16>(clamp(-8000.0f, v.getY(), 8000.f)*(32767.f / 8000.f));
        z = static_cast<int16>(clamp(-8000.0f, v.getZ(), 8000.f)*(32767.f / 8000.f));
    }

    Vector3 get() {
        return Vector3((x*(8000.f / 32767.f)), (y*(8000.f / 32767.f)), (z*(8000.f / 32767.f)));
    }
};


#endif /* SRC_SERVER_ZONE_PACKETS_SHIP_PACKEDVELOCITY_H_ */
