/*
 * ShipAgentTemplate.cpp
 *
 * Created on: 2024/11/01
 * Author: Hakry
 */

#include "ShipAgentTemplate.h"
#include "server/zone/managers/ship/ShipAgentTemplateManager.h"

// Constructor
ShipAgentTemplate::ShipAgentTemplate() {
	templateName = "";

	shipTemplate = "";
	pilotTemplate = "";
	shipType = "";

	experience = 0;

	lootChance = 0.f;
	lootRolls = 0;
	lootTable = "";

	minCredits = 0;
	maxCredits = 0;

	aggressive = 0;

	spaceFaction = "";

	imperialFactionReward = 0;
	rebelFactionReward = 0;

	color1 = 0;
	color2 = 0;
	texture = 0;

	questLoot = "";
	interiorChassis = "";
	formationLocation = 0;
	appearance = "";

	tauntType = "";
	tauntAttackChance = 0.f;
	tauntDefendChance = 0.f;
	tauntDieChance = 0.f;
	tauntAggressiveness = 0.f;

	pvpBitmask = 0;
	shipBitmask = 0;
	optionsBitmask = 0;

	customShipAiMap = 0;

	conversationTemplate = 0;
	conversationMobile = 0;
	conversationMessage = 0;
}

// Destructor
ShipAgentTemplate::~ShipAgentTemplate() {
}

void ShipAgentTemplate::readObject(LuaObject* templateData) {
	shipTemplate = templateData->getStringField("template").trim();
	pilotTemplate = templateData->getStringField("pilotTemplate").trim();
	shipType = templateData->getStringField("shipType").trim();

	experience = templateData->getIntField("experience");

	lootChance = templateData->getFloatField("lootChance");
	lootRolls = templateData->getIntField("lootRolls");
	lootTable = templateData->getStringField("lootTable").trim();

	minCredits = templateData->getIntField("minCredits");
	maxCredits = templateData->getIntField("maxCredits");

	aggressive = templateData->getIntField("aggressive");

	spaceFaction = templateData->getStringField("spaceFaction").trim();

	// Vector<String> alliedFactions;
	LuaObject allies = templateData->getObjectField("alliedFactions");

	if (allies.isValidTable()) {
		for (int i = 1; i <= allies.getTableSize(); ++i) {
			String ally = allies.getStringAt(i).trim();

			alliedFactions.add(ally);
		}
	}

	allies.pop();

	// Vector<String> enemyFactions;
	LuaObject enemies = templateData->getObjectField("enemyFactions");

	if (enemies.isValidTable()) {
		for (int i = 1; i <= enemies.getTableSize(); ++i) {
			String enemy = enemies.getStringAt(i).trim();

			enemyFactions.add(enemy);
		}
	}

	enemies.pop();

	imperialFactionReward = templateData->getIntField("imperialFactionReward");
	rebelFactionReward = templateData->getIntField("rebelFactionReward");

	color1 = templateData->getIntField("color1");
	color2 = templateData->getIntField("color2");
	texture = templateData->getIntField("texture");

	questLoot = templateData->getStringField("questLoot").trim();
	interiorChassis = templateData->getStringField("interiorChassis").trim();
	formationLocation = templateData->getIntField("formationLocation");
	appearance = templateData->getStringField("appearance").trim();

	tauntType = templateData->getStringField("tauntType").trim();
	tauntAttackChance = templateData->getFloatField("tauntAttackChance");
	tauntDefendChance = templateData->getFloatField("tauntDefendChance");
	tauntDieChance = templateData->getFloatField("tauntDieChance");
	tauntAggressiveness = templateData->getFloatField("tauntAggressiveness");

	pvpBitmask = templateData->getIntField("pvpBitmask");
	shipBitmask = templateData->getIntField("shipBitmask");
	optionsBitmask = templateData->getIntField("optionsBitmask");

	if (!templateData->getStringField("customShipAiMap").isEmpty()) {
		customShipAiMap = templateData->getStringField("customShipAiMap").hashCode();
	}

	conversationTemplate = String(templateData->getStringField("conversationTemplate").trim()).hashCode();
	conversationMobile = String(templateData->getStringField("conversationMobile").trim()).hashCode();
	conversationMessage = String(templateData->getStringField("conversationMessage").trim()).hashCode();
}
