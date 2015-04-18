/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATUREOBJECTDELTAMESSAGE1_H_
#define CREATUREOBJECTDELTAMESSAGE1_H_

#include "../../packets/DeltaMessage.h"
#include "../../objects/creature/CreatureAttribute.h"

class CreatureObjectDeltaMessage1 : public DeltaMessage {
	CreatureObjectImplementation* creo;

public:
	CreatureObjectDeltaMessage1(CreatureObjectImplementation* cr)
			: DeltaMessage(cr->getObjectID(), 0x4352454F, 1) {
		creo = cr;
	}

	void updateBankCredits() {
		startUpdate(0x00);
		insertInt(creo->getBankCredits());
	}

	void updateCashCredits() {
		startUpdate(0x01);
		insertInt(creo->getCashCredits());
	}



};

#endif /*CREATUREOBJECTDELTAMESSAGE1_H_*/
