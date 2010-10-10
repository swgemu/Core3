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
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/chat/ChatManager.h"

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

		if (cityTerminal == NULL) {
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
	}

	cell = getCell(2);

	//Place a CityVoteTerminal in cellid 2
	if (cell != NULL) {
		String cityVoteTerminalTemplateString = "object/tangible/terminal/terminal_city_vote.iff";

		if (cityVoteTerminal == NULL) {
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
	}

	if (cityRegion == NULL)
		return;

	cityRegion->insertToZone(zone);
	zone->getPlanetManager()->addRegion(cityRegion);
	//cityRegion->updateToDabatase();
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

		player->sendSystemMessage("Sorry, but a city with that name already exists or the name was rejected as inappropriate.");

		notifyStructurePlaced(player);

		return;
	}

	//TODO: All this should be moved to another function as it has nothing to do with "trySetCityName"

	mayorObjectID = player->getObjectID();

	player->setDeclaredResidence(_this);
	declareCitizenship(player, false);

	cityName = name;

	//New city established email.
	ManagedReference<ChatManager*> chatManager = server->getChatManager();

	if (chatManager != NULL) {
		ParameterizedStringId emailBody;
		emailBody.setStringId("@city/city:new_city_body"); //Congratulations, you have successfully established a new outpost on the frontier!...
		emailBody.setTO(player->getObjectName());
		UnicodeString subject = "@city/city:new_city_subject"; //New City Established!
		chatManager->sendMail("@city/city:new_city_from", subject, emailBody, player->getFirstName());
	}

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
	setTheName->setPromptText("@city/city:city_name_d");
	setTheName->setUsingObject(_this);

	player->addSuiBox(setTheName);
	player->sendMessage(setTheName->generateMessage());

	return 0;
}

void CityHallObjectImplementation::sendStatusTo(PlayerCreature* player) {
	ManagedReference<SceneObject*> mayorObject = server->getZoneServer()->getObject(mayorObjectID);

	if (mayorObject == NULL || !mayorObject->isPlayerCreature())
		return;

	PlayerCreature* mayor = (PlayerCreature*) mayorObject.get();

	String mayorName = mayor->getObjectName()->getDisplayedName();

	StringBuffer location;
	location << getPositionX() << ", " << getPositionZ() << ", " << getPositionY() << " @planet_n:" << Planet::getPlanetName(getZone()->getZoneID());

	ManagedReference<SuiListBox*> listBox = new SuiListBox(player, 0x00);
	listBox->setPromptTitle("@city/city:city_info_t"); //City Status Report
	listBox->setPromptText("@city/city:city_info_d"); //A report of the current city status follows.

	//Lists basic information about the city.
	listBox->addMenuItem("@city/city:name_prompt " + cityName);
	listBox->addMenuItem("@city/city:mayor_prompt " + mayorName);
	listBox->addMenuItem("@city/city:location_prompt " + location.toString());
	listBox->addMenuItem("@city/city:radius_prompt " + String::valueOf(cityRegion->getRadius()));
	listBox->addMenuItem("@city/city:citizen_prompt " + String::valueOf(declaredCitizens.size()));
	listBox->addMenuItem("@city/city:structures_prompt " + String::valueOf(cityStructures.size()));
	listBox->addMenuItem("@city/city:specialization_prompt "); //TODO: Specialization
	listBox->addMenuItem("@city/city:income_tax_prompt " + String::valueOf(incomeTax));
	listBox->addMenuItem("@city/city:promperty_tax_prompt " + String::valueOf(propertyTax)); //LOL at the spelling error
	listBox->addMenuItem("@city/city:sales_tax_prompt " + String::valueOf(salesTax));

	if (cityRegion->getShuttle() == NULL)
		listBox->addMenuItem("@city/city:travel_cost_prompt_none");
	else
		listBox->addMenuItem("@city/city:travel_cost_prompt "); //TODO: Shuttle costs

	player->sendMessage(listBox->generateMessage());
}

void CityHallObjectImplementation::sendCitizenshipReportTo(PlayerCreature* player) {
	ManagedReference<SuiListBox*> listBox = new SuiListBox(player, 0x00);
	listBox->setPromptTitle("@city/city:citizen_list_t"); //City Citizenship Report
	listBox->setPromptText("@city/city:citizen_list_d"); //The following is a list of the currently declared citizens (residents) of this city.  All citizens are elligible to vote.

	//TODO: This is a good instance of a player where a playerObjectID->playerName lookup would be good.
	for (int i = 0; i < declaredCitizens.size(); ++i) {
		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(declaredCitizens.get(i));

		if (obj == NULL || !obj->isPlayerCreature())
			continue;

		listBox->addMenuItem(obj->getObjectName()->getDisplayedName());
	}

	player->sendMessage(listBox->generateMessage());
}

void CityHallObjectImplementation::sendStructureReportTo(PlayerCreature* player) {
}

