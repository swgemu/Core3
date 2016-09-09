/*
 * WearableObjectImplementation.cpp
 *
 *  Created on: 02/08/2009
 *      Author: victor
 */

#include "server/zone/objects/tangible/wearables/PsgArmorObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"


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
