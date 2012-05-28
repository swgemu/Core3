/*
 * SurveySessionImplementation.cpp
 *
 *  Created on: May 22, 2012
 *      Author: Kyle
 */

#include "SurveySession.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/player/sessions/survey/sui/SurveyGMinigameSuiCallback.h"
#include "server/zone/objects/player/sessions/survey/sui/SurveyCMinigameSuiCallback.h"
#include "server/zone/managers/resource/resourcespawner/SampleTask.h"

int SurveySessionImplementation::initializeSession(SurveyTool* tool) {

	activeSurveyTool = tool;
	surveyerGhost = surveyer->getPlayerObject();
	return startSession();
}

int SurveySessionImplementation::startSession() {

	if(surveyer == NULL || activeSurveyTool == NULL || surveyerGhost == NULL) {
		cancelSession();
		return false;
	}

	resourceManager = surveyer->getZoneServer()->getResourceManager();
	if(resourceManager == NULL) {
		cancelSession();
		return false;
	}

	surveyer->addActiveSession(SessionFacadeType::SURVEY, _this);

	return true;
}

int SurveySessionImplementation::cancelSession() {

	if(surveyer != NULL)
		surveyer->dropActiveSession(SessionFacadeType::SURVEY);


	return clearSession();
}

int SurveySessionImplementation::clearSession() {

	return 0;
}

void SurveySessionImplementation::startSurvey(const String& resname) {

	if (activeSurveyTool == NULL) {
		error("surveyTool is NULL");
		return;
	}

	if (resourceManager == NULL) {
		error("ResourceManager is NULL");
		return;
	}

	if (surveyer == NULL) {
		error("surveyer is NULL");
		return;
	}

	if (surveyer->getParent() != NULL && surveyer->getParent()->isCellObject()) {
		surveyer->sendSystemMessage("@error_message:survey_in_structure"); //You cannot perform survey-related actions inside a structure.
		return;
	}

	if (surveyer->isSwimming()) {
		surveyer->sendSystemMessage("@error_message:survey_swimming");
		return;
	}

	if (surveyer->isMounted()) {
		if(surveyer->isInWater()) {
			surveyer->sendSystemMessage("@error_message:survey_cant");
			return;
		}
	} else {
		if(surveyer->getPosture() != CreaturePosture::UPRIGHT) {
			surveyer->sendSystemMessage("@error_message:survey_standing");
			return;
		}
	}

	if (surveyer->getHAM(CreatureAttribute::MIND) < 100) {
		surveyer->setPosture(CreaturePosture::UPRIGHT, true);
		surveyer->sendSystemMessage("@error_message:survey_mind"); //You are exhausted. You nee to clear your head before you can survey again.
		return;
	}

	ManagedReference<ResourceSpawn*> spawn = resourceManager->getResourceSpawn(resname);
	if(spawn == NULL) {
		return;
	}

	if(spawn->getSurveyToolType() != activeSurveyTool->getToolType()) {
		StringIdChatParameter message("@survey:wrong_tool"); // %TO resources cannot be located with this tool
		message.setTO(spawn->getFinalClass());
		surveyer->sendSystemMessage(message);
		return;
	}

	PlayClientEffectLoc* effect = new PlayClientEffectLoc(activeSurveyTool->getSurveyAnimation(),
			surveyer->getZone()->getZoneName(),
			surveyer->getPositionX(), surveyer->getPositionZ(),
			surveyer->getPositionY());

	surveyer->broadcastMessage(effect, true);

	resourceManager->sendSurvey(surveyer, resname);
}

void SurveySessionImplementation::startSample(const String& resname) {

	if (activeSurveyTool == NULL) {
		error("surveyTool is NULL");
		return;
	}

	if (resourceManager == NULL) {
		info("ResourceManager is NULL");
		return;
	}

	if (surveyer == NULL) {
		info("surveyer is NULL");
		return;
	}

	if (!resname.isEmpty())
		 lastResourceSampleName = resname;

	ManagedReference<ResourceSpawn* > resourceSpawn = resourceManager->getResourceSpawn(lastResourceSampleName);
	if (resourceSpawn == NULL) {
		return;
	}

	if (surveyer->getParent() != NULL && surveyer->getParent()->isCellObject()) {
		surveyer->sendSystemMessage("@error_message:survey_in_structure"); //You cannot perform survey-related actions inside a structure.
		return;
	}

	if (surveyer->isSwimming()) {
		surveyer->sendSystemMessage("@error_message:survey_swimming");
		return;
	}

	if (surveyer->isMounted()) {
		surveyer->sendSystemMessage("@error_message:survey_on_mount");
		return;
	}

	if (surveyer->getHAM(CreatureAttribute::ACTION) < 200) {
		surveyer->setPosture(CreaturePosture::UPRIGHT, true);
		surveyer->sendSystemMessage("@error_message:survey_mind"); //You are exhausted. You nee to clear your head before you can survey again.
		return;
	}

	if(resourceSpawn->getSurveyToolType() != activeSurveyTool->getToolType()) {
		StringIdChatParameter message("@survey:wrong_tool"); // %TO resources cannot be located with this tool
		message.setTO(resourceSpawn->getFinalClass());
		surveyer->sendSystemMessage(message);
		return;
	}

	if(!lastResourceSampleName.isEmpty() && !activeSurveyTool->canSampleRadioactive()) {

		if(resourceSpawn->isType("radioactive") && !activeSurveyTool->canSampleRadioactive()) {
			activeSurveyTool->sendRadioactiveWarning(surveyer);
			return;
		}
	}

	// Player must be kneeling to sample
	if (!surveyer->isKneeling()) {
		surveyer->setPosture(CreaturePosture::CROUCHED, true);
	}

	if(surveyer->getPendingTask("sample") != NULL) {
		return;
	}

	StringIdChatParameter message("survey","start_sampling");
	message.setTO(lastResourceSampleName);
	surveyer->sendSystemMessage(message);

	if (!doGamble && richSampleLocation == NULL && System::random(50) == 7) {

		if(System::random(1) == 1)
			surveyCnodeMinigameSui();
		else
			surveyGnodeMinigameSui();

	} else {

		if (!lastResourceSampleName.isEmpty())
			resourceManager->sendSample(surveyer, lastResourceSampleName,
					activeSurveyTool->getSampleAnimation());
	}
}

