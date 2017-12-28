/*
 * WearableObjectImplementation.cpp
 *
 *  Created on: 02/08/2009
 *      Author: victor
 */

#include "server/zone/objects/tangible/wearables/PsgArmorObject.h"
#include "server/zone/objects/tangible/wearables/WearableObject.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
namespace manufactureschematic {
namespace craftingvalues {
class CraftingValues;
}  // namespace craftingvalues
}  // namespace manufactureschematic
}  // namespace objects
namespace packets {
namespace scene {
class AttributeListMessage;
}  // namespace scene
}  // namespace packets
}  // namespace zone
}  // namespace server


void PsgArmorObjectImplementation::initializeTransientMembers() {
	WearableObjectImplementation::initializeTransientMembers();

	setLoggingName("PsgArmorObject");
}

void PsgArmorObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {

}

void PsgArmorObjectImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	/*
	 * Values available:	Range:
	 * sockets				0-0(novice artisan) (Don't use)
	 * hitpoints			1000-1000 (Don't Use)
	 */

	//if(firstUpdate) {

//	}

}
