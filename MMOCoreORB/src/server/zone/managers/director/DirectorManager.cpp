/*
 * DirectorManager.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "DirectorManager.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/creature/LuaCreatureObject.h"
#include "server/zone/objects/scene/LuaSceneObject.h"
#include "server/zone/objects/building/LuaBuildingObject.h"
#include "server/zone/objects/intangible/LuaIntangibleObject.h"
#include "server/zone/objects/intangible/ControlDevice.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/player/LuaPlayerObject.h"
#include "server/zone/objects/tangible/LuaTangibleObject.h"
#include "server/zone/packets/cell/UpdateCellPermissionsMessage.h"
#include "server/zone/managers/structure/tasks/DestroyStructureTask.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/faction/FactionManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "ScreenPlayTask.h"
#include "server/zone/managers/director/ScreenPlayObserver.h"
#include "server/zone/managers/director/PersistentEvent.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/player/creation/PlayerCreationManager.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/ServerCore.h"
#include "server/chat/ChatManager.h"
#include "server/chat/ChatMessage.h"
#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/creature/CreatureState.h"
#include "server/zone/objects/creature/CreaturePosture.h"
#include "server/zone/objects/creature/LuaAiAgent.h"
#include "server/zone/objects/creature/ai/bt/Behavior.h"
#include "server/zone/objects/area/LuaActiveArea.h"
#include "server/zone/templates/mobile/ConversationScreen.h"
#include "server/zone/templates/mobile/ConversationTemplate.h"
#include "server/zone/templates/mobile/LuaConversationScreen.h"
#include "server/zone/templates/mobile/LuaConversationTemplate.h"
#include "server/zone/objects/player/sessions/LuaConversationSession.h"
#include "server/zone/objects/tangible/terminal/startinglocation/StartingLocationTerminal.h"
#include "server/zone/objects/area/SpawnArea.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/managers/sui/LuaSuiManager.h"
#include "server/zone/objects/player/sui/LuaSuiBox.h"
#include "server/zone/objects/scene/components/LuaObjectMenuResponse.h"
#include "server/zone/objects/scene/variables/ContainerPermissions.h"
#include "server/zone/objects/tangible/deed/Deed.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/managers/jedi/JediManager.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/creature/AiMap.h"
#include "server/chat/LuaStringIdChatParameter.h"
#include "server/zone/objects/tangible/ticket/TicketObject.h"
#include "server/db/ServerDatabase.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/managers/player/BadgeList.h"

int DirectorManager::DEBUG_MODE = 0;
int DirectorManager::ERROR_CODE = NO_ERROR;

SynchronizedHashTable<uint32, Reference<PersistentEvent*> > DirectorManager::persistentEvents;

DirectorManager::DirectorManager() : Logger("DirectorManager") {
	if (!DEBUG_MODE)
		info("loading..", true);

	sharedMemory = new DirectorSharedMemory();
	sharedMemory->setNullValue(0);

	screenPlays.setNullValue(false);
	screenPlays.setNoDuplicateInsertPlan();

	questStatuses.setNullValue(NULL);
	questStatuses.setNoDuplicateInsertPlan();
}

void DirectorManager::loadPersistentEvents() {
	info("Loading persistent events from events.db");

	ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();
	ObjectDatabase* eventDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("events", true);

	if (eventDatabase == NULL) {
		error("Could not load the event database.");
		return;
	}

	int i = 0;

	try {
		ObjectDatabaseIterator iterator(eventDatabase);

		uint64 objectID;

		while (iterator.getNextKey(objectID)) {
			Reference<PersistentEvent*> event = Core::getObjectBroker()->lookUp(objectID).castTo<PersistentEvent*>();
			++i;

			if (event != NULL && persistentEvents.put(event->getEventName().hashCode(), event) != NULL) {
				error("duplicate persistent event " + event->getEventName() + " loading from database!");
			} else if (event != NULL) {
				event->loadTransientTask();
			} else {
				error("could not load PersistentEvent!");
			}
		}
	} catch (DatabaseException& e) {
		error("Database exception in DirectorManager::loadPersistentEvents(): "	+ e.getMessage());
	}

	info(String::valueOf(i) + " persistent events loaded.", true);
}

void DirectorManager::loadPersistentStatus() {
	info("Loading persistent quest status from questdata.db");

	ObjectDatabaseManager* dbManager = ObjectDatabaseManager::instance();
	ObjectDatabase* statusDatabase = dbManager->loadObjectDatabase("questdata", true);

	if (statusDatabase == NULL) {
		error("Could not load the questdata database.");
		return;
	}

	try {
		ObjectDatabaseIterator iterator(statusDatabase);

		uint64 objectID;

		while (iterator.getNextKey(objectID)) {
			Reference<QuestStatus*> status = Core::getObjectBroker()->lookUp(objectID).castTo<QuestStatus*>();

			if (status != NULL)
				questStatuses.put(status->getKey(), status);
		}
	} catch (DatabaseException& e) {
		error("Database exception in DirectorManager::loadPersistentStatus(): "	+ e.getMessage());
	}

	info(String::valueOf(questStatuses.size()) + " persistent statuses loaded.", true);
}

void DirectorManager::setQuestStatus(String keyString, String valString) {
	ManagedReference<QuestStatus*> status = questStatuses.get(keyString);

	if (status == NULL) {
		status = new QuestStatus();
		status->setKey(keyString);
		questStatuses.put(keyString, status);

		ObjectManager::instance()->persistObject(status, 1, "questdata");
	}

	status->setStatus(valString);
}

String DirectorManager::getQuestStatus(String keyString) {
	String str = "";

	Reference<QuestStatus*> status = questStatuses.get(keyString);
	if (status != NULL)
		str = status->getStatus();

	return str;
}

void DirectorManager::removeQuestStatus(String key) {
	ManagedReference<QuestStatus*> status = NULL;

	status = questStatuses.get(key);

	questStatuses.drop(key);

	if (status != NULL)
		ObjectManager::instance()->destroyObjectFromDatabase(status->_getObjectID());
}

void DirectorManager::startGlobalScreenPlays() {
	for (int i = 0; i < screenPlays.size(); ++i) {
		String screenPlay = screenPlays.elementAt(i).getKey();
		bool start = screenPlays.elementAt(i).getValue();

		if (start)
			startScreenPlay(NULL, screenPlay);
	}
}

void DirectorManager::setupLuaPackagePath(Lua* luaEngine) {
	lua_State* L = luaEngine->getLuaState();
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "path");
	String currentPath = lua_tostring(L, -1);
	currentPath = currentPath.concat(";scripts/?.lua");
	lua_pop(L, 1);
	lua_pushstring(L, currentPath.toCharArray());
	lua_setfield(L, -2, "path");
	lua_pop(L, 1);
}

void DirectorManager::initializeLuaEngine(Lua* luaEngine) {
	if (DEBUG_MODE)
		setLogging(true);

	if (!DEBUG_MODE)
		info("initializeLuaEngine");

	luaEngine->init();
	luaEngine->setLoggingName("DirectorManagerLuaInstance");
	luaEngine->setGlobalLogging(true);
	luaEngine->setLogging(true);

	setupLuaPackagePath(luaEngine);

	lua_register(luaEngine->getLuaState(), "includeFile", includeFile);
	lua_register(luaEngine->getLuaState(), "createEvent", createEvent);
	lua_register(luaEngine->getLuaState(), "createEventActualTime", createEventActualTime);
	lua_register(luaEngine->getLuaState(), "createServerEvent", createServerEvent);
	lua_register(luaEngine->getLuaState(), "hasServerEvent", hasServerEvent);
	lua_register(luaEngine->getLuaState(), "getServerEventTimeLeft", getServerEventTimeLeft);
	lua_register(luaEngine->getLuaState(), "createObserver", createObserver);
	lua_register(luaEngine->getLuaState(), "dropObserver", dropObserver);
	lua_register(luaEngine->getLuaState(), "spawnMobile", spawnMobile);
	lua_register(luaEngine->getLuaState(), "spatialChat", spatialChat);
	lua_register(luaEngine->getLuaState(), "spatialMoodChat", spatialMoodChat);

	lua_register(luaEngine->getLuaState(), "getRandomNumber", getRandomNumber);

	lua_register(luaEngine->getLuaState(), "forcePeace", forcePeace);

	lua_register(luaEngine->getLuaState(), "readSharedMemory", readSharedMemory);
	lua_register(luaEngine->getLuaState(), "writeSharedMemory", writeSharedMemory);
	lua_register(luaEngine->getLuaState(), "deleteSharedMemory", deleteSharedMemory);
	lua_register(luaEngine->getLuaState(), "readStringSharedMemory", readStringSharedMemory);
	lua_register(luaEngine->getLuaState(), "writeStringSharedMemory", writeStringSharedMemory);
	lua_register(luaEngine->getLuaState(), "deleteStringSharedMemory", deleteStringSharedMemory);
	lua_register(luaEngine->getLuaState(), "spawnSceneObject", spawnSceneObject);
	lua_register(luaEngine->getLuaState(), "spawnActiveArea", spawnActiveArea);
	lua_register(luaEngine->getLuaState(), "spawnBuilding", spawnBuilding);
	lua_register(luaEngine->getLuaState(), "destroyBuilding", destroyBuilding);
	lua_register(luaEngine->getLuaState(), "getSceneObject", getSceneObject);
	lua_register(luaEngine->getLuaState(), "getCreatureObject", getCreatureObject);
	lua_register(luaEngine->getLuaState(), "addStartingItemsInto", addStartingItemsInto);
	lua_register(luaEngine->getLuaState(), "addStartingWeaponsInto", addStartingWeaponsInto);
	lua_register(luaEngine->getLuaState(), "setAuthorizationState", setAuthorizationState);
	lua_register(luaEngine->getLuaState(), "giveItem", giveItem);
	lua_register(luaEngine->getLuaState(), "giveControlDevice", giveControlDevice);
	lua_register(luaEngine->getLuaState(), "checkTooManyHirelings", checkTooManyHirelings);
	lua_register(luaEngine->getLuaState(), "checkInt64Lua", checkInt64Lua);
	lua_register(luaEngine->getLuaState(), "getChatMessage", getChatMessage);
	lua_register(luaEngine->getLuaState(), "getStringId", getStringId);
	lua_register(luaEngine->getLuaState(), "getRankName", getRankName);
	lua_register(luaEngine->getLuaState(), "getRankCost", getRankCost);
	lua_register(luaEngine->getLuaState(), "getRankDelegateRatioFrom", getRankDelegateRatioFrom);
	lua_register(luaEngine->getLuaState(), "getRankDelegateRatioTo", getRankDelegateRatioTo);
	lua_register(luaEngine->getLuaState(), "isHighestRank", isHighestRank);
	lua_register(luaEngine->getLuaState(), "getFactionPointsCap", getFactionPointsCap);
	lua_register(luaEngine->getLuaState(), "registerScreenPlay", registerScreenPlay);
	lua_register(luaEngine->getLuaState(), "getZoneByName", getZoneByName);
	lua_register(luaEngine->getLuaState(), "isZoneEnabled", isZoneEnabled);
	lua_register(luaEngine->getLuaState(), "getContainerObjectByTemplate", getContainerObjectByTemplate);
	lua_register(luaEngine->getLuaState(), "updateCellPermission", updateCellPermission);
	lua_register(luaEngine->getLuaState(), "updateCellPermissionGroup", updateCellPermissionGroup);

	// call for createLoot(SceneObject* container, const String& lootGroup, int level)
	lua_register(luaEngine->getLuaState(), "createLoot", createLoot);
	lua_register(luaEngine->getLuaState(), "createLootSet", createLootSet);
	lua_register(luaEngine->getLuaState(), "createLootFromCollection", createLootFromCollection);

	lua_register(luaEngine->getLuaState(), "getRegion", getRegion);
	lua_register(luaEngine->getLuaState(), "writeScreenPlayData", writeScreenPlayData);
	lua_register(luaEngine->getLuaState(), "readScreenPlayData", readScreenPlayData);
	lua_register(luaEngine->getLuaState(), "deleteScreenPlayData", deleteScreenPlayData);
	lua_register(luaEngine->getLuaState(), "clearScreenPlayData", clearScreenPlayData);
	lua_register(luaEngine->getLuaState(), "getObjectTemplatePathByCRC", getObjectTemplatePathByCRC);
	lua_register(luaEngine->getLuaState(), "getTimestamp", getTimestamp);
	lua_register(luaEngine->getLuaState(), "getTimestampMilli", getTimestampMilli);
	lua_register(luaEngine->getLuaState(), "getFormattedTime", getFormattedTime);
	lua_register(luaEngine->getLuaState(), "getSpawnPoint", getSpawnPoint);
	lua_register(luaEngine->getLuaState(), "getSpawnArea", getSpawnArea);
	lua_register(luaEngine->getLuaState(), "makeCreatureName", makeCreatureName);
	lua_register(luaEngine->getLuaState(), "getGCWDiscount", getGCWDiscount);
	lua_register(luaEngine->getLuaState(), "getTerrainHeight", getTerrainHeight);
	lua_register(luaEngine->getLuaState(), "awardSkill", awardSkill);
	lua_register(luaEngine->getLuaState(), "getCityRegionAt", getCityRegionAt);
	lua_register(luaEngine->getLuaState(), "setDungeonTicketAttributes", setDungeonTicketAttributes);
	lua_register(luaEngine->getLuaState(), "setQuestStatus", setQuestStatus);
	lua_register(luaEngine->getLuaState(), "getQuestStatus", getQuestStatus);
	lua_register(luaEngine->getLuaState(), "removeQuestStatus", removeQuestStatus);
	lua_register(luaEngine->getLuaState(), "getControllingFaction", getControllingFaction);
	lua_register(luaEngine->getLuaState(), "playClientEffectLoc", playClientEffectLoc);

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
	luaEngine->setGlobalInt("SPATIALCHATRECEIVED", ObserverEventType::SPATIALCHATRECEIVED);
	luaEngine->setGlobalInt("ITEMLOOTED", ObserverEventType::ITEMLOOTED);
	luaEngine->setGlobalInt("MEDPACKUSED", ObserverEventType::MEDPACKUSED);
	luaEngine->setGlobalInt("BADGEAWARDED", ObserverEventType::BADGEAWARDED);
	luaEngine->setGlobalInt("FACTIONBASEFLIPPED", ObserverEventType::FACTIONBASEFLIPPED);
	luaEngine->setGlobalInt("LOOTCREATURE", ObserverEventType::LOOTCREATURE);
	luaEngine->setGlobalInt("SCREENPLAYSTATECHANGED", ObserverEventType::SCREENPLAYSTATECHANGED);
	luaEngine->setGlobalInt("AIMESSAGE", ObserverEventType::AIMESSAGE);
	luaEngine->setGlobalInt("STARTENTERTAIN", ObserverEventType::STARTENTERTAIN);
	luaEngine->setGlobalInt("CHANGEENTERTAIN", ObserverEventType::CHANGEENTERTAIN);
	luaEngine->setGlobalInt("STOPENTERTAIN", ObserverEventType::STOPENTERTAIN);
	luaEngine->setGlobalInt("FLOURISH", ObserverEventType::FLOURISH);
	luaEngine->setGlobalInt("CONTAINERCONTENTSCHANGED", ObserverEventType::CONTAINERCONTENTSCHANGED);
	luaEngine->setGlobalInt("WASLISTENEDTO", ObserverEventType::WASLISTENEDTO);
	luaEngine->setGlobalInt("WASWATCHED", ObserverEventType::WASWATCHED);
	luaEngine->setGlobalInt("PARENTCHANGED", ObserverEventType::PARENTCHANGED);

	luaEngine->setGlobalInt("UPRIGHT", CreaturePosture::UPRIGHT);
	luaEngine->setGlobalInt("PRONE", CreaturePosture::PRONE);
	luaEngine->setGlobalInt("POSTURESITTING", CreaturePosture::SITTING);
	luaEngine->setGlobalInt("KNOCKEDDOWN", CreaturePosture::KNOCKEDDOWN);
	luaEngine->setGlobalInt("STATESITTINGONCHAIR", CreatureState::SITTINGONCHAIR);

	//Waypoint Colors
	luaEngine->setGlobalInt("WAYPOINTBLUE", WaypointObject::COLOR_BLUE);
	luaEngine->setGlobalInt("WAYPOINTGREEN", WaypointObject::COLOR_GREEN);
	luaEngine->setGlobalInt("WAYPOINTYELLOW", WaypointObject::COLOR_YELLOW);
	luaEngine->setGlobalInt("WAYPOINTPURPLE", WaypointObject::COLOR_PURPLE);
	luaEngine->setGlobalInt("WAYPOINTWHITE", WaypointObject::COLOR_WHITE);
	luaEngine->setGlobalInt("WAYPOINTORANGE", WaypointObject::COLOR_ORANGE);

	//Waypoint Special Types
	luaEngine->setGlobalInt("WAYPOINTTHEMEPARK", WaypointObject::SPECIALTYPE_THEMEPARK);
	luaEngine->setGlobalInt("WAYPOINTRACETRACK", WaypointObject::SPECIALTYPE_RACETRACK);
	luaEngine->setGlobalInt("WAYPOINTTREASUREMAP", WaypointObject::SPECIALTYPE_TREASUREMAP);

	luaEngine->setGlobalInt("HEALTH", CreatureAttribute::HEALTH);
	luaEngine->setGlobalInt("CONSTITUTION", CreatureAttribute::CONSTITUTION);
	luaEngine->setGlobalInt("STAMINA", CreatureAttribute::STAMINA);
	luaEngine->setGlobalInt("ACTION", CreatureAttribute::ACTION);
	luaEngine->setGlobalInt("STRENGTH", CreatureAttribute::STRENGTH);
	luaEngine->setGlobalInt("QUICKNESS", CreatureAttribute::QUICKNESS);
	luaEngine->setGlobalInt("MIND", CreatureAttribute::MIND);
	luaEngine->setGlobalInt("FOCUS", CreatureAttribute::FOCUS);
	luaEngine->setGlobalInt("WILLPOWER", CreatureAttribute::WILLPOWER);

	luaEngine->setGlobalInt("POISONED", CreatureState::POISONED);
	luaEngine->setGlobalInt("DISEASED", CreatureState::DISEASED);
	luaEngine->setGlobalInt("ONFIRE", CreatureState::ONFIRE);
	luaEngine->setGlobalInt("BLEEDING", CreatureState::BLEEDING);
	luaEngine->setGlobalInt("PEACE", CreatureState::PEACE);

	luaEngine->setGlobalInt("NONE", CreatureFlag::NONE);
	luaEngine->setGlobalInt("ATTACKABLE", CreatureFlag::ATTACKABLE);
	luaEngine->setGlobalInt("AGGRESSIVE", CreatureFlag::AGGRESSIVE);
	luaEngine->setGlobalInt("OVERT", CreatureFlag::OVERT);
	luaEngine->setGlobalInt("TEF", CreatureFlag::TEF);
	luaEngine->setGlobalInt("PLAYER", CreatureFlag::PLAYER);
	luaEngine->setGlobalInt("ENEMY", CreatureFlag::ENEMY);
	luaEngine->setGlobalInt("CHANGEFACTIONSTATUS", CreatureFlag::CHANGEFACTIONSTATUS);
	luaEngine->setGlobalInt("BLINK_GREEN", CreatureFlag::BLINK_GREEN);

	luaEngine->setGlobalInt("OPEN", ContainerPermissions::OPEN);
	luaEngine->setGlobalInt("MOVEIN", ContainerPermissions::MOVEIN);
	luaEngine->setGlobalInt("MOVEOUT", ContainerPermissions::MOVEOUT);
	luaEngine->setGlobalInt("WALKIN", ContainerPermissions::WALKIN);

	// Transfer Error Codes
	luaEngine->setGlobalInt("TRANSFERCANADD", TransferErrorCode::SUCCESS);
	luaEngine->setGlobalInt("TRANSFERCANTADD", TransferErrorCode::CANTADD);
	luaEngine->setGlobalInt("TRANSFERCANTREMOVE", TransferErrorCode::CANTREMOVE);
	luaEngine->setGlobalInt("TRANSFERSUCCESS", 1);
	luaEngine->setGlobalInt("TRANSFERFAIL", 0);

	// NPC reaction chat types / states
	luaEngine->setGlobalInt("REACTION_HI", ReactionManager::HI);
	luaEngine->setGlobalInt("REACTION_BYE", ReactionManager::BYE);
	luaEngine->setGlobalInt("REACTION_NICE", ReactionManager::NICE);
	luaEngine->setGlobalInt("REACTION_MID", ReactionManager::MID);
	luaEngine->setGlobalInt("REACTION_MEAN", ReactionManager::MEAN);

	// Badges
	VectorMap<unsigned int, const Badge*>* badges = BadgeList::instance()->getMap();
	const int vectorSize = badges->size();
	for (int i = 0; i < vectorSize;i++) {
		const Badge* badge = badges->get(i);
		String val = badge->getKey().toUpperCase();
		luaEngine->setGlobalInt(val, badge->getIndex());
	}

	// SUI Window Types (WIP)
	luaEngine->setGlobalInt("NEWSNET_INFO", SuiWindowType::NEWSNET_INFO);

	Luna<LuaCellObject>::Register(luaEngine->getLuaState());
	Luna<LuaBuildingObject>::Register(luaEngine->getLuaState());
	Luna<LuaCreatureObject>::Register(luaEngine->getLuaState());
	Luna<LuaSceneObject>::Register(luaEngine->getLuaState());
	Luna<LuaConversationScreen>::Register(luaEngine->getLuaState());
	Luna<LuaConversationSession>::Register(luaEngine->getLuaState());
	Luna<LuaConversationTemplate>::Register(luaEngine->getLuaState());
	Luna<LuaIntangibleObject>::Register(luaEngine->getLuaState());
	Luna<LuaControlDevice>::Register(luaEngine->getLuaState());
	Luna<LuaPlayerObject>::Register(luaEngine->getLuaState());
	Luna<LuaAiAgent>::Register(luaEngine->getLuaState());
	Luna<LuaActiveArea>::Register(luaEngine->getLuaState());
	Luna<LuaTangibleObject>::Register(luaEngine->getLuaState());
	Luna<LuaSuiManager>::Register(luaEngine->getLuaState());
	Luna<LuaSuiBox>::Register(luaEngine->getLuaState());
	Luna<LuaObjectMenuResponse>::Register(luaEngine->getLuaState());
	Luna<LuaDeed>::Register(luaEngine->getLuaState());
	Luna<LuaCityRegion>::Register(luaEngine->getLuaState());
	Luna<LuaStringIdChatParameter>::Register(luaEngine->getLuaState());
	Luna<LuaTicketObject>::Register(luaEngine->getLuaState());
}

int DirectorManager::loadScreenPlays(Lua* luaEngine) {
	bool res = luaEngine->runFile("scripts/screenplays/screenplays.lua");

	if (!DEBUG_MODE)
		info("Loaded " + String::valueOf(instance()->screenPlays.size()) + " screenplays.", true);

	if (!res)
		return 1;

	return 0;
}

int DirectorManager::writeScreenPlayData(lua_State* L) {
	if (checkArgumentCount(L, 4) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::writeScreenPlayData");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String data = lua_tostring(L, -1);
	String variable = lua_tostring(L, -2);
	String screenPlay = lua_tostring(L, -3);

	SceneObject* player = (SceneObject*) lua_touserdata(L, -4);

	if (player == NULL || !player->isPlayerCreature()) {
		DirectorManager::instance()->error("Attempted to write screen play data to a non-player Scene Object in screen play: " + screenPlay + ".");
		return 0;
	}

	Reference<PlayerObject*> ghost = player->getSlottedObject("ghost").castTo<PlayerObject*>();
	ghost->setScreenPlayData(screenPlay, variable, data);

	return 0;
}

int DirectorManager::createLoot(lua_State* L) {
	if (checkArgumentCount(L, 4) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::createLoot");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	SceneObject* container = (SceneObject*)lua_touserdata(L, -4);
	String lootGroup = lua_tostring(L, -3);
	int level = lua_tonumber(L, -2);
	bool maxCondition = lua_toboolean(L, -1);

	if (container == NULL || lootGroup == "")
		return 0;

	LootManager* lootManager = ServerCore::getZoneServer()->getLootManager();
	lootManager->createLoot(container, lootGroup, level, maxCondition);

	return 0;
}

int DirectorManager::createLootSet(lua_State* L) {
	if (checkArgumentCount(L,5) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::createLootSet");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	SceneObject* container = (SceneObject*)lua_touserdata(L, -5);
	String lootGroup = lua_tostring(L, -4);
	int level = lua_tonumber(L, -3);
	bool maxCondition = lua_toboolean(L, -2);
	int setSize = lua_tonumber(L, -1);

	if (container == NULL || lootGroup == "")
		return 0;

	LootManager* lootManager = ServerCore::getZoneServer()->getLootManager();
	lootManager->createLootSet(container, lootGroup, level, maxCondition, setSize);

	return 0;
}

int DirectorManager::createLootFromCollection(lua_State* L) {
	if (checkArgumentCount(L, 3) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::createLootFromCollection");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	SceneObject* container = (SceneObject*)lua_touserdata(L, -3);

	if (container == NULL)
		return 0;

	int level = lua_tonumber(L, -1);
	lua_pop(L, 1);

	LuaObject luaObject(L);

	LootGroupCollection lootCollection;
	lootCollection.readObject(&luaObject, level);

	luaObject.pop();

	LootManager* lootManager = ServerCore::getZoneServer()->getLootManager();
	lootManager->createLootFromCollection(container, &lootCollection, level);

	return 0;
}

int DirectorManager::getTimestamp(lua_State* L) {
	Time now;
	lua_pushinteger(L, now.getTime());

	return 1;
}

int DirectorManager::getTimestampMilli(lua_State* L) {
	Time now;
	lua_pushinteger(L, now.getMiliTime());

	return 1;
}

int DirectorManager::getFormattedTime(lua_State* L) {
	Time now;
	lua_pushstring(L, now.getFormattedTime().toCharArray());

	return 1;
}

int DirectorManager::readScreenPlayData(lua_State* L) {
	if (checkArgumentCount(L, 3) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::readScreenPlayData");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String variable = lua_tostring(L, -1);
	String screenPlay = lua_tostring(L, -2);
	SceneObject* player = (SceneObject*) lua_touserdata(L, -3);

	if (player == NULL || !player->isPlayerCreature()) {
		DirectorManager::instance()->error("Attempted to read screen play data from a non-player Scene Object in screen play: " + screenPlay + ".");
		return 0;
	}

	Reference<PlayerObject*> ghost = player->getSlottedObject("ghost").castTo<PlayerObject*>();

	//readScreenPlayData(player, screenPlay, variable)

	lua_pushstring(L, ghost->getScreenPlayData(screenPlay, variable).toCharArray());

	return 1;
}

int DirectorManager::deleteScreenPlayData(lua_State* L) {
	if (checkArgumentCount(L, 3) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::deleteScreenPlayData");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String variable = lua_tostring(L, -1);
	String screenPlay = lua_tostring(L, -2);
	SceneObject* player = (SceneObject*) lua_touserdata(L, -3);

	if (player == NULL || !player->isPlayerCreature()) {
		DirectorManager::instance()->error("Attempted to delete screen play data from a non-player Scene Object in screen play: " + screenPlay + ".");
		return 0;
	}

	Reference<PlayerObject*> ghost = player->getSlottedObject("ghost").castTo<PlayerObject*>();

	ghost->deleteScreenPlayData(screenPlay, variable);

	return 0;
}

int DirectorManager::clearScreenPlayData(lua_State* L) {
	if (checkArgumentCount(L, 2) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::clearScreenPlayData");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String screenPlay = lua_tostring(L, -1);
	SceneObject* player = (SceneObject*) lua_touserdata(L, -2);

	if (player == NULL || !player->isPlayerCreature()) {
		DirectorManager::instance()->error("Attempted to clear screen play data from a non-player Scene Object in screen play: " + screenPlay + ".");
		return 0;
	}

	Reference<PlayerObject*> ghost = player->getSlottedObject("ghost").castTo<PlayerObject*>();

	ghost->clearScreenPlayData(screenPlay);

	return 0;
}

int DirectorManager::registerScreenPlay(lua_State* L) {
	if (checkArgumentCount(L, 2) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::registerScreenPlay");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String name = lua_tostring(L, -2);
	bool start = lua_toboolean(L, -1);

	instance()->wlock();

	instance()->screenPlays.put(name, start);

	instance()->unlock();

	return 0;
}

int DirectorManager::checkInt64Lua(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::checkInt64Lua");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	uint64 data = lua_tointeger(L, -1);

	uint64 bigNumber = 0x01000000;
	bigNumber += bigNumber << 32;

	if (data < bigNumber) {
		instance()->error("Lua not using lnum patch with 64 bit integers, please patch lua!!");
	} else {
		instance()->info("Lua reads int64", true);
	}

	lua_pop(L, 1);

	return 0;
}

int DirectorManager::includeFile(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::includeFile");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String filename = Lua::getStringParameter(L);

	int oldError = ERROR_CODE;

	bool ret = Lua::runFile("scripts/screenplays/" + filename, L);

	if (!ret) {
		ERROR_CODE = GENERAL_ERROR;

		DirectorManager::instance()->error("running file: scripts/screenplays/" + filename);
	} else if (!oldError && ERROR_CODE) {
		DirectorManager::instance()->error("running file: scripts/screenplays/" + filename);
	}

	return 0;
}

int DirectorManager::readSharedMemory(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::readSharedMemory");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

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
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::deleteSharedMemory");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String key = Lua::getStringParameter(L);

#ifndef WITH_STM
	DirectorManager::instance()->wlock();
#endif

	DirectorManager::instance()->sharedMemory->remove(key);

#ifndef WITH_STM
	DirectorManager::instance()->unlock();
#endif

	return 0;
}

int DirectorManager::writeSharedMemory(lua_State* L) {
	if (checkArgumentCount(L, 2) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::writeSharedMemory");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

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



int DirectorManager::readStringSharedMemory(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::readStringSharedMemory");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String key = Lua::getStringParameter(L);

#ifndef WITH_STM
	DirectorManager::instance()->rlock();
#endif

	String data = DirectorManager::instance()->sharedMemory->getString(key);

#ifndef WITH_STM
	DirectorManager::instance()->runlock();
#endif

	lua_pushstring(L, data.toCharArray());

	return 1;
}

int DirectorManager::deleteStringSharedMemory(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::deleteStringSharedMemory");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String key = Lua::getStringParameter(L);

#ifndef WITH_STM
	DirectorManager::instance()->wlock();
#endif

	DirectorManager::instance()->sharedMemory->removeString(key);

#ifndef WITH_STM
	DirectorManager::instance()->unlock();
#endif

	return 0;
}

int DirectorManager::writeStringSharedMemory(lua_State* L) {
	if (checkArgumentCount(L, 2) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::writeStringSharedMemory");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String key = lua_tostring(L, -2);
	String data = lua_tostring(L, -1);

#ifndef WITH_STM
	DirectorManager::instance()->wlock();
#endif

	DirectorManager::instance()->sharedMemory->putString(key, data);

#ifndef WITH_STM
	DirectorManager::instance()->unlock();
#endif

	return 0;
}

int DirectorManager::createEvent(lua_State* L) {
	if (checkArgumentCount(L, 4) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::createEvent");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	SceneObject* obj = (SceneObject*) lua_touserdata(L, -1);
	String key = lua_tostring(L, -2);
	String play = lua_tostring(L, -3);
	uint32 mili = lua_tonumber(L, -4);

	int parameterCount = lua_gettop(L);

	//System::out << "scheduling task with mili:" << mili << endl;

	Reference<ScreenPlayTask*> task = new ScreenPlayTask(obj, key, play);

	if (parameterCount > 4) {
		bool save = lua_toboolean(L, -5);

		if (save && obj != NULL) {
			Time expireTime;
			uint64 currentTime = expireTime.getMiliTime();

			Reference<PersistentEvent*> pevent = new PersistentEvent();
			pevent->setObject(obj);
			pevent->setKey(key);
			pevent->setScreenplay(play);
			pevent->setTimeStamp(mili);
			pevent->setCurTime(currentTime);

			StringBuffer eventName;
			eventName << key << ":" << play << obj->getObjectID();

			String eventStringName = eventName.toString();

			pevent->setEventName(eventStringName);

			ObjectManager::instance()->persistObject(pevent, 1, "events");

			task->setPersistentEvent(pevent.get());

			if (persistentEvents.put(eventStringName.hashCode(), pevent) != NULL) {
				instance()->error("Duplicate persistent event for " + eventStringName);
			}
		}

		task->schedule(mili);
	} else {
		task->schedule(mili);
	}

	return 0;
}

int DirectorManager::createEventActualTime(lua_State* L) {
	if (checkArgumentCount(L, 3) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::createEventActualTime");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	SceneObject* obj = (SceneObject*) NULL;
	String key = lua_tostring(L, -1);
	String play = lua_tostring(L, -2);
	uint32 timeInMinutes = lua_tonumber(L, -3);
	ManagedReference<ScreenPlayTask*> task = new ScreenPlayTask(obj, key, play);
	Time actualTime = Time(timeInMinutes);
	Time now;
	uint64 days=now.getMiliTime()/(24*60*60000);
	uint64 dModifier = now.getMiliTime() - (days * (24*60*60000));
	uint64 interval =(24*60*60000);
	if (actualTime.getMiliTime()<= dModifier){
		interval =(24*60*60000) - (dModifier - actualTime.getMiliTime());
	}
	task->schedule(interval);
	return 0;
}

int DirectorManager::createServerEvent(lua_State* L) {
	if (checkArgumentCount(L, 4) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::createServerEvent");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String eventName = lua_tostring(L, -1);
	String key = lua_tostring(L, -2);
	String play = lua_tostring(L, -3);
	uint32 mili = lua_tonumber(L, -4);

	Reference<PersistentEvent*> pEvent = getServerEvent(eventName);

	if (pEvent != NULL) {
		instance()->error("Server event " + eventName + " already exists, exiting...");
		ERROR_CODE = GENERAL_ERROR;
		return 0;
	}

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime();

	Reference<ScreenPlayTask*> task = new ScreenPlayTask(NULL, key, play);

	Reference<PersistentEvent*> pevent = new PersistentEvent();
	pevent->setTimeStamp(mili);
	pevent->setCurTime(currentTime);
	pevent->setEventName(eventName);
	pevent->setKey(key);
	pevent->setScreenplay(play);

	if (persistentEvents.put(eventName.hashCode(), pevent) != NULL) {
		instance()->error("Persistent event with " + eventName + " already exists!");
	}

	task->setPersistentEvent(pevent);

	ObjectManager::instance()->persistObject(pevent, 1, "events");

	task->schedule(mili);

	lua_pushinteger(L, pevent->_getObjectID());

	return 1;
}

int DirectorManager::hasServerEvent(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::hasServerEvent");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String eventName = lua_tostring(L, -1);

	Reference<PersistentEvent*> pEvent = getServerEvent(eventName);

	if (pEvent != NULL)
		lua_pushboolean(L, true);
	else
		lua_pushboolean(L, false);

	return 1;
}

int DirectorManager::getServerEventTimeLeft(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getServerEventTimeLeft");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	uint64 objectID = lua_tointeger(L, -1);

	Reference<PersistentEvent*> pEvent = Core::getObjectBroker()->lookUp(objectID).castTo<PersistentEvent*>();

	if (pEvent == NULL)
		lua_pushnil(L);
	else {
		Time curTime;
		uint64 currentTime = curTime.getMiliTime();
		int origTime = pEvent->getCurTime();
		int timeStamp = pEvent->getTimeStamp();
		int timeLeft = origTime + timeStamp - currentTime;

		lua_pushinteger(L, timeLeft);
	}

	return 1;
}

void DirectorManager::dropServerEventReference(const String& eventName) {
	persistentEvents.remove(eventName.hashCode());
}

Reference<PersistentEvent*> DirectorManager::getServerEvent(const String& eventName) {
	return persistentEvents.get(eventName.hashCode());
}

int DirectorManager::getChatMessage(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getChatMessage");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	ChatMessage* cm = (ChatMessage*)lua_touserdata(L, -1);

	String text = "";

	if (cm != NULL)
		text = cm->toString();

	lua_pushstring(L, text.toCharArray());

	return 1;
}

int DirectorManager::spatialChat(lua_State* L) {
	if (checkArgumentCount(L, 2) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::spatialChat");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	ZoneServer* zoneServer = ServerCore::getZoneServer();
	ChatManager* chatManager = zoneServer->getChatManager();

	Reference<CreatureObject*> creature = (CreatureObject*)lua_touserdata(L, -2);

	if (lua_islightuserdata(L, -1)) {
		StringIdChatParameter* message = (StringIdChatParameter*)lua_touserdata(L, -1);

		if (creature != NULL && message != NULL) {
			StringIdChatParameter taskMessage = *message;

			EXECUTE_TASK_3(creature, chatManager, taskMessage, {
				Locker locker(creature_p);

				chatManager_p->broadcastMessage(creature_p, taskMessage_p, 0, 0, 0);
			});
		}
	} else {
		String message = lua_tostring(L, -1);

		if (creature != NULL) {
			EXECUTE_TASK_3(creature, chatManager, message, {
					Locker locker(creature_p);

					chatManager_p->broadcastMessage(creature_p, message_p, 0, 0, 0);
			});
		}
	}

	return 0;
}

int DirectorManager::spatialMoodChat(lua_State* L) {
	if (checkArgumentCount(L, 4) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::spatialMoodChat");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	ZoneServer* zoneServer = ServerCore::getZoneServer();
	ChatManager* chatManager = zoneServer->getChatManager();

	SceneObject* scene = (SceneObject*)lua_touserdata(L, -4);

	CreatureObject* creature = dynamic_cast<CreatureObject*>(scene);

	assert(creature);

	int moodType = lua_tonumber(L, -2);
	int chatType = lua_tonumber(L, -1);

	if (creature == NULL)
		return 0;

	Locker locker(creature);

	if (lua_isuserdata(L, -3)) {
		StringIdChatParameter* message = (StringIdChatParameter*)lua_touserdata(L, -3);

		chatManager->broadcastMessage(creature, *message, 0, moodType, chatType);
	} else {
		String message = lua_tostring(L, -3);

		chatManager->broadcastMessage(creature, message, 0, moodType, chatType);
	}

	return 0;
}

int DirectorManager::getSceneObject(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getSceneObject");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	uint64 objectID = lua_tointeger(L, -1);
	ZoneServer* zoneServer = ServerCore::getZoneServer();
	Reference<SceneObject*> object = zoneServer->getObject(objectID);

	if (object == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, object.get());
		object->_setUpdated(true); //mark updated so the GC doesnt delete it while in LUA
	}

	return 1;
}

int DirectorManager::getRandomNumber(lua_State* L) {
	int numberOfArguments = lua_gettop(L);
	if (numberOfArguments != 1 && numberOfArguments != 2) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getRandomNumber");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}
	int random;

	if (numberOfArguments == 1) {
		int max = lua_tointeger(L, -1);
		random = System::random(max - 1) + 1;
	} else {
		int min = lua_tointeger(L, -2);
		int max = lua_tointeger(L, -1);
		random = min + System::random(max - min);
	}
	lua_pushinteger(L, random);

	return 1;
}


int DirectorManager::getRegion(lua_State* L) {
	if (checkArgumentCount(L, 2) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getRegion");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

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
	else {
		spawnArea->_setUpdated(true); //mark updated so the GC doesnt delete it while in LUA
		lua_pushlightuserdata(L, spawnArea);
	}

	return 1;
}

int DirectorManager::getCreatureObject(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getCreatureObject");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	uint64 objectID = lua_tointeger(L, -1);
	ZoneServer* zoneServer = ServerCore::getZoneServer();
	Reference<SceneObject*> object = zoneServer->getObject(objectID);

	if (object != NULL && object->isCreatureObject()) {
		lua_pushlightuserdata(L, object.get());
		object->_setUpdated(true); //mark updated so the GC doesnt delete it while in LUA
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int DirectorManager::getContainerObjectByTemplate(lua_State* L) {
	if (checkArgumentCount(L, 3) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getContainerObjectByTemplate");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	SceneObject* container = (SceneObject*)lua_touserdata(L, -3);
	String objectTemplate = lua_tostring(L, -2);
	bool checkChildren = lua_toboolean(L, -1);

	uint32 objectCRC = objectTemplate.hashCode();

	if (container == NULL) {
		instance()->info("getContainerObjectByTemplate: SceneObject NULL", true);
		lua_pushnil(L);

		return 1;
	}

	SceneObject* sco = NULL;
	SceneObject* child = NULL;

	for (int i=0; i< container->getContainerObjectsSize(); i++) {
		sco = container->getContainerObject(i);

		if (sco == NULL)
			continue;

		if (sco->getServerObjectCRC() == objectCRC) {
			sco->_setUpdated(true); //mark updated so the GC doesnt delete it while in LUA
			lua_pushlightuserdata(L, sco);
			return 1;
		}

		if (checkChildren && sco->getContainerObjectsSize() > 0) {
			for (int j=0; j < sco->getContainerObjectsSize(); j++) {
				SceneObject* child = sco->getContainerObject(j);

				if (child == NULL)
					continue;

				if (child->getServerObjectCRC() == objectCRC) {
					child->_setUpdated(true); //mark updated so the GC doesnt delete it while in LUA
					lua_pushlightuserdata(L, child);
					return 1;
				}
			}
		}
	}

	lua_pushnil(L);

	return 1;
}

int DirectorManager::updateCellPermission(lua_State* L) {
	//realObject->info("getting values",true);
	if (checkArgumentCount(L, 3) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::updateCellPermission");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	SceneObject* sco = (SceneObject*)lua_touserdata(L, -3);
	bool allowEntry = lua_toboolean(L, -2);
	CreatureObject* obj = (CreatureObject*)lua_touserdata(L, -1);

	//sco->info("allowentry:" + String::valueOf(allowEntry), true);
	if (obj == NULL) {
		instance()->info("Object NULL", true);
		return 0;
	}


	//sco->info("values not NULL", true);

	if (sco == NULL) {
		obj->info("Cell NULL", true);
		return 0;
	}


	if (!sco->isCellObject()) {
		sco->info("Unknown entity error: Cell", true);
		return 0;
	}

	if (!obj->isCreatureObject()) {
		//sco->info("Unknown entity error: Creature", true);
		obj->info("Unknown entity error: Creature", true);
		return 0;
	}

	//sco->info("checks are fine", true);

	BaseMessage* perm = new UpdateCellPermissionsMessage(sco->getObjectID(), allowEntry);
	obj->sendMessage(perm);

	return 0;
}

int DirectorManager::updateCellPermissionGroup(lua_State* L) {
	if (checkArgumentCount(L, 3) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::updateCellPermissionGroup");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	//realObject->info("getting values",true);
	SceneObject* sco = (SceneObject*)lua_touserdata(L, -3);
	int allowEntry = lua_tonumber(L, -2);
	CreatureObject* obj = (CreatureObject*)lua_touserdata(L, -1);
	//realObject->info("allowentry:" + String::valueOf(allowEntry), true);
	if (obj == NULL)
		return 0;

	//realObject->info("values not NULL", true);

	if (!sco->isCellObject()) {
		sco->info("Unknown entity error: Cell", true);
		return 0;
	}

	if (!obj->isCreatureObject()) {
		//sco->info("Unknown entity error: Creature", true);
		obj->info("Unknown entity error: Creature", true);
		return 0;
	}

	BaseMessage* perm = new UpdateCellPermissionsMessage(sco->getObjectID(), allowEntry);

	//sco->info("checks are fine", true);
	if (obj->isGrouped()) {
		// do group
		GroupObject* group = obj->getGroup();
		if (group != NULL) {
			group->broadcastMessage(perm);
		}
	} else {
		// do single creature
		obj->sendMessage(perm);
	}

	return 0;
}

int DirectorManager::forcePeace(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::forcePeace");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	CreatureObject* creatureObject = (CreatureObject*)lua_touserdata(L, -1);

	if (creatureObject != NULL) {
		Locker locker(creatureObject);

		ThreatMap* threatMap = creatureObject->getThreatMap();

		if (threatMap != NULL)
			threatMap->removeAll();

		CombatManager::instance()->forcePeace(creatureObject);
	}

	return 0;
}

int DirectorManager::addStartingItemsInto(lua_State* L) {
	if (checkArgumentCount(L, 2) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::addStartingItemsInto");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	CreatureObject* creatureObject = (CreatureObject*)lua_touserdata(L, -2);
	SceneObject* sceneObject = (SceneObject*)lua_touserdata(L, -1);

	if (creatureObject != NULL && sceneObject != NULL) {
		PlayerCreationManager* pcm = PlayerCreationManager::instance();
		pcm->addStartingItemsInto(creatureObject, sceneObject);
	}

	return 0;
}

int DirectorManager::addStartingWeaponsInto(lua_State* L) {
	if (checkArgumentCount(L, 2) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::addStartingWeaponsInto");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

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
	if (checkArgumentCount(L, 3) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::giveItem");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	SceneObject* obj = (SceneObject*) lua_touserdata(L, -3);
	String objectString = lua_tostring(L, -2);
	int slot = lua_tointeger(L, -1);

	if (obj == NULL)
		return 0;

	ZoneServer* zoneServer = obj->getZoneServer();

	ManagedReference<SceneObject*> item = zoneServer->createObject(objectString.hashCode(), 1);

	if (item != NULL && obj != NULL) {
		if (obj->transferObject(item, slot, true)) {
			item->_setUpdated(true); //mark updated so the GC doesnt delete it while in LUA

			ManagedReference<SceneObject*> parent = item->getParentRecursively(SceneObjectType::PLAYERCREATURE);
			if (parent != NULL && parent->isPlayerCreature()) {
				item->sendTo(parent, true);
			}

			lua_pushlightuserdata(L, item.get());
		} else {
			item->destroyObjectFromDatabase(true);
			lua_pushnil(L);
		}
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int DirectorManager::giveControlDevice(lua_State* L) {
	if (checkArgumentCount(L, 5) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::giveControlDevice");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	SceneObject* datapad = (SceneObject*) lua_touserdata(L, -5);
	String objectString = lua_tostring(L, -4);
	String controlledObjectPath = lua_tostring(L, -3);
	int slot = lua_tointeger(L, -2);
	bool mobile = lua_toboolean(L, -1);

	if (datapad == NULL) {
		lua_pushnil(L);
		return 1;
	}

	ZoneServer* zoneServer = datapad->getZoneServer();
	Zone* zone = datapad->getZone();

	if (zone == NULL) {
		lua_pushnil(L);
		return 1;
	}

	ManagedReference<ControlDevice*> controlDevice = zoneServer->createObject(objectString.hashCode(), 1).castTo<ControlDevice*>();

	if (controlDevice == NULL) {
		lua_pushnil(L);
		return 1;
	}

	Locker locker(controlDevice);

	ManagedReference<TangibleObject*> controlledObject = NULL;
	ManagedReference<CreatureObject*> player = (datapad->getParent().get()).castTo<CreatureObject*>();

	if (mobile) {
		CreatureManager* creatureManager = zone->getCreatureManager();
		CreatureTemplate* creoTempl = CreatureTemplateManager::instance()->getTemplate(controlledObjectPath.hashCode());

		if (creoTempl == NULL) {
			controlDevice->destroyObjectFromDatabase(true);
			lua_pushnil(L);
			return 1;
		}

		String templateToSpawn = creatureManager->getTemplateToSpawn(controlledObjectPath.hashCode());
		controlledObject = creatureManager->createCreature(templateToSpawn.hashCode(), true, controlledObjectPath.hashCode());

		if (controlledObject == NULL) {
			controlDevice->destroyObjectFromDatabase(true);
			lua_pushnil(L);
			return 1;
		}

		Locker locker2(controlledObject);

		if (!controlledObject->isAiAgent()) {
			controlDevice->destroyObjectFromDatabase(true);
			controlledObject->destroyObjectFromDatabase(true);
			lua_pushnil(L);
			return 1;
		}

		AiAgent* pet = controlledObject.castTo<AiAgent*>();
		pet->loadTemplateData(creoTempl);

	} else {
		controlledObject = zoneServer->createObject(controlledObjectPath.hashCode(), 1).castTo<TangibleObject*>();

		if (controlledObject == NULL) {
			controlDevice->destroyObjectFromDatabase(true);
			lua_pushnil(L);
			return 1;
		}

		Locker locker2(controlledObject);

		SharedObjectTemplate* temp = controlledObject->getObjectTemplate();
		controlledObject->loadTemplateData(temp);
	}

	controlDevice->setControlledObject(controlledObject);
	StringId s;
	s.setStringId(controlledObject->getObjectName()->getFullPath());
	controlDevice->setObjectName(s);

	PetControlDevice* petControlDevice = cast<PetControlDevice*>(controlDevice.get());
	if( petControlDevice != NULL ){
		petControlDevice->setDefaultCommands();
	}

	if (datapad->transferObject(controlDevice, slot, true)) {
		controlDevice->_setUpdated(true); //mark updated so the GC doesnt delete it while in LUA
		lua_pushlightuserdata(L, controlDevice.get());
	} else {
		controlDevice->destroyObjectFromDatabase(true);
		lua_pushnil(L);
	}

	return 1;
}

int DirectorManager::checkTooManyHirelings(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::checkTooManyHirelings");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	SceneObject* datapad = (SceneObject*) lua_touserdata(L, -1);

	if (datapad == NULL) {
		lua_pushboolean(L, true);
		return 1;
	}

	int numberOfHirelings = 0;

	for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
		Reference<SceneObject*> object = datapad->getContainerObject(i);

		if (object != NULL && object->isPetControlDevice()) {
			PetControlDevice* device = object.castTo<PetControlDevice*>();

			if (device->getPetType() == PetManager::FACTIONPET)
				numberOfHirelings++;
		}
	}

	ManagedReference<PlayerManager*> playerManager = ServerCore::getZoneServer()->getPlayerManager();

	bool result = numberOfHirelings >= playerManager->getBaseStoredFactionPets();

	lua_pushboolean(L, result);

	return 1;
}

int DirectorManager::setAuthorizationState(lua_State* L) {
	if (checkArgumentCount(L, 2) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::setAuthorizationState");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

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
    int numberOfArguments = lua_gettop(L);
    if (numberOfArguments != 8 && numberOfArguments != 9) {
            instance()->error("incorrect number of arguments passed to DirectorManager::spawnMobile");
            ERROR_CODE = INCORRECT_ARGUMENTS;
            return 0;
    }

    bool randomRespawn = false;
    uint64 parentID;
    float x, y, z, heading;
    int respawnTimer;
    String mobile, zoneid;

    if (numberOfArguments == 8) {
    	parentID = lua_tointeger(L, -1);
		heading = lua_tonumber(L, -2);
		y = lua_tonumber(L, -3);
		z = lua_tonumber(L, -4);
		x = lua_tonumber(L, -5);
		respawnTimer = lua_tointeger(L, -6);
		mobile = lua_tostring(L, -7);
		zoneid = lua_tostring(L, -8);
    } else {
    	randomRespawn = lua_toboolean(L, -1);
    	parentID = lua_tointeger(L, -2);
		heading = lua_tonumber(L, -3);
		y = lua_tonumber(L, -4);
		z = lua_tonumber(L, -5);
		x = lua_tonumber(L, -6);
		respawnTimer = lua_tointeger(L, -7);
		mobile = lua_tostring(L, -8);
		zoneid = lua_tostring(L, -9);
    }

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
		instance()->error("could not spawn mobile " + mobile);

		lua_pushnil(L);
	} else {
		Locker locker(creature);

		creature->updateDirection(Math::deg2rad(heading));

		if (creature->isAiAgent()) {
			AiAgent* ai = cast<AiAgent*>(creature);
			ai->setRespawnTimer(respawnTimer);

			if (randomRespawn)
				ai->setRandomRespawn(true);

			// TODO (dannuic): this is a temporary measure until we add an AI setting method to DirectorManager -- make stationary the default
			ai->activateLoad("stationary");
		}

		creature->_setUpdated(true); //mark updated so the GC doesnt delete it while in LUA
		lua_pushlightuserdata(L, creature);
	}

	return 1;
	//public native CreatureObject spawnCreature(unsigned int templateCRC, float x, float z, float y, unsigned long parentID = 0);
}

int DirectorManager::spawnBuilding(lua_State* L) {
	int numberOfArguments = lua_gettop(L);
	if (numberOfArguments != 5) {
		instance()->error("incorrect number of arguments passed to DirectorManager::spawnBuilding");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	float x, y, angle;
	uint64 parentID;
	String script, zoneID;

	angle = lua_tointeger(L, -1);
	y = lua_tonumber(L, -2);
	x = lua_tonumber(L, -3);
	script = lua_tostring(L, -4);
	CreatureObject* creature = (CreatureObject*)lua_touserdata(L, -5);

	SharedStructureObjectTemplate* serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(TemplateManager::instance()->getTemplate(script.hashCode()));

	if (serverTemplate == NULL) {
		instance()->error("Unable to find template for building " + script);
		lua_pushnil(L);
	} else {
		StructureObject* structure = StructureManager::instance()->placeStructure(creature, script, x, y, 0, 0);
		if (structure == NULL) {
			instance()->error("Unable to spawn building " + script);
			lua_pushnil(L);
		} else {
			structure->_setUpdated(true);
			lua_pushlightuserdata(L, structure);
		}
	}
	return 1;
}

int DirectorManager::destroyBuilding(lua_State* L) {
       int numberOfArguments = lua_gettop(L);
       if (numberOfArguments != 1) {
               instance()->error("incorrect number of arguments passed to DirectorManager::destroyBuilding");
               ERROR_CODE = INCORRECT_ARGUMENTS;
               return 0;
       }
       uint64 objectID = lua_tointeger(L, -1);
       ZoneServer* zoneServer = ServerCore::getZoneServer();
       Reference<SceneObject*> object = zoneServer->getObject(objectID);

       if (object == NULL)
               return 0;

       ManagedReference<StructureObject*> building = object.castTo<StructureObject*>();

       if (building == NULL || !building->isStructureObject())
               return 0;

       Reference<Task*> pendingTask = building->getPendingTask("destruction");

       if (pendingTask != NULL)
               return 0;

       Reference<DestroyStructureTask*> task = new DestroyStructureTask(building);
       task->execute();
       return 1;
}

int DirectorManager::spawnSceneObject(lua_State* L) {
	int numberOfArguments = lua_gettop(L);
	if (numberOfArguments != 10 && numberOfArguments != 7) {
		instance()->error("incorrect number of arguments passed to DirectorManager::spawnSceneObject");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	float dz, dy, dx, dw, x, y, z;
	uint64 parentID;
	String script, zoneID;

	if (numberOfArguments == 10) {
		dz = lua_tonumber(L, -1);
		dy = lua_tonumber(L, -2);
		dx = lua_tonumber(L, -3);
		dw = lua_tonumber(L, -4);
		parentID = lua_tointeger(L, -5);
		y = lua_tonumber(L, -6);
		z = lua_tonumber(L, -7);
		x = lua_tonumber(L, -8);
		script = lua_tostring(L, -9);
		zoneID = lua_tostring(L, -10);
	} else {
		Quaternion direction;
		direction.setHeadingDirection(lua_tonumber(L, -1));
		dz = direction.getZ();
		dy = direction.getY();
		dx = direction.getX();
		dw = direction.getW();
		parentID = lua_tointeger(L, -2);
		y = lua_tonumber(L, -3);
		z = lua_tonumber(L, -4);
		x = lua_tonumber(L, -5);
		script = lua_tostring(L, -6);
		zoneID = lua_tostring(L, -7);
	}

	ZoneServer* zoneServer = ServerCore::getZoneServer();
	Zone* zone = zoneServer->getZone(zoneID);

	if (zone == NULL) {
		lua_pushnil(L);
		return 1;
	}

	ManagedReference<SceneObject*> object = zoneServer->createObject(script.hashCode(), 0);

	if (object != NULL) {
		Locker objLocker(object);

		object->initializePosition(x, z, y);
		object->setDirection(dw, dx, dy, dz);

		Reference<SceneObject*> cellParent = NULL;

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

		object->createChildObjects();

		object->_setUpdated(true); //mark updated so the GC doesnt delete it while in LUA

		lua_pushlightuserdata(L, object.get());
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int DirectorManager::spawnActiveArea(lua_State* L) {
	int numberOfArguments = lua_gettop(L);
	if (numberOfArguments != 7) {
		instance()->error("incorrect number of arguments passed to DirectorManager::spawnActiveArea");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	uint64 cellID = lua_tointeger(L, -1);
	int radius = lua_tointeger(L, -2);
	float y = lua_tonumber(L, -3);
	float z = lua_tonumber(L, -4);
	float x = lua_tonumber(L, -5);
	String script = lua_tostring(L, -6);
	String zoneID = lua_tostring(L, -7);

	ZoneServer* zoneServer = ServerCore::getZoneServer();
	Zone* zone = zoneServer->getZone(zoneID);

	if (zone == NULL) {
		lua_pushnil(L);
		return 1;
	}

	ManagedReference<SceneObject*> object = zoneServer->createObject(script.hashCode(), 0);

	if (object != NULL && object->isActiveArea()) {
		ActiveArea* area = object.castTo<ActiveArea*>();

		if (area == NULL) {
			lua_pushnil(L);
			return 1;
		}

		Locker locker(area);

		area->initializePosition(x, z, y);
		area->setRadius(radius);

		Reference<SceneObject*> cellParent = NULL;

		if (cellID != 0) {
			cellParent = zoneServer->getObject(cellID);

			if (cellParent == NULL || !cellParent->isCellObject()) {
				cellID = 0;
			}
		}

		area->setCellObjectID(cellID);

		Locker zoneLocker(zone);
		
		zone->transferObject(area, -1, true);

		area->_setUpdated(true); //mark updated so the GC doesnt delete it while in LUA

		lua_pushlightuserdata(L, area);
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int DirectorManager::createObserver(lua_State* L) {
	int numberOfArguments = lua_gettop(L);
	if (numberOfArguments != 4 && numberOfArguments != 5) {
		instance()->error("incorrect number of arguments passed to DirectorManager::createObserver");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	SceneObject* sceneObject;
	String key, play;
	uint32 eventType;
	int persistence = 0;

	if (numberOfArguments == 4) {
		sceneObject = (SceneObject*) lua_touserdata(L, -1);
		key = lua_tostring(L, -2);
		play = lua_tostring(L, -3);
		eventType = lua_tointeger(L, -4);
	} else {
		persistence = lua_tointeger(L, -1);
		sceneObject = (SceneObject*) lua_touserdata(L, -2);
		key = lua_tostring(L, -3);
		play = lua_tostring(L, -4);
		eventType = lua_tointeger(L, -5);
	}

	if (sceneObject == NULL)
		return 0;

	ManagedReference<ScreenPlayObserver*> observer = dynamic_cast<ScreenPlayObserver*>(ObjectManager::instance()->createObject("ScreenPlayObserver", persistence, ""));
	observer->setScreenPlay(play);
	observer->setScreenKey(key);
	observer->setObserverType(ObserverType::SCREENPLAY);

	sceneObject->registerObserver(eventType, observer);

	return 0;
}

int DirectorManager::dropObserver(lua_State* L) {
	if (checkArgumentCount(L, 2) > 0) {
		instance()->error("incorrect number of arguments passed to DirectorManager::dropObserver");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	SceneObject* sceneObject = (SceneObject*) lua_touserdata(L, -1);
	uint32 eventType = lua_tonumber(L, -2);

	if (sceneObject == NULL)
		return 0;

	SortedVector<ManagedReference<Observer* > > observers = sceneObject->getObservers(eventType);
	for (int i = 0; i < observers.size(); i++) {
		Observer* observer = observers.get(i).get();
		if (observer != NULL && observer->isObserverType(ObserverType::SCREENPLAY)) {
			sceneObject->dropObserver(eventType, observer);

			if (observer->isPersistent())
				ObjectManager::instance()->destroyObjectFromDatabase(observer->_getObjectID());
		}
	}

	return 0;
}

Lua* DirectorManager::getLuaInstance() {
	Lua* lua = localLua.get();

	if (lua == NULL) {
		lua = new Lua();
		initializeLuaEngine(lua);
		loadScreenPlays(lua);
		JediManager::instance()->loadConfiguration(lua);
		AiMap::instance()->initialize(lua);
		if (!AiMap::instance()->isLoaded())
			AiMap::instance()->loadTemplates(lua);

		localLua.set(lua);
	}

	return lua;
}

int DirectorManager::runScreenPlays() {
	Lua* lua = localLua.get();
	int ret = 0;

	if (lua == NULL) {
		lua = new Lua();
		initializeLuaEngine(lua);
		ret = loadScreenPlays(lua);
		JediManager::instance()->loadConfiguration(lua);
		AiMap::instance()->initialize(lua);
		if (!AiMap::instance()->isLoaded())
			AiMap::instance()->loadTemplates(lua);

		localLua.set(lua);
	}

	return ret || ERROR_CODE;
}

void DirectorManager::startScreenPlay(CreatureObject* creatureObject, const String& screenPlayName) {
	Lua* lua = getLuaInstance();

	LuaFunction startScreenPlay(lua->getLuaState(), screenPlayName, "start", 0);
	startScreenPlay << creatureObject;

	startScreenPlay.callFunction();
}

ConversationScreen* DirectorManager::getNextConversationScreen(const String& luaClass, ConversationTemplate* conversationTemplate, CreatureObject* conversingPlayer, int selectedOption, CreatureObject* conversingNPC) {
	Lua* lua = getLuaInstance();

	LuaFunction runMethod(lua->getLuaState(), luaClass, "getNextConversationScreen", 1);
	runMethod << conversationTemplate;
	runMethod << conversingPlayer;
	runMethod << selectedOption;
	runMethod << conversingNPC;

	runMethod.callFunction();

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

	runMethod.callFunction();

	ConversationScreen* result = (ConversationScreen*) lua_touserdata(lua->getLuaState(), -1);

	lua_pop(lua->getLuaState(), 1);

	return result;
}

void DirectorManager::activateEvent(ScreenPlayTask* task) {
	Reference<SceneObject*> obj = task->getSceneObject();
	String play = task->getScreenPlay();
	String key = task->getTaskKey();

	Reference<PersistentEvent*> persistentEvent = task->getPersistentEvent();

	if (persistentEvent != NULL) {
		persistentEvent->setEventExecuted(true);

		dropServerEventReference(persistentEvent->getEventName());

		ObjectManager::instance()->destroyObjectFromDatabase(persistentEvent->_getObjectID());
	} /*else {
		StringBuffer msg;
		msg << "no PersistentEvent object in the task " << play << ":" << task;

		error(msg.toString());
	}*/

	Lua* lua = getLuaInstance();

	try {
		LuaFunction startScreenPlay(lua->getLuaState(), play, key, 0);
		startScreenPlay << obj;

		startScreenPlay.callFunction();
	} catch (Exception& e) {
		StringBuffer msg;
		msg << "exception while running lua task " << play << ":" << key;
		error(msg.toString());

		e.printStackTrace();
	}
}

