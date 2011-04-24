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
#include "events/SandstormTickEvent.h"
#include "server/zone/managers/player/PlayerMap.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/creature/CreaturePosture.h"

#include "server/zone/packets/scene/ServerWeatherMessage.h"


void WeatherManagerImplementation::initialize() {
	//Customize the Manager's name.
	String managerName = "WeatherManager ";
	setLoggingName(managerName + zone->getZoneName());
	setGlobalLogging(true);
	setLogging(true);

	weatherChangeEvent = NULL;
	sandstormTickEvent = NULL;

	sandstormEffectsEnabled = false; //Default, because only Tat/Lok overwrite this from the lua.

	//Load weather configuration from the luas.
	info("Loading configuration from Lua.");
	if(!loadLuaConfig()) {
		info("ERROR in Lua config. Loading default values.");
		loadDefaultValues();
	} else
		info("Loading from Lua was successful.");

	//Randomize wind direction.
	windX = -1.0f + (float)System::random(2);
	windY = -1.0f + (float)System::random(2);
	changeWindDirection();

	//Initialize weather events.
	if (weatherEnabled) {
		weatherChangeEvent = new WeatherChangeEvent(_this);
		int time = newWeatherTimeMin + System::random(newWeatherTimeMax - newWeatherTimeMin);
		weatherChangeEvent->schedule(time * 1000);
	}

	if (sandstormEffectsEnabled) {
		sandstormTickEvent = new SandstormTickEvent(_this);
		sandstormTick(); //In case the starting weather is level 4.
	}
}


bool WeatherManagerImplementation::loadLuaConfig() {
	Locker weatherManagerLocker(_this);

	Lua* lua = new Lua();
	lua->init();

	if (!lua->runFile("scripts/managers/weather_manager.lua"))
		return false;

	LuaObject luaObject = lua->getGlobalObject(zone->getZoneName() + "_weather");

	if (!luaObject.isValidTable())
		return false;

	weatherEnabled = luaObject.getByteField("weatherEnabled");

	//Starting weather ID.
	int startingWeatherID = luaObject.getIntField("startingWeatherID");
	if (startingWeatherID == 5)
		weatherID = System::random(2);
	else if (startingWeatherID >= 0 && startingWeatherID < 5)
		weatherID = startingWeatherID;
	else
		return false;

	targetWeatherID = weatherID;

	//Weather ID odds.
	int total = 0;
	levelZeroChance = luaObject.getIntField("levelZeroChance");
	total += levelZeroChance;
	levelOneChance = luaObject.getIntField("levelOneChance");
	total += levelOneChance;
	levelTwoChance = luaObject.getIntField("levelTwoChance");
	total += levelTwoChance;
	levelThreeChance = luaObject.getIntField("levelThreeChance");
	total += levelThreeChance;
	levelFourChance = luaObject.getIntField("levelFourChance");
	total += levelFourChance;
	if (total != 100)
		return false;

	//Wind.
	windChangeChance = luaObject.getIntField("windChangeChance");
	if (windChangeChance > 100)
		return false;

	//New weather selection times.
	newWeatherTimeMin = luaObject.getIntField("newWeatherTimeMin");
	newWeatherTimeMax = luaObject.getIntField("newWeatherTimeMax");
	if (newWeatherTimeMin > newWeatherTimeMax || newWeatherTimeMax > 100000)
		return false;

	//Weather transition times.
	transitionTimeMin = luaObject.getIntField("transitionTimeMin");
	transitionTimeMax = luaObject.getIntField("transitionTimeMax");
	if (transitionTimeMin > transitionTimeMax || transitionTimeMax > 100000)
		return false;

	//Optional sandstorm feature for Tatooine & Lok.
	//TODO: Should make this a list of planets, so that new planets can easily be added from lua.
	String zoneName = zone->getZoneName();

	if (zoneName == "tatooine" || zoneName == "lok") {
		sandstormEffectsEnabled = luaObject.getByteField("sandstormEffectsEnabled");

		sandstormWounds = luaObject.getIntField("sandstormWounds");
		if (sandstormWounds > 500)
			return false;

		sandstormWoundsMitigation = luaObject.getIntField("sandstormWoundsMitigation");
		if (sandstormWoundsMitigation > 500)
			return false;

		sandstormKnockdownChance = luaObject.getIntField("sandstormKnockdownChance");
		if (sandstormKnockdownChance > 100)
			return false;

		sandstormKnockdownModifier = luaObject.getIntField("sandstormKnockdownModifier");
		if (sandstormKnockdownModifier > 100)
			return false;

		sandstormTickTime = luaObject.getIntField("sandstormTickTime");
		if (sandstormTickTime < 5 || sandstormTickTime > 60)
			return false;
	}

	luaObject.pop();
	delete lua;
	lua = NULL;
	return true;
}


