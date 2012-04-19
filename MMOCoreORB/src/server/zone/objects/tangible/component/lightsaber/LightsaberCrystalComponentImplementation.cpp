/*
 * LightsaberCrystalComponentImplementation.cpp
 *
 *      Author: Katherine
 */

#include "engine/engine.h"


#include "server/zone/objects/tangible/component/Component.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "LightsaberCrystalComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/templates/tangible/LightsaberCrystalObjectTemplate.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/callbacks/LightsaberCrystalTuneSuiCallback.h"

void LightsaberCrystalComponentImplementation::initializeTransientMembers() {
	ComponentImplementation::initializeTransientMembers();

	lightsaberCrystalObjectTemplate = dynamic_cast<LightsaberCrystalObjectTemplate*>(TemplateManager::instance()->getTemplate(serverObjectCRC));

	setLoggingName("LightsaberCrystalComponent");
}


void LightsaberCrystalComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ComponentImplementation::loadTemplateData(templateData);

	lightsaberCrystalObjectTemplate = dynamic_cast<LightsaberCrystalObjectTemplate*>(templateData);

	crystalType = lightsaberCrystalObjectTemplate->getCrystalType();

	setCrystalType(crystalType);
}

void LightsaberCrystalComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	ComponentImplementation::fillAttributeList(alm, object);

	if (owner == ""){
		StringBuffer str;
		str << "\\#FF6600" << "UNTUNED" ;
		alm->insertAttribute("crystal_owner", str);
	} else {
		alm->insertAttribute("crystal_owner", owner);
	}


	if (getCrystalType() == "color"){
	StringBuffer str;
	str << "@jedi_spam:saber_color_" << getColor();
	alm->insertAttribute("color", str);
	}

	PlayerObject* player = object->getPlayerObject();
	if (player->getJediState() > 1){

	if (getCrystalType() == "power"){
		if (owner != ""){
		alm->insertAttribute("mindamage", minimumDamage);
		alm->insertAttribute("maxdamage", maximumDamage);
		alm->insertAttribute("wpn_attack_speed", attackSpeed);
		alm->insertAttribute("wpn_wound_chance", woundChance);
		alm->insertAttribute("wpn_attack_cost_health", sacHealth);
		alm->insertAttribute("wpn_attack_cost_action", sacAction);
		alm->insertAttribute("wpn_attack_cost_mind", sacMind);
		alm->insertAttribute("forcecost", forceCost);
	} else {
		StringBuffer str;
		str << "@jedi_spam:crystal_quality_" << getQuality();
		alm->insertAttribute("quality", str);
		}
	}
	}

}


void LightsaberCrystalComponentImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	ComponentImplementation::fillObjectMenuResponse(menuResponse, player);

	if ((owner == "") && player->hasSkill("force_title_jedi_rank_01")){
	String text = "@jedi_spam:tune_crystal";
	menuResponse->addRadialMenuItem(128, 3, text);
	}
}

int LightsaberCrystalComponentImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	if (selectedID == 128) {
	
		ManagedReference<SuiMessageBox*> suiMessageBox = new SuiMessageBox(player, SuiWindowType::TUNE_CRYSTAL);

		suiMessageBox->setPromptTitle("@jedi_spam:confirm_tune_title");
		suiMessageBox->setPromptText("@jedi_spam:confirm_tune_prompt");
		suiMessageBox->setCancelButton(true, "Cancel");
		suiMessageBox->setUsingObject(_this);
		suiMessageBox->setCallback(new LightsaberCrystalTuneSuiCallback(player->getZoneServer()));


		player->getPlayerObject()->addSuiBox(suiMessageBox);
		player->sendMessage(suiMessageBox->generateMessage());

	}

	return 0;
}

void LightsaberCrystalComponentImplementation::tuneCrystal(CreatureObject* player) {

	String name = player->getDisplayedName();

	setOwner(name);


	UnicodeString oldName = _this->getDisplayedName(); // Get the displayed name, which is in a string file format and change it to literal.

	if (oldName == "@craft_weapon_ingredients_n:force_crystal")
		_this->setCustomObjectName("Crystal", false);

	if (oldName == "@craft_weapon_ingredients_n:krayt_dragon_pearl")
		_this->setCustomObjectName("Krayt Dragon Pearl", false);


	StringBuffer newName;

	newName << "\\#00FF00" << _this->getCustomObjectName().toString() << " (tuned)";
	_this->setCustomObjectName(newName.toString(), true);

	player->sendSystemMessage("@jedi_spam:crystal_tune_success");

}

