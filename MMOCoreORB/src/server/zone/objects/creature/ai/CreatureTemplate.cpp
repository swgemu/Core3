/*
 * CreatureTemplate.cpp
 *
 *  Created on: 22/01/2012
 *      Author: victor
 */

#include "CreatureTemplate.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"

CreatureTemplate::CreatureTemplate() {
	conversationTemplate = 0;
	kinetic = 0;
	energy = 0;
	electricity = 0;
	stun = 0;
	blast = 0;
	heat = 0;
	cold = 0;
	acid = 0;
	lightSaber = 0;

	scale = 1.f;

	objectName = "";
	randomNameType = 0;
	mobType = 0;
	randomNameTag = false;
	customName = "";
	planetMapCategory = 0;
	mapCategoryName = "";
	planetMapSubCategory = 0;
	mapSubCategoryName = "";
	socialGroup = "";
	faction = "";
	level = 0;
	chanceHit = 0.f;
	damageMin = 0;
	damageMax = 0;
	attackSpeed = 0.0f;
	specialDamageMult = 1.f;
	range = 0;
	baseXp = 0;
	baseHAM = 0;
	baseHAMmax = 0;
	armor = 0;
	meatType = "";
	meatAmount = 0;
	hideType = "";
	hideAmount = 0;
	boneType = "";
	boneAmount = 0;
	milkType = "";
	milk = 0.f;
	tamingChance = 0.f;
	ferocity = 0;
	aggroRadius = 0;
	pvpBitmask = 0;
	creatureBitmask = 0;
	diet = 0;
	optionsBitmask = 0;
	customAiMap = 0;
	tauntable = true;
	healerType = "";
	lightsaberColor = 0;

	primaryWeapon = "";
	secondaryWeapon = "";
	thrownWeapon = "",

	templates.removeAll();

	primaryAttacks = new CreatureAttackMap();
	secondaryAttacks = new CreatureAttackMap();

	aiTemplate = "example";
	defaultWeapon = "";
	defaultAttack = "defaultattack";
	controlDeviceTemplate = "object/intangible/pet/pet_control.iff";
	containerComponentTemplate = "";
	reactionStf = "";
	personalityStf = "";
}

CreatureTemplate::~CreatureTemplate() {
	templates.removeAll();

	delete primaryAttacks;
	primaryAttacks = nullptr;

	delete secondaryAttacks;
	secondaryAttacks = nullptr;
}

