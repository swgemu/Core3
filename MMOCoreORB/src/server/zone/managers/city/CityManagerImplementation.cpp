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
#include "server/zone/objects/region/CitizenList.h"

CitiesAllowed CityManagerImplementation::citiesAllowedPerRank;
Vector<uint8> CityManagerImplementation::citizensPerRank;
Vector<uint16> CityManagerImplementation::radiusPerRank;
int CityManagerImplementation::cityUpdateInterval = 0;
int CityManagerImplementation::newCityGracePeriod = 0;
uint64 CityManagerImplementation::citySpecializationCooldown = 0;
int CityManagerImplementation::cityVotingDuration = 0;
uint64 CityManagerImplementation::treasuryWithdrawalCooldown = 0;

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
					Vector<byte> table;

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

	//Only load the static values on the first zone.
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
	ManagedReference<CityRegion*> city = new CityRegion();
	ObjectManager::instance()->persistObject(city, 1, "cityregions");
	city->setCustomRegionName(cityName);
	city->setZone(mayor->getZone());
	city->setCityRank(OUTPOST);
	city->setMayorID(mayor->getObjectID());
	city->addRegion(x, y, radiusPerRank.get(OUTPOST - 1), true);
	city->rescheduleUpdateEvent(newCityGracePeriod * 60); //Minutes

	//TODO: Send email to mayor.

	cities.put(cityName, city);

	return city;
}


bool CityManagerImplementation::validateCityName(const String& name) {
	if (cities.contains(name))
		return false;

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

	ManagedReference<SceneObject*> mayor = zoneServer->getObject(city->getMayorID());

	list->addMenuItem("@city/city:name_prompt " + city->getRegionName()); //Name:

	if (mayor != NULL)
		list->addMenuItem("@city/city:mayor_prompt " + mayor->getDisplayedName()); //Mayor:

	StringBuffer location;
	location << city->getPositionX() << " " << city->getPositionY();

	list->addMenuItem("@city/city:location_prompt " + location.toString()); //Location:
	list->addMenuItem("@city/city:radius_prompt " + String::valueOf(city->getRadius())); //Radius:
	list->addMenuItem("@city/city:reg_citizen_prompt " + String::valueOf(city->getCitizenCount())); //Registered Citizens:
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
	transfer->setCallback(new CityTreasuryDepositSuiCallback(zoneServer, city));

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

	CitizenList* citizenList = city->getCitizenList();

	for (int i = 0; i < citizenList->size(); ++i) {
		ManagedReference<SceneObject*> citizen = zoneServer->getObject(citizenList->get(i));

		if (citizen != NULL) {
			String name = citizen->getDisplayedName();

			if (city->isMilitiaMember(citizen->getObjectID()))
				name += " (Militia)";

			listbox->addMenuItem(name);
		}
	}

	ghost->addSuiBox(listbox);
	creature->sendMessage(listbox->generateMessage());
}

void CityManagerImplementation::processCityUpdate(CityRegion* city) {
	info("Processing city update: " + city->getRegionName());

	int cityRank;
	float radius;

	//TODO: fix this
	try {
		cityRank = city->getCityRank();

		if (cityRank == CLIENT)
			return; //It's a client region.

		radius = city->getRadius();
	} catch (Exception& e) {
		error(e.getMessage() + "in CityManagerImplementation::processCityUpdate");

		return;
	}

	int citizens = city->getCitizenCount();

	if (cityRank - 1 >= citizensPerRank.size() || cityRank >= citizensPerRank.size())
		return;

	int maintainCitizens = citizensPerRank.get(cityRank - 1);
	int advanceCitizens = citizensPerRank.get(cityRank);

	//System::out << "maintainCitizens: " << maintainCitizens << endl;
	//System::out << "advanceCitizens: " << advanceCitizens << endl;

	if (citizens < maintainCitizens) {
		contractCity(city);
	} else if (citizens >= advanceCitizens) {
		expandCity(city);
	}

	city->rescheduleUpdateEvent(cityUpdateInterval * 60);

	//TODO: Taxation
	//TODO: Deduct Maintenance
	//TODO: Election
	//TODO: Set next update cycle.
}

void CityManagerImplementation::contractCity(CityRegion* city) {
	uint8 newRank = city->getCityRank() - 1;

	if (newRank == CLIENT) {
		destroyCity(city);
		return;
	}

	ManagedReference<SceneObject*> obj = zoneServer->getObject(city->getMayorID());

	if (obj != NULL && obj->isCreatureObject()) {
		CreatureObject* mayor = cast<CreatureObject*>(obj.get());

		//Send out contraction mail.
		StringIdChatParameter params("city/city", "city_contract_body");
		params.setTO(city->getRegionName());
		params.setDI(newRank);

		UnicodeString subject = "@city/city:city_contract_subject";

		if (newRank == OUTPOST) {
			params.setStringId("city/city", "city_invalid_body");
			subject = "@city/city:city_invalid_subject";
		}

		ChatManager* chatManager = zoneServer->getChatManager();
		chatManager->sendMail("@city/city:new_city_from", subject, params, mayor->getFirstName(), NULL);
	}

	//TODO: Destroy civic structures.
	//TODO: Remove citizens outside city limits.

	city->setCityRank(newRank);
	city->setRadius(radiusPerRank.get(newRank - 1));
}