void CityHallObjectImplementation::sendCityAdvancementTo(PlayerCreature* player) {
	checkCityUpdate();

	if (zone == NULL)
		return;

	ManagedReference<StructureManager*> structureManager = zone->getPlanetManager()->getStructureManager();

	if (structureManager == NULL)
		return;

	String timeLeft = structureManager->getTimeString(-1 * nextCityUpdate.miliDifference() / 1000);

	ParameterizedStringId params;
	params.setStringId("@city/city:city_update_eta"); //Next City Update: %TO
	params.setTO(timeLeft);
	player->sendSystemMessage(params);

	//I think this is a city rank info status, rather than the generic status.
	sendStatusTo(player);
}

void CityHallObjectImplementation::sendTreasuryReportTo(PlayerCreature* player) {
}

void CityHallObjectImplementation::sendChangeCityNameTo(PlayerCreature* player) {
	//player->sendSystemMessage("@city/city:name_changed"); //The city name has been successfully changed.
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
	if (cityRank < TOWNSHIP) {
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

void CityHallObjectImplementation::sendMaintenanceReportTo(PlayerCreature* player) {

}

void CityHallObjectImplementation::sendEnableZoningTo(PlayerCreature* player) {
	if (player->getObjectID() != mayorObjectID) {
		player->sendSystemMessage("@city/city:zoning_skill"); //You must be a Politician to enable city zoning.
		return;
	}

	if (!zoningEnabled) {
		ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, SuiWindowType::CITY_ENABLEZONING);
		suiBox->setPromptTitle("@city/city:zoning_t"); //Zoning
		suiBox->setPromptText("@city/city:zoning_d"); //If you enable zoning laws in your city, other players will not be able to build structures in your city without permission.  You and your militia can grant permission with the /grantZoningRights command.  This command gives the target the right to build structures in your city for 24 hours.
		suiBox->setUsingObject(_this);
		suiBox->setCancelButton(true, "@cancel");

		player->addSuiBox(suiBox);
		player->sendMessage(suiBox->generateMessage());
	} else {
		toggleZoningEnabled(player);
	}
}

void CityHallObjectImplementation::toggleCityRegistration(PlayerCreature* player) {
	if (!player->hasSkillBox("social_politician_fiscal_01")) {
		player->sendSystemMessage("@city/city:cant_register"); //You lack the ability to register your city!
		return;
	}

	if (cityRank < TOWNSHIP) {
		player->sendSystemMessage("@city/city:cant_register_rank"); //Your city must be rank 3 (Township) to be registered on the planetary map.
		return;
	}

	//Register/Unregister the city (and all civic structures) from the map.
	updateToDatabaseWithoutChildren();
}

bool CityHallObjectImplementation::hasZoningRights(uint64 playerID) {
	if (playerID == mayorObjectID)
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

void CityHallObjectImplementation::checkCityUpdate() {
	if (!nextCityUpdate.isPast())
		return;

	nextCityUpdate.updateToCurrentTime();
	nextCityUpdate.addMiliTime(CITY_UPDATEINTERVAL * 3600000);

	if (cityRegion == NULL)
		return;

	int citizens = declaredCitizens.size();

	//If the city is a new city, then it has to first pass a "probation stage".
	if (cityRank == NEWCITY) {
		if (citizens >= 10) {
			handleNewCitySuccess();
		} else {
			handleNewCityFailure();
		}

		return;
	}

	uint8 oldRank = cityRank;


	//TODO: Make this step up rather than skip levels. For example, if you are a TOWNSHIP, and you get 85 citizens, you still have to go through a stage as a CITY before becoming a METROPOLIS.
	if (citizens >= 85) {
		cityRank = METROPOLIS;
		cityRegion->setRadius(450);
	} else if (citizens >= 55) {
		cityRank = CITY;
		cityRegion->setRadius(400);
	} else if (citizens >= 35) {
		cityRank = TOWNSHIP;
		cityRegion->setRadius(300);
	} else if (citizens >= 20) {
		cityRank = VILLAGE;
		cityRegion->setRadius(200);
	} else if (citizens >= 10) {
		cityRank = OUTPOST;
		cityRegion->setRadius(150);
	} else {
		cityRank = NEWCITY;
		cityRegion->setRadius(150);
	}

	//No update occurred.
	if (oldRank == cityRank)
		return;

	ManagedReference<ChatManager*> chatManager = server->getChatManager();
	ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

	if (chatManager == NULL || playerManager == NULL)
		return;

	ManagedReference<SceneObject*> mayorObject = server->getZoneServer()->getObject(mayorObjectID);

	if (mayorObject == NULL || !mayorObject->isPlayerCreature())
		return;

	PlayerCreature* mayor = (PlayerCreature*) mayorObject.get();

	//Send email to the mayor
	ParameterizedStringId email;
	UnicodeString subject;
	if (oldRank < cityRank) {
		subject = "@city/city:city_expand_subject"; //City Expansion!
		email.setStringId("@city/city:city_expand_body"); //Congratulations
	} else {
		subject = "@city/city:city_contract_subject"; //City Contraction!
		email.setStringId("@city/city:city_contract_body"); //Warning!
	}

	email.setTO(cityName);
	email.setDI(cityRank);

	chatManager->sendMail("@city/city:new_city_from", subject, email, mayor->getFirstName());

	updateToDatabaseWithoutChildren();
}

void CityHallObjectImplementation::declareCitizenship(PlayerCreature* player, bool sendMail) {
	if (player == NULL)
		return;

	uint64 playerID = player->getObjectID();

	if (declaredCitizens.contains(playerID))
		return;

	declaredCitizens.put(playerID);

	//Save the declared citizens vector.
	updateToDatabaseWithoutChildren();

	if (!sendMail)
		return;

	//Send out new citizen email
	ManagedReference<ChatManager*> chatManager = server->getChatManager();
	ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

	if (chatManager == NULL || playerManager == NULL)
		return;

	ManagedReference<SceneObject*> mayorObject = server->getZoneServer()->getObject(mayorObjectID);

	if (mayorObject == NULL || !mayorObject->isPlayerCreature())
		return;

	PlayerCreature* mayor = (PlayerCreature*) mayorObject.get();

	String mayorName = mayor->getObjectName()->getDisplayedName();

	//Send email to the citizen declaring citizenship
	ParameterizedStringId email;
	UnicodeString subject = "@city/city:new_city_citizen_other_subject"; //Welcome, Citizen!
	email.setStringId("@city/city:new_city_citizen_other_body"); //Welcome to %TU, citizen!
	email.setTU(cityName);
	email.setTT(mayorName);

	chatManager->sendMail(mayorName, subject, email, player->getFirstName());

	//Send email to the mayor
	subject = "@city/city:new_city_citizen_subject"; //City Growth: Added Citizen
	email.setStringId("@city/city:new_city_citizen_body"); //A new citizen has joined your city.
	email.setTU(NULL);
	email.setTT(NULL);
	email.setTO(player->getObjectName()->getDisplayedName());

	chatManager->sendMail("@city/city:new_city_from", subject, email, mayor->getFirstName());
}

void CityHallObjectImplementation::revokeCitizenship(PlayerCreature* player, bool sendMail) {
	if (player == NULL)
		return;

	uint64 playerID = player->getObjectID();

	if (!declaredCitizens.contains(playerID))
		return;

	declaredCitizens.drop(playerID);

	updateToDatabaseWithoutChildren();

	if (!sendMail)
		return;

	//Send out new citizen email
	ManagedReference<ChatManager*> chatManager = server->getChatManager();
	ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

	if (chatManager == NULL || playerManager == NULL)
		return;

	ManagedReference<SceneObject*> mayorObject = server->getZoneServer()->getObject(mayorObjectID);

	if (mayorObject == NULL || !mayorObject->isPlayerCreature())
		return;

	PlayerCreature* mayor = (PlayerCreature*) mayorObject.get();

	//Send email to the mayor
	ParameterizedStringId email;
	UnicodeString subject = "@city/city:lost_city_citizen_subject"; //Lost Citizen!
	email.setStringId("@city/city:lost_city_citizen_body"); //A citizen has left your city.
	email.setTO(player->getObjectName()->getDisplayedName());

	chatManager->sendMail("@city/city:new_city_from", subject, email, mayor->getFirstName());
}

void CityHallObjectImplementation::handleNewCitySuccess() {
	//Send out emails.
	cityRank = OUTPOST;

	if (cityRegion != NULL)
		cityRegion->setRadius(150);

	ManagedReference<ChatManager*> chatManager = server->getChatManager();
	ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

	if (chatManager == NULL || playerManager == NULL)
		return;

	ManagedReference<SceneObject*> mayorObject = server->getZoneServer()->getObject(mayorObjectID);

	if (mayorObject == NULL || !mayorObject->isPlayerCreature())
		return;

	PlayerCreature* mayor = (PlayerCreature*) mayorObject.get();

	//Send email to the mayor
	ParameterizedStringId email;
	UnicodeString subject = "@city/city:new_city_success_subject"; //New City Approved!
	email.setStringId("@city/city:new_city_success_body"); //Congratulations!  The Planetary Civic Authority has approved your city's zoning permits!  Your city is valid and will begin to grow as citizens join it.

	chatManager->sendMail("@city/city:new_city_from", subject, email, mayor->getFirstName());
}

void CityHallObjectImplementation::handleNewCityFailure() {
	ManagedReference<ChatManager*> chatManager = server->getChatManager();
	ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

	if (chatManager == NULL || playerManager == NULL)
		return;

	ManagedReference<SceneObject*> mayorObject = server->getZoneServer()->getObject(mayorObjectID);

	if (mayorObject == NULL || !mayorObject->isPlayerCreature())
		return;

	PlayerCreature* mayor = (PlayerCreature*) mayorObject.get();

	//Send email to the mayor
	ParameterizedStringId email;
	UnicodeString subject = "@city/city:new_city_fail_subject"; //Zoning Permits Rejected
	email.setStringId("@city/city:new_city_fail_body"); //We are sorry to inform you that your city failed to receive sufficient interest to remain solvent.  Your zoning applications have been rejected and your city hall has been removed.

	chatManager->sendMail("@city/city:new_city_from", subject, email, mayor->getFirstName());

	//TODO: Destroy the city hall and civic structures.
}