void CreatureTemplate::readObject(LuaObject* templateData) {
	conversationTemplate = String(templateData->getStringField("conversationTemplate").trim()).hashCode();
	objectName = templateData->getStringField("objectName").trim();
	randomNameType = templateData->getIntField("randomNameType");
	randomNameTag = templateData->getBooleanField("randomNameTag");

	mapCategoryName = String(templateData->getStringField("planetMapCategory").trim());
	planetMapCategory = mapCategoryName.hashCode();

	mapSubCategoryName = String(templateData->getStringField("planetMapSubCategory").trim());
	planetMapSubCategory = mapSubCategoryName.hashCode();

	mobType = templateData->getIntField("mobType");

	customName = templateData->getStringField("customName").trim();
	socialGroup = templateData->getStringField("socialGroup").trim();
	faction = templateData->getStringField("faction").trim().toLowerCase();
	level = templateData->getIntField("level");
	chanceHit = templateData->getFloatField("chanceHit");
	damageMin = templateData->getIntField("damageMin");
	damageMax = templateData->getIntField("damageMax");
	specialDamageMult = templateData->getFloatField("specialDamageMult");
	attackSpeed = templateData->getFloatField("attackSpeed");
	if (specialDamageMult < 0.001f) specialDamageMult = 1.f; // could use numeric_limit here, but this will prevent people from putting tiny modifiers in as well.
	baseXp = templateData->getIntField("baseXp");
	baseHAM = templateData->getIntField("baseHAM");
	baseHAMmax = templateData->getIntField("baseHAMmax");
	armor = templateData->getIntField("armor");
	meatType = templateData->getStringField("meatType").trim();
	meatAmount = templateData->getIntField("meatAmount");
	hideType = templateData->getStringField("hideType").trim();
	hideAmount = templateData->getIntField("hideAmount");
	boneType = templateData->getStringField("boneType").trim();
	boneAmount = templateData->getIntField("boneAmount");
	milk = templateData->getIntField("milk");
	tamingChance = templateData->getFloatField("tamingChance");
	ferocity = templateData->getIntField("ferocity");
	aggroRadius = templateData->getIntField("aggroRadius");
	pvpBitmask = templateData->getIntField("pvpBitmask");
	creatureBitmask = templateData->getIntField("creatureBitmask");
	diet = templateData->getIntField("diet");
	optionsBitmask = templateData->getIntField("optionsBitmask");
	patrolPathTemplate = templateData->getStringField("patrolPathTemplate");
	defaultWeapon = templateData->getStringField("defaultWeapon");
	tauntable = templateData->getBooleanField("tauntable", true);
	healerType = templateData->getStringField("healerType").trim();
	lightsaberColor = templateData->getIntField("lightsaberColor");

	if(!templateData->getStringField("defaultAttack").isEmpty())
		defaultAttack = templateData->getStringField("defaultAttack");

	if(!templateData->getStringField("customAiMap").isEmpty())
		customAiMap = templateData->getStringField("customAiMap").hashCode();

	scale = templateData->getFloatField("scale");

	if (!templateData->getStringField("milkType").isEmpty()) {
		milkType = templateData->getStringField("milkType").trim();
	}

	LuaObject res = templateData->getObjectField("resists");
	if (res.getTableSize() == 9) {
		kinetic = res.getFloatAt(1);
		energy = res.getFloatAt(2);
		blast = res.getFloatAt(3);
		heat = res.getFloatAt(4);
		cold = res.getFloatAt(5);
		electricity = res.getFloatAt(6);
		acid = res.getFloatAt(7);
		stun = res.getFloatAt(8);
		lightSaber = res.getFloatAt(9);
	}

	res.pop();

	LuaObject temps = templateData->getObjectField("templates");
	if (temps.isValidTable()) {
		for (int i = 1; i <= temps.getTableSize(); ++i) {
			String tempName = temps.getStringAt(i).trim();

			if (tempName.endsWith(".iff")) {
				templates.add(tempName);
				continue;
			}

			const Vector<String>& dressGroup = CreatureTemplateManager::instance()->getDressGroup(tempName);
			templates.addAll(dressGroup);
		}
	}

	temps.pop();

	LuaObject lootCollections = templateData->getObjectField("lootGroups");
	lootgroups.readObject(&lootCollections, level);
	lootCollections.pop();

	primaryWeapon = templateData->getStringField("primaryWeapon");
	secondaryWeapon = templateData->getStringField("secondaryWeapon");
	thrownWeapon = templateData->getStringField("thrownWeapon");

	LuaObject attackList = templateData->getObjectField("primaryAttacks");
	if (attackList.isValidTable()) {
		int size = attackList.getTableSize();
		lua_State* L = attackList.getLuaState();
		for (int i = 1; i <= size; ++i) {
			lua_rawgeti(L, -1, i);
			LuaObject atk(L);

			if (atk.isValidTable()) {
				int atkSize = atk.getTableSize();
				if (atkSize == 2) {
					String com = atk.getStringAt(1).trim();
					String arg = atk.getStringAt(2).trim();

					primaryAttacks->addAttack(com, arg);
				}
			}

			atk.pop();
		}
	}

	attackList.pop();

	attackList = templateData->getObjectField("secondaryAttacks");
	if (attackList.isValidTable()) {
		int size = attackList.getTableSize();
		lua_State* L = attackList.getLuaState();
		for (int i = 1; i <= size; ++i) {
			lua_rawgeti(L, -1, i);
			LuaObject atk(L);

			if (atk.isValidTable()) {
				int atkSize = atk.getTableSize();
				if (atkSize == 2) {
					String com = atk.getStringAt(1).trim();
					String arg = atk.getStringAt(2).trim();

					secondaryAttacks->addAttack(com, arg);
				}
			}

			atk.pop();
		}
	}

	attackList.pop();

	LuaObject hueTable = templateData->getObjectField("hues");
	if (hueTable.isValidTable()) {
		for (int i = 1; i <= hueTable.getTableSize(); ++i) {
			hues.add(hueTable.getIntAt(i));
		}
	}

	hueTable.pop();

	outfit = templateData->getStringField("outfit");

	aiTemplate = templateData->getStringField("aiTemplate");

	if(!templateData->getStringField("controlDeviceTemplate").isEmpty())
		controlDeviceTemplate = templateData->getStringField("controlDeviceTemplate");

	containerComponentTemplate = templateData->getStringField("containerComponentTemplate");

	reactionStf = templateData->getStringField("reactionStf");
	personalityStf = templateData->getStringField("personalityStf");
}
