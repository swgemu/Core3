/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHIPOBJECTMESSAGE3_H_
#define SHIPOBJECTMESSAGE3_H_

#include "server/zone/packets/tangible/TangibleObjectMessage3.h"
#include "server/zone/objects/ship/ShipObject.h"

class ShipObjectMessage3 : public TangibleObjectMessage3 {
public:
	ShipObjectMessage3(ShipObject* ship)
			: TangibleObjectMessage3(ship, 0x53484950, 0x16) {

                //11
		insertFloat(ship->getSlip()); //?Speed or Acceleration?

        
		insertFloat(ship->getChassisCurrentHealth()); //chassis cur
		insertFloat(ship->getChassisMaxHealth()); //chassis max

		insertInt(ship->getShipNameCRC()); //chassis type

        ship->getMaxArmorMap()->insertToMessage(this); //15
        ship->getCurrentArmorMap()->insertToMessage(this);
        ship->getCurrentHitpointsMap()->insertToMessage(this);
        ship->getMaxHitpointsMap()->insertToMessage(this);
        ship->getComponentOptionsMap()->insertToMessage(this); // 19


		insertFloat(ship->getMaxFrontShield()); //front shield max
		insertFloat(ship->getMaxRearShield()); // back shield max

		setSize();
	}
};

#endif /*SHIPOBJECTMESSAGE3_H_*/
