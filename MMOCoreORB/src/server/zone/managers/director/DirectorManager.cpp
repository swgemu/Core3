/*
 * DirectorManager.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "DirectorManager.h"
#include "server/zone/objects/creature/LuaCreatureObject.h"
#include "server/zone/objects/scene/LuaSceneObject.h"
#include "server/zone/objects/building/LuaBuildingObject.h"
#include "server/zone/objects/intangible/LuaIntangibleObject.h"
#include "server/zone/objects/player/LuaPlayerObject.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/faction/FactionManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "ScreenPlayTask.h"
#include "ScreenPlayObserver.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/player/creation/PlayerCreationManager.h"
#include "server/ServerCore.h"
#include "server/chat/ChatManager.h"
#include "server/chat/ChatMessage.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/objects/creature/CreatureState.h"
#include "server/zone/objects/creature/CreaturePosture.h"
#include "server/zone/objects/creature/LuaAiAgent.h"
#include "server/zone/objects/area/LuaActiveArea.h"
#include "server/zone/templates/mobile/ConversationScreen.h"
#include "server/zone/templates/mobile/ConversationTemplate.h"
#include "server/zone/templates/mobile/LuaConversationScreen.h"
#include "server/zone/templates/mobile/LuaConversationTemplate.h"
#include "server/zone/objects/player/sessions/LuaConversationSession.h"
#include "server/zone/objects/tangible/terminal/startinglocation/StartingLocationTerminal.h"
#include "server/zone/objects/area/SpawnArea.h"

DirectorManager::DirectorManager() : Logger("DirectorManager") {
	info("loading..", true);

	sharedMemory = new DirectorSharedMemory();
	sharedMemory->setNullValue(0);

	screenPlays.setNullValue(false);
	screenPlays.setNoDuplicateInsertPlan();
}

void DirectorManager::startGlobalScreenPlays() {
	for (int i = 0; i < screenPlays.size(); ++i) {
		String screenPlay = screenPlays.elementAt(i).getKey();
		bool start = screenPlays.elementAt(i).getValue();

		if (start)
			startScreenPlay(NULL, screenPlay);
	}
}

void DirectorManager::initializeLuaEngine(Lua* luaEngine) {
	info("initializeLuaEngine");

	luaEngine->init();
	luaEngine->setLoggingName("DirectorManagerLuaInstance");
	luaEngine->setGlobalLogging(true);
	luaEngine->setLogging(true);

	lua_register(luaEngine->getLuaState(), "includeFile", includeFile);
	lua_register(luaEngine->getLuaState(), "createEvent", createEvent);
	lua_register(luaEngine->getLuaState(), "createObserver", createObserver);
	lua_register(luaEngine->getLuaState(), "spawnMobile", spawnMobile);
	lua_register(luaEngine->getLuaState(), "spatialChat", spatialChat);
	lua_register(luaEngine->getLuaState(), "spatialShout", spatialShout);
	lua_register(luaEngine->getLuaState(), "readSharedMemory", readSharedMemory);
	lua_register(luaEngine->getLuaState(), "writeSharedMemory", writeSharedMemory);
	lua_register(luaEngine->getLuaState(), "deleteSharedMemory", deleteSharedMemory);
	lua_register(luaEngine->getLuaState(), "spawnSceneObject", spawnSceneObject);
	lua_register(luaEngine->getLuaState(), "getSceneObject", getSceneObject);
	lua_register(luaEngine->getLuaState(), "getCreatureObject", getCreatureObject);
	lua_register(luaEngine->getLuaState(), "addStartingItemsInto", addStartingItemsInto);
	lua_register(luaEngine->getLuaState(), "addStartingWeaponsInto", addStartingWeaponsInto);
	lua_register(luaEngine->getLuaState(), "setAuthorizationState", setAuthorizationState);
	lua_register(luaEngine->getLuaState(), "giveItem", giveItem);
	lua_register(luaEngine->getLuaState(), "checkInt64Lua", checkInt64Lua);
	lua_register(luaEngine->getLuaState(), "getChatMessage", getChatMessage);
	lua_register(luaEngine->getLuaState(), "getRankName", getRankName);
	lua_register(luaEngine->getLuaState(), "getRankCost", getRankCost);
	lua_register(luaEngine->getLuaState(), "getRankDelegateRatioFrom", getRankDelegateRatioFrom);
	lua_register(luaEngine->getLuaState(), "getRankDelegateRatioTo", getRankDelegateRatioTo);
	lua_register(luaEngine->getLuaState(), "isHighestRank", isHighestRank);
	lua_register(luaEngine->getLuaState(), "getFactionPointsCap", getFactionPointsCap);
	lua_register(luaEngine->getLuaState(), "registerScreenPlay", registerScreenPlay);
	lua_register(luaEngine->getLuaState(), "isZoneEnabled", isZoneEnabled);

	lua_register(luaEngine->getLuaState(), "getRegion", getRegion);
	lua_register(luaEngine->getLuaState(), "writeScreenPlayData", writeScreenPlayData);
	lua_register(luaEngine->getLuaState(), "readScreenPlayData", readScreenPlayData);
	lua_register(luaEngine->getLuaState(), "clearScreenPlayData", clearScreenPlayData);
	lua_register(luaEngine->getLuaState(), "getObjectTemplatePathByCRC", getObjectTemplatePathByCRC);

	luaEngine->setGlobalInt("POSITIONCHANGED", ObserverEventType::POSITIONCHANGED);
	luaEngine->setGlobalInt("CLOSECONTAINER", ObserverEventType::CLOSECONTAINER);
	luaEngine->setGlobalInt("OBJECTDESTRUCTION", ObserverEventType::OBJECTDESTRUCTION);
	luaEngine->setGlobalInt("SAMPLE", ObserverEventType::SAMPLE);
	luaEngine->setGlobalInt("CONVERSE", ObserverEventType::CONVERSE);
	luaEngine->setGlobalInt("KILLEDCREATURE", ObserverEventType::KILLEDCREATURE);
	luaEngine->setGlobalInt("OBJECTREMOVEDFROMZONE", ObserverEventType::OBJECTREMOVEDFROMZONE);
	luaEngine->setGlobalInt("ENTEREDAREA", ObserverEventType::ENTEREDAREA);
	luaEngine->setGlobalInt("EXITEDAREA", ObserverEventType::EXITEDAREA);
	luaEngine->setGlobalInt("DESTINATIONREACHED", ObserverEventType::DESTINATIONREACHED);
	luaEngine->setGlobalInt("SPECIALATTACK", ObserverEventType::SPECIALATTACK);
	luaEngine->setGlobalInt("CALLFORHELP", ObserverEventType::CALLFORHELP);
	luaEngine->setGlobalInt("NEWBIETUTORIALZOOMCAMERA", ObserverEventType::NEWBIETUTORIALZOOMCAMERA);
	luaEngine->setGlobalInt("CHAT", ObserverEventType::CHAT);
	luaEngine->setGlobalInt("NEWBIETUTORIALHOLOCRON", ObserverEventType::NEWBIETUTORIALHOLOCRON);
	luaEngine->setGlobalInt("OBJECTINRANGEMOVED", ObserverEventType::OBJECTINRANGEMOVED);
	luaEngine->setGlobalInt("PLAYERCHANGEDTARGET", ObserverEventType::PLAYERCHANGEDTARGET);
	luaEngine->setGlobalInt("STARTCONVERSATION", ObserverEventType::STARTCONVERSATION);
	luaEngine->setGlobalInt("SELECTCONVERSATION", ObserverEventType::SELECTCONVERSATION);
	luaEngine->setGlobalInt("STOPCONVERSATION", ObserverEventType::STOPCONVERSATION);
	luaEngine->setGlobalInt("OPENCONTAINER", ObserverEventType::OPENCONTAINER);
	luaEngine->setGlobalInt("NEWBIEOPENINVENTORY", ObserverEventType::NEWBIEOPENINVENTORY);
	luaEngine->setGlobalInt("NEWBIECLOSEINVENTORY", ObserverEventType::NEWBIECLOSEINVENTORY);
	luaEngine->setGlobalInt("OBJECTRADIALUSED", ObserverEventType::OBJECTRADIALUSED);
	luaEngine->setGlobalInt("DAMAGERECEIVED", ObserverEventType::DAMAGERECEIVED);
	luaEngine->setGlobalInt("OBJECTNAMECHANGED", ObserverEventType::OBJECTNAMECHANGED);
	luaEngine->setGlobalInt("SURVEY", ObserverEventType::SURVEY);
	luaEngine->setGlobalInt("GETATTRIBUTESBATCHCOMMAND", ObserverEventType::GETATTRIBUTESBATCHCOMMAND);
	luaEngine->setGlobalInt("HEALINGPERFORMED", ObserverEventType::HEALINGPERFORMED);
	luaEngine->setGlobalInt("STARTCOMBAT", ObserverEventType::STARTCOMBAT);
	luaEngine->setGlobalInt("DEFENDERADDED", ObserverEventType::DEFENDERADDED);
	luaEngine->setGlobalInt("DEFENDERDROPPED", ObserverEventType::DEFENDERDROPPED);
	luaEngine->setGlobalInt("OBJECTRADIALOPENED", ObserverEventType::OBJECTRADIALOPENED);
	luaEngine->setGlobalInt("ENTEREDBUILDING", ObserverEventType::ENTEREDBUILDING);
	luaEngine->setGlobalInt("EXITEDBUILDING", ObserverEventType::EXITEDBUILDING);

	luaEngine->setGlobalInt("POSTURESITTING", CreaturePosture::SITTING);
	luaEngine->setGlobalInt("STATESITTINGONCHAIR", CreatureState::SITTINGONCHAIR);

	//Waypoint Colors
	luaEngine->setGlobalInt("WAYPOINTBLUE", WaypointObject::COLOR_BLUE);
	luaEngine->setGlobalInt("WAYPOINTGREEN", WaypointObject::COLOR_GREEN);
	luaEngine->setGlobalInt("WAYPOINTYELLOW", WaypointObject::COLOR_YELLOW);
	luaEngine->setGlobalInt("WAYPOINTPURPLE", WaypointObject::COLOR_PURPLE);
	luaEngine->setGlobalInt("WAYPOINTWHITE", WaypointObject::COLOR_WHITE);
	luaEngine->setGlobalInt("WAYPOINTORANGE", WaypointObject::COLOR_ORANGE);


	Luna<LuaBuildingObject>::Register(luaEngine->getLuaState());
	Luna<LuaCreatureObject>::Register(luaEngine->getLuaState());
	Luna<LuaSceneObject>::Register(luaEngine->getLuaState());
	Luna<LuaConversationScreen>::Register(luaEngine->getLuaState());
	Luna<LuaConversationSession>::Register(luaEngine->getLuaState());
	Luna<LuaConversationTemplate>::Register(luaEngine->getLuaState());
	Luna<LuaIntangibleObject>::Register(luaEngine->getLuaState());
	Luna<LuaPlayerObject>::Register(luaEngine->getLuaState());
	Luna<LuaAiAgent>::Register(luaEngine->getLuaState());
	Luna<LuaActiveArea>::Register(luaEngine->getLuaState());

	if (!luaEngine->runFile("scripts/screenplays/screenplay.lua"))
		error("could not run scripts/screenplays/screenplay.lua");
}

int DirectorManager::writeScreenPlayData(lua_State* L) {
	String data = lua_tostring(L, -1);
	String variable = lua_tostring(L, -2);
	String screenPlay = lua_tostring(L, -3);
	CreatureObject* player = (CreatureObject*) lua_touserdata(L, -4);

	//writeScreenPlayData(player, screenPlay, variable, data)

	PlayerObject* ghost = player->getPlayerObject();
	ghost->setScreenPlayData(screenPlay, variable, data);

	return 0;
}

int DirectorManager::readScreenPlayData(lua_State* L) {
	String variable = lua_tostring(L, -1);
	String screenPlay = lua_tostring(L, -2);
	CreatureObject* player = (CreatureObject*) lua_touserdata(L, -3);
	PlayerObject* ghost = player->getPlayerObject();

	//readScreenPlayData(player, screenPlay, variable)

	lua_pushstring(L, ghost->getScreenPlayData(screenPlay, variable));

	return 1;
}

int DirectorManager::clearScreenPlayData(lua_State* L) {
	String screenPlay = lua_tostring(L, -1);
	CreatureObject* player = (CreatureObject*) lua_touserdata(L, -2);
	PlayerObject* ghost = player->getPlayerObject();

	ghost->clearScreenPlayData(screenPlay);

	return 0;
}

int DirectorManager::registerScreenPlay(lua_State* L) {
	String name = lua_tostring(L, -2);
	bool start = lua_toboolean(L, -1);

	instance()->wlock();

	instance()->screenPlays.put(name, start);

	instance()->unlock();

	return 0;
}

int DirectorManager::checkInt64Lua(lua_State* L) {
	uint64 data = lua_tointeger(L, -1);

	uint64 bigNumber = 0x01000000;
	bigNumber += bigNumber << 32;

	if (data < bigNumber) {
		instance()->error("Lua not using lnum patch with 64 bit integers, please patch lua!!");
	} else {
		instance()->info("Lua reads int64");
	}

	lua_pop(L, 1);

	return 0;
}

int DirectorManager::includeFile(lua_State* L) {
	String filename = Lua::getStringParameter(L);

	Lua::runFile("scripts/screenplays/" + filename, L);

	return 0;
}

int DirectorManager::readSharedMemory(lua_State* L) {
	String key = Lua::getStringParameter(L);

#ifndef WITH_STM
	DirectorManager::instance()->rlock();
#endif

	uint64 data = DirectorManager::instance()->sharedMemory->get(key);

#ifndef WITH_STM
	DirectorManager::instance()->runlock();
#endif

	lua_pushinteger(L, data);

	return 1;
}

int DirectorManager::deleteSharedMemory(lua_State* L) {
	String key = Lua::getStringParameter(L);

#ifndef WITH_STM
	DirectorManager::instance()->rlock();
#endif

	DirectorManager::instance()->sharedMemory->remove(key);

#ifndef WITH_STM
	DirectorManager::instance()->runlock();
#endif

	return 1;
}

int DirectorManager::writeSharedMemory(lua_State* L) {
	String key = lua_tostring(L, -2);
	uint64 data = lua_tointeger(L, -1);

#ifndef WITH_STM
	DirectorManager::instance()->wlock();
#endif

	DirectorManager::instance()->sharedMemory->put(key, data);

#ifndef WITH_STM
	DirectorManager::instance()->unlock();
#endif

	return 0;
}

int DirectorManager::createEvent(lua_State* L) {
	CreatureObject* creatureObject = (CreatureObject*)lua_touserdata(L, -1);
	String key = lua_tostring(L, -2);
	String play = lua_tostring(L, -3);
	uint32 mili = lua_tonumber(L, -4);

	//System::out << "scheduling task with mili:" << mili << endl;

	Reference<Task*> task = new ScreenPlayTask(creatureObject, key, play);
	task->schedule(mili);

	return 0;
}

int DirectorManager::getChatMessage(lua_State* L) {
	ChatMessage* cm = (ChatMessage*)lua_touserdata(L, -1);

	String text = "";

	if (cm != NULL)
		text = cm->toString();

	text = text.toLowerCase();

	lua_pushstring(L, text.toCharArray());

	return 1;
}

int DirectorManager::spatialChat(lua_State* L) {
	ZoneServer* zoneServer = ServerCore::getZoneServer();
	ChatManager* chatManager = zoneServer->getChatManager();

	CreatureObject* creature = (CreatureObject*)lua_touserdata(L, -2);
	String message = lua_tostring(L, -1);

	if (creature != NULL)
		chatManager->broadcastMessage(creature, message, 0, 0, 0);

	return 0;
}

int DirectorManager::spatialShout(lua_State* L) {
	ZoneServer* zoneServer = ServerCore::getZoneServer();
	ChatManager* chatManager = zoneServer->getChatManager();

	CreatureObject* creature = (CreatureObject*)lua_touserdata(L, -2);
	String message = lua_tostring(L, -1);

	if (creature != NULL)
		chatManager->broadcastMessage(creature, message, 0, 0, 80);

	return 0;
}

int DirectorManager::getSceneObject(lua_State* L) {
	uint64 objectID = lua_tointeger(L, -1);
	ZoneServer* zoneServer = ServerCore::getZoneServer();
	SceneObject* object = zoneServer->getObject(objectID);

	if (object == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, object);
	}

	return 1;
}

int DirectorManager::getRegion(lua_State* L) {
	String regionName = lua_tostring(L, -1);
	String zoneName = lua_tostring(L, -2);
	ZoneServer* zoneServer = ServerCore::getZoneServer();
	Zone* zone = zoneServer->getZone(zoneName);

	if (zone == NULL) {
		lua_pushnil(L);
		return 1;
	}

	CreatureManager* creatureManager = zone->getCreatureManager();

	SceneObject* spawnArea = creatureManager->getSpawnArea(regionName);

	if (spawnArea == NULL)
		lua_pushnil(L);
	else
		lua_pushlightuserdata(L, spawnArea);

	return 1;
}

int DirectorManager::getCreatureObject(lua_State* L) {
	uint64 objectID = lua_tointeger(L, -1);
	ZoneServer* zoneServer = ServerCore::getZoneServer();
	SceneObject* object = zoneServer->getObject(objectID);

	if (object != NULL && object->isCreatureObject()) {
		lua_pushlightuserdata(L, object);
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int DirectorManager::addStartingItemsInto(lua_State* L) {
	CreatureObject* creatureObject = (CreatureObject*)lua_touserdata(L, -2);
	SceneObject* sceneObject = (SceneObject*)lua_touserdata(L, -1);

	if (creatureObject != NULL && sceneObject != NULL) {
		PlayerCreationManager* pcm = PlayerCreationManager::instance();
		pcm->addStartingItemsInto(creatureObject, sceneObject);
	}

	return 0;
}

int DirectorManager::addStartingWeaponsInto(lua_State* L) {
	CreatureObject* creatureObject = (CreatureObject*)lua_touserdata(L, -2);
	SceneObject* sceneObject = (SceneObject*)lua_touserdata(L, -1);

	//SceneObject* sceneObject = creatureObject->getSlottedObject("inventory");

	if (creatureObject != NULL && sceneObject != NULL) {
		PlayerCreationManager* pcm = PlayerCreationManager::instance();
		pcm->addStartingWeaponsInto(creatureObject, sceneObject);
	}

	return 0;
}

int DirectorManager::giveItem(lua_State* L) {
	int slot = lua_tointeger(L, -1);
	String objectString = lua_tostring(L, -2);
	SceneObject* obj = (SceneObject*) lua_touserdata(L, -3);

	if (obj == NULL)
		return 0;

	ZoneServer* zoneServer = obj->getZoneServer();

	ManagedReference<SceneObject*> item = zoneServer->createObject(objectString.hashCode(), 1);

	if (item != NULL && obj != NULL) {
		obj->transferObject(item, slot, true);

		lua_pushlightuserdata(L, item.get());
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int DirectorManager::setAuthorizationState(lua_State* L) {
	SceneObject* terminal = (SceneObject*)lua_touserdata(L, -2);
	bool state = lua_toboolean(L, -1);

	//SceneObject* sceneObject = creatureObject->getSlottedObject("inventory");

	if (terminal == NULL) {
		instance()->info("setAuthorizationState: Terminal is NULL");
		return 0;
	}

	if (terminal->getGameObjectType() != SceneObjectType::NEWBIETUTORIALTERMINAL) {
		instance()->info("setAuthorizationState: Wrong SceneObjectType:" + String::valueOf(terminal->getGameObjectType()));
		return 0;
	}

	ManagedReference<StartingLocationTerminal*> item = (StartingLocationTerminal*)terminal;
	item->setAuthorizationState(state);

	return 0;
}

int DirectorManager::spawnMobile(lua_State* L) {
	uint64 parentID = lua_tointeger(L, -1);
	float heading = lua_tonumber(L, -2);
	float y = lua_tonumber(L, -3);
	float z = lua_tonumber(L, -4);
	float x = lua_tonumber(L, -5);
	int respawnTimer = lua_tointeger(L, -6);
	String mobile = lua_tostring(L, -7);
	String zoneid = lua_tostring(L, -8);

	ZoneServer* zoneServer = ServerCore::getZoneServer();

	Zone* zone = zoneServer->getZone(zoneid);

	if (zone == NULL) {
		lua_pushnil(L);
		return 1;
	}

	CreatureManager* creatureManager = zone->getCreatureManager();

	/*StringBuffer msg;
	msg << "trying to spawn with mobile: " << mobile << " x:" << x;
	DirectorManager::instance()->info(msg.toString(), true);*/

	CreatureObject* creature = creatureManager->spawnCreature(mobile.hashCode(), 0, x, z, y, parentID);

	if (creature == NULL) {
		instance()->error("coult not spawn mobile " + mobile);
	} else {
		creature->setDirection(Math::deg2rad(heading));
		
		if (creature->isAiAgent()) {
			AiAgent* ai = cast<AiAgent*>(creature);
			ai->setRespawnTimer(respawnTimer);
		}
	}

	lua_pushlightuserdata(L, creature);

	return 1;
	//public native CreatureObject spawnCreature(unsigned int templateCRC, float x, float z, float y, unsigned long parentID = 0);
}

