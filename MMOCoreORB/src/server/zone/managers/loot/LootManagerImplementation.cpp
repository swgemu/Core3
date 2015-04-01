/*
 * LootManagerImplementation.cpp
 *
 *  Created on: Jun 20, 2011
 *      Author: Kyle
 */

#include "engine/engine.h"

#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/templates/LootItemTemplate.h"
#include "server/zone/templates/LootGroupTemplate.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "LootGroupMap.h"

void LootManagerImplementation::initialize() {
	lua = new Lua();
	lua->init();

	info("Loading configuration.");

	if(!loadConfigData()) {

		loadDefaultConfig();

		info("Failed to load configuration values. Using default.");
	}

	lootGroupMap = LootGroupMap::instance();
	lootGroupMap->initialize();

	info("Loaded " + String::valueOf(lootableArmorAttachmentMods.size()) + " lootable armor attachment stat mods.", true);
	info("Loaded " + String::valueOf(lootableClothingAttachmentMods.size()) + " lootable clothing attachment stat mods.", true);
	info("Loaded " + String::valueOf(lootableArmorMods.size()) + " lootable armor stat mods.", true);
	info("Loaded " + String::valueOf(lootableClothingMods.size()) + " lootable clothing stat mods.", true);
	info("Loaded " + String::valueOf(lootableOneHandedMeleeMods.size()) + " lootable one handed melee stat mods.", true);
	info("Loaded " + String::valueOf(lootableTwoHandedMeleeMods.size()) + " lootable two handed melee stat mods.", true);
	info("Loaded " + String::valueOf(lootableUnarmedMods.size()) + " lootable unarmed stat mods.", true);
	info("Loaded " + String::valueOf(lootablePistolMods.size()) + " lootable pistol stat mods.", true);
	info("Loaded " + String::valueOf(lootableRifleMods.size()) + " lootable rifle stat mods.", true);
	info("Loaded " + String::valueOf(lootableCarbineMods.size()) + " lootable carbine stat mods.", true);
	info("Loaded " + String::valueOf(lootablePolearmMods.size()) + " lootable polearm stat mods.", true);
	info("Loaded " + String::valueOf(lootableHeavyWeaponMods.size()) + " lootable heavy weapon stat mods.", true);
	info("Loaded " + String::valueOf(lootGroupMap->countLootItemTemplates()) + " loot items.", true);
	info("Loaded " + String::valueOf(lootGroupMap->countLootGroupTemplates()) + " loot groups.", true);

	info("Initialized.");
}

bool LootManagerImplementation::loadConfigFile() {
	return lua->runFile("scripts/managers/loot_manager.lua");
}