void LightsaberCrystalComponentImplementation::updateCrystal(int value){

	byte type = 0x02;

	_this->setCustomizationVariable(type, value, true);

}

void LightsaberCrystalComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	int level = values->getMaxValue("creatureLevel");


	int rand = System::random(1);

	if (getCrystalType() == "colorAndPower"){
		if (rand == 1)
		{
			crystalType = "power";
		}
		else if (rand == 0)
		{
			crystalType = "color";
		}
	}

	setCrystalType(crystalType);

	if (getCrystalType() == "color"){
		int mod = System::random(11); // Regular Color range 0-11. Special range 12-30.

		setColor(mod);
		updateCrystal(mod);
	}

	if (getCrystalType() == "power") {
		int max = MAX(0, MIN(6, round(0.1f * level + 5)));
		int min = MAX(0, MIN(6, round(0.075f * level)));
		int mod = System::random(max - min) + min;

		setQuality(mod);
		setColor(31);
		updateCrystal(31);
	}

	// Seems about right according to posted screenshots...

	switch (getQuality()){
	case 0: // Poor
		attackSpeed = (2.00 - System::random(1.25));
		minimumDamage = (2 + System::random(4));
		maximumDamage = (3 + System::random(4));
		woundChance = (1 + System::random(2));
		sacHealth = (0 - System::random(4));
		sacAction = (0 - System::random(4));
		sacMind = (0 - System::random(4));
		forceCost = (0 - System::random(4));
		break;
	case 1: // Good
		attackSpeed = (1.80 - System::random(1.25));
		minimumDamage = (5 + System::random(5));
		maximumDamage = (10 + System::random(10));
		woundChance = (2 + System::random(2));
		sacHealth = (0 - System::random(4));
		sacAction = (0 - System::random(4));
		sacMind = (0 - System::random(4));
		forceCost = (0 - System::random(4));
		break;
	case 2: // Okay
		attackSpeed = (1.60 - System::random(1.25));
		minimumDamage = (10 + System::random(5));
		maximumDamage = (15 + System::random(10));
		woundChance = (2 + System::random(3));
		sacHealth = (0 - System::random(5));
		sacAction = (0 - System::random(5));
		sacMind = (0 - System::random(5));
		forceCost = (0 - System::random(5));
		break;
	case 3: // Quality
		attackSpeed = (1.40 - System::random(1.25));
		minimumDamage = (15 + System::random(5));
		maximumDamage = (20 + System::random(10));
		woundChance = (3 + System::random(3));
		sacHealth = (0 - System::random(6));
		sacAction = (0 - System::random(6));
		sacMind = (0 - System::random(6));
		forceCost = (0 - System::random(6));
		break;
	case 4: // Select
		attackSpeed = (1.20 - System::random(1.25));
		minimumDamage = (20 + System::random(5));
		maximumDamage = (25 + System::random(10));
		woundChance = (3 + System::random(4));
		sacHealth = (0 - System::random(7));
		sacAction = (0 - System::random(7));
		sacMind = (0 - System::random(7));
		forceCost = (0 - System::random(7));
		break;
	case 5: // Premium
		attackSpeed = (1.00 - System::random(1.25));
		minimumDamage = (30 + System::random(20));
		maximumDamage = (35 + System::random(15));
		woundChance = (4 + System::random(4));
		sacHealth = (0 - System::random(8));
		sacAction = (0 - System::random(8));
		sacMind = (0 - System::random(8));
		forceCost = (0 - System::random(8));
		break;
	case 6: // Flawless
		attackSpeed = (0.80 - System::random(1.25));
		minimumDamage = (40 + System::random(10));
		maximumDamage = (45 + System::random(5));
		woundChance = (4 + System::random(5));
		sacHealth = (0 - System::random(9));
		sacAction = (0 - System::random(9));
		sacMind = (0 - System::random(9));
		forceCost = (0 - System::random(9));
		break;
	}

	setAttackSpeed(attackSpeed);
	setMinimumDamage(minimumDamage);
	setMaximumDamage(maximumDamage);
	setWoundChance(woundChance);
	setSacHealth(sacHealth);
	setSacAction(sacAction);
	setSacMind(sacMind);
	setForceCost(forceCost);

}
