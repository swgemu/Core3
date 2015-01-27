/*
 * PlayerManagerImplementation.cpp
 *
 *  Created on: 18/07/2009
 *      Author: TheAnswer
 */

#include "server/zone/managers/player/PlayerManager.h"

#include "server/login/account/Account.h"
#include "server/zone/packets/charcreation/ClientCreateCharacter.h"
#include "server/zone/packets/charcreation/ClientCreateCharacterCallback.h"
#include "server/zone/packets/charcreation/ClientCreateCharacterSuccess.h"
#include "server/zone/packets/charcreation/ClientCreateCharacterFailed.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/faction/FactionManager.h"
#include "server/db/ServerDatabase.h"
#include "server/db/MantisDatabase.h"
#include "server/chat/ChatManager.h"
#include "server/conf/ConfigManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/player/VeteranRewardList.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/skill/Performance.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/objects/intangible/VehicleControlDevice.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/login/packets/ErrorMessage.h"
#include "server/zone/packets/player/LogoutMessage.h"
#include "server/zone/objects/player/sessions/TradeSession.h"
#include "server/zone/objects/player/sessions/ProposeUnitySession.h"
#include "server/zone/objects/player/sessions/VeteranRewardSession.h"
#include "server/zone/objects/tangible/OptionBitmask.h"

#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/ship/ShipObject.h"

#include "server/zone/objects/group/GroupObject.h"

#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/templates/tangible/CloningBuildingObjectTemplate.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/wearables/WearableObject.h"

#include "server/zone/objects/player/events/PlayerIncapacitationRecoverTask.h"
#include "server/zone/objects/creature/events/ProposeUnityExpiredTask.h"
#include "server/zone/objects/player/events/ForceMeditateTask.h"
#include "server/zone/objects/player/events/MeditateTask.h"
#include "server/zone/objects/player/events/LogoutTask.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"

#include "server/zone/objects/building/cloning/CloneSpawnPoint.h"

#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/managers/skill/SkillManager.h"

#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/managers/planet/PlanetManager.h"

#include "server/zone/packets/trade/AbortTradeMessage.h"
#include "server/zone/packets/trade/AcceptTransactionMessage.h"
#include "server/zone/packets/trade/UnAcceptTransactionMessage.h"
#include "server/zone/packets/trade/AddItemMessage.h"
#include "server/zone/packets/trade/BeginTradeMessage.h"
#include "server/zone/packets/trade/DenyTradeMessage.h"
#include "server/zone/packets/trade/TradeCompleteMessage.h"
#include "server/zone/packets/trade/GiveMoneyMessage.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/packets/tangible/UpdatePVPStatusMessage.h"

#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"
#include "server/zone/packets/player/PlayerObjectDeltaMessage6.h"
#include "server/zone/packets/object/StartingLocationListMessage.h"

#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/director/DirectorManager.h"

#include "server/zone/objects/player/sui/callbacks/CloningRequestSuiCallback.h"

#include "server/zone/objects/tangible/tool/CraftingStation.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"

#include "server/zone/Zone.h"
#include "server/zone/managers/player/creation/PlayerCreationManager.h"
#include "server/ServerCore.h"

#include "server/login/account/Account.h"

#include "server/zone/objects/player/sui/callbacks/PlayerTeachSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/PlayerTeachConfirmSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/ProposeUnitySuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/SelectUnityRingSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/ConfirmDivorceSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/SelectVeteranRewardSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/ConfirmVeteranRewardSuiCallback.h"

#include "server/zone/managers/stringid/StringIdManager.h"

#include "server/zone/objects/creature/buffs/PowerBoostBuff.h"

#include "server/zone/objects/creature/Creature.h"
#include "server/zone/objects/creature/events/DespawnCreatureTask.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/managers/gcw/GCWManager.h"

#include "server/zone/managers/creature/LairObserver.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/managers/creature/PetManager.h"

#include "server/zone/objects/creature/events/BurstRunNotifyAvailableEvent.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/objects/tangible/components/droid/DroidPlaybackModuleDataComponent.h"

#include <iostream>

int PlayerManagerImplementation::MAX_CHAR_ONLINE_COUNT = 2;

PlayerManagerImplementation::PlayerManagerImplementation(ZoneServer* zoneServer, ZoneProcessServer* impl) :
										Logger("PlayerManager") {
	server = zoneServer;
	processor = impl;

	playerMap = new PlayerMap(3000);
	nameMap = new CharacterNameMap();

	DirectorManager::instance()->getLuaInstance()->runFile("scripts/screenplays/checklnum.lua");

	loadLuaConfig();
	loadStartingLocations();
	loadBadgeMap();
	loadPermissionLevels();

	setGlobalLogging(true);
	setLogging(false);

	if (ServerCore::truncateDatabases()) {
		try {
			String query = "TRUNCATE TABLE characters";

			Reference<ResultSet*> res = ServerDatabase::instance()->executeQuery(query);

			info("characters table truncated", true);
		} catch (Exception& e) {
			error(e.getMessage());
		}
	}

	loadNameMap();
}

bool PlayerManagerImplementation::createPlayer(MessageCallback* data) {
	PlayerCreationManager* pcm = PlayerCreationManager::instance();
	return pcm->createCharacter(data);
}

void PlayerManagerImplementation::loadLuaConfig() {
	info("Loading configuration script.");

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/player_manager.lua");

	performanceBuff = lua->getGlobalInt("performanceBuff");
	medicalBuff = lua->getGlobalInt("medicalBuff");
	performanceDuration = lua->getGlobalInt("performanceDuration");
	medicalDuration = lua->getGlobalInt("medicalDuration");

	groupExpMultiplier = lua->getGlobalFloat("groupExpMultiplier");

	globalExpMultiplier = lua->getGlobalFloat("globalExpMultiplier");

	baseStoredCreaturePets = lua->getGlobalInt("baseStoredCreaturePets");
	baseStoredFactionPets = lua->getGlobalInt("baseStoredFactionPets");
	baseStoredDroids = lua->getGlobalInt("baseStoredDroids");
	baseStoredVehicles = lua->getGlobalInt("baseStoredVehicles");
	baseStoredShips = lua->getGlobalInt("baseStoredShips");


	LuaObject rewardMilestonesLua = lua->getGlobalObject("veteranRewardMilestones");
	for (int i = 1; i <= rewardMilestonesLua.getTableSize(); ++i) {
		veteranRewardMilestones.add(rewardMilestonesLua.getIntAt(i));
	}
	rewardMilestonesLua.pop();

	LuaObject rewardsListLua = lua->getGlobalObject("veteranRewards");
	int size = rewardsListLua.getTableSize();

	lua_State* L = rewardsListLua.getLuaState();

	for (int i = 0; i < size; ++i) {
		lua_rawgeti(L, -1, i + 1);
		LuaObject a(L);

		VeteranReward reward;
		reward.parseFromLua(&a);
		veteranRewards.add(reward);

		a.pop();
	}

	rewardsListLua.pop();

	info("Loaded " + String::valueOf(veteranRewards.size()) + " veteran rewards.", true);

	delete lua;
	lua = NULL;
}

void PlayerManagerImplementation::loadStartingLocations() {
	info("Loading starting locations.");

	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/creation/starting_locations.iff");

	if (iffStream == NULL) {
		info("Couldn't load starting locations.", true);
		return;
	}

	startingLocationList.parseFromIffStream(iffStream);

	delete iffStream;

	info("Loaded " + String::valueOf(startingLocationList.getTotalLocations()) + " starting locations.", true);
}

void PlayerManagerImplementation::loadBadgeMap() {
	info("Loading badges.");

	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/badge/badge_map.iff");

	if (iffStream == NULL) {
		info("Couldn't load badge map.", true);
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	highestBadgeIndex = 0;

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		int idx = 0;
		String key;

		DataTableRow* row = dtiff.getRow(i);
		row->getCell(0)->getValue(idx);
		row->getCell(1)->getValue(key);
		badgeMap.put(idx, key);

		if (idx > highestBadgeIndex)
			highestBadgeIndex = idx;
	}

	info("Loaded " + String::valueOf(badgeMap.size()) + " badges.", true);

	delete iffStream;
}

void PlayerManagerImplementation::loadPermissionLevels() {
	try {
		permissionLevelList = PermissionLevelList::instance();
		permissionLevelList->loadLevels();
	}
	catch(Exception& e) {
		error("Couldn't load permission levels.");
		error(e.getMessage());
	}


}

void PlayerManagerImplementation::finalize() {
	delete playerMap;
	playerMap = NULL;

	delete nameMap;
	nameMap = NULL;
}

void PlayerManagerImplementation::loadNameMap() {
	info("loading character names");

	try {
		String query = "SELECT * FROM characters where character_oid > 16777216 and galaxy_id = " + String::valueOf(server->getGalaxyID()) + " order by character_oid asc";

		Reference<ResultSet*> res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {
			uint64 oid = res->getUnsignedLong(0);
			String firstName = res->getString(3);

			if (!nameMap->put(firstName.toLowerCase(), oid)) {
				error("error coliding name:" + firstName.toLowerCase());
			}
		}

	} catch (Exception& e) {
		error(e.getMessage());
	}

	StringBuffer msg;
	msg << "loaded " << nameMap->size() << " character names in memory";
	info(msg.toString(), true);
}

bool PlayerManagerImplementation::existsName(const String& name) {
	bool res = false;

	rlock();

	try {
		res = nameMap->containsKey(name.toLowerCase());
	} catch (DatabaseException& e) {
		error(e.getMessage());
	}

	runlock();

	return res;
}


bool PlayerManagerImplementation::kickUser(const String& name, const String& admin, String& reason, bool doBan) {
	ManagedReference<ChatManager*> chatManager = server->getChatManager();

	if (chatManager == NULL)
		return false;

	ManagedReference<CreatureObject*> player = chatManager->getPlayer(name);

	if (player == NULL)
		return false;

	ManagedReference<CreatureObject*> adminplayer = chatManager->getPlayer(admin);

	if (adminplayer == NULL)
		return false;

	Reference<PlayerObject*> ghost = player->getSlottedObject("ghost").castTo<PlayerObject*>();


	Reference<PlayerObject*> adminghost = adminplayer->getSlottedObject("ghost").castTo<PlayerObject*>();

	if(adminghost == NULL)
		return false;

	StringBuffer kickMessage;
	kickMessage << "You have been kicked by " << admin << " for '" << reason << "'";
	player->sendSystemMessage(kickMessage.toString());

	if(ghost != NULL)
		ghost->setLoggingOut();

	ErrorMessage* errmsg = new ErrorMessage(admin, "You have been kicked", 0);
	player->sendMessage(errmsg);

	player->sendMessage(new LogoutMessage());

	ManagedReference<ZoneClientSession*> session = player->getClient();

	if(session != NULL)
		session->disconnect(true);

	/// 10 min ban
	if(doBan) {
		String banMessage = banAccount(adminghost, getAccount(ghost->getAccountID()), 60 * 10, reason);
		adminplayer->sendSystemMessage(banMessage);
	}

	return true;
}

Reference<CreatureObject*> PlayerManagerImplementation::getPlayer(const String& name) {
	uint64 oid = 0;

	rlock();

	oid = nameMap->get(name.toLowerCase());

	runlock();

	if (oid == 0)
		return NULL;

	Reference<SceneObject*> obj = server->getObject(oid);

	if (obj == NULL || !obj->isPlayerCreature())
		return NULL;

	return obj.castTo<CreatureObject*>();
}

uint64 PlayerManagerImplementation::getObjectID(const String& name) {
	uint64 oid = 0;

	rlock();

	oid = nameMap->get(name.toLowerCase());

	runlock();

	return oid;
}

bool PlayerManagerImplementation::checkExistentNameInDatabase(const String& name) {
	if (name.isEmpty())
		return false;

	try {
		String fname = name.toLowerCase();
		Database::escapeString(fname);
		String query = "SELECT * FROM characters WHERE lower(firstname) = \""
				+ fname + "\"";

		Reference<ResultSet*> res = ServerDatabase::instance()->executeQuery(query);
		bool nameExists = res->next();

		return !nameExists;
	} catch (DatabaseException& e) {
		return false;
	}

	return false;
}

bool PlayerManagerImplementation::checkPlayerName(MessageCallback* messageCallback) {
	ClientCreateCharacterCallback* callback = cast<ClientCreateCharacterCallback*>( messageCallback);
	ZoneClientSession* client = callback->getClient();

	NameManager* nm = processor->getNameManager();
	BaseMessage* msg = NULL;

	String firstName;

	UnicodeString unicodeName;
	callback->getCharacterName(unicodeName);

	String name = unicodeName.toString();

	//Get the firstname
	int idx = name.indexOf(" ");
	if (idx != -1)
		firstName = name.subString(0, idx);
	else
		firstName = name;

	//Does this name already exist?
	if (nameMap->containsKey(firstName.toLowerCase())) {
		msg = new ClientCreateCharacterFailed("name_declined_in_use");
		client->sendMessage(msg);

		return false;
	}

	//Check to see if name is valid
	int res = nm->validateName(name, callback->getSpecies());

	if (res != NameManagerResult::ACCEPTED) {
		switch (res) {
		case NameManagerResult::DECLINED_EMPTY:
			msg = new ClientCreateCharacterFailed("name_declined_empty");
			break;
		case NameManagerResult::DECLINED_DEVELOPER:
			msg = new ClientCreateCharacterFailed("name_declined_developer");
			break;
		case NameManagerResult::DECLINED_FICT_RESERVED:
			msg = new ClientCreateCharacterFailed("name_declined_fictionally_reserved");
			break;
		case NameManagerResult::DECLINED_PROFANE:
			msg = new ClientCreateCharacterFailed("name_declined_profane");
			break;
		case NameManagerResult::DECLINED_RACE_INAPP:
			msg = new ClientCreateCharacterFailed("name_declined_racially_inappropriate");
			break;
		case NameManagerResult::DECLINED_SYNTAX:
			msg = new ClientCreateCharacterFailed("name_declined_syntax");
			break;
		case NameManagerResult::DECLINED_RESERVED:
			msg = new ClientCreateCharacterFailed("name_declined_reserved");
			break;
		default:
			msg = new ClientCreateCharacterFailed("name_declined_retry");
			break;
		}

		client->sendMessage(msg); //Name failed filters
		return false;
	}

	return true;
}


Reference<TangibleObject*> PlayerManagerImplementation::createHairObject(const String& hairObjectFile, const String& hairCustomization) {
	Reference<TangibleObject*> hairObject = NULL;

	if (hairObjectFile.isEmpty()) {
		info("hairObjectFile empty");
		return NULL;
	}

	info("trying to create hair object " + hairObjectFile);
	Reference<SceneObject*> hair = server->createObject(hairObjectFile.hashCode(), 1);

	if (hair == NULL) {
		info("objectManager returned NULL hair object");
		return NULL;
	}

	if (hair->getGameObjectType() != SceneObjectType::GENERICITEM || hair->getArrangementDescriptor(0).get(0) != "hair") {
		ManagedReference<SceneObject*> clearRef = hair;

		return NULL;
	} else {
		hairObject = hair.castTo<TangibleObject*>();

		hairObject->setCustomizationString(hairCustomization);

		info("hair object created successfully");
	}

	return hairObject;
}

void PlayerManagerImplementation::createTutorialBuilding(CreatureObject* player) {
	Zone* zone = server->getZone("tutorial");

	String tut = "object/building/general/newbie_hall.iff";
	String cell = "object/cell/cell.iff";

	Reference<BuildingObject*> tutorial = server->createObject(tut.hashCode(), 1).castTo<BuildingObject*>();
	tutorial->createCellObjects();
	tutorial->setPublicStructure(true);

	tutorial->initializePosition(System::random(5000), 0, System::random(5000));
	zone->transferObject(tutorial, -1, true);

	SceneObject* cellTut = tutorial->getCell(11);

	SceneObject* cellTutPlayer = tutorial->getCell(1);

	player->initializePosition(0, 0, -3);

	cellTutPlayer->transferObject(player, -1);
	PlayerObject* ghost = player->getPlayerObject();
	ghost->setSavedTerrainName(zone->getZoneName());
	ghost->setSavedParentID(cellTutPlayer->getObjectID());

	tutorial->updateToDatabase();
}

void PlayerManagerImplementation::createSkippedTutorialBuilding(CreatureObject* player) {
	Zone* zone = server->getZone("tutorial");

	String tut = "object/building/general/newbie_hall_skipped.iff";
	String cell = "object/cell/cell.iff";

	Reference<BuildingObject*> tutorial = server->createObject(tut.hashCode(), 1).castTo<BuildingObject*>();
	tutorial->createCellObjects();
	tutorial->initializePosition(System::random(5000), 0, System::random(5000));
	zone->transferObject(tutorial, -1, true);

	Reference<SceneObject*> travelTutorialTerminal = server->createObject((uint32)String("object/tangible/beta/beta_terminal_warp.iff").hashCode(), 1);

	SceneObject* cellTut = tutorial->getCell(1);
	cellTut->transferObject(travelTutorialTerminal, -1);

	travelTutorialTerminal->initializePosition(27.0f, -3.5f, -168.0f);

	player->initializePosition(27.0f, -3.5f, -165.0f);
	cellTut->transferObject(player, -1);
	PlayerObject* ghost = player->getPlayerObject();
	ghost->setSavedTerrainName(zone->getZoneName());
	ghost->setSavedParentID(cellTut->getObjectID());

	tutorial->updateToDatabase();
}

uint8 PlayerManagerImplementation::calculateIncapacitationTimer(CreatureObject* playerCreature, int condition) {
	//Switch the sign of the value
	int32 value = -condition;

	if (value < 0)
		return 0;

	uint32 recoveryTime = (value / 5); //In seconds - 3 seconds is recoveryEvent timer

	//Recovery time is gated between 10 and 60 seconds.
	recoveryTime = MIN(MAX(recoveryTime, 10), 60);

	//Check for incap recovery food buff - overrides recovery time gate.
	/*if (hasBuff(BuffCRC::FOOD_INCAP_RECOVERY)) {
		Buff* buff = getBuff(BuffCRC::FOOD_INCAP_RECOVERY);

		if (buff != NULL) {
			float percent = buff->getSkillModifierValue("incap_recovery");

			recoveryTime = round(recoveryTime * ((100.0f - percent) / 100.0f));

			StfParameter* params = new StfParameter();
			params->addDI(percent);

			sendSystemMessage("combat_effects", "incap_recovery", params); //Incapacitation recovery time reduced by %DI%.
			delete params;

			removeBuff(buff);
		}
	}*/

	return recoveryTime;
}

int PlayerManagerImplementation::notifyDestruction(TangibleObject* destructor, TangibleObject* destructedObject, int condition) {
	if (!destructedObject->isPlayerCreature())
		return 1;

	CreatureObject* playerCreature = cast<CreatureObject*>( destructedObject);

	if (playerCreature->isIncapacitated() || playerCreature->isDead())
		return 1;

	if (playerCreature->isRidingMount()) {
		playerCreature->updateCooldownTimer("mount_dismount", 0);
		playerCreature->executeObjectControllerAction(String("dismount").hashCode());
	}

	playerCreature->clearDots();

	PlayerObject* ghost = playerCreature->getPlayerObject();

	ghost->updateIncapacitationCounter();

	destructor->removeDefender(destructedObject);

	if (!destructor->isKiller() && ghost->getIncapacitationCounter() < 3) {
		playerCreature->setCurrentSpeed(0);
		playerCreature->setPosture(CreaturePosture::INCAPACITATED, true);
		playerCreature->updateLocomotion();

		uint32 incapTime = calculateIncapacitationTimer(playerCreature, condition);
		playerCreature->setCountdownTimer(incapTime, true);

		Reference<Task*> oldTask = playerCreature->getPendingTask("incapacitationRecovery");

		if (oldTask != NULL && oldTask->isScheduled()) {
			oldTask->cancel();
			playerCreature->removePendingTask("incapacitationRecovery");
		}

		Reference<Task*> task = new PlayerIncapacitationRecoverTask(playerCreature, false);
		playerCreature->addPendingTask("incapacitationRecovery", task, incapTime * 1000);

		StringIdChatParameter stringId;

		if (destructor != NULL) {
			stringId.setStringId("base_player", "prose_victim_incap");
			stringId.setTT(destructor->getObjectID());
		} else {
			stringId.setStringId("base_player", "victim_incapacitated");
		}

		playerCreature->sendSystemMessage(stringId);

	} else {
		if (destructor->isKiller() || !ghost->isFirstIncapacitationExpired()) {
			killPlayer(destructor, playerCreature, 0);
		}
	}

	return 0;
}

