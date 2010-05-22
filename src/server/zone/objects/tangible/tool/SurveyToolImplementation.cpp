/*
Copyright (C) 2010 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 3 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "engine/engine.h"

#include "SurveyTool.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/resource/ResourceListForSurveyMessage.h"
#include "server/zone/templates/tangible/survey_tool/SurveyToolTemplate.h"


void SurveyToolImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	SurveyToolTemplate* surveyToolData = dynamic_cast<SurveyToolTemplate*>(templateData);

	type = surveyToolData->getToolType();
	surveyType = surveyToolData->getSurveyType();
}

void SurveyToolImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {

	menuResponse->addRadialMenuItem(135, 3, "@sui:tool_options");
	menuResponse->addRadialMenuItemToRadialID(135,133, 3, "@sui:survey_range");
}

int SurveyToolImplementation::handleObjectMenuSelect(PlayerCreature* playerCreature, byte selectedID) {

	String skill = "survey";
	PlayerObject* playerObject = playerCreature->getPlayerObject();

	if (!playerObject->hasSkill(skill)) {
		playerCreature->sendSystemMessage("error_message", "insufficient_skill");
		return 0;
	}

	if (selectedID == 20) { // use object

		playerCreature->setSurveyTool(_this);

		if(range > 0)
			sendResourceListTo(playerCreature);
		else
			sendRangeSui(playerCreature);

		return 0;
	}

	if (selectedID == 133) { // Set Tool Range
		sendRangeSui(playerCreature);
		return 0;
	}

	return 1;
}

void SurveyToolImplementation::sendRangeSui(PlayerCreature* playerCreature) {

	String surveying = "surveying";

	int surveyMod = playerCreature->getSkillMod(surveying);

	ManagedReference<SuiListBox*> suiToolRangeBox = new SuiListBox(
			playerCreature, SuiWindowType::SURVEY_TOOL_RANGE, 0);

	suiToolRangeBox->setPromptTitle("@base_player:swg");
	suiToolRangeBox->setPromptText("@survey:select_range");

	if (surveyMod >= 0)
		suiToolRangeBox->addMenuItem("64m x 3pts", 0);

	if (surveyMod > 20)
		suiToolRangeBox->addMenuItem("128m x 4pts", 1);

	if (surveyMod > 40)
		suiToolRangeBox->addMenuItem("192m x 4pts", 2);

	if (surveyMod > 60)
		suiToolRangeBox->addMenuItem("256m x 5pts", 3);

	if (surveyMod > 80)
		suiToolRangeBox->addMenuItem("320m x 5pts", 4);


	/// The options below are not true to pre-cu
	if (surveyMod > 105)
		suiToolRangeBox->addMenuItem("384m x 5pts", 5);

	if (surveyMod > 110)
		suiToolRangeBox->addMenuItem("448m x 5pts", 6);

	if (surveyMod > 115)
		suiToolRangeBox->addMenuItem("512m x 5pts", 7);

	if (surveyMod >= 125)
		suiToolRangeBox->addMenuItem("1024m x 1024m", 8);


	playerCreature->addSuiBox(suiToolRangeBox);
	playerCreature->sendMessage(suiToolRangeBox->generateMessage());
}

void SurveyToolImplementation::setRange(int r) {
	range = r;  /// Distance the tool checks during survey
	points = 3; /// Number of grid points in survey SUI 3x3 to 5x5

	if (range >= 128) {
		points = 4;
	}

	if (range >= 255) {
		points = 5;
	}
}

void SurveyToolImplementation::sendResourceListTo(PlayerCreature* playerCreature) {

	ManagedReference<ResourceManager* > resourceManager =
			playerCreature->getZoneServer()->getResourceManager();

	if(resourceManager == NULL) {
		info("ResourceManager is NULL in SurveyToolImplementation::sendResourceListTo");
		return;
	}

	resourceManager->sendResourceListForSurvey(playerCreature, type, surveyType);
}

void SurveyToolImplementation::sendSurveyTo(PlayerCreature* playerCreature, const String& resname) {

	ManagedReference<ResourceManager* > resourceManager =
			playerCreature->getZoneServer()->getResourceManager();

	if(resourceManager == NULL) {
		info("ResourceManager is NULL in SurveyToolImplementation::sendResourceListTo");
		return;
	}

	resourceManager->sendSurvey(playerCreature, resname);
}
