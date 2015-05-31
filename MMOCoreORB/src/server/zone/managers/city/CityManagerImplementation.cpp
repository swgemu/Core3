/*
 * CityManagerImplementation.cpp
 *
 *  Created on: Oct 10, 2010
 *      Author: crush
 */

#include "engine/engine.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/chat/ChatManager.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/player/sessions/CitySpecializationSession.h"
#include "server/zone/objects/player/sessions/CityTreasuryWithdrawalSession.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/callbacks/CityTreasuryDepositSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/CityManageMilitiaSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/CityAddMilitiaMemberSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/CityRegisterSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/CityMayoralVoteSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/CityAdjustTaxSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/CitySetTaxSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/CityToggleZoningSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/CityForceRankSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/CityForceUpdateSuiCallback.h"
#include "server/zone/objects/region/CitizenList.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "TaxPayMailTask.h"
#include "server/zone/templates/tangible/SharedStructureObjectTemplate.h"
#include "server/zone/objects/player/sui/callbacks/RenameCitySuiCallback.h"


#ifndef CITY_DEBUG
#define CITY_DEBUG
#endif

CitiesAllowed CityManagerImplementation::citiesAllowedPerRank;
CitySpecializationMap CityManagerImplementation::citySpecializations;
CityTaxMap CityManagerImplementation::cityTaxes;
Vector<uint8> CityManagerImplementation::citizensPerRank;
Vector<uint16> CityManagerImplementation::radiusPerRank;
int CityManagerImplementation::cityUpdateInterval = 0;
int CityManagerImplementation::newCityGracePeriod = 0;
int CityManagerImplementation::oldCityGracePeriod = 0;
uint64 CityManagerImplementation::citySpecializationCooldown = 0;
int CityManagerImplementation::cityVotingDuration = 0;
uint64 CityManagerImplementation::treasuryWithdrawalCooldown = 0;
byte CityManagerImplementation::cityVotingCycles = 0;
byte CityManagerImplementation::cityVotingCyclesUntilLocked = 0;
int CityManagerImplementation::decorationsPerRank = 10;
int CityManagerImplementation::trainersPerRank = 3;
int CityManagerImplementation::missionTerminalsPerRank = 3;
float CityManagerImplementation::maintenanceDiscount = 1.0f;

void CityManagerImplementation::loadLuaConfig() {
	info("Loading configuration file.", true);

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/city_manager.lua");

	LuaObject luaObject = lua->getGlobalObject("CitiesAllowed");

	if (luaObject.isValidTable()) {
		for (int i = 1; i <= luaObject.getTableSize(); ++i) {
			LuaObject planetCitiesAllowed = luaObject.getObjectAt(i);

			if (planetCitiesAllowed.isValidTable()) {
				String planet = planetCitiesAllowed.getStringAt(1);
				LuaObject citiesAllowed = planetCitiesAllowed.getObjectAt(2);

				if (citiesAllowed.isValidTable()) {
					Vector < byte > table;

					for (int j = 1; j <= citiesAllowed.getTableSize(); ++j) {
						table.add(citiesAllowed.getIntAt(j));
					}

					citiesAllowedPerRank.put(planet, table);
				}

				citiesAllowed.pop();
			}

			planetCitiesAllowed.pop();
		}
	}

	luaObject.pop();

	luaObject = lua->getGlobalObject("CitySpecializations");
	citySpecializations.readObject(&luaObject);
	luaObject.pop();

	info("Loaded " + String::valueOf(citySpecializations.size()) + " city specializations.", true);

	luaObject = lua->getGlobalObject("CityTaxes");
	cityTaxes.readObject(&luaObject);
	luaObject.pop();

	info("Loaded " + String::valueOf(cityTaxes.size()) + " city tax rules.", true);

	//Only load the static values on the first zone.
	cityUpdateInterval = lua->getGlobalInt("CityUpdateInterval");
	newCityGracePeriod = lua->getGlobalInt("NewCityGracePeriod");
	oldCityGracePeriod = lua->getGlobalInt("OldCityGracePeriod");
	citySpecializationCooldown = lua->getGlobalLong("CitySpecializationCooldown");
	cityVotingDuration = lua->getGlobalInt("CityVotingDuration");
	treasuryWithdrawalCooldown = lua->getGlobalLong("TreasuryWithdrawalCooldown");
	cityVotingCycles = lua->getGlobalByte("CityVotingCycles");
	cityVotingCyclesUntilLocked = lua->getGlobalByte("CityVotingCyclesUntilLocked");
	decorationsPerRank = lua->getGlobalInt("DecorationsPerRank");
	trainersPerRank = lua->getGlobalInt("TrainersPerRank");
	missionTerminalsPerRank = lua->getGlobalInt("MissionTerminalsPerRank");
	maintenanceDiscount = lua->getGlobalFloat("maintenanceDiscount");

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

	delete lua;
	lua = NULL;
}

