/*
 * ShipManager.cpp
 *
 *  Created on: 18/10/2013
 *      Author: victor
 */

#include "ShipManager.h"

#include "server/ServerCore.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/packets/ship/OnShipHit.h"
#include "templates/manager/DataArchiveStore.h"
#include "templates/datatables/DataTableIff.h"
#include "server/zone/objects/ship/ShipChassisData.h"
#include "templates/tangible/ship/SharedShipObjectTemplate.h"
#include "server/zone/objects/ship/ComponentSlots.h"
#include "server/zone/objects/ship/ShipComponentFlag.h"
#include "server/zone/packets/ship/DestroyShipMessage.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/ship/components/ShipComponent.h"
#include "templates/params/creature/PlayerArrangement.h"
#include "server/zone/objects/ship/PobShipObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/FindLostItemsSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/DeleteAllItemsSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/PobShipStatusSuiCallback.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/callbacks/NameShipSuiCallback.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/objects/tangible/deed/ship/ShipDeed.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "SpaceSpawnGroup.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "server/zone/managers/ship/ShipAgentTemplateManager.h"


int ShipManager::ERROR_CODE = NO_ERROR;

ShipManager::ShipManager() : Logger("ShipManger") {
	setGlobalLogging(false);
	setLogging(false);

	lua = new Lua();
	lua->init();

	lua->registerFunction("includeFile", includeFile);
	lua->registerFunction("addShipSpawnGroup", addShipSpawnGroup);

	updateTransformTask = new ShipAiAgentUpdateTransformTask(this);
	updateTransformTask->schedule(60000);
}

void ShipManager::initialize() {
	loadShipChassisData();
	loadShipComponentData();
	loadShipWeaponData();
	loadHyperspaceLocations();
	loadShipAppearanceData();
	loadShipMissileData();
	loadShipCountermeasureData();
	loadShipCollisionData();
	loadShipTurretIffData();
	loadShipTurretLuaData();

	// Load the ship spawn groups
	loadShipSpawnGroups();
}

void ShipManager::stop() {
	chassisData.removeAll();
	shipComponents.removeAll();
	shipComponentTemplateNames.removeAll();
	shipAppearanceData.removeAll();
	shipProjectileData.removeAll();
	shipProjectiletTemplateNames.removeAll();
	shipCollisionData.removeAll();
	chassisData.removeAll();

	missileData.removeAll();
	countermeasureData.removeAll();

	for (int i = 0; i < turretData.size(); ++i) {
		auto dataMap = turretData.elementAt(i).getValue();

		dataMap.removeAll();
	}

	hyperspaceLocations.removeAll();
	hyperspaceZones.removeAll();
}

