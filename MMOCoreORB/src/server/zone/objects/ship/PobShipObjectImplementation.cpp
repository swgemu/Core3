/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/objects/ship/PobShipObject.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/Zone.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/ZoneClientSession.h"
#include "templates/tangible/ship/SharedShipObjectTemplate.h"
#include "server/zone/objects/ship/PlayerLaunchPoints.h"
#include "server/zone/objects/ship/DamageSparkLocations.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/packets/cell/UpdateCellPermissionsMessage.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/objects/tangible/item/CreditChipObject.h"
#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/objects/tangible/ship/interiorComponents/ShipInteriorComponent.h"

void PobShipObjectImplementation::notifyLoadFromDatabase() {
	CreatureObject* owner = getOwner().get();

	if (owner != nullptr && shipPermissionList.getOwner() != owner->getObjectID()) {
		shipPermissionList.setOwner(owner->getObjectID());
	}

	ShipObjectImplementation::notifyLoadFromDatabase();
}

void PobShipObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipObjectImplementation::loadTemplateData(templateData);

	auto shipTemp = dynamic_cast<SharedShipObjectTemplate*>(templateData);

	if (shipTemp == nullptr) {
		return;
	}

	setContainerVolumeLimit(0xFFFFFFFF);
	setContainerType(2);

	const auto sparkLocs = shipTemp->getSparkLocations();

	for (int i = 0; i < sparkLocs.size(); i++) {
		String cellName = sparkLocs.elementAt(i).getKey();
		Vector<Vector3> locations = sparkLocs.elementAt(i).getValue();

		for (int k = 0; k < locations.size(); k++) {
			Vector3 point(locations.get(k));
			sparkLocations.addSparkLocation(cellName, point);
		}
	}

	const auto launchLocs = shipTemp->getLaunchLocations();

	for (int i = 0; i < launchLocs.size(); i++) {
		String cellName = launchLocs.elementAt(i).getKey();
		Vector<Vector3> locations = launchLocs.elementAt(i).getValue();

		for (int k = 0; k < locations.size(); k++) {
			Vector3 point(locations.get(k));

			launchPoints.addLaunchPoint(cellName, point);
		}
	}
}