void CityManagerImplementation::loadCityRegions() {
	info("Loading any remaining city regions.", true);

	ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();

	ObjectDatabase* cityRegionsDB = ObjectDatabaseManager::instance()->loadObjectDatabase("cityregions", true);

	if (cityRegionsDB == NULL) {
		error("Could not load the city regions database.");
		return;
	}

	int i = 0;

	try {
		ObjectDatabaseIterator iterator(cityRegionsDB);

		ObjectInputStream* objectData = new ObjectInputStream(2000);

		uint64 objectID;

		while (iterator.getNextKeyAndValue(objectID, objectData)) {
			Reference<CityRegion*> object = Core::getObjectBroker()->lookUp(objectID).castTo<CityRegion*>();

			if (object != NULL && object->getZone() != NULL) {
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
	ManagedReference<CityRegion*> city = new CityRegion(true);
	ObjectManager::instance()->persistObject(city, 1, "cityregions");

	Locker clocker(city, mayor);

	city->setCustomRegionName(cityName);
	city->setZone(mayor->getZone());
	city->setCityRank(OUTPOST);
	city->setMayorID(mayor->getObjectID());
	Region* region = city->addRegion(x, y, radiusPerRank.get(OUTPOST - 1), true);

	city->resetVotingPeriod();
	city->setAssessmentPending(true);
	city->scheduleCitizenAssessment(newCityGracePeriod * 60);
	city->rescheduleUpdateEvent(cityUpdateInterval * 60); //Minutes

	StringIdChatParameter params("city/city", "new_city_body");
	params.setTO(mayor);
	UnicodeString subject = "@city/city:new_city_subject"; // New City Established!

	ChatManager* chatManager = zoneServer->getChatManager();
	chatManager->sendMail("@city/city:new_city_from", subject, params, mayor->getFirstName(), NULL);

	cities.put(cityName, city);

	return city;
}

bool CityManagerImplementation::isCityRankCapped(const String& planetName, byte rank) {
	Vector < byte > *citiesAllowed = &citiesAllowedPerRank.get(planetName);
	byte maxAtRank = citiesAllowed->get(rank - 1);
	byte totalAtRank = 0;

	Locker _lock(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < cities.size(); ++i) {
		CityRegion* city = cities.get(i);

		Zone* cityZone = city->getZone();

		if (cityZone == NULL || cityZone->getZoneName() != planetName)
			continue;

		if (city->getCityRank() >= rank) {
			if (++totalAtRank >= maxAtRank) {
				return true;
			}
		}
	}

	return (totalAtRank >= maxAtRank);
}

void CityManagerImplementation::sendCityReport(CreatureObject* creature, const String& planetName, byte rank) {
	Locker _lock(_this.getReferenceUnsafeStaticCast(),creature);

	Vector < byte > *citiesAllowed = &citiesAllowedPerRank.get(planetName.toLowerCase());

	if(citiesAllowed->size() == 0) {
		creature->sendSystemMessage("INVALID PLANET");
		return;
	}

	int totalCities = 0;
	int totalErroredCities = 0;

	StringBuffer report;
	report << endl << "===============================" << endl;
	report << "City Info / Planet = " << planetName.toUpperCase();

	if (rank > 0)
		report << "  Rank = " << String::valueOf(rank) << endl;
	else
		report << endl;

	report << "===================================" << endl;
	report << "City, ";

	if (rank == 0)
		report << "Rank, ";

	report << "oid, mayorid, cityhallid, regions, citizens, civicstructures, totalstructures, treasury, Loc, Next Update, next citizen Assessment (if pending)" << endl;

	for (int i = 0; i < cities.size(); ++i) {
		CityRegion* city = cities.get(i);

		Zone* cityZone = city->getZone();

		if (cityZone == NULL) {
				totalErroredCities++;
				continue;
		}

		if(cityZone->getZoneName().toLowerCase() != planetName.toLowerCase()) {
			continue;
		}

		if (rank > 0 && city->getCityRank() != rank)
			continue;

		ManagedReference<StructureObject*> cityHall = city->getCityHall();

		totalCities++;
		report << city->getRegionName();

		if (rank == 0)
			report << ", " << String::valueOf(city->getCityRank());

		report << ", " << String::valueOf(city->getObjectID())
			<< ", " << String::valueOf(city->getMayorID());

		if (cityHall != NULL) {
			report << ", " << String::valueOf(cityHall->getObjectID());
		} else {
			report << ", NULL";
		}

		report << ", " << String::valueOf(city->getRegionsCount())
			<< ", " << String::valueOf(city->getCitizenCount())
			<< ", " << String::valueOf(city->getStructuresCount())
			<< ", " << String::valueOf(city->getAllStructuresCount())
			<< ", " << String::valueOf((int)city->getCityTreasury())
			<< ", x: " << String::valueOf(city->getPositionX()) << " y:" << String::valueOf(city->getPositionY())
			<< ", " << city->getNextUpdateTime()->getFormattedTime();

		if (city->hasAssessmentPending()) {
			report << ", " << city->getNextAssessmentTime()->getFormattedTime() << endl;
		} else {
			report << endl;
		}

	}

	report << "==============================" << endl;
	report << "Total Cities: " << String::valueOf(totalCities) << endl;

	if (rank > 0) {
		byte maxAtRank = citiesAllowed->get(rank - 1);
		report << "Max at rank: " << String::valueOf(maxAtRank) << endl;
	}

	report << "Total Errored Cities (all planets & ranks): " << String::valueOf(totalErroredCities) << endl;
	report << "==============================" << endl;
	creature->sendSystemMessage(report.toString());

	ChatManager* chatManager = zoneServer->getChatManager();
	String title = "cityInfo - " + planetName.toUpperCase();
	if (rank > 0)
		title += ", Rank " + String::valueOf(rank);

	chatManager->sendMail("System", title , report.toString(), creature->getFirstName());
}

bool CityManagerImplementation::validateCityInRange(CreatureObject* creature, Zone* zone, float x, float y) {
	Vector3 testPosition(x, y, 0);

	Locker locker(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < cities.size(); ++i) {
		CityRegion* city = cities.get(i);
		Zone* cityZone = city->getZone();

		if (cityZone == zone) {
			try {
				Vector3 position(city->getPositionX(), city->getPositionY(), 0);

				if (position.squaredDistanceTo(testPosition) < 1024 * 1024) {
					StringIdChatParameter msg("player_structure", "city_too_close");
					msg.setTO(city->getRegionName());

					creature->sendSystemMessage(msg);

					return false;
				}
			} catch (Exception& e) {
				continue;
			}
		}
	}

	return true;
}

bool CityManagerImplementation::validateCityName(const String& name) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	if (cities.contains(name) || cities.contains(name.toLowerCase()))
		return false;

	return true;
}

void CityManagerImplementation::promptCitySpecialization(CityRegion* city, CreatureObject* mayor, SceneObject* terminal) {

	ManagedReference<CitySpecializationSession*> session = new CitySpecializationSession(mayor, city, terminal);
	mayor->addActiveSession(SessionFacadeType::CITYSPEC, session);
	session->initializeSession();
}

void CityManagerImplementation::changeCitySpecialization(CityRegion* city, CreatureObject* mayor, const String& spec) {
	Locker _clock(city, mayor);

	city->setCitySpecialization(spec);

	PlayerObject* ghost = mayor->getPlayerObject().get();

	if (ghost != NULL && !ghost->isPrivileged())
		mayor->addCooldown("city_specialization", citySpecializationCooldown); //1 week.

	StringIdChatParameter params("city/city", "spec_set"); //The city's specialization has been set to %TO.

	if (spec.isEmpty())
		params.setTO("@city/city:null");
	else
		params.setTO(spec);

	mayor->sendSystemMessage(params);

	//Resetting the city radius will remove it and reinsert it, updating it to everything in the area.
	city->setRadius(city->getRadius());
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

	ManagedReference<SceneObject*> mayor = zoneServer->getObject(city->getMayorID());

	list->addMenuItem("@city/city:name_prompt " + city->getRegionName()); //Name:

	if (mayor != NULL) {
		list->addMenuItem("@city/city:mayor_prompt " + mayor->getDisplayedName()); //Mayor:
	} else {
		list->addMenuItem("@city/city:mayor_prompt @city/city:null"); // Mayor: None
	}

	StringBuffer location;
	location << city->getPositionX() << " " << city->getPositionY();

	list->addMenuItem("@city/city:location_prompt " + location.toString()); //Location:
	list->addMenuItem("@city/city:radius_prompt " + String::valueOf(city->getRadius())); //Radius:
	list->addMenuItem("@city/city:citizen_prompt " + String::valueOf(city->getCitizenCount())); //Citizenship:
	list->addMenuItem("@city/city:structures_prompt " + String::valueOf(city->getAllStructuresCount())); //Structures:

	if (city->getCitySpecialization().isEmpty())
		list->addMenuItem("@city/city:specialization_prompt @city/city:null"); //Specialization: None
	else
		list->addMenuItem("@city/city:specialization_prompt " + city->getCitySpecialization()); //Specialization:

	list->addMenuItem("@city/city:current_trainers " + String::valueOf(city->getSkillTrainerCount())); // Current Trainer Count:
	list->addMenuItem("@city/city:current_mt " + String::valueOf(city->getMissionTerminalCount())); // Current Terminal Count:

	for (int i = 0; i < cityTaxes.size(); ++i) {
		CityTax* cityTax = &cityTaxes.get(i);
		int tax = city->getTax(i);
		String prompt = cityTax->getStatusPrompt();

		if (prompt.isEmpty())
			continue;

		if (prompt == "@city/city:travel_cost_prompt" && !city->hasShuttleInstallation()) {
			prompt += "_none";
			list->addMenuItem(prompt);
		} else {
			list->addMenuItem(prompt + " " + String::valueOf(tax));
		}
	}

	creature->sendMessage(list->generateMessage());
}

void CityManagerImplementation::sendStructureReport(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	ManagedReference<SuiListBox*> maintList = new SuiListBox(creature, SuiWindowType::CITY_TREASURY_REPORT);
	maintList->setPromptTitle("@city/city:structure_list_t"); // City Structure Report
	maintList->setPromptText("@city/city:structure_list_d");

	for (int i = 0; i < city->getStructuresCount(); i++) {
		ManagedReference<StructureObject*> structure = city->getCivicStructure(i);
		if (structure != NULL)
			maintList->addMenuItem(structure->getObjectName()->getFullPath() + " - Condition : "
					+ String::valueOf((1.0f * structure->getMaxCondition() - structure->getConditionDamage())
							/ structure->getMaxCondition() * 100) + "%", i);

	}

	for (int i = 0; i < city->getDecorationCount(); i++) {
		ManagedReference<StructureObject*> deco = cast<StructureObject*> (city->getCityDecoration(i));

		if (deco != NULL)
			maintList->addMenuItem(deco->getObjectName()->getFullPath() + " - Condition : "
					+ String::valueOf((1.0f * deco->getMaxCondition() - deco->getConditionDamage())
							/ deco->getMaxCondition() * 100) + "%", i);
	}

	ghost->addSuiBox(maintList);
	creature->sendMessage(maintList->generateMessage());
}

void CityManagerImplementation::promptWithdrawCityTreasury(CityRegion* city, CreatureObject* mayor, SceneObject* terminal) {
	if (!city->isMayor(mayor->getObjectID()))
		return;

	if (!mayor->checkCooldownRecovery("city_withdrawal") && !mayor->getPlayerObject()->isPrivileged()) {
		mayor->sendSystemMessage("@city/city:withdraw_daily"); //You may only withdraw from the city treasury once per day.
		return;
	}

	ManagedReference<CityTreasuryWithdrawalSession*> session = new CityTreasuryWithdrawalSession(mayor, city, terminal);
	mayor->addActiveSession(SessionFacadeType::CITYWITHDRAW, session);
	session->initializeSession();
}

void CityManagerImplementation::withdrawFromCityTreasury(CityRegion* city, CreatureObject* mayor, int value, const String& reason, SceneObject* terminal) {
	/**
	 string/en/city/city.stf	264	treasury_withdraw_from	City Treasury Authority
	 string/en/city/city.stf	265	treasury_withdraw_subject	City Treasury Withdrawal
	 string/en/city/city.stf	266	treasury_withdraw_body	Attention! Mayor %TO has made a withdrawal from the City Treasury. Amount: %DI Reason: %TT - Treasury Authority
	 */

	Locker locker(mayor);
	Locker clocker(city, mayor);

	int minWithdrawal = city->getMinWithdrawal();

	if (city->getCityTreasury() < minWithdrawal) {
		mayor->sendSystemMessage("@city/city:no_money"); //There isn't any money to transfer!
		return;
	}

	ManagedReference<CityTreasuryWithdrawalSession*> session = mayor->getActiveSession(SessionFacadeType::CITYWITHDRAW).castTo<CityTreasuryWithdrawalSession*>();

	if (session == NULL) {
		mayor->sendSystemMessage("@city/city:withdraw_treasury_error"); // Unable to complete withdraw. Please try again.
		return;
	}

	if (!mayor->checkCooldownRecovery("city_withdrawal") && !mayor->getPlayerObject()->isPrivileged()) {
		mayor->sendSystemMessage("@city/city:withdraw_daily"); //You may only withdraw from the city treasury once per day.
		session->cancelSession();
		return;
	}

	if (value < 0) {
		mayor->sendSystemMessage("@city/city:withdraw_treasury"); //You must select a positive amount to withdraw from the treasury.
		session->cancelSession();
		return;
	}

	int maxWithdrawal = MIN(city->getMaxWithdrawal(), city->getCityTreasury());

	if (value > maxWithdrawal || value < minWithdrawal) {
		mayor->sendSystemMessage("@city/city:withdraw_limits"); // You may only withdraw between 10,000 and 50,000 credits per day.
		session->cancelSession();
		return;
	}

	mayor->addBankCredits(value, true);
	city->subtractFromCityTreasury(value);

	mayor->addCooldown("city_withdrawal", CityManagerImplementation::treasuryWithdrawalCooldown);

	session->cancelSession();

	StringIdChatParameter message("@new_player:credits_reward"); // %DI credits have been deposited into your bank account.
	message.setDI(value);
	mayor->sendSystemMessage(message);

	StringIdChatParameter emailBody("@city/city:treasury_withdraw_body");
	emailBody.setDI(value);
	emailBody.setTO(mayor);
	emailBody.setTT(reason);

	sendMail(city, "@city/city:treasury_withdraw_from", "@city/city:treasury_withdraw_subject", emailBody, NULL);
}

void CityManagerImplementation::promptDepositCityTreasury(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	ManagedReference<SuiTransferBox*> transfer = new SuiTransferBox(creature, SuiWindowType::CITY_TREASURY_DEPOSIT);
	transfer->setPromptTitle("@city/city:treasury_deposit"); //Treasury Deposit
	transfer->setPromptText("@city/city:treasury_deposit_d"); //Enter the amount you would like to transfer to the city treasury.
	transfer->addFrom("@city/city:funds", String::valueOf(creature->getCashCredits()), String::valueOf(creature->getCashCredits()), "1");
	transfer->addTo("@city/city:treasury", "0", "0", "1");
	transfer->setUsingObject(terminal);
	transfer->setForceCloseDistance(16.f);
	transfer->setCallback(new CityTreasuryDepositSuiCallback(zoneServer, city));

	ghost->addSuiBox(transfer);
	creature->sendMessage(transfer->generateMessage());
}

void CityManagerImplementation::depositToCityTreasury(CityRegion* city, CreatureObject* creature, int amount) {
	int cash = creature->getCashCredits();

	int total = cash - amount;

	if (total < 1 || total > cash) {
		creature->sendSystemMessage("@city/city:positive_deposit"); //You must select a positive amount to transfer to the treasury.
		return;
	}

	double currentTreasury = city->getCityTreasury();

	if ((int)currentTreasury + total > 100000000) {
		creature->sendSystemMessage("The maximum treasury a city can have is 100.000.000");
		return;
	}

	city->addToCityTreasury(total);
	creature->subtractCashCredits(total);

	StringIdChatParameter params("city/city", "deposit_treasury"); //You deposit %DI credits into the treasury.
	params.setDI(total);
	creature->sendSystemMessage(params);
}

void CityManagerImplementation::sendCitizenshipReport(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	//Check if they already have the window open.
	if (ghost->hasSuiBoxWindowType(SuiWindowType::CITY_CITIZEN_REPORT))
		return;

	ManagedReference<SuiListBox*> listbox = new SuiListBox(creature, SuiWindowType::CITY_CITIZEN_REPORT);
	listbox->setPromptTitle("@city/city:citizen_list_t"); //City Citizenship Report
	listbox->setPromptText("@city/city:citizen_list_d"); //The following is a list of the currently declared citizens (residents) of this city. All citizens are elligible to vote.
	listbox->setUsingObject(terminal);
	listbox->setForceCloseDistance(16.f);
	listbox->addMenuItem("@city/city:reg_citizen_prompt"); // Registered Citizens:

	CitizenList* citizenList = city->getCitizenList();

	for (int i = 0; i < citizenList->size(); ++i) {
		ManagedReference<SceneObject*> citizen = zoneServer->getObject(citizenList->get(i));

		if (citizen != NULL) {
			String name = "@city/city:default \t" + citizen->getDisplayedName();

			if (city->isMilitiaMember(citizen->getObjectID()))
				name += " @city/city:militia_suffix"; // (Militia)

			listbox->addMenuItem(name);
		}
	}

	ghost->addSuiBox(listbox);
	creature->sendMessage(listbox->generateMessage());
}

void CityManagerImplementation::assessCitizens(CityRegion* city) {
	Locker locker(city);

	if (zoneServer->isServerLoading()) {
		city->scheduleCitizenAssessment(10);
		return;
	}

	info("Assessing city citizens: " + city->getRegionName(), true);

	city->cleanupCitizens();

	int citizens = city->getCitizenCount();

	ChatManager* chatManager = zoneServer->getChatManager();

	ManagedReference<SceneObject*> obj = zoneServer->getObject(city->getMayorID());
	CreatureObject* mayor = NULL;

	if (obj != NULL && obj->isPlayerCreature()) {
		mayor = cast<CreatureObject*> (obj.get());
	}

	if (citizens < citizensPerRank.get(0)) {
		if (mayor != NULL) {
			StringIdChatParameter params("city/city", "new_city_fail_body");
			UnicodeString subject = "@city/city:new_city_fail_subject"; // Zoning Permits Rejected

			chatManager->sendMail("@city/city:new_city_from", subject, params, mayor->getFirstName(), NULL);
		}

		ManagedReference<StructureObject*> cityhall = city->getCityHall();

		if (cityhall != NULL) {
			StructureManager::instance()->destroyStructure(cityhall);
		} else {
			locker.release();

			destroyCity(city);
		}

	} else {
		if (mayor != NULL) {
			StringIdChatParameter params("city/city", "new_city_success_body");
			UnicodeString subject = "@city/city:new_city_success_subject"; // New City Approved!

			chatManager->sendMail("@city/city:new_city_from", subject, params, mayor->getFirstName(), NULL);
		}

		city->setAssessmentPending(false);
	}
}

void CityManagerImplementation::processCityUpdate(CityRegion* city) {
	info("Processing city update: " + city->getRegionName(), true);

	int cityRank = 0;
	float radius = 0;

	try {
		cityRank = city->getCityRank();

		if (cityRank == CLIENT)
			return; //It's a client region.

		radius = city->getRadius();

		city->cleanupCitizens();

		ManagedReference<SceneObject*> mayor = zoneServer->getObject(city->getMayorID());

		if (mayor != NULL && mayor->isPlayerCreature()) {
			Reference<PlayerObject*> ghost = mayor->getSlottedObject("ghost").castTo<PlayerObject*> ();
			ghost->addExperience("political", 750, true);
		}

		updateCityVoting(city);

		int citizens = city->getCitizenCount();

		if (cityRank - 1 >= citizensPerRank.size())
			return;

		int maintainCitizens = citizensPerRank.get(cityRank - 1);

		if (citizens < maintainCitizens) {
			contractCity(city);
		} else if (cityRank < METROPOLIS) {
			int advanceCitizens = citizensPerRank.get(cityRank);

			if (citizens >= advanceCitizens) {
				expandCity(city);
			} else {
				city->destroyAllStructuresForRank(uint8(cityRank + 1), true);
			}
		}

		city->rescheduleUpdateEvent(cityUpdateInterval * 60);

		processIncomeTax(city);

		deductCityMaintenance(city);

	} catch (Exception& e) {
		error(e.getMessage() + "in CityManagerImplementation::processCityUpdate");
		e.printStackTrace();
		return;
	}

}

void CityManagerImplementation::processIncomeTax(CityRegion* city) {
	int incomeTax = city->getIncomeTax();

	if (incomeTax <= 0)
		return;

	ManagedReference<SceneObject*> mayorObject = zoneServer->getObject(city->getMayorID());

	if (mayorObject == NULL || !mayorObject->isPlayerCreature()) {
		error("Mayor is null or not set in process income tax for city: " + city->getRegionName());
		return;
	}

	CreatureObject* mayor = mayorObject.castTo<CreatureObject*> ();
	String mayorName = mayor->getFirstName();

	ChatManager* chatManager = zoneServer->getChatManager();

	CitizenList* citizens = city->getCitizenList();

	Reference<TaxPayMailTask*> task = new TaxPayMailTask(incomeTax, mayorName, chatManager, city);

	for (int i = 0; i < citizens->size(); ++i) {
		uint64 oid = citizens->get(i);

		ManagedReference<SceneObject*> obj = zoneServer->getObject(oid);

		if (obj == NULL || !obj->isPlayerCreature())
			continue;

		CreatureObject* citizen = obj.castTo<CreatureObject*> ();

		task->addCitizen(citizen);
	}

	task->execute();
}

void CityManagerImplementation::deductCityMaintenance(CityRegion* city) {
	int totalPaid = 0;

	Locker _lock(city);

	TemplateManager* templateManager = TemplateManager::instance();
	if (templateManager == NULL)
		return;

	// pay city hall maintenanance first
	ManagedReference<StructureObject*> ch = city->getCityHall();

	if (ch == NULL || ch->getObjectTemplate() == NULL)
		return;

	Reference<SharedStructureObjectTemplate*> structureTemplate = cast<SharedStructureObjectTemplate*> (ch->getObjectTemplate());

	if (structureTemplate == NULL)
		return;

	int thisCost = maintenanceDiscount * structureTemplate->getCityMaintenanceAtRank(city->getCityRank() - 1);
	totalPaid +=  collectCivicStructureMaintenance(ch, city, thisCost);

	for(int i = 0; i < city->getStructuresCount(); i++) {
		ManagedReference<StructureObject*> str = city->getCivicStructure(i);

		if(str != NULL && str != ch) {
			structureTemplate = cast<SharedStructureObjectTemplate*> (str->getObjectTemplate());
			thisCost = maintenanceDiscount * structureTemplate->getCityMaintenanceAtRank(city->getCityRank() - 1);
			totalPaid += collectCivicStructureMaintenance(str, city, thisCost);
		}
	}

	for(int i = city->getDecorationCount() - 1; i >= 0; i--) {
		ManagedReference<SceneObject*> decoration = city->getCityDecoration(i);

		if(decoration == NULL)
			continue;

		if( decoration->isStructureObject()) {
			StructureObject* structure = cast<StructureObject*>(decoration.get());

			if(structure != NULL) {
				structureTemplate = cast<SharedStructureObjectTemplate*>(structure->getObjectTemplate());
				thisCost = maintenanceDiscount * structureTemplate->getCityMaintenanceAtRank(city->getCityRank() - 1);
				totalPaid += collectCivicStructureMaintenance(structure, city, thisCost);
			}
		} else {
			thisCost = maintenanceDiscount * 1500;
			totalPaid += collectNonStructureMaintenance(decoration, city, thisCost);
		}
	}

	for(int i = city->getMissionTerminalCount() - 1; i >= 0; i--) {
		thisCost = maintenanceDiscount * 1500;
		totalPaid += collectNonStructureMaintenance(city->getCityMissionTerminal(i), city, thisCost);
	}

	for(int i = city->getSkillTrainerCount() -1; i >=0; i--) {
		thisCost = maintenanceDiscount * 1500;
		totalPaid += collectNonStructureMaintenance(city->getCitySkillTrainer(i), city, thisCost);
	}

	if(city->isRegistered()) {
		thisCost = maintenanceDiscount * 5000;

		if(city->getCityTreasury() >= thisCost) {
			city->subtractFromCityTreasury(thisCost);
			totalPaid += thisCost;
		} else {
			ManagedReference<CreatureObject*> mayor = zoneServer->getObject(city->getMayorID()).castTo<CreatureObject*>();
			unregisterCity(city, mayor);
		}
	}

	if (city->getCitySpecialization() != "") {
		CitySpecialization* spec = getCitySpecialization(city->getCitySpecialization());

		if (spec != NULL) {
			thisCost = maintenanceDiscount * spec->getCost();

			if(city->getCityTreasury() >= thisCost) {
				city->subtractFromCityTreasury(thisCost);
				totalPaid += thisCost;
			} else {
				city->setCitySpecialization("");
				// Reset the region to remove specialization modifiers from players
				city->setRadius(city->getRadius());
			}
		}
	}

	sendMaintenanceEmail(city, totalPaid);
}

int CityManagerImplementation::collectNonStructureMaintenance(SceneObject* object, CityRegion* city, int maintenanceDue) {
	if(object == NULL || city == NULL)
		return 0;

	int amountPaid = 0;
	if(city->getCityTreasury() >= maintenanceDue) {
		city->subtractFromCityTreasury(maintenanceDue);
		amountPaid = maintenanceDue;
	} else {
		Locker clock(object, city);

		// can probably be moved to cityregion notifyExit
		if(object->isMissionTerminal())
			city->removeMissionTerminal(object);
		else if (object->isDecoration())
			city->removeDecoration(object);
		else if (object->isCreatureObject())
			city->removeSkillTrainers(object);

		sendMaintenanceDestroyEmail(city, object);

		object->destroyObjectFromWorld(true);
		object->destroyObjectFromDatabase(true);
	}

	return amountPaid;
}
int CityManagerImplementation::collectCivicStructureMaintenance(StructureObject* structure, CityRegion* city, int maintenanceDue) {
	if(structure == NULL || city == NULL)
		return 0;

	Locker clocker(structure, city);

	int amountPaid = 0;
	if (city->getCityTreasury() >= maintenanceDue) {
		// we have enough to pay the full amount.  subtract from city
		city->subtractFromCityTreasury(maintenanceDue);
		amountPaid = maintenanceDue;
		// now try to fix the surplus maintenance if the structure is decayed

		int amountOwed = abs(structure->getSurplusMaintenance());

		if (amountOwed > 0) {
			if (city->getCityTreasury() >= amountOwed) {
				city->subtractFromCityTreasury(amountOwed);
				structure->setConditionDamage(0);
				structure->setSurplusMaintenance(0);
				amountPaid += amountOwed;

				sendMaintenanceRepairEmail(city,structure);

			} else {
				// pay what the city can afford on what it owes

				int currentDecay = structure->getConditionDamage();

				if(currentDecay > 0 && amountOwed > 0) {
					int availableFunds = city->getCityTreasury();
					float costPerUnitCondition = (float) amountOwed / (float) currentDecay;
					int pointsBack = availableFunds / costPerUnitCondition;

					currentDecay -= pointsBack;

					if(pointsBack > 0)
						sendMaintenanceRepairEmail(city,structure);

					city->subtractFromCityTreasury(availableFunds);
					structure->setConditionDamage(currentDecay);
					structure->setSurplusMaintenance(-(amountOwed - availableFunds));
				}
			}
		}

	} else {
		// pay what we can then decay it
		// full maint should deduct 25%
		int currentDecay = structure->getConditionDamage();
		int fundsAvailable = city->getCityTreasury();
		float amountOutstanding = maintenanceDue - fundsAvailable;
		int currentSurplus = structure->getSurplusMaintenance();
		int newDecay = (1.0f * amountOutstanding) / maintenanceDue * structure->getMaxCondition() * .25;

		currentSurplus -= amountOutstanding;
		currentDecay += newDecay;

		structure->setSurplusMaintenance(currentSurplus);
		structure->setConditionDamage(currentDecay);
		city->subtractFromCityTreasury(fundsAvailable);
		amountPaid += fundsAvailable;

		if (structure->getConditionDamage() >= structure->getMaxCondition()) {
				sendMaintenanceDestroyEmail(city, structure);
				StructureManager::instance()->destroyStructure(structure);
		} else {
			sendMaintenanceDecayEmail(city, structure, maintenanceDue);
		}
	}

	return amountPaid;
}

void CityManagerImplementation::sendMaintenanceEmail(CityRegion* city, int maint) {
	if(zoneServer != NULL) {
		ManagedReference<CreatureObject*> mayor = zoneServer->getObject(city->getMayorID()).castTo<CreatureObject*>();

		if(mayor != NULL) {
			/*
			"city_maint_body", "Mayor %TO,A total of %DI credits has been paid from the city treasury for maintenance and upkeep of structures."
			"city_maint_subject", "City Maintenance Paid"
			*/
			StringIdChatParameter emailBody("@city/city:city_maint_body");
			emailBody.setDI(maint);
			emailBody.setTO(mayor);

			Locker clock(mayor, city);
			ChatManager* chatManager = zoneServer->getChatManager();
			chatManager->sendMail("@city/city:treasury_withdraw_from", "@city/city:city_maint_subject", emailBody, mayor->getFirstName(), NULL);
		}
	}
}

void CityManagerImplementation::sendMaintenanceRepairEmail(CityRegion* city, StructureObject* structure) {
	if(zoneServer != NULL) {
		ManagedReference<CreatureObject*> mayor = zoneServer->getObject(city->getMayorID()).castTo<CreatureObject*>();

		if(mayor != NULL) {
			/*
			"structure_repaired_body", "Mayor %TO,Repair work has been done on structure %TT.  You can check the structure's condition in the structure report at the City Management terminal."
			"structure_repaired_subject", "Structure Repaired"
			*/
			StringIdChatParameter emailBody("@city/city:structure_repaired_body");
			emailBody.setTO(mayor);
			emailBody.setTT(structure->getObjectName()->getFullPath());

			Locker clock(mayor, city);
			ChatManager* chatManager = zoneServer->getChatManager();
			chatManager->sendMail("@city/city:treasury_withdraw_from", "@city/city:structure_repaired_subject", emailBody, mayor->getFirstName(), NULL);
		}
	}
}

void CityManagerImplementation::sendMaintenanceDecayEmail(CityRegion* city, StructureObject* structure, int maintenanceDue) {
	if(zoneServer != NULL) {
		ManagedReference<CreatureObject*> mayor = zoneServer->getObject(city->getMayorID()).castTo<CreatureObject*>();

		if(mayor != NULL) {
			/*
			"structure_damaged_body", "Mayor %TT,There was insufficient money to pay for the maintenance of the structure %TO.  The amount required was %DI credits.  The structure has been damaged.  You can check the structure's condition in the structure report at the City Management terminal."
			"structure_damaged_subject", "Insufficient Maintenance, Structure Damaged"
			*/
			StringIdChatParameter emailBody("@city/city:structure_damaged_body");
			emailBody.setTO(structure->getObjectName()->getFullPath());
			emailBody.setTT(mayor);
			emailBody.setDI(maintenanceDue);

			Locker clock(mayor, city);
			ChatManager* chatManager = zoneServer->getChatManager();
			chatManager->sendMail("@city/city:treasury_withdraw_from", "@city/city:structure_damaged_subject", emailBody, mayor->getFirstName(), NULL);
		}
	}
}

void CityManagerImplementation::sendMaintenanceDestroyEmail(CityRegion* city, SceneObject* object) {
	if(zoneServer != NULL) {
		ManagedReference<CreatureObject*> mayor = zoneServer->getObject(city->getMayorID()).castTo<CreatureObject*>();

		if(mayor != NULL) {
			/*
			"structure_destroyed_maint_body", "Alert Mayor %TO!The structure (or object) %TT was condemned and destroyed due to lack of maintenance!"
			"structure_destroyed_maint_subject", "Insufficient Maintenance, Structure DESTROYED"
			*/
			StringIdChatParameter emailBody("@city/city:structure_destroyed_maint_body");
			emailBody.setTO(mayor);
			emailBody.setTT(object->getObjectName()->getFullPath());

			Locker clock(mayor, city);
			ChatManager* chatManager = zoneServer->getChatManager();
			chatManager->sendMail("@city/city:treasury_withdraw_from", "@city/city:structure_destroyed_maint_subject", emailBody, mayor->getFirstName(), NULL);
		}
	}
}

void CityManagerImplementation::updateCityVoting(CityRegion* city, bool override) {
	if (!city->isVotingPeriodOver() && !override)
		return;

	VectorMap<uint64, int>* candidates = city->getCandidates();
	uint64 incumbentID = city->getMayorID();
	String incumbentName = "";
	uint64 topCandidate = city->getMayorID(); //Incumbent mayor defaults as the top candidate.
	int topVotes = 0;

	//Loop through the candidate votes.

	ManagedReference<SceneObject*> oldmayor = zoneServer->getObject(incumbentID);
	if (oldmayor != NULL && oldmayor->isPlayerCreature()) {
		CreatureObject* mayorcreature = cast<CreatureObject*> (oldmayor.get());
		if (mayorcreature != NULL)
			incumbentName = mayorcreature->getFirstName();
	}

	for (int i = 0; i < candidates->size(); ++i) {
		VectorMapEntry<uint64, int> entry = candidates->elementAt(i);

		uint64 candidateID = entry.getKey();
		int votes = entry.getValue();

		//Ensure that each vote is for a valid citizen candidate by a current city citizen.
		if (!city->isCitizen(candidateID) || !city->isCandidate(candidateID)) {
			continue;
		}

		ManagedReference<SceneObject*> mayorObject = zoneServer->getObject(candidateID);

		if (mayorObject != NULL && mayorObject->isPlayerCreature()) {
			Locker _crosslock(mayorObject, city);

			CreatureObject* mayor = cast<CreatureObject*> (mayorObject.get());

			//Make sure the candidate is still a politician.
			if (!mayor->hasSkill("social_politician_novice")) {
				continue;
			}

			Reference<PlayerObject*> ghost = mayorObject->getSlottedObject("ghost").castTo<PlayerObject*>();
			ghost->addExperience("political", votes * 300, true);

			if (votes > topVotes || (votes == topVotes && candidateID == incumbentID)) {
				topCandidate = candidateID;
				topVotes = votes;
			}
		}
	}

	//Make them the new mayor.
	city->setMayorID(topCandidate);

	city->resetBallot();
	city->resetVotingPeriod();

	ManagedReference<SceneObject*> obj = zoneServer->getObject(topCandidate);
	CreatureObject* mayor = NULL;
	if (obj != NULL && obj->isPlayerCreature()) {
		mayor = cast<CreatureObject*> (obj.get());
	}

	if (incumbentID != topCandidate) {
		// transfer structures to new mayor
		city->transferCivicStructuresToMayor();

		// transfer city specialization cooldown to new mayor
		if (mayor != NULL && oldmayor != NULL) {
			CreatureObject* oldmayorCreo = cast<CreatureObject*> (oldmayor.get());

			if (oldmayorCreo != NULL) {
				Time* cooldownTime = oldmayorCreo->getCooldownTime("city_specialization");
				int64 miliDiff = 0;

				if (cooldownTime != NULL) {
					miliDiff = cooldownTime->miliDifference();
					oldmayorCreo->updateCooldownTimer("city_specialization");
				}

				if (miliDiff > 0)
					mayor->addCooldown("city_specialization", miliDiff);
			}
		}
	}

	// send e-mail to mayors and citizens
	String winnerName;
	if (mayor != NULL)
		winnerName = mayor->getFirstName();

	StringIdChatParameter emailbody;
	String subject;

	ChatManager* chatManager = zoneServer->getChatManager();

	// send email to the incumbent
	if (topCandidate == incumbentID) {
		emailbody.setStringId("@city/city:election_incumbent_win_body"); // Congratulations, Mayor %TT!The populace of %TO has elected to retain you for another term.
		emailbody.setTO(city->getRegionName());
		emailbody.setTT(winnerName);
		subject = "@city/city:election_incumbent_win_subject"; // Election Won
		chatManager->sendMail("@city/city:new_city_from", subject, emailbody, incumbentName, NULL);
	} else {
		// send a mail to the new mayor
		emailbody.setStringId("@city/city:election_new_mayor_body"); // Congratulations, Mayor %TT! You have been elected the new mayor of %TO
		subject = "@city/city:election_new_mayor_subject"; // Congratulations Mayor!
		emailbody.setTT(winnerName);
		emailbody.setTO(city->getRegionName());
		chatManager->sendMail("@city/city:new_city_from", subject, emailbody, winnerName, NULL);

		emailbody.setStringId("@city/city:election_incumbent_lost_body"); // Citizen,It is with regret that we inform you that you have lost the position of Mayor of %TO to %TT.
		emailbody.setTO(city->getRegionName());
		emailbody.setTT(winnerName);
		subject = "@city/city:election_incumbent_lost_subject"; // election lost
		chatManager->sendMail("@city/city:new_city_from", subject, emailbody, incumbentName, NULL);
	}

	// send mail to all citizens
	if (topCandidate == incumbentID) {
		emailbody.setStringId("@city/city:public_election_inc_body"); // The city elections for %TT have been held.  The incumbent Mayor is victorious!
		subject = "@city/city:public_election_inc_subject"; // Election Results!
	} else {
		emailbody.setStringId("@city/city:public_election_body"); // The city elections for %TT have been held.  The incumbent Mayor has lost the election!  The new Mayor is citizen %TO
		subject = "@city/city:public_election_subject"; // Election Results!
	}

	emailbody.setTT(city->getRegionName());
	emailbody.setTO(winnerName);

	sendMail(city, "@city/city:new_city_from", subject, emailbody, NULL);

}

void CityManagerImplementation::contractCity(CityRegion* city) {
	uint8 newRank = city->getCityRank() - 1;
	bool startedAssessment = false;

	if (city->getCitizenCount() < citizensPerRank.get(0)) {
		newRank = OUTPOST;
		startedAssessment = true;
		city->setAssessmentPending(true);
		city->scheduleCitizenAssessment(oldCityGracePeriod * 60);
	}

	if (newRank < TOWNSHIP) {
		city->setCitySpecialization("");

		if (city->isRegistered())
			unregisterCity(city, NULL);
	}

	ManagedReference<SceneObject*> obj = zoneServer->getObject(city->getMayorID());

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* mayor = cast<CreatureObject*> (obj.get());

		ChatManager* chatManager = zoneServer->getChatManager();

		if (startedAssessment) {
			StringIdChatParameter params("city/city", "city_invalid_body");
			params.setDI(newRank);
			UnicodeString subject = "@city/city:city_invalid_subject"; // Zoning Permits Invalid!

			chatManager->sendMail("@city/city:new_city_from", subject, params, mayor->getFirstName(), NULL);
		}

		if (newRank != city->getCityRank()) {
			//Send out contraction mail.
			StringIdChatParameter params("city/city", "city_contract_body");
			params.setTO(city->getRegionName());
			params.setDI(newRank);

			UnicodeString subject = "@city/city:city_contract_subject"; // City Contraction!

			chatManager->sendMail("@city/city:new_city_from", subject, params, mayor->getFirstName(), NULL);
		} else {
			return;
		}
	}

	city->removeAmenitiesOutsideCity(radiusPerRank.get(newRank - 1));

	city->setCityRank(newRank);
	city->setRadius(radiusPerRank.get(newRank - 1));
	city->destroyAllStructuresForRank(uint8(newRank + 2), true);
	city->cleanupDecorations(decorationsPerRank * newRank);
	city->cleanupTrainers(trainersPerRank * newRank);
	city->cleanupMissionTerminals(missionTerminalsPerRank * newRank);
	city->sendStructureInvalidMails();
}

void CityManagerImplementation::expandCity(CityRegion* city) {
	uint8 currentRank = city->getCityRank();

	if (currentRank == METROPOLIS) //City doesn't expand if it's metropolis.
		return;

	uint8 newRank = currentRank + 1;

	Zone* zone = city->getZone();

	if (zone == NULL)
		return;

	ManagedReference<SceneObject*> obj = zoneServer->getObject(city->getMayorID());

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* mayor = cast<CreatureObject*> (obj.get());

		//Send out expansion mail.
		StringIdChatParameter params("city/city", "city_expand_body");
		params.setTO(city->getRegionName());
		params.setDI(newRank);

		UnicodeString subject = "@city/city:city_expand_subject"; // City Expansion!

		if (isCityRankCapped(zone->getZoneName(), newRank)) {
			params.setStringId("city/city", "city_expand_cap_body");
			subject = "@city/city:city_expand_cap_subject"; // City Expansion Capped!
			newRank = currentRank;
		}

		ChatManager* chatManager = zoneServer->getChatManager();
		chatManager->sendMail("@city/city:new_city_from", subject, params, mayor->getFirstName(), NULL);
	}

	city->setCityRank(newRank);
	city->setRadius(radiusPerRank.get(newRank - 1));
	city->sendStructureValidMails();
}

