/*
 * FishingPoleObjectImplementation.cpp
 *
 *  Created on: Apr 12, 2010
 *      Author: swgemu
 */

#include "server/zone/objects/tangible/fishing/FishingBaitObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"

void FishingBaitObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm,object);
	// BAIT STATUS ONLY VISIBLE IN FISHING MENU
}

int FishingBaitObjectImplementation::getUseCount() {
	return TangibleObjectImplementation::getUseCount();
}
