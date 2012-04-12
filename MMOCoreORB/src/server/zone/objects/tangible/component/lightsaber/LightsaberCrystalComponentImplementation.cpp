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
		alm->insertAttribute("wpn_attack_speed", attackSpeed);
		alm->insertAttribute("mindamage", minimumDamage);
		alm->insertAttribute("maxdamage", maximumDamage);
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
		setQuality(0);
		int max = MAX(0, MIN(15, round(0.1f * level + 5)));
		int min = MAX(0, MIN(15, round(0.075f * level - 1)));
		int mod = System::random(max - min) + min;

		if (level > 250)
			mod += 15; // Special Color range.

		setColor(mod);
		updateCrystal(mod);
	}

	if (getCrystalType() == "power") {
		int max = MAX(0, MIN(6, round(0.1f * level + 5)));
		int min = MAX(0, MIN(6, round(0.075f * level - 1)));
		int mod = System::random(max - min) + min;

		setQuality(mod);
		setColor(31);
		updateCrystal(31);
	}

	// TODO: Need to get data on crystal gates.

	switch (getQuality()){
	case 0:
		attackSpeed = (2 - System::random(1));
		minimumDamage = (2 + System::random(5));
		maximumDamage = (3 + System::random(5));
		sacHealth = (10 - System::random(5));
		sacAction = (10 - System::random(5));
		sacMind = (10 - System::random(5));
		forceCost = (10 - System::random(5));
		break;
	case 1:
		attackSpeed = (1 - System::random(1));
		minimumDamage = (5 + System::random(5));
		maximumDamage = (10 + System::random(10));
		sacHealth = (9 - System::random(6));
		sacAction = (9 - System::random(6));
		sacMind = (9 - System::random(6));
		forceCost = (9 - System::random(6));
		break;
	case 2:
		attackSpeed = (1 - System::random(1));
		minimumDamage = (10 + System::random(5));
		maximumDamage = (15 + System::random(10));
		sacHealth = (8 - System::random(7));
		sacAction = (8 - System::random(7));
		sacMind = (8 - System::random(7));
		forceCost = (8 - System::random(7));
		break;
	case 3:
		attackSpeed = (1 - System::random(1));
		minimumDamage = (15 + System::random(5));
		maximumDamage = (20 + System::random(10));
		sacHealth = (7 - System::random(9));
		sacAction = (7 - System::random(9));
		sacMind = (7 - System::random(9));
		forceCost = (7 - System::random(9));
		break;
	case 4:
		attackSpeed = (1 - System::random(1));
		minimumDamage = (20 + System::random(5));
		maximumDamage = (25 + System::random(10));
		sacHealth = (6 - System::random(10));
		sacAction = (6 - System::random(10));
		sacMind = (6 - System::random(10));
		forceCost = (6 - System::random(10));
		break;
	case 5:
		attackSpeed = (1 - System::random(1));
		minimumDamage = (40 + System::random(10));
		maximumDamage = (45 + System::random(5));
		sacHealth = (5 - System::random(14));
		sacAction = (5 - System::random(14));
		sacMind = (5 - System::random(14));
		forceCost = (5 - System::random(14));
		break;
	case 6:
		attackSpeed = (1 - System::random(1));
		minimumDamage = (40 + System::random(10));
		maximumDamage = (45 + System::random(5));
		sacHealth = (5 - System::random(14));
		sacAction = (5 - System::random(14));
		sacMind = (5 - System::random(14));
		forceCost = (5 - System::random(14));
		break;
	}

	setAttackSpeed(attackSpeed);
	setMinimumDamage(minimumDamage);
	setMaximumDamage(maximumDamage);
	setSacHealth(sacHealth);
	setSacAction(sacAction);
	setSacMind(sacMind);
	setForceCost(forceCost);

}