void CityManagerImplementation::destroyCity(CityRegion* city) {
	info("Destroying city: " + city->getRegionDisplayedName(), true);

	Locker locker(_this.getReferenceUnsafeStaticCast());

	cities.drop(city->getRegionName());

	locker.release();

	Locker lock(city);

	city->cancelTasks();

	unregisterCity(city, NULL);

	for (int i = CityManager::METROPOLIS; i > 0; i--) {
		city->destroyAllStructuresForRank(uint8(i), false);
	}

	city->removeAllTerminals();
	city->removeAllSkillTrainers();
	city->removeAllDecorations();

	city->destroyActiveAreas();

	ManagedReference<StructureObject*> cityhall = city->getCityHall();

	if (cityhall != NULL) {
		Zone* zone = city->getZone();

		if (zone == NULL)
			zone = cityhall->getZone();

		if (zone != NULL) {
			StructureManager::instance()->destroyStructure(cityhall);
		}
	}

	zoneServer->destroyObjectFromDatabase(city->_getObjectID());

	city->setZone(NULL);
}

void CityManagerImplementation::registerCitizen(CityRegion* city, CreatureObject* creature) {
	ChatManager* chatManager = zoneServer->getChatManager();

	ManagedReference<SceneObject*> mayor = zoneServer->getObject(city->getMayorID());

	if (mayor != NULL && mayor->isPlayerCreature()) {
		CreatureObject* mayorCreature = cast<CreatureObject*> (mayor.get());

		StringIdChatParameter params("city/city", "new_city_citizen_body");
		params.setTO(creature->getDisplayedName());

		chatManager->sendMail("@city/city:new_city_from",
				"@city/city:new_city_citizen_subject", params, // City Growth: Added Citizen
				mayorCreature->getFirstName(), NULL);

		params.setStringId("city/city", "new_city_citizen_other_body");
		params.setTU(city->getRegionName());
		params.setTT(mayorCreature->getDisplayedName());

		chatManager->sendMail("@city/city:new_city_from",
				"@city/city:new_city_citizen_other_subject", params, // Welcome, Citizen!
				creature->getFirstName(), NULL);
	}

	city->addCitizen(creature->getObjectID());
}

