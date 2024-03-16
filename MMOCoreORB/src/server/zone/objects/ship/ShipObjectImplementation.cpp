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
#include "server/zone/packets/object/BeginHyperspace.h"
#include "server/zone/packets/object/OrientForHyperspace.h"
#include "server/zone/packets/scene/SceneObjectCreateMessage.h"
#include "templates/tangible/ship/SharedShipObjectTemplate.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "templates/faction/Factions.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/packets/tangible/UpdatePVPStatusMessage.h"
#include "server/zone/packets/scene/SceneObjectDestroyMessage.h"
#include "server/zone/objects/intangible/tasks/StoreShipTask.h"

// #define DEBUG_COV

void ShipObjectImplementation::initializeTransientMembers() {
	hyperspacing = false;

	if (shipRecoveryEvent == nullptr) {
		shipRecoveryEvent = new ShipRecoveryEvent(asShipObject());
	}

	TangibleObjectImplementation::initializeTransientMembers();
}

void ShipObjectImplementation::notifyLoadFromDatabase() {
	TangibleObjectImplementation::notifyLoadFromDatabase();
}

void ShipObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);
}

void ShipObjectImplementation::loadTemplateData(SharedShipObjectTemplate* ssot) {
	if (ssot == nullptr) {
		return;
	}

	chassisDataName = ssot->getShipName();
	setShipNameCRC(chassisDataName.hashCode(), false);

	setShipName("", false);

	setShipType(ssot->getShipType(), false);
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

		if (attribute == "speedRotationFactorMin") {
			setSpeedRotationFactorMin(value);
		} else if (attribute == "speedRotationFactorOptimal") {
			setSpeedRotationFactorOptimal(value);
		} else if (attribute == "speedRotationFactorMax") {
			setSpeedRotationFactorMax(value);
		} else if (attribute == "slideDamp") {
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
	//info(true) << "ShipObjectImplementation::sendTo - Ship Location: " << getWorldPosition().toString() << " sending to: " << player->getDisplayedName() << " Player Loc: " << player->getWorldPosition().toString()
	//	<< " Containment Type: " << player->getContainmentType();

	TangibleObjectImplementation::sendTo(player, doClose, forceLoadContainer);
}

void ShipObjectImplementation::setShipName(const String& name, bool notifyClient) {
	shipName = name;

	if (notifyClient) {
		ShipObjectMessage3* ship3 = new ShipObjectMessage3(_this.getReferenceUnsafeStaticCast());
		broadcastMessage(ship3, true, false);
	}
}

String ShipObjectImplementation::getShipName() {
	if (shipName.isEmpty()) {
		return getDisplayedName();
	}

	return shipName;
}

String ShipObjectImplementation::getShipLaunchedName() {
	UnicodeString returnName = "";

	auto owner = getOwner().get();

	if (owner != nullptr) {
		returnName = owner->getDisplayedName();

		if (!shipName.isEmpty())
			returnName = returnName + " (" + shipName + ")";

		auto ghost = owner->getPlayerObject();

		if (ghost != nullptr && ghost->isPrivileged()) {
			UnicodeString tag = PermissionLevelList::instance()->getPermissionTag(ghost->getAdminLevel());
			returnName = returnName + " \\#ffff00[" + tag + "]\\#.";
		}
	}

	return returnName.toString();
}

void ShipObjectImplementation::sendSlottedObjectsTo(SceneObject* player) {
	// info(true) << "ShipObjectImplementation::sendSlottedObjectsTo - sending to: " << player->getDisplayedName();

	VectorMap<String, ManagedReference<SceneObject* > > slotted;
	getSlottedObjects(slotted);

	SortedVector<SceneObject*> objects(getSlottedObjectsSize(), getSlottedObjectsSize());
	objects.setNoDuplicateInsertPlan();

	try {
		for (int i = 0; i < slotted.size(); ++i) {
			Reference<SceneObject*> object = getSlottedObject(i);

			int arrangementSize = object->getArrangementDescriptorSize();

			bool sendWithoutContents = false;

			if (arrangementSize > 0) {
				const Vector<String>* descriptors = object->getArrangementDescriptor(0);

				if (descriptors->size() > 0) {
					const String& childArrangement = descriptors->get(0);

					if (((childArrangement == "bank") || (childArrangement == "inventory") || (childArrangement == "datapad") || (childArrangement == "mission_bag"))) {
						sendWithoutContents = true;
					}
				}
			}

			if (objects.put(object) != -1) {
				if (object->isInOctree()) {
					notifyInsert(object);
				} else if (sendWithoutContents) {
					object->sendWithoutContainerObjectsTo(player);
				} else {
					object->sendTo(player, true, false);
				}
			}
		}
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
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
	// info(true) << "ShipObjectImplementation::sendBaselinesTo - sending to: " << player->getDisplayedName();

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

	Locker lock(ammo, asShipObject());

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

	Locker lock(weapon, asShipObject());

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

	Locker lock(shipComponent, asShipObject());

	shipComponent->destroyObjectFromWorld(true);

	components.put(slot, shipComponent);

	shipComponent->install(player, asShipObject(), slot, notifyClient);
}

void ShipObjectImplementation::uninstall(CreatureObject* player, int slot, bool notifyClient) {
	// We do not want to continue with uninstallation if the player giving the command is null
	if (player == nullptr)
		return;

	ManagedReference<ShipComponent*> shipComponent = getComponentObject(slot);

	if (shipComponent == nullptr) {
		return;
	}

	Locker lock(shipComponent, asShipObject());

	shipComponent->destroyObjectFromWorld(true);

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory == nullptr || !inventory->transferObject(shipComponent, -1, notifyClient, true)) {
		return;
	}

	shipComponent->uninstall(player, asShipObject(), slot, notifyClient);

	components.drop(slot);

	if (notifyClient) {
		shipComponent->sendTo(player, true);
	}

}

void ShipObjectImplementation::notifyObjectInsertedToZone(SceneObject* object) {
	// info(true) << getDisplayedName() << " ShipObjectImplementation --- notifyObjectInsertedToZone - Object " << object->getDisplayedName();

	auto closeObjectsVector = getCloseObjects();
	SortedVector<TreeEntry*> closeObjects(200, 50);

	if (closeObjectsVector != nullptr) {
		closeObjectsVector->safeCopyTo(closeObjects);
	} else {
		auto zone = getZone();

		if (zone != nullptr)
			zone->getInRangeObjects(getWorldPositionX(), getWorldPositionZ(), getWorldPositionY(), zone->getZoneObjectRange(), &closeObjects, false);
	}

	for (int i = 0; i < closeObjects.size(); ++i) {
		SceneObject* obj = static_cast<SceneObject*>(closeObjects.get(i));

		if (obj == nullptr || !obj->isCreatureObject())
			continue;

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

	notifyInsert(object);

	if (object->getCloseObjects() != nullptr)
		object->addInRangeObject(asShipObject(), false);

	addInRangeObject(object, false);

	Zone* zone = getZone();

	if (zone != nullptr) {
		object->notifyInsertToZone(zone);
	}
}

void ShipObjectImplementation::notifyInsert(TreeEntry* object) {
	auto sceneO = static_cast<SceneObject*>(object);
	uint64 scnoID = sceneO->getObjectID();

#ifdef DEBUG_COV
	info(true) << "Ship: " << getDisplayedName() << " -- ShipObjectImplementation::notifyInsert -- Object inserted: " << sceneO->getDisplayedName() << " ID: " << scnoID << " Players on Board Size: " << playersOnBoard.size();
#endif // DEBUG_COV

	try {
		for (int i = 0; i < playersOnBoard.size(); ++i) {
			auto shipMember = playersOnBoard.get(i);

			if (shipMember == nullptr)
				continue;

			// Update the Ship member
			if (shipMember->getCloseObjects() != nullptr) {
				shipMember->addInRangeObject(sceneO, false);
			} else {
				shipMember->notifyInsert(sceneO);
			}

			if (shipMember != sceneO) {
				shipMember->sendTo(sceneO, true, false);

				// Update the Object with the ship member
				if (sceneO->getCloseObjects() != nullptr) {
					sceneO->addInRangeObject(shipMember, false);
				} else {
					sceneO->notifyInsert(shipMember);
				}

				if (sceneO->getParent() != nullptr) {
					sceneO->sendTo(shipMember, true, false);
				}
			}
		}
	} catch (Exception& e) {
		warning(e.getMessage());
		e.printStackTrace();
	}
}

void ShipObjectImplementation::notifyDissapear(TreeEntry* object) {
	TangibleObjectImplementation::notifyDissapear(object);

	auto sceneO = static_cast<SceneObject*>(object);
	uint64 scnoID = sceneO->getObjectID();

#ifdef DEBUG_COV
	info(true) << "ShipObjectImplementation::notifyDissapear -- Object removed: " << sceneO->getDisplayedName() << " ID: " << scnoID;
#endif // DEBUG_COV

	try {
		for (int i = 0; i < playersOnBoard.size(); ++i) {
			auto shipMember = playersOnBoard.get(i);

			if (shipMember == nullptr)
				continue;

			if (shipMember->getCloseObjects() != nullptr)
				shipMember->removeInRangeObject(object);
			else
				shipMember->notifyDissapear(object);

			if (object->getCloseObjects() != nullptr)
				object->removeInRangeObject(shipMember);
			else
				object->notifyDissapear(shipMember);
		}
	} catch (const Exception& exception) {
		warning("could not remove all container objects in ShipObjectImplementation::notifyDissapear");

		exception.printStackTrace();
	}
}

void ShipObjectImplementation::sendDestroyTo(SceneObject* player) {
	SceneObjectImplementation::sendDestroyTo(player);
}

void ShipObjectImplementation::notifyInsertToZone(Zone* zone) {
	StringBuffer newName;
	newName << getDisplayedName() << " - " << zone->getZoneName();

	setLoggingName(newName.toString());

	scheduleRecovery();

	TangibleObjectImplementation::notifyInsertToZone(zone);
}

void ShipObjectImplementation::updateZone(bool lightUpdate, bool sendPackets) {
	updatePlayersInShip(lightUpdate, sendPackets);

	SceneObjectImplementation::updateZone(lightUpdate, sendPackets);
}

void ShipObjectImplementation::updatePlayersInShip(bool lightUpdate, bool sendPackets) {
	if (getLocalZone() == nullptr || isHyperspacing())
		return;

	// info(true) << "ShipObjectImplementation::updatePlayersInShip";

	for (int i = 0; i < playersOnBoard.size(); ++i) {
		auto shipMember = playersOnBoard.get(i);

		if (shipMember == nullptr)
			continue;

		Locker clock(shipMember, asShipObject());

		shipMember->setPosition(getPositionX(), getPositionZ(), getPositionY());

		auto parent = shipMember->getParent().get();

		if (parent != nullptr)
			shipMember->updateZoneWithParent(parent, lightUpdate, sendPackets);
	}
}

int ShipObjectImplementation::notifyObjectInsertedToChild(SceneObject* object, SceneObject* child, SceneObject* oldParent) {
	Zone* zone = getZone();

	Locker* _locker = nullptr;

	if (zone != nullptr)
		_locker = new Locker(zone);

	// info(true) << getDisplayedName() << " ShipObjectImplementation::notifyObjectInsertedToChild -- object inserted: " << object->getDisplayedName() << " ID: " << object->getObjectID();

	try {
		if (object->getCloseObjects() != nullptr)
			object->addInRangeObject(object, false);

		if (child->isCellObject()) {
			bool runInRange = true;

			if (oldParent == nullptr || !oldParent->isCellObject() || oldParent == child) {

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
	}

	TangibleObjectImplementation::notifyObjectInsertedToChild(object, child, oldParent);

	return 0;
}

int ShipObjectImplementation::notifyObjectRemovedFromChild(SceneObject* object, SceneObject* child) {
	TangibleObjectImplementation::notifyObjectRemovedFromChild(object, child);

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

float ShipObjectImplementation::getTotalShipDamage() {
	float damage = 0.f;

	float maxChassis = getChassisMaxHealth();
	float currentChassis = getChassisCurrentHealth();

	damage += maxChassis - currentChassis;

	auto componentMap = getShipComponentMap();

	for (int i = 0; i < componentMap->size(); ++i) {
		uint32 slot = componentMap->getKeyAt(i);
		uint32 crc = componentMap->getValueAt(i);

		if (crc == 0) {
			continue;
		}

		float maxArmor = getMaxArmorMap()->get(slot);
		float currentArmor = getCurrentArmorMap()->get(slot);

		damage += maxArmor - currentArmor;

		float maxHitpoints = getMaxHitpointsMap()->get(slot);
		float currentHitpoints = getCurrentHitpointsMap()->get(slot);

		damage += maxHitpoints - currentHitpoints;

		switch (slot) {
			case Components::SHIELD0:
			case Components::SHIELD1: {
				float maxShieldFront = getMaxFrontShield();
				float currentShieldFront = getFrontShield();

				damage += maxShieldFront - currentShieldFront;

				float maxShieldRear = getMaxRearShield();
				float currentShieldRear = getRearShield();

				damage += maxShieldRear - currentShieldRear;

				break;
			}
			case Components::CAPACITOR: {
				float maxCapacitor = getCapacitorMaxEnergy();
				float currentCapacitor = getCapacitorEnergy();

				damage += maxCapacitor - currentCapacitor;

				break;
			}
			case Components::BOOSTER: {
				float maxBoost = getBoosterMaxEnergy();
				float currentBoost = getBoosterEnergy();

				damage += maxBoost - currentBoost;

				break;
			}
		}
	}

	return damage;
}

void ShipObjectImplementation::repairShip(float value, bool decay) {
#ifdef DEBUG_SHIP_REPAIR
	info(true) << "---------- Repair Ship START - Value: " << value << " ------";
#endif

	float repair = Math::clamp(0.f, value, 1.f);

	if (repair == 0.f) {
		return;
	}

	auto pilot = owner.get();
	auto deltaVector = getDeltaVector();

	// Handle Chassis Repair
	float chassisMax = getChassisMaxHealth();
	float currentChassis = getChassisCurrentHealth();
	float chassisDamage = chassisMax - currentChassis;

	float chassisRepair = chassisDamage * repair;
	float newChassis = currentChassis + chassisRepair;

#ifdef DEBUG_SHIP_REPAIR
	info(true) << "Current Chassis: " << currentChassis << " New Chassis: " << newChassis << " Repair Amount: " << chassisRepair;
#endif

	setCurrentChassisHealth(newChassis, false, nullptr, deltaVector);

	uint8 command = DeltaMapCommands::SET;
	auto componentMap = getShipComponentMap();

#ifdef DEBUG_SHIP_REPAIR
	info(true) << "------ Starting Component Map Update ------\n";
#endif

	for (int i = 0; i < componentMap->size(); ++i) {
		uint32 slot = componentMap->getKeyAt(i);
		uint32 crc = componentMap->getValueAt(i);

#ifdef DEBUG_SHIP_REPAIR
		info(true) << "\n";
		info(true) << "Component Map #" << i << " - Component Slot: " << slot << " CRC: " << crc;
#endif

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

		setComponentOptions(slot, flags, nullptr, command,  deltaVector);

		// Handle Armor Repair and Decay
		float armorMax = getMaxArmorMap()->get(slot);
		float currentArmor = getCurrentArmorMap()->get(slot);
		float armorDamage = armorMax - currentArmor;

		float armorRepair = armorDamage * repair;
		int armorDecay = armorRepair / 10;
		float newArmor = currentArmor + armorRepair;

		if (decay && armorDecay > 0) {
			armorMax = Math::max(1.f, (armorMax - armorDecay));

			setComponentMaxArmor(slot, armorMax, nullptr, command, deltaVector);

			newArmor = (newArmor > armorMax ? armorMax : newArmor);
		}

#ifdef DEBUG_SHIP_REPAIR
		info(true) << "Old Armor Max: " << (armorMax + armorDecay) << " Armor Decay: " << armorDecay << " New Armor Max: " << armorMax;
		info(true) << "Current Armor: " << currentArmor << " New Armor: " << newArmor << " Repair Amount: " << armorRepair;
#endif

		setComponentArmor(slot, newArmor, nullptr, command, deltaVector);

		// Handle Hitpoints Repair and Decay
		float hitpointsMax = getMaxHitpointsMap()->get(slot);
		float currentHitpoints = getCurrentHitpointsMap()->get(slot);
		float hitpointsDamage = hitpointsMax - currentHitpoints;

		float hitpointsRepair = hitpointsDamage * repair;
		int hitpointsDecay = hitpointsRepair / 10;
		float newHitpoints = currentHitpoints + hitpointsRepair;

		if (decay && hitpointsDecay > 0) {
			hitpointsMax = Math::max(1.f, (hitpointsMax - hitpointsDecay));

			setComponentMaxHitpoints(slot, hitpointsMax, nullptr, command, deltaVector);

			newHitpoints = (newHitpoints > hitpointsMax ? hitpointsMax : newArmor);
		}

#ifdef DEBUG_SHIP_REPAIR
		info(true) << "Old Hitpoints Max: " << (hitpointsMax + hitpointsDecay) << " Hitpoints Decay: " << hitpointsDecay << " New Hitpoints Max: " << hitpointsMax;
		info(true) << "Current Hitpoints: " << currentHitpoints << " New Hitpoints: " << newHitpoints << " Repair Amount: " << hitpointsRepair;
#endif

		setComponentHitpoints(slot, newHitpoints, nullptr, command, deltaVector);

		switch (slot) {
			case Components::SHIELD0:
			case Components::SHIELD1: {
				float frontShieldMax = getMaxFrontShield();
				float frontShieldCurrent = getFrontShield();
				float frontShieldDamage = frontShieldMax - frontShieldCurrent;

				float frontRepair = frontShieldDamage * repair;
				float newShieldFront = frontShieldCurrent + frontRepair;

#ifdef DEBUG_SHIP_REPAIR
				info(true) << "Current Front Shield: " << frontShieldCurrent << " New Front Shield: " << newShieldFront << " Repair Amount: " << frontRepair;
#endif
				if (frontRepair > 0)
					setFrontShield(newShieldFront, false, nullptr, deltaVector);

				float rearShieldMax = getMaxRearShield();
				float rearShieldCurrent = getRearShield();
				float rearShieldDamage = rearShieldMax - rearShieldCurrent;

				float rearRepair = rearShieldDamage * repair;
				float newShieldRear = rearShieldCurrent + rearRepair;

#ifdef DEBUG_SHIP_REPAIR
				info(true) << "Current Rear Shield: " << frontShieldCurrent << " New Rear Shield: " << newShieldFront << " Repair Amount: " << rearRepair;
#endif
				if (rearRepair > 0)
					setRearShield(newShieldRear, false, nullptr, deltaVector);

				break;
			}

			case Components::CAPACITOR: {
				float maxCapacitor = getCapacitorMaxEnergy();
				float currentCapacitor = getCapacitorEnergy();
				float capacitorDamage = maxCapacitor - currentCapacitor;

				float capacitorRepair = capacitorDamage * repair;
				float newCapacitor = currentCapacitor + capacitorRepair;

#ifdef DEBUG_SHIP_REPAIR
				info(true) << "Current Capacitor: " << currentCapacitor << " New Capacitor: " << newCapacitor << " Repair Amount: " << capacitorRepair;
#endif
				if (capacitorRepair > 0)
					setCapacitorEnergy(newCapacitor, false, nullptr, deltaVector);

				break;
			}

			case Components::BOOSTER: {
				float maxBooster = getBoosterMaxEnergy();
				float currentBooster = getBoosterEnergy();
				float boosterDamage = maxBooster - currentBooster;

				float boosterRepair = boosterDamage * repair;
				float newBooster = currentBooster + boosterRepair;

#ifdef DEBUG_SHIP_REPAIR
				info(true) << "Current Booster: " << currentBooster << " New Booster: " << newBooster << " Repair Amount: " << boosterRepair;
#endif
				if (boosterRepair > 0)
					setBoosterEnergy(newBooster, false, nullptr, deltaVector);

				break;
			}
		}
	}

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(asShipObject(), pilot);
	}

#ifdef DEBUG_SHIP_REPAIR
	info(true) << "---------- Repair Ship END - Value: " << value << " ------";
#endif
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

bool ShipObjectImplementation::checkInConversationRange(SceneObject* targetObject) {
	if (targetObject == nullptr)
		return false;

	float sqDistance = getWorldPosition().squaredDistanceTo(targetObject->getWorldPosition());

	int distanceToCheck = COMM_MAX_DISTANCE * COMM_MAX_DISTANCE;

	// This ensures the check can be passed either direction and the proper distance is used
	if (isSpaceStation() || targetObject->isSpaceStation())
		distanceToCheck = SPACESTATION_COMM_MAX_DISTANCE * SPACESTATION_COMM_MAX_DISTANCE;

	return sqDistance < distanceToCheck;
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
	if (player == nullptr)
		return;

	// uint32 pvpStatus = pvpStatusBitmask;

	TangibleObjectImplementation::sendPvpStatusTo(player);

	// info(true) << "ShipObjectImplementation::sendPvpStatusTo - " << player->getDisplayedName() << " New Pvp Status: " << pvpStatus << " Old Pvp Status: " << pvpStatusBitmask;
}

bool ShipObjectImplementation::isAggressiveTo(TangibleObject* object) {
	if (object == nullptr)
		return false;

	if (!isShipLaunched())
		return false;

	auto thisOwner = getOwner().get();

 	if (thisOwner != nullptr) {
		if (!object->isShipAiAgent() && object->isShipObject()) {
			auto objectShip = object->asShipObject();

			if (objectShip != nullptr) {
				auto attackerOwner = objectShip->getOwner().get();

				// Owner of the other player ship for pvp checks
				if (attackerOwner != nullptr)
					return thisOwner->isAttackableBy(attackerOwner);
			}
		} else {
			thisOwner->isAggressiveTo(object);
		}
	}

	return false;
}

// This will be called for non AI Ships. ShipAgents use their abstracted function in ShipAiAgent
bool ShipObjectImplementation::isAttackableBy(TangibleObject* attackerTano) {
	if (!isShipLaunched())
		return false;

	auto optionsBit = getOptionsBitmask();

	if ((optionsBit & OptionBitmask::DESTROYING) || (optionsBit & OptionBitmask::INVULNERABLE)) {
		return false;
	}

	auto thisOwner = getOwner().get();

	if (thisOwner != nullptr) {
		// Player ship attacking another player ship. Pass the owners to the CreO isAttackable Check
		if (!attackerTano->isShipAiAgent() && attackerTano->isShipObject()) {
			auto attackerShip = attackerTano->asShipObject();

			if (attackerShip != nullptr) {
				auto attackerOwner = attackerShip->getOwner().get();

				// Owner of the other player ship for pvp checks
				if (attackerOwner != nullptr)
					return thisOwner->isAttackableBy(attackerOwner);
			}
		} else {
			// Attacking object is a TanO, likely another ship. Pass to CreO isAttackableBy TanO check
			thisOwner->isAttackableBy(attackerTano);
		}
	} else if (attackerTano->isCreatureObject()) {
		return isAttackableBy(attackerTano->asCreatureObject());
	}

	/*
		Remaining Checks should not be hit but just in case we will run faction checks
	*/

	// info(true) << "ShipObjectImplementation::isAttackableBy TANGIBLE -- attacking object: " << attackerTano->getDisplayedName();

	int thisFaction = getFaction();
	int tanoFaction = attackerTano->getFaction();

	// GCW Faction Checks
	if (thisFaction > 0 && tanoFaction > 0 && thisFaction == tanoFaction) {
		// Same faction, unable to attack
		return false;
	}

	// Attacker is factionally aligned, we are not
	if (thisFaction == 0 && tanoFaction > 0)
		return false;

	// info(true) << "ShipObjectImplementation::isAttackableBy TANGIBLE == TRUE -- attacking object: " << attackerTano->getDisplayedName();

	return true;
}

bool ShipObjectImplementation::isAttackableBy(CreatureObject* creature) {
	if (creature == nullptr)
		return false;

	// info(true) << "ShipObjectImplementation::isAttackableBy CREATURE -- attacking creature: " << creature->getDisplayedName();

	if (!isShipLaunched())
		return false;

	auto owner = getOwner().get();

	// This should handle most of our pvp checks, using the CreO isAttackable checks
	if (owner != nullptr)
		return owner->isAttackableBy(creature);

	// info(true) << "ShipObjectImplementation::isAttackableBy CREATURE == TRUE -- attacking creature: " << creature->getDisplayedName();

	return true;
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
	auto thisShip = asShipObject();

	VectorMap<String, ManagedReference<SceneObject* > > slotted;
	getSlottedObjects(slotted);

	SortedVector<ManagedReference<SceneObject*>> players;
	players.setNoDuplicateInsertPlan();

	// Check slotted objects for players
	for (int i = slotted.size() - 1; i >= 0 ; --i) {
		auto object = slotted.get(i);

		if (object == nullptr || !object->isPlayerCreature())
			continue;

		players.put(object);
	}

	// Check container for players
	for (int i = getContainerObjectsSize() - 1; i >= 0 ; --i) {
		auto object = getContainerObject(i);

		if (object == nullptr || !object->isPlayerCreature())
			continue;

		players.put(object);
	}

	// Kick all the players to the ground zone
	for (int i = players.size() - 1; i >= 0 ; --i) {
		auto& object = players.get(i);

		if (object == nullptr || !object->isPlayerCreature())
			continue;

		auto player = object->asCreatureObject();

		if (player == nullptr)
			continue;

		Locker clock(player, thisShip);

		auto ghost = player->getPlayerObject();

		if (ghost == nullptr)
			continue;

		auto launchZone = ghost->getSpaceLaunchZone();

		if (launchZone.isEmpty())
			launchZone = "tatooine";

		auto launchLoc = ghost->getSpaceLaunchLocation();

		player->switchZone(launchZone, launchLoc.getX(), launchLoc.getZ(), launchLoc.getY());
	}

	// Remove and destroy all the components
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

	if (getLocalZone() != nullptr)
		destroyObjectFromWorld(true);

	TangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

CreatureObject* ShipObjectImplementation::getPilot() {
	auto chair = getPilotChair().get();

	if (chair != nullptr) {
		return chair->getSlottedObject("ship_pilot_pob").castTo<CreatureObject*>();
	}

	return getSlottedObject("ship_pilot").castTo<CreatureObject*>();
}

CreatureObject* ShipObjectImplementation::getShipOperator() {
	auto chair = getOperationsChair().get();

	if (chair != nullptr) {
		return chair->getSlottedObject("ship_operations_station").castTo<CreatureObject*>();
	}

	return getSlottedObject("ship_operations_station").castTo<CreatureObject*>();
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

float ShipObjectImplementation::getSpeedRotationFactor(float speed) {
	const float maxSpeed = getActualMaxSpeed();
	const float maxFactor = getSpeedRotationFactorMax();
	const float minFactor = getSpeedRotationFactorMin();
	const float optimalFactor = getSpeedRotationFactorOptimal();

	const float speedRatio = maxSpeed > 0.f ? speed / maxSpeed : 0.f;

	auto getFactor = [&]() -> float {
		/*
		 *      rotation factor (in units of max pitch/yaw)
		 *      |
         *        +--------------------------------------------------------------------+
         *        |             +             +            +             +             |
         *        |                                ****                                ---- 1.0 @ optimal speed
         *        |                             ****  ****                             |
         *    0.8 |-+                       ****          ****                       +-|
         *        |                      ****                ****                      |
         *        |                   ***                        ***                   |
         *        |               ****                              ****               |
         *    0.4 |-+          ***                                      ***          +-|
         *        |        ****                                            ****        |
         *        |     ***                                                    ***     |
         *        | ****        +             +            +             +        **** ---- minFactor/maxFactor
         *      0 +-|-------------------------------|--------------------------------|-+
         *        0 |          0.2           0.4    |     0.6           0.8          | 1 -- speed (in units of max speed)
         *          |                               |                                |
         *      Min Speed                     Optimal Speed                     Max Speed
         *
         * When speed < optimal speed:
         *     find y-value on upslope, between minFactor and 1.f,
         *     interpolated from min speed (0.f) to optimal speed
         *     ergo, t = (speedRatio - 0) / (optimalFactor - 0) = speedRatio / optimalFactor
         *
         * When speed > optimal speed:
         *     find y-value on downslope, between 1.f and maxFactor
         *     interpolated from optimal speed to max speed (1.f)
         *     ergo, t = (speedRatio - optimalFactor) / (1 - optimalFactor)
		 */
		if (speedRatio < optimalFactor || optimalFactor >= 1.f) {
			// linearly interpolate between minFactor to 1 (1 being the optimal factor)
			// at a ratio in the range expressed as speedRatio / optimalFactor
			return Math::linearInterpolate(minFactor, 1.f, speedRatio / optimalFactor);
		}

		// linearly interpolate between 1 to maxFactor (1 being the optimal factor)
		// at a ratio in the range expressed as (speedRatio - optimalFactor) / (1 - optimalFactor)
		return Math::linearInterpolate(1.f, maxFactor, (speedRatio - optimalFactor) / (1.f - optimalFactor));
	};

	// discretize factor to prevent overupdating the client
	return floorf((getFactor() * 10.f) + 0.5f) / 10.f;
}

uint64 ShipObjectImplementation::getLastDamageReceivedMili() {
	return lastDamageReceived.getMiliTime();
}

void ShipObjectImplementation::addPlayerOnBoard(CreatureObject* player) {
	if (player == nullptr)
		return;

	playersOnBoard.put(player);
}

void ShipObjectImplementation::sendShipMembersMessage(const String& message) {
	for (int i = 0; i < playersOnBoard.size(); ++i) {
		auto member = playersOnBoard.get(i);

		if (member == nullptr)
			continue;

		member->sendSystemMessage(message);
	}
}

void ShipObjectImplementation::sendShipMembersMusicMessage(const String& message) {
	for (int i = 0; i < playersOnBoard.size(); ++i) {
		auto member = playersOnBoard.get(i);

		if (member == nullptr)
			continue;

		member->playMusicMessage(message);
	}
}

void ShipObjectImplementation::sendMembersHyperspaceBeginMessage(const String& zoneName, const Vector3& location) {
	for (int i = 0; i < playersOnBoard.size(); ++i) {
		auto member = playersOnBoard.get(i);

		if (member == nullptr)
			continue;

		BeginHyperspaceMessage* msg = new BeginHyperspaceMessage(member->getObjectID(), zoneName, location.getX(), location.getZ(), location.getY());
		member->sendMessage(msg);
	}
}

void ShipObjectImplementation::sendMembersHyperspaceOrientMessage(const String& zoneName, const Vector3& location) {
	for (int i = 0; i < playersOnBoard.size(); ++i) {
		auto member = playersOnBoard.get(i);

		if (member == nullptr)
			continue;

		OrientForHyperspaceMessage *msg = new OrientForHyperspaceMessage(member->getObjectID(), zoneName, location.getX(), location.getZ(), location.getY());
		member->sendMessage(msg);
	}
}

void ShipObjectImplementation::sendMembersBaseMessage(BaseMessage* message) {
	for (int i = 0; i < playersOnBoard.size(); ++i) {
		auto member = playersOnBoard.get(i);

		if (member == nullptr)
			continue;

		member->sendMessage(message->clone());
	}

	delete message;
}

bool ShipObjectImplementation::isShipLaunched() {
	return getLocalZone() != nullptr;
}

int ShipObjectImplementation::getReceiverFlags() const {
	int type = CloseObjectsVector::SHIPTYPE;

	if (ownerID > 0)
		type = type | CloseObjectsVector::PLAYERSHIPTYPE;

	return type | TangibleObjectImplementation::getReceiverFlags();
}
