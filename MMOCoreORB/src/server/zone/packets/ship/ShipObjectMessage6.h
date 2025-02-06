/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHIPOBJECTMESSAGE6_H_
#define SHIPOBJECTMESSAGE6_H_

#include "server/zone/packets/tangible/TangibleObjectMessage6.h"
#include "server/zone/objects/ship/ShipObject.h"

class ShipObjectMessage6 : public BaseLineMessage {
protected:
	enum index : int {
		flags = 0,
		defenders = 1,
		uniqueID = 2,
		actualAccelerationRate = 3,
		actualDecelerationRate = 4,
		actualPitchAccelerationRate = 5,
		actualYawAccelerationRate = 6,
		actualRollAccelerationRate = 7,
		actualPitchRate = 8,
		actualYawRate = 9,
		actualRollRate = 10,
		actualMaxSpeed = 11,
		targetID = 12,
		targetIDSlot = 13,
		targetableBitfield = 14,
		shipComponentMap = 15,
		wingName = 16,
		typeName = 17,
		difficulty = 18,
		faction = 19,
		frontShield = 20,
		rearShield = 21,
		guildId = 22,
	};

public:
	ShipObjectMessage6(ShipObject* ship) : BaseLineMessage(ship, 0x53484950, 6, 23) {
		insertInt(0x76); // 0x3D in creos

		ship->getDefenderList()->insertToMessage(this);

		insertShort(ship->getUniqueID());
		insertFloat(ship->getActualAccelerationRate());
		insertFloat(ship->getActualDecelerationRate());

		insertFloat(ship->getActualPitchAccelerationRate());
		insertFloat(ship->getActualYawAccelerationRate());
		insertFloat(ship->getActualRollAccelerationRate());

		insertFloat(ship->getActualPitchRate());
		insertFloat(ship->getActualYawRate());
		insertFloat(ship->getActualRollRate());
		insertFloat(ship->getActualMaxSpeed());

		insertLong(ship->getShipTargetID());
		insertInt(ship->getShipTargetSlot());

		ship->getTargetableBitfield()->insertToMessage(this);
		ship->getShipComponentMap()->insertToMessage(this);

		insertAscii(""); // wingName
		insertAscii(getShipTypeName(ship));
		insertAscii(ship->getShipDifficulty());
		insertAscii(ship->getShipFactionString());

		insertFloat(ship->getFrontShield());
		insertFloat(ship->getRearShield());

		insertInt(getGuildID(ship));

		setSize();
	}

	int getGuildID(ShipObject* ship) {
		auto owner = ship->getOwner().get();
		return owner != nullptr && owner->isInGuild() ? owner->getGuildID() : 0;
	}

	String getShipTypeName(ShipObject* ship) {
		auto owner = ship->getOwner().get();

		if (owner == nullptr || !owner->isASubChildOf(ship)) {
			return ship->getShipType();
		}

		return "";
	}
};

#endif /*SHIPOBJECTMESSAGE6_H_*/