void WeatherManagerImplementation::loadDefaultValues() {
	Locker weatherManagerLocker(_this);

	weatherEnabled = true;
	weatherID = System::random(2);
	targetWeatherID = weatherID;

	//Severity odds used when selecting new weather.
	levelZeroChance = 70;
	levelOneChance = 14;
	levelTwoChance = 9;
	levelThreeChance = 5;
	levelFourChance = 2;
	windChangeChance = 50;

	//Transition times.
	newWeatherTimeMin = 600; //seconds. 10 min
	newWeatherTimeMax = 1800; //seconds. 30 min
	transitionTimeMin = 120; //seconds. 2 min
	transitionTimeMax = 600; //seconds. 10 min

	//Sandstorm stuff.
	sandstormEffectsEnabled = false;
	sandstormWounds = 15;
	sandstormWoundsMitigation = 3;
	sandstormKnockdownChance = 40;
	sandstormKnockdownModifier = 4;
	sandstormTickTime = 10; //seconds.
}


void WeatherManagerImplementation::generateNewWeather() {
	Locker weatherManagerLocker(_this);

	if (!weatherEnabled)
		return;

	//Don't update weather if server is still loading.
	if (zone->getZoneServer()->isServerLoading()) {
		if (weatherChangeEvent->isScheduled())
			weatherChangeEvent->cancel();
		weatherChangeEvent->setNewWeather(true);
		weatherChangeEvent->schedule(300000); //5 minutes
		return;
	}

	//Determine what the weather will change to.
	int sumZeroOne = levelZeroChance + levelOneChance;
	int sumZeroOneTwo = sumZeroOne + levelTwoChance;
	int sumZeroOneTwoThree = sumZeroOneTwo + levelThreeChance;

	int die = System::random(99);

	if (die < levelZeroChance)
		targetWeatherID = 0;

	else if (die >= levelZeroChance && die < sumZeroOne)
		targetWeatherID = 1;

	else if (die >= sumZeroOne && die < sumZeroOneTwo)
		targetWeatherID = 2;

	else if (die >= sumZeroOneTwo && die < sumZeroOneTwoThree)
		targetWeatherID = 3;

	else if (die >= sumZeroOneTwoThree && die < sumZeroOneTwoThree + levelFourChance)
		targetWeatherID = 4;

	else {
		info("ERROR while selecting a new target weather.");
		targetWeatherID = System::random(2);
	}

	//Transition the weather toward the new value and update wind direction.
	weatherTransition();
}


void WeatherManagerImplementation::weatherTransition() {
	Locker weatherManagerLocker(_this);

	int startingWeatherID = weatherID;

	if (!weatherEnabled)
		return;

	//Adjust weather ID closer to the target weather.
	if (targetWeatherID > weatherID)
		weatherID += 1;
	else if (targetWeatherID < weatherID)
		weatherID -= 1;

	//Change wind direction chance.
	changeWindDirection();

	//Update players on the planet with new weather and start sandstorm damage if applicable.
	if (sandstormEffectsEnabled && startingWeatherID == 3 && weatherID == 4) {
		broadcastWeather(true, true); //Send packet, apply sandstorm damage.
		if (!sandstormTickEvent->isScheduled())
			sandstormTickEvent->schedule(sandstormTickTime * 1000);
	} else
		broadcastWeather(true, false); //Send packet, don't apply sandstorm damage.

	if (weatherChangeEvent->isScheduled())
		weatherChangeEvent->cancel();

	//If we are now at the target weather, schedule a weather change.
	if (weatherID == targetWeatherID) {
		weatherChangeEvent->setNewWeather(true);
		int time = newWeatherTimeMin + System::random(newWeatherTimeMax - newWeatherTimeMin);
		weatherChangeEvent->schedule(time * 1000);

	} else { //Otherwise, schedule another transition.
		weatherChangeEvent->setNewWeather(false);
		int time = transitionTimeMin + System::random(transitionTimeMax - transitionTimeMin);
		weatherChangeEvent->schedule(time * 1000);
	}
}


