/*
 * CityManagerImplementation.cpp
 *
 *  Created on: Oct 10, 2010
 *      Author: crush
 */

#include "engine/engine.h"
#include "CityManager.h"
#include "server/chat/ChatManager.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/player/sessions/CitySpecializationSession.h"
#include "server/zone/objects/player/sessions/CityTreasuryWithdrawalSession.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"

Vector<uint8> CityManagerImplementation::citizensPerRank;
Vector<uint16> CityManagerImplementation::radiusPerRank;
int CityManagerImplementation::cityUpdateInterval = 0;
int CityManagerImplementation::newCityGracePeriod = 0;
uint64 CityManagerImplementation::citySpecializationCooldown = 0;
int CityManagerImplementation::cityVotingDuration = 0;
uint64 CityManagerImplementation::treasuryWithdrawalCooldown = 0;

void CityManagerImplementation::loadLuaConfig() {
	info("Loading config file.");

	String zoneName = zone->getZoneName();

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/city_manager.lua");

	LuaObject luaObject = lua->getGlobalObject("CitiesAllowed");

	if (luaObject.isValidTable()) {
		LuaObject rankTable = luaObject.getObjectField(zoneName);

		for (int i = 1; i <= rankTable.getTableSize(); ++i)
			citiesAllowedPerRank.add(rankTable.getIntAt(i));

		rankTable.pop();
	}

	luaObject.pop();

	//Only load the static values on the first zone.
	if (!configLoaded) {
		cityUpdateInterval = lua->getGlobalInt("CityUpdateInterval");
		newCityGracePeriod = lua->getGlobalInt("NewCityGracePeriod");
		citySpecializationCooldown = lua->getGlobalLong("CitySpecializationCooldown");
		cityVotingDuration = lua->getGlobalInt("CityVotingDuration");
		treasuryWithdrawalCooldown = lua->getGlobalLong("TreasuryWithdrawalCooldown");

		luaObject = lua->getGlobalObject("CitizensPerRank");

		if (luaObject.isValidTable()) {
			for (int i = 1; i <= luaObject.getTableSize(); ++i)
				citizensPerRank.add(luaObject.getIntAt(i));
		}

		luaObject.pop();

		luaObject = lua->getGlobalObject("RadiusPerRank");

		if (luaObject.isValidTable()) {
			for (int i = 1; i <= luaObject.getTableSize(); ++i)
				radiusPerRank.add(luaObject.getIntAt(i));
		}

		luaObject.pop();

		configLoaded = true;
	}

	delete lua;
	lua = NULL;
}

CityRegion* CityManagerImplementation::createCity(CreatureObject* mayor, const String& cityName, float x, float y) {
	CityRegion* city = new CityRegion(zone, cityName);
	city->setCityRank(OUTPOST);
	city->setMayorID(mayor->getObjectID());
	city->addRegion(x, y, radiusPerRank.get(OUTPOST));

	//TODO: Send email to mayor.

	cities.put(cityName, city);

	return city;
}

/*
void CityManagerImplementation::createNewCity(CityHallObject* city, CreatureObject* player, const String& name) {
	city->setCityName(name);

	city->setMayorObjectID(player->getObjectID());
	PlayerObject* ghost = player->getPlayerObject();

	ghost->setDeclaredResidence(city);
	declareCitizenship(city, player, false);

	city->rescheduleCityUpdate(newCityGracePeriod);

	//Create the city region
	uint32 crc = String("object/region_area.iff").hashCode();

	Region* cityRegion = cast<Region*>(ObjectManager::instance()->createObject(crc, 2, "cityregions"));
	city->setRegion(cityRegion);
	cityRegion->initializePosition(city->getPositionX(), 0, city->getPositionY());
	cityRegion->setRadius(radiusPerRank.get(NEWCITY));
	//cityRegion->setCityHall(city);

	StringId* objectName = cityRegion->getObjectName();
	objectName->setCustomString(name);

	//cityRegion->insertToZone(zone);
	zone->transferObject(cityRegion, -1, true);

	cityRegion->updateToDatabase();
	city->updateToDatabaseWithoutChildren();

	//zone->getPlanetManager()->addRegion(cityRegion);

	Locker lock(_this);

	cities.put(city->getObjectID(), city);

	//New city established email.

}

void CityManagerImplementation::changeCityName(CityHallObject* city, CreatureObject* player, const String& name) {
	city->setCityName(name);

	ManagedReference<Region*> cityRegion = city->getRegion();

	if (cityRegion != NULL) {
		StringId* objectName = cityRegion->getObjectName();
		objectName->setCustomString(name);

		cityRegion->updateToDatabase();
	}

	city->updateToDatabaseWithoutChildren();

	player->sendSystemMessage("@city/city:name_changed"); //The city name has been successfully changed.

	//TODO: Send email to citizens about name change.
}*/