int DirectorManager::createConversationScreen(lua_State* L) {
	ConversationScreen* screen = new ConversationScreen();

	lua_pushlightuserdata(L, screen);

	return 1;
}

int DirectorManager::getStringId(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getStringId");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String stringid = lua_tostring(L, -1);
	String stringvalue = StringIdManager::instance()->getStringId(stringid.hashCode()).toString();
	lua_pushstring(L, stringvalue.toCharArray());

	return 1;
}

int DirectorManager::getRankName(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getRankName");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	int rank = lua_tointeger(L, -1);

	String rankName = FactionManager::instance()->getRankName(rank);

	lua_pushstring(L, rankName.toCharArray());

	return 1;
}

int DirectorManager::getRankCost(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getRankCost");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	int rank = lua_tointeger(L, -1);

	lua_pushinteger(L, FactionManager::instance()->getRankCost(rank));

	return 1;
}

int DirectorManager::getRankDelegateRatioFrom(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getRankDelegateRatioFrom");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	int rank = lua_tointeger(L, -1);

	lua_pushinteger(L, FactionManager::instance()->getRankDelegateRatioFrom(rank));

	return 1;
}

int DirectorManager::getRankDelegateRatioTo(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getRankDelegateRatioTo");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	int rank = lua_tointeger(L, -1);

	lua_pushinteger(L, FactionManager::instance()->getRankDelegateRatioTo(rank));

	return 1;
}

