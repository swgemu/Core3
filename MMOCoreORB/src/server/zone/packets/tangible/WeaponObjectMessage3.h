/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef WEAPONOBJECTMESSAGE3_H_
#define WEAPONOBJECTMESSAGE3_H_

#include "TangibleObjectMessage3.h"

#include "server/zone/objects/tangible/weapon/WeaponObject.h"

class WeaponObjectMessage3 : public TangibleObjectMessage3 {
public:
	WeaponObjectMessage3(WeaponObject* weao)
			: TangibleObjectMessage3(weao, 0x5745414F, 0x11) {
		/*insertInt(0xE8000000);

		insertInt(3);
		insertInt(0);
		insertInt(0);

		insertFloat(5);

		insertInt(0);
		insertInt(0);
		insertInt(0);*/

		setSize();
	}

};

#endif /*WEAPONOBJECTMESSAGE3_H_*/