void CityManagerImplementation::unregisterCitizen(CityRegion* city, CreatureObject* creature) {
	ChatManager* chatManager = zoneServer->getChatManager();

	ManagedReference<SceneObject*> mayor = zoneServer->getObject(city->getMayorID());

	if (mayor != NULL && mayor->isPlayerCreature()) {
		CreatureObject* mayorCreature = cast<CreatureObject*> (mayor.get());

		StringIdChatParameter params("city/city", "lost_city_citizen_body"); // A citizen has left your city. Citizen Name: %TO
		params.setTO(creature->getDisplayedName());
		UnicodeString subject = "@city/city:lost_city_citizen_subject"; // Lost Citizen!

		chatManager->sendMail("@city/city:new_city_from", subject, params, mayorCreature->getFirstName(), NULL);
	}

	city->removeCitizen(creature->getObjectID());
	city->setMayoralVote(creature->getObjectID(), 0);

	if (city->isCandidate(creature->getObjectID())) {
		unregisterFromMayoralRace(city, creature, true);
	}
}

void CityManagerImplementation::sendManageMilitia(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	if (!ghost->hasAbility("manage_militia")) {
		creature->sendSystemMessage("@city/city:cant_militia"); //You lack the skill to manage the city militia.
		return;
	}

	ManagedReference<SuiListBox*> listbox = new SuiListBox(creature, SuiWindowType::CITY_MILITIA);
	listbox->setPromptTitle("@city/city:militia_t"); //Manage Militia
	listbox->setPromptText("@city/city:militia_d"); //Below is a list of current city militia members. These citizens have the ability to ban visitors from accessing city services as well as the ability to attack visitors for the purposes of law enforcement. To add a new citizen to the militia select "Add Militia Member" and hit OK. To remove someone from the militia, select their name and hit OK.
	listbox->setUsingObject(terminal);
	listbox->setForceCloseDistance(16.f);
	listbox->setCallback(new CityManageMilitiaSuiCallback(zoneServer, city));

	listbox->addMenuItem("@city/city:militia_new_t", 0); //Add Militia Member

	CitizenList* militiaMembers = city->getMilitiaMembers();

	for (int i = 0; i < militiaMembers->size(); ++i) {
		ManagedReference<SceneObject*> militant = zoneServer->getObject(militiaMembers->get(i));

		if (militant != NULL)
			listbox->addMenuItem(militant->getDisplayedName(), militant->getObjectID());
	}

	ghost->addSuiBox(listbox);
	creature->sendMessage(listbox->generateMessage());
}