void CityManagerImplementation::expandCity(CityRegion* city) {
	uint8 currentRank = city->getCityRank();
	uint8 newRank = city->getCityRank() + 1;

	ManagedReference<SceneObject*> obj = zoneServer->getObject(city->getMayorID());

	if (obj != NULL && obj->isCreatureObject()) {
		CreatureObject* mayor = cast<CreatureObject*>(obj.get());

		//Send out expansion mail.
		StringIdChatParameter params("city/city", "city_expand_body");
		params.setTO(city->getRegionName());
		params.setDI(newRank);

		UnicodeString subject = "@city/city:city_expand_subject";

		if (currentRank == METROPOLIS) {
			params.setStringId("city/city", "city_expand_cap_body"); //Capped
			params.setDI(currentRank);

			subject = "@city/city:city_expand_cap_subject";
		}

		ChatManager* chatManager = zoneServer->getChatManager();
		chatManager->sendMail("@city/city:new_city_from", subject, params, mayor->getFirstName(), NULL);
	}

	if (currentRank == METROPOLIS)
		return;

	//TODO: Add new citizens within limits.

	city->setCityRank(newRank);
	city->setRadius(radiusPerRank.get(newRank - 1));
}

void CityManagerImplementation::destroyCity(CityRegion* city) {
	ManagedReference<SceneObject*> obj = zoneServer->getObject(city->getMayorID());

	if (obj != NULL && obj->isCreatureObject()) {
		CreatureObject* mayor = cast<CreatureObject*>(obj.get());

		//Send out contraction mail.
		StringIdChatParameter params("city/city", "new_city_fail_body");

		ChatManager* chatManager = zoneServer->getChatManager();
		chatManager->sendMail("@city/city:new_city_from", "@city/city:new_city_fail_subject", params, mayor->getFirstName(), NULL);
	}

	city->destroyActiveAreas();

	ManagedReference<StructureObject*> cityhall = city->getCityHall();

	if (cityhall != NULL) {
		cityhall->destroyObjectFromWorld(false);
		cityhall->destroyObjectFromDatabase(true);
	}

	//TODO: Destroy civic structures.
}

void CityManagerImplementation::registerCitizen(CityRegion* city, CreatureObject* creature) {
	ChatManager* chatManager = zoneServer->getChatManager();

	ManagedReference<SceneObject*> mayor = zoneServer->getObject(city->getMayorID());

	if (mayor != NULL && mayor->isCreatureObject()) {
		CreatureObject* mayorCreature = cast<CreatureObject*>(mayor.get());

		StringIdChatParameter params("city/city", "new_city_citizen_body");
		params.setTO(creature->getDisplayedName());
		chatManager->sendMail("@city/city:new_city_from", "@city/city:new_city_citizen_subject", params, mayorCreature->getFirstName(), NULL);

		params.setStringId("city/city", "new_city_citizen_other_body");
		params.setTU(city->getRegionName());
		params.setTT(mayorCreature->getDisplayedName());

		chatManager->sendMail("@city/city:new_city_from", "@city/city:new_city_citizen_other_subject", params, creature->getFirstName(), NULL);

	}

	city->addCitizen(creature->getObjectID());
}

void CityManagerImplementation::unregisterCitizen(CityRegion* city, CreatureObject* creature, bool inactive) {
	ChatManager* chatManager = zoneServer->getChatManager();

	ManagedReference<SceneObject*> mayor = zoneServer->getObject(city->getMayorID());

	if (mayor != NULL && mayor->isCreatureObject()) {
		CreatureObject* mayorCreature = cast<CreatureObject*>(mayor.get());

		StringIdChatParameter params("city/city", "lost_citizen_body"); //A citizen has left your city by using the revoke option on the city terminal. Citizen Name: %TO
		params.setTO(creature->getDisplayedName());

		UnicodeString subject = "@city/city:lost_citizen_subject";

		if (inactive) {
			params.setStringId("city/city", "lost_inactive_citizen_body"); //A citizen has been removed due to six weeks inactivity.  If they return, they can rejoin the city by redeclaring at their residence.
			subject = "@city/city:lost_inactive_citizen_subject"; //Lost Inactive Citizen!
		}

		chatManager->sendMail("@city/city:new_city_from", subject, params, mayorCreature->getFirstName(), NULL);
	}

	city->removeCitizen(creature->getObjectID());

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

	if (obj == NULL || !obj->isCreatureObject() || !obj->isInRange(mayor, 16.f)) {
		mayor->sendSystemMessage("@city/city:cannot_find_citizen"); //Unable to find that citizen.
		return;
	}

	CreatureObject* creature = cast<CreatureObject*>(obj.get());
	creature->sendSystemMessage("@city/city:added_militia_target"); //You have been added to the city militia.

	mayor->sendSystemMessage("@city/city:added_militia"); //The player has been successfully added to the city militia.

	city->addMilitiaMember(militiaid);
}

