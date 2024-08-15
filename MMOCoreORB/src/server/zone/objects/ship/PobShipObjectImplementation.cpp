/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/objects/ship/PobShipObject.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/Zone.h"
#include "templates/tangible/ship/SharedShipObjectTemplate.h"
#include "server/zone/objects/ship/PlayerLaunchPoints.h"
#include "server/zone/objects/ship/DamageSparkLocations.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/packets/cell/UpdateCellPermissionsMessage.h"

void PobShipObjectImplementation::notifyLoadFromDatabase() {
	CreatureObject* owner = getOwner().get();

	if (owner != nullptr && shipPermissionList.getOwner() != owner->getObjectID()) {
		shipPermissionList.setOwner(owner->getObjectID());
	}

	ShipObjectImplementation::notifyLoadFromDatabase();
}

void PobShipObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipObjectImplementation::loadTemplateData(templateData);
}

void PobShipObjectImplementation::loadTemplateData(SharedShipObjectTemplate* ssot) {
	if (ssot == nullptr) {
		return;
	}

	ShipObjectImplementation::loadTemplateData(ssot);

	setContainerVolumeLimit(0xFFFFFFFF);
	setContainerType(2);

	const auto sparkLocs = ssot->getSparkLocations();

	for (int i = 0; i < sparkLocs.size(); i++) {
		String cellName = sparkLocs.elementAt(i).getKey();
		Vector<Vector3> locations = sparkLocs.elementAt(i).getValue();

		for (int k = 0; k < locations.size(); k++) {
			Vector3 point(locations.get(k));
			sparkLocations.addSparkLocation(cellName, point);
		}
	}

	const auto launchLocs = ssot->getLaunchLocations();

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

	if (layout == nullptr)
		return;

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

		if (child == nullptr)
			continue;

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

		try {
			if (totalCells >= child->getCellId()) {
				// info(true) << getDisplayedName() << " -- childObject Inserting into cell #" << child->getCellId() << " Object Type: " << obj->getGameObjectType();

				ManagedReference<CellObject*> cellObject = getCell(child->getCellId() - 1);

				if (cellObject != nullptr) {
					if (!cellObject->transferObject(obj, child->getContainmentType(), true)) {
						obj->destroyObjectFromDatabase(true);
						continue;
					}

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
					} else if (childTemplate.contains("alarm_interior")) {
						plasmaAlarms.add(obj->getObjectID());
					}

					ContainerPermissions* permissions = obj->getContainerPermissionsForUpdate();

					if (permissions != nullptr) {
						permissions->setOwner(getObjectID());
						permissions->setInheritPermissionsFromParent(false);
						permissions->setDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
						permissions->setDenyPermission("owner", ContainerPermissions::MOVECONTAINER);
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
	auto thisPob = asShipObject();

	SortedVector<ManagedReference<SceneObject*>> players;

	// Check cells for players
	for (int i = cells.size() - 1; i >= 0 ; --i) {
		auto cell = cells.get(i);

		if (cell == nullptr)
			continue;

		for (int j = cell->getContainerObjectsSize() - 1; j >= 0 ; --j) {
			auto object = cell->getContainerObject(j);

			if (object == nullptr || !object->isPlayerCreature())
				continue;

			players.put(object);
		}
	}

	// Kick all the players to the ground zone
	for (int i = players.size() - 1; i >= 0 ; --i) {
		auto object = players.get(i);

		if (object == nullptr)
			continue;

		auto player = object->asCreatureObject();

		if (player == nullptr)
			continue;

		Locker clock(player, thisPob);

		auto ghost = player->getPlayerObject();

		if (ghost == nullptr)
			continue;

		auto launchZone = ghost->getSpaceLaunchZone();

		if (launchZone.isEmpty())
			launchZone = "tatooine";

		auto launchLoc = ghost->getSpaceLaunchLocation();

		player->switchZone(launchZone, launchLoc.getX(), launchLoc.getZ(), launchLoc.getY(), 0, false, -1);
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

	// Do not send the contents of the ships cells to the player unless it is launched
	if (!isShipLaunched()) {
		return;
	}

	auto closeObjects = player->getCloseObjects();

	// for some reason client doesnt like when you send cell creatures while sending cells?
	for (int i = 0; i < cells.size(); ++i) {
		auto& cell = cells.get(i);

		auto perms = cell->getContainerPermissions();

		if (!perms->hasInheritPermissionsFromParent()) {
			BaseMessage* perm = new UpdateCellPermissionsMessage(cell->getObjectID(), false);
			player->sendMessage(perm);
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

	// Do not send the contents of the ships cells to the player unless it is launched
	if (!isShipLaunched()) {
		return;
	}

	auto player = sceneO->asCreatureObject();

	if (player == nullptr) {
		return;
	}

	auto playerId = player->getObjectID();

	for (int i = 0; i < cells.size(); ++i) {
		auto& cell = cells.get(i);

		cell->sendTo(player, true);
		cell->sendPermissionsTo(player, true);

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

	if (zoneServer == nullptr)
		return;

	for (int i = 0; i < plasmaAlarms.size(); ++i) {
		uint64 alarmID = plasmaAlarms.get(i);

		ManagedReference<SceneObject*> alarm = zoneServer->getObject(alarmID).get();

		if (alarm == nullptr || !alarm->isTangibleObject()) {
			continue;
		}

		TangibleObject* alarmTano = alarm->asTangibleObject();

		if (alarmTano == nullptr)
			continue;

		Locker alocker(alarm, _this.getReferenceUnsafeStaticCast());

		if (alarmTano->getOptionsBitmask() & OptionBitmask::ACTIVATED) {
			alarmTano->setOptionsBitmask(OptionBitmask::DISABLED);
		} else {
			alarmTano->setOptionsBitmask(OptionBitmask::ACTIVATED);
			alarmTano->setMaxCondition(0);
		}
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
