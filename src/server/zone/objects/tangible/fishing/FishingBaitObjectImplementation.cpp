/*
 * FishingPoleObjectImplementation.cpp
 *
 *  Created on: Apr 12, 2010
 *      Author: swgemu
 */

#include "FishingBaitObject.h"
#include "../TangibleObject.h"
#include "../../scene/SceneObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"


void FishingBaitObjectImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {
	TangibleObjectImplementation::fillAttributeList(alm,object);
	// BAIT STATUS ONLY VISIBLE IN FISHING MENU
}