void WeatherManagerImplementation::broadcastWeather(bool notifyPlayer, bool doSandstormDamage) {
	Locker weatherManagerLocker(_this);

	ManagedReference<ChatManager*> chatManager = zone->getZoneServer()->getChatManager();
	Locker playerMapLocker(chatManager);

	PlayerMap* playerMap = chatManager->getPlayerMap();
	if (playerMap == NULL)
		return;

	playerMap->resetIterator();

	ManagedReference<PlayerCreature*> player;

	while (playerMap->hasNext()) {
		player = playerMap->next();
		if (player == NULL)
			continue;

		Locker playerLocker(player);

		if (player->isOnline() && !player->isTeleporting()) {
			//Check if player is on this planet.
			if (player->getZone()->getZoneName() != zone->getZoneName())
				continue;

			//Send the weather packet.
			if (notifyPlayer)
				sendWeatherPacket(player);

			//Send sandstorm warning if applicable.
			if (sandstormEffectsEnabled && weatherID == 3 && targetWeatherID == 4) {
				player->sendSystemMessage("The Planetary Weather Network has issued a severe sandstorm warning.");
				player->sendSystemMessage("You should seek shelter immediately!");
			}

			if (doSandstormDamage && !player->getPvpStatusBitmask() == 0) {
				applySandstormDamage(player);
			}
		}
	}

}


void WeatherManagerImplementation::sendWeatherPacket(PlayerCreature* player) {
	Locker weatherManagerLocker(_this);

	if (player == NULL)
		return;

	Locker playerLocker(player);

	ServerWeatherMessage* weatherMessage = new ServerWeatherMessage(_this);
	player->sendMessage(weatherMessage);
	return;
}


void WeatherManagerImplementation::changeWindDirection() {
	Locker weatherManagerLocker(_this);

	float currentWindValue;
	float newWindValue;
	bool changeX;

	//Determine if wind will change direction during this weather transition.
	if (!(weatherID > 2 && windChangeChance > System::random(99)) && !(windX == 0.0f && windY == 0.0f))
		return;

	//Select which wind direction to change.
	//If one value is 0, we must change that one since they both shouldn't be 0 (flags stop flapping).
	if (windX == 0.0f)
		changeX = true;

	else if (windY == 0.0f)
		changeX = false;

	else {
		switch (System::random(1)) {
		case 0:
			changeX = true;
			break;

		case 1:
			changeX = false;
			break;
		}
	}

	if (changeX)
		currentWindValue = windX;
	else
		currentWindValue = windY;

	//Change the wind direction.
	if (currentWindValue == -1.0f || currentWindValue == 1.0f)
		newWindValue = 0.0f;

	else {
		switch (System::random(1)) {

		case 0:
			newWindValue = -1.0f;
			break;

		case 1:
			newWindValue = 1.0f;
			break;
		}
	}

	//Set the new wind direction.
	if (changeX)
		setWindX(newWindValue);
	else
		setWindY(newWindValue);
}


void WeatherManagerImplementation::sandstormTick() {
	Locker weatherManagerLocker(_this);
	if (!weatherEnabled || !sandstormEffectsEnabled || weatherID != 4)
		return;

	//Apply sandstorm damage to exposed players.
	broadcastWeather(false, true); //Don't send packet, apply sandstorm damage.

	//Schedule the next tick.
	if (sandstormTickEvent->isScheduled())
		sandstormTickEvent->cancel();
	sandstormTickEvent->schedule(sandstormTickTime * 1000);
}


