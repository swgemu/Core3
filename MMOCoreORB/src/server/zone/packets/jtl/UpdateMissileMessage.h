#ifndef UPDATEMISSILEMESSAGE_H_
#define UPDATEMISSILEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

class UpdateMissileMessage : public BaseMessage {
public:
	enum UpdateType : int {
		MISS = 0,
		HIT = 1,
		COUNTERED = 2,
		COUNTERFAILED = 3
	};

	UpdateMissileMessage(ShipObject* ship, const ShipProjectile* projectile, int countermeasureType, int updateType) : BaseMessage() {
		insertShort(0x14);
		insertInt(String::hashCode("UpdateMissileMessage"));

		insertInt(projectile->getUniqueID());
		insertLong(ship->getObjectID());
		insertInt(countermeasureType);
		insertInt(updateType);
	}
};

#endif /* UPDATEMISSILEMESSAGE_H_ */
