/*
 * WeatherManagerImplementation.cpp
 *
 *  Created on: 11/03/2011
 *      Author: Anakis
 */

#include "engine/engine.h"

#include "WeatherManager.h"
#include "server/zone/Zone.h"
#include "server/chat/ChatManager.h"
#include "events/WeatherChangeEvent.h"
#include "server/zone/managers/player/PlayerMap.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/creature/CreaturePosture.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "weathermaps/WeatherMap.h"
#include "server/zone/packets/scene/ServerWeatherMessage.h"


void WeatherManagerImplementation::initialize() {
	//Customize the Manager's name.
	String managerName = "WeatherManager ";
	setLoggingName(managerName + zone->getZoneName());
	setGlobalLogging(true);
	setLogging(true);

	weatherEnabled = true;
	weatherChangeEvent = NULL;

	//Load weather configuration from the luas.
	//info("Loading configuration from Lua.");
	if(!loadLuaConfig()) {
		info("ERROR in Lua config. Loading default values.");
		loadDefaultValues();
	}

	windX.removeAll();
	windY.removeAll();
	windMagnitude.removeAll();

	for(int i = 0; i <= 200; ++i) {
		windX.add(((float)System::random(200) / 100.f) - 1);
		windY.add(((float)System::random(200) / 100.f) - 1);
		windMagnitude.add(((float)System::random(200) / 100.f) - 1);
	}

	createNewWeatherPattern();

	 info("Enabled");
}

bool WeatherManagerImplementation::loadLuaConfig() {
	Locker weatherManagerLocker(_this.get());

	Lua* lua = new Lua();
	lua->init();

	if (!lua->runFile("scripts/managers/weather_manager.lua"))
		return false;

	LuaObject luaObject = lua->getGlobalObject(zone->getZoneName());

	if (!luaObject.isValidTable())
		return false;

	//Starting weather
	baseWeather = luaObject.getByteField("defaultWeather");

	//New weather selection times.
	averageWeatherDuration = luaObject.getIntField("averageWeatherDuration");

	//Weather Stability.
	weatherStability = luaObject.getIntField("weatherStability");
	if(weatherStability > 100)
		weatherStability = 100;

	hasDamagingSandstorms = luaObject.getByteField("hasDamagingSandstorms");

	if(hasDamagingSandstorms) {

		sandstormDamage = luaObject.getIntField("sandstormDamage");
		if (sandstormDamage > 500)
			return false;
	}

	luaObject.pop();
	delete lua;
	lua = NULL;
	return true;
}


void WeatherManagerImplementation::loadDefaultValues() {
	Locker weatherManagerLocker(_this.get());

	weatherEnabled = true;

	baseWeather = 0;
	//Transition times.
	averageWeatherDuration = 3600; //seconds. 1 hour
	weatherStability = 80; // Pretty Stable

	hasDamagingSandstorms = false;
}

void WeatherManagerImplementation::createNewWeatherPattern() {

	Locker weatherManagerLocker(_this.get());

	int roll = System::random(100);

	for(int i = 0; i < 5; ++i) {
		float value = ((float)weatherStability + (i * ((100.f - (float)weatherStability) / (1.f + i))));
		value += (100.f - ((float)weatherStability + (4 * ((100.f - (float)weatherStability) / (5.f)))));

		if(roll <  value) {
			baseWeather = i;
			break;
		}
	}

	int duration = System::random(averageWeatherDuration) + (averageWeatherDuration / 2);
	currentMap = new WeatherMap(weatherStability, zone->getMinX(), zone->getMaxX(), zone->getMinY(), zone->getMaxY(), duration);

	if(weatherChangeEvent != NULL) {
		if(weatherChangeEvent->isScheduled())
			weatherChangeEvent->cancel();
	} else {
		weatherChangeEvent = new WeatherChangeEvent(_this.get());
	}

	weatherChangeEvent->reschedule((duration * 1.5) * 1000);
}

void WeatherManagerImplementation::sendWeatherTo(CreatureObject* player) {

	byte currentWeather = 0;

	if(currentMap != NULL)
		currentWeather = currentMap->getWeatherAt(player->getPositionX(), player->getPositionY()) + baseWeather;
	else
		currentWeather = baseWeather;

	if(currentWeather > 4)
		currentWeather = 0;

	if(hasDamagingSandstorms && currentWeather == WeatherManager::EXTREMESTORM) {
		applySandstormDamage(player);
	}

	if(player->getCurrentWeather() == currentWeather)
		return;

	if(hasDamagingSandstorms && player->getCurrentWeather() == WeatherManager::EXTREMESTORM) {
		player->sendSystemMessage("The storm has subsided.");
	}

	player->setCurrentWeather(currentWeather);

	if(hasDamagingSandstorms && currentWeather == WeatherManager::EXTREMESTORM) {
		player->sendSystemMessage("The weather around you quickly becomes damaging, seek shelter immediately.");
	}

	ServerWeatherMessage* weatherMessage = new ServerWeatherMessage(
			currentWeather,
			windX.get(player->getCurrentWind()),
			windMagnitude.get(player->getCurrentWind()),
			windY.get(player->getCurrentWind()));

	player->sendMessage(weatherMessage);

}