bool LootManagerImplementation::loadConfigData() {
	if (!loadConfigFile())
		return false;
	yellowChance = lua->getGlobalFloat("yellowChance");
	yellowModifier = lua->getGlobalFloat("yellowModifier");
	exceptionalChance = lua->getGlobalFloat("exceptionalChance");
	exceptionalModifier = lua->getGlobalFloat("exceptionalModifier");
	legendaryChance = lua->getGlobalFloat("legendaryChance");
	legendaryModifier = lua->getGlobalFloat("legendaryModifier");
	skillModChance = lua->getGlobalFloat("skillModChance");
	junkValueModifier = lua->getGlobalFloat("junkValueModifier");

	LuaObject dotAttributeTable = lua->getGlobalObject("randomDotAttribute");

	if (dotAttributeTable.isValidTable() && dotAttributeTable.getTableSize() > 0) {
		for (int i = 1; i <= dotAttributeTable.getTableSize(); ++i) {
			int value = dotAttributeTable.getIntAt(i);
			randomDotAttribute.put(value);
		}
		dotAttributeTable.pop();
	}

	LuaObject dotStrengthTable = lua->getGlobalObject("randomDotStrength");

	if (dotStrengthTable.isValidTable() && dotStrengthTable.getTableSize() > 0) {
		for (int i = 1; i <= dotStrengthTable.getTableSize(); ++i) {
			int value = dotStrengthTable.getIntAt(i);
			randomDotStrength.put(value);
		}
		dotStrengthTable.pop();
	}

	LuaObject dotDurationTable = lua->getGlobalObject("randomDotDuration");

	if (dotDurationTable.isValidTable() && dotDurationTable.getTableSize() > 0) {
		for (int i = 1; i <= dotDurationTable.getTableSize(); ++i) {
			int value = dotDurationTable.getIntAt(i);
			randomDotDuration.put(value);
		}
		dotDurationTable.pop();
	}

	LuaObject dotPotencyTable = lua->getGlobalObject("randomDotPotency");

	if (dotPotencyTable.isValidTable() && dotPotencyTable.getTableSize() > 0) {
		for (int i = 1; i <= dotPotencyTable.getTableSize(); ++i) {
			int value = dotPotencyTable.getIntAt(i);
			randomDotPotency.put(value);
		}
		dotPotencyTable.pop();
	}

	LuaObject dotUsesTable = lua->getGlobalObject("randomDotUses");

	if (dotUsesTable.isValidTable() && dotUsesTable.getTableSize() > 0) {
		for (int i = 1; i <= dotUsesTable.getTableSize(); ++i) {
			int value = dotUsesTable.getIntAt(i);
			randomDotUses.put(value);
		}
		dotUsesTable.pop();
	}

	LuaObject modsTable = lua->getGlobalObject("lootableArmorAttachmentStatMods");
	loadLootableMods( &modsTable, &lootableArmorAttachmentMods );

	modsTable = lua->getGlobalObject("lootableClothingAttachmentStatMods");
	loadLootableMods( &modsTable, &lootableClothingAttachmentMods );

	modsTable = lua->getGlobalObject("lootableArmorStatMods");
	loadLootableMods( &modsTable, &lootableArmorMods );

	modsTable = lua->getGlobalObject("lootableClothingStatMods");
	loadLootableMods( &modsTable, &lootableClothingMods );

	modsTable = lua->getGlobalObject("lootableOneHandedMeleeStatMods");
	loadLootableMods( &modsTable, &lootableOneHandedMeleeMods );

	modsTable = lua->getGlobalObject("lootableTwoHandedMeleeStatMods");
	loadLootableMods( &modsTable, &lootableTwoHandedMeleeMods );

	modsTable = lua->getGlobalObject("lootableUnarmedStatMods");
	loadLootableMods( &modsTable, &lootableUnarmedMods );

	modsTable = lua->getGlobalObject("lootablePistolStatMods");
	loadLootableMods( &modsTable, &lootablePistolMods );

	modsTable = lua->getGlobalObject("lootableRifleStatMods");
	loadLootableMods( &modsTable, &lootableRifleMods );

	modsTable = lua->getGlobalObject("lootableCarbineStatMods");
	loadLootableMods( &modsTable, &lootableCarbineMods );

	modsTable = lua->getGlobalObject("lootablePolearmStatMods");
	loadLootableMods( &modsTable, &lootablePolearmMods );

	modsTable = lua->getGlobalObject("lootableHeavyWeaponStatMods");
	loadLootableMods( &modsTable, &lootableHeavyWeaponMods );

	return true;
}

void LootManagerImplementation::loadLootableMods(LuaObject* modsTable, SortedVector<String>* mods ){

	if (!modsTable->isValidTable())
		return;

	for (int i = 1; i <= modsTable->getTableSize(); ++i) {
		String mod = modsTable->getStringAt(i);
		mods->put(mod);
	}

	modsTable->pop();

}

void LootManagerImplementation::loadDefaultConfig() {

}