int DirectorManager::isHighestRank(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::isHighestRank");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	int rank = lua_tointeger(L, -1);

	bool result = FactionManager::instance()->isHighestRank(rank);

	lua_pushboolean(L, result);

	return 1;
}

int DirectorManager::getFactionPointsCap(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getFactionPointsCap");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	int rank = lua_tointeger(L, -1);

	lua_pushinteger(L, FactionManager::instance()->getFactionPointsCap(rank));

	return 1;
}

int DirectorManager::getObjectTemplatePathByCRC(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getObjectTemplatePathByCRC");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	uint32 crc = lua_tointeger(L, -1);

	lua_pushstring(L, TemplateManager::instance()->getTemplateFile(crc).toCharArray());

	return 1;
}

int DirectorManager::getZoneByName(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getZoneByName");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String zoneid = lua_tostring(L, -1);

	Zone* zone = ServerCore::getZoneServer()->getZone(zoneid);

	if (zone == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, zone);
	}

	return 1;
}

int DirectorManager::isZoneEnabled(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::isZoneEnabled");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String zoneid = lua_tostring(L, -1);

	Zone* zone = ServerCore::getZoneServer()->getZone(zoneid);

	lua_pushboolean(L, (zone != NULL));

	return 1;
}

Vector3 DirectorManager::generateSpawnPoint(String zoneName, float x, float y, float minimumDistance, float maximumDistance, float extraNoBuildRadius, float sphereCollision, bool forceSpawn) {
	bool found = false;
	Vector3 position(0, 0, 0);
	int retries = 40;
	ZoneServer* zoneServer = ServerCore::getZoneServer();
	Zone* zone = zoneServer->getZone(zoneName);

	if (zone == NULL) {
		return position;
	}

	while (!found && retries > 0) {
		float distance = minimumDistance + System::random(maximumDistance - minimumDistance);
		float angle = System::random(360);
		float newAngle = angle * (M_PI / 180.0f);

		float newX = x + (cos(newAngle) * distance); // client has x/y inverted
		float newY = y + (sin(newAngle) * distance);
		float newZ = zone->getHeight(newX, newY);

		position = Vector3(newX, newY, newZ);


		found = forceSpawn == true || (zone->getPlanetManager()->isSpawningPermittedAt(position.getX(), position.getY(), extraNoBuildRadius) &&
				!CollisionManager::checkSphereCollision(position, sphereCollision, zone));

		retries--;
	}

	if (!found) {
		position = Vector3(0, 0, 0);
	}

	return position;
}

