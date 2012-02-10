/*
 * PlaceCityHallComponent.cpp
 *
 *  Created on: Feb 5, 2012
 *      Author: xyborn
 */

#include "PlaceCityHallComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/deed/Deed.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/callbacks/PlaceCityHallSuiCallback.h"
#include "server/zone/objects/area/ActiveArea.h"

int PlaceCityHallComponent::placeStructure(CreatureObject* creature, Deed* deed, float x, float y, int angle) {
	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return 0;

	SuiInputBox* inputBox = new SuiInputBox(creature, 0, 0);
	inputBox->setPromptTitle("@city/city:city_name_t"); //Enter City Name
	inputBox->setPromptText("@city/city:city_name_d"); //Enter the desired name for your new city. Note that you must have at least 10 citizens join your city within 24 hours of placement in order for your city to be approved.
	inputBox->setForceCloseDisabled();
	inputBox->setCallback(new PlaceCityHallSuiCallback(creature->getZone(), deed, x, y, angle));

	ghost->addSuiBox(inputBox);
	creature->sendMessage(inputBox->generateMessage());

	return 0;
}
