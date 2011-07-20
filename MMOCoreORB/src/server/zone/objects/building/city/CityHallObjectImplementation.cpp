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
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/chat/ChatManager.h"

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/tangible/terminal/city/CityTerminal.h"
#include "server/zone/objects/tangible/terminal/city/CityVoteTerminal.h"

void CityHallObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	BuildingObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

void CityHallObjectImplementation::spawnCityHallObjects() {
	ZoneServer* zoneServer = getZone()->getZoneServer();

	//TODO: Deprecate this as well.

	//if (cityRegion == NULL)
		//return;

	//cityRegion->insertToZone(getZone());
	//getZone()->getPlanetManager()->addRegion(cityRegion);
}

void CityHallObjectImplementation::despawnCityHallObjects() {
	if (getZone() == NULL)
		return;

	if (cityRegion != NULL) {
		//cityRegion->removeFromZone();

		//getZone()->getPlanetManager()->dropRegion(cityRegion);
	}
}

bool CityHallObjectImplementation::checkRequisitesForPlacement(CreatureObject* player) {
	Zone* zone = player->getZone();

	if (zone == NULL)
		return false;

	PlayerObject* ghost = player->getPlayerObject();

	ManagedReference<BuildingObject*> declaredResidence = ghost->getDeclaredResidence();

	if (declaredResidence != NULL && declaredResidence->isCityHallBuilding()) {
		player->sendSystemMessage("@city/city:already_mayor"); //You are already the mayor of a city. You may not be the mayor of another city.
		return false;
	}

	ManagedReference<CityManager*> cityManager = zone->getCityManager();

	if (cityManager->checkCitiesCappedAtRank(CityManager::NEWCITY)) {
		player->sendSystemMessage("@player_structure:max_cities"); //This planet has already reached its max allowed number of player cities.
		return false;
	}

	//We want to find the nearest City, rather than city hall, since NPC cities
	ManagedReference<SceneObject*> obj = zone->getNearestPlanetaryObject(player, "city");

	if (obj == NULL || !obj->isRegion())
		return true;

	Region* city = (Region*) obj.get();

	if (city->isInRange(player, 1000.f + MAX(1000.f, city->getRadius()))) {
		StringIdChatParameter stringID("@player_structure:city_too_close"); //You cannot place here. It is too close to %TO.
		stringID.setTO(city->getObjectName()->getDisplayedName());
		player->sendSystemMessage(stringID);

		return false;
	}

	return true;
}

void CityHallObjectImplementation::sendCityNamePromptTo(CreatureObject* player, bool newCity) {
	int windowType = SuiWindowType::CITY_CREATE;

	if (!newCity)
		windowType = SuiWindowType::CITY_SET_NAME;

	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, windowType, 0x00);

	if (newCity) {
		inputBox->setPromptTitle("@city/city:city_name_t");
		inputBox->setPromptText("@city/city:city_name_d");
	} else {
		inputBox->setPromptTitle("@city/city:city_name_new_t");
		inputBox->setPromptText("@city/city:city_name_new_d");
	}

	inputBox->setUsingObject(_this);

	player->getPlayerObject()->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());
}

int CityHallObjectImplementation::notifyStructurePlaced(CreatureObject* creature) {
	//cityName = creature->getFirstName();

	//sendCityNamePromptTo(player, true);

	return 0;
}

void CityHallObjectImplementation::sendStatusTo(CreatureObject* player) {
	ManagedReference<SceneObject*> mayorObject = server->getZoneServer()->getObject(mayorObjectID);

	if (mayorObject == NULL || !mayorObject->isPlayerCreature())
		return;

	CreatureObject* mayor = (CreatureObject*) mayorObject.get();

	String mayorName = mayor->getObjectName()->getDisplayedName();

	StringBuffer location;
	location << getPositionX() << ", " << getPositionY();

	ManagedReference<SuiListBox*> listBox = new SuiListBox(player, 0x00);
	listBox->setPromptTitle("@city/city:city_info_t"); //City Status Report
	listBox->setPromptText("@city/city:city_info_d"); //A report of the current city status follows.

	//Lists basic information about the city.
	listBox->addMenuItem("@city/city:name_prompt " + cityName);
	listBox->addMenuItem("@city/city:mayor_prompt " + mayorName);
	listBox->addMenuItem("@city/city:location_prompt " + location.toString() + " @city/city:radius_prompt " + String::valueOf(cityRegion->getRadius()));
	listBox->addMenuItem("@city/city:citizen_prompt " + String::valueOf(declaredCitizens.size()) + " @city/city:structures_prompt " + String::valueOf(cityStructures.size()));
	listBox->addMenuItem("@city/city:specialization_prompt "); //TODO: Specialization
	listBox->addMenuItem("@city/city:income_tax_prompt " + String::valueOf(incomeTax) + " @city/city:promperty_tax_prompt " + String::valueOf(propertyTax) + " @city/city:sales_tax_prompt " + String::valueOf(salesTax));

	/**
	if (cityRegion->getShuttle() == NULL)
		listBox->addMenuItem("@city/city:travel_cost_prompt_none");
	else
		listBox->addMenuItem("@city/city:travel_cost_prompt "); //TODO: Shuttle costs
	**/

	player->sendMessage(listBox->generateMessage());
}

