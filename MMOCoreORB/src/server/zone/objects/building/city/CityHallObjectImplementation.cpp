/*
 * CityHallObjectImplementation.cpp
 *
 *  Created on: 31/07/2010
 *      Author: victor
 */

#include "CityHallObject.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/managers/name/NameManager.h"

void CityHallObjectImplementation::spawnCityHallObjects() {
	if (cityRegion == NULL)
		return;

	cityRegion->insertToZone(zone);
	zone->getPlanetManager()->addRegion(cityRegion);
}

void CityHallObjectImplementation::trySetCityName(PlayerCreature* player, const String& name) {
	PlanetManager* planetManager = zone->getPlanetManager();

	NameManager* nameManager = server->getNameManager();

	if (nameManager->validateName(name, 0) != NameManagerResult::ACCEPTED
			|| name.length() < 3 || planetManager->hasRegion(name)) {

		player->sendSystemMessage("Invalid region name");

		notifyStructurePlaced(player);

		return;
	}

	cityName = name;

	uint32 crc = String("object/region_area.iff").hashCode();

	cityRegion = (Region*) ObjectManager::instance()->createObject(crc, 2, "cityregions");
	cityRegion->initializePosition(positionX, 0, positionY);
	cityRegion->setRadius(150);
	StringId* objectName = cityRegion->getObjectName();
	objectName->setCustomString(cityName);

	cityRegion->insertToZone(zone);

	cityRegion->updateToDatabase();
	updateToDatabase();

	zone->getPlanetManager()->addRegion(cityRegion);
}

bool CityHallObjectImplementation::checkRequisitesForPlacement(PlayerCreature* player) {
	Zone* zone = player->getZone();

	ManagedReference<SceneObject*> object = zone->getNearestPlanetaryObject(player, 50);

	if (object == NULL)
		return true;

	if (object->isInRange(player, 1000.f)) {
		ParameterizedStringId stringID("player_structure", "city_too_close");
		StringId* name = object->getObjectName();
		UnicodeString cityName = name->getCustomString();

		stringID.setTO(cityName);

		player->sendSystemMessage(stringID);

		return false;
	}

	return true;
}

int CityHallObjectImplementation::notifyStructurePlaced(PlayerCreature* player) {
	cityName = player->getFirstName();

	ManagedReference<SuiInputBox*> setTheName = new SuiInputBox(player, SuiWindowType::CREATE_CITY_HALL_NAME, 0x00);

	setTheName->setPromptTitle("@city/city:city_name_t");
	setTheName->setPromptText("@city/city:city_name_t");
	setTheName->setUsingObject(_this);

	player->addSuiBox(setTheName);
	player->sendMessage(setTheName->generateMessage());

	return 0;
}
