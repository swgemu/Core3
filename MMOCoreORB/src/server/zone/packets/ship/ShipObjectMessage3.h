/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHIPOBJECTMESSAGE3_H_
#define SHIPOBJECTMESSAGE3_H_

#include "../../packets/tangible/TangibleObjectMessage3.h"
#include "server/zone/objects/ship/ShipObject.h"

class ShipObjectMessage3 : public TangibleObjectMessage3 {
public:
	ShipObjectMessage3(ShipObject* ship)
			: TangibleObjectMessage3(ship, 0x53484950, 0x16) {

		insertFloat(10.9f); //?Speed or Acceleration?

		insertFloat(800.f); //chassis cur
		insertFloat(800.f); //chassis max

		insertInt(0x16B73FE9); //unk

		//armor
		/*insertInt(0);
			insertInt(0);*/

		//Float 100
		insertDummyList(0x42c80000);//const Archive::AutoDeltaPackedMap<int,float,Archive::DefaultObjectType>::`vftable

		//max armor
		/*insertInt(0);
		insertInt(0);*/

		//Float 100
		insertDummyList(0x42c80000);

		//cur hit
		/*insertInt(0);
			insertInt(0);*/

		//float 200
		insertDummyList(0x43480000);

		//max hit
		/*insertInt(0);
		insertInt(0);*/
		//float 200
		insertDummyList(0x43480000);

		//unk
		/*insertInt(0);
		insertInt(0);*/

		insertDummyList(0x2);

		insertFloat(301.f); //front shield max
		insertFloat(302.f); // back shield max

		setSize();
	}

	void insertDummyList(int val) {
		insertInt(7);
		insertInt(7);

		insertByte(0);
		insertInt(0);
		insertInt(val); // 0xDC, 0xBF, 0xBD, 0x9A,

		insertByte(0);
		insertInt(1);
		insertInt(val); // 0x05, 0xC7, 0xA0, 0x35,

		insertByte(0);
		insertInt(2);
		insertInt(val); // 0xBE, 0x17, 0x32, 0xE7

		insertByte(0);
		insertInt(4);
		insertInt(val); // 0x9E, 0x60, 0xCB, 0xE1,

		insertByte(0);
		insertInt(5);
		insertInt(val); // 0x9E, 0x60, 0xCB, 0xE1,

		insertByte(0);
		insertInt(6);
		insertInt(val); // 0xEE, 0xD6, 0xCE, 0x20,

		insertByte(0);
		insertInt(0x0f);
		insertInt(val); //0x3D, 0x3C, 0x82, 0x2C,
	}
};

#endif /*SHIPOBJECTMESSAGE3_H_*/
