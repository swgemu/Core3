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
#include "templates/tangible/SharedShipObjectTemplate.h"
#include "server/zone/objects/ship/ComponentSlots.h"
#include "server/zone/objects/ship/ShipComponentFlag.h"
#include "server/zone/packets/ship/DestroyShipMessage.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/ship/components/ShipComponent.h"
#include "templates/params/creature/PlayerArrangement.h"

/*ShipManager::ShipManager() {
	IffStream* iffStream = DataArchiveStore::instance()->openIffFile(
			"datatables/space/ship_components.iff");

	if (iffStream == nullptr) {
		fatal("datatables/space/ship_components.iff could not be found.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		Reference<ShipComponent*> component = new ShipComponent();
		component->readObject(row);

		debug() << "loaded ship component " << component->getName() << " crc: " << component->getName();

		shipComponents.put(component->getName().hashCode(), component);
	}

	delete iffStream;
}

ShipManager::ShipManager() {
	setLoggingName("ShipManager");

	loadShipChassisData();
	loadShipComponentData();
	loadShipWeaponData();
	loadHyperspaceLocations();
	loadShipAppearanceData();

	projectileThread = new ProjectileThread();
	projectileThread->start();
}
*/

void ShipManager::initialize() {
	loadShipChassisData();
	loadShipComponentData();
	loadShipWeaponData();
	loadHyperspaceLocations();
	loadShipAppearanceData();
}

void ShipManager::checkProjectiles() {
	if (projectiles.size() == 0)
		return;

	Locker locker(&projectileMutex);
	for (int i = projectiles.size() - 1; i >= 0; i--) {
		ShipProjectile* projectile = projectiles.get(i);
		if (projectile == nullptr)
			break;

		Reference<ShipObject*> ship = projectile->getShip().get();

		if (ship == nullptr) {
			delete projectile;
			projectiles.remove(i);
		}

		float dt = projectile->peekDelta();
		if (dt < .3f)
			continue;

		dt = projectile->getDelta();

		Vector3 startPos = projectile->position;
		Vector3 dir = projectile->direction;
		dir.normalize();

		projectile->position = startPos + (dir * projectile->speed * dt);
		float dist = (projectile->position - projectile->startPosition).squaredLength();
		// info("Updated projectile[" + String::valueOf(i) + "]: " + startPos.toString() + "-->" + projectile->position.toString() + " dt: " + String::valueOf(dt), true);

		Vector3 collisionPoint;
		Vector<ManagedReference<SceneObject*>> collidedObject;

		if (CollisionManager::checkShipWeaponCollision(ship, startPos, projectile->position, collisionPoint, collidedObject)) {
			if (collidedObject.size() > 0) {
				applyDamage(projectile, ship, collisionPoint, collidedObject);

				delete projectile;
				projectiles.remove(i);
				continue;
			}
		}

		if (dist > projectile->rangeSq) {
			// info("Projectile moving out of range", true);
			// info("Final position: " + (projectile->startPosition + (dir * projectile->range)).toString(), true);
			delete projectile;
			projectiles.remove(i);
			continue;
		}
	}
}

