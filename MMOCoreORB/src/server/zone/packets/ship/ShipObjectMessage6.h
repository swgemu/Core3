/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHIPOBJECTMESSAGE6_H_
#define SHIPOBJECTMESSAGE6_H_

#include "server/zone/packets/tangible/TangibleObjectMessage6.h"
#include "server/zone/objects/ship/ShipObject.h"

class ShipObjectMessage6 : public TangibleObjectMessage6 {
public:
	ShipObjectMessage6(ShipObject* ship) : TangibleObjectMessage6(ship, 0x53484950, 0x18) {
		//ship->info(true) << "ShipObjectMessage6 sent";

		insertShort(ship->getUniqueID()); // ShipID
		insertFloat(ship->getShipAccelerationRate()); // acceleration rate
		insertFloat(ship->getShipDecelerationRate()); // decelleration rate

		insertFloat(ship->getCurrentPitchRate()); //5 Pitch Acceleration Max
		insertFloat(ship->getCurrentYawRate()); // 6 Yaw Acceleration Max
		insertFloat(ship->getCurrentRollRate()); //7 Roll Acceleration Max

		insertFloat(ship->getMaxPitchRate()); //8 Pitch Acceleration
		insertFloat(ship->getMaxYawRate()); //9 Yaw Acceleration
		insertFloat(ship->getMaxRollRate()); //10 Roll Acceleration
		insertFloat(ship->getMaxSpeed()); //11 max speed

		// look at target
		insertLong(0); //12 const

		insertInt(0); //13 m_pilotLookAtTargetSlot

		ship->getTargetableBitfield()->insertToMessage(this);

		ship->getShipComponentMap()->insertToMessage(this); //15

		insertAscii("");
		insertAscii("");
		insertAscii("");
		insertAscii("");

		insertFloat(ship->getFrontShield()); //20 front shield current
		insertFloat(ship->getRearShield()); //21 back shield current

		insertInt(0); // Guild ID?

		setSize();
	}
};

#endif /*SHIPOBJECTMESSAGE6_H_*/
