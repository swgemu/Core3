#ifndef SHIPOBJECTMESSAGE4_H_
#define SHIPOBJECTMESSAGE4_H_

#include "../../packets/BaseLineMessage.h"

#include "../../objects/ship/ShipObject.h"
#include "../../objects/tangible/component/ShipComponent.h"

/*
 * This packet is in active reversing. Subject to differ from documentation until final revision
 * is worked out.
 */

class ShipObjectMessage4 : public BaseLineMessage {
public:
	ShipObjectMessage4(ShipObject* ship)
			: BaseLineMessage(ship->getObjectID(), 0x53484950, 4, 0x06) {
				
		insertFloat(ship->getTotalMass());
		
		insertFloat(0.95f);
		insertFloat(ship->getWeaponCharge());
		insertInt(0);
		
		insertInt(0x00);
		insertInt(0x00);
		
		/* (blank list) - todo: research on the effect of these lists.
			insertInt(0x01);
			insertInt(0x01);
			insertByte(0);
			insertInt(0x0F);
			insertFloat(1.0f);
		*/
		
		insertInt(0);
		insertInt(0);
		
	}
		
};

#endif /*SHIPOBJECTMESSAGE4_H_*/