bool ShipManager::doComponentDamage(ShipObject* ship, const Vector3& collisionPoint, const Vector3& direction, float& damage, int& slot, float& previousHealth, float& currentHealth) const {
	const auto& componentCRCs = ship->getShipComponentMap();

	const ShipChassisData* chassis = chassisData.get(ship->getShipName());
	const AppearanceTemplate* appr = ship->getObjectTemplate()->getAppearanceTemplate();
	const VectorMap<String, Matrix4>& hardpointTransforms = appr->getHardpoints();
	int closestSlot = -1;
	float closestDistance = FLT_MAX;

	if (appr == nullptr || chassis == nullptr || componentCRCs->size() == 0)
		return false;

	Vector<int> activeComponents;
	const auto& hitpoints = ship->getCurrentHitpointsMap();
	for (int i = 0; i < componentCRCs->size(); i++) {
		int crc32 = componentCRCs->getValueAt(i);
		int slot = componentCRCs->getKeyAt(i);
		const ShipComponentData* componentData = getShipComponent(crc32);
		const String& name = componentData->getName();
		const ShipChassisData::ComponentSlotData* slotData = chassis->getComponentSlotData(slot);
		const Vector<const ShipChassisData::ComponentHardpoint*> hardpoints = slotData->getHardpoint(name);
		if (hitpoints->get(i) > 0)
			activeComponents.add(i);

		if (ship->getGameObjectType() == SceneObjectType::SHIPCAPITAL && !slotData->isTargetable())
			continue;

		for (const ShipChassisData::ComponentHardpoint* hardpoint : hardpoints) {
			const String& hardpointName = hardpoint->getHardpointName();
			if (hardpointName.isEmpty() && hardpointTransforms.contains(hardpointName))
				continue;

			const Matrix4& transform = hardpointTransforms.get(hardpointName);
			Vector3 pos = Vector3(transform[3][0], transform[3][2], transform[3][1]);
			float sqDist = pos.squaredDistanceTo(collisionPoint);

			if (sqDist < (hardpoint->getRange() * hardpoint->getRange()) && sqDist < closestDistance) {
				closestSlot = slot;
				closestDistance = sqDist;
				info("Hit: " + hardpointName, true);
			}
		}
	}

	if (closestSlot != -1) {
		return damageComponent(ship, damage, closestSlot, direction);
	} else {
		while (activeComponents.size() > 0 && damage > 0) {
			int slot = System::random(activeComponents.size() - 1);
			damageComponent(ship, damage, slot, direction);
			if (damage > 0) // component was completely destroyed if we still have damage left over
				activeComponents.remove(slot);
		}
	}

	return false;
}

bool ShipManager::damageComponent(ShipObject* ship, float& damage, int closestSlot, const Vector3& direction) const {
	float currentHealth;
	float previousHealth;
	DeltaMessage* delta = new DeltaMessage(ship->getObjectID(), 'SHIP', 3);
	float armor = ship->getCurrentArmorMap()->get(closestSlot);
	float health = ship->getCurrentHitpointsMap()->get(closestSlot);
	float total = armor + health;
	bool doUpdate = false;
	if (damage > 0 && armor > 0) {
		armor -= damage;
		if (armor < 0) {
			damage = armor * -1.0f;
			armor = 0.0f;
		} else {
			damage = 0;
		}
		doUpdate = true;
		ship->setComponentArmor(closestSlot, armor, delta);
	}

	if (damage > 0 && health > 0) {
		health -= damage;
		if (health < 0) {
			damage = health * -1.0f;
			health = 0.0f;
		} else {
			damage = 0;
		}
		doUpdate = true;
		ship->setComponentHitpoints(closestSlot, health, delta);
	}

	if (armor <= 0 && damage <= 0) {
		int flags = ship->getComponentOptionsMap()->get(closestSlot);

		if (!(flags & ShipComponentFlag::DEMOLISHED)) {
			ship->setComponentOptions(closestSlot, flags, delta);
		}
	}

	if (doUpdate) {
		previousHealth = total;
		currentHealth = armor + health;
		delta->close();
		ship->broadcastMessage(delta, true);
		notifyShipHit(ship, direction, 2, currentHealth / total, previousHealth / total);
		return true;
	} else {
		delete delta;
	}
	return false;
}

void ShipManager::notifyShipHit(ShipObject* target, const Vector3& localdir, int type, float curHealth, float prevHealth) {
	if (target == nullptr)
		return;

	Matrix4* transform = CollisionManager::getTransformMatrix(target);
	Vector3 dir = localdir * *transform;
	OnShipHit* shipHit = new OnShipHit(target, dir, type, 0.5, 0.9);
	target->broadcastMessage(shipHit, true);
}

