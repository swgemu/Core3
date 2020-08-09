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
#include "server/zone/objects/ship/components/ShipWeaponComponent.h"
#include "server/zone/objects/ship/components/ShipShieldComponent.h"
#include "server/zone/objects/ship/components/ShipEngineComponent.h"
#include "server/zone/objects/ship/components/ShipCapacitorComponent.h"
#include "server/zone/objects/ship/components/ShipReactorComponent.h"
#include "server/zone/objects/ship/components/ShipArmorComponent.h"
#include "server/zone/objects/ship/components/ShipBoosterComponent.h"
#include "server/zone/objects/ship/ShipChassisData.h"
#include "server/ServerCore.h"
#include "server/zone/ZoneServer.h"
#include "templates/tangible/SharedShipObjectTemplate.h"
#include "server/zone/objects/ship/ComponentSlots.h"
#include "server/zone/packets/ship/DestroyShipMessage.h"


ShipManager::ShipManager() {
    loadShipChassisData();
	loadShipComponentData();
    loadShipWeaponData();
    loadHyperspaceLocations();
    projectileThread = new ProjectileThread();
    projectileThread->start();
}

void ShipManager::checkProjectiles() {
    if (projectiles.size() == 0)
        return;

    Locker locker(&projectileMutex);
    for (int i=projectiles.size()-1; i >= 0; i--) {

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
        info("Updated projectile[" + String::valueOf(i) + "]: " + startPos.toString() + "-->" + projectile->position.toString() + " dt: " + String::valueOf(dt), true);

        Vector3 collisionPoint;
        Vector<ManagedReference<SceneObject*> > collidedObject;

        if (CollisionManager::checkShipWeaponCollision(ship, startPos, projectile->position, collisionPoint, collidedObject)) {
            if (collidedObject.size() > 0) {
				applyDamage(projectile, ship, collisionPoint, collidedObject);

				delete projectile;
                projectiles.remove(i);
				continue;
            }
        }

        if (dist > projectile->rangeSq) {
            info("Projectile moving out of range", true);
            info("Final position: " + (projectile->startPosition + (dir * projectile->range)).toString(), true);
            delete projectile;
            projectiles.remove(i);
			continue;
        }
    }
}

bool ShipManager::doComponentDamage(ShipObject* ship, const Vector3& collisionPoint, const Vector3& direction, float& damage, int& slot, float& previousHealth, float& currentHealth) const {
	const auto& componentCRCs = ship->getShipComponentMap();

	const ShipChassisData* chassis = chassisData.get(ship->getShipName());
	const AppearanceTemplate *appr = ship->getObjectTemplate()->getAppearanceTemplate();
	const VectorMap<String, Matrix4>& hardpointTransforms = appr->getHardpoints();
	int closestSlot = -1;
	float closestDistance = FLT_MAX;

	if (appr == nullptr || chassis == nullptr || componentCRCs->size() == 0)
		return false;

	Vector<int> activeComponents;
	const auto& hitpoints = ship->getCurrentHitpointsMap();
	for (int i=0; i<componentCRCs->size(); i++) {
		int crc32 = componentCRCs->getValueAt(i);
		int slot = componentCRCs->getKeyAt(i);
		const ShipComponentData *componentData = getShipComponent(crc32);
		const String& name = componentData->getName();
		const ShipChassisData::ComponentSlotData *slotData = chassis->getComponentSlotData(slot);
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
			int slot = System::random(activeComponents.size()-1);
			damageComponent(ship, damage, slot, direction);
			if (damage > 0) // component was completely destroyed if we still have damage left over
				activeComponents.remove(slot);
		}
	}

	return false;
}

bool ShipManager::damageComponent(ShipObject *ship, float &damage, int closestSlot, const Vector3& direction) const {
	float currentHealth;
	float previousHealth;
	DeltaMessage *delta = new DeltaMessage(ship->getObjectID(), 'SHIP', 3);
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
			if (!(flags & 0x08)) {
				flags |= 0x08;
				ship->setComponentOptions(closestSlot, flags, delta);
			}
		}

	if (doUpdate) {
			previousHealth = total;
			currentHealth = armor + health;
			delta->close();
			ship->broadcastMessage(delta, true);
			notifyShipHit(ship, direction, 2, currentHealth/total, previousHealth/total);
			return true;
		} else {
			delete delta;
		}
	return false;
}