void CityHallObjectImplementation::sendCitizenshipReportTo(CreatureObject* player) {
	ManagedReference<SuiListBox*> listBox = new SuiListBox(player, 0x00);
	listBox->setPromptTitle("@city/city:citizen_list_t"); //City Citizenship Report
	listBox->setPromptText("@city/city:citizen_list_d"); //The following is a list of the currently declared citizens (residents) of this city.  All citizens are eligible to vote.

	for (int i = 0; i < declaredCitizens.size(); ++i) {
		uint64 playerID = declaredCitizens.get(i);
		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(playerID);

		if (obj == NULL || !obj->isPlayerCreature())
			continue;

		String displayedName = obj->getObjectName()->getDisplayedName();

		if (isMilitiaMember(playerID))
			displayedName += " @city/city:militia_suffix"; //(Militia)

		listBox->addMenuItem(displayedName);
	}

	player->sendMessage(listBox->generateMessage());
}

void CityHallObjectImplementation::sendStructureReportTo(CreatureObject* player) {
}

void CityHallObjectImplementation::sendCityAdvancementTo(CreatureObject* player) {
	if (getZone() == NULL)
		return;

	ManagedReference<StructureManager*> structureManager = getZone()->getStructureManager();

	if (structureManager == NULL)
		return;

	String timeLeft = structureManager->getTimeString(-1 * nextCityUpdate.miliDifference() / 1000);

	StringIdChatParameter params;
	params.setStringId("@city/city:city_update_eta"); //Next City Update: %TO
	params.setTO(timeLeft);
	player->sendSystemMessage(params);

	//I think this is a city rank info status, rather than the generic status.
	sendStatusTo(player);
}

void CityHallObjectImplementation::sendTreasuryReportTo(CreatureObject* player) {
}

void CityHallObjectImplementation::sendChangeCityNameTo(CreatureObject* player) {
	//player->sendSystemMessage("@city/city:name_changed"); //The city name has been successfully changed.
}

void CityHallObjectImplementation::sendManageMilitiaTo(CreatureObject* player) {
	if (!isMayor(player->getObjectID())) {
		//Only the mayor can manage the militia.
		return;
	}

	if (!player->hasSkillBox("social_politician_martial_01")) {
		player->sendSystemMessage("@city/city:cant_militia"); //You lack the skill to manage the city militia.
		return;
	}

	ManagedReference<SuiListBox*> listBox = new SuiListBox(player, SuiWindowType::CITY_MILITIA, SuiListBox::HANDLETHREEBUTTON);
	listBox->setPromptTitle("@city/city:militia_t"); //Manage Militia
	listBox->setPromptText("@city/city:militia_d"); //Below is a list of current city militia members.  These citizens have the ability to ban visitors from accessing city services as well as the ability to attack visitors for the purposes of law enforcement.  To add a new citizen to the militia select "Add Militia Member" and hit OK.  To remove someone from the militia, select their name and hit OK.
	listBox->setOtherButton(true, "@city/city:militia_new_t"); //Add Militia Member
	listBox->setCancelButton(true, "@cancel");
	listBox->setUsingObject(_this);

	for (int i = 0; i < militiaMembers.size(); ++i) {
		uint64 playerid = militiaMembers.get(i);
		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(playerid);

		if (obj == NULL || !obj->isPlayerCreature())
			return;

		CreatureObject* player = (CreatureObject*) obj.get();

		listBox->addMenuItem(player->getObjectName()->getDisplayedName(), playerid);
	}

	player->getPlayerObject()->addSuiBox(listBox);
	player->sendMessage(listBox->generateMessage());
}