bool CityManagerImplementation::validateCityName(const String& name) {
	ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();
	//ManagedReference<NameManager*> nameManager;

	if (name.length() < 3)
		return false;

	if (planetManager->hasRegion(name))
		return false;

	//Check name filter
	//if (nameManager->)

	return true;
}

void CityManagerImplementation::promptCitySpecialization(CityRegion* city, CreatureObject* mayor, SceneObject* terminal) {
	//if (city->getCityRank() < CityRegion::RANK_TOWNSHIP) {
		//mayor->sendSystemMessage("@city/city:no_rank_spec"); //Your city must be at least rank 3 before you can set a specialization
		//return;
	//}

	if (!mayor->checkCooldownRecovery("city_specialization")) {
		StringIdChatParameter params("city/city", "spec_time"); //You can't set another city spec right now. Time Remaining: %TO

		Time* timeRemaining = mayor->getCooldownTime("city_specialization");
		params.setTO(String::valueOf(round(abs(timeRemaining->miliDifference() / 1000.f))) + " seconds");
		mayor->sendSystemMessage(params);
	}

	CitySpecializationSession* session = new CitySpecializationSession(mayor, city, terminal);
	mayor->addActiveSession(SessionFacadeType::CITYSPEC, session);
	session->initializeSession();
}

void CityManagerImplementation::changeCitySpecialization(CityRegion* city, CreatureObject* mayor, const String& spec) {
	city->setCitySpecialization(spec);
	mayor->addCooldown("city_specialization", citySpecializationCooldown); //1 week.

	StringIdChatParameter params("city/city", "spec_set"); //The city's specialization has been set to %TO.
	params.setTO(spec);
	mayor->sendSystemMessage(params);
}

void CityManagerImplementation::sendStatusReport(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	/* Status Report - Lists basic information about the city.
	 * Shows the city name, current Mayor, the waypoint for the city,
	 * the city radius, number of citizens, number of structures in the city, the city specialization,
	 * tax information, and the travel cost.
	 */

	ManagedReference<SuiListBox*> list = new SuiListBox(creature, SuiWindowType::CITY_STATUS_REPORT, 0x00);
	list->setPromptTitle("@city/city:city_info_t"); //City Status Report
	list->setPromptText("@city/city:city_info_d"); //A report of the current city follows.
	list->setUsingObject(terminal);
	list->setForceCloseDistance(16.f);

	ManagedReference<SceneObject*> mayor = creature->getZoneServer()->getObject(city->getMayorID());

	list->addMenuItem("@city/city:name_prompt " + city->getRegionName()); //Name:

	if (mayor != NULL)
		list->addMenuItem("@city/city:mayor_prompt " + mayor->getObjectName()->getDisplayedName()); //Mayor:

	StringBuffer location;
	location << city->getPositionX() << " " << city->getPositionY();

	list->addMenuItem("@city/city:location_prompt " + location.toString()); //Location:
	list->addMenuItem("@city/city:radius_prompt " + String::valueOf(city->getRadius())); //Radius:
	list->addMenuItem("@city/city:reg_citizen_prompt " + String::valueOf(city->getRegisteredCitizenCount())); //Registered Citizens:
	list->addMenuItem("@city/city:structures_prompt " + String::valueOf(city->getStructuresCount())); //Structures:
	list->addMenuItem("@city/city:specialization_prompt " + city->getCitySpecialization()); //Specialization:

	//TODO: Tax information and travel cost.

	creature->sendMessage(list->generateMessage());
}

void CityManagerImplementation::promptWithdrawCityTreasury(CityRegion* city, CreatureObject* mayor, SceneObject* terminal) {
	if (!city->isMayor(mayor->getObjectID()))
		return;

	if (!mayor->checkCooldownRecovery("city_withdrawal")) {
		mayor->sendSystemMessage("@city/city:withdraw_daily"); //You may only withdraw from the city treasury once per day.
		return;
	}

	CityTreasuryWithdrawalSession* session = new CityTreasuryWithdrawalSession(mayor, city, terminal);
	mayor->addActiveSession(SessionFacadeType::CITYWITHDRAW, session);
	session->initializeSession();
}