void ShipManager::notifyShipHit(ShipObject *target, const Vector3& localdir, int type, float curHealth, float prevHealth) {
	Matrix4 transform = CollisionManager::getTransformMatrix(target);
	Vector3 dir = localdir * transform;
	OnShipHit *shipHit = new OnShipHit(target, dir, type, 0.5, 0.9);
	target->broadcastMessage(shipHit, true);
}


bool ShipManager::applyDamage(const ShipManager::ShipProjectile *projectile, Reference<ShipObject *> &ship,
								  const Vector3 &collisionPoint,
								  const Vector<ManagedReference<SceneObject *>> &collidedObject) const {
	info("Collison with : " + collidedObject.get(0)->getDisplayedName() + " at " + collisionPoint.toString(), true);
	Vector3 reverse = (collisionPoint - projectile->startPosition);
	reverse.normalize();
	float health = ship->getChassisCurrentHealth();



	ShipObject* target = dynamic_cast<ShipObject*>(collidedObject.get(0).get());
	float min = ship->getComponentMinDamageMap()->get(ShipObject::WEAPON_COMPONENT_START+projectile->weaponIndex);
	float max = ship->getComponentMaxDamageMap()->get(ShipObject::WEAPON_COMPONENT_START+projectile->weaponIndex);
	float dmg = (System::getMTRand()->rand() * (max - min)) + min;
	//dmg *= 15;

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
			notifyShipHit(target, reverse, 0, current/max, prevHealth/max);
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
			//hitType = 1;
			// do armor damage
			DeltaMessage *delta = new DeltaMessage(target->getObjectID(), 'SHIP', 3);
			target->setComponentArmor(hitFront ? 4 : 5, armor, delta);
			delta->close();
			ship->broadcastMessage(delta, true);

			target->info("Hit for " + String::valueOf(orig - armor) + " damage in the " + (hitFront ? "front" : "rear") + " armor", true);
			float current = target->getCurrentArmorMap()->get(4) + target->getCurrentArmorMap()->get(5);
			notifyShipHit(target, reverse, 1, current/max, prevHealth/max);
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
				notifyShipHit(target, reverse, 3, chassis/max, orig/max);
				target->info("Hit for " + String::valueOf(orig - chassis) + " chassis damage", true);
			}
		}

		if (dmg > 0) {
			DestroyShipMessage *msg = new DestroyShipMessage(target->getObjectID(), (float)System::getMTRand()->rand());
			target->broadcastMessage(msg, true);
			target->destroyObjectFromWorld(true);
		}
	}
	return true;
}

void ShipManager::loadHyperspaceLocations() {
    IffStream* iffStream = DataArchiveStore::instance()->openIffFile(
            "datatables/space/hyperspace/hyperspace_locations.iff");

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

        Reference<ShipComponentData*> component = new ShipComponentData();
        component->readObject(row);

		shipComponents.put(component->getName().hashCode(), component);
        shipComponentTemplateNames.put(component->getObjectTemplate(), component);
    }
    delete iffStream;
}


void ShipManager::loadShipChassisData() {
    IffStream* iffStream = DataArchiveStore::instance()->openIffFile(
            "datatables/space/ship_chassis.iff");

    if (iffStream == nullptr) {
        fatal("datatables/space/ship_chassis.iff could not be found.");
        return;
    }

    DataTableIff dtiff;
    dtiff.readObject(iffStream);

	Vector<String> columns(dtiff.getTotalColumns(), 3);
	for (int i=0; i<dtiff.getTotalColumns(); i++) {
		columns.add(dtiff.getColumnNameByIndex(i));
		info("Column: " + columns.get(i), true);
	}

    for (int i = 0; i < dtiff.getTotalRows(); ++i) {
        const ShipChassisData *data = new ShipChassisData(dtiff.getRow(i), columns);
        chassisData.put(data->getName(), data);
    }
    delete iffStream;
}

