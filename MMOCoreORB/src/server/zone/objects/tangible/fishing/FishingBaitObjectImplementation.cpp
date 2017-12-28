/*
 * FishingPoleObjectImplementation.cpp
 *
 *  Created on: Apr 12, 2010
 *      Author: swgemu
 */

#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/tangible/fishing/FishingBaitObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
}  // namespace objects
namespace packets {
namespace scene {
class AttributeListMessage;
}  // namespace scene
}  // namespace packets
}  // namespace zone
}  // namespace server

void FishingBaitObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm,object);
	// BAIT STATUS ONLY VISIBLE IN FISHING MENU
}

int FishingBaitObjectImplementation::getUseCount() {
	return TangibleObjectImplementation::getUseCount();
}