void WeatherManagerImplementation::applySandstormDamage(CreatureObject* player) {
	if (player == NULL)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	//Check player's online status.
	if (ghost->isTeleporting() || !player->isOnline())
		return;

	//Check if player is in a shelter.
	if ((!player->isMounted() && player->getParentID() != 0) || player->getCurrentCamp() != NULL) //TODO: Add camp protection.
		return;

	//Blind player
	player->setBlindedState(60);

	//Calculate the sandstorm protection the player has.
	int totalCoverings = calculateSandstormProtection(player);

	//Apply wounds.
	int applicableDamage = sandstormDamage - totalCoverings;
	if (applicableDamage > 0) {
		player->inflictDamage(NULL, CreatureAttribute::HEALTH, applicableDamage, true, true);
		player->inflictDamage(NULL, CreatureAttribute::ACTION, applicableDamage, true, true);
		player->inflictDamage(NULL, CreatureAttribute::MIND, applicableDamage, true, true);
	}

	//Apply knockdown.
	int applicableKDChance = sandstormDamage - totalCoverings;
	if (applicableKDChance > 0 && !player->isProne() && !player->isKnockedDown() && System::random(200) > 198 ) {
		if (player->isMounted()) {
			player->sendSystemMessage("A gust of wind blows you off your vehicle!");
			player->dismount();
		} else
			player->sendSystemMessage("A gust of wind blows you off balance!");

		player->setPosture(CreaturePosture::KNOCKEDDOWN, true);
	}
}


int WeatherManagerImplementation::calculateSandstormProtection(CreatureObject* player) {
	if (player == NULL)
		return 0;

	int protection = 0;
	uint32 crc;

	//Check for protective head gear.
	ManagedReference<SceneObject*> hat = player->getSlottedObject("hat");
	if (hat != NULL) {
		crc = hat->getServerObjectCRC();
		if (crc == 0x612f992f || crc == 0xba3831b8 || crc == 0xdc8d2e72 || crc == 0x754b6f93) //Tusken Raider helmets, Swoop helmet, Large Headwrap.
			protection += 1;
		else if (hat->isArmorObject())
			protection += 1;
	}

	//Check for protective chest covering.
	bool tuskenRobe = false;
	ManagedReference<SceneObject*> robe = player->getSlottedObject("chest2");
	if (robe != NULL) {
		crc = robe->getServerObjectCRC();
		if (crc == 0xc20d81d9 || crc == 0x191a294e) { //Tusken Robes.
			tuskenRobe = true;
			protection += 2; //They cover both chest and legs.
		} else if (crc == 0xd95ec143 || crc == 0x3995e72f) //Scout Jacket, Heavy Reinforced Jacket.
			protection += 1;
		else if (crc == 0x9053a6ce || crc == 0x663c19d1) //Vested jacket, Desert Command Jacket.
			protection += 1;
		else if (robe->isArmorObject())
			protection += 1;
	}

	//Check for protective pants.
	if (!tuskenRobe) {
		ManagedReference<SceneObject*> pants = player->getSlottedObject("pants1");
		if (pants != NULL) {
			crc = pants->getServerObjectCRC();
			if (crc == 0x9488cb5f || crc == 0x10369d36 || crc == 0x9c6cabd4) //Paramilitary Camos, Basic Camos, Reinforced Pants.
				protection += 1;
			else if (crc == 0xb9f0dcd7 || crc == 0xc6ada1aa) //Desert Crawlers, Padded Workpants
				protection += 1;
		}

		ManagedReference<SceneObject*> pants2 = player->getSlottedObject("pants2");
		if (pants2 != NULL) {
			crc = pants2->getServerObjectCRC();
			if (pants2->isArmorObject())
				protection += 1;
		}
	}

	//Check for protective gloves.
	ManagedReference<SceneObject*> gloves = player->getSlottedObject("gloves");
	if (gloves != NULL) {
		crc = gloves->getServerObjectCRC();
		if (crc == 0x29fc844 || crc == 0x41ba6c29 || crc == 0x614eefaa) //Tusken gloves, Link-Steel Reinforced Gloves, Heavy Gloves.
			protection += 1;
		else if (gloves->isArmorObject())
			protection += 1;
	}

	//Check for protective boots.
	ManagedReference<SceneObject*> boots = player->getSlottedObject("shoes");
	if (boots != NULL) {
		crc = boots->getServerObjectCRC();
		if (crc == 0xbcc9eaac || crc == 0x873644ed) //Tusken boots, Sturdy boots
			protection += 1;
		else if (crc == 0x9192dd9e || crc == 0x35d80874) //Paneled Boots, Wrapped Boots.
			protection += 1;
		else if (boots->isArmorObject())
			protection += 1;
	}

	return protection;
}


void WeatherManagerImplementation::enableWeather(CreatureObject* player) {

	initialize();

	if (player != NULL)
		player->sendSystemMessage("The weather on this planet will now change automatically.");
}


void WeatherManagerImplementation::disableWeather(CreatureObject* player) {

	if (player == NULL || !weatherEnabled)
		return;

	Locker weatherManagerLocker(_this.get());
	weatherEnabled = false;

	if (weatherChangeEvent != NULL) {
		if (weatherChangeEvent->isScheduled())
			weatherChangeEvent->cancel();

		weatherChangeEvent = NULL;
	}

	currentMap = NULL;

	player->sendSystemMessage("The weather on this planet will no longer change automatically.");
}


void WeatherManagerImplementation::changeWeather(CreatureObject* player, int newWeather) {

	disableWeather(player);

	Locker weatherManagerLocker(_this.get());

	if(newWeather == 5)
		baseWeather = System::random(5);
	else {
		baseWeather = newWeather;
	}
}

void WeatherManagerImplementation::printInfo(CreatureObject* player) {

	if(currentMap == NULL) {
		player->sendSystemMessage("The weather currently is " + String::valueOf(baseWeather));
		return;
	}

	StringBuffer message;
	message << "Base: " << baseWeather << " " << currentMap->printInfo(player->getPositionX(), player->getPositionY());
	player->sendSystemMessage(message.toString());
}