int DirectorManager::spawnSceneObject(lua_State* L) {
	float dz = lua_tonumber(L, -1);
	float dy = lua_tonumber(L, -2);
	float dx = lua_tonumber(L, -3);
	float dw = lua_tonumber(L, -4);
	uint64 parentID = lua_tointeger(L, -5);
	float y = lua_tonumber(L, -6);
	float z = lua_tonumber(L, -7);
	float x = lua_tonumber(L, -8);
	String script = lua_tostring(L, -9);
	String zoneid = lua_tostring(L, -10);

	ZoneServer* zoneServer = ServerCore::getZoneServer();
	Zone* zone = zoneServer->getZone(zoneid);

	if (zone == NULL) {
		lua_pushnil(L);
		return 1;
	}


	ManagedReference<SceneObject*> object = zoneServer->createObject(script.hashCode(), 0);

	if (object != NULL) {
		object->initializePosition(x, z, y);
		object->setDirection(dw, dx, dy, dz);

		SceneObject* cellParent = NULL;

		if (parentID != 0) {
			cellParent = zoneServer->getObject(parentID);

			if (cellParent != NULL && !cellParent->isCellObject()) {
				//error("trying to set a parent that is not a cell to creature");
				cellParent = NULL;
			}
		}

		if (cellParent != NULL) {
			cellParent->transferObject(object, -1);
		} else
			zone->transferObject(object, -1, true);
	}

	lua_pushlightuserdata(L, object.get());

	return 1;
}