int DirectorManager::getSpawnPoint(lua_State* L) {
    int numberOfArguments = lua_gettop(L);
    if (numberOfArguments != 5 && numberOfArguments != 6) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getSpawnArea");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

    float maximumDistance, minimumDistance, y, x;
    CreatureObject* creatureObject;
    bool forceSpawn = false;

    if (numberOfArguments == 5) {
    	maximumDistance = lua_tonumber(L, -1);
		minimumDistance = lua_tonumber(L, -2);
		y = lua_tonumber(L, -3);
		x = lua_tonumber(L, -4);
		creatureObject = (CreatureObject*) lua_touserdata(L, -5);
    } else {
    	forceSpawn = lua_toboolean(L, -1);
    	maximumDistance = lua_tonumber(L, -2);
		minimumDistance = lua_tonumber(L, -3);
		y = lua_tonumber(L, -4);
		x = lua_tonumber(L, -5);
		creatureObject = (CreatureObject*) lua_touserdata(L, -6);
    }

	if (creatureObject == NULL || creatureObject->getZone() == NULL) {
		return 0;
	}

	Vector3 position = generateSpawnPoint(creatureObject->getZone()->getZoneName(), x, y, minimumDistance, maximumDistance, 5.0, 20, forceSpawn);

	if (position != Vector3(0, 0, 0)) {
		lua_newtable(L);
		lua_pushnumber(L, position.getX());
		lua_pushnumber(L, position.getZ());
		lua_pushnumber(L, position.getY());
		lua_rawseti(L, -4, 3);
		lua_rawseti(L, -3, 2);
		lua_rawseti(L, -2, 1);

		return 1;
	} else {
		instance()->error("Unable to generate spawn point in DirectorManager::getSpawnPoint");
		return 0;
	}
}

