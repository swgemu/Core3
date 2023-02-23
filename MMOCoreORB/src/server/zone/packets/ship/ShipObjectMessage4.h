/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHIPOBJECTMESSAGE4_H_
#define SHIPOBJECTMESSAGE4_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

class ShipObjectMessage4 : public BaseLineMessage {
protected:
	enum index : int {
		currentMass = 0,
		chassisSpeed = 1,
		capacitorEnergy = 2,
		boosterEnergy = 3,
		componentRefireEfficiency = 4
	};

public:
	ShipObjectMessage4(ShipObject* ship) : BaseLineMessage(ship->getObjectID(), 0x53484950, 4, 5) {

		insertFloat(ship->getChassisMass());
		insertFloat(ship->getChassisSpeed());

		insertFloat(ship->getCapacitorEnergy());
		insertFloat(ship->getBoosterEnergy());

		ship->getComponentRefireEfficiency()->insertToMessage(this);

		setSize();
	}
};

#endif /*SHIPOBJECTMESSAGE4_H_*/