void ShipManager::loadHyperspaceLocations() {
	IffStream* iffStream = DataArchiveStore::instance()->openIffFile("datatables/space/hyperspace/hyperspace_locations.iff");

	if (iffStream == nullptr) {
		fatal("datatables/space/hyperspace/hyperspace_locations could not be found.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);
		String name;
		String zone;
		int x, y, z;
		row->getCell(0)->getValue(name);
		row->getCell(1)->getValue(zone);
		row->getCell(2)->getValue(x);
		row->getCell(3)->getValue(y);
		row->getCell(4)->getValue(z);

		hyperspaceLocations.put(name, Vector3(x, y, z));
		hyperspaceZones.put(name, zone);
	}
	delete iffStream;
}

void ShipManager::loadShipComponentData() {
	IffStream* iffStream = DataArchiveStore::instance()->openIffFile("datatables/space/ship_components.iff");

	if (iffStream == nullptr) {
		fatal("datatables/space/ship_components.iff could not be found.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		Reference<ShipComponentData*> component = new ShipComponentData();
		component->readObject(row);

		shipComponents.put(component->getName().hashCode(), component);
		shipComponentTemplateNames.put(component->getObjectTemplate(), component);
	}
	delete iffStream;
}

void ShipManager::loadShipChassisData() {
	info(true) << "Loading Ship Chassis Data";

	IffStream* iffStream = DataArchiveStore::instance()->openIffFile("datatables/space/ship_chassis.iff");

	if (iffStream == nullptr) {
		fatal("datatables/space/ship_chassis.iff could not be found.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	Vector<String> columns(dtiff.getTotalColumns(), 3);

	for (int i = 0; i < dtiff.getTotalColumns(); i++) {
		columns.add(dtiff.getColumnNameByIndex(i));
		// info("Column: " + columns.get(i), true);
	}

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		ShipChassisData* data = new ShipChassisData(dtiff.getRow(i), columns);
		chassisData.put(data->getName(), data);
	}

	info(true) << "Ship Chassis Data Loading Complete - Total: " << chassisData.size();

	delete iffStream;
}

void ShipManager::loadShipWeaponData() {
	info(true) << "Loading Ship Weapon Data";

	IffStream* iffStream = DataArchiveStore::instance()->openIffFile("datatables/space/ship_weapon_components.iff");

	if (iffStream == nullptr) {
		fatal("datatables/space/ship_weapon_components.iff could not be found.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		Reference<ShipProjectileData*> data = new ShipProjectileData();
		data->readObject(row);

		shipProjectileData.put(data->getName().hashCode(), data);
		shipProjectiletTemplateNames.put(data->getName(), data);
	}

	delete iffStream;

	info(true) << "Ship Weapon Data Loading Complete - Total: " << shipProjectiletTemplateNames.size();
}

void ShipManager::loadShipAppearanceData() {
	info(true) << "Loading Ship Appearance Data";

	IffStream* iffStream = DataArchiveStore::instance()->openIffFile("datatables/space/ship_chassis.iff");

	if (iffStream == nullptr) {
		fatal("datatables/space/ship_chassis.iff could not be found.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);
		if (row == nullptr || row->getCellsSize() == 0) {
			continue;
		}

		DataTableCell* cell = row->getCell(0);
		if (cell == nullptr) {
			continue;
		}

		String key = cell->toString();
		if (key == "") {
			continue;
		}

		Reference<ShipAppearanceData*> data = new ShipAppearanceData(key);
		shipAppearanceData.put(key, data);
	}

	delete iffStream;

	info(true) << "Ship Appearance Data Loading Complete - Total: " << shipAppearanceData.size();
}

void ShipManager::loadShipMissileData() {
	info(true) << "Loading Ship Missile Data";

	IffStream* iffStream = DataArchiveStore::instance()->openIffFile("datatables/space/missiles.iff");

	if (iffStream == nullptr) {
		info(true) << "datatables/space/missiles.iff could not be found.";
		return;
	}

	try {

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);
		if (row == nullptr || row->getCellsSize() == 0) {
			continue;
		}

		Reference<ShipMissileData*> data = new ShipMissileData();
		data->readObject(row);

		missileData.put(data->getMissileType(), data);
	}

	} catch (Exception& e) {
		e.printStackTrace();
	}

	delete iffStream;

	info(true) << "Ship Missile Data Loading Complete - Total: " << missileData.size();
}

void ShipManager::loadShipCountermeasureData() {
	info(true) << "Loading Ship Countermeasure Data";

	IffStream* iffStream = DataArchiveStore::instance()->openIffFile("datatables/space/countermeasures.iff");

	if (iffStream == nullptr) {
		info(true) << "datatables/space/countermeasures.iff could not be found.";
		return;
	}

	try {

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);
		if (row == nullptr || row->getCellsSize() == 0) {
			continue;
		}

		Reference<ShipCountermeasureData*> data = new ShipCountermeasureData();
		data->readObject(row);

		countermeasureData.put(data->getCountermeasureType(), data);
	}

	} catch (Exception& e) {
		e.printStackTrace();
	}

	delete iffStream;

	info(true) << "Ship Countermeasure Data Loading Complete - Total: " << countermeasureData.size();
}

void ShipManager::loadShipTurretIffData() {
	info(true) << "Loading Ship Turret Iff Data";

	IffStream* iffStream = DataArchiveStore::instance()->openIffFile("datatables/space/ship_turret.iff");

	if (iffStream == nullptr) {
		info(true) << "datatables/space/ship_turret.iff could not be found.";
		return;
	}

	try {

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);
		if (row == nullptr || row->getCellsSize() == 0) {
			continue;
		}

		Reference<ShipTurretData*> data = new ShipTurretData();
		data->readObject(row);

		String chassisName = data->getChassisName();

		if (!turretData.contains(chassisName)) {
			turretData.put(chassisName, VectorMap<uint32, Reference<ShipTurretData*>>());
		}

		auto& entry = turretData.get(chassisName);
		entry.put(data->getWeaponIndex(), data);
	}

	} catch (Exception& e) {
		e.printStackTrace();
	}

	delete iffStream;

	info(true) << "Ship Turret Iff Data Loading Complete - Total: " << turretData.size();
}

void ShipManager::loadShipTurretLuaData() {
	info(true) << "Loading Ship Turret Lua Data";

	Lua* lua = new Lua();
	lua->init();

	if (lua->runFile("scripts/managers/space/ship_turret.lua")) {
		LuaObject luaData = lua->getGlobalObject("turretData");

		if (luaData.isValidTable() && luaData.getTableSize() > 0) {
			for (int i = 1; i <= luaData.getTableSize(); ++i) {
				auto row = luaData.getObjectAt(i);

				if (row.isValidTable() && row.getTableSize() > 0) {
					String chassisName = row.getStringAt(1);

					if (chassisName != "") {
						Reference<ShipTurretData*> data = new ShipTurretData();
						data->readObject(&row);

						if (!turretData.contains(chassisName)) {
							turretData.put(chassisName, VectorMap<uint32, Reference<ShipTurretData*>>());
						}

						auto& entry = turretData.get(chassisName);
						entry.put(data->getWeaponIndex(), data);
					}
				}

				row.pop();
			}
		}
	}

	delete lua;

	info(true) << "Ship Turret Lua Data Loading Complete - Total: " << turretData.size();
}