void CityHallObjectImplementation::sendAddMilitiaMemberTo(CreatureObject* player) {
	if (!isMayor(player->getObjectID())) {
		//Only the mayor can manage the militia.
		return;
	}

	if (!player->hasSkillBox("social_politician_martial_01")) {
		player->sendSystemMessage("@city/city:cant_militia"); //You lack the skill to manage the city militia.
		return;
	}

	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::CITY_ADD_MILITIA);
	inputBox->setPromptTitle("@city/city:militia_new_t"); //Add Militia Member
	inputBox->setPromptText("@city/city:militia_new_d"); //Enter the name of the person you wish to add to the militia (the name must be entered exactly as it appears in game).  In order to join the city militia, the player must be a citizen of this city and must be standing near the city management terminal.
	inputBox->setUsingObject(_this);
	inputBox->setCancelButton(true, "@cancel");

	player->getPlayerObject()->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());
}

void CityHallObjectImplementation::sendAdjustTaxesTo(CreatureObject* player) {
}

void CityHallObjectImplementation::sendTreasuryDepositTo(CreatureObject* player) {
}

void CityHallObjectImplementation::sendTreasuryWithdrawalTo(CreatureObject* player) {
}

void CityHallObjectImplementation::sendCitySpecializationSelectionTo(CreatureObject* player) {
	if (cityRank < CityManager::TOWNSHIP) {
		player->sendSystemMessage("@city/city:no_rank_spec"); //Your city must be at least rank 3 before you can set a specialization.
		return;
	}

	/*
	ManagedReference<SuiListBox*> listBox = new SuiListBox(player, SuiWindowType::CITY_SPECIALIZATIONSELECT);
	listBox->setPromptTitle("@city/city:city_spec_t"); //City Specialization
	listBox->setPromptText("@city/city:city_spec_d"); //At rank 3, a city can select an area of specialization (spec).  A spec grants a certain set of bonuses that apply within the city borders in exchange for increased weekly maintenance.  New spec types are earned through the Politician profession.  The city's spec can only be set once per week, although it can be disabled at any time.  Select a spec from the list below to learn more about it.  When a spec is selected, the weekly city hall maintenance fee will increase by the indicated amount.

	listBox->addMenuItem();

	player->addSuiBox(listBox);
	player->sendMessage(listBox->generateMessage());
	*/

}

void CityHallObjectImplementation::sendMaintenanceReportTo(CreatureObject* player) {

}

void CityHallObjectImplementation::sendEnableZoningTo(CreatureObject* player) {
	if (player->getObjectID() != mayorObjectID) {
		player->sendSystemMessage("@city/city:zoning_skill"); //You must be a Politician to enable city zoning.
		return;
	}

	if (!zoningEnabled) {
		ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, SuiWindowType::CITY_ENABLE_ZONING);
		suiBox->setPromptTitle("@city/city:zoning_t"); //Zoning
		suiBox->setPromptText("@city/city:zoning_d"); //If you enable zoning laws in your city, other players will not be able to build structures in your city without permission.  You and your militia can grant permission with the /grantZoningRights command.  This command gives the target the right to build structures in your city for 24 hours.
		suiBox->setUsingObject(_this);
		suiBox->setCancelButton(true, "@cancel");

		player->getPlayerObject()->addSuiBox(suiBox);
		player->sendMessage(suiBox->generateMessage());
	} else {
		toggleZoningEnabled(player);
	}
}

void CityHallObjectImplementation::toggleCityRegistration(CreatureObject* player) {
	if (!player->hasSkillBox("social_politician_fiscal_01")) {
		player->sendSystemMessage("@city/city:cant_register"); //You lack the ability to register your city!
		return;
	}

	if (cityRank < CityManager::TOWNSHIP) {
		player->sendSystemMessage("@city/city:cant_register_rank"); //Your city must be rank 3 (Township) to be registered on the planetary map.
		return;
	}

	//Register/Unregister the city (and all civic structures) from the map.
	updateToDatabaseWithoutChildren();
}

bool CityHallObjectImplementation::hasZoningRights(uint64 playerID) {
	if (playerID == mayorObjectID)
		return true;

	if (isMilitiaMember(playerID))
		return true;

	uint32 expires = playerZoningRights.get(playerID);

	Time currentTime;

	if (currentTime.getTime() < expires)
		return true;

	removeZoningRights(playerID);
	return false;
}

void CityHallObjectImplementation::addZoningRights(uint64 playerID, uint32 seconds) {
	Time currentTime;
	currentTime.addMiliTime(seconds * 1000);

	playerZoningRights.put(playerID, currentTime.getTime());
}


void CityHallObjectImplementation::rescheduleCityUpdate(uint32 minutes) {
	nextCityUpdate.updateToCurrentTime();
	nextCityUpdate.addMiliTime(minutes * 60000);
}
