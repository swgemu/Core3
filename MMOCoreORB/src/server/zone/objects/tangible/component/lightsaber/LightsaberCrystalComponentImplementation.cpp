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

	setLoggingName("LightsaberCrystalComponent");

}

void LightsaberCrystalComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	lcoTemplate = dynamic_cast<LightsaberCrystalObjectTemplate*>(templateData);

	postTuneName = lcoTemplate->getPostTunedName();
}

void LightsaberCrystalComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	if (owner == ""){
		StringBuffer str;
		str << "\\#FF6600" << "UNTUNED" ;
		alm->insertAttribute("crystal_owner", str);
	} else {
		alm->insertAttribute("crystal_owner", owner);
	}


	if (getColor() != 31){
	StringBuffer str;
	str << "@jedi_spam:saber_color_" << getColor();
	alm->insertAttribute("color", str);
	}

	PlayerObject* player = object->getPlayerObject();
	if (player->getJediState() > 1){

	if (getColor() == 31){
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

	// Color code is lime green.
	String tuneName = "\\#00FF00" + postTuneName + " (tuned)";

	setCustomObjectName(tuneName, true);

	player->sendSystemMessage("@jedi_spam:crystal_tune_success");

}

void LightsaberCrystalComponentImplementation::updateCrystal(int value){

	byte type = 0x02;

	setCustomizationVariable(type, value, true);

}

void LightsaberCrystalComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ComponentImplementation::updateCraftingValues(values, firstUpdate);

	int color = values->getCurrentValue("color");
	setColor(color);


	if (color == 31){
		setQuality(values->getCurrentValue("quality"));
		setAttackSpeed(Math::getPrecision(values->getCurrentValue("attackspeed"), 2));
		setMinimumDamage(values->getCurrentValue("mindamage"));
		setMaximumDamage(values->getCurrentValue("maxdamage"));
		setWoundChance(values->getCurrentValue("woundchance"));
		setSacHealth(values->getCurrentValue("attackhealthcost"));
		setSacAction(values->getCurrentValue("attackactioncost"));
		setSacMind(values->getCurrentValue("attackmindcost"));
		setForceCost(values->getCurrentValue("forcecost"));
	}

	updateCrystal(color);

}
