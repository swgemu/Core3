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
#include "server/zone/managers/spacecombat/SpaceCombatManager.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "templates/params/creature/CreatureAttribute.h"
#include "server/zone/objects/ship/events/PobCellDotTask.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"

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

	const auto conduitTypes = shipTemp->getPlasmaConduitTypes();

	for (int i = 0; i < conduitTypes.size(); i++) {
		int conduit = conduitTypes.elementAt(i).getKey();
		uint32 componentType = conduitTypes.elementAt(i).getValue();

		plasmaConduitTypes.put(conduit, componentType);
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

	int conduitCount = 0;

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

							if (interiorComponent->isShipPlasmaConduit()) {
								int componentType = plasmaConduitTypes.elementAt(conduitCount).getValue();

								StringBuffer newName;
								newName << "@space/space_item:conduit_";

								switch(componentType) {
									case Components::REACTOR: {
										newName << "reactor";
										break;
									}
									case Components::ENGINE: {
										newName << "engine";
										break;
									}
									case Components::CAPACITOR: {
										newName << "capacitor";
										break;
									}
									case Components::SHIELD0: {
										newName << "shield_0";
										break;
									}
									default:
										break;
								}

								interiorComponent->setObjectName(newName.toString(), false);

								interiorComponent->setPlasmaConduitType(componentType);
								conduitCount++;

								plasmaConduits.add(interiorComponent);
							} else {
								interiorComponents.add(interiorComponent);
							}
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

	// Check plasma conduits for cell fires
	checkPlasmaConduits();

	// Scehedule the CellDotTask
	if (cellDotTask == nullptr) {
		cellDotTask = new PobCellDotTask(asPobShip());
	}

	if (!cellDotTask->isScheduled()) {
		cellDotTask->schedule(PobShipObject::CELL_DOT_TICK * 2000);
	}

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

	damagedInteriorComponents.put(interiorComponentID, type);
}

void PobShipObjectImplementation::removeDamagedInteriorComponent(uint64 interiorComponentID) {
	Locker lock(&intComponentsMutex);

	damagedInteriorComponents.drop(interiorComponentID);
}

bool PobShipObjectImplementation::hasActivePlasmaLeaks() {
	for (int i = 0; i < plasmaConduits.size(); i++) {
		auto plasmaConduit = plasmaConduits.get(i);

		if (plasmaConduit == nullptr) {
			return false;
		}

		if (!(plasmaConduit->getOptionsBitmask() & OptionBitmask::ACTIVATED)) {
			continue;
		}

		return true;
	}

	return false;
}

