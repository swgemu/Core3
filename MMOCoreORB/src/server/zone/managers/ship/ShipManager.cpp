/*
 * ShipManager.cpp
 *
 *  Created on: 18/10/2013
 *      Author: victor
 */

#include <server/zone/managers/collision/CollisionManager.h>
#include <server/zone/packets/ship/OnShipHit.h>
#include "ShipManager.h"
#include "templates/manager/DataArchiveStore.h"
#include "templates/datatables/DataTableIff.h"
#include "server/zone/objects/ship/ShipChassisData.h"
#include "server/ServerCore.h"
#include "server/zone/ZoneServer.h"
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
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/objects/tangible/deed/ship/ShipDeed.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/planet/PlanetManager.h"

void ShipManager::initialize() {
	loadShipChassisData();
	loadShipComponentData();
	loadShipWeaponData();
	loadHyperspaceLocations();
	loadShipAppearanceData();
	loadShipMissileData();
	loadShipCountermeasureData();
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

		auto compShot = TemplateManager::instance()->getTemplate(compData->getObjectTemplate().hashCode());
		if (compShot == nullptr || !(compShot->getGameObjectType() & SceneObjectType::SHIPATTACHMENT)) {
			continue;
		}

		ManagedReference<ShipComponent*> component = ServerCore::getZoneServer()->createObject(compData->getObjectTemplate().hashCode(), ship->getPersistenceLevel()).castTo<ShipComponent*>();
		if (component != nullptr) {
			ship->install(nullptr, component, slot, false);
		}
	}
}

// Ship is locked coming in
ShipControlDevice* ShipManager::createShipControlDevice(ShipObject* ship) {
	String controlName = "object/intangible/ship/" + ship->getShipName().replaceAll("player_", "") + "_pcd.iff";

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

	shipControlDevice->setShipType(ship->isPobShipObject() ? POBSHIP : FIGHTERSHIP);
	shipControlDevice->setControlledObject(ship);

	ship->setControlDeviceID(shipControlDevice->getObjectID());

	return shipControlDevice;
}

ShipObject* ShipManager::createShip(const String& shipName, int persistence, bool loadComponents) {
	String chassisName = shipName.replaceAll("shared_", "");

	if (!chassisName.contains(".iff")) {
		String path = chassisName.contains("player_") ? "object/ship/player/" : "object/ship/";
		chassisName = path + chassisName + ".iff";
	}

	auto shot = TemplateManager::instance()->getTemplate(chassisName.hashCode());

	if (shot == nullptr || !(shot->getGameObjectType() & SceneObjectType::SHIP)) {
		return nullptr;
	}

	auto zoneServer = ServerCore::getZoneServer();

	if (zoneServer == nullptr)
		return nullptr;

	ManagedReference<ShipObject*> ship = zoneServer->createObject(chassisName.hashCode(), persistence).castTo<ShipObject*>();

	if (ship == nullptr) {
		return nullptr;
	}

	auto shipTemp = dynamic_cast<SharedShipObjectTemplate*>(ship->getObjectTemplate());

	if (shipTemp == nullptr)
		return nullptr;

	if (loadComponents && ship->isShipAiAgent()) {
		ShipAiAgent* agent = ship->asShipAiAgent();

		if (agent != nullptr) {
			agent->loadTemplateData(shot);
			agent->loadTemplateData(shipTemp);

			agent->setShipAiTemplate();
		}
	} else {
		ship->loadTemplateData(shipTemp);
	}

	return ship;
}

ShipObject* ShipManager::createPlayerShip(CreatureObject* owner, const String& shipName, bool loadComponents) {
	if (owner == nullptr)
		return nullptr;

	E3_ASSERT(owner->isLockedByCurrentThread());

	ManagedReference<SceneObject*> dataPad = owner->getSlottedObject("datapad");

	if (dataPad == nullptr) {
		return nullptr;
	}

	PlayerObject* ghost = owner->getPlayerObject();

	if (ghost == nullptr) {
		return nullptr;
	}

	auto ship = createShip(shipName, 1, false);

	if (ship == nullptr) {
		return nullptr;
	}

	Locker shipLock(ship, owner);

	auto shipControlDevice = createShipControlDevice(ship);

	if (shipControlDevice == nullptr) {
		ship->destroyObjectFromDatabase(true);
		ship->destroyObjectFromWorld(true);

		return nullptr;
	}

	Locker cLock(shipControlDevice, ship);

	ship->createChildObjects();

	if (ship->isPobShipObject()) {
		PobShipObject* pobShip = ship->asPobShipObject();

		if (pobShip != nullptr) {
			pobShip->grantPermission("ADMIN", owner->getObjectID());
		}
	}

	if (loadComponents) {
		loadShipComponentObjects(ship);
	}

	if (!dataPad->transferObject(shipControlDevice, -1)) {
		return nullptr;
	}

	ship->setOwner(owner);

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

	auto inventory = player->getSlottedObject("inventory");

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
			auto travelPoint = planetManager->getNearestPlanetTravelPoint(player->getWorldPosition(), 128.f);

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
