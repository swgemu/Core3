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
		currentAccelerationRate = 3,
		currentDecelerationRate = 4,
		currentPitchRate = 5,
		currentYawRate = 6,
		currentRollRate = 7,
		currentMaxPitchRate = 8,
		currentMaxYawRate = 9,
		currentMaxRollRate = 10,
		currentMaxSpeed = 11,
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
		insertFloat(ship->getShipAccelerationRate());
		insertFloat(ship->getShipDecelerationRate());

		insertFloat(ship->getCurrentPitchRate());
		insertFloat(ship->getCurrentYawRate());
		insertFloat(ship->getCurrentRollRate());

		insertFloat(ship->getMaxPitchRate());
		insertFloat(ship->getMaxYawRate());
		insertFloat(ship->getMaxRollRate());
		insertFloat(ship->getActualSpeed());

		insertLong(ship->getShipTargetID());
		insertInt(ship->getShipTargetSlot());

		ship->getTargetableBitfield()->insertToMessage(this);
		ship->getShipComponentMap()->insertToMessage(this);

		insertAscii("");
		insertAscii(ship->getShipType());
		insertAscii(ship->getShipDifficulty());
		insertAscii(ship->getShipFaction());

		insertFloat(ship->getFrontShield());
		insertFloat(ship->getRearShield());

		insertInt(0);

		setSize();
	}
};

#endif /*SHIPOBJECTMESSAGE6_H_*/