void PobShipObjectImplementation::triggerInteriorDamage(int hitType, float damageVar) {
	uint8 hitLevel = PobShipObject::DAMAGE_LOW;

	if (damageVar < 20.f) {
		hitLevel = PobShipObject::DAMAGE_HIGH;
	}

	// info(true) << "triggerInteriorDamage -- Component Type: " << hitType << " Damage Variable: " << damageVar;

	int totalSparkLocs = sparkLocations.getTotalSparkCells();

	if (totalSparkLocs < 1) {
		return;
	}

	auto randomCell = sparkLocations.getRandomCell();

	if (randomCell.isEmpty()) {
		return;
	}

	auto cell = getCell(randomCell);

	if (cell == nullptr) {
		return;
	}

	const auto damageSparkLocs = sparkLocations.getSparkLocations(randomCell);

	if (damageSparkLocs.size() < 1) {
		return;
	}

	Vector3 location = damageSparkLocs.get(System::random(damageSparkLocs.size() - 1));

	auto zone = getZone();

	if (zone == nullptr) {
		return;
	}

	// info(true) << "triggerInteriorDamage -- Component Type: " << hitType << " Damage Variable: " << damageVar << " Random Cell: " << randomCell << " Total Spark Locs: " << damageSparkLocs.size();

	PlayClientEffectLoc* effectLoc = nullptr;

	int count = 0;
	int chance = 0;
	Vector<String> clientEffects;
	Vector<float> damageRanges;
	int conduitChance = 0;

	switch (hitType) {
		case SpaceCombatManager::ShipHitType::HITSHIELD: {
			effectLoc = new PlayClientEffectLoc("clienteffect/int_camshake_light.cef", zone->getZoneName(), location.getX(), location.getZ(), location.getY(), cell->getObjectID());

			if (hitLevel == PobShipObject::DAMAGE_LOW) {
				count = 5;
				chance = 50;
				clientEffects = {"clienteffect/lair_damage_light.cef"};
				damageRanges = {0.f};
			} else {
				count = 7;
				chance = 50;
				clientEffects = {"clienteffect/lair_damage_light.cef", "clienteffect/lair_damage_light.cef", "clienteffect/lair_damage_medium.cef"};
				damageRanges = {0.f, 0.f, 2.f};
			}
			break;
		}
		case SpaceCombatManager::ShipHitType::HITARMOR: {
			if (hitLevel == PobShipObject::DAMAGE_LOW) {
				effectLoc = new PlayClientEffectLoc("clienteffect/int_camshake_light.cef", zone->getZoneName(), location.getX(), location.getZ(), location.getY(), cell->getObjectID());

				count = 5;
				chance = 50;
				clientEffects = {"clienteffect/lair_damage_light.cef", "clienteffect/lair_med_damage_smoke.cef", "clienteffect/lair_damage_medium.cef"};
				damageRanges = {0.f, 0.f, 2.f};
				conduitChance = 2;
			} else {
				effectLoc = new PlayClientEffectLoc("clienteffect/int_camshake_medium.cef", zone->getZoneName(), location.getX(), location.getZ(), location.getY(), cell->getObjectID());

				count = 15;
				chance = 50;
				clientEffects = {"clienteffect/lair_damage_light.cef", "clienteffect/lair_damage_medium.cef", "clienteffect/lair_damage_light.cef", "clienteffect/lair_damage_medium.cef", "clienteffect/lair_damage_medium.cef", "clienteffect/lair_damage_medium.cef"};
				damageRanges = {0.f, 2.f, 0.f, 2.f, 2.f, 2.f};
				conduitChance = 5;
			}
			break;
		}
		case SpaceCombatManager::ShipHitType::HITCOMPONENT: {
			if (hitLevel == PobShipObject::DAMAGE_LOW) {
				effectLoc = new PlayClientEffectLoc("clienteffect/int_camshake_light.cef", zone->getZoneName(), location.getX(), location.getZ(), location.getY(), cell->getObjectID());

				count = 10;
				chance = 50;
				clientEffects = {"clienteffect/lair_damage_light.cef", "clienteffect/lair_med_damage_smoke.cef", "clienteffect/lair_damage_medium.cef", "clienteffect/combat_ship_hit_shield.cef"};
				damageRanges = {0.f, 2.f, 2.f, 4.f};
				conduitChance = 10;
			} else {
				effectLoc = new PlayClientEffectLoc("clienteffect/int_camshake_heavy.cef", zone->getZoneName(), location.getX(), location.getZ(), location.getY(), cell->getObjectID());

				count = 20;
				chance = 50;
				clientEffects = {"clienteffect/lair_damage_light.cef", "clienteffect/lair_med_damage_smoke.cef", "clienteffect/lair_damage_medium.cef", "clienteffect/combat_ship_hit_component.cef"};
				damageRanges = {0.f, 0.f, 2.f, 8.f};
				conduitChance = 20;
			}
			break;
		}
		case SpaceCombatManager::ShipHitType::HITCHASSIS: {
			if (hitLevel == PobShipObject::DAMAGE_LOW) {
				effectLoc = new PlayClientEffectLoc("clienteffect/int_camshake_heavy.cef", zone->getZoneName(), location.getX(), location.getZ(), location.getY(), cell->getObjectID());

				count = 5;
				chance = 50;
				clientEffects = {"clienteffect/lair_damage_light.cef", "clienteffect/lair_med_damage_smoke.cef", "clienteffect/lair_damage_medium.cef", "clienteffect/combat_ship_hit_component.cef"};
				damageRanges = {0.f, 0.f, 2.f, 8.f};
				conduitChance = 30;
			} else {
				effectLoc = new PlayClientEffectLoc("clienteffect/int_camshake_heavy.cef", zone->getZoneName(), location.getX(), location.getZ(), location.getY(), cell->getObjectID());

				count = 10;
				chance = 50;
				clientEffects = {"clienteffect/lair_damage_light.cef", "clienteffect/lair_med_damage_smoke.cef", "clienteffect/lair_damage_medium.cef", "clienteffect/combat_ship_hit_death.cef"};
				damageRanges = {0.f, 0.f, 2.f, 8.f};
				conduitChance = 50;
			}
			break;
		}
		default:
			break;
	}

	doInteriorEffect(zone, cell, randomCell, count, chance, clientEffects, damageRanges, conduitChance);

	if (effectLoc != nullptr) {
		sendMembersBaseMessage(effectLoc);
	}
}