void CityManagerImplementation::promptAddMilitiaMember(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	ManagedReference<SuiInputBox*> input = new SuiInputBox(creature, SuiWindowType::CITY_ADD_MILITIA);
	input->setPromptTitle("@city/city:militia_new_t"); //Add Militia Member
	input->setPromptText("@city/city:militia_new_d");
	input->setUsingObject(terminal);
	input->setForceCloseDistance(16.f);
	input->setCallback(new CityAddMilitiaMemberSuiCallback(zoneServer, city));

	ghost->addSuiBox(input);
	creature->sendMessage(input->generateMessage());
}

void CityManagerImplementation::addMilitiaMember(CityRegion* city, CreatureObject* mayor, const String& playerName) {
	Locker clocker(city, mayor);

	if (!city->isMayor(mayor->getObjectID()))
		return;

	PlayerManager* playerManager = zoneServer->getPlayerManager();
	uint64 militiaid = playerManager->getObjectID(playerName);

	if (militiaid == mayor->getObjectID())
		return; //Cannot add the mayor.

	if (militiaid == 0) {
		mayor->sendSystemMessage("@city/city:cant_find_player"); //The system was unable to find that player.  Make sure they are standing within 10 meters of the city terminal and try again.
		return;
	}

	if (!city->isCitizen(militiaid)) {
		mayor->sendSystemMessage("@city/city:not_citizen"); //That player must be a citizen to join the city militia.
		return;
	}

	ManagedReference<SceneObject*> obj = zoneServer->getObject(militiaid);

	if (obj == NULL || !obj->isPlayerCreature() || !obj->isInRange(mayor, 10.f)) {
		mayor->sendSystemMessage("@city/city:cant_find_player"); //The system was unable to find that player.  Make sure they are standing within 10 meters of the city terminal and try again.
		return;
	}

	CreatureObject* creature = cast<CreatureObject*> (obj.get());
	creature->sendSystemMessage("@city/city:added_militia_target"); //You have been added to the city militia.

	mayor->sendSystemMessage("@city/city:added_militia"); //The player has been successfully added to the city militia.

	city->addMilitiaMember(militiaid);
}

void CityManagerImplementation::removeMilitiaMember(CityRegion* city, CreatureObject* mayor, uint64 militiaid) {
	Locker clocker(city, mayor);

	if (!city->isMayor(mayor->getObjectID()))
		return;

	ManagedReference<SceneObject*> obj = zoneServer->getObject(militiaid);

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* creature = cast<CreatureObject*> (obj.get());
		creature->sendSystemMessage("@city/city:removed_militia_target"); //You have been removed from the city militia.
	}

	mayor->sendSystemMessage("@city/city:removed_militia"); //The player has been successfully removed from the city militia.

	city->removeMilitiaMember(militiaid);
}

void CityManagerImplementation::sendTreasuryReport(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	ManagedReference<SuiListBox*> listbox = new SuiListBox(creature, SuiWindowType::CITY_TREASURY_REPORT);
	listbox->setPromptTitle("@city/city:treasury_balance_t"); //Treasury Balance
	listbox->setPromptText("@city/city:treasury_balance_d"); //A report on the current treasury follows.
	listbox->setUsingObject(terminal);
	listbox->setForceCloseDistance(16.f);

	listbox->addMenuItem("@city/city:treasury : " + String::valueOf((int) city->getCityTreasury()) + " @city/city:credits"); // Treasury credits

	creature->sendMessage(listbox->generateMessage());
}