void WeatherManagerImplementation::applySandstormDamage(PlayerCreature* player) {
	if (player == NULL)
		return;

	//Check player's online status.
	if (player->isTeleporting() || !player->isOnline())
		return;

	//Check if player is in a shelter.
	if (!player->isMounted() && player->getParentID() != 0) //TODO: Add camp protection.
		return;

	//Blind player
	player->setBlindedState(60);

	//Calculate the sandstorm protection the player has.
	Vector<int> sandstormCoverings;
	calculateSandstormProtection(player, sandstormCoverings);
	int clothingPieces = sandstormCoverings.get(0);
	int armourPieces = sandstormCoverings.get(1);
	int totalCoverings = clothingPieces + armourPieces;

	//Apply wounds.
	int applicableWounds = sandstormWounds - (totalCoverings * sandstormWoundsMitigation);
	if (applicableWounds > 0) {
		player->addWounds(CreatureAttribute::HEALTH, applicableWounds, true);
		player->addWounds(CreatureAttribute::ACTION, applicableWounds, true);
		player->addWounds(CreatureAttribute::MIND, applicableWounds, true);
	}

	//Apply knockdown.
	int applicableKDChance = sandstormKnockdownChance - (clothingPieces * sandstormKnockdownModifier) + (armourPieces * sandstormKnockdownModifier);
	if (applicableKDChance > System::random(99) && !player->isProne() && !player->isKnockedDown()) {
		if (player->isMounted()) {
			player->sendSystemMessage("A gust of wind blows you off your vehicle!");
			player->dismount();
		} else
			player->sendSystemMessage("A gust of wind blows you off balance!");

		player->setPosture(CreaturePosture::KNOCKEDDOWN, true);
	}
}


void WeatherManagerImplementation::calculateSandstormProtection(PlayerCreature* player, Vector<int>& sandstormCoverings) {
	if (player == NULL)
		return;

	int clothing = 0;
	int armour = 0;
	uint32 crc;

	//Check for protective head gear.
	ManagedReference<SceneObject*> hat = player->getSlottedObject("hat");
	if (hat != NULL) {
		crc = hat->getServerObjectCRC();
		if (crc == 0x612f992f || crc == 0xba3831b8 || crc == 0xdc8d2e72 || crc == 0x754b6f93) //Tusken Raider helmets, Swoop helmet, Large Headwrap.
			clothing += 1;
		else if (hat->isArmorObject())
			armour += 1;
	}

	//Check for protective chest covering.
	bool tuskenRobe = false;
	ManagedReference<SceneObject*> robe = player->getSlottedObject("chest2");
	if (robe != NULL) {
		crc = robe->getServerObjectCRC();
		if (crc == 0xc20d81d9 || crc == 0x191a294e) { //Tusken Robes.
			tuskenRobe = true;
			clothing += 2; //They cover both chest and legs.
		} else if (crc == 0xd95ec143 || crc == 0x3995e72f) //Scout Jacket, Heavy Reinforced Jacket.
			clothing += 1;
		else if (crc == 0x9053a6ce || crc == 0x663c19d1) //Vested jacket, Desert Command Jacket.
			clothing += 1;
		else if (robe->isArmorObject())
			armour += 1;
	}

	//Check for protective pants.
	if (!tuskenRobe) {
		ManagedReference<SceneObject*> pants = player->getSlottedObject("pants1");
		if (pants != NULL) {
			crc = pants->getServerObjectCRC();
			if (crc == 0x9488cb5f || crc == 0x10369d36 || crc == 0x9c6cabd4) //Paramilitary Camos, Basic Camos, Reinforced Pants.
				clothing += 1;
			else if (crc == 0xb9f0dcd7 || crc == 0xc6ada1aa) //Desert Crawlers, Padded Workpants
				clothing += 1;
		}

		ManagedReference<SceneObject*> pants2 = player->getSlottedObject("pants2");
		if (pants2 != NULL) {
			crc = pants2->getServerObjectCRC();
			if (pants2->isArmorObject())
				armour += 1;
		}
	}

	//Check for protective gloves.
	ManagedReference<SceneObject*> gloves = player->getSlottedObject("gloves");
	if (gloves != NULL) {
		crc = gloves->getServerObjectCRC();
		if (crc == 0x29fc844 || crc == 0x41ba6c29 || crc == 0x614eefaa) //Tusken gloves, Link-Steel Reinforced Gloves, Heavy Gloves.
			clothing += 1;
		else if (gloves->isArmorObject())
			armour += 1;
	}

	//Check for protective boots.
	ManagedReference<SceneObject*> boots = player->getSlottedObject("shoes");
	if (boots != NULL) {
		crc = boots->getServerObjectCRC();
		if (crc == 0xbcc9eaac || crc == 0x873644ed) //Tusken boots, Sturdy boots
			clothing += 1;
		else if (crc == 0x9192dd9e || crc == 0x35d80874) //Paneled Boots, Wrapped Boots.
			clothing += 1;
		else if (boots->isArmorObject())
			armour += 1;
	}

	sandstormCoverings.add(clothing);
	sandstormCoverings.add(armour);
}


