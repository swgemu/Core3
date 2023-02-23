/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "ComponentSlots.h"
#include "ShipComponentFlag.h"
#include "system/lang/UnicodeString.h"
#include "server/zone/Zone.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/ZoneClientSession.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/components/ShipComponent.h"
#include "server/zone/objects/ship/components/ShipEngineComponent.h"
#include "server/zone/objects/ship/events/ShipRecoveryEvent.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/packets/ship/ShipObjectMessage1.h"
#include "server/zone/packets/ship/ShipObjectMessage3.h"
#include "server/zone/packets/ship/ShipObjectMessage4.h"
#include "server/zone/packets/ship/ShipObjectMessage6.h"
#include "server/zone/packets/cell/UpdateCellPermissionsMessage.h"
#include "server/zone/packets/scene/SceneObjectCreateMessage.h"
#include "templates/tangible/SharedShipObjectTemplate.h"
#include "server/zone/objects/ship/ShipChassisData.h"
#include "templates/faction/Factions.h"

void ShipObjectImplementation::initializeTransientMembers() {
	hyperspacing = false;

	if (shipRecoveryEvent == nullptr) {
		shipRecoveryEvent = new ShipRecoveryEvent(asShipObject());
	}

	TangibleObjectImplementation::initializeTransientMembers();
}

void ShipObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	SharedShipObjectTemplate* ssot = dynamic_cast<SharedShipObjectTemplate*>(templateData);

	if (ssot != nullptr) {
		setShipName(ssot->getShipName());
		setShipType(ssot->getShipType(), false);
		setShipNameCRC(chassisDataName.hashCode(), false);
		setUniqueID(generateUniqueID(), false);

		setChassisMaxHealth(ssot->getChassisHitpoints(), false);
		setCurrentChassisHealth(ssot->getChassisHitpoints(), false);

		setSlipRate(ssot->getChassisSlipRate(), false);
		setChassisSpeed(ssot->getChassisSpeed(), false);
		setChassisMaxMass(ssot->getChassisMass(), false);

		setShipFaction(ssot->getShipFaction(), false);
		setShipDifficulty(ssot->getShipDifficulty(), false);

		setConversationMessage(ssot->getConversationMessage());
		setConversationMobile(ssot->getConversationMobile());
		setConversationTemplate(ssot->getConversationTemplate());

		setHasWings(ssot->shipHasWings());
	}

	const ShipChassisData* chassisData = ShipManager::instance()->getChassisData(getShipName());

	if (chassisData != nullptr) {
		openWingSpeed = chassisData->getWingOpenSpeed();
	}

	const PortalLayout* portal = ssot->getPortalLayout();

	if (portal != nullptr) {
		totalCellNumber = portal->getCellTotalNumber();
	} else {
		totalCellNumber = 0;
	}
}

