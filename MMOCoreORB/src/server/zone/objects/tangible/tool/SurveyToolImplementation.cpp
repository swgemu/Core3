/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "engine/engine.h"

#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "templates/tangible/tool/SurveyToolTemplate.h"
#include "server/zone/objects/tangible/tool/sui/SurveyToolSetRangeSuiCallback.h"
#include "server/zone/objects/tangible/tool/sui/SurveyToolApproveRadioactiveSuiCallback.h"
#include "server/zone/objects/player/sessions/survey/SurveySession.h"

void SurveyToolImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	SurveyToolTemplate* surveyToolData = dynamic_cast<SurveyToolTemplate*>(templateData);

	if (surveyToolData == NULL) {
		throw Exception("invalid template for SurveyTool");
	}

	type = surveyToolData->getToolType();
	surveyType = surveyToolData->getSurveyType();
	surveyAnimation = surveyToolData->getSurveyAnimation();
	sampleAnimation = surveyToolData->getSampleAnimation();
}

void SurveyToolImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);
	menuResponse->addRadialMenuItem(135, 3, "@sui:tool_options");
	menuResponse->addRadialMenuItemToRadialID(135,133, 3, "@sui:survey_range");
}

int SurveyToolImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	PlayerObject* playerObject = player->getPlayerObject();

	if(isASubChildOf(player)) {
		if (!playerObject->hasAbility("survey")) {
			player->sendSystemMessage("@error_message:insufficient_skill");
			return 0;
		}

		if (selectedID == 20) { // use object
			int range = getRange(player);

			if(range <= 0 || range > 384) {
				sendRangeSui(player);
				return 0;
			}

			Locker locker(_this.getReferenceUnsafeStaticCast());

			ManagedReference<SurveySession*> session = player->getActiveSession(SessionFacadeType::SURVEY).castTo<SurveySession*>();
			if(session == NULL) {
				session = new SurveySession(player);
				session->initializeSession(_this.getReferenceUnsafeStaticCast());
			}

			session->setOpenSurveyTool(_this.getReferenceUnsafeStaticCast());

			ManagedReference<ResourceManager*> resourceManager = cast<ResourceManager*>(server->getZoneServer()->getResourceManager());
			if(resourceManager == NULL) {
				error("null resource manager");
				return 0;
			}
			resourceManager->sendResourceListForSurvey(player, getToolType(), getSurveyType());

			return 0;
		}

		if (selectedID == 133) { // Set Tool Range

			sendRangeSui(player);

			return 0;
		}
	}

	return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

void SurveyToolImplementation::sendRangeSui(CreatureObject* player) {
	int surveyMod = player->getSkillMod("surveying");

	ManagedReference<SuiListBox*> suiToolRangeBox = new SuiListBox(player, SuiWindowType::SURVEY_TOOL_RANGE, 0);

	suiToolRangeBox->setPromptTitle("@base_player:swg");
	suiToolRangeBox->setPromptText("@survey:select_range");

	if (surveyMod >= 20)
		suiToolRangeBox->addMenuItem("64m x 3pts", 0);

	if (surveyMod >= 35)
		suiToolRangeBox->addMenuItem("128m x 4pts", 1);

	if (surveyMod >= 55)
		suiToolRangeBox->addMenuItem("192m x 4pts", 2);

	if (surveyMod >= 75)
		suiToolRangeBox->addMenuItem("256m x 5pts", 3);

	if (surveyMod >= 100)
		suiToolRangeBox->addMenuItem("320m x 5pts", 4);

	if (surveyMod >= 120)
		suiToolRangeBox->addMenuItem("384m x 5pts", 5);

	suiToolRangeBox->setUsingObject(_this.getReferenceUnsafeStaticCast());
	suiToolRangeBox->setCallback(new SurveyToolSetRangeSuiCallback(server->getZoneServer()));
	player->getPlayerObject()->addSuiBox(suiToolRangeBox);
	player->sendMessage(suiToolRangeBox->generateMessage());
}

int SurveyToolImplementation::getRange(CreatureObject* player) {

	int surveyMod = player->getSkillMod("surveying");
	int rangeBasedOnSkill = getSkillBasedRange(surveyMod);

	if (range > rangeBasedOnSkill)
		setRange(rangeBasedOnSkill);

	return range;
}

int SurveyToolImplementation::getSkillBasedRange(int skillLevel) {

	if (skillLevel >= 120)
		return 384;
	else if (skillLevel >= 100)
		return 320;
	else if (skillLevel >= 75)
		return 256;
	else if (skillLevel >= 55)
		return 192;
	else if (skillLevel >= 35)
		return 128;
	else if (skillLevel >= 20)
		return 64;

	return 0;
}

void SurveyToolImplementation::setRange(int r) {
	range = r;  // Distance the tool checks during survey

	// Set number of grid points in survey SUI 3x3 to 5x5
	if (range >= 256) {
		points = 5;
	} else if (range >= 128) {
		points = 4;
	} else {
		points = 3;
	}
}

void SurveyToolImplementation::sendRadioactiveWarning(CreatureObject* player) {

	ManagedReference<SuiMessageBox* > messageBox = new SuiMessageBox(player, SuiWindowType::SAMPLE_RADIOACTIVE_CONFIRM);
	messageBox->setPromptTitle("Confirm Radioactive Sample");
	messageBox->setPromptText("Sampling a radioactive material will result in harmful effects. Are you sure you wish to continue?");
	messageBox->setCancelButton(true, "");

	messageBox->setCallback(new SurveyToolApproveRadioactiveSuiCallback(server->getZoneServer()));
	messageBox->setUsingObject(_this.getReferenceUnsafeStaticCast());

	player->getPlayerObject()->addSuiBox(messageBox);

	player->sendMessage(messageBox->generateMessage());
}

void SurveyToolImplementation::consentRadioactiveSample(CreatureObject* player) {
	radioactiveOk = true;

	player->sendSystemMessage("@survey:radioactive_sample_unknown");
}