void WeatherManagerImplementation::enableWeather(PlayerCreature* player) {
	Locker weatherManagerLocker(_this);
	if (player == NULL)
		return;

	weatherEnabled = true;

	if (weatherChangeEvent == NULL)
		weatherChangeEvent = new WeatherChangeEvent(_this);

	if (weatherChangeEvent->isScheduled())
		weatherChangeEvent->cancel();

	weatherChangeEvent->setNewWeather(true);

	int time = newWeatherTimeMin + System::random(newWeatherTimeMax - newWeatherTimeMin);
	weatherChangeEvent->schedule(time * 1000);

	sandstormTick(); //In case sandstorm effects are enabled and weather ID is 4.

	player->sendSystemMessage("The weather on this planet will now change automatically.");
}


void WeatherManagerImplementation::disableWeather(PlayerCreature* player) {
	Locker weatherManagerLocker(_this);
	if (player == NULL)
		return;

	weatherEnabled = false;

	if (weatherChangeEvent != NULL) {
		if (weatherChangeEvent->isScheduled())
			weatherChangeEvent->cancel();

		weatherChangeEvent = NULL;
	}

	player->sendSystemMessage("The weather on this planet will no longer change automatically.");
}


void WeatherManagerImplementation::changeWeather(PlayerCreature* player, int newWeather) {
	Locker weatherManagerLocker(_this);
	if (player == NULL)
		return;

	targetWeatherID = newWeather;
	weatherID = newWeather;

	//Update players on the planet with new weather and start sandstorm damage if applicable.
	if (sandstormEffectsEnabled && weatherID == 4) {
		broadcastWeather(true, true); //Send packet, apply sandstorm damage.
		if (!sandstormTickEvent->isScheduled())
			sandstormTickEvent->schedule(sandstormTickTime * 1000);
	} else
		broadcastWeather(true, false); //Send packet, don't apply sandstorm damage.
}


void WeatherManagerImplementation::weatherInfo(PlayerCreature* player) {
	Locker weatherManagerLocker(_this);
	if (player == NULL)
		return;

	Locker playerLocker(player);

	String planetName = zone->getZoneName();

	Time executionTime;
	StringBuffer output;
	output << "Weather info for " << planetName << ":";
	player->sendSystemMessage(output.toString());
	output.deleteAll();

	//Operational booleans.
	output << "weatherEnabled = ";
	if (weatherEnabled)
		output << "true";
	else
		output << "false";

	output << " and sandstormEffectsEnabled = ";

	if (sandstormEffectsEnabled)
		output << "true";
	else
		output << "false";

	player->sendSystemMessage(output.toString());
	output.deleteAll();

	//Weather IDs.
	output << "weatherID = " << weatherID << " and targetWeatherID = " << targetWeatherID;
	player->sendSystemMessage(output.toString());
	output.deleteAll();

	output << "windX = " << windX << " and windY = " << windY;
	player->sendSystemMessage(output.toString());
	output.deleteAll();

	//Weather change event.
	if (weatherChangeEvent == NULL)
		player->sendSystemMessage("weatherChangeEvent is NULL.");
	else if (weatherChangeEvent->isScheduled()) {
		executionTime = weatherChangeEvent->getNextExecutionTime();
		output << "weatherChangeEvent is scheduled to run in " << abs(executionTime.miliDifference() / 1000) << " seconds.";
		player->sendSystemMessage(output.toString());
		output.deleteAll();
	} else
		player->sendSystemMessage("weatherChangeEvent exists but is not scheduled.");

	//Sandstorm tick event.
	if (sandstormTickEvent == NULL)
		player->sendSystemMessage("sandstormTickEvent is NULL.");
	else if (sandstormTickEvent->isScheduled()) {
		executionTime = sandstormTickEvent->getNextExecutionTime();
		output << "sandstormTickEvent is scheduled to run in " << abs(executionTime.miliDifference() / 1000) << " seconds.";
		player->sendSystemMessage(output.toString());
		output.deleteAll();
	} else
		player->sendSystemMessage("sandstormTickEvent exists but is not scheduled.");

}
