/*
 * LootManagerImplementation.cpp
 *
 *  Created on: Jun 20, 2011
 *      Author: Kyle
 */

#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "templates/LootItemTemplate.h"
#include "templates/LootGroupTemplate.h"
#include "server/zone/ZoneServer.h"
#include "LootGroupMap.h"
#include "server/zone/objects/tangible/component/lightsaber/LightsaberCrystalComponent.h"

void LootManagerImplementation::initialize() {
	info("Loading configuration.");

	if (!loadConfigData()) {

		loadDefaultConfig();

		info("Failed to load configuration values. Using default.");
	}

	lootGroupMap = LootGroupMap::instance();
	lootGroupMap->initialize();

	info("Loaded " + String::valueOf(lootableArmorAttachmentMods.size()) + " lootable armor attachment stat mods.");
	info("Loaded " + String::valueOf(lootableClothingAttachmentMods.size()) + " lootable clothing attachment stat mods.");
	info("Loaded " + String::valueOf(lootableArmorMods.size()) + " lootable armor stat mods.");
	info("Loaded " + String::valueOf(lootableClothingMods.size()) + " lootable clothing stat mods.");
	info("Loaded " + String::valueOf(lootableOneHandedMeleeMods.size()) + " lootable one handed melee stat mods.");
	info("Loaded " + String::valueOf(lootableTwoHandedMeleeMods.size()) + " lootable two handed melee stat mods.");
	info("Loaded " + String::valueOf(lootableUnarmedMods.size()) + " lootable unarmed stat mods.");
	info("Loaded " + String::valueOf(lootablePistolMods.size()) + " lootable pistol stat mods.");
	info("Loaded " + String::valueOf(lootableRifleMods.size()) + " lootable rifle stat mods.");
	info("Loaded " + String::valueOf(lootableCarbineMods.size()) + " lootable carbine stat mods.");
	info("Loaded " + String::valueOf(lootablePolearmMods.size()) + " lootable polearm stat mods.");
	info("Loaded " + String::valueOf(lootableHeavyWeaponMods.size()) + " lootable heavy weapon stat mods.");
	info("Loaded " + String::valueOf(lootGroupMap->countLootItemTemplates()) + " loot items.");
	info("Loaded " + String::valueOf(lootGroupMap->countLootGroupTemplates()) + " loot groups.");

	info("Initialized.", true);
}

void LootManagerImplementation::stop() {
	lootGroupMap = nullptr;
	craftingManager = nullptr;
	objectManager = nullptr;
	zoneServer = nullptr;
}

bool LootManagerImplementation::loadConfigData() {
	Lua* lua = new Lua();
	lua->init();

	if (!lua->runFile("scripts/managers/loot_manager.lua")) {
		delete lua;
		return false;
	}

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

	LuaObject luaObject = lua->getGlobalObject("jediCrystalStats");
	LuaObject crystalTable = luaObject.getObjectField("lightsaber_module_force_crystal");
	CrystalData* crystal = new CrystalData();
	crystal->readObject(&crystalTable);
	crystalData.put("lightsaber_module_force_crystal", crystal);
	crystalTable.pop();

	crystalTable = luaObject.getObjectField("lightsaber_module_krayt_dragon_pearl");
	crystal = new CrystalData();
	crystal->readObject(&crystalTable);
	crystalData.put("lightsaber_module_krayt_dragon_pearl", crystal);
	crystalTable.pop();
	luaObject.pop();

	delete lua;

	return true;
}