void SurveySessionImplementation::surveyCnodeMinigameSui() {
	int surveyMod = surveyer->getSkillMod("surveying");

	ManagedReference<SuiListBox*> suiConcMinigameBox = new SuiListBox(
			surveyer, SuiWindowType::SURVEY_TOOL_CONCENTRATED_MINIGAME, 0);

	suiConcMinigameBox->setPromptTitle("@survey:cnode_t");
	suiConcMinigameBox->setPromptText("@survey:cnode_d");

	suiConcMinigameBox->addMenuItem("@survey:cnode_1", 0);
	suiConcMinigameBox->addMenuItem("@survey:cnode_2", 1);

	suiConcMinigameBox->setCancelButton(true, "Cancel");

	suiConcMinigameBox->setCallback(new SurveyCMinigameSuiCallback(surveyer->getZoneServer()));
	surveyer->getPlayerObject()->addSuiBox(suiConcMinigameBox);
	surveyer->sendMessage(suiConcMinigameBox->generateMessage());
}

void SurveySessionImplementation::surveyCnodeMinigame(int value) {

	if(value == 0) {
		// Add sampletask
		Reference<SampleTask*> sampleTask = new SampleTask(surveyer, activeSurveyTool);
		surveyer->addPendingTask("sample", sampleTask, 18000);

		return;
	}

	richSampleLocation = new Coordinate(surveyer->getPositionX(), surveyer->getPositionZ(), surveyer->getPositionY());
	richSampleLocation->randomizePosition(50);

	ManagedReference<WaypointObject*> newwaypoint = NULL;

	PlayerObject* ghost = surveyer->getPlayerObject();

	// Get previous survey waypoint
	ManagedReference<WaypointObject*> waypoint = ghost->getSurveyWaypoint();

	// Create new waypoint
	if (waypoint == NULL)
		newwaypoint = cast<WaypointObject*>( surveyer->getZoneServer()->createObject(0xc456e788, 1));
	else {
		ghost->removeWaypoint(waypoint->getObjectID(), true);
		newwaypoint = waypoint.get();
	}

	// Update new waypoint
	newwaypoint->setCustomObjectName(UnicodeString("Resource Survey"), false);
	newwaypoint->setPlanetCRC(surveyer->getZone()->getZoneCRC());
	newwaypoint->setPosition(richSampleLocation->getPositionX(), 0, richSampleLocation->getPositionY());
	newwaypoint->setColor(WaypointObject::COLOR_BLUE);
	newwaypoint->setSpecialTypeID(WaypointObject::SPECIALTYPE_RESOURCE);
	newwaypoint->setActive(true);

	ghost->addWaypoint(newwaypoint, false, true); // Should second argument be true, and waypoints with the same name thus remove their old version?
	surveyer->sendSystemMessage("@survey:node_waypoint");

	// Player must be kneeling to sample
	if (!surveyer->isStanding())
		surveyer->setPosture(CreaturePosture::UPRIGHT, true);
}

void SurveySessionImplementation::surveyGnodeMinigameSui() {
	int surveyMod = surveyer->getSkillMod("surveying");

	ManagedReference<SuiListBox*> suiConcMinigameBox = new SuiListBox(
			surveyer, SuiWindowType::SURVEY_TOOL_CONCENTRATED_MINIGAME2, 0);

	suiConcMinigameBox->setPromptTitle("@survey:gnode_t");
	suiConcMinigameBox->setPromptText("@survey:gnode_d");

	suiConcMinigameBox->addMenuItem("@survey:gnode_1", 0);
	suiConcMinigameBox->addMenuItem("@survey:gnode_2", 1);

	suiConcMinigameBox->setCancelButton(true, "Cancel");

	suiConcMinigameBox->setCallback(new SurveyGMinigameSuiCallback(surveyer->getZoneServer()));
	surveyer->getPlayerObject()->addSuiBox(suiConcMinigameBox);
	surveyer->sendMessage(suiConcMinigameBox->generateMessage());
}

void SurveySessionImplementation::surveyGnodeMinigame(int value) {

	if(value == 1) {

		if(surveyer->getHAM(CreatureAttribute::ACTION) < 300) {
			surveyer->sendSystemMessage("@survey:gamble_no_action");
			return;
		}

		surveyer->inflictDamage(surveyer, CreatureAttribute::ACTION, 300, false, true);
		doGamble = true;
	}

	// Add sampletask
	Reference<SampleTask*> sampleTask = new SampleTask(surveyer, activeSurveyTool);
	surveyer->addPendingTask("sample", sampleTask, 18000);

}