void CityManagerImplementation::removeMilitiaMember(CityRegion* city, CreatureObject* mayor, uint64 militiaid) {
	if (!city->isMayor(mayor->getObjectID()))
		return;

	ManagedReference<SceneObject*> obj = zoneServer->getObject(militiaid);

	if (obj != NULL && obj->isCreatureObject()) {
		CreatureObject* creature = cast<CreatureObject*>(obj.get());
		creature->sendSystemMessage("@city/city:removed_militia_target"); //You have been removed from the city militia.
	}

	mayor->sendSystemMessage("@city/city:removed_militia"); //The player has been successfully removed from the city militia.

	city->removeMilitiaMember(militiaid);
}

void CityManagerImplementation::sendTreasuryReport(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	//@city/city:treasury_balance_t
	ManagedReference<SuiListBox*> listbox = new SuiListBox(creature, SuiWindowType::CITY_TREASURY_REPORT);
	listbox->setPromptTitle("@city/city:treasury_balance_t"); //Treasury Balance
	listbox->setPromptText("@city/city:treasury_balance_d"); //A report on the current treasury follows.
	listbox->setUsingObject(terminal);
	listbox->setForceCloseDistance(16.f);

	listbox->addMenuItem("@city/city:treasury " + String::valueOf(city->getCityTreasury()));

	creature->sendMessage(listbox->generateMessage());
}

void CityManagerImplementation::sendCityAdvancement(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	ManagedReference<SuiListBox*> listbox = new SuiListBox(creature, SuiWindowType::CITY_ADVANCEMENT);
	listbox->setPromptTitle("@city/city:rank_info_t"); //City Rank Info
	listbox->setPromptText("@city/city:rank_info_d"); //The following report shows the current city rank, the current city population, the abilities of the city and the population required for the next rank.  If you have met your rank requirement, the city will advance in rank during the next city update.  Check the maintenance report for a projected time to the next update.
	listbox->setUsingObject(terminal);
	listbox->setForceCloseDistance(16.f);

	//City Abilities:
	//bank Bank
	//cantina  Cantina

	int rank = city->getCityRank();

	if (rank - 1 >= citizensPerRank.size() || rank >= citizensPerRank.size())
		return;

	int currentRank = citizensPerRank.get(rank - 1);
	int nextRank = citizensPerRank.get(rank);

	//pop_req_current_rankPop. Req. for Current Rank:
	//pop_req_next_rankPop. Req. for Next Rank:
	listbox->addMenuItem("@city/city:city_rank_prompt @city/city:rank" + String::valueOf(rank));
	listbox->addMenuItem("@city/city:reg_citizen_prompt " + String::valueOf(city->getCitizenCount()));
	listbox->addMenuItem("@city/city:pop_req_current_rank " + String::valueOf(currentRank));
	listbox->addMenuItem("@city/city:pop_req_next_rank " + String::valueOf(nextRank));

	creature->sendMessage(listbox->generateMessage());
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
	aa->getZone()->registerObjectWithPlanetaryMap(aa);

	mayor->sendSystemMessage("@city/city:registered"); //Your city is now registered on the planetary map. All civic and major commercial structures in the city are also registered and can be found with the /find command.

	//TODO: Register all city structures in city.
}

void CityManagerImplementation::unregisterCity(CityRegion* city, CreatureObject* mayor) {
	city->setRegistered(false);

	ManagedReference<Region*> aa = city->getRegion(0);
	aa->getZone()->unregisterObjectWithPlanetaryMap(aa);
	aa->setPlanetMapCategory(NULL);

	mayor->sendSystemMessage("@city/city:unregistered"); //Your city is no longer registered on the planetary map.

	//TODO: Unregister all city structures in city.
}

void CityManagerImplementation::promptAdjustTaxes(CityRegion* city, CreatureObject* mayor, SceneObject* terminal) {
	//adjust_taxes_t Adjust Taxes
	//adjust_taxes_d Select the tax you wish to adjust from the list below.
	//cant_tax You lack the knowledge to manage the city's taxes.
	//manage_taxes
}

void CityManagerImplementation::sendMaintenanceReport(CityRegion* city, CreatureObject* creature, SceneObject* terminal) {
	//TODO: Encapsulate this, and clean up.
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

	StringIdChatParameter params("city/city", "city_update_eta"); //Next City Update: %TO
	params.setTO(updateStr);

	creature->sendSystemMessage(params);
}

bool CityManagerImplementation::isCityInRange(Zone* zone, float x, float y) {
	return true;
}