int DirectorManager::createObserver(lua_State* L) {
	SceneObject* sceneObject = (SceneObject*) lua_touserdata(L, -1);
	String key = lua_tostring(L, -2);
	String play = lua_tostring(L, -3);
	uint32 eventType = lua_tonumber(L, -4);

	ManagedReference<ScreenPlayObserver*> observer = dynamic_cast<ScreenPlayObserver*>(ObjectManager::instance()->createObject("ScreenPlayObserver", 0, ""));
	observer->setScreenPlay(play);
	observer->setScreenKey(key);

	sceneObject->registerObserver(eventType, observer);

	return 0;
}

Lua* DirectorManager::getLuaInstance() {
	Lua* lua = localLua.get();

	if (lua == NULL) {
		lua = new Lua();
		initializeLuaEngine(lua);

		localLua.set(lua);
	}

	//lua->runFile("scripts/screenplays/screenplay.lua");

	return lua;
}

void DirectorManager::startScreenPlay(CreatureObject* creatureObject, const String& screenPlayName) {
	Lua* lua = getLuaInstance();

	LuaFunction startScreenPlay(lua->getLuaState(), screenPlayName, "start", 0);
	startScreenPlay << creatureObject;

	lua->callFunction(&startScreenPlay);
}

ConversationScreen* DirectorManager::getNextConversationScreen(const String& luaClass, ConversationTemplate* conversationTemplate, CreatureObject* conversingPlayer, int selectedOption, CreatureObject* conversingNPC) {
	Lua* lua = getLuaInstance();

	LuaFunction runMethod(lua->getLuaState(), luaClass, "getNextConversationScreen", 1);
	runMethod << conversationTemplate;
	runMethod << conversingPlayer;
	runMethod << selectedOption;
	runMethod << conversingNPC;

	lua->callFunction(&runMethod);

	ConversationScreen* result = (ConversationScreen*) lua_touserdata(lua->getLuaState(), -1);

	lua_pop(lua->getLuaState(), 1);

	return result;
}

