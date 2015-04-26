/*
 * PlaceCityHallComponent.cpp
 *
 *  Created on: Feb 5, 2012
 *      Author: xyborn
 */

#include "PlaceCityHallComponent.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/deed/Deed.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/sui/callbacks/PlaceCityHallSuiCallback.h"
#include "server/zone/objects/area/ActiveArea.h"

int PlaceCityHallComponent::placeStructure(StructureDeed* deed, CreatureObject* creature, float x, float y, int angle) {
	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return 1;

	Zone* zone = creature->getZone();

	if (zone == NULL)
		return 1;

	//Check the capped cities on this planet.
	CityManager* cityManager = zone->getZoneServer()->getCityManager();

	if (cityManager->isCityRankCapped(zone->getZoneName(), CityManager::OUTPOST)) {
		creature->sendSystemMessage("@player_structure:max_cities"); // This planet has already reached its max allowed number of player cities.
		return 1;
	}

	uint64 declaredOidResidence = ghost->getDeclaredResidence();

	ManagedReference<BuildingObject*> declaredResidence = zone->getZoneServer()->getObject(declaredOidResidence).castTo<BuildingObject*>();

	if (declaredResidence != NULL) {
		ManagedReference<CityRegion*> city = declaredResidence->getCityRegion();

		if (city != NULL && city->isMayor(creature->getObjectID())) {
			creature->sendSystemMessage("@city/city:already_mayor"); //You are already the mayor of a city.  You may not be mayor of another city.
			return 1;
		}
	}

	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(creature, SuiWindowType::CITY_CREATE, 0);
	inputBox->setPromptTitle("@city/city:city_name_t"); //Enter City Name
	inputBox->setPromptText("@city/city:city_name_d"); //Enter the desired name for your new city. Note that you must have at least 10 citizens join your city within 24 hours of placement in order for your city to be approved.
	inputBox->setForceCloseDisabled();
	inputBox->setMaxInputSize(40);
	inputBox->setCallback(new PlaceCityHallSuiCallback(creature->getZone(), deed, x, y, angle));

	ghost->addSuiBox(inputBox);
	creature->sendMessage(inputBox->generateMessage());

	return 0;
}

int PlaceCityHallComponent::notifyStructurePlaced(StructureDeed* deed, CreatureObject* creature, StructureObject* structure) {
	PlaceStructureComponent::notifyStructurePlaced(deed, creature, structure);

	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost != NULL && structure->isBuildingObject()) {
		ManagedReference<CityRegion*> city = structure->getCityRegion();

		if (city != NULL && city->isMayor(creature->getObjectID())) {
			Locker locker(city);

			city->setCityHall(structure);
			city->setLoaded();

			locker.release();

			StructureManager::instance()->declareResidence(creature, structure);
		}
	}

	return 0;
}
