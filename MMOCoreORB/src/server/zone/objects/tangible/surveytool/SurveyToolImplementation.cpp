/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
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

#include "../../../packets.h"

#include "../../../objects.h"

#include "SurveyTool.h"
#include "SurveyToolImplementation.h"

#include "../../../managers/resource/ResourceManager.h"
#include "../../../managers/resource/ResourceHarvestType.h"

SurveyToolImplementation::SurveyToolImplementation(uint64 object_id, uint32 tempCRC, const UnicodeString& n, const String& tempn)
		: SurveyToolServant(object_id, tempCRC, n, tempn, SURVEYTOOL) {
	objectCRC = tempCRC;
	templateTypeName = "obj_n";

	templateName = tempn;

	name = n;

	init();
}

SurveyToolImplementation::SurveyToolImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempn)
		: SurveyToolServant(creature, tempCRC, n, tempn, SURVEYTOOL) {
	objectCRC = tempCRC;

	templateTypeName = "obj_n";
	templateName = tempn;

	name = n;

	init();
}

SurveyToolImplementation::~SurveyToolImplementation() {

}

void SurveyToolImplementation::init() {
	if (templateName == "survey_tool_mineral") {
		surveyToolType = ResourceHarvestType::MINERAL;
	} else if (templateName == "survey_tool_solar") {
		surveyToolType = ResourceHarvestType::SOLAR;
	} else if (templateName == "survey_tool_chemical") {
		surveyToolType = ResourceHarvestType::CHEMICAL;
	} else if (templateName == "survey_tool_flora") {
		surveyToolType = ResourceHarvestType::FLORA;
	} else if (templateName == "survey_tool_gas") {
		surveyToolType = ResourceHarvestType::GAS;
	} else if (templateName == "survey_tool_geothermal") {
		surveyToolType = ResourceHarvestType::GEOTHERMAL;
	} else if (templateName == "survey_tool_water") {
		surveyToolType = ResourceHarvestType::WATER;
	} else if (templateName == "survey_tool_wind") {
		surveyToolType = ResourceHarvestType::WIND;
	}

	setSurveyToolRange(0);
}

int SurveyToolImplementation::useObject(Player* player) {
	ResourceManager* resourceManager = player->getZone()->getZoneServer()->getResourceManager();

	String skillBox = "crafting_artisan_novice";
	if (player->getParent() != NULL && player->getParent()->isCell()) {
		player->sendSystemMessage("You cannot perform survey-related actions inside a structure.");
		return 0;
	}

	if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
		// Added to set a default range.  Remove this to disable feature.
		if (getSurveyToolRange() == 0)
			setSurveyToolRange(64);

		if (getSurveyToolRange() > 0) {
			if (resourceManager->sendSurveyResources(player, getSurveyToolType())) {
				player->setSurveyTool(_this);
			}
		} else {
			ChatSystemMessage* sysMessage = new ChatSystemMessage("survey","select_range");
			player->sendMessage(sysMessage);
		}
	} else {
		player->sendSystemMessage("You do not have sufficient abilities to open "
					+ getName().toString() + ".");
	}

	return 0;
}

void SurveyToolImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	try {
		SceneObject* parent = getParent();

		if (parent != NULL) {

			if (parent->isCell()) {
				omr->addRadialItem(0, 10, 3, "Pickup");

			} else if (parent == player->getInventory() && player->getParent() == NULL) {
				omr->addRadialItem(0, 136, 3, "@sui:tool_options");
				omr->addRadialItem(4, 137, 3, "@sui:survey_range");
			}

		}

	} catch (...) {
		System::out << "Unreported exception in SurveyToolImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr\n";
	}

	omr->finish();

	player->sendMessage(omr);

	//TODO: Delta for updating the tool's range
}

void SurveyToolImplementation::generateAttributes(SceneObject* obj) {

	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);

}

void SurveyToolImplementation::addAttributes(AttributeListMessage* alm) {

	alm->insertAttribute("volume", "1");

	if (craftersName != ""){

		alm->insertAttribute("crafter", craftersName);
	}
	if (craftedSerial != ""){

		alm->insertAttribute("serial_number", craftedSerial);
	}

	alm->insertAttribute("range", surveyToolRange);

}

void SurveyToolImplementation::parseItemAttributes() {

	String temp = "craftersname";
	craftersName = itemAttributes->getStringAttribute(temp);

	temp = "craftedserial";
	craftedSerial = itemAttributes->getStringAttribute(temp);

	temp = "range";
	surveyToolRange = itemAttributes->getIntAttribute(temp);

}