void LootManagerImplementation::setInitialObjectStats(LootItemTemplate* templateObject, CraftingValues* craftingValues, TangibleObject* prototype) {
	SharedTangibleObjectTemplate* tanoTemplate = dynamic_cast<SharedTangibleObjectTemplate*>(prototype->getObjectTemplate());

	if (tanoTemplate != NULL) {
		Vector<String>* titles = tanoTemplate->getExperimentalGroupTitles();
		Vector<String>* props = tanoTemplate->getExperimentalSubGroupTitles();
		Vector<float>* mins = tanoTemplate->getExperimentalMin();
		Vector<float>* maxs = tanoTemplate->getExperimentalMax();
		Vector<short>* prec = tanoTemplate->getExperimentalPrecision();

		for (int i = 0; i < props->size(); ++i) {
			String title = titles->get(i);
			String property = props->get(i);

			if (craftingValues->hasProperty(property))
				continue;

			craftingValues->addExperimentalProperty(property, property, mins->get(i), maxs->get(i), prec->get(i), false, CraftingManager::LINEARCOMBINE);
			if (title == "null")
				craftingValues->setHidden(property);
		}
	}

	Vector<String>* customizationData = templateObject->getCustomizationStringNames();
	Vector<Vector<int> >* customizationValues = templateObject->getCustomizationValues();

	for (int i = 0; i < customizationData->size(); ++i) {
		String customizationString = customizationData->get(i);
		Vector<int>* values = &customizationValues->get(i);

		if (values->size() > 0) {
			int randomValue = values->get(System::random(values->size() - 1));

			prototype->setCustomizationVariable(customizationString, randomValue, false);
		}
	}
}

void LootManagerImplementation::setCustomObjectName(TangibleObject* object, LootItemTemplate* templateObject) {
	String customName = templateObject->getCustomObjectName();

	if (!customName.isEmpty()) {
		if (customName.charAt(0) == '@') {
			StringId stringId(customName);

			object->setObjectName(stringId);
		} else {
			object->setCustomObjectName(customName, false);
		}
	}
}

int LootManagerImplementation::calculateLootCredits(int level) {
	int maxcredits = (int) round((.03f * level * level) + (3 * level) + 50);
	int mincredits = (int) round((((float) maxcredits) * .5f) + (2.0f * level));

	int credits = mincredits + System::random(maxcredits - mincredits);

	return credits;
}