void PlayerManagerImplementation::killPlayer(TangibleObject* attacker, CreatureObject* player, int typeofdeath) {
	StringIdChatParameter stringId;

	if (attacker->isPlayerCreature()) {
		stringId.setStringId("base_player", "prose_target_dead");
		stringId.setTT(player->getObjectID());
		(cast<CreatureObject*>(attacker))->sendSystemMessage(stringId);
	}

	if (player->isRidingMount()) {
		player->updateCooldownTimer("mount_dismount", 0);
		player->executeObjectControllerAction(String("dismount").hashCode());
	}

	player->setCurrentSpeed(0);
	player->setPosture(CreaturePosture::DEAD, true);
	player->updateLocomotion();

	sendActivateCloneRequest(player, typeofdeath);

	stringId.setStringId("base_player", "prose_victim_dead");
	stringId.setTT(attacker->getObjectID());
	player->sendSystemMessage(stringId);

	player->updateTimeOfDeath();
	player->clearBuffs(true);

	if (attacker->getFaction() != 0) {
		if (attacker->isPlayerCreature() || attacker->isPet()) {
			CreatureObject* attackerCreature = cast<CreatureObject*>(attacker);

			if (attackerCreature->isPet()) {
				CreatureObject* owner = attackerCreature->getLinkedCreature().get();

				if (owner != NULL && owner->isPlayerCreature()) {
					attackerCreature = owner;
				}
			}

			if (attackerCreature->isPlayerCreature()) {
				PlayerObject* attackerGhost = attackerCreature->getPlayerObject();
				PlayerObject* ghost = player->getPlayerObject();

				bool areInDuel = (ghost->requestedDuelTo(attackerCreature) && attackerGhost->requestedDuelTo(player));

				if (!areInDuel) {
					FactionManager::instance()->awardPvpFactionPoints(attackerCreature, player);
				}
			}
		}
	}

	CombatManager::instance()->freeDuelList(player, false);

	player->notifyObjectKillObservers(attacker);

	/*Reference<Task*> task = new PlayerIncapacitationRecoverTask(player, true);
	task->schedule(10 * 1000);*/
}

void PlayerManagerImplementation::sendActivateCloneRequest(CreatureObject* player, int typeofdeath) {
	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	ghost->removeSuiBoxType(SuiWindowType::CLONE_REQUEST);
	ghost->removeSuiBoxType(SuiWindowType::CLONE_REQUEST_DECAY);

	ManagedReference<SuiListBox*> cloneMenu = new SuiListBox(player, SuiWindowType::CLONE_REQUEST);
	cloneMenu->setCallback(new CloningRequestSuiCallback(player->getZoneServer(), typeofdeath));
	cloneMenu->setPromptTitle("@base_player:revive_title");

	/*
	if (typeofdeath == 1) {
		cloneMenu = new SuiListBox(player, SuiWindowType::CLONE_REQUEST);//no decay - GM command, deathblow or factional death
	} else if (typeofdeath == 0) {
		cloneMenu = new SuiListBox(player, SuiWindowType::CLONE_REQUEST_DECAY);
	} else if (ghost->getFactionStatus() == FactionStatus::OVERT) {//TODO: Do proper check if faction death
		cloneMenu = new SuiListBox(player, SuiWindowType::CLONE_REQUEST_FACTIONAL);
	}*/

	uint64 preDesignatedFacilityOid = ghost->getCloningFacility();
	ManagedReference<SceneObject*> preDesignatedFacility = server->getObject(preDesignatedFacilityOid);
	String predesignatedName = "None";

	//Get the name of the pre-designated facility
	if (preDesignatedFacility != NULL) {
		ManagedReference<CityRegion*> cr = preDesignatedFacility->getCityRegion();

		if (preDesignatedFacility->getZone() != zone) {
			predesignatedName = "off-planet (unavailable)";
		} else if (cr != NULL) {
			predesignatedName = cr->getRegionDisplayedName();
		} else {
			predesignatedName = preDesignatedFacility->getDisplayedName();
		}
	}

	SortedVector<ManagedReference<SceneObject*> > locations = zone->getPlanetaryObjectList("cloningfacility");
	ManagedReference<SceneObject*> closestCloning = zone->getNearestPlanetaryObject(player, "cloningfacility");
	if(closestCloning == NULL){
		warning("nearest cloning facility for player is NULL");
		return;
	}
	String closestName = "None";
	ManagedReference<CityRegion*> cr = closestCloning->getCityRegion();
	unsigned long long playerID = player->getObjectID();
	CloningBuildingObjectTemplate* cbot = cast<CloningBuildingObjectTemplate*>(closestCloning->getObjectTemplate());

	//Check if player is city banned where the closest facility is or if it's not a valid cloner
	if ((cr != NULL && cr->isBanned(playerID)) || cbot == NULL) {
		int distance = 50000;
		for (int j = 0; j < locations.size(); j++) {
			ManagedReference<SceneObject*> location = locations.get(j);

			if (location == NULL)
				continue;

			cbot = cast<CloningBuildingObjectTemplate*>(location->getObjectTemplate());

			if (cbot == NULL)
				continue;

			cr = location->getCityRegion();
			String name;

			if (cr != NULL) {
				if (cr->isBanned(playerID))
					continue;

				name = cr->getRegionDisplayedName();
			} else {
				name = location->getDisplayedName();
			}

			if (location->getDistanceTo(player) < distance) {
				distance = location->getDistanceTo(player);
				closestName = name;
				closestCloning = location;
			}
		}

	} else {
		if (cr != NULL)
			closestName = cr->getRegionDisplayedName();
		else
			closestName = closestCloning->getDisplayedName();
	}

	StringBuffer promptText;
	promptText << "Closest:\t\t " << closestName << "\n"
			<< "Pre-Designated: " << predesignatedName << "\n"
			<< "Cash Balance:\t " << player->getCashCredits() << "\n\n"
			<< "Select the desired option and click OK.";

	cloneMenu->setPromptText(promptText.toString());

	if (closestCloning != NULL)
		cloneMenu->addMenuItem("@base_player:revive_closest", closestCloning->getObjectID());

	if (preDesignatedFacility != NULL && preDesignatedFacility->getZone() == zone)
		cloneMenu->addMenuItem("@base_player:revive_bind", preDesignatedFacility->getObjectID());

	ghost->addSuiBox(cloneMenu);
	player->sendMessage(cloneMenu->generateMessage());
}

void PlayerManagerImplementation::sendPlayerToCloner(CreatureObject* player, uint64 clonerID, int typeofdeath) {
	ManagedReference<SceneObject*> cloner = server->getObject(clonerID);

	if (cloner == NULL) {
		error("Cloning structure is null");
		return;
	}

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)	{
		error("The player to be cloned is null");
		return;
	}


	CloningBuildingObjectTemplate* cbot = cast<CloningBuildingObjectTemplate*>(cloner->getObjectTemplate());

	if (cbot == NULL) {
		error("Not a cloning building template.");
		return;
	}

	BuildingObject* cloningBuilding = cloner.castTo<BuildingObject*>();

	if (cloningBuilding == NULL)  {
		error("Cloning building is null");
		return;
	}

	CloneSpawnPoint* clonePoint = cbot->getRandomSpawnPoint();

	if (clonePoint == NULL) {
		error("clone point null");
		return;
	}

	Coordinate* coordinate = clonePoint->getCoordinate();
	Quaternion* direction = clonePoint->getDirection();

	int cellID = clonePoint->getCellID();

	SceneObject* cell = cloningBuilding->getCell(cellID);

	if (cell == NULL) {
		StringBuffer msg;
		msg << "null cell for cellID " << cellID << " in building: " << cbot->getFullTemplateString();
		error(msg.toString());
		return;
	}

	Zone* zone = player->getZone();

	player->switchZone(zone->getZoneName(), coordinate->getPositionX(), coordinate->getPositionZ(), coordinate->getPositionY(), cell->getObjectID());

	uint64 preDesignatedFacilityOid = ghost->getCloningFacility();
	ManagedReference<SceneObject*> preDesignatedFacility = server->getObject(preDesignatedFacilityOid);

	if (preDesignatedFacility != NULL && preDesignatedFacility == cloningBuilding) {
		// bind removed
		player->sendSystemMessage("@base_player:bind_removed");
		ghost->setCloningFacility(NULL);
	} else {
		player->addWounds(CreatureAttribute::HEALTH, 100, true);
		player->addWounds(CreatureAttribute::ACTION, 100, true);
		player->addWounds(CreatureAttribute::MIND, 100, true);
	}

	player->addShockWounds(100, true);

	if (ghost->getFactionStatus() != FactionStatus::ONLEAVE)
		ghost->setFactionStatus(FactionStatus::ONLEAVE);

	// Decay
	if (typeofdeath == 0) {
		SortedVector<ManagedReference<SceneObject*> > insurableItems = getInsurableItems(player, false);

		for (int i = 0; i < insurableItems.size(); i++) {
			SceneObject* item = insurableItems.get(i);

			if (item != NULL && item->isTangibleObject()) {
				ManagedReference<TangibleObject*> obj = cast<TangibleObject*>(item);

				if (obj->getOptionsBitmask() & OptionBitmask::INSURED) {
					//1% Decay for insured items
					obj->inflictDamage(obj, 0, 0.01 * obj->getMaxCondition(), true, true);
					//Set uninsured
					uint32 bitmask = obj->getOptionsBitmask() - OptionBitmask::INSURED;
					obj->setOptionsBitmask(bitmask);
				} else {
					//5% Decay for uninsured items
					obj->inflictDamage(obj, 0, 0.05 * obj->getMaxCondition(), true, true);
				}
			}
		}
	}

	Reference<Task*> task = new PlayerIncapacitationRecoverTask(player, true);
	task->schedule(3 * 1000);

	player->notifyObservers(ObserverEventType::PLAYERCLONED, player, 0);

	// Jedi experience loss.
	if (ghost->getJediState() > 1)
		awardExperience(player, "jedi_general", -200000, true);
}

void PlayerManagerImplementation::ejectPlayerFromBuilding(CreatureObject* player) {
	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	ManagedReference<SceneObject*> parent = player->getParent();

	if (parent == NULL || !parent->isCellObject())
		return;

	ManagedReference<CellObject*> cell = cast<CellObject*>(parent.get());

	if (cell == NULL)
		return;

	ManagedReference<BuildingObject*> building = cell->getParent().castTo<BuildingObject*>();

	if (building == NULL)
		return;

	if (building->hasTemplateEjectionPoint()) {
		Vector3 ejectionPoint = building->getEjectionPoint();
		player->switchZone(zone->getZoneName(), ejectionPoint.getX(), ejectionPoint.getZ(), ejectionPoint.getY(), 0);
	}
}



void PlayerManagerImplementation::disseminateExperience(TangibleObject* destructedObject, ThreatMap* threatMap, Vector<ManagedReference<CreatureObject*> >* spawnedCreatures) {
	uint32 totalDamage = threatMap->getTotalDamage();

	VectorMap<ManagedReference<CreatureObject*>, int> slExperience;
	slExperience.setAllowOverwriteInsertPlan();
	slExperience.setNullValue(0);


	float gcwBonus = 1.0f;
	uint32 winningFaction = -1;
	int baseXp = 0;

	Zone* zone = destructedObject->getZone();
	if(zone != NULL){
		GCWManager* gcwMan = zone->getGCWManager();
		gcwBonus += (gcwMan->getGCWXPBonus() / 100.0f);
		winningFaction = gcwMan->getWinningFaction();
	}

	if (!destructedObject->isCreatureObject() && spawnedCreatures != NULL) {
		ManagedReference<AiAgent*> ai = NULL;

		for (int i = 0; i < spawnedCreatures->size(); i++) {
			ai = cast<AiAgent*>(spawnedCreatures->get(i).get());

			if (ai != NULL) {
				Creature* creature = cast<Creature*>(ai.get());

				if (creature != NULL && creature->isBaby())
					continue;
				else
					break;
			}
		}

		if (ai != NULL)
			baseXp = ai->getBaseXp();

	} else {
		ManagedReference<AiAgent*> ai = cast<AiAgent*>(destructedObject);

		if (ai != NULL)
			baseXp = ai->getBaseXp();
	}

	for (int i = 0; i < threatMap->size(); ++i) {

		CreatureObject* attacker = threatMap->elementAt(i).getKey();
		CreatureObject* owner = NULL;
		int totalPets = 1;

		if (attacker->isPet()) {
			PetControlDevice* pcd = attacker->getControlDevice().get().castTo<PetControlDevice*>();

			if (pcd == NULL || pcd->getPetType() != PetManager::CREATUREPET) {
				continue;
			}

			owner = attacker->getLinkedCreature().get();

			if (owner == NULL || !owner->isPlayerCreature() || !owner->hasSkill("outdoors_creaturehandler_novice"))
				continue;

			PlayerObject* ownerGhost = owner->getPlayerObject();

			if (ownerGhost == NULL)
				continue;

			for (int i = 0; i < ownerGhost->getActivePetsSize(); i++) {
				ManagedReference<AiAgent*> object = ownerGhost->getActivePet(i);

				if (object != NULL && object->isCreature()) {
					if (object == attacker)
						continue;

					PetControlDevice* petControlDevice = object->getControlDevice().get().castTo<PetControlDevice*>();
					if (petControlDevice != NULL && petControlDevice->getPetType() == PetManager::CREATUREPET)
						totalPets++;
				}
			}

		}

		if (!attacker->isPlayerCreature() && !attacker->isPet())
			continue;

		ManagedReference<GroupObject*> group = attacker->getGroup();

		ThreatMapEntry* entry = &threatMap->elementAt(i).getValue();

		uint32 combatXp = 0;

		for (int j = 0; j < entry->size(); ++j) {
			uint32 damage = entry->elementAt(j).getValue();
			String xpType = entry->elementAt(j).getKey();
			float xpAmount = baseXp;

			if (attacker->isPlayerCreature()) {
				xpAmount *= (float) damage / totalDamage;

				//Cap xp based on level
				xpAmount = MIN(xpAmount, calculatePlayerLevel(attacker, xpType) * 300.f);

			} else if (attacker->isPet()) {
				// TODO: Find a more correct CH xp formula
				float levelRatio = (float)destructedObject->getLevel() / (float)attacker->getLevel();

				xpAmount = (float)attacker->getLevel() * 25.f * levelRatio;

				xpAmount = MIN(xpAmount,attacker->getLevel() * 50.f);

				xpAmount /= totalPets;

				if (levelRatio <= 0.5)
					xpAmount = 1;
			}

			//Apply group bonus if in group
			if (group != NULL)
				xpAmount *= groupExpMultiplier;

			//Jedi experience doesn't count towards combat experience supposedly.
			if (xpType != "jedi_general")
				combatXp += xpAmount;

			if( winningFaction == attacker->getFaction()){
				xpAmount *= gcwBonus;
				combatXp *= gcwBonus;
			}
			//Award individual weapon exp.
			if (attacker->isPlayerCreature()) {
				Locker crossLocker(attacker, destructedObject);

				awardExperience(attacker, xpType, xpAmount);
			} else if (attacker->isPet()) {
				Locker crossLocker(owner, destructedObject);

				awardExperience(owner, xpType, xpAmount);
			}
		}

		if (attacker->isPet())
			continue;

		combatXp /= 10.f;

		Locker crossLocker(attacker, destructedObject);

		awardExperience(attacker, "combat_general", combatXp);

		//Check if the group leader is a squad leader
		if (group == NULL)
			continue;

		Vector3 pos(attacker->getWorldPositionX(), attacker->getWorldPositionY(), 0);

		crossLocker.release();

		ManagedReference<SceneObject*> groupLeader = group->getLeader();

		if (groupLeader == NULL || !groupLeader->isPlayerCreature())
			continue;

		CreatureObject* squadLeader = groupLeader.castTo<CreatureObject*>();

		Locker squadLock(squadLeader, destructedObject);

		//If he is a squad leader, and is in range of this player, then add the combat exp for him to use.
		if (squadLeader->hasSkill("outdoors_squadleader_novice") && pos.distanceTo(attacker->getWorldPosition()) <= 192.f) {
			int v = slExperience.get(squadLeader) + combatXp;
			slExperience.put(squadLeader, v);
		}
	}

	//Send out squad leader experience.
	for (int i = 0; i < slExperience.size(); ++i) {
		VectorMapEntry<ManagedReference<CreatureObject*>, int>* entry = &slExperience.elementAt(i);

		Locker clock(entry->getKey(), destructedObject);

		awardExperience(entry->getKey(), "squadleader", entry->getValue() * 2.f);
	}

	threatMap->removeAll();
}



bool PlayerManagerImplementation::checkEncumbrancies(CreatureObject* player, ArmorObject* armor) {
	int strength = player->getHAM(CreatureAttribute::STRENGTH);
	int constitution = player->getHAM(CreatureAttribute::CONSTITUTION);
	int quickness = player->getHAM(CreatureAttribute::QUICKNESS);
	int stamina = player->getHAM(CreatureAttribute::STAMINA);
	int focus = player->getHAM(CreatureAttribute::FOCUS);
	int willpower = player->getHAM(CreatureAttribute::WILLPOWER);

	int healthEncumb = armor->getHealthEncumbrance();
	int actionEncumb = armor->getActionEncumbrance();
	int mindEncumb = armor->getMindEncumbrance();

	if (healthEncumb >= strength || healthEncumb >= constitution ||
			actionEncumb >= quickness || actionEncumb >= stamina ||
			mindEncumb >= focus || mindEncumb >= willpower)
		return false;
	else
		return true;
}


void PlayerManagerImplementation::applyEncumbrancies(CreatureObject* player, ArmorObject* armor) {
	int healthEncumb = MAX(0, armor->getHealthEncumbrance());
	int actionEncumb = MAX(0, armor->getActionEncumbrance());
	int mindEncumb = MAX(0, armor->getMindEncumbrance());

	player->addEncumbrance(CreatureEncumbrance::HEALTH, healthEncumb, true);
	player->addEncumbrance(CreatureEncumbrance::ACTION, actionEncumb, true);
	player->addEncumbrance(CreatureEncumbrance::MIND, mindEncumb, true);

	player->inflictDamage(player, CreatureAttribute::STRENGTH, healthEncumb, true);
	player->addMaxHAM(CreatureAttribute::STRENGTH, -healthEncumb, true);

	player->inflictDamage(player, CreatureAttribute::CONSTITUTION, healthEncumb, true);
	player->addMaxHAM(CreatureAttribute::CONSTITUTION, -healthEncumb, true);

	player->inflictDamage(player, CreatureAttribute::QUICKNESS, actionEncumb, true);
	player->addMaxHAM(CreatureAttribute::QUICKNESS, -actionEncumb, true);

	player->inflictDamage(player, CreatureAttribute::STAMINA, actionEncumb, true);
	player->addMaxHAM(CreatureAttribute::STAMINA, -actionEncumb, true);

	player->inflictDamage(player, CreatureAttribute::FOCUS, mindEncumb, true);
	player->addMaxHAM(CreatureAttribute::FOCUS, -mindEncumb, true);

	player->inflictDamage(player, CreatureAttribute::WILLPOWER, mindEncumb, true);
	player->addMaxHAM(CreatureAttribute::WILLPOWER, -mindEncumb, true);
}

