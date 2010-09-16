/*
 * WearableObjectImplementation.cpp
 *
 *  Created on: 02/08/2009
 *      Author: victor
 */

#include "PsgArmorObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/draftschematic/DraftSchematic.h"


void PsgArmorObjectImplementation::initializeTransientMembers() {
	WearableObjectImplementation::initializeTransientMembers();

	setLoggingName("PsgArmorObject");
}

void PsgArmorObjectImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {

}

void PsgArmorObjectImplementation::updateCraftingValues(ManufactureSchematic* schematic) {
	/*
	 * Values available:	Range:
	 * sockets				0-0(novice artisan) (Don't use)
	 * hitpoints			1000-1000 (Don't Use)
	 */

	if(schematic->isFirstCraftingUpdate()) {

	}

}
