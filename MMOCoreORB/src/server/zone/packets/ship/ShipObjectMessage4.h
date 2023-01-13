/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHIPOBJECTMESSAGE4_H_
#define SHIPOBJECTMESSAGE4_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/ship/ShipObject.h"


class ShipObjectMessage4 : public BaseLineMessage {
public:
	ShipObjectMessage4(ShipObject* ship) : BaseLineMessage(ship->getObjectID(), 0x53484950, 4, 0x06) {
		//ship->info(true) << "ShipObjectMessage4 sent";

		insertFloat(ship->getChassisMass()); // Current Mass
		insertFloat(ship->getChassisSpeed()); // Chassis Speed

		insertFloat(ship->getCapacitorEnergy()); // Cpacitor Energy
		insertFloat(ship->getBoosterEnergy()); // Booster Energy

		ship->getComponentRefireEfficiency()->insertToMessage(this);

		setSize();
	}
};

#endif /*SHIPOBJECTMESSAGE4_H_*/