void PlayerManagerImplementation::removeEncumbrancies(CreatureObject* player, ArmorObject* armor) {
	int healthEncumb = MAX(0, armor->getHealthEncumbrance());
	int actionEncumb = MAX(0, armor->getActionEncumbrance());
	int mindEncumb = MAX(0, armor->getMindEncumbrance());

	player->addEncumbrance(CreatureEncumbrance::HEALTH, -healthEncumb, true);
	player->addEncumbrance(CreatureEncumbrance::ACTION, -actionEncumb, true);
	player->addEncumbrance(CreatureEncumbrance::MIND, -mindEncumb, true);

	player->addMaxHAM(CreatureAttribute::STRENGTH, healthEncumb, true);
	player->healDamage(player, CreatureAttribute::STRENGTH, healthEncumb, true);

	player->addMaxHAM(CreatureAttribute::CONSTITUTION, healthEncumb, true);
	player->healDamage(player, CreatureAttribute::CONSTITUTION, healthEncumb, true);

	player->addMaxHAM(CreatureAttribute::QUICKNESS, actionEncumb, true);
	player->healDamage(player, CreatureAttribute::QUICKNESS, actionEncumb, true);

	player->addMaxHAM(CreatureAttribute::STAMINA, actionEncumb, true);
	player->healDamage(player, CreatureAttribute::STAMINA, actionEncumb, true);

	player->addMaxHAM(CreatureAttribute::FOCUS, mindEncumb, true);
	player->healDamage(player, CreatureAttribute::FOCUS, mindEncumb, true);

	player->addMaxHAM(CreatureAttribute::WILLPOWER, mindEncumb, true);
	player->healDamage(player, CreatureAttribute::WILLPOWER, mindEncumb, true);
}


void PlayerManagerImplementation::awardBadge(PlayerObject* ghost, uint32 badge) {
	if (!Badge::exists(badge))
		return;

	StringIdChatParameter stringId("badge_n", "");
	stringId.setTO("badge_n", Badge::getName(badge));

	ManagedReference<CreatureObject*> player = dynamic_cast<CreatureObject*>(ghost->getParent().get().get());

	if (ghost->hasBadge(badge)) {
		stringId.setStringId("badge_n", "prose_hasbadge");
		player->sendSystemMessage(stringId);
		return;
	}

	ghost->setBadge(badge);
	stringId.setStringId("badge_n", "prose_grant");
	player->sendSystemMessage(stringId);

	player->notifyObservers(ObserverEventType::BADGEAWARDED, player, badge);

	switch (ghost->getNumBadges()) {
	case 5:
		awardBadge(ghost, Badge::COUNT_5);
		break;
	case 10:
		awardBadge(ghost, Badge::COUNT_10);
		break;
	case 25:
		awardBadge(ghost, Badge::COUNT_25);
		break;
	case 50:
		awardBadge(ghost, Badge::COUNT_50);
		break;
	case 75:
		awardBadge(ghost, Badge::COUNT_75);
		break;
	case 100:
		awardBadge(ghost, Badge::COUNT_100);
		break;
	case 125:
		awardBadge(ghost, Badge::COUNT_125);
		break;
	default:
		break;
	}

	if (Badge::getType(badge) == Badge::EXPLORATION) {
		switch (ghost->getBadgeTypeCount(Badge::EXPLORATION)) {
		case 10:
			awardBadge(ghost, Badge::BDG_EXP_10_BADGES);
			break;
		case 20:
			awardBadge(ghost, Badge::BDG_EXP_20_BADGES);
			break;
		case 30:
			awardBadge(ghost, Badge::BDG_EXP_30_BADGES);
			break;
		case 40:
			awardBadge(ghost, Badge::BDG_EXP_40_BADGES);
			break;
		case 45:
			awardBadge(ghost, Badge::BDG_EXP_45_BADGES);
			break;
		default:
			break;
		}
	}
}

void PlayerManagerImplementation::setExperienceMultiplier(float globalMultiplier) {
	globalExpMultiplier = globalMultiplier;
}

/*
 * Award experience to a player.
 * Ex.
	PlayerManager* playerManager = server->getPlayerManager();
	playerManager->awardExperience(playerCreature, "resource_harvesting_inorganic", 500);
 *
 */
void PlayerManagerImplementation::awardExperience(CreatureObject* player, const String& xpType,
		int amount, bool sendSystemMessage, float localMultiplier) {

	PlayerObject* playerObject = player->getPlayerObject();
	int xp = playerObject->addExperience(xpType, (int) (amount * localMultiplier * globalExpMultiplier));

	player->notifyObservers(ObserverEventType::XPAWARDED, player, xp);

	if (sendSystemMessage) {
		if (xp > 0) {
			StringIdChatParameter message("base_player","prose_grant_xp");
			message.setDI(xp);
			message.setTO("exp_n", xpType);
			player->sendSystemMessage(message);
		}
		if (xp > 0 && playerObject->hasCappedExperience(xpType)) {
			StringIdChatParameter message("base_player", "prose_hit_xp_cap"); //You have achieved your current limit for %TO experience.
			message.setTO("exp_n", xpType);
			player->sendSystemMessage(message);
		}
	}


}

void PlayerManagerImplementation::sendLoginMessage(CreatureObject* creature) {
	String motd = server->getLoginMessage();

	ChatSystemMessage* csm = new ChatSystemMessage(UnicodeString(motd), ChatSystemMessage::DISPLAY_CHATONLY);
	creature->sendMessage(csm);
}

void PlayerManagerImplementation::resendLoginMessageToAll() {
	ChatManager* chatManager = server->getChatManager();

	if (chatManager != NULL) {
		String motd = server->getLoginMessage();

		ChatSystemMessage* csm = new ChatSystemMessage(UnicodeString(motd), ChatSystemMessage::DISPLAY_CHATONLY);
		chatManager->broadcastMessage(csm);
	}
}

void PlayerManagerImplementation::handleAbortTradeMessage(CreatureObject* player) {
	Locker _locker(player);

	ManagedReference<TradeSession*> tradeContainer = player->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

	if (tradeContainer == NULL) {
		AbortTradeMessage* msg = new AbortTradeMessage();
		player->sendMessage(msg);

		return;
	}

	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	AbortTradeMessage* msg = new AbortTradeMessage();

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* receiver = cast<CreatureObject*>( obj.get());

		Locker locker(receiver, player);

		ManagedReference<TradeSession*> receiverContainer = receiver->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

		if (receiverContainer != NULL && receiverContainer->getTradeTargetPlayer() == player->getObjectID()) {
			receiver->dropActiveSession(SessionFacadeType::TRADE);
			receiver->sendMessage(msg->clone());
		}

		locker.release();
	}

	player->sendMessage(msg->clone());

	delete msg;

	player->dropActiveSession(SessionFacadeType::TRADE);
}

void PlayerManagerImplementation::handleAddItemToTradeWindow(CreatureObject* player, uint64 itemID) {
	Locker _locker(player);

	ManagedReference<TradeSession*> tradeContainer = player->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

	if (tradeContainer == NULL)
		return;

	// First Verify Target is Player
	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj == NULL || !obj->isPlayerCreature())
		return;

	CreatureObject* receiver = cast<CreatureObject*>( obj.get());

	ManagedReference<SceneObject*> objectToTrade = server->getObject(itemID);

	if (objectToTrade == NULL || !objectToTrade->isASubChildOf(player) ||
			!objectToTrade->checkContainerPermission(player, ContainerPermissions::MOVECONTAINER)) {
		player->sendSystemMessage("@container_error_message:container26");
		handleAbortTradeMessage(player);
		return;
	}

	if (objectToTrade->isNoTrade()) {
		player->sendSystemMessage("@container_error_message:container26");
		handleAbortTradeMessage(player);
		return;
	}

	// Containers containing notrade items...
	if (objectToTrade->containsNoTradeObjectRecursive()) {
		player->sendSystemMessage("@container_error_message:container26");
		handleAbortTradeMessage(player);
		return;
	}

	if(objectToTrade->isControlDevice()) {
		Reference<ControlDevice*> controlDevice = cast<ControlDevice*>(objectToTrade.get());
		Reference<TangibleObject*> controlledObject = controlDevice->getControlledObject();

		if (controlledObject != NULL) {
			Locker crossLocker(controlledObject, player);

			controlDevice->storeObject(player, true);
		}
	}

	tradeContainer->addTradeItem(objectToTrade);

	SceneObject* inventory = player->getSlottedObject("inventory");
	inventory->sendWithoutContainerObjectsTo(receiver);
	objectToTrade->sendTo(receiver, true);

	AddItemMessage* msg = new AddItemMessage(itemID);
	receiver->sendMessage(msg);
}

void PlayerManagerImplementation::handleGiveMoneyMessage(CreatureObject* player, uint32 value) {
	Locker _locker(player);

	int currentMoney = player->getCashCredits();

	if (value > currentMoney)
		value = currentMoney;

	ManagedReference<TradeSession*> tradeContainer = player->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

	if (tradeContainer == NULL)
		return;

	tradeContainer->setMoneyToTrade(value);

	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* receiver = cast<CreatureObject*>( obj.get());

		GiveMoneyMessage* msg = new GiveMoneyMessage(value);
		receiver->sendMessage(msg);
	}
}

void PlayerManagerImplementation::handleAcceptTransactionMessage(CreatureObject* player) {
	Locker _locker(player);

	ManagedReference<TradeSession*> tradeContainer = player->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

	if (tradeContainer == NULL)
		return;

	tradeContainer->setAcceptedTrade(true);

	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* receiver = cast<CreatureObject*>(obj.get());

		AcceptTransactionMessage* msg = new AcceptTransactionMessage();
		receiver->sendMessage(msg);
	}
}

void PlayerManagerImplementation::handleUnAcceptTransactionMessage(CreatureObject* player) {
	Locker _locker(player);

	ManagedReference<TradeSession*> tradeContainer = player->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

	if (tradeContainer == NULL)
		return;

	tradeContainer->setAcceptedTrade(false);

	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* receiver = cast<CreatureObject*>(obj.get());

		UnAcceptTransactionMessage* msg = new UnAcceptTransactionMessage();
		receiver->sendMessage(msg);
	}

}

bool PlayerManagerImplementation::checkTradeItems(CreatureObject* player, CreatureObject* receiver) {
	PlayerObject* ghost = player->getPlayerObject();
	PlayerObject* targetGhost = receiver->getPlayerObject();

	ManagedReference<TradeSession*> tradeContainer = player->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();
	ManagedReference<TradeSession*> receiverContainer = receiver->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

	if (tradeContainer == NULL || receiverContainer == NULL)
		return false;

	if (tradeContainer->getTradeTargetPlayer() != receiver->getObjectID())
		return false;

	if (receiverContainer->getTradeTargetPlayer() != player->getObjectID())
		return false;

	SceneObject* playerInventory = player->getSlottedObject("inventory");
	SceneObject* receiverInventory = receiver->getSlottedObject("inventory");

	SceneObject* playerDatapad = player->getSlottedObject("datapad");
	SceneObject* receiverDatapad = receiver->getSlottedObject("datapad");

	int playerTanos = 0;
	int playerItnos = 0;
	int recieverTanos = 0;
	int recieverItnos = 0;
	int playerCreaturePetsTraded = 0;
	int receiverCreaturePetsTraded = 0;
	int playerFactionPetsTraded = 0;
	int receiverFactionPetsTraded = 0;
	int playerDroidsTraded = 0;
	int receiverDroidsTraded = 0;
	int playerVehiclesTraded = 0;
	int receiverVehiclesTraded = 0;
	int playerShipsTraded = 0;
	int receiverShipsTraded = 0;

	for (int i = 0; i < tradeContainer->getTradeSize(); ++i) {
		ManagedReference<SceneObject*> scene = tradeContainer->getTradeItem(i);

		if(scene->isNoTrade())
			return false;

		if(scene->isTangibleObject()) {

			String err;
			if (receiverInventory->canAddObject(scene, -1, err) != 0)
				return false;

			if (!playerInventory->hasObjectInContainer(scene->getObjectID()))
				return false;

			recieverTanos++;

		} else if(scene->isIntangibleObject()) {

			String err;
			if (receiverDatapad->canAddObject(scene, -1, err) != 0)
				return false;

			if (!playerDatapad->hasObjectInContainer(scene->getObjectID()))
				return false;

			if (scene->isPetControlDevice()) {
				PetControlDevice* petControlDevice = cast<PetControlDevice*>(scene.get());

				if (petControlDevice->getPetType() == PetManager::CREATUREPET) {
					if (!petControlDevice->canBeTradedTo(player, receiver, receiverCreaturePetsTraded))
						return false;

					receiverCreaturePetsTraded++;
				} else if (petControlDevice->getPetType() == PetManager::FACTIONPET) {
					if (!petControlDevice->canBeTradedTo(player, receiver, receiverFactionPetsTraded))
						return false;

					receiverFactionPetsTraded++;
				} else if (petControlDevice->getPetType() == PetManager::DROIDPET) {
					if (!petControlDevice->canBeTradedTo(player, receiver, receiverDroidsTraded))
						return false;

					receiverDroidsTraded++;
				}
			} else if (scene->isVehicleControlDevice()) {
				VehicleControlDevice* vehicleControlDevice = cast<VehicleControlDevice*>(scene.get());

				if (!vehicleControlDevice->canBeTradedTo(player, receiver, receiverVehiclesTraded))
					return false;

				receiverVehiclesTraded++;
			} else if (scene->isShipControlDevice()) {
				ShipControlDevice* shipControlDevice = cast<ShipControlDevice*>(scene.get());

				if (!shipControlDevice->canBeTradedTo(player, receiver, receiverShipsTraded))
					return false;

				receiverShipsTraded++;
			}

			recieverItnos++;

		} else {
			return false;
		}
	}

	for (int i = 0; i < receiverContainer->getTradeSize(); ++i) {
		ManagedReference<SceneObject*> scene = receiverContainer->getTradeItem(i);

		if(scene->isNoTrade())
			return false;

		if(scene->isTangibleObject()) {

			String err;
			if (playerInventory->canAddObject(scene, -1, err) != 0)
				return false;

			if (!receiverInventory->hasObjectInContainer(scene->getObjectID()))
				return false;

			playerTanos++;

		} else if(scene->isIntangibleObject()) {

			String err;
			if (playerDatapad->canAddObject(scene, -1, err) != 0)
				return false;

			if (!receiverDatapad->hasObjectInContainer(scene->getObjectID()))
				return false;

			if (scene->isPetControlDevice()) {
				PetControlDevice* petControlDevice = cast<PetControlDevice*>(scene.get());

				if (petControlDevice->getPetType() == PetManager::CREATUREPET) {
					if (!petControlDevice->canBeTradedTo(receiver, player, playerCreaturePetsTraded))
						return false;

					playerCreaturePetsTraded++;
				} else if (petControlDevice->getPetType() == PetManager::FACTIONPET) {
					if (!petControlDevice->canBeTradedTo(receiver, player, playerFactionPetsTraded))
						return false;

					playerFactionPetsTraded++;
				} else if (petControlDevice->getPetType() == PetManager::DROIDPET) {
					if (!petControlDevice->canBeTradedTo(receiver, player, playerDroidsTraded))
						return false;

					playerDroidsTraded++;
				}
			} else if (scene->isVehicleControlDevice()) {
				VehicleControlDevice* vehicleControlDevice = cast<VehicleControlDevice*>(scene.get());

				if (!vehicleControlDevice->canBeTradedTo(receiver, player, playerVehiclesTraded))
					return false;

				playerVehiclesTraded++;
			} else if (scene->isShipControlDevice()) {
				ShipControlDevice* shipControlDevice = cast<ShipControlDevice*>(scene.get());

				if (!shipControlDevice->canBeTradedTo(receiver, player, playerShipsTraded))
					return false;

				playerShipsTraded++;
			}

			playerItnos++;

		} else {
			return false;
		}
	}

	if (recieverTanos != 0 && (receiverInventory->getContainerObjectsSize() + recieverTanos >= receiverInventory->getContainerVolumeLimit())) {
		player->sendSystemMessage("@container_error_message:container19");
		receiver->sendSystemMessage("@container_error_message:container19");
		return false;
	}

	if (playerTanos != 0 && (playerInventory->getContainerObjectsSize() + playerTanos >= playerInventory->getContainerVolumeLimit())) {
		player->sendSystemMessage("@container_error_message:container19");
		receiver->sendSystemMessage("@container_error_message:container19");
		return false;
	}

	if (receiverDatapad->getContainerObjectsSize() + recieverItnos >= receiverDatapad->getContainerVolumeLimit()) {
		player->sendSystemMessage("@container_error_message:container19");
		receiver->sendSystemMessage("@container_error_message:container19");
		return false;
	}

	if (playerDatapad->getContainerObjectsSize() + playerItnos >= playerDatapad->getContainerVolumeLimit()) {
		player->sendSystemMessage("@container_error_message:container19");
		receiver->sendSystemMessage("@container_error_message:container19");
		return false;
	}

	int playerMoneyToTrade = tradeContainer->getMoneyToTrade();

	if (playerMoneyToTrade < 0)
		return false;

	if (playerMoneyToTrade > player->getCashCredits())
		return false;

	int receiverMoneyToTrade = receiverContainer->getMoneyToTrade();

	if (receiverMoneyToTrade < 0)
		return false;

	if (receiverMoneyToTrade > receiver->getCashCredits())
		return false;

	if (player->getDistanceTo(receiver) >= 15.f) {
		player->sendSystemMessage("You are too far to trade");
		receiver->sendSystemMessage("You are too far to trade");
		return false;
	}


	return true;
}

void PlayerManagerImplementation::handleVerifyTradeMessage(CreatureObject* player) {
	ManagedReference<ObjectController*> objectController = server->getObjectController();

	Locker locker(player);

	ManagedReference<TradeSession*> tradeContainer = player->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

	if (tradeContainer == NULL) {
		return;
	}

	tradeContainer->setVerifiedTrade(true);

	uint64 targID = tradeContainer->getTradeTargetPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* receiver = cast<CreatureObject*>(obj.get());

		Locker clocker(receiver, player);

		ManagedReference<TradeSession*> receiverTradeContainer = receiver->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

		if (receiverTradeContainer == NULL) {
			tradeContainer->setVerifiedTrade(false);
			return;
		}

		if (!checkTradeItems(player, receiver)) {
			clocker.release();
			handleAbortTradeMessage(player);

			locker.release();
			return;
		}

		if (receiverTradeContainer->hasVerifiedTrade()) {
			SceneObject* receiverInventory = receiver->getSlottedObject("inventory");
			SceneObject* receiverDatapad = receiver->getSlottedObject("datapad");

			for (int i = 0; i < tradeContainer->getTradeSize(); ++i) {
				ManagedReference<SceneObject*> item = tradeContainer->getTradeItem(i);

				if(item->isTangibleObject()) {
					if (objectController->transferObject(item, receiverInventory, -1, true))
						item->sendDestroyTo(player);
				} else {
					if (objectController->transferObject(item, receiverDatapad, -1, true))
						item->sendDestroyTo(player);
				}
			}

			SceneObject* playerInventory = player->getSlottedObject("inventory");
			SceneObject* playerDatapad = player->getSlottedObject("datapad");

			for (int i = 0; i < receiverTradeContainer->getTradeSize(); ++i) {
				ManagedReference<SceneObject*> item = receiverTradeContainer->getTradeItem(i);

				if(item->isTangibleObject()) {
					if (objectController->transferObject(item, playerInventory, -1, true))
						item->sendDestroyTo(receiver);
				} else {
					if (objectController->transferObject(item, playerDatapad, -1, true))
						item->sendDestroyTo(receiver);
				}
			}

			uint32 giveMoney = tradeContainer->getMoneyToTrade();

			if (giveMoney > 0) {
				player->subtractCashCredits(giveMoney);
				receiver->addCashCredits(giveMoney);
			}

			giveMoney = receiverTradeContainer->getMoneyToTrade();

			if (giveMoney > 0) {
				receiver->subtractCashCredits(giveMoney);
				player->addCashCredits(giveMoney);
			}

			receiver->dropActiveSession(SessionFacadeType::TRADE);
			player->dropActiveSession(SessionFacadeType::TRADE);

			TradeCompleteMessage* msg = new TradeCompleteMessage();
			receiver->sendMessage(msg->clone());
			player->sendMessage(msg->clone());

			delete msg;
		}
	}
}

int PlayerManagerImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {

	if (eventType == ObserverEventType::POSTURECHANGED) {
		CreatureObject* creature = cast<CreatureObject*>( observable);


		if (creature->hasState(CreatureState::ALERT)) { // This can apply to TKA AND Jedi meditate since they share the same sysmsgs / moods.
			creature->sendSystemMessage("@teraskasi:med_end");
			creature->setMood(creature->getMoodID(), true);
			creature->clearState(CreatureState::ALERT, true);

			// Check POSTERCHANGE on Meditate...
			Reference<MeditateTask*> meditateTask = creature->getPendingTask("meditate").castTo<MeditateTask*>();
			if (meditateTask != NULL) {
				creature->removePendingTask("meditate");

				if (meditateTask->isScheduled())
					meditateTask->cancel();
			}

			// Check POSTERCHANGE on Force Meditate...
			Reference<ForceMeditateTask*> fmeditateTask = creature->getPendingTask("forcemeditate").castTo<ForceMeditateTask*>( );

			if (fmeditateTask != NULL) {
				creature->removePendingTask("forcemeditate");

				if (fmeditateTask->isScheduled())
					fmeditateTask->cancel();
			}
		}

		// Check POSTURECHANGED disrupting Logout...
		Reference<LogoutTask*> logoutTask = creature->getPendingTask("logout").castTo<LogoutTask*>();
		if(logoutTask != NULL) {
			logoutTask->cancelLogout();
		}
	}

	return 1;
}

void PlayerManagerImplementation::sendBattleFatigueMessage(CreatureObject* player, CreatureObject* target) {
	if (target->isPlayerCreature()) {
		uint32 targetBattleFatigue = target->getShockWounds();

		if (targetBattleFatigue >= 250 && targetBattleFatigue < 500) {
			target->sendSystemMessage("@healing:shock_effect_low_target");
		} else if (targetBattleFatigue >= 500 && targetBattleFatigue < 750) {
			target->sendSystemMessage("@healing:shock_effect_medium_target");
		} else if (targetBattleFatigue >= 750) {
			target->sendSystemMessage("@healing:shock_effec_high_target");
		}
	}

	uint32 playerBattleFatigue = player->getShockWounds();

	if (playerBattleFatigue >= 250 && playerBattleFatigue < 500) {
		player->sendSystemMessage("@healing:shock_effect_low");
	} else if (playerBattleFatigue >= 500 && playerBattleFatigue < 750) {
		player->sendSystemMessage("@healing:shock_effect_medium");
	} else if (playerBattleFatigue >= 750) {
		player->sendSystemMessage("@healing:shock_effect_high");
	}
}

int PlayerManagerImplementation::healEnhance(CreatureObject* enhancer, CreatureObject* patient, byte attribute, int buffvalue, float duration) {
	String buffname = "medical_enhance_" + BuffAttribute::getName(attribute);
	uint32 buffcrc = buffname.hashCode();
	uint32 buffdiff = buffvalue;

	//If a stronger buff already exists, then we don't buff the patient.
	if (patient->hasBuff(buffcrc)) {
		Buff* buff = patient->getBuff(buffcrc);

		if (buff != NULL) {
			int value = buff->getAttributeModifierValue(attribute);

			if(BuffAttribute::isProtection(attribute))
				value = buff->getSkillModifierValue(BuffAttribute::getProtectionString(attribute));

			if (value > buffvalue)
				return 0;

			buffdiff -= value;
		}
	}

	Reference<Buff*> buff = new Buff(patient, buffname.hashCode(), duration, BuffType::MEDICAL);

	if(BuffAttribute::isProtection(attribute))
		buff->setSkillModifier(BuffAttribute::getProtectionString(attribute), buffvalue);
	else{
		buff->setAttributeModifier(attribute, buffvalue);
		buff->setFillAttributesOnBuff(true);
	}

	patient->addBuff(buff);

	enhancer->notifyObservers(ObserverEventType::ENHANCINGPERFORMED, patient, buffdiff);

	return buffdiff;
}

void PlayerManagerImplementation::stopListen(CreatureObject* creature, uint64 entid, bool doSendPackets, bool forced, bool doLock, bool outOfRange) {
	Locker locker(creature);

	ManagedReference<SceneObject*> object = server->getObject(entid);
	uint64 listenID = creature->getListenID();

	if (object == NULL)
		return;

	if(object->isDroidObject()) {
		creature->setMood(creature->getMoodID());
		if (entid != listenID ) {
			creature->sendSystemMessage("You are not currently listening to " + object->getDisplayedName() + ".");
			return;
		}
		if(doSendPackets) {
			creature->setListenToID(0, true);
			creature->setMoodString(creature->getMoodString(), true);
		}
		if (creature->isPlayerCreature()) {
			CreatureObject* player = cast<CreatureObject*>( creature);
			StringIdChatParameter stringID;
			if (forced) {
				stringID.setTU(entid);
				stringID.setStringId("performance", "music_stop_other");
				player->sendSystemMessage(stringID);
				return;
			} else if (outOfRange) {
				StringBuffer msg;
				msg << "You stop listening to " << object->getDisplayedName() << " because they are too far away.";
				player->sendSystemMessage(msg.toString());
				return;
			} else {
				player->sendSystemMessage("@performance:music_listen_stop_self"); //"You stop watching."
				return;
			}
		}
		return;
	}

	if (!object->isPlayerCreature()) {
		creature->sendSystemMessage("You cannot stop listening an object.");
		return;
	}

	CreatureObject* entertainer = cast<CreatureObject*>( object.get());

	if (entertainer == creature)
		return;

	String entName;
	ManagedReference<EntertainingSession*> esession;

	if (entertainer != NULL) {
		Locker clocker(entertainer, creature);

		entName = entertainer->getFirstName();

		ManagedReference<Facade*> session = entertainer->getActiveSession(SessionFacadeType::ENTERTAINING);

		if (session != NULL) {
			esession = dynamic_cast<EntertainingSession*>(session.get());

			if (esession != NULL) {
				esession->activateEntertainerBuff(creature, PerformanceType::MUSIC);

				esession->removeListener(creature);
			}
		}

		clocker.release();
	}

	if (entid != listenID && entertainer != NULL) {
		creature->sendSystemMessage("You are not currently listening to " + entName + ".");

		return;
	}

	creature->setMood(creature->getMoodID());

	if (doSendPackets && esession != NULL)
		esession->sendEntertainmentUpdate(creature, 0, creature->getMoodString());

	if (creature->isPlayerCreature() && entertainer != NULL) {
		CreatureObject* player = cast<CreatureObject*>( creature);

		StringIdChatParameter stringID;

		if (forced) {
			stringID.setTU(entid);
			stringID.setStringId("performance", "music_stop_other");

			player->sendSystemMessage(stringID);
			//player->sendSystemMessage("performance", "dance_stop_other", params); //"%TU stops dancing."
		} else if (outOfRange) {
			StringBuffer msg;
			msg << "You stop watching " << entertainer->getFirstName() << " because they are too far away.";
			player->sendSystemMessage(msg.toString());

			//TODO: Why does %OT say "him/her" instead of "he/she"?
			//params->addTT(entid);
			//player->sendSystemMessage("performance", "dance_watch_out_of_range", params); //"You stop watching %TT because %OT is too far away."
		} else {
			player->sendSystemMessage("@performance:music_listen_stop_self"); //"You stop watching."
		}

		ManagedReference<PlayerObject*> entPlayer = entertainer->getPlayerObject();
		if (entPlayer != NULL && entPlayer->getPerformanceBuffTarget() == player->getObjectID())
			entPlayer->setPerformanceBuffTarget(0);
	}
	//esession->setEntertainerBuffDuration(creature, PerformanceType::MUSIC, 0.0f); // reset
	//esession->setEntertainerBuffStrength(creature, PerformanceType::MUSIC, 0.0f);
	creature->info("stopped watching [" + entName + "]");

	//creature->setListenToID(0, true);
}


void PlayerManagerImplementation::stopWatch(CreatureObject* creature, uint64 entid, bool doSendPackets, bool forced, bool doLock, bool outOfRange) {
	Locker locker(creature);

	ManagedReference<SceneObject*> object = server->getObject(entid);
	uint64 watchID = creature->getWatchToID();

	if (object == NULL)
		return;

	if (!object->isPlayerCreature()) {
		creature->sendSystemMessage("You cannot stop watching an object.");
		return;
	}

	CreatureObject* entertainer = cast<CreatureObject*>( object.get());

	if (entertainer == creature)
		return;

	ManagedReference<EntertainingSession*> esession = NULL;

	String entName;
	if (entertainer != NULL) {
		Locker clocker(entertainer, creature);

		entName = entertainer->getFirstName();

		ManagedReference<Facade*> session = entertainer->getActiveSession(SessionFacadeType::ENTERTAINING);

		if (session != NULL) {
			esession = dynamic_cast<EntertainingSession*>(session.get());

			if (esession != NULL) {
				esession->activateEntertainerBuff(creature, PerformanceType::DANCE);

				esession->removeWatcher(creature);
			}
		}

		clocker.release();
	}

	if (entid != watchID) {
		creature->sendSystemMessage("You are not currently watching " + entName + ".");

		return;
	}

	creature->setMood(creature->getMoodID());

	if (doSendPackets && esession != NULL)
		esession->sendEntertainmentUpdate(creature, 0, creature->getMoodString());

	//System Message.
	if (creature->isPlayerCreature() && entertainer != NULL) {
		CreatureObject* player = cast<CreatureObject*>( creature);

		StringIdChatParameter stringID;
		//StfParameter* params = new StfParameter;

		if (forced) {
			stringID.setTU(entid);
			stringID.setStringId("performance", "dance_stop_other");

			player->sendSystemMessage(stringID);
			//player->sendSystemMessage("performance", "dance_stop_other", params); //"%TU stops dancing."
		} else if (outOfRange) {
			StringBuffer msg;
			msg << "You stop watching " << entertainer->getFirstName() << " because they are too far away.";
			player->sendSystemMessage(msg.toString());

			//TODO: Why does %OT say "him/her" instead of "he/she"?
			//params->addTT(entid);
			//player->sendSystemMessage("performance", "dance_watch_out_of_range", params); //"You stop watching %TT because %OT is too far away."
		} else {
			player->sendSystemMessage("@performance:dance_watch_stop_self"); //"You stop watching."
		}

		ManagedReference<PlayerObject*> entPlayer = entertainer->getPlayerObject();
		if (entPlayer != NULL && entPlayer->getPerformanceBuffTarget() == player->getObjectID())
			entPlayer->setPerformanceBuffTarget(0);
	}


	//esession->setEntertainerBuffDuration(creature, PerformanceType::DANCE, 0.0f); // reset
	//esession->setEntertainerBuffStrength(creature, PerformanceType::DANCE, 0.0f);
	creature->info("stopped watching [" + entName + "]");

	creature->setWatchToID(0);
	/*doWatching = false;
	watchID = 0;*/
}

void PlayerManagerImplementation::startWatch(CreatureObject* creature, uint64 entid) {
	Locker locker(creature);

	ManagedReference<SceneObject*> object = server->getObject(entid);
	uint64 watchID = creature->getWatchToID();

	if (object == NULL)
		return;

	/*if (object->isNonPlayerCreature()) {
		creature->sendSystemMessage("@performance:dance_watch_npc");
		return;
	}*/

	if (!object->isPlayerCreature()) {
		creature->sendSystemMessage("You cannot start watching an object.");
		return;
	}

	CreatureObject* entertainer = cast<CreatureObject*>( object.get());

	if (creature == entertainer)
		return;

	Locker clocker(entertainer, creature);

	if (creature->isDancing() || creature->isPlayingMusic()) {
		creature->sendSystemMessage("You cannot /watch while skill animating.");

		return;
	} else if (!entertainer->isDancing()) {
		creature->sendSystemMessage(entertainer->getCustomObjectName().toString() + " is not currently dancing.");

		return;
	} else if (entid == watchID) {
		creature->sendSystemMessage("You are already watching " + entertainer->getCustomObjectName().toString() + ".");

		return;
	}

	ManagedReference<Facade*> facade = entertainer->getActiveSession(SessionFacadeType::ENTERTAINING);

	if (facade == NULL)
		return;

	EntertainingSession* entertainingSession = dynamic_cast<EntertainingSession*>(facade.get());

	if (entertainingSession == NULL)
		return;

	if (creature->isWatching()) {
		stopWatch(creature, watchID, false);
	}

	//sendEntertainmentUpdate(entid, "entertained");

	entertainingSession->sendEntertainmentUpdate(creature, entid, "entertained");
	entertainingSession->addWatcher(creature);

	entertainer->notifyObservers(ObserverEventType::WASWATCHED, creature);

	//creature->addWatcher(_this);

	//if (isPlayer())
	creature->sendSystemMessage("You begin watching " + entertainer->getCustomObjectName().toString() + ".");

	//setEntertainerBuffDuration(PerformanceType::DANCE, 0.0f);
	//setEntertainerBuffStrength(PerformanceType::DANCE, 0.0f);

	creature->info("started watching [" + entertainer->getCustomObjectName().toString() + "]");

	creature->setWatchToID(entertainer->getObjectID());
	//watchID =  entid;
}

void PlayerManagerImplementation::startListen(CreatureObject* creature, uint64 entid) {
	Locker locker(creature);

	ManagedReference<SceneObject*> object = server->getObject(entid);
	uint64 listenID = creature->getListenID();

	if (object == NULL)
		return;

	/*if (object->isNonPlayerCreature()) {
		creature->sendSystemMessage("@performance:dance_watch_npc");
		return;
	}*/

	// Droid playback handling
	if(object->isDroidObject()) {
		DroidObject* droid = cast<DroidObject*>( object.get());
		if (droid == NULL) {
			creature->sendSystemMessage("You cannot start listening an object.");
			return;
		}
		BaseDroidModuleComponent* bmodule = droid->getModule("playback_module");
		if(bmodule != NULL) {
			DroidPlaybackModuleDataComponent* module = cast<DroidPlaybackModuleDataComponent*>(bmodule);
			if(module != NULL) {
				if (creature->isDancing() || creature->isPlayingMusic()) {
					creature->sendSystemMessage("You cannot /watch while skill animating.");
					return;
				}

				if(module->isActive()) {
					// the droid is playing so we can do something
					if (entid == listenID) {
						creature->sendSystemMessage("You are already listening " + droid->getDisplayedName() + ".");
						return;
					}
					if (creature->isListening()) {
						stopListen(creature, listenID, false);
					}
					creature->sendSystemMessage("You begin to listen " + droid->getDisplayedName() + ".");
					creature->setListenToID(entid, true);
					String str = Races::getMoodStr("entertained");
					creature->setMoodString(str, true);
					creature->setListenToID(droid->getObjectID());
					module->addListener(creature->getObjectID());
					return;
				} else {
					creature->sendSystemMessage(droid->getDisplayedName() + " is not currently playing music.");
					return;
				}
			} else {
				creature->sendSystemMessage("You cannot start listening an object.");
			}
		} else {
			creature->sendSystemMessage("You cannot start listening an object.");
		}
		return;
	}

	if (!object->isPlayerCreature()) {
		creature->sendSystemMessage("You cannot start listening an object.");
		return;
	}

	CreatureObject* entertainer = cast<CreatureObject*>( object.get());

	if (creature == entertainer)
		return;

	Locker clocker(entertainer, creature);

	if (creature->isDancing() || creature->isPlayingMusic()) {
		creature->sendSystemMessage("You cannot /watch while skill animating.");

		return;
	} else if (!entertainer->isPlayingMusic()) {
		creature->sendSystemMessage(entertainer->getCustomObjectName().toString() + " is not currently playing music.");

		return;
	} else if (entid == listenID) {
		creature->sendSystemMessage("You are already listening " + entertainer->getCustomObjectName().toString() + ".");

		return;
	}

	ManagedReference<Facade*> facade = entertainer->getActiveSession(SessionFacadeType::ENTERTAINING);

	if (facade == NULL)
		return;

	EntertainingSession* entertainingSession = dynamic_cast<EntertainingSession*>(facade.get());

	if (entertainingSession == NULL)
		return;

	if (creature->isListening()) {
		stopListen(creature, listenID, false);
	}

	//sendEntertainmentUpdate(entid, "entertained");

	entertainingSession->sendEntertainmentUpdate(creature, entid, "entertained");
	entertainingSession->addListener(creature);

	entertainer->notifyObservers(ObserverEventType::WASLISTENEDTO, creature);

	//creature->addWatcher(_this);

	//if (isPlayer())
	creature->sendSystemMessage("You begin to listen " + entertainer->getCustomObjectName().toString() + ".");

	//setEntertainerBuffDuration(PerformanceType::DANCE, 0.0f);
	//setEntertainerBuffStrength(PerformanceType::DANCE, 0.0f);

	creature->info("started watching [" + entertainer->getCustomObjectName().toString() + "]");

	creature->setListenToID(entertainer->getObjectID());
	//watchID =  entid;
}


SceneObject* PlayerManagerImplementation::getInRangeStructureWithAdminRights(CreatureObject* creature, uint64 targetID) {
	ZoneServer* zoneServer = server;

	//First we need to check if the target. if it's not right...
	//Check the building they are standing in, if it's not right...
	//Find the nearest installation.

	ManagedReference<SceneObject*> obj = NULL;

	if (targetID != 0) {
		obj = zoneServer->getObject(targetID);

		if (obj != NULL && obj->isStructureObject() && (cast<StructureObject*>(obj.get()))->isOnAdminList(creature))
			return obj.get();
	}


	ManagedReference<SceneObject*> rootParent = creature->getRootParent();

	if (rootParent != NULL && rootParent->isStructureObject() && (cast<StructureObject*>(rootParent.get()))->isOnAdminList(creature)) {
		return rootParent;
	}

	StructureObject* structure = NULL;
	float distance = 16000;

	Zone* zone = creature->getZone();

	if (zone == NULL) {
		return NULL;
	}

	//We need to search nearby for an installation that belongs to the player.
	Locker _locker(zone);

	SortedVector<ManagedReference<QuadTreeEntry*> >* closeObjects = creature->getCloseObjects();

	for (int i = 0; i < closeObjects->size(); ++i) {
		ManagedReference<SceneObject*> tObj = cast<SceneObject*>( closeObjects->get(i).get());

		if (tObj != NULL) {
			if (tObj->isStructureObject()) {
				float dist = tObj->getDistanceTo(creature);

				StructureObject* structureObject = cast<StructureObject*>( tObj.get());

				if (structureObject->isOnAdminList(creature) && dist < distance) {
					structure = structureObject;
					distance = dist;
				}
			}
		}
	}

	if (distance < 25)
		return structure;

	return NULL;
}

StructureObject* PlayerManagerImplementation::getInRangeOwnedStructure(CreatureObject* creature, float range) {
	Locker _lock(creature);

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost == NULL)
		return NULL;

	ManagedReference<StructureObject*> closestStructure = NULL;
	float closestDistance = 16000.f;

	for (int i = 0; i < ghost->getTotalOwnedStructureCount(); ++i) {
		uint64 oid = ghost->getOwnedStructure(i);

		ManagedReference<StructureObject*> structure = (ghost->getZoneServer()->getObject(oid)).castTo<StructureObject*>();

		Locker _slock(structure, creature);

		if (creature->getZone() != structure->getZone())
			continue;

		float distance = structure->getDistanceTo(creature);

		if (distance <= range && distance < closestDistance) {
			closestStructure = structure;
			closestDistance = distance;
		}
	}

	return closestStructure;
}

