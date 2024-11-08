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
#include "server/zone/managers/loot/LootValues.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/Zone.h"
#include "templates/params/creature/CreatureAttribute.h"
#include "server/zone/objects/ship/components/ShipComponent.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"

// #define DEBUG_LOOT_MAN

void LootManagerImplementation::initialize() {
	info(true) << "Loading configuration...";

	if (!loadConfigData()) {

		loadDefaultConfig();

		info(true) << "Failed to load configuration values, using default.";
	}

	lootGroupMap = LootGroupMap::instance();
	lootGroupMap->initialize();

	info(true) << "Loaded " << lootableArmorAttachmentMods.size() << " lootable Armor Attachment Stat Mods.";
	info(true) << "Loaded " << lootableClothingAttachmentMods.size() << " lootable Clothing Attachment Stat Mods.";
	info(true) << "Loaded " << lootableArmorMods.size() << " lootable Armor Stat Mods.";
	info(true) << "Loaded " << lootableClothingMods.size() << " lootable Clothing Stat Mods.";
	info(true) << "Loaded " << lootableOneHandedMeleeMods.size() << " lootable One-handed Melee Stat Mods.";
	info(true) << "Loaded " << lootableTwoHandedMeleeMods.size() << " lootable Two-handed Melee Stat Mods.";
	info(true) << "Loaded " << lootableUnarmedMods.size() << " lootable Unarmed Stat Mods.";
	info(true) << "Loaded " << lootablePistolMods.size() << " lootable Pistol Stat Mods.";
	info(true) << "Loaded " << lootableRifleMods.size() << " lootable Rifle Stat Mods.";
	info(true) << "Loaded " << lootableCarbineMods.size() << " lootable Carbine Stat Mods.";
	info(true) << "Loaded " << lootablePolearmMods.size() << " lootable Polearm Stat Mods.";
	info(true) << "Loaded " << lootableHeavyWeaponMods.size() << " lootable Heavy Weapon Stat Mods.";
	info(true) << "Loaded " << lootGroupMap->countLootGroupTemplates() << " Loot Groups.";
	info(true) << "Loaded " << lootGroupMap->countLootItemTemplates() << " Loot Items.";

	info(true) << "Initialized.";
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

	levelChance = lua->getGlobalFloat("levelChance");
	baseChance = lua->getGlobalFloat("baseChance");
	baseModifier = lua->getGlobalFloat("baseModifier");
	yellowChance = lua->getGlobalFloat("yellowChance");
	yellowModifier = lua->getGlobalFloat("yellowModifier");
	exceptionalChance = lua->getGlobalFloat("exceptionalChance");
	exceptionalModifier = lua->getGlobalFloat("exceptionalModifier");
	legendaryChance = lua->getGlobalFloat("legendaryChance");
	legendaryModifier = lua->getGlobalFloat("legendaryModifier");
	skillModChance = lua->getGlobalFloat("skillModChance");
	junkValueModifier = lua->getGlobalFloat("junkValueModifier");

	fireDotChance = lua->getGlobalFloat("fireDotChance");
	diseaseDotChance = lua->getGlobalFloat("diseaseDotChance");
	poisonDotChance = lua->getGlobalFloat("poisonDotChance");

	if (fabs((fireDotChance + diseaseDotChance + poisonDotChance) - 1.f) > 0.01f) {
		error() << "Weapon DOT Type chance is not properly distributed. Chances need to equate to 1 - Current Value: " << (fireDotChance + diseaseDotChance + poisonDotChance);
	}

	healthDotChance = lua->getGlobalFloat("healthDotChance");
	actionDotChance = lua->getGlobalFloat("actionDotChance");
	mindDotChance = lua->getGlobalFloat("mindDotChance");

	if (fabs((healthDotChance + actionDotChance + mindDotChance) - 1.f) > 0.01f) {
		error() << "Weapon DOT HAM Attribute chance is not properly distributed. Chances need to equate to 1 - Current Value: " << (healthDotChance + actionDotChance + mindDotChance);
	}

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

void LootManagerImplementation::setCustomizationData(const LootItemTemplate* templateObject, TangibleObject* prototype) {
#ifdef DEBUG_LOOT_MAN
	info(true) << " ========== LootManagerImplementation::setCustomizationData -- called ==========";
#endif

	const Vector<String>* customizationData = templateObject->getCustomizationStringNames();
	const Vector<Vector<int> >* customizationValues = templateObject->getCustomizationValues();

	for (int i = 0; i < customizationData->size(); ++i) {
		const String& customizationString = customizationData->get(i);
		Vector<int>* values = &customizationValues->get(i);

		if (values->size() > 0) {
			int randomValue = values->get(System::random(values->size() - 1));

#ifdef DEBUG_LOOT_MAN
		info(true) << "Setting Customization String: " << customizationString << " To a value: " << randomValue;
#endif

			prototype->setCustomizationVariable(customizationString, randomValue, false);
		}
	}

#ifdef DEBUG_LOOT_MAN
	info(true) << " ========== LootManagerImplementation::setCustomizationData -- COMPLETE ==========";
#endif
}

void LootManagerImplementation::setCustomObjectName(TangibleObject* object, const LootItemTemplate* templateObject, float excMod) {
	const String& customName = templateObject->getCustomObjectName();

	if (!customName.isEmpty()) {
		if (customName.charAt(0) == '@') {
			StringId stringId(customName);

			object->setObjectName(stringId, false);
		} else {
			object->setCustomObjectName(customName, false);
		}
	}

	String suffixName = "";

	if (excMod >= legendaryModifier) {
		suffixName = " (Legendary)";
	} else if (excMod >= exceptionalModifier) {
		suffixName = " (Exceptional)";
	}

	if (suffixName != "") {
		object->setCustomObjectName(object->getDisplayedName() + suffixName, false);
		object->addMagicBit(false);
	}
}

void LootManagerImplementation::setJunkValue(TangibleObject* prototype, const LootItemTemplate* itemTemplate, int level, float excMod) {
	float valueMin = itemTemplate->getJunkMinValue() * junkValueModifier;
	float valueMax = itemTemplate->getJunkMaxValue() * junkValueModifier;

	int junkType = itemTemplate->getJunkDealerTypeNeeded();
	int junkValue = System::random(valueMax - valueMin) + valueMin;

	if (junkType >= 2) {
		junkValue = ((level * 0.01f) * junkValue) + junkValue;
	}

	if (excMod >= legendaryModifier) {
		junkValue *= 2.5f;
	} else if (excMod >= yellowModifier) {
		junkValue *= 1.25;
	}

	prototype->setJunkDealerNeeded(junkType);
	prototype->setJunkValue(junkValue);
}

int LootManagerImplementation::calculateLootCredits(int level) {
	int maxcredits = (int) round((.03f * level * level) + (3 * level) + 50);
	int mincredits = (int) round((((float) maxcredits) * .5f) + (2.0f * level));

	int credits = mincredits + System::random(maxcredits - mincredits);

	return credits;
}

void LootManagerImplementation::setRandomLootValues(TransactionLog& trx, TangibleObject* prototype, const LootItemTemplate* itemTemplate, int level, float excMod) {
	auto debugAttributes = ConfigManager::instance()->getLootDebugAttributes();

	float modifier = getRandomModifier(itemTemplate, level, excMod);

	auto lootValues = LootValues(itemTemplate, level, modifier);
	prototype->updateCraftingValues(&lootValues, true);

#ifdef LOOTVALUES_DEBUG
	lootValues.debugAttributes(prototype, itemTemplate);
#endif // LOOTVALUES_DEBUG

	if (excMod >= legendaryModifier) {
		trx.addState("lootIsLegendary", true);
		legendaryLooted.increment();
	} else if (excMod >= exceptionalModifier) {
		trx.addState("lootIsExceptional", true);
		exceptionalLooted.increment();
	} else if (lootValues.getDynamicValues() > 0) {
		trx.addState("lootIsYellow", true);
		yellowLooted.increment();

		prototype->addMagicBit(false);
	}

	if (debugAttributes) {
		JSONSerializationType attrDebug;

		for (int i = 0; i < lootValues.getTotalExperimentalAttributes(); ++i) {
			const String& attribute = lootValues.getAttribute(i);

			JSONSerializationType attrDebugEntry;
			attrDebugEntry["mod"] = lootValues.getMaxPercentage(attribute);
			attrDebugEntry["pct"] = lootValues.getCurrentPercentage(attribute);
			attrDebugEntry["min"] = lootValues.getMinValue(attribute);
			attrDebugEntry["max"] = lootValues.getMaxValue(attribute);
			attrDebugEntry["final"] = lootValues.getCurrentValue(attribute);
			attrDebug[attribute] = attrDebugEntry;
		}

		if (!attrDebug.empty()) {
			trx.addState("lootAttributeDebug", attrDebug);
		}
	}
}

TangibleObject* LootManagerImplementation::createLootObject(TransactionLog& trx, const LootItemTemplate* templateObject, int level, bool maxCondition) {
#ifdef DEBUG_LOOT_MAN
	info(true) << " ---------- LootManagerImplementation::createLootObject -- called ----------";
#endif

	const String& directTemplateObject = templateObject->getDirectObjectTemplate();
	level = Math::clamp((int)LEVELMIN, level, (int)LEVELMAX);

	trx.addState("lootVersion", 2);
	trx.addState("lootTemplate", directTemplateObject);
	trx.addState("lootLevel", level);
	trx.addState("lootMaxCondition", maxCondition);

#ifdef DEBUG_LOOT_MAN
	info(true) << "Item Template: " << directTemplateObject << "    Level = " << level;
#endif

	if (templateObject->isRandomResourceContainer()) {
		return createLootResource(templateObject->getTemplateName(), "tatooine");
	}

	if (templateObject->isShipComponent()) {
		return createShipComponent(trx, templateObject);
	}

	ManagedReference<TangibleObject*> prototype = zoneServer->createObject(directTemplateObject.hashCode(), 2).castTo<TangibleObject*>();

	if (prototype == nullptr) {
		error() << "could not create loot object: " << directTemplateObject;
		return nullptr;
	}

	// Lock the loot item
	Locker objLocker(prototype);

	// Create child objects of loot item
	prototype->createChildObjects();

	// Add a seriel number for objects that do not hide them
	if (!templateObject->getSuppressSerialNumber()) {
		String serial = craftingManager->generateSerial();
		prototype->setSerialNumber(serial);
	}

	// Calculate level rank value chance
	float chance = LootValues::getLevelRankValue(Math::max(level - 50, 0), 0.f, 0.35f) * levelChance;
	float excMod = baseModifier;

	if (System::random(legendaryChance) <= chance) {
		excMod = legendaryModifier;
	} else if (System::random(exceptionalChance) <= chance) {
		excMod = exceptionalModifier;
	}

#ifdef DEBUG_LOOT_MAN
	info(true) << "Exceptional Modifier (excMod) = " << excMod << "  chance = " << chance;
#endif

	// Set loot item customization and object name
	setCustomizationData(templateObject, prototype);
	setCustomObjectName(prototype, templateObject, excMod);

	// Set the values for the random attributes to be modified if there are any
	setRandomLootValues(trx, prototype, templateObject, level, excMod);

	// Set the value for those items that can be sold at a junk dealer
	setJunkValue(prototype, templateObject, level, excMod);

	// Chance to add skill modifiers to weapons and wearable objects (clothing, armor)
	if (prototype->isWeaponObject() || prototype->isWearableObject()) {
		setSkillMods(prototype, templateObject, level, excMod);
	}

	// Add static DoT's to weapons and check for chance to add random DoTs
	if (prototype->isWeaponObject()) {
		addStaticDots(prototype, templateObject, level);
		addRandomDots(prototype, templateObject, level, excMod);
	}

	// Add some condition damage to the looted item if it is a weapon or piece of armor
	if (!maxCondition && (prototype->isWeaponObject() || prototype->isArmorObject())) {
		addConditionDamage(prototype);
	}

	trx.addState("lootAdjustment", chance);
	trx.addState("lootExcMod", excMod);
	trx.addState("lootJunkValue", prototype->getJunkValue());
	trx.addState("lootConditionDmg", prototype->getConditionDamage());
	trx.addState("lootConditionMax", prototype->getMaxCondition());

#ifdef DEBUG_LOOT_MAN
	info(true) << " ---------- LootManagerImplementation::createLootObject -- COMPLETE ----------";
#endif

	return prototype;
}

TangibleObject* LootManagerImplementation::createShipComponent(TransactionLog& trx, const LootItemTemplate* itemTemplate) {
	if (itemTemplate == nullptr || !itemTemplate->isShipComponent()) {
		return nullptr;
	}

	uint32 templateCRC = itemTemplate->getDirectObjectTemplate().hashCode();

	if (templateCRC == 0) {
		return nullptr;
	}

	ManagedReference<ShipComponent*> prototype = zoneServer->createObject(templateCRC, 2).castTo<ShipComponent*>();

	if (prototype == nullptr) {
		return nullptr;
	}

	Locker objLocker(prototype);

	setCustomizationData(itemTemplate, prototype);
	setCustomObjectName(prototype, itemTemplate, 0.f);

	auto lootValues = LootValues(itemTemplate, 0, 1.f);
	prototype->updateCraftingValues(&lootValues, true);

	return prototype;
}

TangibleObject* LootManagerImplementation::createLootResource(const String& resourceDataName, const String& resourceZoneName) {
	auto lootItemTemplate = lootGroupMap->getLootItemTemplate(resourceDataName);

	if (lootItemTemplate == nullptr || lootItemTemplate->getObjectType() != SceneObjectType::RESOURCECONTAINER) {
		return nullptr;
	}

	auto resourceManager = zoneServer->getResourceManager();

	if (resourceManager == nullptr) {
		return nullptr;
	}

	auto resourceSpawner = resourceManager->getResourceSpawner();

	if (resourceSpawner == nullptr) {
		return nullptr;
	}

	auto resourceMap = resourceSpawner->getResourceMap();

	if (resourceMap == nullptr) {
		return nullptr;
	}

	auto resourceList = resourceMap->getZoneResourceList(resourceZoneName);

	if (resourceList == nullptr) {
		return nullptr;
	}

	String resourceTypeName = resourceDataName.replaceAll("resource_container_", "");

	if (resourceTypeName == "") {
		return nullptr;
	}

	Vector<ManagedReference<ResourceSpawn*>> resourceIndex;

	for (int i = 0; i < resourceList->size(); ++i) {
		ManagedReference<ResourceSpawn*> resourceEntry = resourceList->elementAt(i).getValue();

		if (resourceEntry != nullptr && resourceEntry->isType(resourceTypeName)) {
			resourceIndex.add(resourceEntry);
		}
	}

	if (resourceIndex.size() > 0) {
		ManagedReference<ResourceSpawn*> resourceEntry = resourceIndex.get(System::random(resourceIndex.size()-1));

		if (resourceEntry != nullptr) {
			Locker rLock(resourceEntry);

			const auto& valueMap = lootItemTemplate->getAttributesMapCopy();

			if (!valueMap.hasExperimentalAttribute("quantity")) {
				return nullptr;
			}

			float min = Math::max(1.f, valueMap.getMinValue("quantity"));
			float max = Math::max(min, valueMap.getMaxValue("quantity"));

			ManagedReference<ResourceContainer*> resourceContainer = resourceEntry->createResource(System::random(max - min) + min);

			return resourceContainer;
		}
	}

	return nullptr;
}

void LootManagerImplementation::addConditionDamage(TangibleObject* prototype) {
	if (prototype == nullptr) {
		return;
	}

	int conditionMax = prototype->getMaxCondition();

	if (conditionMax < 0) {
		prototype->setMaxCondition(0, false);
		return;
	}

	int conditionDmg = std::round(conditionMax / 3.f);

	if (conditionDmg > 1) {
		prototype->setConditionDamage(System::random(conditionDmg), false);
	}
}

void LootManagerImplementation::setSkillMods(TangibleObject* prototype, const LootItemTemplate* templateObject, int level, float excMod) {
	if (prototype == nullptr || templateObject == nullptr) {
		return;
	}

	VectorMap<String,int> skillMods = *templateObject->getSkillMods();

	float modifier = Math::max(getRandomModifier(templateObject, level, excMod), baseModifier);
	int chance = LootValues::getLevelRankValue(level, 0.2f, 0.9f) * modifier * levelChance;
	int roll = System::random(skillModChance);
	int randomMods = 0;

	if (roll <= chance) {
		int pivot = chance - roll;

		if (pivot < 40) {
			randomMods = 1;
		} else if (pivot < 70) {
			randomMods = System::random(1) + 1;
		} else if (pivot < 100) {
			randomMods = System::random(2) + 1;
		} else {
			randomMods = System::random(1) + 2;
		}
	}

	for (int i = 0; i < randomMods; ++i) {
		String modName = getRandomLootableMod(prototype->getGameObjectType());

		if (modName.isEmpty()) {
			continue;
		}

		float step = 1.f - ((i / (float)randomMods) * 0.5f);
		int min = Math::clamp(-1, (int)round(0.075f * level) - 1, 25) * step;
		int max = Math::clamp(-1, (int)round(0.125f * level) + 1, 25);
		int mod = System::random(max - min) + min;

		skillMods.add(skillMods.size(), VectorMapEntry<String,int>(modName, ((mod <= 0) ? 1 : mod)));
	}

	if (skillMods.size() == 0) {
		return;
	}

	for (int i = 0; i < skillMods.size(); i++) {
		const String& key = skillMods.elementAt(i).getKey();
		int value = skillMods.elementAt(i).getValue();

		prototype->addSkillMod(SkillModManager::WEARABLE, key, value);
	}

	prototype->addMagicBit(false);
}

String LootManagerImplementation::getRandomLootableMod(uint32 sceneObjectType) {
	if (sceneObjectType == SceneObjectType::ARMORATTACHMENT) {
		return lootableArmorAttachmentMods.get(System::random(lootableArmorAttachmentMods.size() - 1));
	} else if (sceneObjectType == SceneObjectType::CLOTHINGATTACHMENT) {
		return lootableClothingAttachmentMods.get(System::random(lootableClothingAttachmentMods.size() - 1));
	} else if (sceneObjectType & SceneObjectType::ARMOR) {
		return lootableArmorMods.get(System::random(lootableArmorMods.size() - 1));
	} else if ((sceneObjectType & SceneObjectType::CLOTHING) || (sceneObjectType & SceneObjectType::JEWELRY)) {
		return lootableClothingMods.get(System::random(lootableClothingMods.size() - 1));
	} else if (sceneObjectType == SceneObjectType::ONEHANDMELEEWEAPON) {
		return lootableOneHandedMeleeMods.get(System::random(lootableOneHandedMeleeMods.size() - 1));
	} else if (sceneObjectType == SceneObjectType::TWOHANDMELEEWEAPON) {
		return lootableTwoHandedMeleeMods.get(System::random(lootableTwoHandedMeleeMods.size() - 1));
	} else if (sceneObjectType == SceneObjectType::MELEEWEAPON) {
		return lootableUnarmedMods.get(System::random(lootableUnarmedMods.size() - 1));
	} else if (sceneObjectType == SceneObjectType::PISTOL) {
		return lootablePistolMods.get(System::random(lootablePistolMods.size() - 1));
	} else if (sceneObjectType == SceneObjectType::RIFLE) {
		return lootableRifleMods.get(System::random(lootableRifleMods.size() - 1));
	} else if (sceneObjectType == SceneObjectType::CARBINE) {
		return lootableCarbineMods.get(System::random(lootableCarbineMods.size() - 1));
	} else if (sceneObjectType == SceneObjectType::POLEARM) {
		return lootablePolearmMods.get(System::random(lootablePolearmMods.size() - 1));
	} else if (sceneObjectType == SceneObjectType::SPECIALHEAVYWEAPON) {
		return lootableHeavyWeaponMods.get(System::random(lootableHeavyWeaponMods.size() - 1));
	}

	return "";
}

bool LootManagerImplementation::createLoot(TransactionLog& trx, SceneObject* container, AiAgent* creature) {
	auto lootCollection = creature->getLootGroups();

	if (lootCollection == nullptr) {
		trx.abort() << "No lootCollection.";
		return false;
	}

	if (lootCollection->count() == 0) {
		trx.abort() << "Empty loot collection.";
		trx.discard();
		return false;
	}

	return createLootFromCollection(trx, container, lootCollection, creature->getLevel());
}

uint64 LootManagerImplementation::createLoot(TransactionLog& trx, SceneObject* container, ShipAiAgent* shipAgent) {
	if (container == nullptr || shipAgent == nullptr) {
		return 0;
	}

	String lootMapEntry = shipAgent->getLootTable();

	if (!lootGroupMap->lootGroupExists(lootMapEntry) && !lootGroupMap->lootItemExists(lootMapEntry)) {
		return 0;
	}

	float lootChanceFloat = shipAgent->getLootChance();
	uint32 lootChance = lootChanceFloat * 10000000;
	uint32 playerRoll = System::random(10000000);

	if (playerRoll > lootChance) {
		return 0;
	}

	return createLoot(trx, container, lootMapEntry, 0, true);
}

bool LootManagerImplementation::createLootFromCollection(TransactionLog& trx, SceneObject* container, const LootGroupCollection* lootCollection, int level) {
	uint64 objectID = 0;

	trx.addState("lootCollectionSize", lootCollection->count());

	Vector<int> chances;
	Vector<int> rolls;
	Vector<String> lootGroupNames;

	for (int i = 0; i < lootCollection->count(); ++i) {
		const LootGroupCollectionEntry* collectionEntry = lootCollection->get(i);
		int lootChance = collectionEntry->getLootChance();

		if (lootChance <= 0)
			continue;

		int roll = System::random(10000000);

		rolls.add(roll);

		if (roll > lootChance)
			continue;

 		// Start at 0
		int tempChance = 0;

		const LootGroups* lootGroups = collectionEntry->getLootGroups();

		//Now we do the second roll to determine loot group.
		roll = System::random(10000000);

		rolls.add(roll);

		//Select the loot group to use.
		for (int k = 0; k < lootGroups->count(); ++k) {
			const LootGroupEntry* groupEntry = lootGroups->get(k);

			lootGroupNames.add(groupEntry->getLootGroupName());

			tempChance += groupEntry->getLootChance();

			// Is this entry lower than the roll? If yes, then we want to try the next groupEntry.
			if (tempChance < roll)
				continue;

			objectID = createLoot(trx, container, groupEntry->getLootGroupName(), level);

			break;
		}
	}

	trx.addState("lootChances", chances);
	trx.addState("lootRolls", rolls);
	trx.addState("lootGroups", lootGroupNames);

	if (objectID == 0) {
		trx.abort() << "Did not win loot rolls.";
	}

	return objectID > 0 ? true : false;
}

uint64 LootManagerImplementation::createLoot(TransactionLog& trx, SceneObject* container, const String& lootMapEntry, int level, bool maxCondition) {
	String lootEntry = lootMapEntry;
	String lootGroup = "";

	int depthMax = 32;
	int depth = 0;

	while (lootGroupMap->lootGroupExists(lootEntry) && depthMax > depth++) {
		auto group = lootGroupMap->getLootGroupTemplate(lootEntry);

		if (group != nullptr) {
			lootGroup = lootEntry;
			lootEntry = group->getLootGroupEntryForRoll(System::random(10000000));
		}
	}

	Reference<const LootItemTemplate*> itemTemplate = lootGroupMap->getLootItemTemplate(lootEntry);

	if (itemTemplate == nullptr) {
		error() << "LootMapEntry does not exist: lootItem: " << lootEntry << " lootGroup: " << lootGroup << " lootMapEntry: " << lootMapEntry << " at search depth: " << depth;
		return 0;
	}

	trx.addState("lootMapEntry", lootMapEntry);

	TangibleObject* obj = nullptr;

	if (itemTemplate->isRandomResourceContainer()) {
		auto zone = container->getZone();

		if (zone == nullptr) {
			return 0;
		}

		obj = createLootResource(lootEntry, zone->getZoneName());
	} else if (itemTemplate->isShipComponent()) {
		obj = createShipComponent(trx, itemTemplate);
	} else {
		obj = createLootObject(trx, itemTemplate, level, maxCondition);
	}

	if (obj == nullptr) {
		return 0;
	}

	trx.setSubject(obj);

	if (container->transferObject(obj, -1, false, true)) {
		container->broadcastObject(obj, true);
	} else {
		obj->destroyObjectFromDatabase(true);
		trx.errorMessage() << "failed to transferObject to container.";
		return 0;
	}

	return obj != nullptr ? obj->getObjectID() : 0;
}

bool LootManagerImplementation::createLootSet(TransactionLog& trx, SceneObject* container, const String& lootGroup, int level, bool maxCondition, int setSize) {
	Reference<const LootGroupTemplate*> group = lootGroupMap->getLootGroupTemplate(lootGroup);

	if (group == nullptr) {
		warning("Loot group template requested does not exist: " + lootGroup);
		return false;
	}
	//Roll for the item out of the group.
	int roll = System::random(10000000);

	int lootGroupEntryIndex = group->getLootGroupIntEntryForRoll(roll);

	trx.addState("lootSetSize", setSize);
	trx.addState("lootGroup", lootGroup);

	for(int q = 0; q < setSize; q++) {
		String selection = group->getLootGroupEntryAt(lootGroupEntryIndex+q);
		Reference<const LootItemTemplate*> itemTemplate = lootGroupMap->getLootItemTemplate(selection);

		if (itemTemplate == nullptr) {
			warning("Loot item template requested does not exist: " + group->getLootGroupEntryForRoll(roll) + " for templateName: " + group->getTemplateName());
			return false;
		}

		TangibleObject* obj = nullptr;

		if (q == 0) {
			obj = createLootObject(trx, itemTemplate, level, maxCondition);
			trx.addState("lootSetNum", q);
		} else {
			TransactionLog trxSub = trx.newChild();

			trxSub.addState("lootSetSize", setSize);
			trxSub.addState("lootGroup", lootGroup);
			trxSub.addState("lootSetNum", q);

			obj = createLootObject(trxSub, itemTemplate, level, maxCondition);

			trxSub.setSubject(obj);
		}

		if (obj == nullptr)
			return false;

		trx.addRelatedObject(obj);

		if (container->transferObject(obj, -1, false, true)) {
			container->broadcastObject(obj, true);
		} else {
			trx.errorMessage() << "failed to transferObject " << obj->getObjectID() << " to container.";
			obj->destroyObjectFromDatabase(true);
			return false;
		}
	}

	return true;
}

void LootManagerImplementation::addStaticDots(TangibleObject* object, const LootItemTemplate* templateObject, int level) {
	if (object == nullptr) {
		return;
	}

	auto weapon = dynamic_cast<WeaponObject*>(object);

	if (weapon == nullptr) {
		return;
	}

	float staticDotChance = templateObject->getStaticDotChance();

	if (staticDotChance < 0.f) {
		return;
	}

	int levelRank = LootValues::getLevelRankValue(level, 0.f, 0.15f) * levelChance;
	int staticDots = 0;

	if (staticDotChance == 0 || System::random(staticDotChance) <= levelRank) {
		staticDots = 1;
	}

	if (staticDots == 0) {
		return;
	}

	int dotType = templateObject->getStaticDotType();

	if (dotType < LootManager::DOT_POISON || dotType > LootManager::DOT_BLEEDING) {
		return;
	}

	const auto dotValues = templateObject->getStaticDotValues();

	if (dotValues == nullptr || dotValues->size() < 5) {
		return;
	}

	int attribute = 0;
	int strength = 0;
	int duration = 0;
	int potency = 0;
	int uses = 0;

	for (int i = 0; i < dotValues->size(); ++i) {
		const auto& property = dotValues->elementAt(i).getKey();
		const auto& values = dotValues->elementAt(i).getValue();

		int min = values.get(0);
		int max = values.get(1);

		if (property == "attribute") {
			attribute = System::random(max - min) + min;

			if (dotType != LootManager::DOT_DISEASE) {
				attribute = (int)(attribute / 3.f) * 3;
			}
		} else if (property == "strength") {
			strength = LootValues::getDistributedValue(min, max, level);
		} else if (property == "duration") {
			duration = LootValues::getDistributedValue(min, max, level);
		} else if (property == "potency") {
			potency = LootValues::getDistributedValue(min, max, level);
		} else if (property == "uses") {
			uses = LootValues::getDistributedValue(min, max, level);
		}
	}

	if (strength <= 0 || duration <= 0 || potency <= 0 || uses <= 0) {
		return;
	}

	weapon->addDotType(dotType);
	weapon->addDotAttribute(attribute);
	weapon->addDotStrength(strength);
	weapon->addDotDuration(duration);
	weapon->addDotPotency(potency);
	weapon->addDotUses(uses);

	weapon->addMagicBit(false);
}

void LootManagerImplementation::addRandomDots(TangibleObject* object, const LootItemTemplate* templateObject, int level, float excMod) {
	if (object == nullptr) {
		return;
	}

	auto weapon = dynamic_cast<WeaponObject*>(object);

	if (weapon == nullptr) {
		return;
	}

	float randomDotChance = templateObject->getRandomDotChance();

	if (randomDotChance < 0.f) {
		return;
	}

	float modifier = Math::max(getRandomModifier(templateObject, level, excMod), baseModifier);
	int levelRank = LootValues::getLevelRankValue(level, 0.f, 0.15f) * modifier * levelChance;
	int randomDots = 0;

	if (randomDotChance == 0 || System::random(randomDotChance) <= levelRank) {
		randomDots = 1;

		if (randomDotChance != 0 && System::random(randomDotChance) <= levelRank) {
			randomDots = System::random(1) + 1;
		}
	}

	if (randomDots == 0) {
		return;
	}

	int fireChance = fireDotChance * LootManager::DOTROLLCHANCE;
	int diseaseChance = (diseaseDotChance * LootManager::DOTROLLCHANCE) + fireChance;
	// int poisonChance = poisonDotChance * LootManager::DOTROLLCHANCE;

	int mindChance = mindDotChance * LootManager::DOTROLLCHANCE;
	int actionChance = (actionDotChance * LootManager::DOTROLLCHANCE) + mindChance;
	// int healthChance = healthDotChance * LootManager::DOTROLLCHANCE;

	for (int i = 0; i < randomDots; i++) {
		// Determine DOT type
		int typeChance = System::random(LootManager::DOTROLLCHANCE);
		int dotType = LootManager::DOT_POISON;

		if (typeChance < fireChance) {
			dotType = LootManager::DOT_FIRE;
		} else if (typeChance < diseaseChance) {
			dotType = LootManager::DOT_DISEASE;
		} // DOT Type is poison

		// Determine DOT HAM attribute
		int attributeChance = System::random(LootManager::DOTROLLCHANCE);
		int attribute = CreatureAttribute::HEALTH;

		if (attributeChance < mindChance) {
			attribute = CreatureAttribute::MIND;
		} else if (attributeChance < actionChance) {
			attribute = CreatureAttribute::ACTION;
		} // DOT is a HEALTH attribute

		// Chance for HAM attribute to be a secondary for disease DOTs
		if (dotType == LootManager::DOT_DISEASE) {
			attribute += System::random(2);
		}

		float strMod = 1.f;
		float durMod = 1.f;

		if (dotType == LootManager::DOT_POISON) {
			strMod = 1.5f;
		} else if (dotType == LootManager::DOT_DISEASE) {
			strMod = 0.5f;
			durMod = 4.f;
		} else if (dotType == LootManager::DOT_FIRE) {
			durMod = 1.5f;
		}

		int strength = LootValues::getDistributedValue(randomDotStrength.get(0), randomDotStrength.get(1), level) * modifier * strMod;
		int duration = LootValues::getDistributedValue(randomDotDuration.get(0), randomDotDuration.get(1), level) * modifier * durMod;
		int potency = LootValues::getDistributedValue(randomDotPotency.get(0), randomDotPotency.get(1), level) * modifier;
		int uses = LootValues::getDistributedValue(randomDotUses.get(0), randomDotUses.get(1), level) * modifier;

		if (strength <= 0 || duration <= 0 || potency <= 0 || uses <= 0) {
			continue;
		}

		weapon->addDotType(dotType);
		weapon->addDotAttribute(attribute);
		weapon->addDotStrength(strength);
		weapon->addDotDuration(duration);
		weapon->addDotPotency(potency);
		weapon->addDotUses(uses);
	}

	weapon->addMagicBit(false);
}

float LootManagerImplementation::getRandomModifier(const LootItemTemplate* itemTemplate, int level, float excMod) {
	if (level <= 0 || excMod <= 0.f || itemTemplate == nullptr || itemTemplate->getLevelMax() == 0) {
		return 0.f;
	}

	if (excMod <= baseModifier) {
		float chance = LootValues::getLevelRankValue(level, 0.2f, 0.9f) * levelChance;

		if (System::random(yellowChance) <= chance) {
			excMod = yellowModifier;
		} else if (System::random(baseChance) <= chance) {
			excMod = baseModifier;
		} else {
			excMod = 0.f;
		}
	}

	int modMax = 0;
	int modMin = 0;

	if (excMod >= legendaryModifier) {
		modMax = legendaryModifier;
		modMin = exceptionalModifier;
	} else if (excMod >= exceptionalModifier) {
		modMax = exceptionalModifier;
		modMin = yellowModifier;
	} else if (excMod >= yellowModifier) {
		modMax = yellowModifier;
		modMin = baseModifier;
	} else if (excMod >= baseModifier) {
		modMax = baseModifier;
		modMin = 0.f;
	}

	return modMax == modMin ? modMin : LootValues::getDistributedValue(modMin, modMax, level) + baseModifier;
}
