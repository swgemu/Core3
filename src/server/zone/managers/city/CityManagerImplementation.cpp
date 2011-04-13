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
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/building/city/CityHallObject.h"
#include "server/zone/objects/region/Region.h"

Vector<uint8> CityManagerImplementation::citizensPerRank;
Vector<uint16> CityManagerImplementation::radiusPerRank;
int CityManagerImplementation::cityUpdateInterval = 0;
int CityManagerImplementation::newCityGracePeriod = 0;

void CityManagerImplementation::loadLuaConfig() {
	info("Loading config file.", true);

	String terrainName = zone->getTerrainName();

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/city_manager.lua");

	/*
	 * TODO: Refactor this to use terrainName

	LuaObject luaObject = lua->getGlobalObject("CitiesAllowed");

	if (luaObject.isValidTable()) {
		lua_State* L = luaObject.getLuaState();
		lua_rawgeti(L, -1, zoneid+1);
		LuaObject a(L);

		for (int i = 1; i <= a.getTableSize(); ++i)
			citiesAllowedPerRank.add(a.getIntAt(i));

		a.pop();
	}

	luaObject.pop();

	//Only load the static values on the first zone.
	if (zoneid == 0) {
		cityUpdateInterval = lua->getGlobalInt("CityUpdateInterval");
		newCityGracePeriod = lua->getGlobalInt("NewCityGracePeriod");

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
	}

	*/

	delete lua;
	lua = NULL;
}

void CityManagerImplementation::createNewCity(CityHallObject* city, PlayerCreature* player, const String& name) {
	city->setCityName(name);

	city->setMayorObjectID(player->getObjectID());

	player->setDeclaredResidence(city);
	declareCitizenship(city, player, false);

	city->rescheduleCityUpdate(newCityGracePeriod);

	//Create the city region
	uint32 crc = String("object/region_area.iff").hashCode();

	Region* cityRegion = (Region*) ObjectManager::instance()->createObject(crc, 2, "cityregions");
	city->setCityRegion(cityRegion);
	cityRegion->initializePosition(city->getPositionX(), 0, city->getPositionY());
	cityRegion->setRadius(radiusPerRank.get(NEWCITY));
	cityRegion->setCityHall(city);

	StringId* objectName = cityRegion->getObjectName();
	objectName->setCustomString(name);

	cityRegion->insertToZone(zone);

	cityRegion->updateToDatabase();
	city->updateToDatabaseWithoutChildren();

	zone->getPlanetManager()->addRegion(cityRegion);

	Locker lock(_this);

	cities.put(city->getObjectID(), city);

	//New city established email.
	UnicodeString subject = "@city/city:new_city_subject"; //New City Established!

	StringIdChatParameter emailBody;
	emailBody.setStringId("@city/city:new_city_body"); //Congratulations, you have successfully established a new outpost on the frontier!...
	emailBody.setTO(player->getObjectName());

	sendMailToMayor(city, "@city/city:new_city_from", subject, emailBody);
}