void ShipManager::loadShipWeaponData() {
    IffStream* iffStream = DataArchiveStore::instance()->openIffFile(
            "datatables/space/ship_weapon_components.iff");

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
}


ShipObject* ShipManager::generateShip(String templateName) {
	const static char* components[] = {"reactor", "engine", "shield_0", "shield_1", "armor_0", "armor_1", "capacitor", "booster", "droid_interface", "bridge", "hangar",
									   "targeting_station","weapon_0", "weapon_1", "weapon_2", "weapon_3", "weapon_4", "weapon_5","weapon_6", "weapon_7"};
	const int numComponents = 20;

    ManagedReference<ShipObject*> ship = ServerCore::getZoneServer()->createObject(String::hashCode(templateName), 1).castTo<ShipObject*>();
    Locker locker(ship);
    ship->createChildObjects();

	SharedObjectTemplate *shot = ship->getObjectTemplate();
	shot->getAppearanceTemplate(); // force appearance to load

	ZoneServer* server = ServerCore::getZoneServer();

	SharedShipObjectTemplate *tmpl = (SharedShipObjectTemplate*)ship->getObjectTemplate();
	if (tmpl == nullptr)
		return nullptr;

	const VectorMap<String, String>& componentNames = tmpl->getComponentNames();
	const VectorMap<String, VectorMap<String, float>>& componentValues = tmpl->getComponentValues();
	const ShipChassisData *data = chassisData.get(ship->getShipName());

	for (int i = 0; i < 20; i++) {
		String k = components[i];
		if (componentValues.contains(k)) {
			const VectorMap<String, float> values = componentValues.get(k);
			float hitpoints = values.get("hitpoints");
			float armor = values.get("armor");
			const String& componentName = componentNames.get(k);
			const ShipComponentData *componentData = getShipComponent(componentName);
			const ShipChassisData::ComponentSlotData *slotData = data->getComponentSlotData(i);
			const auto& hardpoints = slotData->getHardpoint(componentName);
			float range = 0.0f;
			if (hardpoints.size() > 0) {
				const ShipChassisData::ComponentHardpoint *hardpoint = hardpoints.get(0);
				range = hardpoint->getRange();
			}
			if (componentData == nullptr)
				Logger::console.fatal("NULL component data for " + componentName);

			String templateName = componentData->getSharedObjectTemplate().replaceFirst("shared_", "");

			Logger::console.info("Attempting to load component: " + componentName, true);
			if (componentName == "bdg_generic" ||componentName == "hgr_generic") { // These aren't real components
				ship->setComponentCRC(i, componentName.hashCode());
				continue;
			}

			ManagedReference<ShipComponent*> shipComponent = server->createObject(templateName.hashCode()).castTo<ShipComponent*>();
			if (shipComponent == nullptr) {
				ship->error("Failed to create component " + componentName);
				continue;
			}
			Locker locker(shipComponent);
			if (hitpoints > 0) {
				shipComponent->setHitpointsMax(hitpoints);
				shipComponent->setHitpoints(hitpoints);
			}

			if (armor > 0) {
				shipComponent->setArmorMax(armor);
				shipComponent->setArmor(armor);
			}
			shipComponent->setComponentDataName(componentData->getName());
			shipComponent->setCollisionRange(range);
			//shipComponent->setName(componentName);

			switch (i) {
				case Components::REACTOR: {
					ShipReactorComponent *reactor = shipComponent.castTo<ShipReactorComponent*>();
					Locker locker(reactor);
					reactor->setReactorGenerationRate(10000.0f);
					break;
				}
				case Components::ENGINE: {
					ShipEngineComponent* engine = shipComponent.castTo<ShipEngineComponent*>();
					float speed = values.get("speed");
					float pitch = values.get("pitch");
					float roll = values.get("roll");
					float yaw = values.get("yaw");
					float pitchRate = values.get("pitchRate");
					float rollRate = values.get("rollRate");
					float yawRate = values.get("yawRate");
					float accel = values.get("acceleration");
					float decel = values.get("deceleration");
					engine->setMaxSpeed(speed);
					engine->setMaxPitch(pitch/57.2958f);
					engine->setMaxYaw(yaw/57.2958f);
					engine->setMaxRoll(roll/57.2958f);
					engine->setMaxAcceleration(accel);
					engine->setMaxDeceleration(decel);
					// TODO: FIXME
					break;
				}
				case Components::SHIELD0:
				case Components::SHIELD1: {
					ShipShieldComponent *shield = shipComponent.castTo<ShipShieldComponent*>();
					float front = values.get("front");
					float back = values.get("back");
					float regen = values.get("regen");
					shield->setFrontHitpoints(front);
					shield->setRearHitpoints(back);
					shield->setRechargeRate(regen);
					break;
				}
				case Components::ARMOR0:
				case Components::ARMOR1:
					break;
				case Components::CAPACITOR: {
					ShipCapacitorComponent *capacitor = shipComponent.castTo<ShipCapacitorComponent*>();
					float rechargeRate = values.get("rechargeRate");
					float energy = values.get("energy");
					capacitor->setRechargeRate(rechargeRate);
					capacitor->setCapacitorEnergy(energy);
					break;
				}
				case Components::BOOSTER: {
					ShipBoosterComponent *booster = shipComponent.castTo<ShipBoosterComponent*>();
					float rechargeRate = values.get("rechargeRate");
					float energy = values.get("energy");
					float accel = values.get("acceleration");
					float decel = values.get("deceleration");
					float speed = values.get("speed");
					booster->setBoosterRechargeRate(rechargeRate);
					booster->setBoosterEnergy(energy);
					booster->setBoosterAcceleration(accel);
					booster->setBoosterSpeed(speed);
					// TODO: FIXME TOO
					break;
				}
				default: {
					if (i >= Components::WEAPON_START) {
						ShipWeaponComponent *weapon = shipComponent.castTo<ShipWeaponComponent *>();
						float fireRate = values.get("rate");
						float drain = values.get("drain");
						float maxDamage = values.get("maxDamage");
						float minDamage = values.get("minDamage");
						float sEfficiency = values.get("shieldEfficiency");
						float aEfficiency = values.get("armorEfficiency");
						float ammo = values.get("ammo");
						float ammo_type = values.get("ammo_type");
						weapon->setRefireRate(fireRate);
						weapon->setEnergyPerShot(drain);
						weapon->setMinDamage(minDamage);
						weapon->setMaxDamage(maxDamage);
						if (sEfficiency > 0.001f)
							weapon->setShieldEffectiveness(sEfficiency);
						if (aEfficiency > 0.001f)
							weapon->setArmorEffectiveness(aEfficiency);
						//TODO: AMMO
					}
					break;
				}
			};
			ship->install(NULL, shipComponent, i, false);
			ship->setComponentTargetable(i, slotData->isTargetable());
		}
	}
    return ship;
}