void SurveyToolImplementation::sendSurveyEffect(Player* player) {
	PlayClientEffectLoc* effect;

	StringBuffer file;

	switch (getSurveyToolType()) {
	case ResourceHarvestType::SOLAR: // Solar
		file << "clienteffect/survey_tool_moisture.cef";
		break;
	case ResourceHarvestType::CHEMICAL: // Chemical
		file << "clienteffect/survey_tool_moisture.cef";
		break;
	case ResourceHarvestType::FLORA: // Flora
		file << "clienteffect/survey_tool_lumber.cef";
		break;
	case ResourceHarvestType::GAS: // Gas
		file << "clienteffect/survey_tool_gas.cef";
		break;
	case ResourceHarvestType::GEOTHERMAL: // Geothermal
		file << "clienteffect/survey_tool_liquid.cef";
		break;
	case ResourceHarvestType::MINERAL: // Mineral
		file << "clienteffect/survey_tool_mineral.cef";
		break;
	case ResourceHarvestType::WATER: // Water
		file << "clienteffect/survey_tool_liquid.cef";
		break;
	case ResourceHarvestType::WIND: // Wind
		file << "clienteffect/survey_tool_gas.cef";
		break;
	}

	effect = new PlayClientEffectLoc(file.toString(), player->getZoneIndex(), player->getPositionX(), player->getPositionZ(), player->getPositionY());

	player->broadcastMessage(effect);
}

void SurveyToolImplementation::sendSampleEffect(Player* player) {
	PlayClientEffectLoc* effect;

	StringBuffer file;

	switch (getSurveyToolType()) {
	case 1: // Solar
		file << "clienteffect/survey_sample_moisture.cef";
		break;
	case 2: // Chemical
		file << "clienteffect/survey_sample_moisture.cef";
		break;
	case 3: // Flora
		file << "clienteffect/survey_sample_lumber.cef";
		break;
	case 4: // Gas
		file << "clienteffect/survey_sample_gas.cef";
		break;
	case 5: // Geothermal
		file << "clienteffect/survey_sample_liquid.cef";
		break;
	case 6: // Mineral
		file << "clienteffect/survey_sample_mineral.cef";
		break;
	case 7: // Water
		file << "clienteffect/survey_sample_liquid.cef";
		break;
	case 8: // Wind
		file << "clienteffect/survey_sample_gas.cef";
		break;
	}

	effect = new PlayClientEffectLoc(file.toString(), player->getZoneIndex(), player->getPositionX(), player->getPositionZ(), player->getPositionY());

	player->broadcastMessage(effect);
}

void SurveyToolImplementation::surveyRequest(Player* player, String resourceName) {
	if (player->getParent() != NULL && player->getParent()->isCell()) {
		player->sendSystemMessage("You cannot perform survey-related actions inside a structure.");
		return;
	}

	if (player->getZone()->getZoneServer()->getResourceManager()->checkResource(player, resourceName, getSurveyToolType())) {
		if (!player->getCanSample() && !player->getCancelSample()) {
			ChatSystemMessage* sysMessage = new ChatSystemMessage("survey","survey_sample");
			player->sendMessage(sysMessage);
		} else if (player->getCanSurvey()) {
			// Send's System Message
			ChatSystemMessage* sysMessage = new ChatSystemMessage("survey","start_survey",resourceName,0,false);
			player->sendMessage(sysMessage);
			// Begin Surveying
			sendSurveyEffect(player);
			player->setSurveyEvent(resourceName);
		}
	}
}

void SurveyToolImplementation::sampleRequest(Player* player, String resourceName) {
	if (player->getParent() != NULL && player->getParent()->isCell()) {
		player->sendSystemMessage("You cannot perform survey-related actions inside a structure.");
		return;
	}

	if (player->getZone()->getZoneServer()->getResourceManager()->checkResource(player, resourceName, getSurveyToolType())) {
		if (!player->getCanSurvey()) {
			ChatSystemMessage* sysMessage = new ChatSystemMessage("survey","sample_survey");
			player->sendMessage(sysMessage);
		} else if (getSurveyToolType() == ResourceHarvestType::SOLAR || getSurveyToolType() == ResourceHarvestType::WIND) {
			player->sendSystemMessage("Unable to sample this resource type.");
		} else if (player->getCanSample()) {
			if (!player->isKneeling()) {
				player->changePosture(CreaturePosture::CROUCHED);
			}
			ChatSystemMessage* sysMessage = new ChatSystemMessage("survey","start_sampling",resourceName,0,false);
			player->sendMessage(sysMessage);
			// Begin Sampling
			player->setSampleEvent(resourceName, true);
		} else {
			player->sendSampleTimeRemaining();
		}
	}
}