void ShipManager::loadShipCollisionData() {
	info(true) << "Loading Ship Collision Data";

	Lua* lua = new Lua();
	lua->init();

	if (lua->runFile("scripts/managers/space/ship_chassis.lua")) {
		LuaObject luaData = lua->getGlobalObject("chassisData");

		if (luaData.isValidTable() && luaData.getTableSize() > 0) {
			for (int i = 1; i <= luaData.getTableSize(); ++i) {
				auto row = luaData.getObjectAt(i);

				if (!row.isValidTable() || row.getTableSize() < 3) {
					row.pop();
					continue;
				}

				String chassisType = row.getStringAt(1);
				String chassisName = row.getStringAt(2);
				String chassisPath = row.getStringAt(3);
				row.pop();

				if (chassisType == "" || chassisName == "" || chassisPath == "") {
					continue;
				}

				auto chassisData = getChassisData(chassisName);

				if (chassisData == nullptr) {
					continue;
				}

				uint32 templateCRC = chassisPath.hashCode();

				auto templateObject = TemplateManager::instance()->getTemplate(templateCRC);

				if (templateObject == nullptr) {
					continue;
				}

				auto chassisTemplate = dynamic_cast<SharedShipObjectTemplate*>(templateObject);

				if (chassisTemplate == nullptr) {
					continue;
				}

				Reference<ShipCollisionData*> data = new ShipCollisionData(chassisTemplate, chassisData);
				shipCollisionData.put(templateCRC, data);
			}
		}
	}

	delete lua;

	info(true) << "Ship Collision Data Loading Complete - Total: " << shipCollisionData.size();
}

void ShipManager::loadShipComponentObjects(ShipObject* ship) {
	auto shipTemp = dynamic_cast<SharedShipObjectTemplate*>(ship->getObjectTemplate());
	if (shipTemp == nullptr) {
		return;
	}

	auto chassisData = getChassisData(shipTemp->getShipName());
	if (chassisData == nullptr) {
		return;
	}

	const auto& componentNames = shipTemp->getComponentNames();

	for (uint32 slot = 0; slot <= Components::FIGHTERSLOTMAX; slot++) {
		String slotName = Components::shipComponentSlotToString(slot);

		if (slotName == "") {
			continue;
		}

		String dataName = componentNames.get(slotName);

		if (dataName == "") {
			continue;
		}

		auto compData = getShipComponent(dataName);

		if (compData == nullptr) {
			continue;
		}

		auto componentTempName = compData->getObjectTemplate();
		auto compShot = TemplateManager::instance()->getTemplate(componentTempName.hashCode());

		if (compShot == nullptr || !(compShot->getGameObjectType() & SceneObjectType::SHIPATTACHMENT)) {
			continue;
		}

		ManagedReference<ShipComponent*> component = ServerCore::getZoneServer()->createObject(componentTempName.hashCode(), ship->getPersistenceLevel()).castTo<ShipComponent*>();

		if (component != nullptr) {
			ship->install(nullptr, component, slot, false);
		}
	}
}

int ShipManager::loadShipSpawnGroups() {
	info(true) << "Loading Ship Spawn Groups...";

	bool ret = false;

	try {
		ret = lua->runFile("scripts/object/ship/spawn/shipSpawnGroups.lua");
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
		ret = false;
	}

	// Set the reference to lua null
	lua = nullptr;

	if (!ret) {
		ERROR_CODE = GENERAL_ERROR;
	}

	info(true) << "Finished loading " << ShipManager::instance()->spawnGroupMap.size() << " Ship Spawn Groups.";

	return ERROR_CODE;
}

int ShipManager::checkArgumentCount(lua_State* L, int args) {
	int parameterCount = lua_gettop(L);

	if (parameterCount < args) {
		return 1;
	} else if (parameterCount > args)
		return 2;

	return 0;
}