TangibleObject* LootManagerImplementation::createLootObject(LootItemTemplate* templateObject, int level, bool maxCondition) {

	if(level < 1)
		level = 1;

	if(level > 300)
		level = 300;

	String directTemplateObject = templateObject->getDirectObjectTemplate();

	ManagedReference<TangibleObject*> prototype = zoneServer->createObject(directTemplateObject.hashCode(), 2).castTo<TangibleObject*>();

	if (prototype == NULL) {
		error("could not create loot object: " + directTemplateObject);
		return NULL;
	}

	Locker objLocker(prototype);

	prototype->createChildObjects();

	String serial = craftingManager->generateSerial();
	prototype->setSerialNumber(serial);
	prototype->setJunkDealerNeeded(templateObject->getJunkDealerTypeNeeded());
	float junkMinValue = templateObject->getJunkMinValue() * junkValueModifier;
	float junkMaxValue = templateObject->getJunkMaxValue() * junkValueModifier;
	float fJunkValue = junkMinValue+System::random(junkMaxValue-junkMinValue);

	if (level>0 && templateObject->getJunkDealerTypeNeeded()>1){
		fJunkValue=fJunkValue + (fJunkValue * ((float)level / 100)); // This is the loot value calculation if the item has a level
	}
	CraftingValues craftingValues = templateObject->getCraftingValuesCopy();

	setInitialObjectStats(templateObject, &craftingValues, prototype);

	setCustomObjectName(prototype, templateObject);

	float excMod = 1.0;

	if (level >= 50 && System::random(legendaryChance) >= legendaryChance - floor((level-50)/2 + 0.5)) {
			UnicodeString newName = prototype->getDisplayedName() + " (Legendary)";
			prototype->setCustomObjectName(newName, false);

			excMod = legendaryModifier;

			prototype->addMagicBit(false);
	} else if (level >= 50 && System::random(exceptionalChance) >= exceptionalChance - floor((level-50)/2 + 0.5)) {
		UnicodeString newName = prototype->getDisplayedName() + " (Exceptional)";
		prototype->setCustomObjectName(newName, false);

		excMod = exceptionalModifier;

		prototype->addMagicBit(false);
	}
	String subtitle;
	bool yellow = false;

	for (int i = 0; i < craftingValues.getExperimentalPropertySubtitleSize(); ++i) {
		subtitle = craftingValues.getExperimentalPropertySubtitle(i);

		if (subtitle == "hitpoints" || subtitle == "maxrange") {
			if(!(prototype->isComponent())) {
				continue;
			}
		}

		float min = craftingValues.getMinValue(subtitle);
		float max = craftingValues.getMaxValue(subtitle);

		if (min == max)
			continue;

		if (subtitle != "useCount" &&
				subtitle != "quantity" &&
				subtitle != "charges" &&
				subtitle != "uses" &&
				subtitle != "charge") {

			float minMod = (max > min) ? 2000.f : -2000.f;
			float maxMod = (max > min) ? 500.f : -500.f;

			if (max > min && min >= 0) { // Both max and min non-negative, max is higher
				min = ((min * level / minMod) + min) * excMod;
				max = ((max * level / maxMod) + max) * excMod;

			} else if (max > min && max <= 0) { // Both max and min are non-positive, max is higher
				minMod *= -1;
				maxMod *= -1;
				min = ((min * level / minMod) + min) / excMod;
				max = ((max * level / maxMod) + max) / excMod;

			} else if (max > min) { // max is positive, min is negative
				minMod *= -1;
				min = ((min * level / minMod) + min) / excMod;
				max = ((max * level / maxMod) + max) * excMod;

			} else if (max < min && max >= 0) { // Both max and min are non-negative, min is higher
				min = ((min * level / minMod) + min) / excMod;
				max = ((max * level / maxMod) + max) / excMod;

			} else if (max < min && min <= 0) { // Both max and min are non-positive, min is higher
				minMod *= -1;
				maxMod *= -1;
				min = ((min * level / minMod) + min) * excMod;
				max = ((max * level / maxMod) + max) * excMod;

			} else { // max is negative, min is positive
				maxMod *= -1;
				min = ((min * level / minMod) + min) / excMod;
				max = ((max * level / maxMod) + max) * excMod;
			}
		} else {
			if (excMod != 1.0) {
				min *= yellowModifier;
				max *= yellowModifier;
			}
		}

		if (excMod == 1.0 && (yellowChance == 0 || System::random(yellowChance) == 0)) {
			if (max > min && min >= 0) {
				min *= yellowModifier;
				max *= yellowModifier;
			} else if (max > min && max <= 0) {
				min /= yellowModifier;
				max /= yellowModifier;
			} else if (max > min) {
				min /= yellowModifier;
				max *= yellowModifier;
			} else if (max < min && max >= 0) {
				min /= yellowModifier;
				max /= yellowModifier;
			} else if (max < min && min <= 0) {
				min *= yellowModifier;
				max *= yellowModifier;
			} else {
				min /= yellowModifier;
				max *= yellowModifier;
			}

			yellow = true;
		}

		craftingValues.setMinValue(subtitle, min);
		craftingValues.setMaxValue(subtitle, max);

		float percentage = System::random(10000) / 10000.f;

		craftingValues.setCurrentPercentage(subtitle, percentage);
	}

	if (yellow) {
		prototype->addMagicBit(false);
		prototype->setJunkValue((int)(fJunkValue * 1.25));
	}else{
		if (excMod==1){
			prototype->setJunkValue((int)(fJunkValue));
		}else{
			prototype->setJunkValue((int)(fJunkValue * (excMod/2)));
		}
	}

	// Use percentages to recalculate the values
	craftingValues.recalculateValues(false);

	craftingValues.addExperimentalProperty("creatureLevel", "creatureLevel", level, level, 0, false, CraftingManager::LINEARCOMBINE);
	craftingValues.setHidden("creatureLevel");

	//check weapons and weapon components for min damage > max damage
	if (prototype->isComponent() || prototype->isWeaponObject()) {
		if (craftingValues.hasProperty("mindamage") && craftingValues.hasProperty("maxdamage")) {
			float oldMin = craftingValues.getCurrentValue("mindamage");
			float oldMax = craftingValues.getCurrentValue("maxdamage");

			if (oldMin > oldMax) {
				craftingValues.setCurrentValue("mindamage", oldMax);
				craftingValues.setCurrentValue("maxdamage", oldMin);
			}
		}
	}

	// Add Dots to weapon objects.
	addStaticDots(prototype, templateObject, level);
	addRandomDots(prototype, templateObject, level, excMod);

	setSkillMods(prototype, templateObject, level, excMod);

	setSockets(prototype, &craftingValues);

	// Update the Tano with new values
	prototype->updateCraftingValues(&craftingValues, true);

	//add some condition damage where appropriate
	if (!maxCondition)
		addConditionDamage(prototype, &craftingValues);

	return prototype;
}