ConversationScreen* DirectorManager::runScreenHandlers(const String& luaClass, ConversationTemplate* conversationTemplate, CreatureObject* conversingPlayer, CreatureObject* conversingNPC, int selectedOption, ConversationScreen* conversationScreen) {
	Lua* lua = getLuaInstance();

	LuaFunction runMethod(lua->getLuaState(), luaClass, "runScreenHandlers", 1);
	runMethod << conversationTemplate;
	runMethod << conversingPlayer;
	runMethod << conversingNPC;
	runMethod << selectedOption;
	runMethod << conversationScreen;

	lua->callFunction(&runMethod);

	ConversationScreen* result = (ConversationScreen*) lua_touserdata(lua->getLuaState(), -1);

	lua_pop(lua->getLuaState(), 1);

	return result;
}

void DirectorManager::activateEvent(ScreenPlayTask* task) {
	CreatureObject* creo = task->getCreatureObject();
	String play = task->getScreenPlay();
	String key = task->getTaskKey();

	Lua* lua = getLuaInstance();

	LuaFunction startScreenPlay(lua->getLuaState(), play, key, 0);
	startScreenPlay << creo;

	lua->callFunction(&startScreenPlay);
}

int DirectorManager::createConversationScreen(lua_State* L) {
	ConversationScreen* screen = new ConversationScreen();

	lua_pushlightuserdata(L, screen);

	return 1;
}