ShipObject* ShipManager::generateImperialNewbieShip(Reference<CreatureObject*> owner) {
    ManagedReference<ShipObject*> ship = generateShip("object/ship/player/player_prototype_tiefighter.iff");
    ZoneServer* server = ServerCore::getZoneServer();
    Locker locker(ship);
    ship->setChassisMaxHealth(1000.0f);
    ship->setCurrentChassisHealth(1000.0f);
    ship->setOwner(owner);

    return ship;
}
ShipObject* ShipManager::generateRebelNewbieShip(Reference<CreatureObject*> owner) {
    //ManagedReference<ShipObject*> ship = generateShip("object/ship/star_destroyer.iff");
	ManagedReference<ShipObject*> ship = generateShip("object/ship/player/player_basic_z95.iff");
	Locker locker(ship);
	ship->setChassisMaxHealth(1000.0f);
	ship->setCurrentChassisHealth(1000.0f);
	ship->setOwner(owner);
    return ship;
}
ShipObject* ShipManager::generateNeutralNewbieShip(Reference<CreatureObject*> owner) {
    ManagedReference<ShipObject*> ship = generateShip("object/ship/player/player_basic_hutt_light.iff");
	Locker locker(ship);
	ship->setChassisMaxHealth(1000.0f);
	ship->setCurrentChassisHealth(1000.0f);
	ship->setOwner(owner);
    return ship;
}

