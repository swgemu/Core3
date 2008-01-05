#ifndef SHIPOBJECTMESSAGE6_H_
#define SHIPOBJECTMESSAGE6_H_

#include "../../packets/BaseLineMessage.h"

#include "../../objects/ship/ShipObject.h"
#include "../../objects/tangible/component/ShipComponent.h"

/*
 * This packet is in active reversing. Subject to differ from documentation until final revision
 * is worked out.
 */

class ShipObjectMessage6 : public BaseLineMessage {
public:
	ShipObjectMessage6(ShipObject* ship)
			: BaseLineMessage(ship->getObjectID(), 0x53484950, 6, 0x18) {
				
		insertInt(0x8B);
		
		insertInt(0);
		insertInt(0);
		insertShort(0);
		
		insertFloat(0);
		insertFloat(1.0f); //min speed
		insertFloat(50.0f);
		insertFloat(50.0f);
		
		//first 3 have something to do with pitch, yaw, and roll
		insertFloat(10.472f);
		insertFloat(10.472f);
		insertFloat(5.23599f); //note: 1/2 of first 2 floats
		insertFloat(0.753982f);
		insertFloat(ship->getMaxSpeed()); //this value * 10 = max speed
		
		insertLong(ship->getObjectID());
		
		insertInt(0); //LENGTH FOR SOMETHING, swg will allocate this number of bytes
		
		//(list?)
		insertInt(0);
		insertInt(0);
		
		insertCrcList(ship);
		
		//pretty sure these shorts are 2 int's for lists.
		insertShort(0);
		insertShort(0);
		insertShort(0);
		insertShort(0);
		
		insertFloat(ship->getFrontshieldCur());
		insertFloat(ship->getBackshieldCur());
		
		insertInt(0); //?
	}
	
	void insertCrcList(ShipObject* ship) {
		/*
		List struct:
		INT: List Size
		INT: Update Count
		{
    		BYTE: ??
    		INT: Component Index
    		INT: Component CRC
		}
		*/
		insertInt(ship->getActiveComponentListSize());
		insertInt(ship->getNextCrcUpdateCnt());
		for(int i = 0; i < ship->getComponentListSize(); i++) {
			ShipComponent* tsc = new ShipComponent();
			tsc = ship->getComponent(i);
			if(tsc->getComponentCrc() != 0) {
				insertByte(0); //?
				insertInt(i);
				insertInt(tsc->getComponentCrc());
			}
			delete tsc;
		}
	}
};

#endif /*SHIPOBJECTMESSAGE6_H_*/