int DirectorManager::getRankName(lua_State* L) {
	int rank = lua_tointeger(L, -1);

	String rankName = FactionManager::instance()->getRankName(rank);

	lua_pushstring(L, rankName.toCharArray());

	return 1;
}

int DirectorManager::getRankCost(lua_State* L) {
	int rank = lua_tointeger(L, -1);

	lua_pushinteger(L, FactionManager::instance()->getRankCost(rank));

	return 1;
}

int DirectorManager::getRankDelegateRatioFrom(lua_State* L) {
	int rank = lua_tointeger(L, -1);

	lua_pushinteger(L, FactionManager::instance()->getRankDelegateRatioFrom(rank));

	return 1;
}

int DirectorManager::getRankDelegateRatioTo(lua_State* L) {
	int rank = lua_tointeger(L, -1);

	lua_pushinteger(L, FactionManager::instance()->getRankDelegateRatioTo(rank));

	return 1;
}

int DirectorManager::isHighestRank(lua_State* L) {
	int rank = lua_tointeger(L, -1);

	bool result = FactionManager::instance()->isHighestRank(rank);

	lua_pushboolean(L, result);

	return 1;
}

int DirectorManager::getFactionPointsCap(lua_State* L) {
	int rank = lua_tointeger(L, -1);

	lua_pushinteger(L, FactionManager::instance()->getFactionPointsCap(rank));

	return 1;
}

int DirectorManager::getObjectTemplatePathByCRC(lua_State* L) {
	uint32 crc = lua_tointeger(L, -1);

	lua_pushstring(L, TemplateManager::instance()->getTemplateFile(crc));

	return 1;
}

int DirectorManager::isZoneEnabled(lua_State* L) {
	String zoneid = lua_tostring(L, -1);
	
	Zone* zone = ServerCore::getZoneServer()->getZone();
	
	lua_pushboolean(L, (zone != NULL));
	
	return 1;
}
