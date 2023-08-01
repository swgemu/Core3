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
#include "server/zone/objects/ship/components/ShipWeaponComponent.h"
#include "server/zone/objects/ship/events/ShipRecoveryEvent.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/packets/ship/ShipObjectMessage1.h"
#include "server/zone/packets/ship/ShipObjectMessage3.h"
#include "server/zone/packets/ship/ShipObjectMessage4.h"
#include "server/zone/packets/ship/ShipObjectMessage6.h"
#include "server/zone/packets/scene/SceneObjectCreateMessage.h"
#include "templates/tangible/SharedShipObjectTemplate.h"
#include "server/zone/objects/ship/ShipChassisData.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "templates/faction/Factions.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/packets/tangible/UpdatePVPStatusMessage.h"
#include "server/zone/packets/scene/SceneObjectDestroyMessage.h"
#include "server/zone/objects/intangible/tasks/StoreShipTask.h"

void ShipObjectImplementation::initializeTransientMembers() {
	hyperspacing = false;

	if (shipRecoveryEvent == nullptr) {
		shipRecoveryEvent = new ShipRecoveryEvent(asShipObject());
	}

	TangibleObjectImplementation::initializeTransientMembers();
}

void ShipObjectImplementation::notifyLoadFromDatabase() {
	auto owner = getOwner().get();

	if (owner != nullptr && getSpaceZone() != nullptr) {
		auto zoneServer = getZoneServer();

		if (zoneServer != nullptr) {
			ManagedReference<SceneObject*> deviceSceneO = zoneServer->getObject(getControlDeviceID()).get();

			if (deviceSceneO != nullptr && deviceSceneO->isShipControlDevice()) {
				ShipControlDevice* shipDevice = cast<ShipControlDevice*>(deviceSceneO.get());

				if (shipDevice != nullptr) {
					StoreShipTask* task = new StoreShipTask(owner, shipDevice, shipDevice->getStoredZoneName(), shipDevice->getStoredPosition(true));

					if (task != nullptr)
						task->schedule(1500);
				}
			}
		}
	}

	TangibleObjectImplementation::notifyLoadFromDatabase();
}

void ShipObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);
}

void ShipObjectImplementation::loadTemplateData(SharedShipObjectTemplate* ssot) {
	if (ssot == nullptr) {
		return;
	}

	setShipName(ssot->getShipName());
	setShipType(ssot->getShipType(), false);
	setShipNameCRC(chassisDataName.hashCode(), false);
	setUniqueID(getUniqueID(), false);

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

	setChassisCategory(ssot->getChassisCategory());
	setChassisLevel(ssot->getChassisLevel());

	auto values = ssot->getAttributeMap();

	for (int i = 0; i < values.size(); ++i) {
		auto attribute = values.elementAt(i).getKey();
		auto value = values.elementAt(i).getValue();

		if (attribute == "slideDamp") {
			setSlipRate(value, false);
		} else if (attribute == "engineAccel") {
			setEngineAccelerationRate(value, false);
			setActualAccelerationRate(value, false);
		} else if (attribute == "engineDecel") {
			setEngineDecelerationRate(value, false);
			setActualDecelerationRate(value, false);
		} else if (attribute == "engineYawAccel") {
			setEngineYawAccelerationRate(value * Math::DEG2RAD, false);
			setActualYawAccelerationRate(value * Math::DEG2RAD, false);
		} else if (attribute == "enginePitchAccel") {
			setEnginePitchAccelerationRate(value * Math::DEG2RAD, false);
			setActualPitchAccelerationRate(value * Math::DEG2RAD, false);
		} else if (attribute == "engineRollAccel") {
			setEngineRollAccelerationRate(value * Math::DEG2RAD, false);
			setActualRollAccelerationRate(value * Math::DEG2RAD, false);
		} else if (attribute == "maxSpeed") {
			setChassisSpeed(value, false);
		}
	}

	totalCellNumber = ssot->getTotalCellNumber();

	auto portalLayout = ssot->getPortalLayout();

	if (portalLayout != nullptr)
		totalCellNumber = portalLayout->getFloorMeshNumber();

	//info(true) << getDisplayedName() << " loaded a total of " << totalCellNumber << " cells.";

	auto chassisData = ShipManager::instance()->getChassisData(ssot->getShipName());

	if (chassisData != nullptr) {
		for (uint32 slot = 0; slot <= Components::FIGHTERSLOTMAX; slot++) {
			auto slotData = chassisData->getComponentSlotData(slot);
			setComponentTargetable(slot, slotData ? slotData->isTargetable() : false);
		}
	}

	auto appearance = ssot->getAppearanceTemplate();

	if (appearance != nullptr) {
		auto volume = appearance->getBoundingVolume();

		if (volume != nullptr) {
			const auto& sphere = volume->getBoundingSphere();
			boundingRadius = sphere.getCenter().length() + sphere.getRadius();
		}
	}
}