void PlayerManagerImplementation::updatePermissionLevel(CreatureObject* targetPlayer, int permissionLevel) {

	if (targetPlayer == NULL) {
		return;
	}

	//Locker clocker(targetPlayer, player);
	Locker locker(targetPlayer);
	ManagedReference<PlayerObject*> ghost = targetPlayer->getPlayerObject();

	if (ghost == NULL) {
		return;
	}

	SkillManager* skillManager = server->getSkillManager();

	int currentPermissionLevel = ghost->getAdminLevel();

	/*Temporarily removed so that we can update admin levels immediately
	if(currentPermissionLevel == permissionLevel)
		return;*/

	if (currentPermissionLevel != 0) {
		Vector<String>* skillsToBeRemoved = permissionLevelList->getPermissionSkills(currentPermissionLevel);
		if(skillsToBeRemoved != NULL) {
			for(int i = 0; i < skillsToBeRemoved->size(); i++) {
				String skill = skillsToBeRemoved->get(i);
				targetPlayer->sendSystemMessage("Staff skill revoked: " + skill);
				skillManager->surrenderSkill(skill, targetPlayer, true);
			}
		}
	}

	if(permissionLevel != 0) {
		Vector<String>* skillsToBeAdded = permissionLevelList->getPermissionSkills(permissionLevel);
		if(skillsToBeAdded != NULL) {
			for(int i = 0; i < skillsToBeAdded->size(); ++i) {
				String skill = skillsToBeAdded->get(i);
				targetPlayer->sendSystemMessage("Staff skill granted: " + skill);
				skillManager->awardSkill(skill, targetPlayer, false, true, true);
			}
		}
	}

	ghost->setAdminLevel(permissionLevel);
	updatePermissionName(targetPlayer, permissionLevel);
}

void PlayerManagerImplementation::updatePermissionName(CreatureObject* player, int permissionLevel) {
	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
	//Send deltas
	if (player->isOnline()) {
		UnicodeString tag = permissionLevelList->getPermissionTag(permissionLevel);

		TangibleObjectDeltaMessage3* tanod3 = new TangibleObjectDeltaMessage3(player);
		tanod3->updateName(player->getDisplayedName(), tag);
		tanod3->close();
		player->broadcastMessage(tanod3, true);

		/*PlayerObjectDeltaMessage6* playd6 = new PlayerObjectDeltaMessage6(ghost);
			playd6->setAdminLevel(adminLevel);
			playd6->close();
			player->broadcastMessage(playd6, true);*/
	}
}

void PlayerManagerImplementation::updateSwimmingState(CreatureObject* player, float newZ, IntersectionResults* intersections, CloseObjectsVector* closeObjectsVector) {
	player->notifySelfPositionUpdate();
	if (player->getParent() != NULL) {
		return;
	}

	ManagedReference<Zone*> zone = player->getZone();

	if (zone == NULL) {
		player->info("No zone.", true);
		return;
	}

	ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

	if (planetManager == NULL) {
		player->info("No planet manager.", true);
		return;
	}

	ManagedReference<TerrainManager*> terrainManager = planetManager->getTerrainManager();

	if (terrainManager == NULL) {
		player->info("No terrain manager.", true);
		return;
	}

	float landHeight = zone->getHeight(player->getPositionX(), player->getPositionY());
	float waterHeight = landHeight;
	bool waterIsDefined = terrainManager->getWaterHeight(player->getPositionX(), player->getPositionY(), waterHeight);

	if (waterIsDefined && (waterHeight > landHeight) && (landHeight + player->getSwimHeight() - waterHeight < 0.2)) {
		//Water level is higher than the terrain level and is deep enough for the player to be swimming.
		//Check if the player is on a bridge or other terrain above the water level.
		//SortedVector<IntersectionResult> intersections;
		Reference<IntersectionResults*> ref;

		if (intersections == NULL) {
			ref = intersections = new IntersectionResults();

			CollisionManager::getWorldFloorCollisions(player->getPositionX(), player->getPositionY(), zone, intersections, closeObjectsVector);
		}

		for (int i = 0; i < intersections->size(); i++) {
			if (fabs(16384 - intersections->get(i).getIntersectionDistance() - newZ) < 0.2) {
				//Player is on terrain above the water.
				player->clearState(CreatureState::SWIMMING, true);
				return;
			}
		}

		//Player is in the water.
		player->setState(CreatureState::SWIMMING, true);
		return;
	}

	//Terrain is above water level.
	player->clearState(CreatureState::SWIMMING, true);
}

int PlayerManagerImplementation::checkSpeedHackFirstTest(CreatureObject* player, float parsedSpeed, ValidatedPosition& teleportPosition, float errorMultiplier) {
	float allowedSpeedMod = player->getSpeedMultiplierMod();
	float allowedSpeedBase = player->getRunSpeed();
	ManagedReference<SceneObject*> parent = player->getParent();
	SpeedMultiplierModChanges* changeBuffer = player->getSpeedMultiplierModChanges();
	Vector3 teleportPoint = teleportPosition.getPosition();
	uint64 teleportParentID = teleportPosition.getParent();

	if (parent != NULL && parent->isVehicleObject()) {
		VehicleObject* vehicle = cast<VehicleObject*>( parent.get());

		allowedSpeedMod = vehicle->getSpeedMultiplierMod();
		allowedSpeedBase = vehicle->getRunSpeed();
	} else if (parent != NULL && parent->isMount()){
		Creature* mount = cast<Creature*>( parent.get());

		allowedSpeedMod = mount->getSpeedMultiplierMod();

		PetManager* petManager = server->getPetManager();

		if (petManager != NULL) {
			allowedSpeedBase = petManager->getMountedRunSpeed(mount);
		}

	}

	float maxAllowedSpeed = allowedSpeedMod * allowedSpeedBase;

	if (parsedSpeed > maxAllowedSpeed * errorMultiplier) {
		//float delta = abs(parsedSpeed - maxAllowedSpeed);

		if (changeBuffer->size() == 0) { // no speed changes
			StringBuffer msg;
			msg << "max allowed speed should be " << maxAllowedSpeed * errorMultiplier;
			msg << " parsed " << parsedSpeed;
			player->info(msg.toString());

			player->teleport(teleportPoint.getX(), teleportPoint.getZ(), teleportPoint.getY(), teleportParentID);

			return 1;
		}

		SpeedModChange* firstChange = &changeBuffer->get(changeBuffer->size() - 1);
		Time* timeStamp = &firstChange->getTimeStamp();

		if (timeStamp->miliDifference() > 2000) { // we already should have lowered the speed, 2 seconds lag
			StringBuffer msg;
			msg << "max allowed speed should be " << maxAllowedSpeed * errorMultiplier;
			msg << " parsed " << parsedSpeed;
			player->info(msg.toString());

			player->teleport(teleportPoint.getX(), teleportPoint.getZ(), teleportPoint.getY(), teleportParentID);

			return 1;
		}

		for (int i = 0; i < changeBuffer->size() - 1; ++i) {
			SpeedModChange* change = &changeBuffer->get(i);
			//Time timeStamp = change->getTimeStamp();

			float oldSpeedMod = change->getNewSpeed();
			float allowed = allowedSpeedBase * oldSpeedMod * errorMultiplier;

			if (allowed >= parsedSpeed) {
				return 0; // no hack detected
			}

			if (allowed > maxAllowedSpeed)
				maxAllowedSpeed = allowed;
		}

		StringBuffer msg;
		msg << "max allowed speed should be " << maxAllowedSpeed;
		msg << " parsed " << parsedSpeed;
		msg << " changeBufferSize: " << changeBuffer->size();

		player->info(msg.toString());

		player->teleport(teleportPoint.getX(), teleportPoint.getZ(), teleportPoint.getY(), teleportParentID);

		return 1;
	}

	return 0;
}

int PlayerManagerImplementation::checkSpeedHackSecondTest(CreatureObject* player, float newX, float newZ, float newY, uint32 newStamp, SceneObject* newParent) {
	PlayerObject* ghost = player->getPlayerObject();

	uint32 deltaTime = ghost->getServerMovementTimeDelta();//newStamp - stamp;

	if (deltaTime < 1000) {
		//info("time hasnt passed yet", true);
		return 0;
	}

	uint32 stamp = ghost->getClientLastMovementStamp();

	if (stamp > newStamp) {
		//info("older stamp received", true);
		return 1;
	}

	Vector3 newWorldPosition(newX, newY, newZ);

	/*StringBuffer newWorldPosMsg;
	newWorldPosMsg << "x:" << newWorldPosition.getX() << " z:" << newWorldPosition.getZ() << " y:" << newWorldPosition.getY();
	player->info(newWorldPosMsg.toString(), true);*/

	if (newParent != NULL) {
		ManagedReference<SceneObject*> root = newParent->getRootParent();

		if (!root->isBuildingObject())
			return 1;

		float length = Math::sqrt(newX * newX + newY * newY);
		float angle = root->getDirection()->getRadians() + atan2(newX, newY);

		newWorldPosition.set(root->getPositionX() + (sin(angle) * length), root->getPositionZ() + newZ, root->getPositionY() + (cos(angle) * length));
	}

	/*newWorldPosMsg.deleteAll();
	newWorldPosMsg << "x:" << newWorldPosition.getX() << " z:" << newWorldPosition.getZ() << " y:" << newWorldPosition.getY();
	player->info(newWorldPosMsg.toString(), true);*/

	ValidatedPosition* lastValidatedPosition = ghost->getLastValidatedPosition();

	Vector3 lastValidatedWorldPosition = lastValidatedPosition->getWorldPosition(server);

	//ignoring Z untill we have all heightmaps
	float oldValidZ = lastValidatedWorldPosition.getZ();
	float oldNewPosZ = newWorldPosition.getZ();

	lastValidatedWorldPosition.setZ(0);
	newWorldPosition.setZ(0);

	float dist = newWorldPosition.distanceTo(lastValidatedWorldPosition);

	if (dist < 1) {
		//info("distance too small", true);
		return 0;
	}

	float speed = dist / (float) deltaTime * 1000;

	/*if (oldNewPosZ > oldValidZ) {
		float heightDist = oldNewPosZ - oldValidZ;

		//if (heightDist > speed) {
			StringBuffer msg;
			msg << " heightDist:" << heightDist << " speed:" << speed << " terrain neg:" << player->getSlopeModPercent();
			player->info(msg.toString(), true);
		//}
	}*/

	//lastValidatedPosition->set(newWorldPosition.getX(), oldNewPosZ, newWorldPosition.getY());

	/*StringBuffer msg;
	msg << "distancia recorreguda " << dist << " a una velocitat " << speed;
	info(msg, true);*/

	int ret = checkSpeedHackFirstTest(player, speed, *lastValidatedPosition, 1.5f);

	if (ret == 0) {
		lastValidatedPosition->setPosition(newX, newZ, newY);

		if (newParent != NULL)
			lastValidatedPosition->setParent(newParent->getObjectID());
		else
			lastValidatedPosition->setParent(0);

		ghost->updateServerLastMovementStamp();
	}

	return ret;

	//return 0;
}

void PlayerManagerImplementation::lootAll(CreatureObject* player, CreatureObject* ai) {
	Locker locker(ai, player);

	if (!ai->isDead() || player->isDead())
		return;

	if (ai->getDistanceTo(player) > 6) {
		player->sendSystemMessage("@pet/droid_modules:corpse_too_far");
		return;
	}

	SceneObject* creatureInventory = ai->getSlottedObject("inventory");

	if (creatureInventory == NULL)
		return;

	if (creatureInventory->getContainerPermissions()->getOwnerID() != player->getObjectID() && creatureInventory->getContainerPermissions()->getOwnerID() != player->getGroupID()) {
		player->sendSystemMessage("@error_message:no_corpse_permission"); //You do not have permission to access this corpse.

		return;
	}

	int cashCredits = ai->getCashCredits();

	if (cashCredits > 0) {
		player->addCashCredits(cashCredits, true);
		ai->setCashCredits(0);

		StringIdChatParameter param("base_player", "prose_coin_loot"); //You loot %DI credits from %TT.
		param.setDI(cashCredits);
		param.setTT(ai);

		player->sendSystemMessage(param);
	}

	ai->notifyObservers(ObserverEventType::LOOTCREATURE, player, 0);

	SceneObject* playerInventory = player->getSlottedObject("inventory");

	if (playerInventory == NULL)
		return;

	int totalItems = creatureInventory->getContainerObjectsSize();

	if (totalItems < 1) {
		rescheduleCorpseDestruction(player, ai);
		return;
	}

	StringBuffer args;
	args << playerInventory->getObjectID() << " -1 0 0 0";

	String stringArgs = args.toString();

	for (int i = totalItems - 1; i >= 0; --i) {
		SceneObject* object = creatureInventory->getContainerObject(i);

		player->executeObjectControllerAction(String("transferitemmisc").hashCode(), object->getObjectID(), stringArgs);
	}

	if (creatureInventory->getContainerObjectsSize() <= 0) {
		player->sendSystemMessage("@base_player:corpse_looted"); //You have completely looted the corpse of all items.

		rescheduleCorpseDestruction(player, ai);
	}
}

void PlayerManagerImplementation::sendStartingLocationsTo(CreatureObject* player) {
	StartingLocationListMessage* slm = new StartingLocationListMessage(player);
	startingLocationList.insertToMessage(slm);

	player->sendMessage(slm);
}

StartingLocation* PlayerManagerImplementation::getStartingLocation(const String& city) {
	for (int i = 0; i < startingLocationList.size(); ++i) {
		StartingLocation* loc = &startingLocationList.get(i);

		if (loc == NULL)
			continue;

		if (loc->getLocation() == city)
			return loc;
	}

	return NULL;
}

void PlayerManagerImplementation::addInsurableItemsRecursive(SceneObject* obj, SortedVector<ManagedReference<SceneObject*> >* items, bool onlyInsurable) {
	for (int j = 0; j < obj->getContainerObjectsSize(); j++) {
		SceneObject* object = obj->getContainerObject(j);

		if (!object->isTangibleObject())
			continue;

		TangibleObject* item = cast<TangibleObject*>( object);

		if(item == NULL || item->hasAntiDecayKit())
			continue;

		if (!(item->getOptionsBitmask() & OptionBitmask::INSURED) && (item->isArmorObject() || item->isWearableObject())) {
			items->put(item);
		} else if ((item->getOptionsBitmask() & OptionBitmask::INSURED) && (item->isArmorObject() || item->isWearableObject()) && !onlyInsurable) {
			items->put(item);
		}

		if (object->isContainerObject())
			addInsurableItemsRecursive(object, items, onlyInsurable);
	}
}

SortedVector<ManagedReference<SceneObject*> > PlayerManagerImplementation::getInsurableItems(CreatureObject* player, bool onlyInsurable) {
	SortedVector<ManagedReference<SceneObject*> > insurableItems;
	insurableItems.setNoDuplicateInsertPlan();

	if (player == NULL)
		return insurableItems;

	SceneObject* datapad = player->getSlottedObject("datapad");
	SceneObject* defweapon = player->getSlottedObject("default_weapon");
	SceneObject* bank = player->getSlottedObject("bank");

	for (int i = 0; i < player->getSlottedObjectsSize(); ++i) {
		SceneObject* container = player->getSlottedObject(i);

		if (container == datapad || container == NULL || container == bank || container == defweapon)
			continue;

		if (container->isTangibleObject()) {
			TangibleObject* item = cast<TangibleObject*>( container);

			if(item == NULL || item->hasAntiDecayKit())
				continue;

			if (!(item->getOptionsBitmask() & OptionBitmask::INSURED) && (item->isArmorObject() || item->isWearableObject())) {
				insurableItems.put(item);
			} else if ((item->getOptionsBitmask() & OptionBitmask::INSURED) && (item->isArmorObject() || item->isWearableObject()) && !onlyInsurable) {
				insurableItems.put(item);
			}
		}

		addInsurableItemsRecursive(container, &insurableItems, onlyInsurable);
	}

	return insurableItems;
}

int PlayerManagerImplementation::calculatePlayerLevel(CreatureObject* player) {

	ManagedReference<WeaponObject*> weapon = player->getWeapon();

	if (weapon == NULL) {
		player->error("player with NULL weapon");

		return 0;
	}

	String weaponType = weapon->getWeaponType();
	int skillMod = player->getSkillMod("private_" + weaponType + "_combat_difficulty");

	if (player->getPlayerObject() != NULL && player->getPlayerObject()->isJedi() && weapon->isJediWeapon())
		skillMod += player->getSkillMod("private_jedi_difficulty");

	int level = MIN(25, skillMod / 100 + 1);

	return level;
}

int PlayerManagerImplementation::calculatePlayerLevel(CreatureObject* player, String& xpType) {
	if (xpType.isEmpty() || xpType == "jedi_general")
		return calculatePlayerLevel(player);

	String weaponType;
	if (xpType.contains("onehand"))
		weaponType = "onehandmelee";
	else if (xpType.contains("polearm"))
		weaponType = "polearm";
	else if (xpType.contains("twohand"))
		weaponType = "twohandmelee";
	else if (xpType.contains("unarmed"))
		weaponType = "unarmed";
	else if (xpType.contains("carbine"))
		weaponType = "carbine";
	else if (xpType.contains("pistol"))
		weaponType = "pistol";
	else if (xpType.contains("rifle"))
		weaponType = "rifle";
	else
		weaponType = "heavyweapon";

	int level = MIN(25, player->getSkillMod("private_" + weaponType + "_combat_difficulty") / 100 + 1);

	return level;
}

String PlayerManagerImplementation::getBadgeKey(int idx) {
	VectorMapEntry<int, String> entry = badgeMap.elementAt(idx);

	return entry.getValue();
}

CraftingStation* PlayerManagerImplementation::getNearbyCraftingStation(CreatureObject* player, int type) {

	ManagedReference<Zone*> zone = player->getZone();

	if (zone == NULL)
		return NULL;

	ManagedReference<ZoneServer*> server = zone->getZoneServer();

	if (server == NULL)
		return NULL;

	ManagedReference<CraftingStation*> station = NULL;

	//Locker locker(zone);

	SortedVector < QuadTreeEntry* > *closeObjects = new SortedVector<QuadTreeEntry*>(100, 50);
	CloseObjectsVector* vec = (CloseObjectsVector*) player->getCloseObjects();
	vec->safeCopyTo(*closeObjects);

	for (int i = 0; i < closeObjects->size(); ++i) {
		SceneObject* scno = cast<SceneObject*> (closeObjects->get(i));
		if (scno->isCraftingStation() && (abs(scno->getPositionZ() - player->getPositionZ()) < 7.0f) && player->isInRange(scno, 7.0f)) {

			station = server->getObject(scno->getObjectID()).castTo<CraftingStation*>();

			if (station == NULL)
				continue;

			ManagedReference<SceneObject*> parent = station->getParent().get();

			if (parent != NULL && !parent->isCellObject())
				continue;

			if (type == station->getStationType() || (type
					== CraftingTool::JEDI && station->getStationType()
					== CraftingTool::WEAPON)) {

				return station;
			}
		}
		// dont check Z axis here just check in range call. z axis check for some reason returns a huge number when checking a mob standing on you.
		// in range should be sufficient
		if( scno->isDroidObject() && player->isInRange(scno, 7.0f)){
			// check the droids around
			DroidObject* droid = cast<DroidObject*>(scno);
			if (droid == NULL) {
				continue;
			}
			// only the player can benefit form thier droid
			if( droid->getLinkedCreature() != player ) {
				continue;
			}
			// check the droid
			station = droid->getCraftingStation(type);
			if (station != NULL) {
				return station;
			}
		}
	}

	return NULL;
}

void PlayerManagerImplementation::finishHologrind(CreatureObject* player) {

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost->hasSuiBoxWindowType(SuiWindowType::HOLOGRIND_UNLOCK))
		return;

	ManagedReference<SuiMessageBox*> box = new SuiMessageBox(player, SuiWindowType::NONE);
	box->setPromptTitle("@quest/force_sensitive/intro:force_sensitive"); // You feel a tingle in the Force.
	box->setPromptText("Perhaps you should meditate somewhere alone...");

	ghost->addSuiBox(box);
	player->sendMessage(box->generateMessage());

	SkillManager::instance()->awardSkill("force_title_jedi_novice", player, true, false, true);

	ghost->setJediState(1);

}