void CityManagerImplementation::sendCityAdvancement(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	ManagedReference<SuiListBox*> listbox = new SuiListBox(creature, SuiWindowType::CITY_ADVANCEMENT);
	listbox->setPromptTitle("@city/city:rank_info_t"); //City Rank Info
	listbox->setPromptText("@city/city:rank_info_d"); //The following report shows the current city rank, the current city population, the abilities of the city and the population required for the next rank.  If you have met your rank requirement, the city will advance in rank during the next city update.  Check the maintenance report for a projected time to the next update.
	listbox->setUsingObject(terminal);
	listbox->setForceCloseDistance(16.f);

	int rank = city->getCityRank();

	if (rank - 1 >= citizensPerRank.size())
		return;

	int currentRank = citizensPerRank.get(rank - 1);
	int nextRank = citizensPerRank.get(rank == METROPOLIS ? rank - 1 : rank);

	listbox->addMenuItem("@city/city:city_rank_prompt @city/city:rank" + String::valueOf(rank)); // City Rank:
	listbox->addMenuItem("@city/city:city_pop_prompt " + String::valueOf(city->getCitizenCount()) + " @city/city:citizens"); // City Population: citizens
	listbox->addMenuItem("@city/city:pop_req_current_rank " + String::valueOf(currentRank) + " @city/city:citizens"); // Pop. Req. for Current Rank: citizens

	if (rank < CityRegion::RANK_METROPOLIS)
		listbox->addMenuItem("@city/city:pop_req_next_rank " + String::valueOf(nextRank) + " @city/city:citizens"); // Pop. Req. for Next Rank: citizens
	else
		listbox->addMenuItem("@city/city:pop_req_next_rank @city/city:max_rank_achieved"); // Pop. Req. for Next Rank: Maximum City Rank Achieved

	listbox->addMenuItem("@city/city:max_decorations " + String::valueOf(rank * decorationsPerRank)); // Max Decorations:
	listbox->addMenuItem("@city/city:max_trainers " + String::valueOf(rank * trainersPerRank)); // Max Skill Trainers:
	listbox->addMenuItem("@city/city:max_terminals " + String::valueOf(rank * missionTerminalsPerRank)); // Max Mission Terminals:

	listbox->addMenuItem("@city/city:rank_enabled_structures"); // Rank Enabled Structures

	if (rank >= CityRegion::RANK_OUTPOST) {
		listbox->addMenuItem("@city/city:default \t @city/city:small_garden"); // Small Gardens
	}
	if (rank >= CityRegion::RANK_VILLAGE) {
		listbox->addMenuItem("@city/city:default \t @city/city:bank"); // Bank
		listbox->addMenuItem("@city/city:default \t @city/city:cantina"); // Cantina
		listbox->addMenuItem("@city/city:default \t @city/city:medium_garden"); // Medium Gardens
		listbox->addMenuItem("@city/city:default \t @city/city:garage"); // Garage
	}
	if (rank >= CityRegion::RANK_TOWNSHIP) {
		listbox->addMenuItem("@city/city:default \t @city/city:cloning_facility"); // Cloning Facility
		listbox->addMenuItem("@city/city:default \t @city/city:hospital"); // Hospital
		listbox->addMenuItem("@city/city:default \t @city/city:large_garden"); // Large Gardens
	}
	if (rank >= CityRegion::RANK_CITY) {
		listbox->addMenuItem("@city/city:default \t @city/city:theater"); // Theater
		listbox->addMenuItem("@city/city:default \t @city/city:shuttleport"); // Shuttleport
	}

	creature->sendMessage(listbox->generateMessage());

	StringIdChatParameter params("city/city", "city_update_eta"); // Next City Update: %TO
	params.setTO(getNextUpdateTimeString(city));
	creature->sendSystemMessage(params);
}

String CityManagerImplementation::getNextUpdateTimeString(CityRegion* city) {
	if (city == NULL)
		return "";

	int seconds = city->getTimeToUpdate();

	int days = floor(seconds / 86400);
	seconds -= days * 86400;

	int hours = floor(seconds / 3600);
	seconds -= hours * 3600;

	int minutes = floor(seconds / 60);
	seconds -= minutes * 60;

	StringBuffer buffer;

	if (days > 0) {
		buffer << days << " day";

		if (days > 1)
			buffer << "s";

		if (hours > 0 || minutes > 0 || seconds > 0)
			buffer << ", ";
	}

	if (hours > 0) {
		buffer << hours << " hour";

		if (hours > 1)
			buffer << "s";

		if (minutes > 0 || seconds > 0)
			buffer << ", ";
	}

	if (minutes > 0) {
		buffer << minutes << " minute";

		if (minutes > 1)
			buffer << "s";

		if (seconds > 0)
			buffer << ", ";
	}

	if (seconds > 0) {
		buffer << seconds << " second";

		if (seconds > 1)
			buffer << "s";
	}

	String updateStr = buffer.toString();

	if (updateStr.isEmpty())
		updateStr = "Now";

	return updateStr;
}

void CityManagerImplementation::promptRegisterCity(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	if (!city->isMayor(creature->getObjectID()))
		return;

	if (!ghost->hasAbility("city_map")) {
		creature->sendSystemMessage("@city/city:cant_register"); //You lack the ability to register your city!
		return;
	}

	if (city->getCityRank() < TOWNSHIP) {
		creature->sendSystemMessage("@city/city:cant_register_rank"); //Your city must be rank 3 (Township) to be registered on the planetary map.
		return;
	}

	ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, SuiWindowType::CITY_REGISTER);
	box->setPromptTitle("@city/city:register_t"); //Register City
	box->setPromptText("@city/city:register_d");
	box->setUsingObject(terminal);
	box->setForceCloseDistance(16.f);
	box->setCallback(new CityRegisterSuiCallback(zoneServer, city));

	ghost->addSuiBox(box);
	creature->sendMessage(box->generateMessage());
}

void CityManagerImplementation::promptUnregisterCity(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	if (!city->isMayor(creature->getObjectID()))
		return;

	ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, SuiWindowType::CITY_REGISTER);
	box->setPromptTitle("@city/city:unregister_t"); //Unregister City
	box->setPromptText("@city/city:unregister_d");
	box->setUsingObject(terminal);
	box->setForceCloseDistance(16.f);
	box->setCallback(new CityRegisterSuiCallback(zoneServer, city, true));

	ghost->addSuiBox(box);
	creature->sendMessage(box->generateMessage());
}

void CityManagerImplementation::registerCity(CityRegion* city, CreatureObject* mayor) {
	Reference<PlanetMapCategory*> cityCat = TemplateManager::instance()->getPlanetMapCategoryByName("city");

	if (cityCat == NULL)
		return;

	city->setRegistered(true);

	ManagedReference<Region*> aa = city->getRegion(0);
	aa->setPlanetMapCategory(cityCat);
	aa->getZone()->getPlanetManager()->addRegion(city);
	aa->getZone()->registerObjectWithPlanetaryMap(aa);

	for (int i = 0; i < city->getStructuresCount(); i++) {
		ManagedReference<StructureObject*> structure = city->getCivicStructure(i);
		aa->getZone()->registerObjectWithPlanetaryMap(structure);

		SortedVector<ManagedReference<SceneObject*> >* children = structure->getChildObjects();

		for (int j = 0; j < children->size(); j++) {
			SceneObject* child = children->get(j);

			if (child != NULL)
				aa->getZone()->registerObjectWithPlanetaryMap(child);
		}
	}

	for (int i = 0; i < city->getCommercialStructuresCount(); i++) {
		ManagedReference<StructureObject*> structure = city->getCommercialStructure(i);
		aa->getZone()->registerObjectWithPlanetaryMap(structure);
	}

	for (int i = 0; i < city->getSkillTrainerCount(); i++) {
		ManagedReference<SceneObject*> trainer = city->getCitySkillTrainer(i);
		aa->getZone()->registerObjectWithPlanetaryMap(trainer);
	}

	mayor->sendSystemMessage("@city/city:registered"); //Your city is now registered on the planetary map. All civic and major commercial structures in the city are also registered and can be found with the /find command.
}

void CityManagerImplementation::unregisterCity(CityRegion* city, CreatureObject* mayor) {
	city->setRegistered(false);

	if (city->getRegionsCount() != 0) {
		ManagedReference<Region*> aa = city->getRegion(0);
		Zone* aaZone = aa->getZone();

		if (aaZone != NULL) {
			aaZone->unregisterObjectWithPlanetaryMap(aa);

			aaZone->getPlanetManager()->dropRegion(city->getRegionName());

			for (int i = 0; i < city->getStructuresCount(); i++) {
				ManagedReference<StructureObject*> structure = city->getCivicStructure(i);
				aaZone->unregisterObjectWithPlanetaryMap(structure);

				SortedVector<ManagedReference<SceneObject*> >* children = structure->getChildObjects();

				for (int j = 0; j < children->size(); j++) {
					SceneObject* child = children->get(j);

					if (child != NULL)
						aa->getZone()->unregisterObjectWithPlanetaryMap(child);
				}
			}

			for (int i = 0; i < city->getCommercialStructuresCount(); i++) {
				ManagedReference<StructureObject*> structure = city->getCommercialStructure(i);
				aaZone->unregisterObjectWithPlanetaryMap(structure);
			}

			for (int i = 0; i < city->getSkillTrainerCount(); i++) {
				ManagedReference<SceneObject*> trainer = city->getCitySkillTrainer(i);
				aaZone->unregisterObjectWithPlanetaryMap(trainer);
			}
		}

		aa->setPlanetMapCategory(NULL);
	}

	if (mayor != NULL)
		mayor->sendSystemMessage("@city/city:unregistered"); //Your city is no longer registered on the planetary map.
}

void CityManagerImplementation::promptAdjustTaxes(CityRegion* city, CreatureObject* mayor, SceneObject* terminal) {
	ManagedReference<PlayerObject*> ghost = mayor->getPlayerObject();

	if (ghost == NULL)
		return;

	if (!ghost->hasAbility("manage_taxes")) {
		mayor->sendSystemMessage("@city/city:cant_tax"); //You lack the knowledge to manage the city's taxes.
		return;
	}

	if (city->getCityRank() < CityRegion::RANK_VILLAGE) {
		mayor->sendSystemMessage("@city/city:no_rank_taxes"); // Your city must be at least rank 2 to levy taxes.
		return;
	}

	ManagedReference<SuiListBox*> listbox = new SuiListBox(mayor, SuiWindowType::CITY_ADJUST_TAX);
	listbox->setPromptTitle("@city/city:adjust_taxes_t"); //Adjust Taxes
	listbox->setPromptText("@city/city:adjust_taxes_d"); //Select the tax you wish to adjust from the list below.
	listbox->setUsingObject(terminal);
	listbox->setForceCloseDistance(16.f);
	listbox->setCallback(new CityAdjustTaxSuiCallback(zoneServer, city));

	for (int i = 0; i < cityTaxes.size(); ++i) {
		CityTax* cityTax = &cityTaxes.get(i);
		listbox->addMenuItem(cityTax->getMenuText(), i); //Property Tax
	}

	ghost->addSuiBox(listbox);
	mayor->sendMessage(listbox->generateMessage());
}