int ShipManager::includeFile(lua_State* L) {
	if (checkArgumentCount(L, 1) == 1) {
		instance()->error("incorrect number of arguments passed to ShipManager::includeFile");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String filename = Lua::getStringParameter(L);

	int oldError = ERROR_CODE;

	bool ret = Lua::runFile("scripts/object/ship/spawn/" + filename, L);

	if (!ret) {
		ERROR_CODE = GENERAL_ERROR;

		instance()->error("scripts/object/ship/spawn/" + filename);
	} else {
		if (!oldError && ERROR_CODE) {
			instance()->error("scripts/object/ship/spawn/" + filename);
		}
	}

	return 0;
}

int ShipManager::addShipSpawnGroup(lua_State* L) {
	if (checkArgumentCount(L, 2) == 1) {
		instance()->error("incorrect number of arguments passed to ShipManager::addShipSpawnGroup");
		ERROR_CODE = INCORRECT_ARGUMENTS;
		return 0;
	}

	String groupName = lua_tostring(L, -2);
	uint32 groupCRC = (uint32) groupName.hashCode();

#ifdef DEBUG_SPACE_REGIONS
	Logger::console.info(true) << "Adding SpaceSpawnGroup: " << groupName;
#endif // DEBUG_SPACE_REGIONS

	LuaObject shipSpawnGroup(L);

	// SpaceSpawnGroup is loaded from lua here
	ShipManager::instance()->spawnGroupMap.put(groupCRC, new SpaceSpawnGroup(groupName, shipSpawnGroup));

	shipSpawnGroup.pop();

	return 0;
}

// Ship is locked coming in
ShipControlDevice* ShipManager::createShipControlDevice(ShipObject* ship) {
	String controlName = "object/intangible/ship/" + ship->getShipChassisName().replaceAll("player_", "") + "_pcd.iff";

	auto shot = TemplateManager::instance()->getTemplate(controlName.hashCode());

	if (shot == nullptr || !(shot->getGameObjectType() & SceneObjectType::SHIPCONTROLDEVICE)) {
		return nullptr;
	}

	ManagedReference<ShipControlDevice*> shipControlDevice = ServerCore::getZoneServer()->createObject(controlName.hashCode(), ship->getPersistenceLevel()).castTo<ShipControlDevice*>();

	if (shipControlDevice == nullptr) {
		return nullptr;
	}

	Locker cLock(shipControlDevice, ship);

	if (!shipControlDevice->transferObject(ship, PlayerArrangement::RIDER)) {
		return nullptr;
	}

	shipControlDevice->setShipType(ship->isPobShip() ? POBSHIP : FIGHTERSHIP);
	shipControlDevice->setControlledObject(ship);

	ship->setControlDeviceID(shipControlDevice->getObjectID());

	return shipControlDevice;
}

ShipAiAgent* ShipManager::createAiShip(const String& shipName) {
	// info(true) << "ShipManager::createAiShip -- Create Chassis Name: " << shipName;

	return createAiShip(shipName, shipName.hashCode());
}

ShipAiAgent* ShipManager::createAiShip(const String& shipName, uint32 shipCRC) {
	auto shipTemplateManager = ShipAgentTemplateManager::instance();

	if (shipTemplateManager == nullptr) {
		return nullptr;
	}

	Reference<ShipAgentTemplate*> agentTemplate = shipTemplateManager->getTemplate(shipCRC);

	if (agentTemplate == nullptr) {
		error() << "Ship Agent template is null -- " << shipName;
		return nullptr;
	}

	auto zoneServer = ServerCore::getZoneServer();

	if (zoneServer == nullptr) {
		return nullptr;
	}

	String shipTemplateName = agentTemplate->getShipTemplate();
	shipTemplateName =  "object/ship/" + shipTemplateName + ".iff";

	uint32 shipTempHash = shipTemplateName.hashCode();

	auto shipTemp = dynamic_cast<SharedShipObjectTemplate*>(TemplateManager::instance()->getTemplate(shipTempHash));

	if (shipTemp == nullptr) {
		error() << "Ship Object template is null for: " << shipTemplateName;
		return nullptr;
	}

	// info(true) << "Trying to spawn ship object: " << shipTemplateName;

	ManagedReference<ShipAiAgent*> shipAgent = zoneServer->createObject(shipTemplateName.hashCode(), 0).castTo<ShipAiAgent*>();

	if (shipAgent == nullptr) {
		return nullptr;
	}

	Locker lock(shipAgent);

	// info(true) << "ShipManager::createAiShip -- ShipName: " << agentTemplate->getTemplateName() << " Game Object Type: " << shipTemp->getGameObjectType() << " Ship Hash: " << shipTemp->getServerObjectCRC() << " Full Template: " << shipTemp->getFullTemplateString();

	// Load data from ShipAgentTemplate
	shipAgent->loadTemplateData(agentTemplate);

	shipAgent->setShipAiTemplate();

	return shipAgent;
}

ShipObject* ShipManager::createPlayerShip(CreatureObject* owner, const String& shipName, const String& certificationRequired, bool loadComponents) {
	if (owner == nullptr)
		return nullptr;

	ManagedReference<SceneObject*> dataPad = owner->getDatapad();

	if (dataPad == nullptr) {
		return nullptr;
	}

	PlayerObject* ghost = owner->getPlayerObject();

	if (ghost == nullptr) {
		return nullptr;
	}

	auto shipTemp = dynamic_cast<SharedShipObjectTemplate*>(TemplateManager::instance()->getTemplate(shipName.hashCode()));

	if (shipTemp == nullptr) {
		return nullptr;
	}

	auto zoneServer = ServerCore::getZoneServer();

	if (zoneServer == nullptr)
		return nullptr;

	// Create ship and set persistent
	ManagedReference<ShipObject*> ship = zoneServer->createObject(shipTemp->getServerObjectCRC(), 1).castTo<ShipObject*>();

	if (ship == nullptr) {
		return nullptr;
	}

	// info(true) << "ShipManager::createPlayerShip -- ShipName: " << shipName << " Game Object Type: " << shipTemp->getGameObjectType() << " Ship Hash: " << shipTemp->getServerObjectCRC() << " Full Template: " << shipTemp->getFullTemplateString();

	Locker shipLock(ship, owner);

	// Set ship owner
	ship->setOwner(owner);

	// Load ship template data
	ship->loadTemplateData(shipTemp);

	ship->setCertificationRequired(certificationRequired);

	// Create Control device
	auto shipControlDevice = createShipControlDevice(ship);

	if (shipControlDevice == nullptr) {
		ship->destroyObjectFromDatabase(true);
		ship->destroyObjectFromWorld(true);

		return nullptr;
	}

	Locker cLock(shipControlDevice, ship);

	ship->createChildObjects();

	if (ship->isPobShip()) {
		PobShipObject* pobShip = ship->asPobShip();

		if (pobShip != nullptr) {
			pobShip->grantPermission("ADMIN", owner->getObjectID());
		}
	}

	if (loadComponents) {
		loadShipComponentObjects(ship);
	}

	if (!dataPad->transferObject(shipControlDevice, -1)) {
		shipControlDevice->destroyObjectFromWorld(true);
		shipControlDevice->destroyObjectFromDatabase(true);

		return nullptr;
	}

	owner->sendSystemMessage("@chassis_npc:succeed"); // You successfully add a ship control device to your datapad.

	shipControlDevice->sendTo(owner, true);

	return ship;
}

bool ShipManager::createDeedFromChassis(CreatureObject* player, ShipChassisComponent* chassisBlueprint, CreatureObject* chassisDealer) {
	if (player == nullptr || chassisBlueprint == nullptr || chassisDealer == nullptr)
		return false;

	String deedPath = chassisBlueprint->getChassisDeed();
	String certification = chassisBlueprint->getCertificationRequired();
	int shipCost = chassisBlueprint->getDealerFee();

	auto zoneServer = player->getZoneServer();

	if (zoneServer == nullptr) {
		return false;
	}

	auto chatManager = zoneServer->getChatManager();

	if (chatManager == nullptr) {
		return false;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return false;

	// Increase ship cost if player is not certified
	if (!certification.isEmpty() && !ghost->hasAbility(certification))
		shipCost *= NO_CERT_COST_MULTI;

	// Check player has the cash
	int playerCash = player->getCashCredits();

	if (shipCost > playerCash) {
		chatManager->broadcastChatMessage(chassisDealer, "@chassis_npc:no_money", player->getObjectID(), 0, chassisDealer->getMoodID());

		return false;
	}

	auto inventory = player->getInventory();

	if (inventory == nullptr) {
		return false;
	}

	if (inventory->isContainerFull()) {
		chatManager->broadcastChatMessage(chassisDealer, "@chassis_npc:inv_full", player->getObjectID(), 0, chassisDealer->getMoodID());

		return false;
	}

	auto object = (zoneServer->createObject(deedPath.hashCode(), 2)).castTo<TangibleObject*>();

	if (object == nullptr || !object->isShipDeedObject()) {
		return false;
	}

	ShipDeed* shipDeed = object.castTo<ShipDeed*>();

	if (shipDeed == nullptr) {
		return false;
	}

	Locker lock(shipDeed);
	Locker inventoryLock(inventory, shipDeed);

	if (!inventory->transferObject(shipDeed, -1)) {
		shipDeed->destroyObjectFromWorld(true);
		shipDeed->destroyObjectFromDatabase();

		error("Failed to transfer ShipDeed: " + String::valueOf(shipDeed->getObjectID()) + " Template: " + deedPath);

		return false;
	}

	// release lock on inventory
	inventoryLock.release();

	TransactionLog trx(chassisDealer, player, shipDeed, TrxCode::SHIPDEEDPURCHASE, false);

	// set hitpoints, mass, location
	shipDeed->setMass(chassisBlueprint->getMass());
	shipDeed->setMaxHitPoints(chassisBlueprint->getMaxHitpoints());
	shipDeed->setCreateComponents(false);

	shipDeed->setCertificationRequired(certification);

	int totalSkillReq = chassisBlueprint->getTotalSkillsRequired();

	for (int i = 0; i < totalSkillReq; ++i) {
		String skillName = chassisBlueprint->getSkillRequired(i);

		shipDeed->addSkillRequired(skillName);
	}

	// Set the parking location to the nearest travel point
	auto zone = player->getZone();

	if (zone != nullptr) {
		auto planetManager = zone->getPlanetManager();

		if (planetManager != nullptr) {
			auto travelPoint = planetManager->getNearestPlanetTravelPoint(player->getWorldPosition());

			if (travelPoint != nullptr) {
				auto travelPointName = travelPoint->getPointName();

				shipDeed->setParkingLocation(travelPointName);
			}
		}
	}

	// Broadcast ship deed to the player
	shipDeed->sendTo(player, true);

	// Deduct cost from player
	Locker plock(player, shipDeed);

	trx.addState("deedCost", shipCost);

	TransactionLog trxCash(player, chassisDealer, TrxCode::SHIPDEEDPURCHASE, player->getCashCredits(), true);
	player->subtractCashCredits(shipCost);

	trxCash.groupWith(trx);

	plock.release();

	// Handle Destruction of the Chassis Blueprint
	Locker chassisLock(chassisBlueprint, shipDeed);

	chassisBlueprint->destroyObjectFromWorld(true);
	chassisBlueprint->destroyObjectFromDatabase();

	trx.commit();

	return true;
}

int ShipManager::notifyDestruction(ShipObject* destructorShip, ShipAiAgent* destructedShip, int condition, bool isCombatAction) {
	if (destructedShip == nullptr) {
		return 1;
	}

	// info(true) << "ShipManager::notifyDestruction -- called for: " << destructedShip->getDisplayedName() << " Attacker: " << destructorShip->getDisplayedName();

	destructedShip->cancelBehaviorEvent();
	destructedShip->cancelRecovery();

	destructedShip->wipeBlackboard();
	destructedShip->clearRunningChain();

	auto zoneServer = destructorShip->getZoneServer();

	if (zoneServer == nullptr || zoneServer->isServerShuttingDown()) {
		return 1;
	}

	// Create copy of current threat map
	ThreatMap* threatMap = destructedShip->getThreatMap();
	ThreatMap copyThreatMap(*threatMap);

	threatMap->removeObservers();
	threatMap->removeAll(true);

	auto destructorObjectID = destructorShip->getObjectID();

	// lets unlock destructor so we dont get into complicated deadlocks
	if (destructedShip != destructorShip) {
		destructorShip->unlock();
	}

	try {
		/* Order of priority
			1. Credit chip Granted
			2. Loot Given
			3. Quest Kill
			4. Ship Destroyed (killed creature style observer if needed)
			5. FP Awarded
			5. XP awarded
		*/

		// This function will return a player ship that either has the highest single damage or highest group damage.
		auto highestShip = copyThreatMap.getHighestDamagePlayerShip();

		if (highestShip != nullptr) {
			Locker highestLock(highestShip, destructedShip);

			int minCredits = destructedShip->getMinLootCredits();
			int maxCredits = destructedShip->getMaxLootCredits();
			int randomPayout = 0;

			if (maxCredits > 0) {
				randomPayout = System::random(maxCredits - minCredits) + minCredits;
			}

			highestShip->awardLootItems(destructedShip, randomPayout);
		}

		// Quest Kill Observers
		SortedVector<ManagedReference<Observer* > > observers = destructedShip->getObservers(ObserverEventType::QUESTKILL);

		if (observers.size() > 0) {
			for (int i = 0; i < copyThreatMap.size(); ++i) {
				TangibleObject* attacker = copyThreatMap.elementAt(i).getKey();

				if (attacker == nullptr || !attacker->isPlayerShip())
					continue;

				auto attackerShip = attacker->asShipObject();

				if (attackerShip == nullptr || !attackerShip->isPlayerShip()) {
					continue;
				}

				auto pilot = attackerShip->getPilot();

				if (pilot == nullptr) {
					continue;
				}

				pilot->notifyObservers(ObserverEventType::QUESTKILL, destructedShip);
			}
		}

		ManagedReference<ShipObject*> playerShip = copyThreatMap.getHighestDamageGroupShip();

		if (playerShip != nullptr) {
			ManagedReference<CreatureObject*> pilot = playerShip->getPilot();

			if (pilot != nullptr) {
				if (pilot->isGrouped()) {
					ManagedReference<GroupObject*> group = pilot->getGroup();

					if (group != nullptr) {
						for (int i = 0; i < group->getGroupSize(); i++) {
							ManagedReference<CreatureObject*> groupMember = group->getGroupMember(i);

							if (groupMember == nullptr || !groupMember->isPlayerCreature()) {
								continue;
							}

							Locker locker(groupMember, destructedShip);

							groupMember->notifyObservers(ObserverEventType::DESTROYEDSHIP, destructedShip);
						}
					}
				} else {
					Locker locker(pilot, destructedShip);
					pilot->notifyObservers(ObserverEventType::DESTROYEDSHIP, destructedShip);
				}
			}
		}

		// Handle Awarding XP
		ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

		if (playerManager != nullptr) {
			playerManager->disseminateSpaceExperience(destructedShip, &copyThreatMap);
		}
	} catch (Exception& e) {
		destructedShip->scheduleDespawn(10, true);

		// now we can safely lock destructor again
		if (destructedShip != destructorShip) {
			destructorShip->wlock(destructedShip);
		}

		throw;
	}

	// now we can safely lock destructor again
	if (destructedShip != destructorShip) {
		destructorShip->wlock(destructedShip);

		ThreatMap* destructorThreatMap = destructorShip->getThreatMap();

		if (destructorThreatMap != nullptr) {
			uint64 destructedID = destructedShip->getObjectID();

			for (int i = 0; i < destructorThreatMap->size(); i++) {
				TangibleObject* threatTano = destructorThreatMap->elementAt(i).getKey();

				if (threatTano == nullptr || threatTano->getObjectID() != destructedID) {
					continue;
				}

				destructorThreatMap->remove(i);
			}
		}

		if (destructorShip->hasDefender(destructedShip)) {
			destructorShip->removeDefender(destructedShip);
		}

		// Finally if the destructor has no more defenders, clear their combat state
		if (!destructorShip->hasDefenders()) {
			destructorShip->clearCombatState(false);
		}

		// Remove the destucted ship agent from the destructors enemy list
		if (destructorShip->isShipAiAgent()) {
			auto agentDestructor = destructorShip->asShipAiAgent();

			if (agentDestructor != nullptr) {
				agentDestructor->removeEnemyShip(destructedShip->getObjectID());
			}
		}
	}

	// info(true) << "ShipManager::notifyDestruction -- COMPLETE - for: " << destructedShip->getDisplayedName() << " Attacker: " << destructorShip->getDisplayedName();

	return 1;
}


void ShipManager::reportPobShipStatus(CreatureObject* player, PobShipObject* pobShip, SceneObject* terminal) {
	if (player == nullptr || pobShip == nullptr) {
		return;
	}

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	auto zoneServer = pobShip->getZoneServer();

	if (zoneServer == nullptr)
		return;

	// Close the window if it is already open.
	if (ghost->hasSuiBoxWindowType(SuiWindowType::STRUCTURE_STATUS)) {
		ghost->closeSuiWindowType(SuiWindowType::STRUCTURE_STATUS);
	}

	ManagedReference<SuiListBox*> status = new SuiListBox(player, SuiWindowType::STRUCTURE_STATUS);
	status->setPromptTitle("@player_structure:structure_status_t"); // Structure Status

	String displayedName = pobShip->getDisplayedName();

	if (displayedName != "") {
		status->setPromptText("@player_structure:structure_name_prompt " + displayedName); // Structure Name:
	}

	if (terminal != nullptr) {
		status->setUsingObject(terminal);
	} else {
		status->setUsingObject(pobShip);
	}

	status->setPobShipObject(pobShip);
	status->setOkButton(true, "@refresh");
	status->setCancelButton(true, "@cancel");
	status->setCallback(new PobShipStatusSuiCallback(zoneServer));

	ManagedReference<CreatureObject*> ownerObject = pobShip->getOwner().get();

	if (ownerObject != nullptr && ownerObject->isCreatureObject()) {
		CreatureObject* owner = cast<CreatureObject*>(ownerObject.get());
		status->addMenuItem("@player_structure:owner_prompt " + owner->getFirstName());
	}

	status->addMenuItem("@player_structure:items_in_building_prompt " + String::valueOf(pobShip->getCurrentNumberOfPlayerItems())); // Number of Items in Building:

	ghost->addSuiBox(status);
	player->sendMessage(status->generateMessage());
}

void ShipManager::promptDeleteAllItems(CreatureObject* player, PobShipObject* pobShip) {
	if (player == nullptr || pobShip == nullptr)
		return;

	auto zoneServer = player->getZoneServer();

	if (zoneServer == nullptr)
		return;

	ManagedReference<SuiMessageBox*> sui = new SuiMessageBox(player, 0x00);

	sui->setUsingObject(pobShip);
	sui->setPromptTitle("@player_structure:delete_all_items");	// Delete All Items
	sui->setPromptText("@player_structure:delete_all_items_d"); // This command will delete every object in your house.  Are you ABSOLUTELY sure you want to destroy every object in your house?
	sui->setCancelButton(true, "@cancel");
	sui->setCallback(new DeleteAllItemsSuiCallback(zoneServer));

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost != nullptr) {
		ghost->addSuiBox(sui);
		player->sendMessage(sui->generateMessage());
	}
}

void ShipManager::promptFindLostItems(CreatureObject* player, PobShipObject* pobShip) {
	if (player == nullptr || pobShip == nullptr)
		return;

	auto zoneServer = player->getZoneServer();

	if (zoneServer == nullptr)
		return;

	ManagedReference<SuiMessageBox*> sui = new SuiMessageBox(player, 0x00);
	sui->setUsingObject(pobShip);
	sui->setPromptTitle("@player_structure:move_first_item");  // Find Lost Items
	sui->setPromptText("@player_structure:move_first_item_d"); // This command will move the first item in your pobShip to your location...
	sui->setCallback(new FindLostItemsSuiCallback(zoneServer));

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost != nullptr) {
		ghost->addSuiBox(sui);
		player->sendMessage(sui->generateMessage());
	}
}