Account* PlayerManagerImplementation::getAccount(const String& username) {

	String name = username;

	Database::escapeString(name);

	StringBuffer query;
	query << "SELECT a.active, a.username, a.password, a.salt, a.account_id, a.station_id, UNIX_TIMESTAMP(a.created), a.admin_level FROM accounts a WHERE a.username = '" << name << "' LIMIT 1;";

	return queryForAccount(query.toString());
}

Account* PlayerManagerImplementation::getAccount(uint32 accountID) {

	StringBuffer query;
	query << "SELECT a.active, a.username, a.password, a.salt, a.account_id, a.station_id, UNIX_TIMESTAMP(a.created), a.admin_level FROM accounts a WHERE a.account_id = '" << accountID << "' LIMIT 1;";

	return queryForAccount(query.toString());
}

Account* PlayerManagerImplementation::queryForAccount(const String& query) {
	Account* account = NULL;

	Reference<ResultSet*> result;

	try {
		result = ServerDatabase::instance()->executeQuery(query);
	} catch (DatabaseException& e) {
		error(e.getMessage());
	}

	if (result != NULL && result->next()) {

		account = new Account();

		account->setActive(result->getBoolean(0));
		account->setUsername(result->getString(1));

		account->setAccountID(result->getUnsignedInt(4));
		account->setStationID(result->getUnsignedInt(5));

		account->setTimeCreated(result->getUnsignedInt(6));
		account->setAdminLevel(result->getInt(7));

		account->updateFromDatabase();
	}

	result = NULL;

	return account;
}

String PlayerManagerImplementation::banAccount(PlayerObject* admin, Account* account, uint32 seconds, const String& reason) {

	if(admin == NULL || !admin->isPrivileged())
		return "";

	if(account == NULL)
		return "Account Not Found";

	String escapedReason = reason;
	Database::escapeString(escapedReason);

	try {
		StringBuffer query;
		query << "INSERT INTO account_bans values (NULL, " << account->getAccountID() << ", " << admin->getAccountID() << ", now(), " << (uint64)time(0) + seconds << ", '" << escapedReason << "');";

		ServerDatabase::instance()->executeStatement(query);
	} catch(Exception& e) {
		return "Exception banning account: " + e.getMessage();
	}

	try {

		CharacterList* characters = account->getCharacterList();
		for(int i = 0; i < characters->size(); ++i) {
			CharacterListEntry* entry = &characters->get(i);
			if(entry->getGalaxyID() == server->getGalaxyID()) {

				ManagedReference<CreatureObject*> player = getPlayer(entry->getFirstName());
				if(player != NULL) {
					clearOwnedStructuresPermissions(player);

					if (player->isOnline()) {
						player->sendMessage(new LogoutMessage());

						Reference<ZoneClientSession*> session = player->getClient();

						if(session != NULL)
							session->disconnect(true);
					}
				}
			}
		}
	} catch(Exception& e) {
		return "Account Successfully Banned, but error kicking characters. " + e.getMessage();
	}

	return "Account Successfully Banned";
}

String PlayerManagerImplementation::unbanAccount(PlayerObject* admin, Account* account, const String& reason) {

	if(admin == NULL || !admin->isPrivileged())
		return "";

	if(account == NULL)
		return "Account Not Found";

	String escapedReason = reason;
	Database::escapeString(escapedReason);

	try {
		StringBuffer query;
		query << "UPDATE account_bans SET expires = UNIX_TIMESTAMP(), reason = '" << escapedReason << "'  WHERE account_id = " << account->getAccountID() << " and expires > UNIX_TIMESTAMP();";

		ServerDatabase::instance()->executeStatement(query);
	} catch(Exception& e) {
		return "Exception unbanning account: " + e.getMessage();
	}

	return "Account Successfully Unbanned";
}

String PlayerManagerImplementation::banFromGalaxy(PlayerObject* admin, Account* account, const uint32 galaxy, uint32 seconds, const String& reason) {

	if(admin == NULL || !admin->isPrivileged())
		return "";

	if(account == NULL)
		return "Account Not Found";

	String escapedReason = reason;
	Database::escapeString(escapedReason);

	try {
		StringBuffer query;
		query << "INSERT INTO galaxy_bans values (NULL, " << account->getAccountID() << ", " << admin->getAccountID() << "," << galaxy << ", now()," << (uint64)time(0) + seconds << ", '" << escapedReason << "');";

		ServerDatabase::instance()->executeStatement(query);
	} catch(Exception& e) {
		return "Exception banning from galaxy: " + e.getMessage();
	}

	try {

		if (server->getGalaxyID() == galaxy) {
			CharacterList* characters = account->getCharacterList();
			for(int i = 0; i < characters->size(); ++i) {
				CharacterListEntry* entry = &characters->get(i);
				if(entry->getGalaxyID() == galaxy) {

					ManagedReference<CreatureObject*> player = getPlayer(entry->getFirstName());
					if(player != NULL) {
						clearOwnedStructuresPermissions(player);

						if (player->isOnline()) {
							player->sendMessage(new LogoutMessage());

							ManagedReference<ZoneClientSession*> session = player->getClient();

							if(session != NULL)
								session->disconnect(true);
						}
					}
				}
			}
		} else {
			return "Successfully Banned from Galaxy, but cannot kick characters because Galaxy is not your current galaxy.";
		}
	} catch(Exception& e) {
		return "Successfully Banned from Galaxy, but error kicking characters. " + e.getMessage();
	}

	return "Successfully Banned from Galaxy";
}

String PlayerManagerImplementation::unbanFromGalaxy(PlayerObject* admin, Account* account, const uint32 galaxy, const String& reason) {

	if(admin == NULL || !admin->isPrivileged())
		return "";

	if(account == NULL)
		return "Account Not Found";

	String escapedReason = reason;
	Database::escapeString(escapedReason);

	try {
		StringBuffer query;

		query << "UPDATE galaxy_bans SET expires = UNIX_TIMESTAMP(), reason = '" << escapedReason << "' WHERE account_id = " <<  account->getAccountID() << " and galaxy_id = " << galaxy << " and expires > UNIX_TIMESTAMP();";

		ServerDatabase::instance()->executeStatement(query);
	} catch(Exception& e) {
		return "Exception unbanning from galaxy: " + e.getMessage();
	}

	return "Successfully Unbanned from Galaxy";
}

String PlayerManagerImplementation::banCharacter(PlayerObject* admin, Account* account, const String& name, const uint32 galaxyID, uint32 seconds, const String& reason) {

	if(admin == NULL || !admin->isPrivileged())
		return "";

	if(account == NULL)
		return "Account Not Found";

	String escapedReason = reason;
	Database::escapeString(escapedReason);

	String escapedName = name;
	Database::escapeString(escapedName);

	try {
		StringBuffer query;
		query << "INSERT INTO character_bans values (NULL, " << account->getAccountID() << ", " << admin->getAccountID() << ", " << galaxyID << ", '" << escapedName << "', " <<  "now(), UNIX_TIMESTAMP() + " << seconds << ", '" << escapedReason << "');";

		ServerDatabase::instance()->executeStatement(query);
	} catch(Exception& e) {
		return "Exception banning character: " + e.getMessage();
	}

	try {
		if (server->getGalaxyID() == galaxyID) {
			ManagedReference<CreatureObject*> player = getPlayer(name);
			if(player != NULL) {
				clearOwnedStructuresPermissions(player);

				if (player->isOnline()) {
					player->sendMessage(new LogoutMessage());

					ManagedReference<ZoneClientSession*> session = player->getClient();

					if(session != NULL)
						session->disconnect(true);
				}
			}
		} else {
			return "Character Successfully Banned, but cannot kick character because it's on a different galaxy.";
		}
	} catch(Exception& e) {
		return "Character Successfully Banned, but error kicking Character. " + e.getMessage();
	}

	return "Character Successfully Banned";
}

String PlayerManagerImplementation::unbanCharacter(PlayerObject* admin, Account* account, const String& name, const uint32 galaxyID, const String& reason) {

	if(admin == NULL || !admin->isPrivileged())
		return "";

	if(account == NULL)
		return "Account Not Found";

	String escapedReason = reason;
	Database::escapeString(escapedReason);

	String escapedName = name;
	Database::escapeString(escapedName);

	try {
		StringBuffer query;
		query << "UPDATE character_bans SET expires = UNIX_TIMESTAMP(), reason = '" << escapedReason << "' WHERE account_id = " <<  account->getAccountID() << " AND galaxy_id = " << galaxyID << " and name =  '" << escapedName << "' and expires > UNIX_TIMESTAMP();";

		ServerDatabase::instance()->executeStatement(query);
	} catch(Exception& e) {
		return "Exception banning character: " + e.getMessage();
	}

	return "Character Successfully Unbanned";
}

void PlayerManagerImplementation::clearOwnedStructuresPermissions(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL) {
		return;
	}

	for (int i = 0; i < ghost->getTotalOwnedStructureCount(); i++) {
		uint64 structureID = ghost->getOwnedStructure(i);

		ManagedReference<StructureObject*> structure = server->getObject(structureID).castTo<StructureObject*>();

		if (structure == NULL) {
			continue;
		}

		structure->revokeAllPermissions();
	}
}

void PlayerManagerImplementation::fixHAM(CreatureObject* player) {
	Locker locker(player);

	try {
		BuffList* buffs = player->getBuffList();

		VectorMap<byte, int> attributeValues;
		attributeValues.setNullValue(0);
		attributeValues.setAllowOverwriteInsertPlan();

		ManagedReference<Buff*> powerBoost;

		//check buffs
		for (int i = 0; i < buffs->getBuffListSize(); ++i) {
			ManagedReference<Buff*> buff = buffs->getBuffByIndex(i);

			PowerBoostBuff* power = dynamic_cast<PowerBoostBuff*>(buff.get());

			if (power != NULL) {
				powerBoost = power;
				continue;
			}

			VectorMap<byte, int>* attributeModifiers = buff->getAttributeModifiers();

			for (int j = 0; j < attributeModifiers->size(); ++j) {
				byte modifier = attributeModifiers->elementAt(j).getKey();
				int val = attributeModifiers->elementAt(j).getValue();

				attributeValues.put(modifier, attributeValues.get(modifier) + val);
			}
		}

		if (powerBoost != NULL)
			player->removeBuff(powerBoost);

		int encumbranceType = -1;

		for (int i = 0; i < 9; ++i) {
			int maxModifier = attributeValues.get((byte)i);
			int baseHam = player->getBaseHAM(i);
			int max = player->getMaxHAM(i);

			int calculated = baseHam + maxModifier;

			if (i % 3 == 0) {
				++encumbranceType;
			} else {
				calculated -= player->getEncumbrance(encumbranceType);
			}

			//info("attribute: " + CreatureAttribute::getName(i, true) + " max = " + String::valueOf(max) + " calculatedMax = " + String::valueOf(calculated), true);

			if (calculated != max && calculated > 1) {
				if (player->getHAM(i) > calculated)
					player->setHAM(i, calculated, false);

				player->setMaxHAM(i, calculated, false);
			}
		}
	} catch (Exception& e) {
		error(e.getMessage());
	}
}

bool PlayerManagerImplementation::promptTeachableSkills(CreatureObject* teacher, SceneObject* target) {
	if (target == NULL || !target->isPlayerCreature()) {
		teacher->sendSystemMessage("@teaching:no_target"); //Whom do you want to teach?
		return false;
	}

	if (target == teacher) {
		teacher->sendSystemMessage("@teaching:no_teach_self"); //You cannot teach yourself.
		return false;
	}

	Locker _lock(target, teacher);

	//We checked if they had the player object in slot with isPlayerCreature
	CreatureObject* student = cast<CreatureObject*>(target);

	if (teacher->getGroup() == NULL || student->getGroup() != teacher->getGroup()) {
		StringIdChatParameter params("teaching", "not_in_same_group"); //You must be within the same group as %TT in order to teach.
		params.setTT(student->getDisplayedName());
		teacher->sendSystemMessage(params);
		return false;
	}

	if (student->isDead()) {
		StringIdChatParameter params("teaching", "student_dead"); //%TT does not feel like being taught right now.
		params.setTT(student->getDisplayedName());
		teacher->sendSystemMessage(params);
		return false;
	}

	if (!student->isInRange(teacher, 32.f)) {
		teacher->sendSystemMessage("@teaching:student_too_far"); // Your student must be nearby in order to teach.
		return false;
	}

	ManagedReference<PlayerObject*> studentGhost = student->getPlayerObject();

	//Do they have an outstanding teaching offer?
	if (studentGhost->hasSuiBoxWindowType(SuiWindowType::TEACH_OFFER)) {
		StringIdChatParameter params("teaching", "student_has_offer_to_learn"); //%TT already has an offer to learn.
		params.setTT(student->getDisplayedName());
		teacher->sendSystemMessage(params);
		return false;
	}

	SortedVector<String> skills = getTeachableSkills(teacher, student);

	if (skills.size() <= 0) {
		StringIdChatParameter params("teaching", "no_skills_for_student"); //You have no skills that  %TT can currently learn."
		params.setTT(student->getDisplayedName());
		teacher->sendSystemMessage(params);
		return false;
	}

	ManagedReference<SuiListBox*> listbox = new SuiListBox(teacher, SuiWindowType::TEACH_SKILL);
	listbox->setUsingObject(student);
	listbox->setForceCloseDistance(32.f);
	listbox->setPromptTitle("SELECT SKILL");
	listbox->setPromptText("Select a skill to teach.");
	listbox->setCancelButton(true, "@cancel");

	for (int i = 0; i < skills.size(); ++i) {
		String skill = skills.get(i);
		listbox->addMenuItem("@skl_n:" + skill, skill.hashCode());
	}

	listbox->setCallback(new PlayerTeachSuiCallback(server));

	if (teacher->isPlayerCreature()) {
		ManagedReference<PlayerObject*> teacherGhost = teacher->getPlayerObject();

		teacherGhost->addSuiBox(listbox);
	}

	teacher->sendMessage(listbox->generateMessage());

	return true;
}

bool PlayerManagerImplementation::offerTeaching(CreatureObject* teacher, CreatureObject* student, Skill* skill) {
	ManagedReference<PlayerObject*> studentGhost = student->getPlayerObject();

	//Do they have an outstanding teaching offer?
	if (studentGhost->hasSuiBoxWindowType(SuiWindowType::TEACH_OFFER)) {
		StringIdChatParameter params("teaching", "student_has_offer_to_learn"); //%TT already has an offer to learn.
		params.setTT(student->getDisplayedName());
		teacher->sendSystemMessage(params);
		return false;
	}

	ManagedReference<SuiMessageBox*> suibox = new SuiMessageBox(teacher, SuiWindowType::TEACH_OFFER);
	suibox->setUsingObject(teacher);
	suibox->setForceCloseDistance(32.f);
	suibox->setPromptTitle("@sui:swg"); //Star Wars Galaxies

	StringIdManager* sidman = StringIdManager::instance();

	String sklname = sidman->getStringId(String("@skl_n:" + skill->getSkillName()).hashCode()).toString();
	String expname = sidman->getStringId(String("@exp_n:" + skill->getXpType()).hashCode()).toString();

	StringBuffer prompt;
	prompt << teacher->getDisplayedName()
															<< " has offered to teach you " << sklname << " (" << skill->getXpCost()
															<< " " << expname  << " experience cost).";

	suibox->setPromptText(prompt.toString());
	suibox->setCallback(new PlayerTeachConfirmSuiCallback(server, skill));

	suibox->setOkButton(true, "@yes");
	suibox->setCancelButton(true, "@no");

	studentGhost->addSuiBox(suibox);
	student->sendMessage(suibox->generateMessage());

	StringIdChatParameter params("teaching", "offer_given"); //You offer to teach %TT %TO.
	params.setTT(student->getDisplayedName());
	params.setTO("@skl_n:" + skill->getSkillName());
	teacher->sendSystemMessage(params);

	return true;
}

bool PlayerManagerImplementation::acceptTeachingOffer(CreatureObject* teacher, CreatureObject* student, Skill* skill) {
	if (teacher->getGroup() == NULL || student->getGroup() != teacher->getGroup()) {
		StringIdChatParameter params("teaching", "not_in_same_group"); //You must be within the same group as %TT in order to teach.
		params.setTT(student->getDisplayedName());
		teacher->sendSystemMessage(params);
		return false;
	}

	//Check to see if the teacher still has the skill and the student can still learn the skill.
	SkillManager* skillManager = SkillManager::instance();

	if (!student->isInRange(teacher, 32.f)) {
		StringIdChatParameter params("teaching", "teacher_too_far_target"); //You are too far away from %TT to learn.
		params.setTT(teacher->getDisplayedName());
		student->sendSystemMessage(params);

		params.setStringId("teaching", "student_too_far_target");
		params.setTT(student->getDisplayedName()); //You are too far away from %TT to teach.
		teacher->sendSystemMessage(params);
		return false;
	}

	if (teacher->hasSkill(skill->getSkillName()) && skillManager->awardSkill(skill->getSkillName(), student, true, false, false)) {
		StringIdChatParameter params("teaching", "student_skill_learned"); //You learn %TO from %TT.
		params.setTO("@skl_n:" + skill->getSkillName());
		params.setTT(teacher->getDisplayedName());
		student->sendSystemMessage(params);

		params.setStringId("teaching", "teacher_skill_learned"); //%TT learns %TO from you.
		params.setTT(student->getDisplayedName());
		teacher->sendSystemMessage(params);

		if (skillManager->isApprenticeshipEnabled() && !skill->getSkillName().endsWith("novice")) {
			int exp = 10 + (skill->getTotalChildren() * 10);

			StringIdChatParameter params("teaching", "experience_received"); //You have received %DI Apprenticeship experience.
			params.setDI(exp);
			teacher->sendSystemMessage(params);

			awardExperience(teacher, "apprenticeship", exp, false);
		}
	} else {
		student->sendSystemMessage("@teaching:learning_failed"); //Learning failed.
		teacher->sendSystemMessage("@teaching:teaching_failed"); //Teaching failed.
		return false;
	}

	return true;
}

SortedVector<String> PlayerManagerImplementation::getTeachableSkills(CreatureObject* teacher, CreatureObject* student) {
	SortedVector<String> skills;
	skills.setNoDuplicateInsertPlan();

	SkillList* skillList = teacher->getSkillList();

	SkillManager* skillManager = SkillManager::instance();

	for (int i = 0; i < skillList->size(); ++i) {
		Skill* skill = skillList->get(i);

		String skillName = skill->getSkillName();

		if (!(skillName.contains("novice") || skillName.contains("force_sensitive") || skillName.contains("force_rank") || skillName.contains("force_title")) && skillManager->canLearnSkill(skillName, student, false))
			skills.put(skillName);
	}	

	return skills;
}

void PlayerManagerImplementation::decreaseOnlineCharCount(ZoneClientSession* client) {
	Locker locker(&onlineMapMutex);

	uint32 accountId = client->getAccountID();

	if (!onlineZoneClientMap.containsKey(accountId))
		return;

	BaseClientProxy* session = client->getSession();



	Vector<Reference<ZoneClientSession*> > clients = onlineZoneClientMap.get(accountId);

	for (int i = 0; i < clients.size(); ++i)
		if (clients.get(i) == client) {
			clients.remove(i);

			break;
		}

	if (clients.size() == 0)
		onlineZoneClientMap.remove(accountId);
	else
		onlineZoneClientMap.put(accountId, clients);

	locker.release();

	if (session != NULL) {
		onlineZoneClientMap.accountLoggedOut(session->getIPAddress(), accountId);
	}
}

