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
#include "server/zone/managers/skill/SkillModManager.h"

void WearableObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();
	setLoggingName("WearableObject");
}

void WearableObjectImplementation::fillAttributeList(AttributeListMessage* alm,
		CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	if (socketsLeft() > 0)
		alm->insertAttribute("sockets", socketsLeft());

	for(int i = 0; i < wearableSkillMods.size(); ++i) {
		String key = wearableSkillMods.elementAt(i).getKey();
		String statname = "cat_skill_mod_bonus.@stat_n:" + key;
		int value = wearableSkillMods.get(key);

		if (value > 0)
			alm->insertAttribute(statname, value);
	}
}

void WearableObjectImplementation::updateCraftingValues(CraftingValues* values, bool initialUpdate) {
	/*
	 * Values available:	Range:
	 * sockets				0-0(novice artisan) (Don't use)
	 * hitpoints			1000-1000 (Don't Use)
	 */
	if(initialUpdate) {
		if(values->hasProperty("sockets"))
			generateSockets(values);
	}
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
				skill = player->getSkillMod(assemblySkill) * 2.5; // 0 to 250 max
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


	socketCount = generatedCount;

	socketsGenerated = true;
}

int WearableObjectImplementation::socketsUsed() {
	return wearableSkillMods.size();
}

void WearableObjectImplementation::applyAttachment(CreatureObject* player,
		Attachment* attachment) {

	if (socketsLeft() > 0) {

		if (isEquipped())
			setAttachmentMods(player, true, false);

		VectorMap<String, int>* mods = attachment->getSkillMods();

		VectorMap<short, SortedVector<String> > reverseMods;

		for(int i = 0; i < mods->size(); ++i) {

			short value = mods->get(i);
			if(!reverseMods.contains(value)) {
				SortedVector<String> newSorted;
				reverseMods.put(value, newSorted);
			}

			SortedVector<String>* stats = &reverseMods.get(value);

			stats->add(mods->elementAt(i).getKey());
		}

		for(int i = reverseMods.size() - 1; i >= 0; --i) {

			SortedVector<String>* stats = &reverseMods.elementAt(i).getValue();
			int value = reverseMods.elementAt(i).getKey();

			String statName = "";

			for(int j = 0; j < stats->size(); ++j) {

				statName = stats->get(j);

				if(!wearableSkillMods.contains(statName))
					break;

				statName = "";
			}

			if(!statName.isEmpty()) {
				wearableSkillMods.put(statName, value);
				break;
			}
		}

		attachment->destroyObjectFromWorld(true);

		if (isEquipped())
			setAttachmentMods(player);

	}

}

void WearableObjectImplementation::setAttachmentMods(CreatureObject* player,
		bool remove, bool doCheck) {
	if (player == NULL)
		return;

	for (int i = 0; i < wearableSkillMods.size(); ++i) {
		String name = wearableSkillMods.elementAt(i).getKey();
		int value = wearableSkillMods.get(name);

		if (!remove)
			player->addSkillMod(SkillModManager::WEARABLE, name, value, true);
		else
			player->removeSkillMod(SkillModManager::WEARABLE, name, value, true);
	}

	if(doCheck)
		SkillModManager::instance()->verifyWearableSkillMods(player);
}

bool WearableObjectImplementation::isEquipped() {
	ManagedReference<SceneObject*> parent = getParent();
	if (parent != NULL && parent->isPlayerCreature())
		return true;

	return false;
}

String WearableObjectImplementation::repairAttempt(int repairChance) {

	String message = "@error_message:";

	if(repairChance < 25) {
		message += "sys_repair_failed";
		setMaxCondition(1, true);
		setConditionDamage(0, true);
	} else if(repairChance < 50) {
		message += "sys_repair_imperfect";
		setMaxCondition(getMaxCondition() * .65f, true);
		setConditionDamage(0, true);
	} else if(repairChance < 75) {
		setMaxCondition(getMaxCondition() * .80f, true);
		setConditionDamage(0, true);
		message += "sys_repair_slight";
	} else {
		setMaxCondition(getMaxCondition() * .95f, true);
		setConditionDamage(0, true);
		message += "sys_repair_perfect";
	}

	return message;
}

