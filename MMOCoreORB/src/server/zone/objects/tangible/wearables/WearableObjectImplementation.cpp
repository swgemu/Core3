/*
 * WearableObjectImplementation.cpp
 *
 *  Created on: 02/08/2009
 *      Author: victor
 */

#include "WearableObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/draftschematic/DraftSchematic.h"


void WearableObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("WearableObject");
}

void WearableObjectImplementation::updateCraftingValues(ManufactureSchematic* schematic) {
	/*
	 * Values available:	Range:
	 * sockets				0-0(novice artisan) (Don't use)
	 * hitpoints			1000-1000 (Don't Use)
	 */

	if(!socketsGenerated) {
		generateSockets(schematic);
	}

}

void WearableObjectImplementation::generateSockets(ManufactureSchematic* schematic) {

	ManagedReference<DraftSchematic* > draftSchematic = schematic->getDraftSchematic();
	ManagedReference<PlayerCreature* > player = schematic->getCrafter();

	String assemblySkill = draftSchematic->getAssemblySkill();
	// Get assembly points from skill

	if (player == NULL) {

		setMaxSockets(0);

	} else {

		int skill = player->getSkillMod(assemblySkill) * 2; // 0 to 250 max
		int luck = System::random(player->getSkillMod("luck") + player->getSkillMod("force_luck")); //0 to 250
		int random = (System::random(750)) - 250; // -250 to 500

		float roll = System::random(skill + luck + random);

		int generatedCount = int(float(MAXSOCKETS * roll) / float(MAXSOCKETS * 100));

		if (generatedCount > MAXSOCKETS)
			generatedCount = MAXSOCKETS;
		if (generatedCount < 0)
			generatedCount = 0;

		setMaxSockets(generatedCount);
	}
}