void LootManagerImplementation::addConditionDamage(TangibleObject* loot, CraftingValues* craftingValues) {
	if (!loot->isWeaponObject() && !loot->isArmorObject())
		return;

	float min = 0;

	if(loot->isWeaponObject())
		min = craftingValues->getMinValue("hitpoints");

	if(loot->isArmorObject())
		min = craftingValues->getMinValue("armor_integrity");

	float damage = (float) System::random(min / 3);

	loot->setConditionDamage(damage);
}

void LootManagerImplementation::setSkillMods(TangibleObject* object, LootItemTemplate* templateObject, int level, float excMod) {
	if (!object->isWeaponObject() && !object->isWearableObject())
		return;

	VectorMap<String, int>* skillMods = templateObject->getSkillMods();
	VectorMap<String, int> additionalMods;

	bool yellow = false;

	if (System::random(skillModChance / excMod) == 0) {
		// if it has a skillmod the name will be yellow
		yellow = true;
		int modCount = 1;
		int roll = System::random(100);

		if(roll > (100 - excMod))
			modCount += 2;

		if(roll < (5 * excMod))
			modCount += 1;

		for(int i = 0; i < modCount; ++i) {
			//Mods can't be lower than -1 or greater than 25
			int max = MAX(-1, MIN(25, round(0.1f * level + 3)));
			int min = MAX(-1, MIN(25, round(0.075f * level - 1)));

			int mod = System::random(max - min) + min;

			if(mod == 0)
				mod = 1;

			String modName = getRandomLootableMod( object->getGameObjectType() );
			if( !modName.isEmpty() )
				additionalMods.put(modName, mod);
		}
	}

	if (yellow)
		object->addMagicBit(false);

	if (object->isWearableObject()) {
		ManagedReference<WearableObject*> wearableObject = cast<WearableObject*>(object);

		for (int i = 0; i < additionalMods.size(); i++) {
			wearableObject->addSkillMod(SkillModManager::WEARABLE, additionalMods.elementAt(i).getKey(), additionalMods.elementAt(i).getValue());
		}

		for (int i = 0; i < skillMods->size(); i++) {
			wearableObject->addSkillMod(SkillModManager::WEARABLE, skillMods->elementAt(i).getKey(), skillMods->elementAt(i).getValue());
		}
	} else if (object->isWeaponObject()) {
		ManagedReference<WeaponObject*> weaponObject = cast<WeaponObject*>(object);

		for (int i = 0; i < additionalMods.size(); i++) {
			weaponObject->addSkillMod(SkillModManager::WEARABLE, additionalMods.elementAt(i).getKey(), additionalMods.elementAt(i).getValue());
		}

		for (int i = 0; i < skillMods->size(); i++) {
			weaponObject->addSkillMod(SkillModManager::WEARABLE, skillMods->elementAt(i).getKey(), skillMods->elementAt(i).getValue());
		}
	}
}