void ShipManager::promptNameShip(CreatureObject* player, ShipControlDevice* shipDevice) {
	if (player == nullptr || shipDevice == nullptr) {
		return;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	auto controlledObject = shipDevice->getControlledObject();

	if (controlledObject == nullptr) {
		return;
	}

	auto ship = controlledObject->asShipObject();

	if (ship == nullptr) {
		return;
	}

	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::OBJECT_NAME);

	inputBox->setUsingObject(shipDevice);

	inputBox->setPromptTitle("@sui:rename_ship"); // Rename Ship
	inputBox->setPromptText("@sui:rename_ship_text"); // What would you like to name your ship?  (Limit: 20 characters)

	inputBox->setMaxInputSize(20);

	inputBox->setCallback(new NameShipSuiCallback(player->getZoneServer()));
	inputBox->setForceCloseDistance(-1);

	ghost->addSuiBox(inputBox);

	player->sendMessage(inputBox->generateMessage());
}

void ShipManager::reDeedShip(CreatureObject* player, ShipControlDevice* shipDevice) {
	if (player == nullptr || shipDevice == nullptr) {
		return;
	}

	ManagedReference<ShipObject*> ship = shipDevice->getControlledObject()->asShipObject();

	if (ship == nullptr) {
		return;
	}

	auto zoneServer = player->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	auto zone = player->getZone();

	if (zone == nullptr) {
		return;
	}

	auto planetManager = zone->getPlanetManager();

	if (planetManager == nullptr) {
		return;
	}

	auto parkingLocation = shipDevice->getParkingLocation();
	auto travelPoint = planetManager->getNearestPlanetTravelPoint(player->getWorldPosition(), 128.f);

	if (travelPoint == nullptr || parkingLocation != travelPoint->getPointName()) {
		player->sendSystemMessage("@space/space_interaction:wrong_parking_location"); // "Your ship is not parked here. (Examine the Ship Control Device to see where it is actually parked)"
		return;
	}

	if (ship->isSorosuubSpaceYacht()) {
		player->sendSystemMessage("@space/space_interaction:space_yacht"); // "The Sorosuub Yacht cannot be re-deeded!"
		return;
	} else if (ship->isStarterShip()) {
		player->sendSystemMessage("@space/space_interaction:newbie_ship"); // "You cannot redeed a starter ship!"
		return;
	} else if (ship->isPobShip()) {
		auto pobShip = ship->asPobShip();

		if (pobShip == nullptr) {
			return;
		}

		if (pobShip->getCurrentNumberOfPlayerItems() > 0) {
			player->sendSystemMessage("@space/space_interaction:items_in_ship"); // "You cannot pack this ship into a deed until you have removed all items from its interior."
			return;
		}
	}

	if (ship->hasComponentsInstalled()) {
		player->sendSystemMessage("@space/space_interaction:components_installed"); // "You cannot pack this ship until all components have been removed from the ship."
		return;
	}

	auto inventory = player->getInventory();

	if (inventory == nullptr) {
		return;
	}

	String chassisName = ship->getShipChassisName().replaceAll("player_", "");
	String deedPath = "object/tangible/ship/crafted/chassis/" + chassisName + "_deed.iff";

	// Create the deed and transfer
	auto object = zoneServer->createObject(deedPath.hashCode(), 2);

	if (object == nullptr || !object->isShipDeedObject()) {
		return;
	}

	ShipDeed* shipDeed = object.castTo<ShipDeed*>();

	if (shipDeed == nullptr) {
		return;
	}

	// Transfer the ship stats to the deed
	Locker deedLock(shipDeed, shipDevice);

	auto controlDeviceTemplate = shipDevice->getObjectTemplate();

	if (controlDeviceTemplate == nullptr) {
		return;
	}

	auto deviceStringName = controlDeviceTemplate->getFullTemplateString();
	auto certificationRequired = ship->getCertificationRequired();


	int shipType = shipDevice->getShipType();
	float maxHealth = ship->getChassisMaxHealth();
	float currentHealthDamage = (maxHealth - ship->getChassisCurrentHealth());
	float maxMass = ship->getChassisMaxMass();

	/*
	StringBuffer msg;
	msg << "Ship ReDeed Ship Stats Debug -- Control Device Template: " << deviceStringName << endl <<
	"Max Hit Points: " << maxHealth << endl <<
	"Hit Points Damage = " << currentHealthDamage << endl <<
	"Max Mass: " << maxMass << endl <<
	"Certifcation Required: " << certificationRequired << endl <<
	"Parking Locaiton: " << parkingLocation << endl;
	*/

	for (int i = 0; i < shipDevice->getTotalSkillsRequired(); i++) {
		auto skillName = shipDevice->getSkillRequired(i);
		shipDeed->addSkillRequired(skillName);
		// msg << "Skills Required: " << skillName << endl;
	}

	/*
	info(true) << msg.toString();
	*/

	shipDeed->setControlDeviceTemplate(deviceStringName);
	shipDeed->setCertificationRequired(certificationRequired);
	shipDeed->setParkingLocation(parkingLocation);

	shipDeed->setMaxHitPoints(maxHealth);
	shipDeed->setHitPointsDamage(currentHealthDamage);
	shipDeed->setMass(maxMass);
	shipDeed->setShipType(shipType);

	deedLock.release();

	TransactionLog trx(shipDevice, player, shipDeed, TrxCode::SHIPREDEED, true);
	trx.commit();

	Locker playerLock(player, shipDevice);

	// Transfer the deed
	inventory->transferObject(shipDeed, -1, true, true);

	playerLock.release();

	player->broadcastObject(shipDeed, true);

	// Destroy the ship
	Locker shipLock(ship, shipDevice);

	ship->destroyObjectFromWorld(true);
	ship->destroyObjectFromDatabase(true);

	shipLock.release();

	// Destroy the control device
	shipDevice->destroyObjectFromWorld(true);
	shipDevice->destroyObjectFromDatabase(true);

	player->sendSystemMessage("@space/space_interaction:packed"); // "You have successfully packed this ship into a deed!"
}

uint16 ShipManager::setShipUniqueID(ShipObject* ship) {
	if (ship == nullptr) {
		return 0;
	}

	Locker sLock(ship);
	uint16 shipID = shipUniqueIdMap.setUniqueID(ship);

	return shipID;
}

void ShipManager::dropShipUniqueID(ShipObject* ship) {
	if (ship == nullptr) {
		return;
	}

	Locker sLock(ship);
	shipUniqueIdMap.dropUniqueID(ship);
}