void CityManagerImplementation::changeCityName(CityHallObject* city, PlayerCreature* player, const String& name) {
	city->setCityName(name);

	ManagedReference<Region*> cityRegion = city->getCityRegion();

	if (cityRegion != NULL) {
		StringId* objectName = cityRegion->getObjectName();
		objectName->setCustomString(name);

		cityRegion->updateToDatabase();
	}

	city->updateToDatabaseWithoutChildren();

	player->sendSystemMessage("@city/city:name_changed"); //The city name has been successfully changed.

	//TODO: Send email to citizens about name change.
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

void CityManagerImplementation::sendMailToMayor(CityHallObject* city, const String& sendername, const UnicodeString& subject, StringIdChatParameter& body) {
	ZoneServer* zoneServer = zone->getZoneServer();

	ManagedReference<ChatManager*> chatManager = zoneServer->getChatManager();

	if (chatManager == NULL)
		return;

	uint64 mayorID = city->getMayorObjectID();

	ManagedReference<SceneObject*> obj = zoneServer->getObject(mayorID);

	if (obj == NULL || !obj->isPlayerCreature())
		return;

	PlayerCreature* mayor = (PlayerCreature*) obj.get();

	chatManager->sendMail(sendername, subject, body, mayor->getFirstName());
}

void CityManagerImplementation::sendMailToAllCitizens(CityHallObject* city, const String& sendername, const UnicodeString& subject, StringIdChatParameter& body) {
	ZoneServer* zoneServer = zone->getZoneServer();

	ManagedReference<ChatManager*> chatManager = zoneServer->getChatManager();

	if (chatManager == NULL)
		return;

	for (int i = 0; i < city->getCitizenCount(); ++i) {
		uint64 objid = city->getCitizenObjectID(i);
		ManagedReference<SceneObject*> obj = zoneServer->getObject(objid);

		if (obj == NULL || !obj->isPlayerCreature())
			continue;

		PlayerCreature* player = (PlayerCreature*) obj.get();

		Locker _lock(player);

		chatManager->sendMail(sendername, subject, body, player->getFirstName());
	}
}

void CityManagerImplementation::handleCityAdvancement(CityHallObject* city) {
	if (!city->isCityUpdatePast())
		return;

	city->rescheduleCityUpdate(cityUpdateInterval);

	uint8 oldRank = city->getCityRank();

	//Can't advance past Metropolis.
	if (oldRank == METROPOLIS)
		return;

	int citizens = city->getCitizenCount();

	uint8 thisRankCitizensReq = citizensPerRank.get(oldRank);
	uint8 nextRankCitizensReq = citizensPerRank.get(oldRank + 1);

	if (citizens < thisRankCitizensReq)
		contractCity(city);
	else if (citizens >= nextRankCitizensReq)
		expandCity(city);
}

void CityManagerImplementation::contractCity(CityHallObject* city) {
	uint8 cityRank = city->getCityRank();

	if (cityRank == NEWCITY) {
		UnicodeString subject = "@city/city:new_city_fail_subject"; //Zoning Permits Rejected!

		StringIdChatParameter mail;
		mail.setStringId("@city/city:new_city_fail_body"); //We are sorry to inform you that your city failed to receive sufficient interest to remain solvent.  Your zoning applications have been rejected and your city hall has been removed.

		sendMailToMayor(city, "@city/city:new_city_from", subject, mail);

		destroyCity(city);
		return;
	}

	--cityRank;

	//TODO: Zoning Permits Invalid if below 10 citizens (but itll still be an outpost?)

	ManagedReference<Region*> region = city->getCityRegion();

	if (region == NULL)
		return;

	region->setRadius(radiusPerRank.get(cityRank));
	city->setCityRank(cityRank);

	region->updateToDatabase();
	city->updateToDatabaseWithoutChildren();

	UnicodeString subject = "@city/city:city_contract_subject"; //City Contraction!

	StringIdChatParameter mail;
	mail.setStringId("@city/city:city_contract_body"); //The city of %TO has expanded to rank %DI!  New abilities for your city have been unlocked.  Please check the city advancement report for details.
	mail.setTO(city->getCityName());
	mail.setDI(cityRank);

	sendMailToMayor(city, "@city/city:new_city_from", subject, mail);
}

void CityManagerImplementation::expandCity(CityHallObject* city) {
	uint8 cityRank = city->getCityRank();

	//Don't allow expansion beyond metropolis.
	if (cityRank == METROPOLIS)
		return;

	++cityRank;

	//Check to see that the max number of cities of the next level hasn't been reached.
	if (checkCitiesCappedAtRank(cityRank)) {
		UnicodeString subject = "@city/city:city_expand_cap_subject"; //City Expansion Capped!

		StringIdChatParameter mail;
		mail.setStringId("@city/city:city_expand_cap_body"); //Unfortunately, we must deny your rank and land expansion request as there are too many large cities already on the planet.
		mail.setTO(city->getCityName());
		mail.setDI(cityRank);

		sendMailToMayor(city, "@city/city:new_city_from", subject, mail);
		return;
	}

	ManagedReference<Region*> region = city->getCityRegion();

	if (region == NULL)
		return;

	region->setRadius(radiusPerRank.get(cityRank));
	city->setCityRank(cityRank);

	region->updateToDatabase();
	city->updateToDatabaseWithoutChildren();

	if (cityRank == OUTPOST) {
		UnicodeString subject = "@city/city:new_city_success_subject"; //New City Approved!

		StringIdChatParameter mail;
		mail.setStringId("@city/city:new_city_success_body"); //Congratulations!  The Planetary Civic Authority has approved your city's zoning permits!  Your city is valid and will begin to grow as citizens join it.

		sendMailToMayor(city, "@city/city:new_city_from", subject, mail);
	} else {
		UnicodeString subject = "@city/city:city_expand_subject"; //City Expansion!

		StringIdChatParameter mail;
		mail.setStringId("@city/city:city_expand_body"); //The city of %TO has expanded to rank %DI!  New abilities for your city have been unlocked.  Please check the city advancement report for details.
		mail.setTO(city->getCityName());
		mail.setDI(cityRank);

		sendMailToMayor(city, "@city/city:new_city_from", subject, mail);
	}
}

void CityManagerImplementation::destroyCity(CityHallObject* city) {
	//Delete all the civic structures...
	//Remove the city region
	//Remove the city hall
	//Set the mayors residence = NULL
	//Send out mails?

	Locker lock(_this);
	cities.drop(city->getObjectID());
	city->destroyObjectFromDatabase(true);
}


void CityManagerImplementation::declareCitizenship(CityHallObject* city, PlayerCreature* player, bool sendMail) {
	uint64 playerID = player->getObjectID();

	if (city->isCitizen(playerID))
		return;

	city->addCitizen(playerID);

	city->updateToDatabaseWithoutChildren();

	if (!sendMail)
		return;

	//Send out email
	ZoneServer* zoneServer = zone->getZoneServer();

	ManagedReference<ChatManager*> chatManager = zoneServer->getChatManager();

	if (chatManager == NULL)
		return;

	ManagedReference<SceneObject*> obj = zoneServer->getObject(city->getMayorObjectID());

	if (obj == NULL || !obj->isPlayerCreature())
		return;

	PlayerCreature* mayor = (PlayerCreature*) obj.get();

	String mayorName = mayor->getObjectName()->getDisplayedName();

	//Send email to the citizen declaring citizenship
	StringIdChatParameter email;
	UnicodeString subject = "@city/city:new_city_citizen_other_subject"; //Welcome, Citizen!
	email.setStringId("@city/city:new_city_citizen_other_body"); //Welcome to %TU, citizen!
	email.setTU(city->getCityName());
	email.setTT(mayorName);

	chatManager->sendMail(mayorName, subject, email, player->getFirstName());

	email.clear();

	//Send email to the mayor
	subject = "@city/city:new_city_citizen_subject"; //City Growth: Added Citizen
	email.setStringId("@city/city:new_city_citizen_body"); //A new citizen has joined your city.
	email.setTO(player->getObjectName()->getDisplayedName());

	sendMailToMayor(city, "@city/city:new_city_from", subject, email);
}

void CityManagerImplementation::revokeCitizenship(CityHallObject* city, PlayerCreature* player, bool sendMail) {
	uint64 playerID = player->getObjectID();

	if (!city->isCitizen(playerID))
		return;

	city->removeCitizen(playerID);

	city->updateToDatabaseWithoutChildren();

	if (!sendMail)
		return;

	//Send email to the mayor
	StringIdChatParameter email;
	UnicodeString subject = "@city/city:lost_city_citizen_subject"; //Lost Citizen!
	email.setStringId("@city/city:lost_city_citizen_body"); //A citizen has left your city.
	email.setTO(player->getObjectName()->getDisplayedName());

	sendMailToMayor(city, "@city/city:new_city_from", subject, email);
}

bool CityManagerImplementation::checkCitiesCappedAtRank(uint8 rank) {
	int totalCitiesAtRank = 0;

	Locker lock(_this);

	for (int i = 0; i < cities.size(); ++i) {
		ManagedReference<CityHallObject*> city = cities.get(i);

		if (city != NULL && city->getCityRank() == rank)
			++totalCitiesAtRank;
	}

	return getCitiesAllowed(rank) <= totalCitiesAtRank;
}

void CityManagerImplementation::addMilitiaMember(CityHallObject* city, PlayerCreature* player, const String& citizenName) {
	if (!city->isMayor(player->getObjectID())) {
		//Only the mayor can manage the militia.
		return;
	}

	if (!player->hasSkillBox("social_politician_martial_01")) {
		player->sendSystemMessage("@city/city:cant_militia"); //You lack the skill to manage the city militia.
		return;
	}

	ManagedReference<PlayerManager*> playerManager = zone->getZoneServer()->getPlayerManager();

	if (playerManager == NULL)
		return;

	ManagedReference<PlayerCreature*> citizen = playerManager->getPlayer(citizenName);

	if (citizen == NULL)
		return;

	Locker _lock(citizen);

	if (!city->isCitizen(citizen->getObjectID())) {
		player->sendSystemMessage("@city/city:not_citizen"); //That player must be a citizen to join the city militia.
		return;
	}

	if (!citizen->isOnline() || !citizen->isInRange(player, 32))
		return;

	//Citizen is eligible to be militia
	city->addMilitiaMember(citizen->getObjectID()); //Add them to the milita list.

	player->sendSystemMessage("@city/city:added_militia"); //The player has been successfully added to the city militia.
	citizen->sendSystemMessage("@city/city:added_militia_target"); //You have been added to the city militia.

	city->updateToDatabaseWithoutChildren();
}

void CityManagerImplementation::removeMilitiaMember(CityHallObject* city, PlayerCreature* player, uint64 playerID) {
	if (!city->isMayor(player->getObjectID())) {
		//Only the mayor can manage the militia.
		return;
	}

	if (!player->hasSkillBox("social_politician_martial_01")) {
		player->sendSystemMessage("@city/city:cant_militia"); //You lack the skill to manage the city militia.
		return;
	}

	if (!city->isMilitiaMember(playerID))
		return;

	//Citizen is eligible to be removed from the militia
	city->removeMilitiaMember(playerID); //Remove them from the milita list.

	city->updateToDatabaseWithoutChildren();

	player->sendSystemMessage("@city/city:removed_militia"); //The player has been successfully removed from the city militia.

	ManagedReference<SceneObject*> obj = zone->getZoneServer()->getObject(playerID);

	if (obj == NULL || !obj->isPlayerCreature())
		return;

	PlayerCreature* citizen = (PlayerCreature*) obj.get();

	if (citizen->isOnline())
		citizen->sendSystemMessage("@city/city:removed_militia_target"); //You have been removed from the city militia.
}