bool ShipManager::applyDamage(const ShipManager::ShipProjectile* projectile, Reference<ShipObject*>& ship, const Vector3& collisionPoint, const Vector<ManagedReference<SceneObject*>>& collidedObject) const {
	info("Collison with : " + collidedObject.get(0)->getDisplayedName() + " at " + collisionPoint.toString(), true);
	Vector3 reverse = (collisionPoint - projectile->startPosition);
	reverse.normalize();
	float health = ship->getChassisCurrentHealth();

	ShipObject* target = dynamic_cast<ShipObject*>(collidedObject.get(0).get());
	float min = ship->getComponentMinDamageMap()->get(ShipObject::WEAPON_COMPONENT_START + projectile->weaponIndex);
	float max = ship->getComponentMaxDamageMap()->get(ShipObject::WEAPON_COMPONENT_START + projectile->weaponIndex);
	float dmg = (System::getMTRand()->rand() * (max - min)) + min;
	// dmg *= 15;

	if (target != nullptr) {
		Locker locker(target);
		info("Damaging Ship for " + String::valueOf(dmg) + " damage", true);
		Vector3 right = target->getDirection()->toMatrix3()[2];
		float val = right.dotProduct(reverse);
		bool hitFront = val < 0;
		float shields = hitFront ? target->getFrontShield() : target->getRearShield();
		float armor = target->getCurrentArmorMap()->get(hitFront ? 4 : 5);
		float chassis = target->getChassisCurrentHealth();

		if (shields > 0.0f && dmg > 0.0f) {
			float prevHealth = target->getFrontShield() + target->getRearShield();
			float orig = shields;
			shields -= dmg;
			if (shields < 0) {
				dmg = shields * -1.0f;
				shields = 0.0f;
			} else {
				dmg = 0;
			}

			if (hitFront) {
				target->setFrontShield(shields, true);
			} else {
				target->setRearShield(shields, true);
			}
			float current = target->getFrontShield() + target->getRearShield();
			float max = target->getMaxFrontShield() + target->getMaxRearShield();

			target->info("Hit for " + String::valueOf(orig - shields) + " damage in the " + (hitFront ? "front" : "rear") + " shield", true);
			notifyShipHit(target, reverse, 0, current / max, prevHealth / max);
		}

		if (armor > 0.0f && dmg > 0.0f) {
			float prevHealth = target->getCurrentArmorMap()->get(4) + target->getCurrentArmorMap()->get(5);
			float max = target->getMaxArmorMap()->get(4) + target->getMaxArmorMap()->get(5);
			float orig = armor;
			armor -= dmg;
			if (armor < 0) {
				dmg = armor * -1.0f;
				armor = 0.0f;
			} else {
				dmg = 0;
			}
			// hitType = 1;
			// do armor damage
			DeltaMessage* delta = new DeltaMessage(target->getObjectID(), 'SHIP', 3);
			target->setComponentArmor(hitFront ? 4 : 5, armor, delta);
			delta->close();
			ship->broadcastMessage(delta, true);

			target->info("Hit for " + String::valueOf(orig - armor) + " damage in the " + (hitFront ? "front" : "rear") + " armor", true);
			float current = target->getCurrentArmorMap()->get(4) + target->getCurrentArmorMap()->get(5);
			notifyShipHit(target, reverse, 1, current / max, prevHealth / max);
		}

		float prev = 0.0f;
		float current = 0.0f;
		int slot = -1;
		if (doComponentDamage(target, collisionPoint, reverse, dmg, slot, prev, current)) {
			float total = ship->getMaxArmorMap()->get(slot) + ship->getMaxHitpointsMap()->get(slot);

			notifyShipHit(target, reverse, 2, current / total, current / prev);
		}

		if (target->getGameObjectType() != SceneObjectType::SHIPCAPITAL) {
			if (dmg > 0.0f && chassis > 0.0f) {
				float orig = chassis;
				chassis -= dmg;
				if (chassis < 0) {
					dmg = chassis * -1.0f;
					chassis = 0.0f;
				} else {
					dmg = 0.0f;
				}

				float max = target->getChassisMaxHealth();

				target->setCurrentChassisHealth(chassis);
				notifyShipHit(target, reverse, 3, chassis / max, orig / max);
				target->info("Hit for " + String::valueOf(orig - chassis) + " chassis damage", true);
			}
		}

		if (dmg > 0) {
			DestroyShipMessage* msg = new DestroyShipMessage(target->getObjectID(), (float)System::getMTRand()->rand());
			target->broadcastMessage(msg, true);
			target->destroyObjectFromWorld(true);
		}
	}
	return true;
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
		const ShipChassisData* data = new ShipChassisData(dtiff.getRow(i), columns);
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

void ShipManager::loadAiShipComponentData(ShipObject* ship) {
	if (ship == nullptr) {
		return;
	}

	auto shipTemp = dynamic_cast<SharedShipObjectTemplate*>(ship->getObjectTemplate());
	if (shipTemp == nullptr) {
		return;
	}

	const auto& componentNames = shipTemp->getComponentNames();
	if (componentNames.size() == 0) {
		return;
	}

	const auto& componentValues = shipTemp->getComponentValues();
	if (componentValues.size() == 0) {
		return;
	}

	auto appearanceData = getAppearanceData(shipTemp->getShipName());

	for (uint32 slot = 0; slot < Components::FIGHTERSLOTMAX; ++slot) {
		String slotName = componentSlotToString(slot);
		if (slotName == "") {
			continue;
		}

		String compName = componentNames.get(slotName);
		if (compName == "") {
			continue;
		}

		const auto& values = componentValues.get(slotName);
		if (values.size() == 0) {
			continue;
		}

		float hitPoints = Math::max(values.get("hitpoints"), 50.f);
		float armor = Math::max(values.get("armor"), 100.f);

		if (appearanceData != nullptr && !appearanceData->contains(compName)) {
			compName = appearanceData->getDefaultAppearance(slot);
		}

		ship->setComponentCRC(slot, compName.hashCode());
		ship->setComponentName(slot, compName);
		ship->setComponentHitpoints(slot, hitPoints);
		ship->setComponentMaxHitpoints(slot, hitPoints);
		ship->setComponentArmor(slot, armor);
		ship->setComponentMaxArmor(slot, armor);

		switch (slot) {
			case Components::REACTOR: {
				ship->setReactorGenerationRate(10000.0f);
				break;
			}
			case Components::ENGINE: {
				float speed = values.get("speed");
				float pitch = values.get("pitch") * Math::DEG2RAD;
				float yaw = values.get("yaw") * Math::DEG2RAD;
				float roll = values.get("roll") * Math::DEG2RAD;
				float pitchRate = values.get("pitchRate") * Math::DEG2RAD;
				float yawRate = values.get("yawRate") * Math::DEG2RAD;
				float rollRate = values.get("rollRate") * Math::DEG2RAD;
				float acceleration = values.get("acceleration");
				float deceleration = values.get("deceleration");
				ship->setEngineMaxSpeed(speed, false);
				ship->setEnginePitchAccelerationRate(pitch, false);
				ship->setEnginePitchRate(pitchRate, false);
				ship->setEngineYawAccelerationRate(yaw, false);
				ship->setEngineYawRate(yawRate, false);
				ship->setEngineRollAccelerationRate(roll, false);
				ship->setEngineRollRate(rollRate, false);
				ship->setEngineAccelerationRate(acceleration, false);
				ship->setEngineDecelerationRate(deceleration, false);
				break;
			}
			case Components::SHIELD0:
			case Components::SHIELD1: {
				float front = values.get("front");
				float back = values.get("back");
				float regen = values.get("regen");
				ship->setFrontShield(front, false);
				ship->setFrontShieldMax(front, false);
				ship->setRearShield(back, false);
				ship->setRearShieldMax(back, false);
				ship->setShieldRechargeRate(regen, false);
				break;
			}
			case Components::CAPACITOR: {
				float rechargeRate = values.get("rechargeRate");
				float energy = values.get("energy");
				ship->setCapacitorEnergy(energy, false);
				ship->setCapacitorMaxEnergy(energy, false);
				ship->setCapacitorRechargeRate(rechargeRate, false);
				break;
			}
			case Components::BOOSTER: {
				float rechargeRate = values.get("rechargeRate");
				float energy = values.get("energy");
				float accel = values.get("acceleration");
				float decel = values.get("deceleration");
				float speed = values.get("speed");
				float usage = values.get("energyUsage");
				float consumptionRate = values.get("energyConsumptionRate");
				ship->setBoosterRechargeRate(rechargeRate);
				ship->setBoosterEnergy(energy);
				ship->setBoosterEnergyConsumptionRate(usage);
				ship->setBoosterAcceleration(accel);
				ship->setBoosterMaxSpeed(speed);
				ship->setBoosterEnergyConsumptionRate(consumptionRate);
				break;
			}
			default: {
				if (slot >= Components::WEAPON_START) {
					float fireRate = values.get("rate");
					float drain = values.get("drain");
					float maxDamage = values.get("maxDamage");
					float minDamage = values.get("minDamage");
					float shieldEff = values.get("shieldEfficiency");
					float armorEff = values.get("armorEfficiency");
					float ammo = values.get("ammo");
					float ammoType = values.get("ammo_type");

					float totalEff = shieldEff + armorEff;
					if (totalEff < 1.f) {
						shieldEff += (1.f - totalEff) * 0.5f;
						armorEff += (1.f - totalEff) * 0.5f;
					}

					ship->setMaxDamage(slot, maxDamage);
					ship->setMinDamage(slot, maxDamage);
					ship->setRefireRate(fireRate, false);
					ship->setRefireEfficiency(drain, false);
					ship->setShieldEffectiveness(slot, shieldEff);
					ship->setArmorEffectiveness(slot, armorEff);
					ship->setCurrentAmmo(slot, ammo);
					ship->setMaxAmmo(slot, ammo);
					ship->setAmmoClass(slot, ammoType);
				}
				break;
			}
		};
	}
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

	for (uint32 slot = 0; slot < Components::FIGHTERSLOTMAX; slot++) {
		String slotName = componentSlotToString(slot);
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

ShipControlDevice* ShipManager::createShipControlDevice(ShipObject* ship) {
	String controlName = "object/intangible/ship/" + ship->getShipName().replaceAll("player_", "") + "_pcd.iff";

	auto shot = TemplateManager::instance()->getTemplate(controlName.hashCode());
	if (shot == nullptr || !(shot->getGameObjectType() & SceneObjectType::SHIPCONTROLDEVICE)) {
		return nullptr;
	}

	ManagedReference<ShipControlDevice*> control = ServerCore::getZoneServer()->createObject(controlName.hashCode(), ship->getPersistenceLevel()).castTo<ShipControlDevice*>();
	if (control == nullptr) {
		return nullptr;
	}

	Locker sLock(ship);
	Locker cLock(control, ship);

	if (control->transferObject(ship, PlayerArrangement::RIDER)) {
		control->setShipType(ship->getChassisCategory() == "pob" ? POBSHIP : FIGHTERSHIP);
		control->setControlledObject(ship);

		ship->setControlDeviceID(control->getObjectID());
		return control;
	}

	if (control != nullptr) {
		Locker sLock(control);
		control->destroyObjectFromDatabase(true);
	}

	return nullptr;
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

	ManagedReference<ShipObject*> ship = ServerCore::getZoneServer()->createObject(chassisName.hashCode(), persistence).castTo<ShipObject*>();
	if (ship == nullptr) {
		return nullptr;
	}

	if (loadComponents && !chassisName.contains("player")) {
		loadAiShipComponentData(ship);
	}

	return ship;
}

void ShipManager::createPlayerShip(CreatureObject* owner, const String& shipName, bool loadComponents) {
	ManagedReference<SceneObject*> dataPad = owner->getSlottedObject("datapad");
	if (dataPad == nullptr) {
		return;
	}

	PlayerObject* ghost = owner->getPlayerObject();
	if (ghost == nullptr) {
		return;
	}

	auto ship = createShip(shipName, 1, false);
	auto control = ship == nullptr ? nullptr : createShipControlDevice(ship);

	if (ship != nullptr && control != nullptr) {
		Locker sLock(ship);
		Locker cLock(control, ship);

		ship->createChildObjects();

		if (loadComponents) {
			loadShipComponentObjects(ship);
		}

		if (dataPad->transferObject(control, -1)) {
			ship->setOwner(owner);

			control->sendTo(owner, true);
			return;
		}
	}

	if (control != nullptr) {
		Locker cLock(control);
		control->destroyObjectFromDatabase(true);
	}

	if (ship != nullptr) {
		Locker sLock(ship);
		ship->destroyObjectFromDatabase(true);
	}
}