void PlayerManagerImplementation::proposeUnity( CreatureObject* askingPlayer, CreatureObject* respondingPlayer, SceneObject* askingPlayerRing ){

	if( !askingPlayer->isPlayerCreature() ){
		return;
	}

	// Check if target is self
	if( askingPlayer == respondingPlayer ){
		askingPlayer->sendSystemMessage("@unity:bad_target"); // "You must have a valid player target to Propose Unity."
		return;
	}

	// Check if target is a player
	if( !respondingPlayer->isPlayerCreature() ){
		askingPlayer->sendSystemMessage("@unity:bad_target"); // "You must have a valid player target to Propose Unity."
		return;
	}

	Reference<PlayerObject*> askingGhost = askingPlayer->getPlayerObject();
	Reference<PlayerObject*> respondingGhost = respondingPlayer->getPlayerObject();
	if( askingGhost == NULL || respondingGhost == NULL ){
		return;
	}

	// Check if askingPlayer is married
	if( askingGhost->isMarried() ){
		StringIdChatParameter errAskerMarried;
		errAskerMarried.setStringId("unity", "prose_already_married"); // "You cannot propose unity. You are already united with %TO."
		errAskerMarried.setTO( askingGhost->getSpouseName() );
		askingPlayer->sendSystemMessage( errAskerMarried );
		return;
	}

	// Check if respondingPlayer is married
	if( respondingGhost->isMarried() ){
		askingPlayer->sendSystemMessage("@unity:target_married"); // "You cannot propose unity to someone who is already united."
		return;
	}

	// Check distance
	if( !respondingPlayer->isInRange( askingPlayer, 15.0 ) ){
		askingPlayer->sendSystemMessage("@unity:out_of_range"); // "Your target is too far away to properly propose!"
		return;
	}

	// TODO: Check facing
	// askingPlayer->sendSystemMessage("@unity:bad_facing");// "You must be facing your target to properly propose!"

	// Check if asking player has a proposal outstanding
	if( askingPlayer->getActiveSession(SessionFacadeType::PROPOSEUNITY) != NULL ){
		askingPlayer->sendSystemMessage("But you already have an outstanding unity proposal");
		return;
	}

	// Check if responding player has a proposal outstanding
	if( respondingPlayer->getActiveSession(SessionFacadeType::PROPOSEUNITY) != NULL ){
		askingPlayer->sendSystemMessage("@unity:target_proposed"); // "Your proposal target is already engaged in a unity proposal."
		return;
	}

	//
	// All checks passed
	//

	Locker rlocker( askingPlayer, respondingPlayer );

	// Initialize session
	ManagedReference<ProposeUnitySession*> askerUnitySession =
			new ProposeUnitySession( askingPlayer->getObjectID(), respondingPlayer->getObjectID(), askingPlayerRing->getObjectID() );
	askingPlayer->addActiveSession(SessionFacadeType::PROPOSEUNITY, askerUnitySession);

	ManagedReference<ProposeUnitySession*> responderUnitySession =
			new ProposeUnitySession( askingPlayer->getObjectID(), respondingPlayer->getObjectID(), askingPlayerRing->getObjectID() );
	respondingPlayer->addActiveSession(SessionFacadeType::PROPOSEUNITY, responderUnitySession);

	// Submit timeout task
	Reference<Task*> askerExpiredTask = new ProposeUnityExpiredTask( askingPlayer );
	askingPlayer->addPendingTask("propose_unity", askerExpiredTask, 60000); // 1 min

	Reference<Task*> responderExpiredTask = new ProposeUnityExpiredTask( respondingPlayer );
	respondingPlayer->addPendingTask("propose_unity", responderExpiredTask, 60000); // 1 min

	// Build and send proposal window
	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(respondingPlayer, SuiWindowType::PROPOSE_UNITY);
	suiBox->setCallback(new ProposeUnitySuiCallback(server));
	suiBox->setPromptTitle("@unity:accept_title"); // "Accept Unity Proposal?"
	suiBox->setPromptText( askingPlayer->getCreatureName().toString() + " is proposing unity to you. Do you wish to accept?" );
	suiBox->setUsingObject( askingPlayer );
	suiBox->setCancelButton(true, "@no");
	suiBox->setOkButton(true, "@yes");

	respondingGhost->addSuiBox(suiBox);
	respondingPlayer->sendMessage(suiBox->generateMessage());

	// Send message to asking player
	StringIdChatParameter proposalSent;
	proposalSent.setStringId("unity", "prose_propose"); // "You propose unity to %TO."
	proposalSent.setTO( respondingPlayer->getFirstName() );
	askingPlayer->sendSystemMessage( proposalSent );

}

void PlayerManagerImplementation::denyUnity( CreatureObject* respondingPlayer ){

	if( respondingPlayer == NULL )
		return;

	// Check session
	ManagedReference<ProposeUnitySession*> proposeUnitySession = respondingPlayer->getActiveSession(SessionFacadeType::PROPOSEUNITY).castTo<ProposeUnitySession*>();
	if( proposeUnitySession == NULL ){
		respondingPlayer->sendSystemMessage("@unity:expire_target"); // "The unity proposal extended to you has expired."
		return;
	}

	// Pull asking player
	uint64 targID = proposeUnitySession->getAskingPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);
	if( obj == NULL || !obj->isPlayerCreature() ){
		respondingPlayer->sendSystemMessage("@unity:wed_error"); // "An error has occurred during the unity process."
		return;
	}

	CreatureObject* askingPlayer = cast<CreatureObject*>( obj.get());
	Locker alocker( askingPlayer, respondingPlayer );
	askingPlayer->sendSystemMessage("@unity:declined"); // "Your unity proposal has been declined.")
	respondingPlayer->sendSystemMessage("@unity:decline"); // "You decline the unity proposal.")

	// Remove session
	cancelProposeUnitySession(respondingPlayer, askingPlayer);

}

void PlayerManagerImplementation::acceptUnity( CreatureObject* respondingPlayer ){

	if( respondingPlayer == NULL )
		return;

	// Check session
	ManagedReference<ProposeUnitySession*> proposeUnitySession = respondingPlayer->getActiveSession(SessionFacadeType::PROPOSEUNITY).castTo<ProposeUnitySession*>();
	if( proposeUnitySession == NULL ){
		respondingPlayer->sendSystemMessage("@unity:expire_target"); // "The unity proposal extended to you has expired."
		return;
	}

	// Pull asking player
	uint64 targID = proposeUnitySession->getAskingPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);
	if( obj == NULL || !obj->isPlayerCreature() ){
		respondingPlayer->sendSystemMessage("@unity:wed_error"); // "An error has occurred during the unity process."
		return;
	}

	CreatureObject* askingPlayer = cast<CreatureObject*>( obj.get());
	Locker alocker( askingPlayer, respondingPlayer );

	// Check distance
	if( !respondingPlayer->isInRange( askingPlayer, 15.0 ) ){
		askingPlayer->sendSystemMessage("@unity:wed_oor"); // "You must remain within 15 meters during the unity process for it to complete."
		respondingPlayer->sendSystemMessage("@unity:wed_oor"); // "You must remain within 15 meters during the unity process for it to complete."
		cancelProposeUnitySession(respondingPlayer, askingPlayer);
		return;
	}

	// Check for a ring in player's inventory
	ManagedReference<SceneObject*> inventory = respondingPlayer->getSlottedObject("inventory");
	if( inventory == NULL ){
		respondingPlayer->sendSystemMessage("@unity:wed_error"); // "An error has occurred during the unity process."
		askingPlayer->sendSystemMessage("@unity:wed_error"); // "An error has occurred during the unity process."
		cancelProposeUnitySession(respondingPlayer, askingPlayer);
		return;
	}

	bool hasRing = false;
	for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
		ManagedReference<WearableObject*> wearable = cast<WearableObject*>(inventory->getContainerObject(i).get());
		if( wearable != NULL && wearable->getGameObjectType() == SceneObjectType::RING && !wearable->isEquipped() ){
			hasRing = true;
		}
	}

	// No ring found
	if( !hasRing ){
		askingPlayer->sendSystemMessage("@unity:accept_fail"); // "Your proposal target has no ring to offer in return."
		respondingPlayer->sendSystemMessage("@unity:no_ring"); // "You cannot accept a unity proposal without a ring to offer."
		cancelProposeUnitySession(respondingPlayer, askingPlayer);
		return;
	}

	// Build and send list box for ring selection
	ManagedReference<SuiListBox*> box = new SuiListBox(respondingPlayer, SuiWindowType::SELECT_UNITY_RING, SuiListBox::HANDLETWOBUTTON);
	box->setCallback(new SelectUnityRingSuiCallback(server));
	box->setPromptText("@unity:ring_prompt"); // "Select the ring you would like to offer, in return, for your unity."
	box->setPromptTitle("Select Unity Ring");
	box->setOkButton(true, "@ok");
	box->setCancelButton(true, "@cancel");

	for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
		ManagedReference<WearableObject*> wearable = cast<WearableObject*>(inventory->getContainerObject(i).get());
		if( wearable != NULL && wearable->getGameObjectType() == SceneObjectType::RING && !wearable->isEquipped() && !wearable->isNoTrade() ){
			String itemName = wearable->getDisplayedName();
			box->addMenuItem(itemName, wearable->getObjectID());
		}
	}

	box->setUsingObject(respondingPlayer);
	respondingPlayer->getPlayerObject()->addSuiBox(box);
	respondingPlayer->sendMessage(box->generateMessage());

}

void PlayerManagerImplementation::completeUnity( CreatureObject* respondingPlayer, unsigned long long respondingPlayerRingId ){

	if( respondingPlayer == NULL )
		return;

	// Check session
	ManagedReference<ProposeUnitySession*> proposeUnitySession = respondingPlayer->getActiveSession(SessionFacadeType::PROPOSEUNITY).castTo<ProposeUnitySession*>();
	if( proposeUnitySession == NULL ){
		respondingPlayer->sendSystemMessage("@unity:expire_target"); // "The unity proposal extended to you has expired."
		return;
	}

	// Pull asking player
	uint64 targID = proposeUnitySession->getAskingPlayer();
	ManagedReference<SceneObject*> obj = server->getObject(targID);
	if( obj == NULL || !obj->isPlayerCreature() ){
		respondingPlayer->sendSystemMessage("@unity:wed_error"); // "An error has occurred during the unity process."
		return;
	}

	CreatureObject* askingPlayer = cast<CreatureObject*>( obj.get());
	Locker alocker( askingPlayer, respondingPlayer );

	// Check distance
	if( !respondingPlayer->isInRange( askingPlayer, 15.0 ) ){
		askingPlayer->sendSystemMessage("@unity:wed_oor"); // "You must remain within 15 meters during the unity process for it to complete."
		respondingPlayer->sendSystemMessage("@unity:wed_oor"); // "You must remain within 15 meters during the unity process for it to complete."
		cancelProposeUnitySession(respondingPlayer, askingPlayer);
		return;
	}

	// Find selected ring
	ManagedReference<SceneObject*> respondingPlayerInventory = respondingPlayer->getSlottedObject("inventory");
	ManagedReference<SceneObject*> askingPlayerInventory = askingPlayer->getSlottedObject("inventory");
	if( respondingPlayerInventory == NULL || askingPlayerInventory == NULL ){
		respondingPlayer->sendSystemMessage("@unity:wed_error"); // "An error has occurred during the unity process."
		askingPlayer->sendSystemMessage("@unity:wed_error"); // "An error has occurred during the unity process."
		cancelProposeUnitySession(respondingPlayer, askingPlayer);
		return;
	}

	// Find responder's ring
	ManagedReference<WearableObject*> wearable = NULL;
	ManagedReference<WearableObject*> respondingRing = NULL;
	for (int i = 0; i < respondingPlayerInventory->getContainerObjectsSize(); i++) {
		wearable = cast<WearableObject*>(respondingPlayerInventory->getContainerObject(i).get());
		if( wearable != NULL && wearable->getObjectID() == respondingPlayerRingId && !wearable->isEquipped() ){
			respondingRing = wearable;
			break;
		}
	}

	// Find asker's ring
	wearable = NULL;
	ManagedReference<WearableObject*> askingRing = NULL;
	for (int i = 0; i < askingPlayerInventory->getContainerObjectsSize(); i++) {
		wearable = cast<WearableObject*>(askingPlayerInventory->getContainerObject(i).get());
		if( wearable != NULL && wearable->getObjectID() == proposeUnitySession->getAskingPlayerRing() && !wearable->isEquipped() ){
			askingRing = wearable;
			break;
		}
	}


	// Rings not found
	if( respondingRing == NULL || askingRing == NULL ){
		askingPlayer->sendSystemMessage("@unity:accept_fail"); // "Your proposal target has no ring to offer in return."
		respondingPlayer->sendSystemMessage("@unity:no_ring"); // "You cannot accept a unity proposal without a ring to offer."
		cancelProposeUnitySession(respondingPlayer, askingPlayer);
		return;
	}

	// Exchange rings
	ManagedReference<ObjectController*> objectController = server->getObjectController();
	if (objectController->transferObject(askingRing, respondingPlayerInventory, -1, true, true)){ // Allow overflow
		askingRing->sendDestroyTo(askingPlayer);
		respondingPlayerInventory->broadcastObject(askingRing, true);
	}

	if (objectController->transferObject(respondingRing, askingPlayerInventory, -1, true, true)){ // Allow overflow
		respondingRing->sendDestroyTo(respondingPlayer);
		askingPlayerInventory->broadcastObject(respondingRing, true);
	}

	// Set married
	String respondingPlayerName = respondingPlayer->getFirstName();
	String askingPlayerName = askingPlayer->getFirstName();
	askingPlayer->getPlayerObject()->setSpouseName( respondingPlayerName );
	respondingPlayer->getPlayerObject()->setSpouseName( askingPlayerName );

	// Send obligatory congratulations
	StringIdChatParameter congratsAsker;
	congratsAsker.setStringId("unity", "prose_wed_complete"); //  "Your union with %TT is complete."
	congratsAsker.setTT( respondingPlayer->getFirstName() );
	askingPlayer->sendSystemMessage( congratsAsker );

	StringIdChatParameter congratsResponder;
	congratsResponder.setStringId("unity", "prose_wed_complete"); //  "Your union with %TT is complete."
	congratsResponder.setTT( askingPlayer->getFirstName() );
	respondingPlayer->sendSystemMessage( congratsResponder );

	// Remove session
	cancelProposeUnitySession(respondingPlayer, askingPlayer);

}

void PlayerManagerImplementation::cancelProposeUnitySession(CreatureObject* respondingPlayer, CreatureObject* askingPlayer){
	askingPlayer->dropActiveSession(SessionFacadeType::PROPOSEUNITY);
	respondingPlayer->dropActiveSession(SessionFacadeType::PROPOSEUNITY);
	askingPlayer->removePendingTask( "propose_unity" );
	respondingPlayer->removePendingTask( "propose_unity" );
}

void PlayerManagerImplementation::promptDivorce(CreatureObject* player){

	if( player == NULL || !player->isPlayerCreature())
		return;

	// Check if player is married
	PlayerObject* playerGhost = player->getPlayerObject();
	if( !playerGhost->isMarried() ){
		player->sendSystemMessage( "You are not united with anyone!" );
		return;
	}

	// Build and confirmation window
	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, SuiWindowType::CONFIRM_DIVORCE);
	suiBox->setCallback(new ConfirmDivorceSuiCallback(server));
	suiBox->setPromptTitle("Confirm Divorce?"); // "Accept Unity Proposal?"
	suiBox->setPromptText( "Do you wish to nullify your unity with " + playerGhost->getSpouseName() + "?" );
	suiBox->setCancelButton(true, "@no");
	suiBox->setOkButton(true, "@yes");

	playerGhost->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());

}

void PlayerManagerImplementation::grantDivorce(CreatureObject* player){

	if( player == NULL || !player->isPlayerCreature())
		return;

	// Check if player is married
	PlayerObject* playerGhost = player->getPlayerObject();
	if( !playerGhost->isMarried() )
		return;

	// Find spouse
	CreatureObject* spouse = getPlayer(playerGhost->getSpouseName());

	// Remove spouse name from both players
	if( spouse != NULL && spouse->isPlayerCreature() ){
		Locker slocker( spouse, player );

		PlayerObject* spouseGhost = spouse->getPlayerObject();
		spouseGhost->removeSpouse();
		playerGhost->removeSpouse();

		StringIdChatParameter spouseMsg;
		spouseMsg.setStringId("unity", "prose_end_unity"); // "Your union with %TO has ended."
		spouseMsg.setTO( player->getFirstName() );
		spouse->sendSystemMessage( spouseMsg );

		StringIdChatParameter playerMsg;
		playerMsg.setStringId("unity", "prose_end_unity"); //  "Your union with %TO has ended."
		playerMsg.setTO( spouse->getFirstName() );
		player->sendSystemMessage( playerMsg );

	}
	else{
		// If spouse player is null (perhaps it's been deleted), we can still remove the spouse from the current player

		StringIdChatParameter playerMsg;
		playerMsg.setStringId("unity", "prose_end_unity"); //  "Your union with %TO has ended."
		playerMsg.setTO( playerGhost->getSpouseName() );
		player->sendSystemMessage( playerMsg );

		playerGhost->removeSpouse();
	}

}

void PlayerManagerImplementation::claimVeteranRewards(CreatureObject* player){

	if( player == NULL || !player->isPlayerCreature() )
		return;

	PlayerObject* playerGhost = player->getPlayerObject();

	// Get account
	ManagedReference<Account*> account = getAccount( playerGhost->getAccountID() );
	if( account == NULL )
		return;

	// Send message with current account age
	StringIdChatParameter timeActiveMsg;
	timeActiveMsg.setStringId("veteran", "self_time_active"); // You have %DI days logged for veteran rewards.
	timeActiveMsg.setDI( account->getAgeInDays() );
	player->sendSystemMessage( timeActiveMsg );

	// Verify player is eligible for a reward
	int milestone = getEligibleMilestone( playerGhost, account );
	if( milestone < 0){
		player->sendSystemMessage( "@veteran:not_eligible"); // You are not currently eligible for a veteran reward.
		return;
	}

	// Verify player is not already choosing a reward
	if( player->getActiveSession(SessionFacadeType::VETERANREWARD) != NULL ){
		player->sendSystemMessage( "You are already attempting to claim a veteran reward." );
		return;
	}

	// Create session
	ManagedReference<VeteranRewardSession*> rewardSession =	new VeteranRewardSession( milestone );
	player->addActiveSession(SessionFacadeType::VETERANREWARD, rewardSession);

	// Build and SUI list box of rewards
	ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::SELECT_VETERAN_REWARD, SuiListBox::HANDLETWOBUTTON);
	box->setCallback(new SelectVeteranRewardSuiCallback(server));
	box->setPromptText("@veteran_new:choice_description" ); // You may choose one of the items listed below. This item will be placed in your inventory.
	box->setPromptTitle("@veteran_new:item_grant_box_title"); // Reward
	box->setOkButton(true, "@ok");
	box->setCancelButton(true, "@cancel");

	for( int i = 0; i < veteranRewards.size(); i++ ){

		// Any rewards at or below current milestone are eligible
		VeteranReward reward = veteranRewards.get(i);
		if( reward.getMilestone() <= milestone ){

			// Filter out one-time rewards already claimed
			if( reward.isOneTime() && playerGhost->hasChosenVeteranReward( reward.getTemplateFile() ) ){
				continue;
			}

			SharedObjectTemplate* rewardTemplate = TemplateManager::instance()->getTemplate( reward.getTemplateFile().hashCode() );
			if( rewardTemplate != NULL ){
				if( reward.getDescription().isEmpty() ){
					box->addMenuItem( rewardTemplate->getDetailedDescription(), i);
				}
				else{
					box->addMenuItem( reward.getDescription(), i);
				}
			}
		}
	}

	box->setUsingObject(NULL);
	playerGhost->addSuiBox(box);
	player->sendMessage(box->generateMessage());

}

void PlayerManagerImplementation::cancelVeteranRewardSession(CreatureObject* player){
	player->dropActiveSession(SessionFacadeType::VETERANREWARD);
}