int DirectorManager::getSpawnArea(lua_State* L) {
    int numberOfArguments = lua_gettop(L);
    if (numberOfArguments != 7 && numberOfArguments != 8) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getSpawnArea");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

    float maximumHeightDifference, areaSize, maximumDistance, minimumDistance, y, x;
    Zone* zone = NULL;

    if (numberOfArguments == 8) {
    	String zoneName = lua_tostring(L, -1);
    	maximumHeightDifference = lua_tonumber(L, -2);
    	areaSize = lua_tonumber(L, -3);
    	maximumDistance = lua_tonumber(L, -4);
    	minimumDistance = lua_tonumber(L, -5);
    	y = lua_tonumber(L, -6);
    	x = lua_tonumber(L, -7);
    	CreatureObject* creatureObject = (CreatureObject*) lua_touserdata(L, -8);

    	ZoneServer* zoneServer = ServerCore::getZoneServer();
    	zone = zoneServer->getZone(zoneName);
    } else {
    	maximumHeightDifference = lua_tonumber(L, -1);
    	areaSize = lua_tonumber(L, -2);
    	maximumDistance = lua_tonumber(L, -3);
    	minimumDistance = lua_tonumber(L, -4);
    	y = lua_tonumber(L, -5);
    	x = lua_tonumber(L, -6);
    	CreatureObject* creatureObject = (CreatureObject*) lua_touserdata(L, -7);

    	if (creatureObject == NULL) {
    		return 0;
    	}

    	zone = creatureObject->getZone();
    }

	if (zone == NULL) {
		return 0;
	}

	bool found = false;
	Vector3 position;
	int retries = 40;

	while (!found && retries > 0) {
		position = generateSpawnPoint(zone->getZoneName(), x, y, minimumDistance, maximumDistance, areaSize + 5.0, areaSize + 20);

		int x0 = position.getX() - areaSize;
		int x1 = position.getX() + areaSize;
		int y0 = position.getY() - areaSize;
		int y1 = position.getY() + areaSize;

		found = zone->getPlanetManager()->getTerrainManager()->getHighestHeightDifference(x0, y0, x1, y1) <= maximumHeightDifference;
		retries--;
	}

	if (found) {
		lua_newtable(L);
		lua_pushnumber(L, position.getX());
		lua_pushnumber(L, position.getZ());
		lua_pushnumber(L, position.getY());
		lua_rawseti(L, -4, 3);
		lua_rawseti(L, -3, 2);
		lua_rawseti(L, -2, 1);

		return 1;
	} else {
		return 0;
	}
}

