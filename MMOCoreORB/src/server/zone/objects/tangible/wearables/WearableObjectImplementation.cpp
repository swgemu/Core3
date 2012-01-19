/*
 * WearableObjectImplementation.cpp
 *
 *  Created on: 02/08/2009
 *      Author: victor
 */

#include "WearableObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/objects/draftschematic/DraftSchematic.h"
#include "server/zone/objects/tangible/attachment/Attachment.h"


void WearableObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("WearableObject");
}

void WearableObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	if (socketsLeft() > 0)
		alm->insertAttribute("sockets", socketsLeft());

	if (craftersName != "") {
		alm->insertAttribute("crafter", craftersName);
	}

	if (craftersSerial != "") {
		alm->insertAttribute("serial_number", craftersSerial);
	}

	wearableSkillModMap.insertStatMods(alm);

}

void WearableObjectImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	/*
	 * Values available:	Range:
	 * sockets				0-0(novice artisan) (Don't use)
	 * hitpoints			1000-1000 (Don't Use)
	 */

	if(firstUpdate) {
		//generateSockets(schematic);
	}

}

void WearableObjectImplementation::generateSockets(ManufactureSchematic* schematic) {
/*
	ManagedReference<DraftSchematic* > draftSchematic = schematic->getDraftSchematic();
	ManagedReference<CreatureObject* > player = schematic->getCrafter();

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

	socketsGenerated = true;*/
}

void WearableObjectImplementation::applyAttachment(CreatureObject* player, Attachment* attachment) {
	if (socketsLeft() > 0) {
		AttachmentEntry entry;

		if (attachment->removeAttachment(player)) {

			for (int i = 0; i < attachment->getSkillModCount(); ++i) {
				String name = attachment->getSkillModName(i);
				int value = attachment->getSkillModValue(i);

				entry.add(name, value);

			}

			wearableSkillModMap.addAttachment(entry);

			if (isEquipped())
				setAttachmentMods(player);

		}

	}

}

void WearableObjectImplementation::setAttachmentMods(CreatureObject* player, bool remove) {
	if (player == NULL)
		return;

	for (int i = 0; i < wearableSkillModMap.getActiveSkillModCount(); ++i) {
		String name = wearableSkillModMap.getActiveSkillModKey(i);
		int value = wearableSkillModMap.getActiveSkillModValue(name);

		if (!remove)
			player->addSkillMod(name, value, true);
		else
			player->addSkillMod(name, -value, true);
	}
}

bool WearableObjectImplementation::isEquipped() {
	ManagedReference<SceneObject*> parent = getParent();
	if (parent != NULL && parent->isPlayerCreature())
		return true;

	return false;
}