void PobShipObjectImplementation::doInteriorEffect(Zone* zone, CellObject* cell, String& randomCell, int count, int chance, Vector<String>& clientEffects, Vector<float>& damageRanges, int conduitChance) {
	if (zone == nullptr || cell == nullptr || randomCell.isEmpty()) {
		return;
	}

	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	auto thisPob = asPobShip();
	uint64 cellID = cell->getObjectID();

	const Vector<int> damageAmount = {0, 15, 30, 75};
	const Vector<uint8> type = {CreatureAttribute::HEALTH, CreatureAttribute::ACTION, CreatureAttribute::MIND};

	// info(true) << "doInteriorEffect -- Random Cell: " << randomCell << " Count: " << count << " Chance: " << chance << " Conduit Chance: " << conduitChance;

	for (int i = 0; i < count; i++) {
		int effectsRoll = System::random(100);

		if (chance < effectsRoll) {
			continue;
		}

		int randomSelection = System::random(clientEffects.size() - 1);

		const auto clientEffect = clientEffects.get(randomSelection);
		const auto damageRange = damageRanges.get(randomSelection);

		const auto damageSparkLocs = sparkLocations.getSparkLocations(randomCell);
		Vector3 location = damageSparkLocs.get(System::random(damageSparkLocs.size() - 1));

		// info(true) << "Doing Interior Effect - Random Selection: " << randomSelection <<  " Cef: " << clientEffect << " Damage Range: " << damageRange << " Damage Location: " << location.toString();

		PlayClientEffectLoc* effectLoc = new PlayClientEffectLoc("clienteffect/int_camshake_heavy.cef", zone->getZoneName(), location.getX(), location.getZ(), location.getY(), cell->getObjectID());

		if (effectLoc != nullptr) {
			sendMembersBaseMessage(effectLoc);
		}

		if (damageRange > 0.f) {
			for (int j = 0; j < playersOnBoard.size(); ++j) {
				auto shipMemberID = playersOnBoard.get(j);
				auto shipMember = cast<CreatureObject*>(zoneServer->getObject(shipMemberID).get());

				if (shipMember == nullptr) {
					continue;
				}

				if (shipMember->getParentID() != cellID || location.squaredDistanceTo(shipMember->getPosition()) < (damageRange * damageRange)) {
					continue;
				}

				uint8 randomType = type.get(System::random(type.size() - 1));
				int randomAmount = System::random(damageAmount.get((int)randomSelection));

				Core::getTaskManager()->executeTask([shipMember, randomType, randomAmount]() {
					if (shipMember == nullptr) {
						return;
					}

					Locker lock(shipMember);

					shipMember->inflictDamage(nullptr, randomType, randomAmount, true, true);
				}, "PobInternalDamageLambda");
			}
		}
	}

	if (conduitChance == 0) {
		return;
	}

	int conduitRoll = System::random(100);

	// info(true) << "Rolling for Conduits - Chance: " << conduitChance << " Roll: " << conduitRoll << " Total Plasma Conduots: " << plasmaConduits.size();

	if (conduitRoll > conduitChance) {
		return;
	}

	auto randomPlasmaCond = plasmaConduits.get(System::random(plasmaConduits.size() - 1));

	// Activate Plasma Conduit
	if (randomPlasmaCond->getOptionsBitmask() & OptionBitmask::ACTIVATED) {
		return;
	}

	Locker plasmaClock(randomPlasmaCond, thisPob);

	// Activate the Plasma Conduit
	randomPlasmaCond->setOptionBit(OptionBitmask::ACTIVATED);

	// Add it to the damaged interior components map
	addDamagedInteriorComponent(randomPlasmaCond->getObjectID(), PobShipObject::PLASMA_CONDUIT);

	// Activate the plasma Alarms
	togglePlasmaAlarms();

	// Conduit burst message
	StringIdChatParameter conduitMessage("space/space_interaction", "conduit_burst"); // "                  WARNING! WARNING! WARNING!      A %TO has been damaged! A Plasma leak has occurred!                  WARNING! WARNING! WARNING!"
	conduitMessage.setTO(randomPlasmaCond->getDisplayedName());

	ChatSystemMessage* chatMsg = new ChatSystemMessage(conduitMessage);

	// Broadcast the message to players on board
	if (chatMsg != nullptr) {
		sendMembersBaseMessage(chatMsg);
	}

	// info(true) << "Activating Plasma Conduit - " << randomPlasmaCond->getDisplayedName();

	// Get the conduits cell parent
	ManagedReference<CellObject*> cellParent = randomPlasmaCond->getParent().get().castTo<CellObject*>();

	if (cellParent != nullptr) {
		// Lock the cellParent
		Locker clock(cellParent, thisPob);

		// Add fire dot variable to cell
		cellParent->setCellFireVariable(1.f);

		if (cellDotTask == nullptr) {
			cellDotTask = new PobCellDotTask(asPobShip());
		}

		if (!cellDotTask->isScheduled()) {
			cellDotTask->schedule(PobShipObject::CELL_DOT_TICK * 2000);
		}
	}
}