void PobShipObjectImplementation::createChildObjects() {
	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		error() << "Failed to create child objects for ship: " << getDisplayedName() << " ID: " << getObjectID();
		return;
	}

	auto layout = getObjectTemplate()->getPortalLayout();

	if (layout == nullptr) {
		return;
	}

	//info(true) << "creating cells for PoB Ship: " << getDisplayedName();

	for (int i = 0; i < totalCellNumber; ++i) {
		// Skip cell from r0
		if (i == 0)
			continue;

		auto newCellObject = zoneServer->createObject(0xAD431713, getPersistenceLevel());

		if (newCellObject == nullptr || !newCellObject->isCellObject()) {
			error() << "could not create cell";
			continue;
		}

		auto newCell = static_cast<CellObject*>(newCellObject.get());

		if (newCell == nullptr)
			continue;

		//info(true) << "Cell #" << (i) << " with name: " << layout->getCellProperty(i)->getName();

		Locker clocker(newCell, asShipObject());

		if (!transferObject(newCell, -1, false, true)) {
			error() << "could not add cell to ship";
			continue;
		}

		newCell->setCellNumber(i);

		cellNameMap.put(layout->getCellProperty(i)->getName(), newCell);
		cells.put(i, newCell);
	}

	for (int i = 0; i < templateObject->getChildObjectsSize(); ++i) {
		const ChildObject* child = templateObject->getChildObject(i);

		if (child == nullptr) {
			continue;
		}

		const String childTemplate = child->getTemplateFile();
		uint32 childHash = childTemplate.hashCode();

		ManagedReference<SceneObject *> obj = zoneServer->createObject(childHash, getPersistenceLevel());

		if (obj == nullptr)
			continue;

		Locker objLocker(obj, asSceneObject());

		Vector3 childPosition = child->getPosition();
		childObjects.put(obj);
		obj->initializePosition(childPosition.getX(), childPosition.getZ(), childPosition.getY());
		obj->setDirection(child->getDirection());

		int totalCells = getTotalCellNumber();
		uint64 ownerID = getOwnerID();

		try {
			if (totalCells >= child->getCellId()) {
				// info(true) << getDisplayedName() << " -- childObject Inserting into cell #" << child->getCellId() << " Object Type: " << obj->getGameObjectType();

				ManagedReference<CellObject*> cellObject = getCell(child->getCellId() - 1);

				if (cellObject != nullptr) {
					ContainerPermissions* permissions = obj->getContainerPermissionsForUpdate();

					if (permissions == nullptr || !cellObject->transferObject(obj, child->getContainmentType(), true)) {
						obj->destroyObjectFromDatabase(true);
						continue;
					}

					permissions->setOwner(ownerID);

					permissions->setInheritPermissionsFromParent(false);
					permissions->setDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
					permissions->setDenyPermission("owner", ContainerPermissions::MOVECONTAINER);

					if (obj->isPilotChair()) {
						setPilotChair(obj);
					} else if (obj->isOperationsChair()) {
						setOperationsChair(obj);
					} else if (obj->isShipTurret()) {
						setTurretLadder(obj);
					} else if (obj->getGameObjectType() == SceneObjectType::SHIPPERMISSIONS) {
						Terminal* terminalChild = obj.castTo<Terminal*>();

						if (terminalChild != nullptr)
							terminalChild->setControlledObject(asPobShip());
					} else if (childTemplate.contains("alarm_")) {
						plasmaAlarms.add(obj->getObjectID());
					} else if (childHash == STRING_HASHCODE("object/tangible/container/drum/pob_ship_loot_box.iff")) {
						shipLootBox = obj;

						permissions->setDenyPermission("owner", ContainerPermissions::MOVEIN);

						permissions->setAllowPermission("owner", ContainerPermissions::OPEN);
						permissions->setAllowPermission("owner", ContainerPermissions::MOVEOUT);
					} else if (obj->isShipInteriorComponent()) {
						auto interiorComponent = obj.castTo<ShipInteriorComponent*>();

						if (interiorComponent != nullptr) {
							interiorComponent->setComponentSlot(child->getComponentSlot());
						}
					}
				} else {
					error("Cell null for create child objects on PobShip");
					obj->destroyObjectFromDatabase(true);
					continue;
				}
			}
		} catch (Exception &e) {
			error("unreported exception caught in void SceneObjectImplementation::createChildObjects()!");
			e.printStackTrace();
		}
	}

	updateToDatabase();
}

void PobShipObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	auto thisPob = asPobShip();

	auto launchZone = getSpaceLaunchZone();
	auto launchLoc = getSpaceLaunchLocation();

	// This should not be an empty string, but just in case it is, send them to Coronet
	if (launchZone.isEmpty()) {
		launchZone = "corellia";
		launchLoc.set(-66, 28, -4711);
	}

	// info(true) << "Launch Zone: " << launchZone << " Location: " << launchLoc.toString();

	// Handle Pilot
	auto pilot = getPilot();

	if (pilot != nullptr) {
		auto pilotChair = getPilotChair().get();

		Locker pClock(pilot, thisPob);

		pilot->switchZone(launchZone, launchLoc.getX(), launchLoc.getZ(), launchLoc.getY(), 0, false, -1);

		if (pilotChair != nullptr && pilotChair->hasObjectInContainer(pilot->getObjectID())) {
			pilotChair->removeObject(pilot, nullptr, false);
		}
	}

	// Handle Operator
	auto shipOperator = getShipOperator();

	if (shipOperator != nullptr) {
		auto operationsChair = getOperationsChair().get();

		Locker pClock(shipOperator, thisPob);

		shipOperator->switchZone(launchZone, launchLoc.getX(), launchLoc.getZ(), launchLoc.getY(), 0, false, -1);

		if (operationsChair != nullptr && operationsChair->hasObjectInContainer(shipOperator->getObjectID())) {
			operationsChair->removeObject(shipOperator, nullptr, false);
		}
	}

	// Handle Turret Top
	auto playerTurretTop = getTurretOperatorTop();

	if (playerTurretTop != nullptr) {
		auto turretLadder = getTurretLadder().get();

		Locker pClock(playerTurretTop, thisPob);

		playerTurretTop->switchZone(launchZone, launchLoc.getX(), launchLoc.getZ(), launchLoc.getY(), 0, false, -1);

		if (turretLadder != nullptr && turretLadder->hasObjectInContainer(playerTurretTop->getObjectID())) {
			turretLadder->removeObject(playerTurretTop, nullptr, false);
		}
	}

	// Handle Turret Bottom
	auto playerTurretBottom = getTurretOperatorBottom();

	if (playerTurretBottom != nullptr) {
		auto turretLadder = getTurretLadder().get();

		Locker pClock(playerTurretBottom, thisPob);

		playerTurretBottom->switchZone(launchZone, launchLoc.getX(), launchLoc.getZ(), launchLoc.getY(), 0, false, -1);

		if (turretLadder != nullptr && turretLadder->hasObjectInContainer(playerTurretBottom->getObjectID())) {
			turretLadder->removeObject(playerTurretBottom, nullptr, false);
		}
	}

	// Check cells for players
	for (int i = 0; i < cells.size(); ++i) {
		auto& cell = cells.get(i);

		if (cell == nullptr) {
			continue;
		}

		for (int j = cell->getContainerObjectsSize() - 1; j >= 0 ; --j) {
			auto child = cell->getContainerObject(j);

			if (child == nullptr) {
				continue;
			}

			if (!child->isPlayerCreature()) {
				continue;
			}

			Locker clock(child, thisPob);

			child->switchZone(launchZone, launchLoc.getX(), launchLoc.getZ(), launchLoc.getY(), 0, false, -1);

			if (cell->hasObjectInContainer(child->getObjectID())) {
				cell->removeObject(child, nullptr, false);
			}
		}
	}

	ShipObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

void PobShipObjectImplementation::notifyInsert(TreeEntry* object) {
	ShipObjectImplementation::notifyInsert(object);
}

void PobShipObjectImplementation::notifyInsertToZone(Zone* zone) {
	Locker locker(zone);

	for (int i = 0; i < cells.size(); ++i) {
		auto& cell = cells.get(i);

		cell->onShipInsertedToZone(asPobShip());
	}

	locker.release();

	ShipObjectImplementation::notifyInsertToZone(zone);
}

