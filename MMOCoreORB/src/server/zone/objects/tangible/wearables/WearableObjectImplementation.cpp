/*
 * WearableObjectImplementation.cpp
 *
 *  Created on: 02/08/2009
 *      Author: victor
 */

#include "server/zone/objects/tangible/wearables/WearableObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/draftschematic/DraftSchematic.h"
#include "server/zone/objects/tangible/attachment/Attachment.h"
#include "server/zone/managers/skill/SkillModManager.h"

typedef VectorMapEntry<String,int> Mod;

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

	//Anti Decay Kit
	if(hasAntiDecayKit() && !isArmorObject()){
		alm->insertAttribute("@veteran_new:antidecay_examine_title", "@veteran_new:antidecay_examine_text");
	}

}

void WearableObjectImplementation::updateCraftingValues(CraftingValues* values, bool initialUpdate) {
	/*
	 * Values available:	Range:
	 * sockets				0-0(novice artisan) (Don't use)
	 * hitpoints			1000-1000 (Don't Use)
	 */
	if(initialUpdate) {
		if(values->hasProperty("sockets") && values->getCurrentValue("sockets") >= 0)
			generateSockets(values);
	}
}

void WearableObjectImplementation::generateSockets(CraftingValues* craftingValues) {

	if (socketsGenerated) {
		return;
	}

	int skill = 0;
	int luck = 0;

	if (craftingValues != NULL) {
		ManagedReference<ManufactureSchematic*> manuSchematic = craftingValues->getManufactureSchematic();
		if(manuSchematic != NULL) {
			ManagedReference<DraftSchematic*> draftSchematic = manuSchematic->getDraftSchematic();
			ManagedReference<CreatureObject*> player = manuSchematic->getCrafter();

			if (player != NULL && draftSchematic != NULL) {
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

	// TODO: remove this backwards compatibility fix at next wipe. Only usedSocketCount variable should be used.
	objectCreatedPreUsedSocketCountFix = false;
	usedSocketCount = 0;

	socketCount = generatedCount;

	socketsGenerated = true;
}

int WearableObjectImplementation::socketsUsed() {
	// TODO: remove this backwards compatibility fix at next wipe. Only usedSocketCount variable should be used.
	if (objectCreatedPreUsedSocketCountFix) {
		return wearableSkillMods.size() - modsNotInSockets;
	} else {
		return usedSocketCount;
	}
}

void WearableObjectImplementation::applyAttachment(CreatureObject* player,
		Attachment* attachment) {

	if (!isASubChildOf(player))
		return;

	if (socketsLeft() > 0) {

		Locker locker(player);

		if (isEquipped()) {
			removeSkillModsFrom(player);
		}

		if (wearableSkillMods.size() < 6) {
			HashTable<String, int>* mods = attachment->getSkillMods();
			HashTableIterator<String, int> iterator = mods->iterator();
			
			String statName;
			int newValue;

			// Mirror the HashTable to a simple Vector so we can sort it
			Vector< Mod > allMods;
			for( int i = 0; i < mods->size(); i++){
				iterator.getNextKeyAndValue(statName, newValue);
				allMods.add( Mod( statName, newValue ) );
			}

			// We want to pick the highest mod first and, in the event of a tie, favor
			// mods listed first on the SEA. We need a descending sort, that maintains the relative
			// order of tied mods. Basic bubble sort implementation:
			for( int i = 0; i < allMods.size(); i++ ){
				for ( int j = 0; j < allMods.size() - 1; j++ ){
					if ( allMods.elementAt(j+1).getValue() > allMods.elementAt(j).getValue()) {
						Mod temp = allMods.elementAt(j);
						allMods.set(j, allMods.elementAt(j+1) );
						allMods.set(j+1, temp);
					}
				}
			}

			// Select the next mod in the SEA, sorted high-to-low. If that skill mod is already on the
			// wearable, with higher or equal value, don't apply and continue. Break once one mod
			// is applied.
			for( int i = 0; i < allMods.size(); i++ ) {
				String modName = allMods.elementAt(i).getKey();
				int modValue = allMods.elementAt(i).getValue();

				int existingValue = -26;
				if(wearableSkillMods.contains(modName))
					existingValue = wearableSkillMods.get(modName);

				if( modValue > existingValue) {
					wearableSkillMods.put( modName, modValue );
					break;
				}
			}

		}

		usedSocketCount++;

		attachment->destroyObjectFromWorld(true);
		attachment->destroyObjectFromDatabase(true);

		if (isEquipped()) {
			applySkillModsTo(player);
		}
	}
}

void WearableObjectImplementation::applySkillModsTo(CreatureObject* creature) {
	if (creature == NULL) {
		return;
	}

	for (int i = 0; i < wearableSkillMods.size(); ++i) {
		String name = wearableSkillMods.elementAt(i).getKey();
		int value = wearableSkillMods.get(name);

		if (!SkillModManager::instance()->isWearableModDisabled(name))
			creature->addSkillMod(SkillModManager::WEARABLE, name, value, true);
	}

	SkillModManager::instance()->verifyWearableSkillMods(creature);
}

void WearableObjectImplementation::removeSkillModsFrom(CreatureObject* creature) {
	if (creature == NULL) {
		return;
	}

	for (int i = 0; i < wearableSkillMods.size(); ++i) {
		String name = wearableSkillMods.elementAt(i).getKey();
		int value = wearableSkillMods.get(name);

		if (!SkillModManager::instance()->isWearableModDisabled(name))
			creature->removeSkillMod(SkillModManager::WEARABLE, name, value, true);
	}

	SkillModManager::instance()->verifyWearableSkillMods(creature);
}

bool WearableObjectImplementation::isEquipped() {
	ManagedReference<SceneObject*> parent = getParent().get();
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