String LootManagerImplementation::getRandomLootableMod( unsigned int sceneObjectType ) {
	if( sceneObjectType == SceneObjectType::ARMORATTACHMENT ){
		return lootableArmorAttachmentMods.get(System::random(lootableArmorAttachmentMods.size() - 1));
	}
	else if( sceneObjectType == SceneObjectType::CLOTHINGATTACHMENT ){
		return lootableClothingAttachmentMods.get(System::random(lootableClothingAttachmentMods.size() - 1));
	}
	else if( sceneObjectType == SceneObjectType::ARMOR || sceneObjectType == SceneObjectType::BODYARMOR ||
			 sceneObjectType == SceneObjectType::HEADARMOR || sceneObjectType == SceneObjectType::MISCARMOR ||
			 sceneObjectType == SceneObjectType::LEGARMOR || sceneObjectType == SceneObjectType::ARMARMOR ||
			 sceneObjectType == SceneObjectType::HANDARMOR || sceneObjectType == SceneObjectType::FOOTARMOR ){
		return lootableArmorMods.get(System::random(lootableArmorMods.size() - 1));
	}
	else if( sceneObjectType == SceneObjectType::CLOTHING || sceneObjectType == SceneObjectType::BANDOLIER ||
			 sceneObjectType == SceneObjectType::BELT || sceneObjectType == SceneObjectType::BODYSUIT ||
		     sceneObjectType == SceneObjectType::CAPE || sceneObjectType == SceneObjectType::CLOAK ||
			 sceneObjectType == SceneObjectType::FOOTWEAR || sceneObjectType == SceneObjectType::DRESS ||
			 sceneObjectType == SceneObjectType::HANDWEAR || sceneObjectType == SceneObjectType::EYEWEAR ||
			 sceneObjectType == SceneObjectType::HEADWEAR || sceneObjectType == SceneObjectType::JACKET ||
			 sceneObjectType == SceneObjectType::PANTS || sceneObjectType == SceneObjectType::ROBE ||
			 sceneObjectType == SceneObjectType::SHIRT || sceneObjectType == SceneObjectType::VEST ||
			 sceneObjectType == SceneObjectType::WOOKIEGARB || sceneObjectType == SceneObjectType::MISCCLOTHING ||
			 sceneObjectType == SceneObjectType::SKIRT || sceneObjectType == SceneObjectType::WEARABLECONTAINER ||
			 sceneObjectType == SceneObjectType::JEWELRY || sceneObjectType == SceneObjectType::RING ||
			 sceneObjectType == SceneObjectType::BRACELET || sceneObjectType == SceneObjectType::NECKLACE ||
			 sceneObjectType == SceneObjectType::EARRING ){
		return lootableClothingMods.get(System::random(lootableClothingMods.size() - 1));
	}
	else if( sceneObjectType == SceneObjectType::ONEHANDMELEEWEAPON ){
		return lootableOneHandedMeleeMods.get(System::random(lootableOneHandedMeleeMods.size() - 1));
	}
	else if( sceneObjectType == SceneObjectType::TWOHANDMELEEWEAPON ){
		return lootableTwoHandedMeleeMods.get(System::random(lootableTwoHandedMeleeMods.size() - 1));
	}
	else if( sceneObjectType == SceneObjectType::MELEEWEAPON ){
		return lootableUnarmedMods.get(System::random(lootableUnarmedMods.size() - 1));
	}
	else if( sceneObjectType == SceneObjectType::PISTOL ){
		return lootablePistolMods.get(System::random(lootablePistolMods.size() - 1));
	}
	else if( sceneObjectType == SceneObjectType::RIFLE ){
		return lootableRifleMods.get(System::random(lootableRifleMods.size() - 1));
	}
	else if( sceneObjectType == SceneObjectType::CARBINE ){
		return lootableCarbineMods.get(System::random(lootableCarbineMods.size() - 1));
	}
	else if( sceneObjectType == SceneObjectType::POLEARM ){
		return lootablePolearmMods.get(System::random(lootablePolearmMods.size() - 1));
	}
	else if( sceneObjectType == SceneObjectType::SPECIALHEAVYWEAPON ){
		return lootableHeavyWeaponMods.get(System::random(lootableHeavyWeaponMods.size() - 1));
	}
	else{
		return "";
	}

}

void LootManagerImplementation::setSockets(TangibleObject* object, CraftingValues* craftingValues) {
	if (object->isWearableObject() && craftingValues->hasProperty("sockets")) {
		ManagedReference<WearableObject*> wearableObject = cast<WearableObject*>(object);
		// Round number of sockets to closes integer.
		wearableObject->setMaxSockets(craftingValues->getCurrentValue("sockets") + 0.5);
	}
}