int PobShipObjectImplementation::notifyObjectInsertedToChild(SceneObject* object, SceneObject* child, SceneObject* oldParent) {
	Zone* zone = getZone();

	Locker* _locker = nullptr;

	if (zone != nullptr) {
		_locker = new Locker(zone);
	}

	// info(true) << getDisplayedName() << " PobShipObjectImplementation::notifyObjectInsertedToChild -- object inserted: " << object->getDisplayedName() << " ID: " << object->getObjectID() << " Child: " << child->getObjectID() << " oldParent: " << (oldParent != nullptr ? oldParent->getObjectID() : 0);

	try {
		bool objectIsPlayer = object->isPlayerCreature();

		if (object->getCloseObjects() != nullptr) {
			object->addInRangeObject(object, false);
		}

		if (child->isCellObject() || child->isValidJtlParent()) {
			bool hasEnteredRange = false;
			bool oldRootIsPob = false;

			if (oldParent != nullptr) {
				auto oldParentRoot = oldParent->getRootParent();

				if (oldParentRoot == asPobShip()) {
					oldRootIsPob = true;
				}
			}

			// Notify for objects newly transferred into the PobShip
			// Cases old parent is null, old root is not the ship or old parent is not a cell or jtl parent
			//if (oldParent == nullptr || !oldRootIsPob || (oldParent != nullptr && dynamic_cast<Zone*>(oldParent) == nullptr && !oldParent->isCellObject())) {
			if (oldParent == nullptr || !oldRootIsPob || (oldParent != nullptr && (!oldParent->isCellObject() && !oldParent->isValidJtlParent()))) {
				notifyObjectInsertedToZone(object);
				hasEnteredRange = true;
			}

			if (!objectIsPlayer) {
				broadcastDestroy(object, true);
				broadcastObject(object, false);
			}

			if (hasEnteredRange) {
				for (int j = 0; j < child->getContainerObjectsSize(); ++j) {
					ManagedReference<SceneObject*> containedObject = child->getContainerObject(j);

					if (containedObject == nullptr) {
						continue;
					}

					if (containedObject->getCloseObjects() != nullptr) {
						containedObject->addInRangeObject(object, false);
						object->sendTo(containedObject, true, false);
					} else {
						containedObject->notifyInsert(object);
					}

					if (object->getCloseObjects() != nullptr) {
						object->addInRangeObject(containedObject.get(), false);
						containedObject->sendTo(object, true, false);

						if (object->getClient() != nullptr && containedObject->isCreatureObject()) {
							object->sendMessage(containedObject->link(child->getObjectID(), -1));
						}
					} else {
						object->notifyInsert(containedObject.get());
					}
				}

				if (objectIsPlayer) {
					onEnter(object->asCreatureObject());
				}
			}
		}

		if (objectIsPlayer) {
			// Add player to the onboard list
			addPlayerOnBoard(object->asCreatureObject());
		}
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	if (zone != nullptr) {
		delete _locker;
	}

	// info(true) << getDisplayedName() << " PobShipObjectImplementation::notifyObjectInsertedToChild -- FINISHED object inserted: " << object->getDisplayedName() << " ID: " << object->getObjectID();

	return ShipObjectImplementation::notifyObjectInsertedToChild(object, child, oldParent);
}

int PobShipObjectImplementation::notifyObjectRemovedFromChild(SceneObject* object, SceneObject* child) {
	// info(true) << getDisplayedName() << " PobShipObjectImplementation::notifyObjectRemovedFromChild -- object removed: " << object->getDisplayedName() << " ID: " << object->getObjectID();

	ShipObjectImplementation::notifyObjectRemovedFromChild(object, child);

	return 0;
}

void PobShipObjectImplementation::onEnter(CreatureObject* player) {
	if (player == nullptr || !player->isPlayerCreature()) {
		return;
	}

	// info(true) << "PobShipObjectImplementation::onEnter -- Ship ID: " << getObjectID() << " Player: " << player->getDisplayedName();

	// Trigger POB ship entry observer
	notifyObservers(ObserverEventType::ENTEREDPOBSHIP, player, 0);

	// Player has entered the structure. Load objects in the structure for the player
	Reference<CreatureObject*> playerRef = player;

	for (int i = 0; i < cells.size(); ++i) {
		auto& cell = cells.get(i);

		if (cell == nullptr) {
			continue;
		}

		Core::getTaskManager()->scheduleTask([playerRef, cell] () {
			if (playerRef == nullptr || cell == nullptr) {
				return;
			}

			uint64 playerID = playerRef->getObjectID();

			// cell->info(true) << "Loading Cell ID: " << cell->getObjectID() << " for player " << playerRef->getDisplayedName();

			cell->sendTo(playerRef, true);
			cell->sendPermissionsTo(playerRef, true);

			for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
				auto child = cell->getContainerObject(j);

				if (child == nullptr || child->getObjectID() == playerID) {
					continue;
				}

				if (child->getCloseObjects() != nullptr) {
					child->addInRangeObject(playerRef, false);
				} else {
					child->notifyInsert(playerRef);
				}

				child->sendTo(playerRef, true, child->isValidJtlParent());

				if (playerRef->getCloseObjects() != nullptr) {
					playerRef->addInRangeObject(child, false);
				} else {
					playerRef->notifyInsert(child);
				}

				playerRef->sendTo(child, true, false);
			}
		}, "LoadPobShipLambda", ((i * 500) + 5000));
	}
}

void PobShipObjectImplementation::updateZone(bool lightUpdate, bool sendPackets) {
	ShipObjectImplementation::updateZone(lightUpdate, sendPackets);
}

