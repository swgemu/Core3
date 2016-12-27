/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INTANGIBLEOBJECTDELTAMESSAGE3_H_
#define INTANGIBLEOBJECTDELTAMESSAGE3_H_

#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"

class HarvesterObjectDeltaMessage3 : public DeltaMessage {
	HarvesterObject* haro;
	
public:
	HarvesterObjectDeltaMessage3(HarvesterObject* ho)
			: DeltaMessage(ho->getObjectID(), 0x4F4E5449, 3) {
		haro = ho;
	}

	void updateDamage(uint32 value) {
		haro->setConditionDamage(value);
		addIntUpdate(0x0A, value);
	}	
	
};

#endif /*INTANGIBLEOBJECTDELTAMESSAGE3_H_*/

