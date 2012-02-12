/*
 * WearableObjectImplementation.cpp
 *
 *  Created on: 02/08/2009
 *      Author: victor
 */

#include "WearableObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/draftschematic/DraftSchematic.h"
#include "server/zone/objects/tangible/attachment/Attachment.h"

void WearableObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("WearableObject");
}

void WearableObjectImplementation::fillAttributeList(AttributeListMessage* alm,
		CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	if (socketsLeft() > 0)
		alm->insertAttribute("sockets", socketsLeft());

	if (craftersName != "") {
		alm->insertAttribute("crafter", craftersName);
	}

	if (objectSerial != "") {
		alm->insertAttribute("serial_number", objectSerial);
	}

	wearableSkillModMap.insertStatMods(alm);

}

void WearableObjectImplementation::updateCraftingValues(CraftingValues* values, bool initialUpdate) {
	/*
	 * Values available:	Range:
	 * sockets				0-0(novice artisan) (Don't use)
	 * hitpoints			1000-1000 (Don't Use)
	 */
	if(initialUpdate)
		generateSockets(values);
}

void WearableObjectImplementation::generateSockets(CraftingValues* craftingValues) {

	int skill = 0;
	int luck = 0;

	if (craftingValues != NULL) {
		ManagedReference<ManufactureSchematic*> manuSchematic = craftingValues->getManufactureSchematic();
		if(manuSchematic != NULL) {
			ManagedReference<DraftSchematic*> draftSchematic = manuSchematic->getDraftSchematic();
			ManagedReference<CreatureObject*> player = manuSchematic->getCrafter();

			if (player != NULL || draftSchematic != NULL) {
				String assemblySkill = draftSchematic->getAssemblySkill();
				skill = player->getSkillMod(assemblySkill) * 2; // 0 to 250 max
				luck = System::random(player->getSkillMod("luck")
						+ player->getSkillMod("force_luck"));
			}
		}
	}

	int random = (System::random(750)) - 250; // -250 to 500

	float roll = System::random(skill + luck + random);

	int generatedCount = int(float(MAXSOCKETS * roll) / float(MAXSOCKETS * 100));

	if (generatedCount > MAXSOCKETS)
		generatedCount = MAXSOCKETS;
	if (generatedCount < 0)
		generatedCount = 0;

	setMaxSockets(generatedCount);

	socketsGenerated = true;
}

void WearableObjectImplementation::applyAttachment(CreatureObject* player,
		Attachment* attachment) {
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

void WearableObjectImplementation::setAttachmentMods(CreatureObject* player,
		bool remove) {
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