void PobShipObjectImplementation::updatePlayersInShip(bool lightUpdate, bool sendPackets) {
	//info(true) << "PobShipObjectImplementation::updatePlayersInShip - " << getDisplayedName();

	ShipObjectImplementation::updatePlayersInShip(lightUpdate, sendPackets);
}

void PobShipObjectImplementation::sendTo(SceneObject* sceneO, bool doClose, bool forceLoadContainer) {
	if (sceneO == nullptr) {
		return;
	}

	// info(true) << "PobShipObjectImplementation::sendTo - " << getDisplayedName() << " sending to: " << sceneO->getDisplayedName();

	auto player = sceneO->asCreatureObject();

	if (player == nullptr) {
		return;
	}

	ShipObjectImplementation::sendTo(player, doClose, forceLoadContainer);

	bool isLaunched = isShipLaunched();

	auto closeObjects = player->getCloseObjects();

	// for some reason client doesnt like when you send cell creatures while sending cells?
	for (int i = 0; i < cells.size(); ++i) {
		auto& cell = cells.get(i);

		auto perms = cell->getContainerPermissions();

		if (!perms->hasInheritPermissionsFromParent()) {
			BaseMessage* perm = new UpdateCellPermissionsMessage(cell->getObjectID(), false);
			player->sendMessage(perm);
		}

		// Do not send the contents of the ships cells to the player unless it is launched
		if (!isLaunched) {
			continue;
		}

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			auto containerObject = cell->getContainerObject(j);

			if (containerObject == nullptr || containerObject == player) {
				continue;
			}

			if (containerObject->isCreatureObject() || (closeObjects != nullptr && closeObjects->contains(containerObject.get())))
				containerObject->sendTo(player, true, false);
		}
	}
}

void PobShipObjectImplementation::sendContainerObjectsTo(SceneObject* sceneO, bool forceLoad) {
	if (sceneO == nullptr) {
		return;
	}

	// info(true) << "PobShipObjectImplementation::sendContainerObjectsTo - " << getDisplayedName() << " sending to: " << sceneO->getDisplayedName();

	auto player = sceneO->asCreatureObject();

	if (player == nullptr) {
		return;
	}

	auto playerId = player->getObjectID();
	bool isLaunched = isShipLaunched();

	for (int i = 0; i < cells.size(); ++i) {
		auto& cell = cells.get(i);

		cell->sendTo(player, true);
		cell->sendPermissionsTo(player, true);

		// Do not send the contents of the ships cells to the player unless it is launched
		if (!isLaunched) {
			continue;
		}

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			auto object = cell->getContainerObject(j);

			if (object == nullptr || object->getObjectID() == playerId) {
				continue;
			}

			object->sendTo(player, true);
		}
	}
}

void PobShipObjectImplementation::notifyPositionUpdate(TreeEntry* entry) {
	auto scno = static_cast<SceneObject*>(entry);

#if DEBUG_COV_VERBOSE
	info(true) << getDisplayedName() << " -- PobShipObjectImplementation::notifyPositionUpdate being notified for " << scno->getDisplayedName();
#endif // DEBUG_COV_VERBOSE

	for (int i = 0; i < cells.size(); ++i) {
		auto& cell = cells.get(i);

		try {
			for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
				auto child = cell->getContainerObject(j);

				if (child != nullptr && child != entry) {
					if (child->isCreatureObject()) {
						if (child->getCloseObjects() != nullptr)
							child->addInRangeObject(entry);
						else
							child->notifyPositionUpdate(entry);

						if (entry->getCloseObjects() != nullptr)
							entry->addInRangeObject(child);
						else
							entry->notifyPositionUpdate(child);
					} else if (!scno->isCreatureObject() && !child->isCreatureObject()) {
						child->notifyPositionUpdate(entry);
						entry->notifyPositionUpdate(child);
					}
				}
			}
		} catch (Exception& e) {
			warning(e.getMessage());
			e.printStackTrace();
		}
	}
}

void PobShipObjectImplementation::updateCellPermissionsTo(CreatureObject* creature) {
	for (int i = 0; i < cells.size(); ++i) {
		auto& cell = cells.get(i);

		if (cell == nullptr)
			continue;

		cell->sendPermissionsTo(creature, true);
	}
}

