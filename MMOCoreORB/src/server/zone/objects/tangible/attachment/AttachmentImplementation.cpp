/*
 * AttachmentImplementation.cpp
 *
 *  Created on: Mar 10, 2011
 *      Author: polonel
 */

#include "Attachment.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/managers/loot/LootManager.h"

void AttachmentImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("AttachmentObject");

}

void AttachmentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	int level = values->getMaxValue("creatureLevel");
	int roll = System::random(100);
	int modCount = 1;

	if(roll > 99)
		modCount += 2;

	if(roll < 5)
		modCount += 1;

	for(int i = 0; i < modCount; ++i) {
		//Mods can't be lower than -1 or greater than 25
		int max = MAX(-1, MIN(25, round(0.1f * level + 3)));
		int min = MAX(-1, MIN(25, round(0.075f * level - 1)));

		int mod = System::random(max - min) + min;

		if(mod == 0)
			mod = 1;

		String modName = server->getZoneServer()->getLootManager()->getRandomLootableMod();

		skillModMap.put(modName, mod);
	}
}

void AttachmentImplementation::initializeMembers() {
	if (gameObjectType == SceneObjectType::CLOTHINGATTACHMENT) {
		setOptionsBitmask(32, true);
		attachmentType = CLOTHINGTYPE;

	} else if (gameObjectType == SceneObjectType::ARMORATTACHMENT) {
		setOptionsBitmask(32, true);
		attachmentType = ARMORTYPE;

	}

}

void AttachmentImplementation::fillAttributeList(AttributeListMessage* msg, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(msg, object);

	StringBuffer name;
	for(int i = 0; i < skillModMap.size(); ++i) {

		name << "cat_skill_mod_bonus.@stat_n:" << skillModMap.elementAt(i).getKey();
		int value = skillModMap.elementAt(i).getValue();

		msg->insertAttribute(name.toString(), value);

		name.deleteAll();
	}

}
