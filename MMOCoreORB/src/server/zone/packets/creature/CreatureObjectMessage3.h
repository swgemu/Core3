/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATUREOBJECTMESSAGE3_H_
#define CREATUREOBJECTMESSAGE3_H_

#include "server/zone/packets/tangible/TangibleObjectMessage3.h"
#include "server/zone/objects/creature/CreatureObject.h"

class CreatureObjectMessage3 : public TangibleObjectMessage3 {
public:
	CreatureObjectMessage3(CreatureObject* creo)
			: TangibleObjectMessage3(creo, 0x4352454F, 0x12) {

		insertByte(creo->getPosture());
		insertByte(creo->getFactionRank()); // faction rank

		insertLong(creo->getCreatureLinkID()); // creature link id/ mount

		insertFloat(creo->getHeight());
		insertInt((int)creo->getShockWounds()); // BF

		insertLong(creo->getStateBitmask());

		DeltaVector<int>* wounds = creo->getWounds();
		wounds->insertToMessage(this);

		setSize();
	}

};

#endif /*CREATUREOBJECTMESSAGE3_H_*/