void CityManagerImplementation::promptSetTax(CityRegion* city, CreatureObject* mayor, int selectedTax, SceneObject* terminal) {
	CityTax* cityTax = getCityTax(selectedTax);

	if (cityTax == NULL)
		return;

	ManagedReference<PlayerObject*> ghost = mayor->getPlayerObject();

	if (ghost == NULL)
		return;

	if (!ghost->hasAbility("manage_taxes")) {
		mayor->sendSystemMessage("@city/city:cant_tax"); //You lack the knowledge to manage the city's taxes.
		return;
	}

	if (city->getCityRank() < CityRegion::RANK_VILLAGE) {
		mayor->sendSystemMessage("@city/city:no_rank_taxes"); // Your city must be at least rank 2 to levy taxes.
		return;
	}

	if (cityTax->getMenuText() == "@city/city:travel_tax" && !city->hasShuttleInstallation()) {
		mayor->sendSystemMessage("@city/city:no_shuttleport"); // You can't place a travel fee. There is no shuttleport in this city.
		return;
	}

	ManagedReference<SuiInputBox*> inputbox = new SuiInputBox(mayor, SuiWindowType::CITY_TAX_PROMPT);
	inputbox->setUsingObject(terminal);
	inputbox->setForceCloseDistance(16.f);
	inputbox->setCallback(new CitySetTaxSuiCallback(zoneServer, city, selectedTax));
	inputbox->setPromptTitle(cityTax->getInputTitle());
	inputbox->setPromptText(cityTax->getInputText());

	ghost->addSuiBox(inputbox);
	mayor->sendMessage(inputbox->generateMessage());
}

void CityManagerImplementation::setTax(CityRegion* city, CreatureObject* mayor, int selectedTax, int value) {
	CityTax* cityTax = getCityTax(selectedTax);

	if (cityTax == NULL)
		return;

	if (value < cityTax->getMinValue() || value > cityTax->getMaxValue()) {
		mayor->sendSystemMessage("@city/city:tax_out_of_range"); //That tax value is outside the range limitations.
		return;
	}

	Locker _lock(city, mayor);

	city->setTax(selectedTax, value);

	_lock.release();

	StringIdChatParameter params(cityTax->getSystemMessage());
	params.setDI(value);

	mayor->sendSystemMessage(params);

	//Send out emails to all residents.

	params.setStringId(cityTax->getEmailBody());
	params.setTO(city->getRegionName());

	sendMail(city, "@city/city:new_city_from", cityTax->getEmailSubject(), params, NULL);
}

void CityManagerImplementation::sendMaintenanceReport(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	if (city == NULL || creature == NULL)
		return;

	PlayerObject* ghost = creature->getPlayerObject();
	if (ghost == NULL)
		return;

	TemplateManager* templateManager = TemplateManager::instance();
	if (templateManager == NULL)
		return;

	int totalcost = 0;

	ManagedReference<SuiListBox*> maintList = new SuiListBox(creature, SuiWindowType::CITY_TREASURY_REPORT);
	maintList->setPromptTitle("@city/city:maint_info_t"); // Maintenance Report
	maintList->setPromptText("@city/city:maint_info_d");

	ManagedReference<StructureObject*> cityHall = city->getCityHall();

	if (cityHall != NULL) {
		String maintString = "@city/city:city_hall "; // City Hall:

		if (cityHall->getObjectTemplate() != NULL) {
			Reference<SharedStructureObjectTemplate*> serverTemplate = cast<SharedStructureObjectTemplate*> (cityHall->getObjectTemplate());

			if (serverTemplate != NULL) {
				int thiscost = maintenanceDiscount * serverTemplate->getCityMaintenanceAtRank(city->getCityRank()-1);

				totalcost += thiscost;

				maintString += String::valueOf(thiscost) + " @city/city:credits";

			}
		}

		maintList->addMenuItem(maintString);
	}

	if (city->isRegistered()) {
		totalcost += 5000;
		maintList->addMenuItem("@city/city:map_reg_cost"); // Map Registration: 5000 credits
	} else {
		maintList->addMenuItem("@city/city:map_unreg"); // Map Registration: Unregistered
	}

	if (city->getCitySpecialization() != "") {
		CitySpecialization* spec = getCitySpecialization(city->getCitySpecialization());

		if (spec != NULL) {
			int speccost = maintenanceDiscount * spec->getCost();
			totalcost += speccost;
			maintList->addMenuItem("@city/city:specialization " + String::valueOf(speccost) + " @city/city:credits");
		}

	} else {
		maintList->addMenuItem("@city/city:specialization @city/city:null"); // Specialization: None
	}

	maintList->addMenuItem("@city/city:structures"); // Structures:

	for (int i = 0; i < city->getStructuresCount(); i++) {
		ManagedReference<StructureObject*> structure = city->getCivicStructure(i);

		if (structure != NULL) {
			if(structure->isCityHall())
				continue;

			String maintString = "@city/city:default \t" + structure->getObjectName()->getFullPath();

			if (structure->getObjectTemplate() == NULL)
				continue;

			Reference<SharedStructureObjectTemplate*> serverTemplate = cast<SharedStructureObjectTemplate*> (structure->getObjectTemplate());

			if (serverTemplate != NULL) {
				int thiscost = maintenanceDiscount * serverTemplate->getCityMaintenanceAtRank(city->getCityRank()-1);

				totalcost += thiscost;

				maintString += " : " + String::valueOf(thiscost) + " @city/city:credits";
			}

			maintList->addMenuItem(maintString);
		}
	}

	maintList->addMenuItem("@city/city:decorations"); // Decorations:

	for (int i = 0; i < city->getDecorationCount(); i++) {
		ManagedReference<SceneObject*> sceno = city->getCityDecoration(i);

		String maintString = "@city/city:default \t";

		if (sceno != NULL && sceno->isStructureObject()) {
			StructureObject* structure = cast<StructureObject*>(sceno.get());

			if (structure->getObjectTemplate() == NULL)
				continue;

			Reference<SharedStructureObjectTemplate*> serverTemplate = cast<SharedStructureObjectTemplate*> (structure->getObjectTemplate());

			if (serverTemplate != NULL) {
				int decCost = maintenanceDiscount * serverTemplate->getCityMaintenanceAtRank(city->getCityRank()-1);
				totalcost += decCost;
				maintString += structure->getObjectName()->getFullPath() + " : " + String::valueOf(decCost) + " @city/city:credits";
			}

		} else if ( sceno != NULL) {
			int decCost = maintenanceDiscount * 1500;
			totalcost += decCost;
			maintString += sceno->getObjectName()->getFullPath() + " : " + String::valueOf(decCost) + " @city/city:credits";
		}

		maintList->addMenuItem(maintString);
	}

	maintList->addMenuItem("@city/city:train_and_term"); // Trainers & Terminals:

	for (int i = 0; i < city->getSkillTrainerCount(); i++) {
		ManagedReference<SceneObject*> trainer = city->getCitySkillTrainer(i);

		if (trainer != NULL) {
			int trainerCost = maintenanceDiscount * 1500;
			totalcost += trainerCost;
			maintList->addMenuItem("@city/city:default \t" + trainer->getObjectName()->getFullPath() + " : " + String::valueOf(trainerCost) + " @city/city:credits");
		}
	}

	for (int i = 0; i < city->getMissionTerminalCount(); i++) {
		ManagedReference<SceneObject*> term = city->getCityMissionTerminal(i);

		if (term != NULL) {
			int terminalCost = maintenanceDiscount * 1500;
			totalcost += terminalCost;
			maintList->addMenuItem("@city/city:default \t" + term->getObjectName()->getFullPath() + " : " + String::valueOf(terminalCost) + " @city/city:credits");
		}
	}

	maintList->addMenuItem("@city/city:tot_maint " + String::valueOf(totalcost) + " @city/city:credits"); // Total Maintenance:

	ghost->addSuiBox(maintList);
	creature->sendMessage(maintList->generateMessage());
}

bool CityManagerImplementation::isCityInRange(Zone* zone, float x, float y) {
	return true;
}

void CityManagerImplementation::sendMayoralStandings(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	VectorMap<uint64, int>* candidates = city->getCandidates();

	if (candidates->size() == 0) {
		creature->sendSystemMessage("@city/city:no_candidates"); // No one has registered to run.
		return;
	}

	ManagedReference<SuiListBox*> listbox = new SuiListBox(creature, SuiWindowType::CITY_MAYOR_STANDINGS);
	listbox->setPromptText("@city/city:mayoral_standings_d");
	listbox->setPromptTitle("@city/city:mayoral_standings_t"); // Mayoral Race Standings
	listbox->setUsingObject(terminal);
	listbox->setCancelButton(true, "@cancel");

	uint64 mayorid = city->getMayorID();

	for (int i = 0; i < candidates->size(); ++i) {
		VectorMapEntry<uint64, int>* entry = &candidates->elementAt(i);

		uint64 oid = entry->getKey();

		ManagedReference<SceneObject*> candidate = zoneServer->getObject(oid);

		if (candidate == NULL)
			continue;

		if (oid != mayorid)
			listbox->addMenuItem("Challenger: " + candidate->getDisplayedName() + " -- Votes: " + String::valueOf(entry->getValue()));
		else
			listbox->addMenuItem("Incumbent: " + candidate->getDisplayedName() + " -- Votes: " + String::valueOf(entry->getValue()));

	}

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost != NULL)
		ghost->addSuiBox(listbox);

	creature->sendMessage(listbox->generateMessage());
}

void CityManagerImplementation::promptMayoralVote(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	if (!city->isCitizen(creature->getObjectID())) {
		creature->sendSystemMessage("@city/city:vote_noncitizen"); //You must be a citizen of the city to vote for Mayor.
		return;
	}

	VectorMap<uint64, int>* candidates = city->getCandidates();

	if (candidates->size() <= 0) {
		creature->sendSystemMessage("@city/city:no_candidates"); //No one has registered to run.
		return;
	}

	ManagedReference<SuiListBox*> listbox = new SuiListBox(creature, SuiWindowType::CITY_MAYOR_VOTE);
	listbox->setPromptTitle("@city/city:mayoral_vote_t"); //Place Mayoral Vote
	listbox->setPromptText("@city/city:mayoral_vote_d"); //Select your desired candidate from the list below.  You may change your vote at any time.
	listbox->setCallback(new CityMayoralVoteSuiCallback(zoneServer, city));
	listbox->setUsingObject(terminal);
	listbox->setForceCloseDistance(16.f);

	ManagedReference<SceneObject*> mayor = zoneServer->getObject(city->getMayorID());

	for (int i = 0; i < candidates->size(); ++i) {
		VectorMapEntry<uint64, int>* entry = &candidates->elementAt(i);

		ManagedReference<SceneObject*> candidate = zoneServer->getObject(entry->getKey());

		if (candidate != NULL) {
			if (mayor != NULL && candidate == mayor)
				listbox->addMenuItem(mayor->getDisplayedName() + " (Incumbent)", city->getMayorID());
			else
				listbox->addMenuItem(candidate->getDisplayedName() + " (Challenger)", entry->getKey());
		}
	}

	listbox->addMenuItem("Abstain", 0);

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost != NULL)
		ghost->addSuiBox(listbox);

	creature->sendMessage(listbox->generateMessage());
}