bool LootManagerImplementation::createLoot(SceneObject* container, AiAgent* creature) {
	LootGroupCollection* lootCollection = creature->getLootGroups();

	if (lootCollection == NULL)
		return false;

	return createLootFromCollection(container, lootCollection, creature->getLevel());
}

bool LootManagerImplementation::createLootFromCollection(SceneObject* container, LootGroupCollection* lootCollection, int level) {
	for (int i = 0; i < lootCollection->count(); ++i) {
		LootGroupCollectionEntry* entry = lootCollection->get(i);
		int lootChance = entry->getLootChance();

		if (lootChance <= 0)
			continue;

		int roll = System::random(10000000);

		if (roll > lootChance)
			continue;

		int tempChance = 0; //Start at 0.

		LootGroups* lootGroups = entry->getLootGroups();

		//Now we do the second roll to determine loot group.
		roll = System::random(10000000);

		//Select the loot group to use.
		for (int i = 0; i < lootGroups->count(); ++i) {
			LootGroupEntry* entry = lootGroups->get(i);

			tempChance += entry->getLootChance();

			//Is this entry lower than the roll? If yes, then we want to try the next entry.
			if (tempChance < roll)
				continue;

			createLoot(container, entry->getLootGroupName(), level);

			break;
		}
	}

	return true;
}

bool LootManagerImplementation::createLoot(SceneObject* container, const String& lootGroup, int level, bool maxCondition) {
	Reference<LootGroupTemplate*> group = lootGroupMap->getLootGroupTemplate(lootGroup);

	if (group == NULL) {
		warning("Loot group template requested does not exist: " + lootGroup);
		return false;
	}

	//Now we do the third roll for the item out of the group.
	int roll = System::random(10000000);

	String selection = group->getLootGroupEntryForRoll(roll);

	//Check to see if the group entry is another group
	if (lootGroupMap->lootGroupExists(selection))
		return createLoot(container, selection, level, maxCondition);

	//Entry wasn't another group, it should be a loot item
	Reference<LootItemTemplate*> itemTemplate = lootGroupMap->getLootItemTemplate(selection);

	if (itemTemplate == NULL) {
		warning("Loot item template requested does not exist: " + group->getLootGroupEntryForRoll(roll) + " for templateName: " + group->getTemplateName());
		return false;
	}

	TangibleObject* obj = createLootObject(itemTemplate, level, maxCondition);

	if (obj == NULL)
		return false;

	if (container->transferObject(obj, -1, false, true)) {
		container->broadcastObject(obj, true);
	} else {
		obj->destroyObjectFromDatabase(true);
		return false;
	}


	return true;
}

void LootManagerImplementation::addStaticDots(TangibleObject* object, LootItemTemplate* templateObject, int level) {

	if (object == NULL)
		return;

	if (!object->isWeaponObject())
		return;

	ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(object);

	bool shouldGenerateDots = false;

	float dotChance = templateObject->getStaticDotChance();

	if (dotChance < 0)
		return;

	// Apply the Dot if the chance roll equals the number or is zero.
	if (dotChance == 0 || System::random(dotChance) == 0) { // Defined in loot item script.
		shouldGenerateDots = true;
	}

	if (shouldGenerateDots) {

		int dotType = templateObject->getStaticDotType();

		if (dotType < 1 || dotType > 4)
			return;

		VectorMap<String, SortedVector<int> >* dotValues = templateObject->getStaticDotValues();
		int size = dotValues->size();

		// Check if they specified correct vals.
		if (size > 0) {
			weapon->addDotType(dotType);

			for (int i = 0; i < size; i++) {

				String property = dotValues->elementAt(i).getKey();
				SortedVector<int> theseValues = dotValues->elementAt(i).getValue();
				int min = theseValues.elementAt(0);
				int max = theseValues.elementAt(1);
				float value = 0;

				if (max != min) {
					value = calculateDotValue(min, max, level);
				}
				else { value = max; }

				if(property == "attribute") {
					if (min != max)
						value = System::random(max - min) + min;

					if (dotType != 2 && (value != 0 && value != 3 && value != 6)) {
						int numbers[] = { 0, 3, 6 }; // The main pool attributes.
						int choose = System::random(2);
						value = numbers[choose];
					}

					weapon->addDotAttribute(value);
				} else if (property == "strength") {
					weapon->addDotStrength(value);
				} else if (property == "duration") {
					weapon->addDotDuration(value);
				} else if (property == "potency") {
					weapon->addDotPotency(value);
				} else if (property == "uses") {
					weapon->addDotUses(value);
				}
			}
		}
	}
}

