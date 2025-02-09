/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "ComponentSlots.h"
#include "ShipComponentFlag.h"
#include "system/lang/UnicodeString.h"
#include "server/zone/Zone.h"
#include "server/zone/SpaceZone.h"
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
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/objects/tangible/item/CreditChipObject.h"
#include "server/zone/managers/loot/LootManager.h"

// #define DEBUG_COV

void ShipObjectImplementation::initializeTransientMembers() {
	hyperspacing = false;

	if (shipRecoveryEvent == nullptr && !isShipAiAgent()) {
		shipRecoveryEvent = new ShipRecoveryEvent(asShipObject());
	}

	for (int i = 0; i < componentOptions.size(); ++i) {
		resetComponentFlag(componentOptions.getKeyAt(i), false);
	}

	initializeUniqueID(false);

	TangibleObjectImplementation::initializeTransientMembers();
}

void ShipObjectImplementation::notifyLoadFromDatabase() {
	TangibleObjectImplementation::notifyLoadFromDatabase();

	// This ship is launched when loading from DB. Auto store it
	if (!isShipAiAgent() && isShipLaunched()) {
		auto zoneServer = getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		auto shipDevice = cast<ShipControlDevice*>(zoneServer->getObject(controlDeviceID).get());
		auto owner = getOwner().get();

		if (shipDevice != nullptr && owner != nullptr) {

			auto launchZone = getSpaceLaunchZone();
			auto launchLoc = getSpaceLaunchLocation();

			if (launchZone.isEmpty()) {
				launchZone = "naboo";
			}

			if (launchLoc.getX() == 0 && launchLoc.getY() == 0) {
				launchLoc.setX(-4868.f);
				launchLoc.setY(4154.f);
				launchLoc.setZ(6.0f);
			}

			StoreShipTask* storeTask = new StoreShipTask(owner, shipDevice, launchZone, launchLoc);

			if (storeTask != nullptr) {
				storeTask->schedule(2000);
			}
		}
	}
}

void ShipObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	auto shipTemp = dynamic_cast<SharedShipObjectTemplate*>(templateData);

	if (shipTemp == nullptr) {
		return;
	}

	chassisDataName = shipTemp->getShipName();
	setShipNameCRC(chassisDataName.hashCode(), false);

	setShipName("", false);

	setShipType(shipTemp->getShipType(), false);

	setChassisMaxHealth(shipTemp->getChassisHitpoints(), false);
	setCurrentChassisHealth(shipTemp->getChassisHitpoints(), false);

	setSlipRate(shipTemp->getChassisSlipRate(), false);
	setChassisSpeed(shipTemp->getChassisSpeed(), false);
	setChassisMaxMass(shipTemp->getChassisMass(), false);

	setShipFactionString(shipTemp->getShipFaction(), false);

	setShipDifficulty(shipTemp->getShipDifficulty(), false);

	setHasWings(shipTemp->shipHasWings());

	setChassisCategory(shipTemp->getChassisCategory());
	setChassisLevel(shipTemp->getChassisLevel());

	auto values = shipTemp->getAttributeMap();

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

	totalCellNumber = shipTemp->getTotalCellNumber();

	auto portalLayout = shipTemp->getPortalLayout();

	if (portalLayout != nullptr)
		totalCellNumber = portalLayout->getFloorMeshNumber();

	//info(true) << getDisplayedName() << " loaded a total of " << totalCellNumber << " cells.";

	auto chassisData = ShipManager::instance()->getChassisData(shipTemp->getShipName());

	if (chassisData != nullptr) {
		for (uint32 slot = 0; slot <= Components::FIGHTERSLOTMAX; slot++) {
			auto slotData = chassisData->getComponentSlotData(slot);
			setComponentTargetable(slot, slotData ? slotData->isTargetable() : false);
		}

		wingsOpenSpeed = chassisData->getWingOpenSpeed();
	}

	auto appearance = getAppearanceTemplate();

	if (appearance != nullptr) {
		auto volume = appearance->getBoundingVolume();

		if (volume != nullptr) {
			const auto& sphere = volume->getBoundingSphere();
			boundingRadius = sphere.getCenter().length() + sphere.getRadius();
		}
	}
}

void ShipObjectImplementation::sendTo(SceneObject* player, bool doClose, bool forceLoadContainer) {
	if (player == nullptr) {
		return;
	}

	// info(true) << "ShipObjectImplementation::sendTo - Ship Location: " << getWorldPosition().toString() << " sending to: " << player->getDisplayedName() << " Player Loc: " << player->getWorldPosition().toString()
	//	<< " Containment Type: " << player->getContainmentType();

	// Do not send the contents of the ships to anyone but the owner unless it is launched
	if (!isShipLaunched() && player->getObjectID() != getOwnerID()) {
		return;
	}

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
	Vector<TreeEntry*> closeObjects(closeObjectsVector->size(), 10);

	if (closeObjectsVector != nullptr) {
		closeObjectsVector->safeCopyTo(closeObjects);
	}

	// info(true) << getDisplayedName() << " notifyObjectInsertedToZone -- Total closeObjects: " << closeObjects.size();

	for (int i = 0; i < closeObjects.size(); ++i) {
		SceneObject* obj = static_cast<SceneObject*>(closeObjects.get(i));

		if (obj == nullptr || (!obj->isCreatureObject() && !obj->isShipObject())) {
			continue;
		}

		if (obj->getRootParent() != asShipObject()) {
			// info(true) << getDisplayedName() << " notifyObjectInsertedToZone -- adding in range object: " << obj->getDisplayedName();

			if (object->getCloseObjects() != nullptr) {
				object->addInRangeObject(obj, obj->isShipObject());
			} else {
				object->notifyInsert(obj);
			}

			if (obj->getCloseObjects() != nullptr) {
				obj->addInRangeObject(object, false);
			} else {
				obj->notifyInsert(object);
			}
		}
	}

	notifyInsert(object);

	if (object->getCloseObjects() != nullptr) {
		object->addInRangeObject(asShipObject(), false);
	}

	addInRangeObject(object, false);

	Zone* zone = getZone();

	if (zone != nullptr) {
		auto tanO = object->asTangibleObject();

		if (tanO != nullptr) {
			zone->updateActiveAreas(tanO);
		}

		object->notifyInsertToZone(zone);
	}
}