bool PobShipObjectImplementation::isOnAdminList(CreatureObject* player) const {
	if (player == nullptr)
		return false;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != nullptr && ghost->isPrivileged())
		return true;
	else if (shipPermissionList.isOnPermissionList("ADMIN", player->getObjectID()))
		return true;
	else {
		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		if (guild != nullptr && shipPermissionList.isOnPermissionList("ADMIN", guild->getObjectID()))
			return true;
	}

	return false;
}

bool PobShipObjectImplementation::isOnPermissionList(const String& listName, CreatureObject* player) const {
	if (player == nullptr)
		return false;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != nullptr && ghost->isPrivileged()) {
		if (listName == "BAN")
			return false;
		else
			return true;
	} else if (shipPermissionList.isOnPermissionList(listName, player->getObjectID()))
		return true;
	else {
		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		if (guild != nullptr && shipPermissionList.isOnPermissionList(listName, guild->getObjectID()))
			return true;
	}

	return false;
}

void PobShipObjectImplementation::togglePlasmaAlarms() {
	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	bool hasActivePlasmaLeak = hasActivePlasmaLeaks();

	for (int i = 0; i < plasmaAlarms.size(); ++i) {
		uint64 alarmID = plasmaAlarms.get(i);

		ManagedReference<SceneObject*> alarm = zoneServer->getObject(alarmID).get();

		if (alarm == nullptr || !alarm->isTangibleObject()) {
			continue;
		}

		TangibleObject* alarmTano = alarm->asTangibleObject();

		if (alarmTano == nullptr) {
			continue;
		}

		Locker alocker(alarm, _this.getReferenceUnsafeStaticCast());

		uint32 alarmOptionBit = alarmTano->getOptionsBitmask();

		if (!hasActivePlasmaLeak && (alarmOptionBit & OptionBitmask::ACTIVATED)) {
			alarmTano->setOptionsBitmask(OptionBitmask::DISABLED);
		} else if (hasActivePlasmaLeak && !(alarmOptionBit & OptionBitmask::ACTIVATED)) {
			alarmTano->setOptionsBitmask(OptionBitmask::ACTIVATED);
			alarmTano->setMaxCondition(0);
		}
	}
}

void PobShipObjectImplementation::addDamagedInteriorComponent(uint64 interiorComponentID, int type) {
	Locker lock(&intComponentsMutex);

	damageInteriorComponents.put(interiorComponentID, type);
}

void PobShipObjectImplementation::removeDamagedInteriorComponent(uint64 interiorComponentID) {
	Locker lock(&intComponentsMutex);

	damageInteriorComponents.drop(interiorComponentID);
}

bool PobShipObjectImplementation::hasActivePlasmaLeaks() {
	Locker lock(&intComponentsMutex);

	for (int i = 0; i < damageInteriorComponents.size(); i++) {
		if (damageInteriorComponents.elementAt(i).getValue() == PobShipObject::PLASMA_CONDUIT) {
			return true;
		}
	}

	return false;
}

int PobShipObjectImplementation::getCurrentNumberOfPlayerItems() {
	int items = 0;

	for (int i = 0; i < cells.size(); ++i) {
		auto& cell = cells.get(i);

		items += cell->getCurrentNumberOfPlayerItems();
	}

	return items;
}

void PobShipObjectImplementation::destroyAllPlayerItems() {
	for (int i = 0; i < cells.size(); ++i) {
		auto& cell = cells.get(i);

		cell->destroyAllPlayerItems();
	}
}