void ShipObjectImplementation::sendTo(SceneObject* player, bool doClose, bool forceLoadContainer) {
	BaseMessage* msg = new SceneObjectCreateMessage(asSceneObject());
	player->sendMessage(msg);

	link(player, containmentType);

	try {
		sendBaselinesTo(player);
		sendSlottedObjectsTo(player);
		sendContainerObjectsTo(player, false);
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	if (doClose)
		SceneObjectImplementation::close(player);
}

void ShipObjectImplementation::storeShip(CreatureObject* player) {
	if (player == nullptr)
		return;

	ZoneServer* zoneServer = player->getZoneServer();

	if (zoneServer == nullptr)
		return;

	ShipControlDevice* shipControlDevice = zoneServer->getObject(getControlDeviceID()).castTo<ShipControlDevice*>();

	if (shipControlDevice == nullptr)
		return;

	shipControlDevice->storeShip(player);
}

void ShipObjectImplementation::createChildObjects() {
	auto layout = getObjectTemplate()->getPortalLayout();

	if (layout == nullptr)
		return;

	for (int i = 0; i < totalCellNumber; ++i) {

		Reference<CellObject*> newCell = getZoneServer()->createObject(0xAD431713, getPersistenceLevel()).castTo<CellObject*>();

		if (newCell == nullptr) {
			error("could not create cell");
			continue;
		}

		Locker clocker(newCell, asShipObject());

		if (!transferObject(newCell, -1, true, true)) {
			error("could not add cell");
			continue;
		}

		newCell->setCellNumber(i + 1);

		if (i != 0) {
			cellNameMap.put(layout->getCellProperty(i-1)->getName(), newCell);
		}

		cells.put(i, newCell);
	}

	ZoneServer* zoneServer = getZoneServer();

	for (int i = 0; i < templateObject->getChildObjectsSize(); ++i) {
		const ChildObject* child = templateObject->getChildObject(i);

		if (child == nullptr)
			continue;

		uint32 childHash = child->getTemplateFile().hashCode();

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
				ManagedReference<CellObject *> cellObject = getCell(child->getCellId());

				info("Inserting into " + String::valueOf(cellObject->getObjectID()), true);

				if (cellObject != nullptr) {
					if (!cellObject->transferObject(obj, child->getContainmentType(), true)) {
						obj->destroyObjectFromDatabase(true);
						continue;
					} else {
						if (obj->getGameObjectType() == SceneObjectType::PILOTCHAIR)
							setPilotChair(obj);
					}
				} else {
					error("nullptr CELL OBJECT");
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

void ShipObjectImplementation::sendContainerObjectsTo(SceneObject* player, bool forceLoad) {
	auto creo = player->asCreatureObject();

	if (creo == nullptr) {
		return;
	}

	for (int i = 0; i < containerObjects.size(); ++i) {
		auto object = containerObjects.get(i);

		if (object == nullptr) {
			continue;
		}

		object->sendTo(creo, true);
	}

	for (int i = 0; i < cells.size(); ++i) {
		auto cell = cells.get(i);

		if (cell == nullptr || !cell->isContainerLoaded()) {
			continue;
		}

		auto perms = cell->getContainerPermissions();
		if (perms == nullptr) {
			continue;
		}

		cell->sendPermissionsTo(player->asCreatureObject(), true);

		for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
			auto object = cell->getContainerObject(j);
			if (object == nullptr) {
				continue;
			}

			object->sendTo(creo, true);
		}
	}
}

void ShipObjectImplementation::sendSlottedObjectsTo(SceneObject* player) {
	VectorMap<String, ManagedReference<SceneObject* > > slotted;
	getSlottedObjects(slotted);

	SortedVector<uint64> objects(slotted.size(), slotted.size());
	objects.setNoDuplicateInsertPlan();

	for (int i = 0; i < slotted.size(); ++i) {
		SceneObject* object = slotted.get(i);
		if (object == nullptr || objects.put(object->getObjectID()) == -1) {
			continue;
		}

		if (object == player && player->getMovementCounter() != 0) {
			continue;
		}

		if (object->isInOctTree()) {
			notifyInsert(object);
		} else {
			object->sendTo(player, true, false);
		}
	}
}

void ShipObjectImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
		const String& attribute = values->getExperimentalPropertySubtitle(i);
		float value = values->getCurrentValue(attribute);

		if (attribute == "hp") {
			setChassisMaxHealth(value, false);
			setCurrentChassisHealth(value, false);
		} else if (attribute == "massmax") {
			setChassisMaxMass(value, false);
		}
	}
}

void ShipObjectImplementation::sendBaselinesTo(SceneObject* player) {
	bool sendSelf = player == getOwner().get();

	if (sendSelf) {
		ShipObjectMessage1* ship1 = new ShipObjectMessage1(asShipObject());
		player->sendMessage(ship1);
	}

	ShipObjectMessage3* ship3 = new ShipObjectMessage3(asShipObject());
	player->sendMessage(ship3);

	if (sendSelf) {
		ShipObjectMessage4* ship4 = new ShipObjectMessage4(asShipObject());
		player->sendMessage(ship4);
	}

	ShipObjectMessage6* ship6 = new ShipObjectMessage6(asShipObject());
	player->sendMessage(ship6);

	if (player->isPlayerCreature()) {
		auto playerCreature = player->asCreatureObject();

		if (playerCreature != nullptr) {
			sendPvpStatusTo(playerCreature);
		}
	}
}

ShipObject* ShipObjectImplementation::asShipObject() {
	return _this.getReferenceUnsafeStaticCast();
}

ShipObject* ShipObject::asShipObject() {
	return this;
}

void ShipObjectImplementation::install(CreatureObject* player, SceneObject* sceno, int slot, bool notifyClient) {
	if (getComponentObject(slot) != nullptr) {
		return uninstall(player, slot, notifyClient);
	}

	ManagedReference<ShipComponent*> shipComponent = dynamic_cast<ShipComponent*>(sceno);
	if (shipComponent == nullptr) {
		return;
	}

	Locker lock(shipComponent);
	shipComponent->destroyObjectFromWorld(false);

	if (!transferObject(shipComponent, -1, notifyClient, true)) {
		return;
	}

	setComponentObject(slot, shipComponent);

	shipComponent->install(player, asShipObject(), slot, notifyClient);
}

void ShipObjectImplementation::uninstall(CreatureObject* player, int slot, bool notifyClient) {
	ManagedReference<ShipComponent*> shipComponent = getComponentObject(slot);
	if (shipComponent == nullptr) {
		return;
	}

	Locker lock(shipComponent);
	shipComponent->destroyObjectFromWorld(false);

	if (player != nullptr) {
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		if (inventory == nullptr || !inventory->transferObject(shipComponent, -1, notifyClient, true)) {
			return;
		}

		if (notifyClient) {
			shipComponent->sendTo(player, true);
		}
	}

	setComponentObject(slot, nullptr);

	shipComponent->uninstall(player, asShipObject(), slot, notifyClient);
}

String ShipObjectImplementation::getParkingLocation() {
	if (parkingLocation == "") {
		ManagedReference<CreatureObject*> creo = owner.get();
		if (creo != nullptr) {
			parkingLocation = creo->getCityRegion().get()->getRegionDisplayedName();
		}
	}
	return parkingLocation;
}

int ShipObjectImplementation::notifyObjectInsertedToChild(SceneObject* object, SceneObject* child, SceneObject* oldParent) {
	ManagedReference<SpaceZone*> zone = getSpaceZone();

	Locker* _locker = nullptr;

	if (zone != nullptr)
		_locker = new Locker(zone);

	try {
		if (object->getCloseObjects() != nullptr)
			object->addInRangeObject(object, false);

		if (child->isCellObject()) {
			bool runInRange = true;

			if ((oldParent == nullptr || !oldParent->isCellObject()) || oldParent == child) {

				if (oldParent == nullptr || (oldParent != nullptr && dynamic_cast<SpaceZone*>(oldParent) == nullptr && !oldParent->isCellObject())) {
					//notifyObjectInsertedToZone(object);
					runInRange = false;
				}

				if (!object->isPlayerCreature()) {
					broadcastDestroy(object, true);
					broadcastObject(object, false);
				}
			}

			if (runInRange) {
				ManagedReference<CellObject*> cell = cast<CellObject*>(child);

				if (cell != nullptr) {
					for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
						ManagedReference<SceneObject*> cobj = cell->getContainerObject(j);

						if (cobj != object) {

							if (cobj->getCloseObjects() != nullptr) {
								if (!cobj->getCloseObjects()->contains(object)) {
									cobj->addInRangeObject(object, false);
									object->sendTo(cobj, true, false);
								}
							} else
								cobj->notifyInsert(object);

							if (object->getCloseObjects() != nullptr) {
								if (!object->getCloseObjects()->contains(cobj.get())) {
									object->addInRangeObject(cobj.get(), false);
									cobj->sendTo(object, true, false);//sendTo because notifyInsert doesnt send objects with parent
								} else {
									if (object->getClient() != nullptr && cobj->isCreatureObject()) {
										object->sendMessage(cobj->link(cell->getObjectID(), -1));
									}
								}
							} else {
								object->notifyInsert(cobj.get());
							}

						}
					}
				}
			}
		}

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	if (zone != nullptr) {
		delete _locker;

		if (object->isTangibleObject()) {
			TangibleObject* tano = object->asTangibleObject();
		   // zone->updateActiveAreas(tano);
		}
	}
	//info("Added: " + object->getDisplayedName(), true);
	//TangibleObjectImplementation::notifyObjectInsertedToChild(object, child, oldParent);

	return 0;
}

int ShipObjectImplementation::notifyObjectRemovedFromChild(SceneObject* object, SceneObject* child) {
	TangibleObjectImplementation::notifyObjectRemovedFromChild(object, child);
	//info("Removed: " + object->getDisplayedName(), true);
	/*SceneObject* parent = sceneObject->getParent();
	Zone* zone = sceneObject->getZone();

	if (!parent->isCellObject())
		return;

	if (building != parent->getParent()) {
		error("removing from wrong building object");
		return;
	}

	sceneObject->broadcastMessage(sceneObject->link((uint64)0, (uint32)0xFFFFFFFF), true, false);*/

	//parent->removeObject(sceneObject, false);


	//remove(object);

	//		building->removeNotifiedSentObject(sceneObject);


	return 0;
}

void ShipObjectImplementation::damageArmor(float damage, DeltaMessage* delta) {
	// Assume damage > total armor
	float armor0 = getCurrentArmorMap()->get(Components::ARMOR0);
	float armor1 = getCurrentArmorMap()->get(Components::ARMOR1);
	float half = damage * 0.5f;
	armor0 -= damage;
	bool hasArmor0 = armor0 != 0;
	bool hasArmor1 = armor1 != 0;
	float remaining = 0;
	armor0 -= half;

	if (armor0 < 0) {
		remaining = -armor0;
		armor0 = 0;
	}

	armor1 -= remaining + half;

	if (hasArmor0) {
		setComponentArmor(Components::ARMOR0, armor0, delta);
	}

	if (hasArmor1) {
		setComponentArmor(Components::ARMOR1, armor1, delta);
	}
}

void ShipObjectImplementation::doRecovery(int mselapsed) {
	float deltaTime = mselapsed * 0.001f;
	auto componentMap = getShipComponentMap();

	auto pilot = owner.get();
	auto notifyClient = pilot != nullptr;

	auto ship3 = notifyClient ? new DeltaMessage(getObjectID(), 'SHIP', 3) : nullptr;
	auto ship4 = notifyClient ? new DeltaMessage(getObjectID(), 'SHIP', 4) : nullptr;

	for (unsigned int i = 0; i < 20; ++i) {
		if (componentMap->get(i) == 0) {
			continue;
		}

		switch (i)
		{
			case Components::SHIELD0:
			case Components::SHIELD1: {
				float minFront = getFrontShield();
				float maxFront = getMaxFrontShield();

				if (minFront != maxFront) {
					float value = minFront + (deltaTime * getShieldRechargeRate());
					if (value > maxFront) {
						value = maxFront;
					}

					setFrontShield(value, false, ship3);
				}

				float minRear = getRearShield();
				float maxRear = getMaxRearShield();

				if (minRear != maxRear) {
					float value = minRear + (deltaTime * getShieldRechargeRate());
					if (value > maxRear) {
						value = maxRear;
					}

					setRearShield(value, false, ship3);
				}

				break;
			}

			case Components::CAPACITOR: {
				float current = getCapacitorEnergy();
				float max = getCapacitorMaxEnergy();

				if (max != current) {
					float value = current + (deltaTime * getCapacitorRechargeRate());
					if (value > max) {
						value = max;
					}

					setCapacitorEnergy(value, false, ship4);
				}

				break;
			}

			case Components::BOOSTER: {
				if (isBoosterActive()) {
					float current = getBoosterEnergy();

					if (current != 0) {
						float value = current - (deltaTime * getBoosterConsumptionRate());
						if (value < 0.f) {
							value = 0.f;
						}

						setBoosterEnergy(value, false, ship4);
					}

					if (current == 0) {
						removeComponentFlag(Components::BOOSTER, ShipComponentFlag::ACTIVE, true);

						if (pilot != nullptr) {
							pilot->sendSystemMessage("@space/space_interaction:booster_energy_depleted");
						}

						restartBooster();
					}
				} else {
					float current = getBoosterEnergy();
					float max = getBoosterMaxEnergy();

					if (max != current) {
						float value = current + (deltaTime * getBoosterRechargeRate());
						if (value > max) {
							value = max;
						}

						setBoosterEnergy(value, false, ship4);
					}
				}

				break;
			}
		}
	}

	float calculateSpeed = getActualSpeed();

	if (getCurrentSpeed() != calculateSpeed) {
		setCurrentSpeed(calculateSpeed, true);
	}

	if (notifyClient) {
		ship3->close();
		ship4->close();

		broadcastMessage(ship3, false);
		pilot->sendMessage(ship4);
	}

	scheduleRecovery();
}

void ShipObjectImplementation::scheduleRecovery() {
	if (shipRecoveryEvent != nullptr && !shipRecoveryEvent->isScheduled())
		shipRecoveryEvent->schedule(1000);
}

void ShipObjectImplementation::cancelRecovery() {
	if (shipRecoveryEvent != nullptr && shipRecoveryEvent->isScheduled())
		shipRecoveryEvent->cancel();
}

bool ShipObject::isShipObject() {
	return true;
}

bool ShipObjectImplementation::isShipObject() {
	return true;
}

void ShipObjectImplementation::addComponentFlag(uint32 slot, uint32 bit, bool notifyClient) {
	uint32 mask = getComponentOptionsMap()->get(slot);

	if (!(mask & bit)) {
		mask |= bit;
	}

	if (notifyClient) {
		DeltaMessage* message = new DeltaMessage(getObjectID(), 'SHIP', 3);

		setComponentOptions(slot, mask, message);
		message->close();

		broadcastMessage(message, true);
	}
}

void ShipObjectImplementation::removeComponentFlag(uint32 slot, uint32 bit, bool notifyClient) {
	uint32 mask = getComponentOptionsMap()->get(slot);

	if (mask & bit) {
		mask &= ~bit;
	}

	if (notifyClient) {
		DeltaMessage* message = new DeltaMessage(getObjectID(), 'SHIP', 3);

		setComponentOptions(slot, mask, message);
		message->close();

		broadcastMessage(message, true);
	}
}

void ShipObjectImplementation::restartBooster() {
	float boosterMax = getBoosterMaxSpeed();
	float deceleration = getShipDecelerationRate();
	float boostTime = 0.0f;

	if (deceleration > 0.0f) {
		boostTime = boosterMax / deceleration;
	}

	boostTime = Math::clamp(2.0f, boostTime, 10.0f);

	boostTimer.updateToCurrentTime();
	boostTimer.addMiliTime(boostTime * 1000);
}

void ShipObjectImplementation::setHyperspaceDelay() {
	int delay = HYPERSPACE_DELAY;

	ManagedReference<CreatureObject*> player = owner.get();

	if (player != nullptr && player->isPlayerCreature()) {
		PlayerObject* ghost = player->getPlayerObject();

		if (ghost != nullptr && ghost->hasAbility("space_navigator"))
			delay = NAVIGATOR_DELAY;
	}

	hyperspaceTime.updateToCurrentTime();
	hyperspaceTime.addMiliTime(delay * 1000);
}

int ShipObjectImplementation::getHyperspaceDelay() {
	Time now;
	return (now.miliDifference() - hyperspaceTime.miliDifference()) / 1000;
}

float ShipObjectImplementation::getActualSpeed() {
	auto componentMap = getShipComponentMap();
	float componentActual = 0.f;

	if (componentMap->get(Components::ENGINE) != 0) {
		float engineEfficiency = getComponentEfficiencyMap()->get(Components::ENGINE);
		float engineSpeed = getMaxSpeed();
		componentActual += engineEfficiency * engineSpeed;
	}

	if (componentMap->get(Components::BOOSTER) != 0 && isBoosterActive()) {
		float boosterEfficiency = getComponentEfficiencyMap()->get(Components::BOOSTER);
		float boosterSpeed = getBoosterMaxSpeed();
		componentActual += boosterEfficiency * boosterSpeed;
	}

	float chassisActual = 1.f;

	if (hasShipWings() && (getOptionsBitmask() & OptionBitmask::WINGS_OPEN)) {
		chassisActual -= (1.f - openWingSpeed);
	}

	if (getChassisSpeed() != 0.f) {
		float typeSpeed = getChassisSpeed();
		chassisActual -= (1.f - typeSpeed);
	}

	return componentActual * chassisActual;
}

bool ShipObjectImplementation::checkInConvoRange(SceneObject* targetObject) {
	if (targetObject == nullptr)
		return false;

	int sqDistance = getWorldPosition().squaredDistanceTo(targetObject->getWorldPosition());

	if (targetObject->isSpaceStationObject()) {
		int maxSqDistance = SPACESTATION_COMM_MAX_DISTANCE * SPACESTATION_COMM_MAX_DISTANCE;

		if (sqDistance < maxSqDistance)
			return true;
	}

	return false;
}

void ShipObjectImplementation::setFaction(unsigned int crc) {
	TangibleObjectImplementation::setFaction(crc);

	setShipFaction(Factions::factionToString(crc));
}

uint16 ShipObjectImplementation::generateUniqueID() {
	uint32 hash = UnsignedLong::hashCode(getObjectID());
	uint16 id = (uint16) (hash ^ (hash >> 16));

	return id;
}