void ShipObjectImplementation::sendTo(SceneObject* player, bool doClose, bool forceLoadContainer) {
	BaseMessage* destroy = new SceneObjectDestroyMessage(asSceneObject());
	player->sendMessage(destroy);

	BaseMessage* msg = new SceneObjectCreateMessage(asSceneObject());
	player->sendMessage(msg);

	link(player, containmentType);

	auto pilot = getPilot();

	if (pilot != nullptr) {
		player->addInRangeObject(pilot, true);
	}

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

void ShipObjectImplementation::setShipName(const String& name, bool notifyClient) {
	chassisDataName = name;
	shipNameCRC.update(name.hashCode(), false);
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
	for (int i = 0; i < values->getTotalExperimentalAttributes(); ++i) {
		String attribute;
		float min;
		float max;
		float current;

		attribute = values->getAttribute(i);
		min = values->getMinValue(attribute);
		max = values->getMaxValue(attribute);
		current = values->getCurrentValue(attribute);

		//info("Attribute: " + attribute + " min: " + String::valueOf(min) + " max: " + String::valueOf(max) + " current: " + String::valueOf(current), true);
	}

	TangibleObjectImplementation::updateCraftingValues(values, firstUpdate);
}

uint16 ShipObjectImplementation::getUniqueID() {
	uint32 hash = UnsignedLong::hashCode(getObjectID());
	uint16 id = (uint16) (hash ^ (hash >> 16));

	//info("uniqueId: 0x" + String::hexvalueOf(id), true);

	return id;
}

void ShipObjectImplementation::sendBaselinesTo(SceneObject* player) {
	bool sendSelf = player == owner.get() || player->isASubChildOf(asShipObject());

	if (sendSelf) {
		ShipObjectMessage1* ship1 = new ShipObjectMessage1(_this.getReferenceUnsafeStaticCast());
		player->sendMessage(ship1);
	}

	ShipObjectMessage3* ship3 = new ShipObjectMessage3(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(ship3);

	if (sendSelf) {
		ShipObjectMessage4* ship4 = new ShipObjectMessage4(_this.getReferenceUnsafeStaticCast());
		player->sendMessage(ship4);
	}

	ShipObjectMessage6* ship6 = new ShipObjectMessage6(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(ship6);

	if (player->isPlayerCreature()) {
		auto creature = player->asCreatureObject();

		if (creature != nullptr) {
			sendPvpStatusTo(creature);
		}
	}
}

ShipObject* ShipObjectImplementation::asShipObject() {
	return _this.getReferenceUnsafeStaticCast();
}

ShipObject* ShipObject::asShipObject() {
	return this;
}

void ShipObjectImplementation::installAmmo(CreatureObject* player, SceneObject* sceno, int slot, bool notifyClient) {
	if (sceno == nullptr) {
		return;
	}

	auto component = getComponentObject(slot);
	if (component == nullptr) {
		return;
	}

	auto weapon = dynamic_cast<ShipWeaponComponent*>(component);
	if (weapon == nullptr) {
		return;
	}

	auto ammo = dynamic_cast<Component*>(sceno);
	if (ammo == nullptr) {
		return;
	}

	Locker lock(ammo);
	ammo->destroyObjectFromWorld(true);

	weapon->installAmmo(player, asShipObject(), ammo, slot, notifyClient);

	ammo->destroyObjectFromDatabase(true);
}

void ShipObjectImplementation::uninstallAmmo(CreatureObject* player, int slot, bool notifyClient) {
	auto component = getComponentObject(slot);
	if (component == nullptr) {
		return;
	}

	auto weapon = dynamic_cast<ShipWeaponComponent*>(component);
	if (weapon == nullptr) {
		return;
	}

	weapon->uninstallAmmo(player, asShipObject(), slot, notifyClient);
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
	shipComponent->destroyObjectFromWorld(true);

	components.put(slot, shipComponent);

	shipComponent->install(player, asShipObject(), slot, notifyClient);
}

void ShipObjectImplementation::uninstall(CreatureObject* player, int slot, bool notifyClient) {
	ManagedReference<ShipComponent*> shipComponent = getComponentObject(slot);
	if (shipComponent == nullptr) {
		return;
	}

	Locker lock(shipComponent);
	shipComponent->destroyObjectFromWorld(true);

	if (player != nullptr) {
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		if (inventory == nullptr || !inventory->transferObject(shipComponent, -1, notifyClient, true)) {
			return;
		}

		if (notifyClient) {
			shipComponent->sendTo(player, true);
		}
	}

	shipComponent->uninstall(player, asShipObject(), slot, notifyClient);

	components.drop(slot);
}

void ShipObjectImplementation::notifyObjectInsertedToZone(SceneObject* object) {
	auto closeObjectsVector = getCloseObjects();
	Vector<TreeEntry*> closeObjects(closeObjectsVector->size(), 10);
	closeObjectsVector->safeCopyReceiversTo(closeObjects, CloseObjectsVector::CREOTYPE);

	for (int i = 0; i < closeObjects.size(); ++i) {
		SceneObject* obj = static_cast<SceneObject*>(closeObjects.get(i));

		if (obj->isCreatureObject()) {
			if (obj->getRootParent() != _this.getReferenceUnsafe()) {
				if (object->getCloseObjects() != nullptr)
					object->addInRangeObject(obj, false);
				else
					object->notifyInsert(obj);

				if (obj->getCloseObjects() != nullptr)
					obj->addInRangeObject(object, false);
				else
					obj->notifyInsert(object);
			}
		}
	}

	notifyInsert(object);

	if (object->getCloseObjects() != nullptr)
		object->addInRangeObject(asShipObject(), false);

	addInRangeObject(object, false);

	Zone* zone = getZone();

	if (zone != nullptr && zone->isSpaceZone()) {
		TangibleObject* tano = object->asTangibleObject();

		if (tano != nullptr) {
			//zone->updateActiveAreas(tano);
		}

		object->notifyInsertToZone(zone);
	}

	//this->sendTo(object, true);
}

int ShipObjectImplementation::notifyObjectInsertedToChild(SceneObject* object, SceneObject* child, SceneObject* oldParent) {
	Zone* zone = getZone();

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
					notifyObjectInsertedToZone(object);
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

	// info(true) << getDisplayedName() << " notifyObjectInsertedToChild: " << object->getDisplayedName();

	TangibleObjectImplementation::notifyObjectInsertedToChild(object, child, oldParent);

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

void ShipObjectImplementation::doRecovery(int mselapsed) {
	float deltaTime = mselapsed * 0.001f;

	auto pilot = owner.get();
	auto deltaVector = getDeltaVector();
	auto componentMap = getShipComponentMap();

	for (int i = 0; i < componentMap->size(); ++i) {
		uint32 slot = componentMap->getKeyAt(i);
		uint32 crc = componentMap->getValueAt(i);

		if (crc == 0) {
			continue;
		}

		switch (slot) {
			case Components::SHIELD0:
			case Components::SHIELD1: {
				float minFront = getFrontShield();
				float maxFront = getMaxFrontShield();

				if (minFront != maxFront) {
					float value = minFront + (deltaTime * getShieldRechargeRate());
					value = Math::min(value, maxFront);
					setFrontShield(value, false, nullptr, deltaVector);
				}

				float minRear = getRearShield();
				float maxRear = getMaxRearShield();

				if (minRear != maxRear) {
					float value = minRear + (deltaTime * getShieldRechargeRate());
					value = Math::min(value, maxRear);
					setRearShield(value, false, nullptr, deltaVector);
				}

				break;
			}

			case Components::CAPACITOR: {
				float minCap = getCapacitorEnergy();
				float maxCap = getCapacitorMaxEnergy();

				if (maxCap != minCap) {
					float value = minCap + (deltaTime * getCapacitorRechargeRate());
					value = Math::min(value, maxCap);
					setCapacitorEnergy(value, false, nullptr, deltaVector);
				}

				break;
			}

			case Components::BOOSTER: {
				if (isBoosterActive()) {
					float boostEnergy = getBoosterEnergy();
					float boostLimit = getBoosterConsumptionRate() * deltaTime;

					if (boostEnergy >= boostLimit) {
						float value = boostEnergy - boostLimit;
						setBoosterEnergy(value, false, nullptr, deltaVector);
					} else {
						removeComponentFlag(Components::BOOSTER, ShipComponentFlag::DISABLED, true);
						restartBooster();

						if (pilot != nullptr) {
							pilot->sendSystemMessage("@space/space_interaction:booster_energy_depleted");
						}
					}
				} else {
					float maxBoost = getBoosterMaxEnergy();
					float minBoost = getBoosterEnergy();

					if (maxBoost != minBoost) {
						float value = minBoost + (deltaTime * getBoosterRechargeRate());
						value = Math::min(value, maxBoost);
						setBoosterEnergy(value, false, nullptr, deltaVector);
					}
				}

				break;
			}
		}
	}

	float actualSpeed = getActualSpeed();

	if (getActualMaxSpeed() != actualSpeed) {
		setActualMaxSpeed(actualSpeed, false, nullptr, deltaVector);
	}

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(asShipObject(), pilot);
	}

	auto targetVector = getTargetVector();

	if (targetVector != nullptr) {
		targetVector->update();
	}

	scheduleRecovery();
}

void ShipObjectImplementation::repairShip(float value) {
	float repair = Math::clamp(0.f, value, 1.f);
	if (repair == 0.f) {
		return;
	}

	auto pilot = owner.get();
	auto deltaVector = getDeltaVector();

	float maxChassis = getChassisMaxHealth();
	float oldChassis = getChassisCurrentHealth();
	float newChassis = ((maxChassis - oldChassis) * repair) + oldChassis;

	if (oldChassis != newChassis) {
		setCurrentChassisHealth(newChassis, false, nullptr, deltaVector);
	}

	uint8 command = DeltaMapCommands::SET;
	auto componentMap = getShipComponentMap();

	for (int i = 0; i < componentMap->size(); ++i) {
		uint32 slot = componentMap->getKeyAt(i);
		uint32 crc = componentMap->getValueAt(i);

		if (crc == 0) {
			continue;
		}

		int flags = getComponentOptionsMap()->get(slot);

		if (flags & ShipComponentFlag::DEMOLISHED) {
			flags &= ~ShipComponentFlag::DEMOLISHED;
		}

		if (flags & ShipComponentFlag::DISABLED) {
			flags &= ~ShipComponentFlag::DISABLED;
		}

		if (flags != getComponentOptionsMap()->get(slot)) {
			setComponentOptions(slot, flags, nullptr, command,  deltaVector);
		}

		float maxArmor = getMaxArmorMap()->get(slot);
		float oldArmor = getCurrentArmorMap()->get(slot);
		float newArmor = ((maxArmor - oldArmor) * repair) + oldArmor;

		if (newArmor != oldArmor) {
			setComponentArmor(slot, newArmor, nullptr, command, deltaVector);
		}

		float maxHp = getMaxHitpointsMap()->get(slot);
		float oldHp = getCurrentHitpointsMap()->get(slot);
		float newHp = ((maxHp - oldHp) * repair) + oldHp;

		if (newHp != oldHp) {
			setComponentHitpoints(slot, newHp, nullptr, command, deltaVector);
		}

		switch (slot) {
			case Components::SHIELD0:
			case Components::SHIELD1: {
				float maxShieldFront = getMaxFrontShield();
				float minShieldFront = getFrontShield();
				float newShieldFront = ((maxShieldFront - minShieldFront) * repair) + minShieldFront;

				if (newShieldFront != minShieldFront) {
					setFrontShield(newShieldFront, false, nullptr, deltaVector);
				}

				float maxShieldRear = getMaxRearShield();
				float minShieldRear = getRearShield();
				float newShieldRear = ((maxShieldRear - minShieldRear) * repair) + minShieldRear;

				if (newShieldRear != minShieldRear) {
					setRearShield(newShieldRear, false, nullptr, deltaVector);
				}

				break;
			}

			case Components::CAPACITOR: {
				float maxCap = getCapacitorMaxEnergy();
				float minCap = getCapacitorEnergy();
				float newCap = ((maxCap - minCap) * repair) + minCap;

				if (newCap != minCap) {
					setCapacitorEnergy(newCap, false, nullptr, deltaVector);
				}

				break;
			}

			case Components::BOOSTER: {
				float maxBoost = getBoosterMaxEnergy();
				float minBoost = getBoosterEnergy();
				float newBoost = ((maxBoost - minBoost) * repair) + minBoost;

				if (newBoost != minBoost) {
					setBoosterEnergy(newBoost, false, nullptr, deltaVector);
				}

				break;
			}
		}
	}

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(asShipObject(), pilot);
	}
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
	if (slot == -1)
		return;

	ShipComponent* component = getComponentObject(slot);

	if (component == nullptr)
		return;

	Locker lock(component);

	if (notifyClient) {
		DeltaMessage* message = new DeltaMessage(getObjectID(), 'SHIP', 3);

		setComponentOptions(slot, bit, message);
		message->close();

		broadcastMessage(message, true);
	}
}

void ShipObjectImplementation::removeComponentFlag(uint32 slot, uint32 bit, bool notifyClient) {
	if (slot == -1)
		return;

	ShipComponent* component = getComponentObject(slot);

	if (component == nullptr)
		return;

	Locker lock(component);

	if (notifyClient) {
		DeltaMessage* message = new DeltaMessage(getObjectID(), 'SHIP', 3);

		setComponentOptions(slot, 0, message);
		message->close();

		broadcastMessage(message, true);
	}
}

void ShipObjectImplementation::restartBooster() {
	float boosterMax = getBoosterMaxSpeed();
	float deceleration = getActualDecelerationRate();
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
	const auto componentMap = getShipComponentMap();

	float componentActual = 0.f;

	if (componentMap->get(Components::ENGINE) != 0) {
		float efficiency = getComponentEfficiencyMap()->get(Components::ENGINE);
		float condition = getComponentCondition(Components::ENGINE);

		componentActual += engineMaxSpeed * efficiency * condition;
	}

	if (componentMap->get(Components::BOOSTER) != 0 && isBoosterActive()) {
		float efficiency = getComponentEfficiencyMap()->get(Components::BOOSTER);
		float condition = getComponentCondition(Components::BOOSTER);

		componentActual += boosterMaxSpeed * efficiency * condition;
	}

	float chassisActual = 1.f;

	if (chassisSpeed != 0) {
		chassisActual = chassisSpeed;
	}

	if (hasShipWings() && (getOptionsBitmask() & OptionBitmask::WINGS_OPEN)) {
		const auto chassisData = ShipManager::instance()->getChassisData(getShipName());

		if (chassisData != nullptr) {
			chassisActual *= chassisData->getWingOpenSpeed();
		}
	}

	return componentActual * chassisActual;
}

bool ShipObjectImplementation::checkInConvoRange(SceneObject* targetObject) {
	if (targetObject == nullptr)
		return false;

	int sqDistance = getWorldPosition().squaredDistanceTo(targetObject->getWorldPosition());

	if (targetObject->isSpaceStationObject()) {
		return sqDistance <= (SPACESTATION_COMM_MAX_DISTANCE * SPACESTATION_COMM_MAX_DISTANCE);
	}

	return sqDistance <= (COMM_MAX_DISTANCE * COMM_MAX_DISTANCE);
}

float ShipObjectImplementation::calculateCurrentMass() {
	float currentMass = 0;

	for (int i = 0; i < componentMass.size(); ++i) {
		auto value = componentMass.getValueAt(i);

		if (value > 0.f) {
			currentMass += value;
		}
	}

	return currentMass;
}

float ShipObjectImplementation::calculateCurrentEnergyCost() {
	float energyCost = 0;

	for (int i = 0; i < componentEnergyCost.size(); ++i) {
		auto value = componentEnergyCost.getValueAt(i);

		if (value > 0.f) {
			energyCost += value;
		}
	}

	return energyCost;
}

void ShipObjectImplementation::setShipFaction(uint32 value, bool notifyClient) {
	TangibleObjectImplementation::setFaction(value);
	String faction = "";

	if (value == Factions::FACTIONREBEL) {
		faction = "rebel";
	} else if (value == Factions::FACTIONIMPERIAL) {
		faction = "imperial";
	}

	setShipFaction(faction, notifyClient);
}

void ShipObjectImplementation::sendPvpStatusTo(CreatureObject* player) {
	CreatureObject* pilot = owner.get();

	uint32 pvpStatus = 0u;
	bool attackable = false;
	bool aggressive = false;
	int futureStatus = 0;
	int factionStatus = 0;

	if (pilot != nullptr) {
		pvpStatus = pilot->getPvpStatusBitmask();
		attackable = pilot->isAttackableBy(player);
		aggressive = pilot->isAggressiveTo(player);
		futureStatus = pilot->getFutureFactionStatus();
		factionStatus = pilot->getFactionStatus();
	} else {
		pvpStatus = getPvpStatusBitmask();
		attackable = isAttackableBy(player);
		aggressive = isAggressiveTo(player);
		futureStatus = getFutureFactionStatus();
		factionStatus = getFactionStatus();
	}

	if (attackable && !(pvpStatus & CreatureFlag::ATTACKABLE)) {
		pvpStatus |= CreatureFlag::ATTACKABLE;
	} else if (!attackable && (pvpStatus & CreatureFlag::ATTACKABLE)) {
		pvpStatus &= ~CreatureFlag::ATTACKABLE;
	}

	if (aggressive && !(pvpStatus & CreatureFlag::AGGRESSIVE)) {
		pvpStatus |= CreatureFlag::AGGRESSIVE;
	} else if (!aggressive && (pvpStatus & CreatureFlag::AGGRESSIVE)) {
		pvpStatus &= ~CreatureFlag::AGGRESSIVE;
	}

	if (aggressive && !(pvpStatus & CreatureFlag::ENEMY)) {
		pvpStatus |= CreatureFlag::ENEMY;
	} else if (!aggressive && (pvpStatus & CreatureFlag::ENEMY)) {
		pvpStatus &= ~CreatureFlag::ENEMY;
	}

	if (factionStatus == FactionStatus::COVERT && futureStatus == FactionStatus::OVERT) {
		pvpStatus |= CreatureFlag::WILLBEDECLARED;
	} else if (factionStatus == FactionStatus::OVERT && futureStatus == FactionStatus::COVERT) {
		pvpStatus |= CreatureFlag::WASDECLARED;
	}

	if (pilot != player && (pvpStatus & CreatureFlag::TEF)) {
		pvpStatus &= ~CreatureFlag::TEF;
	}

	BaseMessage* pvp = new UpdatePVPStatusMessage(asShipObject(), player, pvpStatus);
	player->sendMessage(pvp);
}

bool ShipObjectImplementation::isAttackableBy(TangibleObject* object) {
	auto optionsBit = getOptionsBitmask();

	if ((optionsBit & OptionBitmask::DESTROYING) || (optionsBit & OptionBitmask::INVULNERABLE)) {
		return false;
	}

	int thisFaction = getFaction();
	int objectFaction = object->getFaction();

	if (thisFaction == 0 && objectFaction > 0)
		return false;

	return faction != objectFaction;
}

bool ShipObjectImplementation::isAggressiveTo(TangibleObject* object) {
	return object->isAttackableBy(asShipObject()) && faction != Factions::FACTIONNEUTRAL;
}

ShipDeltaVector* ShipObjectImplementation::getDeltaVector() {
	if (shipDeltaVector == nullptr) {
		shipDeltaVector = new ShipDeltaVector(asShipObject(), getOwner().get());
	}

	shipDeltaVector->reset(getOwner().get());

	return shipDeltaVector.get();
}

ShipTargetVector* ShipObjectImplementation::getTargetVector() {
	if (shipTargetVector == nullptr) {
		shipTargetVector = new ShipTargetVector(asShipObject());
	}

	return shipTargetVector.get();
}

void ShipObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	auto pilot = owner.get();

	for (uint32 slot = 0; slot <= Components::FIGHTERSLOTMAX; ++slot) {
		auto component = components.get(slot);
		if (component == nullptr) {
			continue;
		}

		if (pilot != nullptr && !destroyContainedObjects) {
			uninstall(pilot, slot, true);
			component = components.get(slot);
		}

		if (component != nullptr) {
			Locker cLock(component);
			component->destroyObjectFromDatabase(true);
		}
	}

	TangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

void ShipObjectImplementation::setSyncStamp(uint32 value) {
	syncTime = System::getMiliTime();
	movementCounter = value;
}

uint32 ShipObjectImplementation::getSyncStamp() {
	long deltaTime = System::getMiliTime() - syncTime;
	return movementCounter + deltaTime;
}

void ShipObjectImplementation::updateZone(bool lightUpdate, bool sendPackets) {
	auto pilot = getPilot();

	if (pilot != nullptr) {
		pilot->setPosition(getPositionX(),getPositionZ(),getPositionY());
		pilot->setMovementCounter(movementCounter);
	}

	SceneObjectImplementation::updateZone(lightUpdate, sendPackets);
}

CreatureObject* ShipObjectImplementation::getPilot() {
	auto chair = pilotChair.get();

	if (chair != nullptr) {
		return chair->getSlottedObject("ship_pilot_pob").castTo<CreatureObject*>();
	}

	return getSlottedObject("ship_pilot").castTo<CreatureObject*>();
}

void ShipObjectImplementation::setRotationMatrix(const Quaternion& value) {
	rotationMatrix.setRotationMatrix(value.toMatrix3());
}

float ShipObjectImplementation::getComponentCondition(uint32 slot) {
	float healthMin = getCurrentHitpointsMap()->get(slot);
	float healthMax = getMaxHitpointsMap()->get(slot);

	if (healthMin == 0.f || healthMax == 0.f) {
		return 0.f;
	}

	return healthMin / healthMax;
}

void ShipObjectImplementation::updateLastDamageReceived() {
	lastDamageReceived.updateToCurrentTime();
}

uint64 ShipObjectImplementation::getLastDamageReceivedMili() {
	return lastDamageReceived.getMiliTime();
}