void PobShipObjectImplementation::awardLootItems(ShipAiAgent* destructedShip, int payout) {
	if (destructedShip == nullptr || shipLootBox == nullptr) {
		return;
	}

	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	auto lootManager = zoneServer->getLootManager();

	if (lootManager == nullptr) {
		return;
	}

	auto pilot = getPilot();

	if (pilot == nullptr) {
		return;
	}

	Locker pilotClock(shipLootBox, destructedShip);

	int lootBoxVolume = shipLootBox->getContainerVolumeLimit();

	// Initial LootBox check can return if full
	if ((shipLootBox->getCountableObjectsRecursive() + 1) > lootBoxVolume) {
		pilot->sendSystemMessage("@space/space_loot:loot_box_full"); // "Your loot box is full so your ship cannot hold any more loot."
		return;
	}

	// Get pilots group for messages
	Reference<GroupObject*> pilotGroup = nullptr;

	if (pilot->isGrouped()) {
		pilotGroup = pilot->getGroup();
	}

	// Main Loot TransactionLog
	TransactionLog trx(TrxCode::NPCLOOT, destructedShip);

	auto creditChip = zoneServer->createObject(STRING_HASHCODE("object/tangible/item/loot_credit_chip.iff"), 1).castTo<CreditChipObject*>();

	if (creditChip != nullptr) {
		Locker creditsClock(creditChip, destructedShip);

		// Set the CreditChip value
		creditChip->setUseCount(payout);

		// Create CreditChip TransactionLog
		TransactionLog trxChip(TrxCode::CREDITCHIP, shipLootBox, creditChip, true);

		trxChip.addState("pilotID", pilot->getObjectID());

		// Transfer to POB LootBox
		if (shipLootBox->transferObject(creditChip, -1, true)) {
			StringIdChatParameter creditsSelfMsg("space/space_loot", "looted_credits_you");
			creditsSelfMsg.setDI(payout);

			pilot->sendSystemMessage(creditsSelfMsg);

			trxChip.groupWith(trx);

			if (pilotGroup != nullptr) {
				StringIdChatParameter creditGroupMsg("space/space_loot", "looted_credits");
				creditGroupMsg.setTT(pilot->getFirstName());
				creditGroupMsg.setDI(payout);

				pilotGroup->sendSystemMessage(creditGroupMsg, pilot);
			}
		} else {
			creditChip->destroyObjectFromWorld(true);
			creditChip->destroyObjectFromDatabase(true);

			trx.abort() << "Failed to transferObject for CreditChip into POB Ship Loot Box";
		}
	}

	// Award Loot items here
	int lootRolls = destructedShip->getLootRolls();
	const auto lootTable = destructedShip->getLootTable();

	for (int i = 0; i < lootRolls; i++) {
		// Check if there is space in players inventory, if not do not itterate anymore attempts
		if ((shipLootBox->getCountableObjectsRecursive() + 1) > lootBoxVolume) {
			pilot->sendSystemMessage("@space/space_loot:loot_box_full"); // "Your loot box is full so your ship cannot hold any more loot."
			break;
		}

		uint64 lootObjectID = lootManager->createLoot(trx, shipLootBox, destructedShip);

		if (lootObjectID < 1) {
			continue;
		}

		// Send Pilot Message
		StringIdChatParameter itemSelfMsg("space/space_loot", "looted_item_you"); // "You have looted an item: %TO."
		itemSelfMsg.setTO(lootObjectID);

		pilot->sendSystemMessage(itemSelfMsg);

		// Send Group Messages
		if (pilotGroup != nullptr) {
			StringIdChatParameter itemGroupMsg("space/space_loot", "looted_item"); // "%TT has looted an item: %TO."
			itemGroupMsg.setTT(pilot->getFirstName());
			itemGroupMsg.setTO(lootObjectID);

			pilotGroup->sendSystemMessage(itemGroupMsg, pilot);
		}
	}

	trx.commit(true);
}

PobShipObject* PobShipObject::asPobShip() {
	return this;
}

PobShipObject* PobShipObjectImplementation::asPobShip() {
	return _this.getReferenceUnsafeStaticCast();
}

String PobShipObjectImplementation::getRandomLaunchCell() {
	String cell = launchPoints.getRandomCell();
	return cell;
}

Vector3 PobShipObjectImplementation::getLaunchPointInCell(const String& cellName) {
	auto locations = launchPoints.getSpawnLocations(cellName);
	int random = System::random(locations.size() - 1);
	Vector3 location(locations.get(random));

	return location;
}