int DirectorManager::makeCreatureName(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::makeCreatureName");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	bool surname = lua_toboolean(L, -1);

	NameManager* nameManager = NameManager::instance();
	String name = nameManager->makeCreatureName(surname);

	lua_pushstring(L, name.toCharArray());
	return 1;
}


int DirectorManager::getGCWDiscount(lua_State* L){
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getGCWDiscount");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	CreatureObject* creature = (CreatureObject*)lua_touserdata(L, -1);

	if(creature == NULL || creature->getZone() == NULL)
		return 0;

	GCWManager* gcwMan = creature->getZone()->getGCWManager();

	if(gcwMan == 0)
		return 0;

	lua_pushnumber(L, gcwMan->getGCWDiscount(creature));
	return 1;
}

int DirectorManager::getTerrainHeight(lua_State* L){
	if (checkArgumentCount(L, 3) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getGCWDiscount");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	float y = lua_tonumber(L, -1);
	float x = lua_tonumber(L, -2);
	CreatureObject* creatureObject = (CreatureObject*) lua_touserdata(L, -3);

	if(creatureObject == NULL || creatureObject->getZone() == NULL)
		return 0;

	lua_pushnumber(L, creatureObject->getZone()->getHeight(x, y));
	return 1;
}

int DirectorManager::checkArgumentCount(lua_State* L, int args) {
	int parameterCount = lua_gettop(L);

	if (parameterCount < args) {
		return 1;
	} else if (parameterCount > args)
		return 2;

	return 0;
}

int DirectorManager::awardSkill(lua_State* L) {
	if (checkArgumentCount(L, 2) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::awardSkill");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	CreatureObject* creature = (CreatureObject*)lua_touserdata(L, -2);
	String skillName = lua_tostring(L, -1);

	if(creature == NULL)
		return 0;

	SkillManager::instance()->awardSkill(skillName, creature, true, false, true);

	return 0;
}

int DirectorManager::getCityRegionAt(lua_State* L) {
	if (checkArgumentCount(L, 3) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getCityRegionAt");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String zoneid = lua_tostring(L, -3);
	float x = lua_tonumber(L, -2);
	float y = lua_tonumber(L, -1);

	PlanetManager* planetManager = ServerCore::getZoneServer()->getZone(zoneid)->getPlanetManager();

	CityRegion* cityRegion = planetManager->getRegionAt(x, y);

	if (cityRegion != NULL) {
		lua_pushlightuserdata(L, cityRegion);
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int DirectorManager::setDungeonTicketAttributes(lua_State* L) {
	if (checkArgumentCount(L, 4) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::setDungeonTicketAttributes");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	SceneObject* scene = (SceneObject*) lua_touserdata(L, -4);
	String ticketDepartPlanet = lua_tostring(L, -3);
	String ticketDepartPoint = lua_tostring(L, -2);
	String ticketArrivePoint = lua_tostring(L, -1);


	if (scene == NULL)
		return 0;

	ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(scene);

	TicketObject* tObj = tano.castTo<TicketObject*>();

	tObj->setDeparturePlanet(ticketDepartPlanet);
	tObj->setDeparturePoint(ticketDepartPoint);
	tObj->setArrivalPoint(ticketArrivePoint);

	return 0;
}

int DirectorManager::setQuestStatus(lua_State* L) {
	if (checkArgumentCount(L, 2) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::setQuestStatus");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String valueString = lua_tostring(L, -1);
	String keyString = lua_tostring(L, -2);

	instance()->setQuestStatus(keyString, valueString);

	return 0;
}

int DirectorManager::getQuestStatus(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getQuestStatus");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String keyString = lua_tostring(L, -1);

	String str = instance()->getQuestStatus(keyString);

	if (str == "")
		lua_pushnil(L);
	else
		lua_pushstring(L, str.toCharArray());

	return 1;
}

int DirectorManager::removeQuestStatus(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::removeQuestStatus");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String keyString = lua_tostring(L, -1);

	instance()->removeQuestStatus(keyString);

	return 0;
}

int DirectorManager::getControllingFaction(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to DirectorManager::getControllingFaction");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String zoneName = lua_tostring(L, -1);

	Zone* zone = ServerCore::getZoneServer()->getZone(zoneName);

	if (zone == NULL) {
		lua_pushnil(L);
	} else {
		GCWManager* gcwMan = zone->getGCWManager();

		if (gcwMan == NULL) {
			lua_pushnil(L);
		} else {
			lua_pushinteger(L, gcwMan->getWinningFaction());
		}
	}
	return 1;
}

int DirectorManager::playClientEffectLoc(lua_State* L) {
	uint64 playerId = lua_tointeger(L, -7);
	String effect = lua_tostring(L, -6);
	String zone = lua_tostring(L, -5);
	float x = lua_tonumber(L, -4);
	float z = lua_tonumber(L, -3);
	float y = lua_tonumber(L, -2);
	int cell = lua_tonumber(L, -1);

	ZoneServer* zoneServer = ServerCore::getZoneServer();

	ManagedReference<CreatureObject*> creature = zoneServer->getObject(playerId).castTo<CreatureObject*>();

	if (creature == NULL)
		return 0;

	PlayClientEffectLoc* effectLoc = new PlayClientEffectLoc(effect, zone, x, z, y, cell);
	creature->broadcastMessage(effectLoc, true);

	return 1;
}