void LootManagerImplementation::loadLootableMods(LuaObject* modsTable, SortedVector<String>* mods) {

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

void LootManagerImplementation::setFinalObjectValues (const LootItemTemplate* templateObject, CraftingValues* craftingValues, TangibleObject* prototype) {
	// apply additional static values to weapon and armor objects.
	if (prototype->isArmorObject() || prototype->isWeaponObject()) {
		SharedTangibleObjectTemplate* tanoTemplate = dynamic_cast<SharedTangibleObjectTemplate*>(prototype->getObjectTemplate());

		const auto props = tanoTemplate->getExperimentalSubGroupTitles();
		const auto mins = tanoTemplate->getExperimentalMin();
		const auto maxs = tanoTemplate->getExperimentalMax();
		const auto prec = tanoTemplate->getExperimentalPrecision();

		for (int i = 0; i < props->size(); ++i) {
			const String& property = props->get(i);

			if (property == "null" || craftingValues->hasProperty(property))
				continue;

			craftingValues->addExperimentalProperty(property, property, mins->get(i), -1, prec->get(i), false, ValuesMap::LINEARCOMBINE);
		}
	}

	craftingValues->addExperimentalProperty("null", "creatureLevel", 0, 0, 0, false, ValuesMap::LINEARCOMBINE);
	craftingValues->setHidden("creatureLevel");

	// apply customization data values from loot template.
	const auto customizationData = templateObject->getCustomizationStringNames();
	const auto customizationValues = templateObject->getCustomizationValues();

	for (int i = 0; i < customizationData->size(); ++i) {
		const String& customizationString = customizationData->get(i);
		Vector<int>* values = &customizationValues->get(i);

		if (values->size() > 0) {
			int randomValue = values->get(System::random(values->size() - 1));

			prototype->setCustomizationVariable(customizationString, randomValue, false);
		}
	}
}

void LootManagerImplementation::setCustomObjectName(TangibleObject* object, const LootItemTemplate* templateObject) {
	const String& customName = templateObject->getCustomObjectName();

	if (!customName.isEmpty()) {
		if (customName.charAt(0) == '@') {
			StringId stringId(customName);

			object->setObjectName(stringId, false);
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

TangibleObject* LootManagerImplementation::createLootObject(const LootItemTemplate* templateObject, int uncappedLevel, bool maxCondition, bool logLoot) {
	int maxLevel = templateObject->getMaximumLevel();
	int minLevel = templateObject->getMinimumLevel();
	int level = uncappedLevel;

	if (maxLevel == -1)
		maxLevel = 300;

	if (level < minLevel)
		level = minLevel;

	if (level > maxLevel)
		level = maxLevel;

	const String& directTemplateObject = templateObject->getDirectObjectTemplate();
	ManagedReference<TangibleObject*> prototype = zoneServer->createObject(directTemplateObject.hashCode(), 2).castTo<TangibleObject*>();

	if (prototype == nullptr)
		return nullptr;

	Locker objLocker(prototype);
	prototype->createChildObjects();

	if (!templateObject->getSuppressSerialNumber())
		prototype->setSerialNumber(craftingManager->generateSerial());

	ValuesMap valuesMap = templateObject->getValuesMapCopy();
	CraftingValues* craftingValues = new CraftingValues(valuesMap);

	setCustomObjectName(prototype, templateObject);

	bool yellow = false;
	float excMod = 1.0;
	float adjustment = (( level > 50) ? level : 50) -50;

	if (System::random(legendaryChance * 10) <= adjustment) {
		prototype->setCustomObjectName(prototype->getDisplayedName() + " (Legendary)", false);

		excMod = legendaryModifier;
		prototype->addMagicBit(false);
		legendaryLooted.increment();

	} else if (System::random(exceptionalChance * 10) <= adjustment) {
		prototype->setCustomObjectName(prototype->getDisplayedName() + " (Exceptional)", false);

		excMod = exceptionalModifier;
		prototype->addMagicBit(false);
		exceptionalLooted.increment();
	}

	if (prototype->isLightsaberCrystalObject()) {
		ManagedReference<LightsaberCrystalComponent*> crystal = dynamic_cast<LightsaberCrystalComponent*>(prototype.get());
		if (crystal != nullptr) {
			crystal->setItemLevel(uncappedLevel);
		}
	}

	Vector<int> subtitleVector;
	int vectorSize = 0;

	// set value percentages, set static values and generate modification index vector.
	for (int x = 0; craftingValues->getExperimentalPropertySubtitleSize() > x; ++x) {
		const String& subtitle = craftingValues->getExperimentalPropertySubtitle(x);

		float min = craftingValues->getMinValue(subtitle);
		float max = craftingValues->getMaxValue(subtitle);

		if (min == max && subtitle != "color") {
			craftingValues->setCurrentValue(subtitle, min, min, -1);
			continue;
		}

		float rollDiff = (max - min) > 0 ? (max - min) : (min - max);

		if (rollDiff != (int)rollDiff)
			rollDiff = (int)(rollDiff * 10);

		float percentage = System::random(rollDiff) / rollDiff;
		craftingValues->setCurrentPercentage(subtitle, percentage);

		if (subtitle == "maxrange"
		 || subtitle == "midrange"
		 || subtitle == "zerorangemod"
		 || subtitle == "maxrangemod"
		 || subtitle == "forcecost"
		 || subtitle == "color"
		 || (subtitle == "midrangemod" && !prototype->isComponent())) {
			continue;
		}
		subtitleVector.add(vectorSize++, x);
	}

	float modsToRoll = 0;

	// roll for yellow, use the roll result to determine number of attributes modified.
	if (excMod == 1 && vectorSize > 0) {
		int yellowRoll = System::random(yellowChance * 10);

		if (yellowRoll <= adjustment) {
			modsToRoll = (int)(1.5 + ((vectorSize - 1) * (1 - (yellowRoll / adjustment))));

			yellow = true;

			prototype->addMagicBit(false);
			yellowLooted.increment();
		}
	}

	// run the vector, randomize execution order if yellow, apply the value modifiers.
	for (int y = vectorSize; y > 0; --y) {
		int index = subtitleVector.get(y - 1);

		if (yellow) {
			int rollIndex = System::random(subtitleVector.size() - 1);

			index = subtitleVector.get(rollIndex);
			subtitleVector.remove(rollIndex);
		}

		const String& subtitle = craftingValues->getExperimentalPropertySubtitle(index);

		float min = craftingValues->getMinValue(subtitle);
		float max = craftingValues->getMaxValue(subtitle);

		float rollLvl = level;
		float rollMod = excMod;

		if (subtitle == "useCount"
		 || subtitle == "quantity"
		 || subtitle == "charges"
		 || subtitle == "uses"
		 || subtitle == "charge") {
			rollLvl = 0.0;

			if (rollMod > yellowModifier)
				rollMod = yellowModifier;
		}

		if (yellow && (subtitleVector.size() <= modsToRoll))
			rollMod = yellowModifier;

		float minMod = (((rollLvl / 2) / 1000) + 1) * rollMod;
		float maxMod = (((rollLvl * 2) / 1000) + 1) * rollMod;

		if (max * min == 0) {
			min /= minMod;
			max *= maxMod;
		} else if (max < min && min > 0) {
			min /= minMod;
			max /= maxMod;
		} else {
			min *= minMod;
			max *= maxMod;
		}
		craftingValues->setMinValue(subtitle, min);
		craftingValues->setMaxValue(subtitle, max);
	}

	setFinalObjectValues(templateObject, craftingValues, prototype);
	craftingValues->setCurrentValue("creatureLevel", level, -1, level);

	craftingValues->recalculateValues(false);

	// check weapons and weapon components for min damage > max damage
	if (prototype->isComponent() || prototype->isWeaponObject()) {
		if (craftingValues->hasProperty("mindamage") && craftingValues->hasProperty("maxdamage")) {
			float oldMin = craftingValues->getCurrentValue("mindamage");
			float oldMax = craftingValues->getCurrentValue("maxdamage");

			if (oldMin > oldMax) {
				craftingValues->setCurrentValue("mindamage", oldMax);
				craftingValues->setCurrentValue("maxdamage", oldMin);
			}
		}
	}

	prototype->setJunkDealerNeeded(templateObject->getJunkDealerTypeNeeded());
	float junkMinValue = templateObject->getJunkMinValue() * junkValueModifier;
	float junkMaxValue = templateObject->getJunkMaxValue() * junkValueModifier;
	float fJunkValue = junkMinValue+System::random(junkMaxValue-junkMinValue);

	if (level > 0 && templateObject->getJunkDealerTypeNeeded() > 1) {
		fJunkValue = fJunkValue + (fJunkValue * ((float)level / 100));
	}

	if (excMod > yellowModifier) {
		prototype->setJunkValue((int)(fJunkValue * (excMod/2)));
	} else if (excMod == yellowModifier) {
		prototype->setJunkValue((int)(fJunkValue * 1.25));
	} else {
		prototype->setJunkValue((int)(fJunkValue));
	}

	addStaticDots(prototype, templateObject, level);
	addRandomDots(prototype, templateObject, level, excMod);

	setSkillMods(prototype, templateObject, level, excMod);
	setSockets(prototype, craftingValues);

	prototype->updateCraftingValues(craftingValues, true);

	if (!maxCondition)
		addConditionDamage(prototype, craftingValues);

	// send values to log/loot/lootLog.tsv. accessible via server loot command.
#ifdef LOOT_DEBUG_TESTING
	if (logLoot)
		writeLootLog(prototype, craftingValues);
#endif // LOOT_DEBUG_TESTING

	delete craftingValues;
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

void LootManagerImplementation::setSkillMods(TangibleObject* object, const LootItemTemplate* templateObject, int level, float excMod) {
	if (!object->isWeaponObject() && !object->isWearableObject())
		return;

	const VectorMap<String, int>* skillMods = templateObject->getSkillMods();
	VectorMap<String, int> additionalMods;

	bool yellow = false;
	float modSqr = excMod * excMod;

	if (System::random(skillModChance / modSqr) == 0) {
		// if it has a skillmod the name will be yellow
		yellow = true;
		int modCount = 1;
		int roll = System::random(100);

		if(roll > (100 - modSqr))
			modCount += 2;

		if(roll < (5 + modSqr))
			modCount += 1;

		for(int i = 0; i < modCount; ++i) {
			//Mods can't be lower than -1 or greater than 25
			int max = (int) Math::max(-1.f, Math::min(25.f, (float) round(0.1f * level + 3)));
			int min = (int) Math::max(-1.f, Math::min(25.f, (float) round(0.075f * level - 1)));

			int mod = System::random(max - min) + min;

			if(mod == 0)
				mod = 1;

			String modName = getRandomLootableMod( object->getGameObjectType() );
			if( !modName.isEmpty() )
				additionalMods.put(modName, mod);
		}
	}

	if (object->isWearableObject() || object->isWeaponObject()) {
		ManagedReference<TangibleObject*> item = cast<TangibleObject*>(object);

		if(additionalMods.size() > 0 || skillMods->size() > 0)
			yellow = true;

		for (int i = 0; i < additionalMods.size(); i++) {
			item->addSkillMod(SkillModManager::WEARABLE, additionalMods.elementAt(i).getKey(), additionalMods.elementAt(i).getValue());
		}

		for (int i = 0; i < skillMods->size(); i++) {
			item->addSkillMod(SkillModManager::WEARABLE, skillMods->elementAt(i).getKey(), skillMods->elementAt(i).getValue());
		}
	}

	if (yellow)
		object->addMagicBit(false);
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
	auto lootCollection = creature->getLootGroups();

	if (lootCollection == nullptr)
		return false;

	return createLootFromCollection(container, lootCollection, creature->getLevel());
}

bool LootManagerImplementation::createLootFromCollection(SceneObject* container, const LootGroupCollection* lootCollection, int level) {
	for (int i = 0; i < lootCollection->count(); ++i) {
		const LootGroupCollectionEntry* entry = lootCollection->get(i);
		int lootChance = entry->getLootChance();

		if (lootChance <= 0)
			continue;

		int roll = System::random(10000000);

		if (roll > lootChance)
			continue;

		int tempChance = 0; //Start at 0.

		const LootGroups* lootGroups = entry->getLootGroups();

		//Now we do the second roll to determine loot group.
		roll = System::random(10000000);

		//Select the loot group to use.
		for (int i = 0; i < lootGroups->count(); ++i) {
			const LootGroupEntry* entry = lootGroups->get(i);

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
	Reference<const LootGroupTemplate*> group = lootGroupMap->getLootGroupTemplate(lootGroup);

	if (group == nullptr) {
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
	Reference<const LootItemTemplate*> itemTemplate = lootGroupMap->getLootItemTemplate(selection);

	if (itemTemplate == nullptr) {
		warning("Loot item template requested does not exist: " + group->getLootGroupEntryForRoll(roll) + " for templateName: " + group->getTemplateName());
		return false;
	}

	TangibleObject* obj = createLootObject(itemTemplate, level, maxCondition);

	if (obj == nullptr)
		return false;

	if (container->transferObject(obj, -1, false, true)) {
		container->broadcastObject(obj, true);
	} else {
		obj->destroyObjectFromDatabase(true);
		return false;
	}

	return true;
}

bool LootManagerImplementation::createLootSet(SceneObject* container, const String& lootGroup, int level, bool maxCondition, int setSize) {
	Reference<const LootGroupTemplate*> group = lootGroupMap->getLootGroupTemplate(lootGroup);

	if (group == nullptr) {
		warning("Loot group template requested does not exist: " + lootGroup);
		return false;
	}
	//Roll for the item out of the group.
	int roll = System::random(10000000);

	int lootGroupEntryIndex = group->getLootGroupIntEntryForRoll(roll);

	for(int q = 0; q < setSize; q++) {
		String selection = group->getLootGroupEntryAt(lootGroupEntryIndex+q);
		Reference<const LootItemTemplate*> itemTemplate = lootGroupMap->getLootItemTemplate(selection);

		if (itemTemplate == nullptr) {
			warning("Loot item template requested does not exist: " + group->getLootGroupEntryForRoll(roll) + " for templateName: " + group->getTemplateName());
			return false;
		}

		TangibleObject* obj = createLootObject(itemTemplate, level, maxCondition);

		if (obj == nullptr)
			return false;

		if (container->transferObject(obj, -1, false, true)) {
			container->broadcastObject(obj, true);
		} else {
			obj->destroyObjectFromDatabase(true);
			return false;
		}

	}

	return true;
}

void LootManagerImplementation::addStaticDots(TangibleObject* object, const LootItemTemplate* templateObject, int level) {
	if (object == nullptr)
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

		const VectorMap<String, SortedVector<int> >* dotValues = templateObject->getStaticDotValues();
		int size = dotValues->size();

		// Check if they specified correct vals.
		if (size > 0) {
			weapon->addDotType(dotType);

			for (int i = 0; i < size; i++) {

				const String& property = dotValues->elementAt(i).getKey();
				const SortedVector<int>& theseValues = dotValues->elementAt(i).getValue();
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

			weapon->addMagicBit(false);
		}
	}
}

void LootManagerImplementation::addRandomDots(TangibleObject* object, const LootItemTemplate* templateObject, int level, float excMod) {
	if (object == nullptr)
		return;

	if (!object->isWeaponObject())
		return;

	ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(object);

	bool shouldGenerateDots = false;

	float dotChance = templateObject->getRandomDotChance();

	if (dotChance < 0)
		return;

	float modSqr = excMod * excMod;

	// Apply the Dot if the chance roll equals the number or is zero.
	if (dotChance == 0 || System::random(dotChance / modSqr) == 0) { // Defined in loot item script.
		shouldGenerateDots = true;
	}

	if (shouldGenerateDots) {

		int number = 1;

		if (System::random(250 / modSqr) == 0)
			number = 2;

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
			}

			weapon->addDotUses(use * excMod);
		}

		weapon->addMagicBit(false);
	}
}

float LootManagerImplementation::calculateDotValue(float min, float max, float level) {
	float randVal = (float)System::random(max - min);
	float value = Math::max(min, Math::min(max, randVal * (1 + (level / 1000)))); // Used for Str, Pot, Dur, Uses.

	if (value < min) {
		value = min;
	}

	return value;
}

void LootManagerImplementation::writeLootLog(TangibleObject* prototype, CraftingValues* craftingValues) {
#ifdef LOOT_DEBUG_TESTING
	StringBuffer lootLog, log;

	File logFile("log/loot/lootLog.tsv");
	FileWriter loggedLoot(&logFile, true);

	log << prototype->getDisplayedName()
		<< "	" << "subtitle"
		<< "	" << "minimum "
		<< "	" << "maximum "
		<< "	" << "percent "
		<< "	" << "value   "
		<< endl;

	for (int i = 0; i < craftingValues->getExperimentalPropertySubtitleSize(); ++i) {
		const String& subtitle = craftingValues->getExperimentalPropertySubtitle(i);

		lootLog << "	" << subtitle
				<< "	" << craftingValues->getMinValue(subtitle)
				<< "	" << craftingValues->getMaxValue(subtitle)
				<< "	" << craftingValues->getCurrentPercentage(subtitle)
				<< "	" << craftingValues->getCurrentValue(subtitle)
				<< endl;

		log << lootLog.toString().toCharArray();
		lootLog.deleteAll();
	}

	if(prototype->isAttachment()){
		ManagedReference<Attachment*> attachment = dynamic_cast<Attachment*>(prototype);
		const auto mods = attachment->getSkillMods();
		auto iterator = mods->iterator();

		String key = "";
		int value = 0;
		int last = 0;

		for(int i = 0; i < mods->size(); ++i) {
			iterator.getNextKeyAndValue(key, value);

			if(value > last){
				last = value;
				lootLog << "	" << key
						<< "				" << value
						<< endl;
			}
		}

		log << lootLog.toString().toCharArray();
		lootLog.deleteAll();

	} else if (prototype->isWearableObject()) {
		ManagedReference<WearableObject*> object = dynamic_cast<WearableObject*>(prototype);

		const auto modVector = object->getWearableSkillMods();
		for(auto mods = modVector[0].begin(); mods != modVector[0].end(); ++mods) {
			lootLog << "	"
					<< mods->getKey()
					<< "				"
					<< mods->getValue()
					<< endl;
		}

		log << lootLog.toString().toCharArray();
		lootLog.deleteAll();

	} else if (prototype->isWeaponObject()) {
		ManagedReference<WeaponObject*> weapon = dynamic_cast<WeaponObject*>(prototype);

		const auto modVector = weapon->getWearableSkillMods();
		for(auto mods = modVector[0].begin(); mods != modVector[0].end(); ++mods) {
			lootLog << "	"
					<< mods->getKey()
					<< "				"
					<< mods->getValue()
					<< endl;
		}

		log << lootLog.toString().toCharArray();
		lootLog.deleteAll();

		for (int j = 0; j < weapon->getNumberOfDots(); ++ j) {
			lootLog << "	" << "dotType     " << "				" << weapon->getDotType(j) << endl
					<< "	" << "dotAttribute" << "				" << weapon->getDotAttribute(j) << endl
					<< "	" << "dotStrength " << "				" << weapon->getDotStrength(j) << endl
					<< "	" << "dotPotency  " << "				" << weapon->getDotPotency(j) << endl
					<< "	" << "dotDuration " << "				" << weapon->getDotDuration(j) << endl
					<< "	" << "dotUses     " << "				" << weapon->getDotUses(j) << endl;

			log << lootLog.toString().toCharArray();
			lootLog.deleteAll();
		}

	} else if (prototype->isLightsaberCrystalObject()) {
		ManagedReference<LightsaberCrystalComponent*> crystal = dynamic_cast<LightsaberCrystalComponent*>(prototype);

		lootLog << "	" << "quality     " << "				" << crystal->getQuality() << endl
				<< "	" << "attackSpeed " << "				" << crystal->getAttackSpeed() << endl
				<< "	" << "damage      " << "				" << crystal->getDamage() << endl
				<< "	" << "woundChance " << "				" << crystal->getWoundChance() << endl
				<< "	" << "sacHealth   " << "				" << crystal->getSacHealth() << endl
				<< "	" << "sacAction   " << "				" << crystal->getSacAction() << endl
				<< "	" << "sacHealth   " << "				" << crystal->getSacHealth() << endl
				<< "	" << "forceCost   " << "				" << crystal->getForceCost() << endl;

		log << lootLog.toString().toCharArray();
		lootLog.deleteAll();
	}

	if (log.length() == (prototype->getDisplayedName().length() + 6))
		log << endl;

	loggedLoot.write(log.toString().toCharArray());
	loggedLoot.close();
#else
	warning("lootLog write attempt while loot debug not defined: " + prototype->getObjectID());
	return;
#endif // LOOT_DEBUG_TESTING

}
