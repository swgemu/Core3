/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHIPOBJECTMESSAGE4_H_
#define SHIPOBJECTMESSAGE4_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/ship/ShipObject.h"


class ShipObjectMessage4 : public BaseLineMessage {
public:
	ShipObjectMessage4(ShipObject* ship)
			: BaseLineMessage(ship->getObjectID(), 0x53484950, 4, 0x06) {

		insertFloat(0.80000001f); //mass
		insertFloat(512.f); //mass max

		insertFloat(100.f); // capacitor ?
		insertFloat(0); //float

		insertInt(0); //const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable'
		insertInt(0);

		setSize();
	}
		
};

#endif /*SHIPOBJECTMESSAGE4_H_*/