void CityManagerImplementation::castMayoralVote(CityRegion* city, CreatureObject* creature, uint64 oid) {

	if (!city->isCitizen(creature->getObjectID())) {
		creature->sendSystemMessage("@city/city:vote_noncitizen"); //You must be a citizen of the city to vote for Mayor.
		return;
	}

	if (oid != 0 && !city->isCandidate(oid))
		return;

	//Check if they chose to abstain from voting.
	if (oid == 0) {
		creature->sendSystemMessage("@city/city:vote_abstain"); //You have chosen to abstain in this election.
	} else {
		ManagedReference<SceneObject*> candidate = zoneServer->getObject(oid);

		if (candidate != NULL && candidate->isPlayerCreature()) {
			StringIdChatParameter params("@city/city:vote_placed"); //Your vote for %TO has been recorded.
			params.setTO(candidate->getDisplayedName());
			creature->sendSystemMessage(params);
		} else {
			return;
		}
	}

	city->setMayoralVote(creature->getObjectID(), oid);
}

void CityManagerImplementation::registerForMayoralRace(CityRegion* city, CreatureObject* creature) {
	uint64 objectid = creature->getObjectID();

	if (!city->isCitizen(objectid)) {
		creature->sendSystemMessage("@city/city:register_noncitizen"); // Only a citizen of the city may enter the race.
		return;
	}

	if (city->isVotingLocked()) {
		creature->sendSystemMessage("@city/city:registration_locked"); // The ballot is locked during the final week of voting.You may not register or unregister for the race at this time.
		return;
	}

	if (city->isCandidate(objectid)) {
		creature->sendSystemMessage("@city/city:register_dupe"); // You are already registered for the Mayoral race.
		return;
	}

	//Check to see if this creature is the mayor of another city.
	PlayerObject* ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return;

	uint64 declaredOidResidence = ghost->getDeclaredResidence();

	ManagedReference<BuildingObject*> declaredResidence = creature->getZoneServer()->getObject(declaredOidResidence).castTo<BuildingObject*>();

	if (declaredResidence != NULL) {
		ManagedReference<CityRegion*> declaredCity = declaredResidence->getCityRegion();

		if (declaredCity != NULL && declaredCity->isMayor(objectid) && city != declaredCity) {
			creature->sendSystemMessage("@city/city:already_mayor"); //You are already the mayor of a city.  You may not be mayor of another city.
			return;
		}
	}

	//Check to see if they are a Novice Politician
	if (!creature->hasSkill("social_politician_novice")) {
		creature->sendSystemMessage("@city/city:register_nonpolitician"); //You must be at least a Novice Politician in order to run for mayor.
		return;
	}

	if (!creature->checkCooldownRecovery("register_mayor") && !ghost->isPrivileged()) {
		creature->sendSystemMessage("@city/city:register_timestamp"); //You may only register to run once within a 24 hour period.
		return;
	}

	city->addCandidate(objectid);
	creature->sendSystemMessage("@city/city:register_congrats"); //Congratulations, you are now listed on the ballot for the Mayoral race!

	creature->addCooldown("register_mayor", 24 * 3600 * 1000); //Can only register to run once per day.

	StringIdChatParameter params("city/city", "rceb"); //%TO has entered the race for mayor. You can now vote for this candidate at the city voting terminal.
	params.setTO(creature->getDisplayedName());

	sendMail(city, "@city/city:new_city_from", "@city/city:registered_citizen_email_subject", params, NULL); // New Mayoral Challenger!
}

void CityManagerImplementation::unregisterFromMayoralRace(CityRegion* city, CreatureObject* creature, bool force) {
	uint64 objectid = creature->getObjectID();

	if (city->isVotingLocked() && !force) {
		creature->sendSystemMessage("@city/city:registration_locked"); // The ballot is locked during the final week of voting.You may not register or unregister for the race at this time.
		return;
	}

	if (!city->isCandidate(objectid)) {
		creature->sendSystemMessage("@city/city:not_registered"); // You aren't registered to run, so you can't unregister.
		return;
	}

	creature->sendSystemMessage("@city/city:unregistered_race"); // You have unregistered from the mayoral race.
	city->removeCandidate(objectid);

	StringIdChatParameter params("city/city", "unregistered_citizen_email_body");
	params.setTO(creature->getDisplayedName());

	sendMail(city, "@city/city:new_city_from", "@city/city:unregistered_citizen_email_subject", params, NULL); // Candidate exited the race!
}

CitySpecialization* CityManagerImplementation::getCitySpecialization(const String& name) {
	if (!citySpecializations.containsKey(name))
		return NULL;

	return &citySpecializations.get(name);
}

CityTax* CityManagerImplementation::getCityTax(int idx) {
	if (idx > cityTaxes.size() - 1 || idx < 0)
		return NULL;

	return &cityTaxes.get(idx);
}

void CityManagerImplementation::sendMail(CityRegion* city, const String& sender, const UnicodeString& subject,
		StringIdChatParameter& params, WaypointObject* waypoint) {
	ChatManager* chat = zoneServer->getChatManager();

	CitizenList* citizenList = city->getCitizenList();

	if (citizenList == NULL)
		return;

	for (int i = 0; i < citizenList->size(); ++i) {
		uint64 citizenID = citizenList->get(i);

		ManagedReference<SceneObject*> obj = zoneServer->getObject(citizenID);

		if (obj == NULL || !obj->isPlayerCreature())
			continue;

		CreatureObject* creo = obj.castTo<CreatureObject*> ();
		//TODO: Modify Chat Manager so that you can send a creo instead of simply the firstname, since sendMail eventually gets the creo anyways
		chat->sendMail(sender, subject, params, creo->getFirstName(), waypoint);
	}
}

bool CityManagerImplementation::canSupportMoreDecorations(CityRegion* city) {
	if (city == NULL)
		return false;

	return city->getDecorationCount() < (decorationsPerRank * city->getCityRank());
}

bool CityManagerImplementation::canSupportMoreTrainers(CityRegion* city) {
	if (city == NULL)
		return false;

	return city->getSkillTrainerCount() < (trainersPerRank * city->getCityRank());
}

bool CityManagerImplementation::canSupportMoreMissionTerminals(CityRegion* city) {
	if (city == NULL)
		return false;

	return city->getMissionTerminalCount() < (missionTerminalsPerRank * city->getCityRank());
}

void CityManagerImplementation::sendChangeCityName(CityRegion* city, CreatureObject* mayor){
	PlayerObject* ghost = mayor->getPlayerObject();

	if (ghost == NULL)
		return;

	if(ghost->hasSuiBoxWindowType(SuiWindowType::CITY_RENAME))
		return;

	if (!ghost->isPrivileged() && !city->isMayor(mayor->getObjectID()))
		return;

	if(!mayor->checkCooldownRecovery("rename_city_cooldown") && !ghost->isPrivileged()) {
		mayor->sendSystemMessage("You can't change the city name now");
		return;
	}

	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(mayor, SuiWindowType::CITY_RENAME, 0);
	inputBox->setPromptTitle("@city/city:city_name_new_t"); //Change City Name
	inputBox->setPromptText("@city/city:city_name_new_d"); //Enter the new city name below.  Your city must be uniquely named for this planet.  Note that the citizens of your town will receive an email notifying them of the city name change.
	inputBox->setMaxInputSize(40);
	inputBox->setCallback(new RenameCitySuiCallback(mayor->getZone(), city) );

	ghost->addSuiBox(inputBox);
	mayor->sendMessage(inputBox->generateMessage());
}

void CityManagerImplementation::sendAddStructureMails(CityRegion* city, StructureObject* structure) {
	ChatManager* chatManager = zoneServer->getChatManager();

	ManagedReference<CreatureObject*> owner = structure->getOwnerCreatureObject();
	ManagedReference<SceneObject*> mayor = zoneServer->getObject(city->getMayorID());

	if (mayor != NULL && mayor->isPlayerCreature() && owner != NULL && owner->isPlayerCreature()) {
		CreatureObject* mayorCreature = cast<CreatureObject*> (mayor.get());

		if (owner == mayorCreature)
			return;

		StringIdChatParameter params("city/city", "new_city_structure_body");
		params.setTO(owner->getDisplayedName());
		params.setTT(structure->getObjectName());

		chatManager->sendMail("@city/city:new_city_from",
				"@city/city:new_city_structure_subject", params, // City Growth: Added Structure
				mayorCreature->getFirstName(), NULL);

		StringIdChatParameter params2("city/city", "new_city_structure_other_body");
		params2.setTU(city->getRegionName());
		params2.setTO(structure->getObjectName());
		params2.setTT(mayorCreature->getDisplayedName());

		chatManager->sendMail("@city/city:new_city_from",
				"@city/city:new_city_structure_other_subject", params2, // Structure Added to City
				owner->getFirstName(), NULL);
	}
}

void CityManagerImplementation::promptToggleZoningEnabled(CityRegion* city, CreatureObject* mayor) {
	if (!city->isMayor(mayor->getObjectID())) {
		return;
	}

	if (!mayor->hasSkill("social_politician_novice")) {
		mayor->sendSystemMessage("@city/city:zoning_skill"); // You must be a Politician to enable city zoning.
		return;
	}

	bool val = city->isZoningEnabled();

	if (val) {
		toggleZoningEnabled(city, mayor);
		return;
	}

	PlayerObject* ghost = mayor->getPlayerObject();

	ManagedReference<SuiMessageBox*> box = new SuiMessageBox(mayor, SuiWindowType::CITY_ENABLE_ZONING);
	box->setPromptTitle("@city/city:zoning_t"); // Zoning
	box->setPromptText("@city/city:zoning_d"); // If you enable zoning laws in your city, other players will not be able to build structures in your city without permission. You and your militia can grant permission with the /grantZoningRights command. This command gives the target the right to build structures in your city for 24 hours.
	box->setCallback(new CityToggleZoningSuiCallback(zoneServer, city) );

	ghost->addSuiBox(box);
	mayor->sendMessage(box->generateMessage());
}

void CityManagerImplementation::promptForceRank(CityRegion* city, CreatureObject* player, bool rankUp) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	if (!ghost->isPrivileged())
		return;

	ManagedReference<SuiMessageBox*> box = new SuiMessageBox(player, SuiWindowType::CITY_ADMIN_FORCE_RANK);
	box->setPromptTitle("@city/city:force_city_rank_t"); // Force City Rank
	box->setPromptText("@city/city:force_city_rank_d");
	box->setCancelButton(true, "@cancel");
	box->setCallback(new CityForceRankSuiCallback(zoneServer, city, rankUp) );

	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void CityManagerImplementation::promptForceUpdate(CityRegion* city, CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	if (!ghost->isPrivileged())
		return;

	ManagedReference<SuiMessageBox*> box = new SuiMessageBox(player, SuiWindowType::CITY_ADMIN_FORCE_UPDATE);
	box->setPromptTitle("@city/city:force_city_update_t"); // Force City Update
	box->setPromptText("@city/city:confirm_city_update");
	box->setCancelButton(true, "@cancel");
	box->setCallback(new CityForceUpdateSuiCallback(zoneServer, city) );

	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());
}

void CityManagerImplementation::alignAmenity(CityRegion* city, CreatureObject* player, SceneObject* amenity, int direction) {
	if (amenity == NULL || player == NULL || city == NULL)
		return;

	if (!city->isMayor(player->getObjectID()) || amenity->getParent().get() != NULL)
		return;

	amenity->updateDirection(Math::deg2rad(90 * direction));
}