bool PobShipObjectImplementation::triggerCellDamageOverTime() {
	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		return false;
	}

	auto thisPob = asPobShip();
	bool returnHasDots = false;

	for (int i = 0; i < cells.size(); ++i) {
		auto& cell = cells.get(i);

		if (cell == nullptr) {
			continue;
		}

		const float damageVar = cell->getCellFireVariable();

		if (damageVar < 1.f) {
			continue;
		}

		returnHasDots = true;

		Locker clock(cell, thisPob);

		float totalDamage = damageVar * PobShipObject::CELL_DOT_MULTI;
		float totalWounds = totalDamage / 10.f;
		uint64 cellID = cell->getObjectID();

		// info(true) << "Cell Fire Dot Tick Triggered -- Cell: " << cell->getObjectID() << " Damage Var: " << damageVar << " Total Damage: " << totalDamage << " Total Wounds: " << totalWounds;

		for (int j = 0; j < playersOnBoard.size(); ++j) {
			auto shipMemberID = playersOnBoard.get(j);
			Reference<CreatureObject*> shipMember = cast<CreatureObject*>(zoneServer->getObject(shipMemberID).get());

			if (shipMember == nullptr) {
				continue;
			}

			Locker clock(shipMember, thisPob);

			if (shipMember->getParentID() != cellID) {
				continue;
			}

			Core::getTaskManager()->executeTask([shipMember, totalDamage, totalWounds]() {
				if (shipMember == nullptr) {
					return;
				}

				Locker lock(shipMember);

				// shipMember->info(true) << "Cell Fire Dot Tick on member - ShipMember: " << shipMember->getDisplayedName() << " Total Damage: " << totalDamage << " Total Wounds: " << totalWounds;

				// Send the message to players in this cell that, others will receive it if they enter the cell.
				if (!shipMember->hasState(CreatureState::ONFIRE)) {
					shipMember->setState(CreatureState::ONFIRE, true);

					shipMember->sendSystemMessage("@space/space_interaction:plasma_leak_begin"); // "This area of the ship has a PLASMA LEAK! It begins to scorch the flesh from your bones!"
				}

				// Add damage and wounds
				shipMember->inflictDamage(nullptr, CreatureAttribute::HEALTH, totalDamage, true, true);
				shipMember->addWounds(CreatureAttribute::HEALTH, totalWounds, true, true);

				// Player Fire DOT effect
				shipMember->playEffect("clienteffect/dot_fire.cef","");

				shipMember->addDotState(shipMember, CreatureState::ONFIRE, 0, totalDamage, CreatureAttribute::HEALTH, 60, -1, 0, 20);
			}, "PobCellFireLambda");
		}
	}

	return returnHasDots;
}
void PobShipObjectImplementation::checkPlasmaConduits() {
	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	auto thisPob = asPobShip();

	VectorMap<uint64, int> cellMap;
	cellMap.setNullValue(0);

	for (int i = 0; i < plasmaConduits.size(); i++) {
		auto plasmaConduit = plasmaConduits.get(i);

		if (plasmaConduit == nullptr) {
			continue;
		}

		Locker clock(plasmaConduit, thisPob);

		uint64 cellID = plasmaConduit->getParentID();
		float currentVar = 0.f;

		if (cellMap.contains(cellID)) {
			currentVar = cellMap.get(cellID);
		}

		// info(true) << "Checking Plasma Conduit: " << plasmaConduit->getDisplayedName() << " in Cell ID: " << cellID << " Active: " << ((plasmaConduit->getOptionsBitmask() & OptionBitmask::ACTIVATED) ? "true" : "false") << " currentVar: " << currentVar;

		if ((plasmaConduit->getOptionsBitmask() & OptionBitmask::ACTIVATED)) {
			currentVar += 1.f;
		}

		// info(true) << "Final currentVar: " << currentVar;

		cellMap.put(cellID, currentVar);
	}

	// Apply to the cells
	for (int i = 0; i < cells.size(); ++i) {
		auto& cell = cells.get(i);

		if (cell == nullptr) {
			continue;
		}

		Locker clock(cell, thisPob);

		auto cellID = cell->getObjectID();
		float currentVar = cell->getCellFireVariable();
		float damageVar = 0.f;

		if (cellMap.contains(cellID)) {
			damageVar = cellMap.get(cellID);
		}

		if (fabs(damageVar - currentVar) < 0.1f) {
			continue;
		}

		// info(true) << "Adjusting cell: " << cellID << " Variable by: " << (damageVar - currentVar);

		cell->setCellFireVariable(damageVar - currentVar);
	}
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
