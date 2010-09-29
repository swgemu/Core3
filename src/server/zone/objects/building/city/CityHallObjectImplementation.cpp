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
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/managers/name/NameManager.h"

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/tangible/terminal/city/CityTerminal.h"
#include "server/zone/objects/tangible/terminal/city/CityVoteTerminal.h"

void CityHallObjectImplementation::spawnCityHallObjects() {
	ZoneServer* zoneServer = zone->getZoneServer();

	//Place a CityTerminal in cellid 4
	ManagedReference<CellObject*> cell = getCell(4);

	//{templateFile = "object/tangible/terminal/terminal_city_vote.iff", x = 0.25, z = 2.0, y = -9.65, ow = 1, ox = 0, oy = 0, oz = 0, cellid = 2, containmentType = -1},
	//{templateFile = "object/tangible/terminal/terminal_city.iff", x = 17.07, z = 2.0, y = -8.7, ow = 1, ox = 0, oy = 0, oz = 0, cellid = 4, containmentType = -1}

	if (cell != NULL) {
		String cityTerminalTemplateString = "object/tangible/terminal/terminal_city.iff";

		cityTerminal = (CityTerminal*) zoneServer->createObject(cityTerminalTemplateString.hashCode(), 1);

		Locker _locker(cityTerminal);

		cityTerminal->initializePosition(17.07, 2.0, -8.7);
		cityTerminal->setDirection(1, 0, 0, 0);
		cityTerminal->setCityHallObject(_this);
		cell->addObject(cityTerminal, -1, true);
		cell->broadcastObject(cityTerminal, false);
		cityTerminal->insertToZone(zone);
		cityTerminal->updateToDatabase();

		_locker.release();
	}

	cell = getCell(2);

	//Place a CityVoteTerminal in cellid 2
	if (cell != NULL) {
		String cityVoteTerminalTemplateString = "object/tangible/terminal/terminal_city_vote.iff";

		cityVoteTerminal = (CityVoteTerminal*) zoneServer->createObject(cityVoteTerminalTemplateString.hashCode(), 1);

		Locker _locker(cityVoteTerminal);

		cityVoteTerminal->initializePosition(0.25, 2.0, -9.65);
		cityVoteTerminal->setDirection(1, 0, 0, 0);
		cityVoteTerminal->setCityHallObject(_this);
		cell->addObject(cityVoteTerminal, -1, true);
		cell->broadcastObject(cityVoteTerminal, false);
		cityVoteTerminal->insertToZone(zone);
		cityVoteTerminal->updateToDatabase();

		_locker.release();
	}

	if (cityRegion == NULL)
		return;

	cityRegion->insertToZone(zone);
	zone->getPlanetManager()->addRegion(cityRegion);
}

void CityHallObjectImplementation::despawnCityHallObjects() {
	if (zone == NULL)
		return;

	if (cityTerminal != NULL) {
		cityTerminal->removeFromZone();
	}

	if (cityVoteTerminal != NULL)
		cityVoteTerminal->removeFromZone();

	if (cityRegion != NULL) {
		cityRegion->removeFromZone();

		zone->getPlanetManager()->dropRegion(cityRegion);
	}
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

	mayorObjectID = player->getObjectID();

	cityName = name;

	uint32 crc = String("object/region_area.iff").hashCode();

	cityRegion = (Region*) ObjectManager::instance()->createObject(crc, 2, "cityregions");
	cityRegion->initializePosition(positionX, 0, positionY);
	cityRegion->setRadius(150);
	cityRegion->setCityHall(_this);
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

		if (cityName.length() > 0) {
			stringID.setTO(cityName);
		} else {
			stringID.setTO(name->getFile(), name->getStringID());
		}

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

void CityHallObjectImplementation::sendStatusTo(PlayerCreature* player) {
//	ManagedReference<SuiListBox*> listBox = new SuiListBox();
}

void CityHallObjectImplementation::sendCitizenshipReportTo(PlayerCreature* player) {
	player->sendSystemMessage(String::valueOf(declaredCitizens.size()));
}

void CityHallObjectImplementation::sendStructureReportTo(PlayerCreature* player) {
}

void CityHallObjectImplementation::sendTreasuryReportTo(PlayerCreature* player) {
}

void CityHallObjectImplementation::sendChangeCityNameTo(PlayerCreature* player) {
}

void CityHallObjectImplementation::sendManageMilitiaTo(PlayerCreature* player) {
}

void CityHallObjectImplementation::sendAdjustTaxesTo(PlayerCreature* player) {
}

void CityHallObjectImplementation::sendTreasuryDepositTo(PlayerCreature* player) {
}

void CityHallObjectImplementation::sendTreasuryWithdrawalTo(PlayerCreature* player) {
}

void CityHallObjectImplementation::sendCitySpecializationSelectionTo(PlayerCreature* player) {
}

void CityHallObjectImplementation::toggleCityRegistration() {
}
