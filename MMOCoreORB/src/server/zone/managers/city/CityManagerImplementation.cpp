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
#include "server/zone/objects/player/sui/callbacks/CityTreasuryDepositSuiCallback.h"

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

	loadCityRegions();
}

void CityManagerImplementation::loadCityRegions() {
	info("Loading city regions.");

	ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();

	ObjectDatabase* cityRegionsDB = ObjectDatabaseManager::instance()->loadObjectDatabase("cityregions", true);

	if (cityRegionsDB == NULL) {
		error("Could not load the city regions database.");
		return;
	}

	int i = 0;

	try {
		String zoneName = zone->getZoneName();
		ObjectDatabaseIterator iterator(cityRegionsDB);

		ObjectInputStream* objectData = new ObjectInputStream(2000);

		uint64 objectID;
		String zoneReference;

		while (iterator.getNextKeyAndValue(objectID, objectData)) {
			if (!Serializable::getVariable<String>("zone", &zoneReference, objectData)) {
				objectData->clear();
				continue;
			}

			if (zoneName != zoneReference) {
				objectData->clear();
				continue;
			}

			CityRegion* object = dynamic_cast<CityRegion*>(Core::getObjectBroker()->lookUp(objectID));

			if (object != NULL) {
				++i;
				cities.put(object->getRegionName(), object);
			} else {
				error("Failed to load city region with objectid: " + String::valueOf(objectID));
			}

			objectData->clear();
		}

		delete objectData;
	} catch (DatabaseException& e) {
		error("Failed loading city regions: " + e.getMessage());
		return;
	}

	info("Loaded " + String::valueOf(cities.size()) + " player city regions.", true);
}

CityRegion* CityManagerImplementation::createCity(CreatureObject* mayor, const String& cityName, float x, float y) {
	ManagedReference<CityRegion*> city = new CityRegion(zone, cityName);
	ObjectManager::instance()->persistObject(city, 1, "cityregions");
	city->setCityRank(OUTPOST);
	city->setMayorID(mayor->getObjectID());
	city->addRegion(x, y, radiusPerRank.get(OUTPOST));

	//TODO: Send email to mayor.

	cities.put(cityName, city);

	return city;
}


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

	ManagedReference<CitySpecializationSession*> session = new CitySpecializationSession(mayor, city, terminal);
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

	ManagedReference<CityTreasuryWithdrawalSession*> session = new CityTreasuryWithdrawalSession(mayor, city, terminal);
	mayor->addActiveSession(SessionFacadeType::CITYWITHDRAW, session);
	session->initializeSession();
}

void CityManagerImplementation::withdrawFromCityTreasury(CityRegion* city, CreatureObject* mayor, int value, SceneObject* terminal) {
	/**
	string/en/city/city.stf	264	treasury_withdraw_from	City Treasury Authority
	string/en/city/city.stf	265	treasury_withdraw_subject	City Treasury Withdrawal
	string/en/city/city.stf	266	treasury_withdraw_body	Attention! Mayor %TO has made a withdrawal from the City Treasury. Amount: %DI Reason: %TT - Treasury Authority
	 */
	if (city->getCityTreasury() <= 0) {
		mayor->sendSystemMessage("@city/city:no_money"); //There isn't any money to transfer!
		return;
	}

	ManagedReference<CityTreasuryWithdrawalSession*> session = dynamic_cast<CityTreasuryWithdrawalSession*>(mayor->getActiveSession(SessionFacadeType::CITYWITHDRAW));

	if (session == NULL)
		return;

	if (!mayor->checkCooldownRecovery("city_withdrawal")) {
		mayor->sendSystemMessage("@city/city:withdraw_daily"); //You may only withdraw from the city treasury once per day.
		session->cancelSession();
		return;
	}

	int maxWithdrawal = MIN(city->getMaxWithdrawal(), city->getCityTreasury());

	if (value < 0) {
		mayor->sendSystemMessage("@city/city:withdraw_treasury"); //You must select a positive amount to withdraw from the treasury.
		session->cancelSession();
		return;
	}

	if (value > maxWithdrawal) {
		mayor->sendSystemMessage("@city/city:withdraw_treasury_error"); //Unable to complete withdraw. Please try again.
		session->cancelSession();
		return;
	}

	mayor->addBankCredits(value, true);
	city->subtractFromCityTreasury(value);

	mayor->addCooldown("city_withdrawal", CityManagerImplementation::treasuryWithdrawalCooldown);

	session->cancelSession();

	//tODO: Send some message about receiving credits.

	//TODO: Send mail
}

void CityManagerImplementation::promptDepositCityTreasury(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	ManagedReference<SuiTransferBox*> transfer = new SuiTransferBox(creature, SuiWindowType::CITY_TREASURY_DEPOSIT);
	transfer->setPromptTitle("@city/city:treasury_deposit"); //Treasury Deposit
	transfer->setPromptText("@city/city:treasury_deposit_d"); //Enter the amount you would like to transfer to the treasury.
	transfer->addFrom("@city/city:total_funds", String::valueOf(creature->getCashCredits()), String::valueOf(creature->getCashCredits()), "1");
	transfer->addTo("@city/city:treasury", "0", "0", "1");
	transfer->setUsingObject(terminal);
	transfer->setForceCloseDistance(16.f);
	transfer->setCallback(new CityTreasuryDepositSuiCallback(creature->getZoneServer(), city));

	ghost->addSuiBox(transfer);
	creature->sendMessage(transfer->generateMessage());
}

void CityManagerImplementation::depositToCityTreasury(CityRegion* city, CreatureObject* creature, int amount) {
	int cash = creature->getCashCredits();

	int total = cash - amount;

	if (total < 1 || amount > cash) {
		creature->sendSystemMessage("@city/city:positive_deposit"); //You must select a positive amount to transfer to the treasury.
		return;
	}

	//if (total > creature->getCashCredits()) {
		//Player doesn't have that many credits
		//return;
	//}

	city->addToCityTreasury(total);
	creature->subtractCashCredits(total);

	StringIdChatParameter params("city/city", "deposit_treasury"); //You deposit %DI credits into the treasury.
	params.setDI(total);
	creature->sendSystemMessage(params);
}