void LootManagerImplementation::addRandomDots(TangibleObject* object, LootItemTemplate* templateObject, int level, float excMod) {

	if (object == NULL)
		return;

	if (!object->isWeaponObject())
		return;

	ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(object);

	bool shouldGenerateDots = false;

	float dotChance = templateObject->getRandomDotChance();

	if (dotChance < 0)
		return;

	// Apply the Dot if the chance roll equals the number or is zero.
	if (dotChance == 0 || System::random(dotChance / excMod) == 0) { // Defined in loot item script.
		shouldGenerateDots = true;
	}

	if (shouldGenerateDots) {

		int number = 1;

		if (System::random(250 / excMod) == 5)
			number = 2;

		bool yellow = false;

		for (int i = 0; i < number; i++) {
			int dotType = System::random(2) + 1;

			weapon->addDotType(dotType);

			int attMin = randomDotAttribute.elementAt(0);
			int attMax = randomDotAttribute.elementAt(1);
			float att = 0;

			if (attMin != attMax)
				att= System::random(attMax - attMin) + attMin;

			if (dotType != 2 && (att != 0 && att != 3 && att != 6)) {
				int numbers[] = { 0, 3, 6 }; // The main pool attributes.
				int choose = System::random(2);
				att = numbers[choose];
			}

			weapon->addDotAttribute(att);

			int strMin = randomDotStrength.elementAt(0);
			int strMax = randomDotStrength.elementAt(1);
			float str = 0;

			if (strMax != strMin)
				str = calculateDotValue(strMin, strMax, level);
			else
				str = strMax;

			if (excMod == 1.0 && (yellowChance == 0 || System::random(yellowChance) == 0)) {
				str *= yellowModifier;
				yellow = true;
			}

			if (dotType == 1)
				str = str * 2;
			else if (dotType == 3)
				str = str * 1.5;

			weapon->addDotStrength(str * excMod);

			int durMin = randomDotDuration.elementAt(0);
			int durMax = randomDotDuration.elementAt(1);
			float dur = 0;

			if (durMax != durMin)
				dur = calculateDotValue(durMin, durMax, level);
			else
				dur = durMax;

			if (excMod == 1.0 && (yellowChance == 0 || System::random(yellowChance) == 0)) {
				dur *= yellowModifier;
				yellow = true;
			}

			if (dotType == 2)
				dur = dur * 5;
			else if (dotType == 3)
				dur = dur * 1.5;

			weapon->addDotDuration(dur * excMod);

			int potMin = randomDotPotency.elementAt(0);
			int potMax = randomDotPotency.elementAt(1);
			float pot = 0;

			if (potMax != potMin)
				pot = calculateDotValue(potMin, potMax, level);
			else
				pot = potMax;

			if (excMod == 1.0 && (yellowChance == 0 || System::random(yellowChance) == 0)) {
				pot *= yellowModifier;
				yellow = true;
			}

			weapon->addDotPotency(pot * excMod);

			int useMin = randomDotUses.elementAt(0);
			int useMax = randomDotUses.elementAt(1);
			float use = 0;

			if (useMax != useMin)
				use = calculateDotValue(useMin, useMax, level);
			else
				use = useMax;

			if (excMod == 1.0 && (yellowChance == 0 || System::random(yellowChance) == 0)) {
				use *= yellowModifier;
				yellow = true;
			}

			weapon->addDotUses(use * excMod);
		}

		if (yellow)
			weapon->addMagicBit(false);
	}
}

float LootManagerImplementation::calculateDotValue(float min, float max, float level) {
	float value = MAX(min, MIN(max, System::random(max - min) * (1 + (level / 1000)))); // Used for Str, Pot, Dur, Uses.

	if (value < min) {
		value = min;
	}

	return value;
}