void PlayerManagerImplementation::confirmVeteranReward(CreatureObject* player, int itemIndex ){

	if( player == NULL || !player->isPlayerCreature() ){
		return;
	}

	if( itemIndex < 0 || itemIndex >= veteranRewards.size() ){
		player->sendSystemMessage( "@veteran:reward_error"); //	The reward could not be granted.
		cancelVeteranRewardSession( player );
		return;
	}

	// Get account
	PlayerObject* playerGhost = player->getPlayerObject();
	ManagedReference<Account*> account = getAccount( playerGhost->getAccountID() );
	if( account == NULL ){
		player->sendSystemMessage( "@veteran:reward_error"); //	The reward could not be granted.
		cancelVeteranRewardSession( player );
		return;
	}

	// Check session
	ManagedReference<VeteranRewardSession*> rewardSession = player->getActiveSession(SessionFacadeType::VETERANREWARD).castTo<VeteranRewardSession*>();
	if( rewardSession == NULL ){
		player->sendSystemMessage( "@veteran:reward_error"); //	The reward could not be granted.
		return;
	}

	VeteranReward reward = veteranRewards.get(itemIndex);
	rewardSession->setSelectedRewardIndex(itemIndex);

	// Generate confirmation dialog if item is one-time.  Otherwise, just generate it.
	if( reward.isOneTime() ){

		ManagedReference<SuiMessageBox*> suibox = new SuiMessageBox(player, SuiWindowType::CONFIRM_VETERAN_REWARD);
		suibox->setPromptTitle("@veteran_new:unique_are_you_sure_box_title"); // Reward
		suibox->setPromptText( "@veteran_new:item_unique_are_you_sure"); // The item you are selecting can only be selected as a reward item once for the the lifetime of your account. Are you sure you wish to continue selecting this item?
		suibox->setCallback(new ConfirmVeteranRewardSuiCallback(server));
		suibox->setOkButton(true, "@yes");
		suibox->setCancelButton(true, "@no");

		playerGhost->addSuiBox(suibox);
		player->sendMessage(suibox->generateMessage());

	}
	else{
		generateVeteranReward( player );
	}

}

void PlayerManagerImplementation::generateVeteranReward(CreatureObject* player ){

	if( player == NULL || !player->isPlayerCreature() ){
		return;
	}

	// Get account
	PlayerObject* playerGhost = player->getPlayerObject();
	ManagedReference<Account*> account = getAccount( playerGhost->getAccountID() );
	if( account == NULL ){
		player->sendSystemMessage( "@veteran:reward_error"); //	The reward could not be granted.
		cancelVeteranRewardSession( player );
		return;
	}

	// Check session
	ManagedReference<VeteranRewardSession*> rewardSession = player->getActiveSession(SessionFacadeType::VETERANREWARD).castTo<VeteranRewardSession*>();
	if( rewardSession == NULL ){
		player->sendSystemMessage( "@veteran:reward_error"); //	The reward could not be granted.
		return;
	}

	// Final check to see if milestone has already been claimed on any of the player's characters
	// (prevent claiming while multi-logged)
	CharacterList* characters = account->getCharacterList();
	bool milestoneClaimed = false;
	for(int i = 0; i < characters->size(); ++i) {
		CharacterListEntry* entry = &characters->get(i);
		if(entry->getGalaxyID() == server->getGalaxyID()) {

			ManagedReference<CreatureObject*> altPlayer = getPlayer(entry->getFirstName());
			if(altPlayer != NULL && altPlayer->getPlayerObject() != NULL) {
				Locker alocker(altPlayer, player);

				if( !altPlayer->getPlayerObject()->getChosenVeteranReward( rewardSession->getMilestone() ).isEmpty() ){
					milestoneClaimed = true;
					alocker.release();
					break;
				}

				alocker.release();
			}
		}
	}

	if( milestoneClaimed ){
		player->sendSystemMessage( "@veteran:reward_error"); //	The reward could not be granted.
		cancelVeteranRewardSession( player );
		return;
	}

	// Generate item
	SceneObject* inventory = player->getSlottedObject("inventory");
	VeteranReward reward = veteranRewards.get(rewardSession->getSelectedRewardIndex());
	Reference<SceneObject*> rewardSceno = server->createObject(reward.getTemplateFile().hashCode(), 1);
	if( rewardSceno == NULL || inventory == NULL ){
		player->sendSystemMessage( "@veteran:reward_error"); //	The reward could not be granted.
		cancelVeteranRewardSession( player );
		return;
	}

	// Transfer to player
	if( !inventory->transferObject(rewardSceno, -1, false, true) ){ // Allow overflow
		player->sendSystemMessage( "@veteran:reward_error"); //	The reward could not be granted.
		cancelVeteranRewardSession( player );
		return;
	}

	inventory->broadcastObject(rewardSceno, true);
	player->sendSystemMessage( "@veteran:reward_given");  // Your reward has been placed in your inventory.

	// Record reward in all characters registered to the account
	for(int i = 0; i < characters->size(); ++i) {
		CharacterListEntry* entry = &characters->get(i);
		if(entry->getGalaxyID() == server->getGalaxyID()) {

			ManagedReference<CreatureObject*> altPlayer = getPlayer(entry->getFirstName());
			if(altPlayer != NULL && altPlayer->getPlayerObject() != NULL) {
				Locker alocker(altPlayer, player);
				altPlayer->getPlayerObject()->addChosenVeteranReward( rewardSession->getMilestone(), reward.getTemplateFile() );
				alocker.release();
			}
		}
	}

	cancelVeteranRewardSession( player );

	// If player is eligible for another reward, kick off selection
	if( getEligibleMilestone( playerGhost, account ) >= 0 ){
		player->enqueueCommand(String("claimveteranreward").hashCode(), 0, 0, "");
	}
}

int PlayerManagerImplementation::getEligibleMilestone( PlayerObject *playerGhost, Account* account ){

	if( account == NULL || playerGhost == NULL )
		return -1;

	int accountAge = account->getAgeInDays();

	// Return the first milestone for which the player is eligible and has not already claimed
	for( int i=0; i < veteranRewardMilestones.size(); i++){
		int milestone = veteranRewardMilestones.get(i);
		if( accountAge >= milestone && playerGhost->getChosenVeteranReward(milestone).isEmpty() ){
			return milestone;
		}
	}

	return -1;
}

int PlayerManagerImplementation::getFirstIneligibleMilestone( PlayerObject *playerGhost, Account* account ){

	if( account == NULL || playerGhost == NULL )
		return -1;

	int accountAge = account->getAgeInDays();

	// Return the first milestone the player has not already claimed
	for( int i=0; i < veteranRewardMilestones.size(); i++){
		int milestone = veteranRewardMilestones.get(i);
		if( accountAge < milestone && !playerGhost->getChosenVeteranReward(milestone).isEmpty() ){
			return milestone;
		}
	}

	return -1;
}

bool PlayerManagerImplementation::increaseOnlineCharCountIfPossible(ZoneClientSession* client) {
	Locker locker(&onlineMapMutex);

	uint32 accountId = client->getAccountID();

	BaseClientProxy* session = client->getSession();

	if (!onlineZoneClientMap.containsKey(accountId)) {
		Vector<Reference<ZoneClientSession*> > clients;
		clients.add(client);

		onlineZoneClientMap.put(accountId, clients);

		locker.release();

		if (session != NULL) {
			String ip = session->getIPAddress();

			onlineZoneClientMap.addAccount(ip, accountId);
		}

		return true;
	}

	Vector<Reference<ZoneClientSession*> > clients = onlineZoneClientMap.get(accountId);

	int onlineCount = 0;

	for (int i = 0; i < clients.size(); ++i) {
		ZoneClientSession* session = clients.get(i);

		ManagedReference<SceneObject*> player = session->getPlayer();

		if (player != NULL) {
			Reference<PlayerObject*> ghost = player->getSlottedObject("ghost").castTo<PlayerObject*>();

			if (ghost != NULL && ghost->getAdminLevel() > 0)
				continue;
			else if (player->getClient() == session)
				++onlineCount;
		}
	}

	if (onlineCount >= MAX_CHAR_ONLINE_COUNT)
		return false;

	clients.add(client);

	onlineZoneClientMap.put(accountId, clients);

	locker.release();

	if (session != NULL) {
		String ip = session->getIPAddress();

		onlineZoneClientMap.addAccount(ip, accountId);
	}

	return true;
}

/*
int PlayerManagerImplementation::getOnlineCharCount(unsigned int accountId) {
	//onlineMapMutex.rlock()
	return 0;
}
 */

bool PlayerManagerImplementation::shouldRescheduleCorpseDestruction(CreatureObject* player, CreatureObject* ai) {

	if(player == NULL || ai == NULL)
		return false;

	if (!player->isPlayerCreature()) {
		return true;
	}

	if (ai->isNonPlayerCreatureObject()) {
		NonPlayerCreatureObject *npc = dynamic_cast<NonPlayerCreatureObject*>(ai);

		if (!npc->hasLoot() && npc->getCashCredits() < 1 && npc->getBankCredits() < 1) {
			return true;
		}
	} else if (ai->isCreature()) {
		Creature * creature = dynamic_cast<Creature*>(ai);

		if(creature->hasLoot() || creature->getCashCredits() > 0 || creature->getBankCredits() > 0)
			return false;

		return !(creature->hasSkillToHarvestMe(player) || canGroupMemberHarvestCorpse(player, creature));

	}

	return false;
}

bool PlayerManagerImplementation::canGroupMemberHarvestCorpse(CreatureObject* player, Creature* creature) {

	if (!player->isGrouped())
		return false;

	ManagedReference<GroupObject*> group = player->getGroup();
	int groupSize = group->getGroupSize();

	for (int i = 0; i < groupSize; i++) {
		ManagedReference<SceneObject*> groupMember = group->getGroupMember(i);

		if (player->getObjectID() == groupMember->getObjectID())
			continue;

		if (creature->isInRange(groupMember, 256.0f)) {

			CreatureObject* groupMemberCreature = dynamic_cast<CreatureObject*>(groupMember.get());

			if (creature->hasSkillToHarvestMe(groupMemberCreature)) {
				return true;
			}
		}
	}

	return false;
}

void PlayerManagerImplementation::rescheduleCorpseDestruction(CreatureObject* player, CreatureObject* ai) {

	//If the looting player or no group members in the area can harvest then despawn immediately
	if (shouldRescheduleCorpseDestruction(player, ai)) {
		Reference<DespawnCreatureTask*> despawn = ai->getPendingTask("despawn").castTo<DespawnCreatureTask*>();
		if (despawn != NULL) {
			despawn->cancel();
			despawn->reschedule(1000);
		}

	}
}


void PlayerManagerImplementation::getCleanupCharacterCount(){
	info("**** GETTING CHARACTER CLEANUP INFORMATION ***",true);

	ObjectDatabase* thisDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("sceneobjects", true, 0xFFFF, false);

	if(thisDatabase == NULL)
		return;

	ObjectInputStream objectData(2000);
	ObjectDatabaseIterator iterator(thisDatabase);

	uint64 objectID;

	String className;
	uint64 deletedCount = 0;
	uint64 playerCount = 0;

	ZoneServer* server = ServerCore::getZoneServer();

	if(server == NULL){
		error("NULL ZoneServer in character cleanup");
		return;
	}

	int galaxyID = server->getGalaxyID();

	while(iterator.getNextKeyAndValue(objectID, &objectData)){
		if(Serializable::getVariable<String>(String("_className").hashCode(), &className, &objectData)){
			if(className == "CreatureObject"){
				playerCount++;

				if(shouldDeleteCharacter(objectID, galaxyID)){
					deletedCount++;
					info("DELETE CHARACTER " + String::valueOf(objectID),true);
				}

			}
		}
		objectData.reset();
	}

	StringBuffer deletedMessage;
	deletedMessage << "TOTAL CHARACTERS " << " TO BE DELETED " << String::valueOf(deletedCount);
	info("TOTAL CHARACTERS IN OBJECT DB: " + String::valueOf(playerCount),true);
	info(deletedMessage.toString(),true);
}

void PlayerManagerImplementation::cleanupCharacters(){

	info("**** PERFORMING CHARACTER CLEANUP ***",true);

	ObjectDatabase* thisDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("sceneobjects", true, 0xFFFF, false);

	if(thisDatabase == NULL)
		return;

	ObjectInputStream objectData(2000);
	ObjectDatabaseIterator iterator(thisDatabase);

	uint64 objectID;

	String className;
	uint64 deletedCount = 0;
	uint64 playerCount = 0;

	ZoneServer* server = ServerCore::getZoneServer();

	if(server == NULL){
		error("NULL ZoneServer in character cleanup");
		return;
	}

	int galaxyID = server->getGalaxyID();

	while(iterator.getNextKeyAndValue(objectID, &objectData) && deletedCount < 400 ){
		if(Serializable::getVariable<String>(String("_className").hashCode(), &className, &objectData)){
			if(className == "CreatureObject"){
				playerCount++;

				if(shouldDeleteCharacter(objectID, galaxyID)){

					ManagedReference<CreatureObject*> object = Core::getObjectBroker()->lookUp(objectID).castTo<CreatureObject*>();

					if(object == NULL){
						info("OBJECT NULL when getting object " + String::valueOf(objectID),true);
					}else if (object->isPlayerCreature()){

						deletedCount++;
						info("DELETING CHARACTER: " + String::valueOf(objectID)+ " NAME: " +  object->getFirstName() + " " + object->getLastName() ,true);
						Locker _lock(object);

						ManagedReference<ZoneClientSession*> client = object->getClient();

						if (client != NULL)
							client->disconnect();

						object->destroyObjectFromWorld(false); //Don't need to send destroy to the player - they are being disconnected.
						object->destroyPlayerCreatureFromDatabase(true);

					}

				}

			}

		}

		objectData.reset();
	}

	StringBuffer deletedMessage;
	deletedMessage << "TOTAL CHARACTERS";
	deletedMessage << " DELETED FROM OBJECTDB: " << String::valueOf(deletedCount);
	info(deletedMessage.toString(),true);

}

bool PlayerManagerImplementation::shouldDeleteCharacter(uint64 characterID, int galaxyID){
	String query = "SELECT * FROM characters WHERE character_oid = " + String::valueOf(characterID) + " AND galaxy_id = " + String::valueOf(galaxyID);

	try {
		Reference<ResultSet*> result = ServerDatabase::instance()->executeQuery(query);

		if(result == NULL) {
			error("ERROR WHILE LOOKING UP CHARACTER IN SQL TABLE");
		} else if (result.get()->getRowsAffected() > 0 ) {

			error("More than one character with oid = " + String::valueOf(characterID) + " in galaxy " + String::valueOf(galaxyID));
			return false;

		} else if ( result.get()->getRowsAffected() == 0) {
			return true;
		}

		return false;

	} catch ( DatabaseException &err){
		info("database error " + err.getMessage(),true);
		return false;
	}

}

bool PlayerManagerImplementation::doBurstRun(CreatureObject* player, float hamModifier, float cooldownModifier) {
	if (player == NULL)
		return false;

	if (player->isRidingMount()) {
		player->sendSystemMessage("@cbt_spam:no_burst"); // You cannot burst-run while mounted on a creature or vehicle.
		return false;
	}

	if (player->hasBuff(String("gallop").hashCode()) || player->hasBuff(String("burstrun").hashCode()) || player->hasBuff(String("retreat").hashCode())) {
		player->sendSystemMessage("@combat_effects:burst_run_no"); // You cannot burst run right now.
		return false;
	}

	Zone* zone = player->getZone();

	if (zone == NULL) {
		return false;
	}

	if (zone->getZoneName() == "dungeon1") {
		player->sendSystemMessage("@combat_effects:burst_run_space_dungeon"); // The artificial gravity makes burst running impossible here.
		return false;
	}

	if (!player->checkCooldownRecovery("burstrun")) {
		player->sendSystemMessage("@combat_effects:burst_run_wait"); //You are too tired to Burst Run.
		return false;
	}

	uint32 crc = String("burstrun").hashCode();
	float hamCost = 100.0f;
	float duration = 30;
	float cooldown = 300;

	float burstRunMod = (float) player->getSkillMod("burst_run");
	hamModifier += (burstRunMod / 100.f);

	if (hamModifier > 1.0f) {
		hamModifier = 1.0f;
	}

	float hamReduction = 1.f - hamModifier;
	hamCost *= hamReduction;
	int newHamCost = (int) hamCost;

	if (cooldownModifier > 1.0f) {
		cooldownModifier = 1.0f;
	}

	float coodownReduction = 1.f - cooldownModifier;
	cooldown *= coodownReduction;
	int newCooldown = (int) cooldown;

	if (player->getHAM(CreatureAttribute::HEALTH) <= newHamCost || player->getHAM(CreatureAttribute::ACTION) <= newHamCost || player->getHAM(CreatureAttribute::MIND) <= newHamCost) {
		player->sendSystemMessage("@combat_effects:burst_run_wait"); // You are too tired to Burst Run.
		return false;
	}

	player->inflictDamage(player, CreatureAttribute::HEALTH, newHamCost, true);
	player->inflictDamage(player, CreatureAttribute::ACTION, newHamCost, true);
	player->inflictDamage(player, CreatureAttribute::MIND, newHamCost, true);

	StringIdChatParameter startStringId("cbt_spam", "burstrun_start_single");
	StringIdChatParameter modifiedStartStringId("combat_effects", "instant_burst_run");
	StringIdChatParameter endStringId("cbt_spam", "burstrun_stop_single");

	ManagedReference<Buff*> buff = new Buff(player, crc, duration, BuffType::SKILL);
	buff->setSpeedMultiplierMod(1.822f);
	buff->setAccelerationMultiplierMod(1.822f);
	if (cooldownModifier == 0.f)
		buff->setStartMessage(startStringId);
	else
		buff->setStartMessage(modifiedStartStringId);
	buff->setEndMessage(endStringId);

	player->addBuff(buff);

	player->updateCooldownTimer("burstrun", (newCooldown + duration) * 1000);

	Reference<BurstRunNotifyAvailableEvent*> task = new BurstRunNotifyAvailableEvent(player);
	player->addPendingTask("burst_run_notify", task, (newCooldown + duration) * 1000);

	return true;
}

bool PlayerManagerImplementation::doEnhanceCharacter(uint32 crc, CreatureObject* player, int amount, int duration, int buffType, uint8 attribute) {
	if (player == NULL)
		return false;

	if (player->hasBuff(crc))
		return false;

	ManagedReference<Buff*> buff = new Buff(player, crc, duration, buffType);
	buff->setAttributeModifier(attribute, amount);
	player->addBuff(buff);

	return true;
}

void PlayerManagerImplementation::enhanceCharacter(CreatureObject* player) {
	if (player == NULL)
		return;

	bool message = true;

	message = message && doEnhanceCharacter(0x98321369, player, medicalBuff, medicalDuration, BuffType::MEDICAL, 0); // medical_enhance_health
	message = message && doEnhanceCharacter(0x815D85C5, player, medicalBuff, medicalDuration, BuffType::MEDICAL, 1); // medical_enhance_strength
	message = message && doEnhanceCharacter(0x7F86D2C6, player, medicalBuff, medicalDuration, BuffType::MEDICAL, 2); // medical_enhance_constitution
	message = message && doEnhanceCharacter(0x4BF616E2, player, medicalBuff, medicalDuration, BuffType::MEDICAL, 3); // medical_enhance_action
	message = message && doEnhanceCharacter(0x71B5C842, player, medicalBuff, medicalDuration, BuffType::MEDICAL, 4); // medical_enhance_quickness
	message = message && doEnhanceCharacter(0xED0040D9, player, medicalBuff, medicalDuration, BuffType::MEDICAL, 5); // medical_enhance_stamina

	message = message && doEnhanceCharacter(0x11C1772E, player, performanceBuff, performanceDuration, BuffType::PERFORMANCE, 6); // performance_enhance_dance_mind
	message = message && doEnhanceCharacter(0x2E77F586, player, performanceBuff, performanceDuration, BuffType::PERFORMANCE, 7); // performance_enhance_music_focus
	message = message && doEnhanceCharacter(0x3EC6FCB6, player, performanceBuff, performanceDuration, BuffType::PERFORMANCE, 8); // performance_enhance_music_willpower

	if (message && player->isPlayerCreature())
		player->sendSystemMessage("An unknown force strengthens you for battles yet to come.");
}