int ShipObjectImplementation::notifyObjectInserted(SceneObject* object) {
	// info(true) << "Ship: " << getDisplayedName() << " -- ShipObjectImplementation::notifyObjectInserted called";

	if (object == nullptr) {
		return 0;
	}

	// info(true) << "Ship: " << getDisplayedName() << " -- notifying for object: " << object->getDisplayedName();

	Reference<SceneObject*> sceneRef = object;
	Reference<ShipObject*> shipRef = asShipObject();

	Core::getTaskManager()->scheduleTask([shipRef, sceneRef] () {
		if (shipRef == nullptr || sceneRef == nullptr) {
			return;
		}

		shipRef->notifyObjectInsertedToZone(sceneRef);
	}, "ShipNotifyInsertedLambda", 500);

	return TangibleObjectImplementation::notifyObjectInserted(object);
}

void ShipObjectImplementation::notifyInsert(TreeEntry* object) {
	auto sceneO = static_cast<SceneObject*>(object);
	uint64 scnoID = sceneO->getObjectID();

#ifdef DEBUG_COV
	info(true) << "Ship: " << getDisplayedName() << " -- ShipObjectImplementation::notifyInsert -- Object inserted: " << sceneO->getDisplayedName() << " ID: " << scnoID << " Players on Board Size: " << getTotalPlayersOnBoard();
#endif // DEBUG_COV

	try {
		auto zoneServer = getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		for (int i = 0; i < playersOnBoard.size(); ++i) {
			auto shipMemberID = playersOnBoard.get(i);
			auto shipMember = cast<CreatureObject*>(zoneServer->getObject(shipMemberID).get());

			if (shipMember == nullptr) {
				continue;
			}

			// info(true) << "Ship: " << getDisplayedName() << " updating shipMember: " << shipMember->getDisplayedName();

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
		auto zoneServer = getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		for (int i = 0; i < playersOnBoard.size(); ++i) {
			auto shipMemberID = playersOnBoard.get(i);
			auto shipMember = cast<CreatureObject*>(zoneServer->getObject(shipMemberID).get());

			if (shipMember == nullptr) {
				continue;
			}

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

void ShipObjectImplementation::notifyDespawn(Zone* zone) {
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
	if (getLocalZone() == nullptr) {
		return;
	}

	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	const auto& worldPosition = getWorldPosition();

	for (int i = 0; i < playersOnBoard.size(); ++i) {
		auto shipMemberID = playersOnBoard.get(i);
		auto shipMember = cast<CreatureObject*>(zoneServer->getObject(shipMemberID).get());

		if (shipMember == nullptr) {
			continue;
		}

		Locker clock(shipMember, asShipObject());

		auto parent = shipMember->getParent().get();

		if (parent == nullptr) {
			continue;
		}

		if (parent == asShipObject()) {
			shipMember->setPosition(worldPosition.getX(), worldPosition.getZ(), worldPosition.getY());
		}

		shipMember->updateZoneWithParent(parent, lightUpdate, sendPackets);
	}
}

void ShipObjectImplementation::doRecovery(int mselapsed) {
	float deltaTime = mselapsed * 0.001f;

	if (deltaTime <= 0.f) {
		return;
	}

	auto pilot = owner.get();
	auto deltaVector = getDeltaVector();
	auto componentMap = getShipComponentMap();

	float reactorEnergy = getReactorGenerationRate() * calculateActualComponentEfficiency(Components::REACTOR) * deltaTime;
	bool updateFlags = false;

	for (int i = 0; i < componentMap->size(); ++i) {
		uint32 slot = componentMap->getKeyAt(i);
		uint32 crc = componentMap->getValueAt(i);

		if (!isComponentInstalled(slot)) {
			continue;
		}

		if (hasComponentFlag(slot, ShipComponentFlag::DEMOLISHED)) {
			continue;
		}

		if (hasComponentFlag(slot, ShipComponentFlag::DISABLED) && !hasComponentFlag(slot, ShipComponentFlag::DISABLED_NEEDS_POWER)) {
			continue;
		}

		float energyEfficiency = Math::clamp(0.1f, getComponentEnergyEfficiency(slot), 10.f);
		float componentEfficiency = Math::clamp(0.1f, getComponentEfficiency(slot), 10.f);
		float componentEnergyCost = getComponentEnergyCostMap()->get(slot);
		float reactorEnergyRate = 1.f;

		uint32 componentFlags = getComponentOptionsMap()->get(slot);

		if (componentEnergyCost > 0.f) {
			float energyCost = Math::max((componentEnergyCost / energyEfficiency) * deltaTime, 0.1f);

			if (reactorEnergy >= energyCost) {
				reactorEnergy -= energyCost;

				if (hasComponentFlag(slot, ShipComponentFlag::DISABLED_NEEDS_POWER)) {
					removeComponentFlag(slot, ShipComponentFlag::DISABLED_NEEDS_POWER, false);
				} else if (hasComponentFlag(slot, ShipComponentFlag::LOW_POWER)) {
					removeComponentFlag(slot, ShipComponentFlag::LOW_POWER, false);
				}
			} else {
				reactorEnergyRate = reactorEnergy / energyCost;
				reactorEnergy = 0.f;

				if (hasComponentFlag(slot, ShipComponentFlag::DISABLED_NEEDS_POWER)) {
					removeComponentFlag(slot, ShipComponentFlag::DISABLED_NEEDS_POWER, false);
				} else if (!hasComponentFlag(slot, ShipComponentFlag::LOW_POWER)) {
					addComponentFlag(slot, ShipComponentFlag::LOW_POWER, false);
				}
			}

			if (reactorEnergyRate <= 0.f) {
				reactorEnergyRate = 0.f;

				if (!hasComponentFlag(slot, ShipComponentFlag::DISABLED_NEEDS_POWER)) {
					addComponentFlag(slot, ShipComponentFlag::DISABLED_NEEDS_POWER, false);
				} else if (hasComponentFlag(slot, ShipComponentFlag::LOW_POWER)) {
					removeComponentFlag(slot, ShipComponentFlag::LOW_POWER, false);
				}
			}
		}

		switch (slot) {
			case Components::SHIELD0:
			case Components::SHIELD1: {
				float maxFront = getMaxFrontShield() * componentEfficiency * reactorEnergyRate;
				float minFront = getFrontShield();

				if (minFront != maxFront) {
					if (minFront < maxFront) {
						float rechargeRate = getShieldRechargeRate() * componentEfficiency * deltaTime;
						minFront = Math::min(minFront + rechargeRate, maxFront);
					} else if (minFront > maxFront) {
						float decayRate = getMaxFrontShield() * reactorEnergyRate * deltaTime;
						minFront = Math::max(minFront - decayRate, maxFront);
					}

					setFrontShield(minFront, false, nullptr, deltaVector);
				}

				float maxRear = getMaxRearShield() * componentEfficiency * reactorEnergyRate;
				float minRear = getRearShield();

				if (minRear != maxRear) {
					if (minRear < maxRear) {
						float rechargeRate = getShieldRechargeRate() * componentEfficiency * deltaTime;
						minRear = Math::min(minRear + rechargeRate, maxRear);
					} else if (minRear > maxRear) {
						float decayRate = getMaxRearShield() * reactorEnergyRate * deltaTime;
						minRear = Math::max(minRear - decayRate, maxRear);
					}

					setRearShield(minRear, false, nullptr, deltaVector);
				}

				break;
			}

			case Components::CAPACITOR: {
				float maxCap = getCapacitorMaxEnergy() * componentEfficiency * reactorEnergyRate;
				float minCap = getCapacitorEnergy();

				if (minCap != maxCap) {
					if (minCap < maxCap) {
						float rechargeRate = getCapacitorRechargeRate() * componentEfficiency * deltaTime;
						minCap = Math::min(minCap + rechargeRate, maxCap);
					} else if (minCap > maxCap) {
						float decayRate = getCapacitorMaxEnergy() * reactorEnergyRate * deltaTime;
						minCap = Math::max(minCap - decayRate, maxCap);
					}

					setCapacitorEnergy(minCap, false, nullptr, deltaVector);
				}

				break;
			}

			case Components::BOOSTER: {
				if (isBoosterActive()) {
					float boostLimit = (getBoosterConsumptionRate() / componentEfficiency) * deltaTime;
					float boostEnergy = getBoosterEnergy();

					if (boostEnergy >= boostLimit) {
						float value = boostEnergy - boostLimit;

						if (boostEnergy != value) {
							setBoosterEnergy(value, false, nullptr, deltaVector);
						}
					} else {
						removeComponentFlag(Components::BOOSTER, ShipComponentFlag::ACTIVE, false);
						restartBooster();

						if (pilot != nullptr) {
							pilot->sendSystemMessage("@space/space_interaction:booster_energy_depleted");
						}
					}
				} else {
					float maxBoost = getBoosterMaxEnergy() * componentEfficiency * reactorEnergyRate;
					float minBoost = getBoosterEnergy();

					if (minBoost != maxBoost) {
						if (minBoost < maxBoost) {
							float rechargeRate = getBoosterRechargeRate() * componentEfficiency * deltaTime;
							minBoost = Math::min(minBoost + rechargeRate, maxBoost);
						} else if (minBoost > maxBoost) {
							float decayRate = getBoosterMaxEnergy() * reactorEnergyRate * deltaTime;
							minBoost = Math::max(minBoost - decayRate, maxBoost);
						}

						setBoosterEnergy(minBoost, false, nullptr, deltaVector);
					}
				}

				break;
			}
		}

		if (!updateFlags && getComponentOptionsMap()->get(slot) != componentFlags) {
			updateFlags = true;
		}
	}

	if (updateFlags) {
		uint32 componentFlag = getComponentOptionsMap()->get(Components::REACTOR);
		setComponentOptions(Components::REACTOR, componentFlag, nullptr, DeltaMapCommands::SET, deltaVector);
	}

	updateActualEngineValues(false, deltaVector);
	updateComponentFlags(false, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(asShipObject());
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

	bool updateFlags = false;

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

		uint32 componentFlag = getComponentOptionsMap()->get(slot);

		if (hasComponentFlag(slot, ShipComponentFlag::DEMOLISHED)) {
			removeComponentFlag(slot, ShipComponentFlag::DEMOLISHED, false);
			setComponentCRC(slot, crc, nullptr, command, deltaVector);
		}

		resetComponentFlag(slot, false);

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

		if (!updateFlags && getComponentOptionsMap()->get(slot) != componentFlag) {
			updateFlags = true;
		}
	}

	if (updateFlags) {
		uint32 componentFlag = getComponentOptionsMap()->get(Components::REACTOR);
		setComponentOptions(Components::REACTOR, componentFlag, nullptr, DeltaMapCommands::SET, deltaVector);
	}

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(asShipObject());
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

bool ShipObjectImplementation::hasComponentFlag(uint32 slot, uint32 value) {
	return (componentOptions.get(slot) & value);
}

void ShipObjectImplementation::addComponentFlag(uint32 slot, uint32 value, bool notifyClient, ShipDeltaVector* deltaVector) {
	uint32 componentFlag = componentOptions.get(slot);

	if (componentFlag & value) {
		return;
	}

	componentFlag |= value;

	if (deltaVector == nullptr && notifyClient) {
		deltaVector = getDeltaVector();
	}

	setComponentOptions(slot, componentFlag, nullptr, DeltaMapCommands::SET, deltaVector);

	if (deltaVector != nullptr && notifyClient) {
		deltaVector->sendMessages(asShipObject());
	}
}

void ShipObjectImplementation::removeComponentFlag(uint32 slot, uint32 value, bool notifyClient, ShipDeltaVector* deltaVector) {
	uint32 componentFlag = componentOptions.get(slot);

	if (!(componentFlag & value)) {
		return;
	}

	componentFlag &= ~value;

	if (deltaVector == nullptr && notifyClient) {
		deltaVector = getDeltaVector();
	}

	setComponentOptions(slot, componentFlag, nullptr, DeltaMapCommands::SET, deltaVector);

	if (deltaVector != nullptr && notifyClient) {
		deltaVector->sendMessages(asShipObject());
	}
}

void ShipObjectImplementation::resetComponentFlag(uint32 slot, bool notifyClient, ShipDeltaVector* deltaVector) {
	uint32 componentFlag = componentOptions.get(slot);

	if (componentFlag & ShipComponentFlag::DISABLED) {
		componentFlag &= ~ShipComponentFlag::DISABLED;
	}

	if (componentFlag & ShipComponentFlag::LOW_POWER) {
		componentFlag &= ~ShipComponentFlag::LOW_POWER;
	}

	if (componentFlag & ShipComponentFlag::ACTIVE) {
		componentFlag &= ~ShipComponentFlag::ACTIVE;
	}

	if (componentFlag & ShipComponentFlag::DISABLED_NEEDS_POWER) {
		componentFlag &= ~ShipComponentFlag::DISABLED_NEEDS_POWER;
	}

	if (componentFlag == componentOptions.get(slot)) {
		return;
	}

	if (deltaVector == nullptr && notifyClient) {
		deltaVector = getDeltaVector();
	}

	setComponentOptions(slot, componentFlag, nullptr, DeltaMapCommands::SET, deltaVector);

	if (deltaVector != nullptr && notifyClient) {
		deltaVector->sendMessages(asShipObject());
	}
}

void ShipObjectImplementation::setComponentDemolished(uint32 slot, bool notifyClient, ShipDeltaVector* deltaVector) {
	if (deltaVector == nullptr && notifyClient) {
		deltaVector = getDeltaVector();
	}

	if (!hasComponentFlag(slot, ShipComponentFlag::DEMOLISHED)) {
		addComponentFlag(slot, ShipComponentFlag::DEMOLISHED, false, deltaVector);
	}

	switch (slot) {
		case Components::SHIELD0:
		case Components::SHIELD1: {
			setFrontShield(0.f, false, nullptr, deltaVector);
			setRearShield(0.f, false, nullptr, deltaVector);
			break;
		}

		case Components::CAPACITOR: {
			setCapacitorEnergy(0.f, false, nullptr, deltaVector);
			break;
		}

		case Components::BOOSTER: {
			setBoosterEnergy(0.f, false, nullptr, deltaVector);
			break;
		}
	}

	if (deltaVector != nullptr && notifyClient) {
		deltaVector->sendMessages(asShipObject());
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

void ShipObjectImplementation::sendPvpStatusTo(CreatureObject* player) {
	if (player == nullptr)
		return;

	// uint32 pvpStatus = pvpStatusBitmask;

	TangibleObjectImplementation::sendPvpStatusTo(player);
}

bool ShipObjectImplementation::isAggressiveTo(TangibleObject* object) {
	if (object == nullptr) {
		return false;
	}

	if (!isShipLaunched())
		return false;

	auto thisOwner = getOwner().get();

 	if (thisOwner != nullptr) {
		if (!object->isShipAiAgent() && object->isShipObject()) {
			auto objectShip = object->asShipObject();

			if (objectShip != nullptr) {
				auto attackerOwner = objectShip->getOwner().get();

				// Owner of the other player ship for pvp checks
				if (attackerOwner != nullptr) {
					return thisOwner->isAggressiveTo(attackerOwner);
				}
			}
		} else {
			thisOwner->isAggressiveTo(object);
		}
	}

	return false;
}

// This will be called for non AI Ships. ShipAgents use their abstracted function in ShipAiAgent
bool ShipObjectImplementation::isAttackableBy(TangibleObject* attackerTano) {
	if (attackerTano == nullptr) {
		return false;
	}

	if (!isShipLaunched()) {
		return false;
	}

	auto optionsBit = getOptionsBitmask();

	if ((optionsBit & OptionBitmask::DESTROYING) || (optionsBit & OptionBitmask::INVULNERABLE)) {
		return false;
	}

	// info(true) << getDisplayedName() << " ShipObjectImplementation::isAttackableBy -- " << attackerTano->getDisplayedName();

	auto thisOwner = getOwner().get();

	if (thisOwner != nullptr) {
		// Player ship attacking another player ship. Pass the owners to the CreO isAttackable Check
		if (!attackerTano->isShipAiAgent() && attackerTano->isShipObject()) {
			auto attackerShip = attackerTano->asShipObject();

			if (attackerShip != nullptr) {
				auto attackerOwner = attackerShip->getOwner().get();

				// Owner of the other player ship for pvp checks
				if (attackerOwner != nullptr) {
					// info(true) << getDisplayedName() << "Using ship owners -- thisOwner: " << thisOwner->getDisplayedName() << " attackerOwner: " << attackerOwner->getDisplayedName();

					return thisOwner->isAttackableBy(attackerOwner);
				}
			}
		} else {
			// info(true) << getDisplayedName() << "Using thisOwner: " << thisOwner->getDisplayedName() << " against tangible object: " << attackerTano->getDisplayedName();

			// Attacking object is a TanO, likely another ship. Pass to CreO isAttackableBy TanO check
			thisOwner->isAttackableBy(attackerTano);
		}
	} else if (attackerTano->isCreatureObject()) {
		// info(true) << getDisplayedName() << " isAttackableBy creature: " << attackerTano->getDisplayedName();

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
	// Clear the players on board list
	playersOnBoard.removeAll();

	auto thisShip = asShipObject();

	VectorMap<String, ManagedReference<SceneObject* > > slotted;
	getSlottedObjects(slotted);

	SortedVector<ManagedReference<SceneObject*>> players;

	// Get the Launch location
	auto launchZone = getSpaceLaunchZone();
	auto launchLoc = getSpaceLaunchLocation();

	// This should not be an empty string, but just in case it is, send them to Coronet
	if (launchZone.isEmpty()) {
		launchZone = "corellia";
		launchLoc.set(-66, 28, -4711);
	}

	// Check slotted objects for players
	for (int i = slotted.size() - 1; i >= 0 ; --i) {
		auto object = slotted.get(i);

		if (object == nullptr || !object->isPlayerCreature()) {
			continue;
		}

		Locker clock(object, thisShip);

		object->switchZone(launchZone, launchLoc.getX(), launchLoc.getZ(), launchLoc.getY(), 0, false, -1);

		if (hasObjectInContainer(object->getObjectID())) {
			removeObject(object, nullptr, false);
		}
	}

	// Check container for players
	for (int i = getContainerObjectsSize() - 1; i >= 0 ; --i) {
		auto object = getContainerObject(i);

		if (object == nullptr || !object->isPlayerCreature()) {
			continue;
		}

		Locker clock(object, thisShip);

		object->switchZone(launchZone, launchLoc.getX(), launchLoc.getZ(), launchLoc.getY(), 0, false, -1);

		if (hasObjectInContainer(object->getObjectID())) {
			removeObject(object, nullptr, false);
		}
	}

	// Remove and destroy all the components
	auto playerOwner = owner.get();

	for (uint32 slot = 0; slot <= Components::FIGHTERSLOTMAX; ++slot) {
		auto component = components.get(slot);

		if (component == nullptr) {
			continue;
		}

		if (playerOwner != nullptr && !destroyContainedObjects) {
			uninstall(playerOwner, slot, true);
			component = components.get(slot);
		}

		if (component != nullptr) {
			Locker cLock(component, thisShip);
			component->destroyObjectFromDatabase(true);
		}
	}

	if (getLocalZone() != nullptr) {
		destroyObjectFromWorld(true);
	}

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

	if (chair == nullptr) {
		return nullptr;
	}

	return chair->getSlottedObject("ship_operations_station").castTo<CreatureObject*>();
}

CreatureObject* ShipObjectImplementation::getTurretOperatorTop() {
	auto turretLadder = getTurretLadder().get();

	if (turretLadder == nullptr) {
		return nullptr;
	}

	return turretLadder->getSlottedObject("ship_gunner0_pob").castTo<CreatureObject*>();
}

CreatureObject* ShipObjectImplementation::getTurretOperatorBottom() {
	auto turretLadder = getTurretLadder().get();

	if (turretLadder == nullptr) {
		return nullptr;
	}

	return turretLadder->getSlottedObject("ship_gunner1_pob").castTo<CreatureObject*>();
}

void ShipObjectImplementation::setRotationMatrix(const Quaternion& value) {
	rotationMatrix.setRotationMatrix(value.toMatrix3());
	conjugateMatrix.setRotationMatrix(value.getConjugate().toMatrix3());
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

CreatureObject* ShipObjectImplementation::getPlayerOnBoard(int index) {
	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		return nullptr;
	}

	auto shipMemberID = playersOnBoard.get(index);
	auto shipMember = cast<CreatureObject*>(zoneServer->getObject(shipMemberID).get());

	if (shipMember == nullptr) {
		return nullptr;
	}

	return shipMember;
}

void ShipObjectImplementation::addPlayerOnBoard(CreatureObject* player) {
	if (player == nullptr) {
		return;
	}

	uint64 playerID = player->getObjectID();

	if (playersOnBoard.contains(playerID)) {
		return;
	}

	playersOnBoard.add(playerID);
}

void ShipObjectImplementation::removePlayerOnBoard(CreatureObject* player) {
	if (player == nullptr) {
		return;
	}

	uint64 playerID = player->getObjectID();

	for (int i = playersOnBoard.size() - 1; i >= 0; i--) {
		if (playersOnBoard.get(i) != playerID) {
			continue;
		}

		playersOnBoard.remove(i);
	}
}

void ShipObjectImplementation::clearPlayersOnBoard() {
	playersOnBoard.removeAll();
}

int ShipObjectImplementation::getTotalPlayersOnBoard() {
	return playersOnBoard.size();
}

Vector<uint64> ShipObjectImplementation::getPlayersOnBoard() {
	return playersOnBoard;
}

void ShipObjectImplementation::sendShipMembersMessage(const String& message) {
	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	for (int i = 0; i < playersOnBoard.size(); ++i) {
		auto shipMemberID = playersOnBoard.get(i);
		auto shipMember = cast<CreatureObject*>(zoneServer->getObject(shipMemberID).get());

		if (shipMember == nullptr) {
			continue;
		}

		shipMember->sendSystemMessage(message);
	}
}

void ShipObjectImplementation::sendShipMembersMusicMessage(const String& message) {
	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	for (int i = 0; i < playersOnBoard.size(); ++i) {
		auto shipMemberID = playersOnBoard.get(i);
		auto shipMember = cast<CreatureObject*>(zoneServer->getObject(shipMemberID).get());

		if (shipMember == nullptr) {
			continue;
		}

		shipMember->playMusicMessage(message);
	}
}

void ShipObjectImplementation::sendMembersHyperspaceBeginMessage(const String& zoneName, const Vector3& location) {
	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	for (int i = 0; i < playersOnBoard.size(); ++i) {
		auto shipMemberID = playersOnBoard.get(i);
		auto shipMember = cast<CreatureObject*>(zoneServer->getObject(shipMemberID).get());

		if (shipMember == nullptr) {
			continue;
		}

		BeginHyperspaceMessage* msg = new BeginHyperspaceMessage(shipMember->getObjectID(), zoneName, location.getX(), location.getZ(), location.getY());
		shipMember->sendMessage(msg);
	}
}

void ShipObjectImplementation::sendMembersHyperspaceOrientMessage(const String& zoneName, const Vector3& location) {
	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	for (int i = 0; i < playersOnBoard.size(); ++i) {
		auto shipMemberID = playersOnBoard.get(i);
		auto shipMember = cast<CreatureObject*>(zoneServer->getObject(shipMemberID).get());

		if (shipMember == nullptr) {
			continue;
		}

		OrientForHyperspaceMessage *msg = new OrientForHyperspaceMessage(shipMember->getObjectID(), zoneName, location.getX(), location.getZ(), location.getY());
		shipMember->sendMessage(msg);
	}
}

void ShipObjectImplementation::sendMembersBaseMessage(BaseMessage* message, bool sendSelf) {
	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	auto selfObject = owner.get();

	for (int i = 0; i < playersOnBoard.size(); ++i) {
		auto shipMemberID = playersOnBoard.get(i);
		auto shipMember = cast<CreatureObject*>(zoneServer->getObject(shipMemberID).get());

		if (shipMember == nullptr || (!sendSelf && shipMember == selfObject)) {
			continue;
		}

		shipMember->sendMessage(message->clone());
	}

	delete message;
}

void ShipObjectImplementation::awardLootItems(ShipAiAgent* destructedShip, int payout) {
	if (destructedShip == nullptr) {
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

	Locker pilotClock(pilot, destructedShip);

	auto inventory = pilot->getInventory();

	if (inventory == nullptr) {
		return;
	}

	int inventoryVolume = inventory->getContainerVolumeLimit();

	// Initial Inventory check can return if full
	if ((inventory->getCountableObjectsRecursive() + 1) > inventoryVolume) {
		pilot->sendSystemMessage("@space/space_loot:no_more_loot"); // "Your inventory is full so you cannot receive any more loot."
		return;
	}

	// Get pilots group for messages
	Reference<GroupObject*> pilotGroup = nullptr;

	if (pilot->isGrouped()) {
		pilotGroup = pilot->getGroup();
	}

	// Main Loot TransactionLog
	TransactionLog trx(TrxCode::NPCLOOT, destructedShip);

	CreditChipObject* creditChip = nullptr;
	uint32 creditChipHash = STRING_HASHCODE("object/tangible/item/loot_credit_chip.iff");

	for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
		auto sceneO = inventory->getContainerObject(i);

		if (sceneO == nullptr || sceneO->getServerObjectCRC() != creditChipHash) {
			continue;
		}

		creditChip = sceneO.castTo<CreditChipObject*>();
		break;
	}

	// No existing credit chip was found, create a new one
	if (creditChip == nullptr) {
		creditChip = zoneServer->createObject(creditChipHash, 1).castTo<CreditChipObject*>();
	}

	if (creditChip != nullptr) {
		Locker creditsClock(creditChip, destructedShip);

		// Create CreditChip TransactionLog
		TransactionLog trxChip(TrxCode::CREDITCHIP, pilot, creditChip, true);

		// Set the CreditChip value
		creditChip->setUseCount(payout + creditChip->getUseCount());

		trxChip.addState("addedValue", payout);

		// Transfer to Pilots inventory
		if (inventory->transferObject(creditChip, -1, false)) {
			creditChip->sendTo(pilot, true);

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

			trxChip.abort() << "Failed to transferObject for CreditChip to shipMember";
		}
	}

	// Award Loot items here
	int lootRolls = destructedShip->getLootRolls();
	const auto lootTable = destructedShip->getLootTable();

	if (lootTable.isEmpty()) {
		trx.commit(true);
		return;
	}

	for (int i = 0; i < lootRolls; i++) {
		// Check if there is space in players inventory, if not do not itterate anymore attempts
		if ((inventory->getCountableObjectsRecursive() + 1) > inventoryVolume) {
			pilot->sendSystemMessage("@space/space_loot:no_more_loot"); // "Your inventory is full so you cannot receive any more loot."
			break;
		}

		uint64 lootObjectID = lootManager->createLoot(trx, inventory, destructedShip);

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

bool ShipObjectImplementation::isShipLaunched() {
	return getLocalZone() != nullptr;
}

int ShipObjectImplementation::getReceiverFlags() const {
	int type = CloseObjectsVector::SHIPTYPE;

	if (ownerID > 0) {
		type = type | CloseObjectsVector::PLAYERSHIPTYPE;
	}

	return type | TangibleObjectImplementation::getReceiverFlags();
}

float ShipObjectImplementation::getOutOfRangeDistance(uint64 specialRangeID) {
	if (specialRangeID > 0) {
		auto pilot = getPilot();

		if (pilot != nullptr) {
			return pilot->getOutOfRangeDistance(specialRangeID);
		}
	}

	return ZoneServer::SPACECLOSEOBJECTRANGE;
}

bool ShipObjectImplementation::isComponentInstalled(uint32 slot) {
	return getShipComponentMap()->get(slot) != 0;
}

bool ShipObjectImplementation::isComponentFunctional(uint32 slot) {
	return isComponentInstalled(slot) && !hasComponentFlag(slot, ShipComponentFlag::DISABLED) && !hasComponentFlag(slot, ShipComponentFlag::DEMOLISHED);
}

float ShipObjectImplementation::calculateActualComponentEfficiency(uint32 slot) {
	return isComponentFunctional(slot) ? Math::clamp(0.1f, getComponentEfficiency(slot) * getComponentCondition(slot), 10.f) : 0.f;
}

float ShipObjectImplementation::calculateSpeedRotationFactor() {
	float speedCurrent = getCurrentSpeed();
	float speedMax = getActualMaxSpeed();

	float factorOptimal = getSpeedRotationFactorOptimal();
	float factorMax = getSpeedRotationFactorMax();
	float factorMin = getSpeedRotationFactorMin();

	if (speedCurrent <= 0.f || speedMax <= 0.f) {
		return factorMin;
	}

	float factorPercent = Math::clamp(0.f, speedCurrent / speedMax, 1.f);
	float factorActual = factorMin;

	if (factorPercent < factorOptimal || factorOptimal >= 1.f) {
		float ratio = factorPercent / factorOptimal;
		factorActual = Math::linearInterpolate(factorMin, 1.f, ratio);
	} else {
		float ratio = (factorPercent - factorOptimal) / (1.f - factorOptimal);
		factorActual = Math::linearInterpolate(1.f, factorMax, ratio);
	}

	return factorActual;
}

float ShipObjectImplementation::calculateActualAccelerationRate() {
	float engineAcceleration = 0.f;

	if (isComponentInstalled(Components::ENGINE)) {
		engineAcceleration = getEngineAccelerationRate() * calculateActualComponentEfficiency(Components::ENGINE);
	}

	float boosterAcceleration = 0.f;

	if (isComponentInstalled(Components::BOOSTER) && isBoosterActive()) {
		boosterAcceleration = getBoosterAcceleration() * calculateActualComponentEfficiency(Components::BOOSTER);
	}

	return engineAcceleration + boosterAcceleration;
}

float ShipObjectImplementation::calculateActualDecelerationRate() {
	float engineDeceleration = getEngineDecelerationRate();

	if (isComponentFunctional(Components::ENGINE)) {
		engineDeceleration *= calculateActualComponentEfficiency(Components::ENGINE);
	}

	return engineDeceleration;
}

float ShipObjectImplementation::calculateActualMaxSpeed() {
	float engineSpeed = 0.f;

	if (isComponentInstalled(Components::ENGINE)) {
		engineSpeed = getEngineMaxSpeed() * calculateActualComponentEfficiency(Components::ENGINE);
	}

	float boosterSpeed = 0.f;

	if (isComponentInstalled(Components::BOOSTER) && isBoosterActive()) {
		boosterSpeed = getBoosterMaxSpeed() * calculateActualComponentEfficiency(Components::BOOSTER);
	}

	float chassisSpeed = getChassisSpeed();

	if (hasShipWings() && (getOptionsBitmask() & OptionBitmask::WINGS_OPEN) && wingsOpenSpeed > 0.f) {
		auto chassisData = ShipManager::instance()->getChassisData(chassisDataName);

		if (chassisData != nullptr) {
			chassisSpeed *= wingsOpenSpeed;
		}
	}

	return Math::clamp(0.f, ((engineSpeed + boosterSpeed) * chassisSpeed), 512.f);
}

void ShipObjectImplementation::updateSpeedRotationValues(bool notifyClient, ShipDeltaVector* deltaVector) {
	float engineEfficiency = calculateActualComponentEfficiency(Components::ENGINE);
	float rotationFactor = calculateSpeedRotationFactor();

	float actualPitchRate = getEnginePitchRate() * engineEfficiency * rotationFactor;
	float actualYawRate = getEngineYawRate() * engineEfficiency * rotationFactor;

	if (getActualPitchRate() == actualPitchRate && getActualYawRate() == actualYawRate) {
		return;
	}

	if (deltaVector == nullptr && notifyClient) {
		deltaVector = getDeltaVector();
	}

	if (getActualPitchRate() != actualPitchRate) {
		setActualPitchRate(actualPitchRate, false, nullptr, deltaVector);
	}

	if (getActualYawRate() != actualYawRate) {
		setActualYawRate(actualYawRate, false, nullptr, deltaVector);
	}

	if (deltaVector != nullptr && notifyClient) {
		deltaVector->sendMessages(asShipObject());
	}
}

void ShipObjectImplementation::updateActualEngineValues(bool notifyClient, ShipDeltaVector* deltaVector) {
	float componentEfficiency = calculateActualComponentEfficiency(Components::ENGINE);
	float rotationFactor = calculateSpeedRotationFactor();

	float actualAcceleration = calculateActualAccelerationRate();
	float actualDeceleration = calculateActualDecelerationRate();
	float actualPitchAccel = getEnginePitchAccelerationRate() * componentEfficiency;
	float actualYawAccel = getEngineYawAccelerationRate() * componentEfficiency;
	float actualRollAccel = getEngineRollAccelerationRate() * componentEfficiency;
	float actualPitch = getEnginePitchRate() * componentEfficiency * rotationFactor;
	float actualYaw = getEnginePitchRate() * componentEfficiency * rotationFactor;
	float actualRoll = getEnginePitchRate() * componentEfficiency;
	float actualSpeed = calculateActualMaxSpeed();

	if (deltaVector == nullptr && notifyClient) {
		deltaVector = getDeltaVector();
	}

	if (getActualAccelerationRate() != actualAcceleration) {
		setActualAccelerationRate(actualAcceleration, false, nullptr, deltaVector);
	}

	if (getActualDecelerationRate() != actualDeceleration) {
		setActualDecelerationRate(actualDeceleration, false, nullptr, deltaVector);
	}

	if (getActualPitchAccelerationRate() != actualPitchAccel) {
		setActualPitchAccelerationRate(actualPitchAccel, false, nullptr, deltaVector);
	}

	if (getActualYawAccelerationRate() != actualYawAccel) {
		setActualYawAccelerationRate(actualYawAccel, false, nullptr, deltaVector);
	}

	if (getActualRollAccelerationRate() != actualRollAccel) {
		setActualRollAccelerationRate(actualRollAccel, false, nullptr, deltaVector);
	}

	if (getActualPitchRate() != actualPitch) {
		setActualPitchRate(actualPitch, false, nullptr, deltaVector);
	}

	if (getActualYawRate() != actualYaw) {
		setActualYawRate(actualYaw, false, nullptr, deltaVector);
	}

	if (getActualRollRate() != actualRoll) {
		setActualRollRate(actualRoll, false, nullptr, deltaVector);
	}

	if (getActualMaxSpeed() != actualSpeed) {
		if (staffModifiedSpeed > 1.f) {
			actualSpeed = staffModifiedSpeed;
		}

		setActualMaxSpeed(actualSpeed, false, nullptr, deltaVector);
	}

	if (deltaVector != nullptr && notifyClient) {
		deltaVector->sendMessages(asShipObject());
	}
}

void ShipObjectImplementation::updateComponentFlags(bool notifyClient, ShipDeltaVector* deltaVector) {
	bool updateFlags = false;

	for (int i = 0; i < componentOptions.size(); ++i) {
		uint32 slot = componentOptions.getKeyAt(i);

		if (!isComponentInstalled(slot)) {
			continue;
		}

		uint32 componentFlag = componentOptions.getValueAt(i);

		if (hasComponentFlag(slot, ShipComponentFlag::DEMOLISHED)) {
			if (hasComponentFlag(slot, ShipComponentFlag::ACTIVE)) {
				removeComponentFlag(slot, ShipComponentFlag::ACTIVE, false);
			} else if (hasComponentFlag(slot, ShipComponentFlag::DISABLED)) {
				removeComponentFlag(slot, ShipComponentFlag::DISABLED, false);
			}
		} else if (hasComponentFlag(slot, ShipComponentFlag::DISABLED_NEEDS_POWER)) {
			if (hasComponentFlag(slot, ShipComponentFlag::ACTIVE)) {
				removeComponentFlag(slot, ShipComponentFlag::ACTIVE, false);
			} else if (!hasComponentFlag(slot, ShipComponentFlag::DISABLED)) {
				addComponentFlag(slot, ShipComponentFlag::DISABLED, false);
			}
		} else {
			if (!hasComponentFlag(slot, ShipComponentFlag::ACTIVE) && slot != Components::BOOSTER) {
				addComponentFlag(slot, ShipComponentFlag::ACTIVE, false);
			} else if (hasComponentFlag(slot, ShipComponentFlag::DISABLED)) {
				removeComponentFlag(slot, ShipComponentFlag::DISABLED, false);
			}
		}

		if (!updateFlags && componentOptions.getValueAt(i) != componentFlag) {
			updateFlags = true;
		}
	}

	if (updateFlags) {
		if (deltaVector == nullptr && notifyClient) {
			deltaVector = getDeltaVector();
		}

		uint32 componentFlag = componentOptions.get(Components::REACTOR);
		componentOptions.update(Components::REACTOR, componentFlag, nullptr, DeltaMapCommands::SET, deltaVector);

		if (deltaVector != nullptr && notifyClient) {
			deltaVector->sendMessages(asShipObject());
		}
	}
}

void ShipObjectImplementation::initializeUniqueID(bool notifyClient) {
	auto shipManager = ShipManager::instance();

	if (shipManager == nullptr) {
		return;
	}

	if (getUniqueID() != 0) {
		shipManager->dropShipUniqueID(asShipObject());
	}

	uint16 shipID = shipManager->setShipUniqueID(asShipObject());
	setUniqueID(shipID, notifyClient);
}

bool ShipObjectImplementation::canBePilotedBy(CreatureObject* player) {
	if (player == nullptr) {
		return false;
	}

	if (certificationRequired.isEmpty()) {
		return true;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr) {
		return false;
	}

	return (ghost->hasAbility(certificationRequired) || player->hasSkill(certificationRequired));
}

bool ShipObjectImplementation::hasComponentsInstalled() {
	for (int i = 0; i < componentOptions.size(); ++i) {
		uint32 slot = componentOptions.getKeyAt(i);

		if (isComponentInstalled(slot)) {
			return true;
		}
	}

	return false;
}

bool ShipObjectImplementation::isStarterShip() {
	auto chassisName = getShipChassisName().hashCode();

	return ((STRING_HASHCODE("player_basic_tiefighter") == chassisName) || (STRING_HASHCODE("player_basic_hutt_light") == chassisName) || (STRING_HASHCODE("player_basic_z95") == chassisName));
}

bool ShipObjectImplementation::isSorosuubSpaceYacht() {
	auto chassisName = getShipChassisName().hashCode();

	return (STRING_HASHCODE("player_sorosuub_space_yacht") == chassisName);
}
