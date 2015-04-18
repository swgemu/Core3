/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FACTORYCRATEOBJECTDELTAMESSAGE3_H_
#define FACTORYCRATEOBJECTDELTAMESSAGE3_H_

#include "../../packets/DeltaMessage.h"

#include "server/zone/objects/factorycrate/FactoryCrate.h"

class FactoryCrateObjectDeltaMessage3 : public DeltaMessage {
	FactoryCrate* tano;

public:
	FactoryCrateObjectDeltaMessage3(FactoryCrate* ta, uint32 objType = 0x46435954)
			: DeltaMessage(ta->getObjectID(), objType, 3) {
		tano = ta;
	}

	void setQuantity(int quantity) {

		addIntUpdate(7, quantity);
	}
};

#endif /*FACTORYCRATEOBJECTDELTAMESSAGE3_H_*/
