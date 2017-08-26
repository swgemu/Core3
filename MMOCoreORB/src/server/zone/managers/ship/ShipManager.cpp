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
#include "server/zone/ZoneServer.h"

ShipManager::ShipManager() {
	loadShipComponentData();
    loadShipWeaponData();
    projectileThread = new ProjectileThread();
    projectileThread->start();
}

void ShipManager::checkProjectiles() {
    if (projectiles.size() == 0)
        return;

    Locker locker(&projectileMutex);
    for (int i=projectiles.size()-1; i >= 0; i--) {

        ShipProjectile* projectile = projectiles.get(i);
        if (projectile == NULL)
            break;

        Reference<ShipObject*> ship = projectile->getShip().get();

        if (ship == NULL) {
            delete projectile;
            projectiles.remove(i);
        }

        float dt = projectile->peekDelta();
        if (dt < .03f)
            continue;

        dt = projectile->getDelta();

        String name = ship->getComponentNameMap()->get(12+projectile->weaponIndex).toString();
        const ShipProjectileData* data = shipProjectileData.get(name.hashCode());
        Vector3 startPos = projectile->position;
        Vector3 dir = (projectile->direction - projectile->startPosition);
        dir.normalize();

        projectile->position = startPos + (dir * data->getSpeed() * dt);
        float dist = (projectile->position - projectile->startPosition).squaredLength();
        info("Updated projectile[" + String::valueOf(i) + "]: " + projectile->position.toString() + " dt: " + String::valueOf(dt), true);

        Vector3 collisionPoint;
        Vector<ManagedReference<SceneObject*> > collidedObject;

        if (CollisionManager::checkShipWeaponCollision(ship, startPos, projectile->position, collisionPoint, collidedObject)) {
            if (collidedObject.size() > 0) {
                info("Collison with : " + collidedObject.get(0)->getDisplayedName() + " at " + collisionPoint.toString(), true);
                Vector3 reverse = (collisionPoint - projectile->startPosition);
                reverse.normalize();
                float health = ship->getChassisCurrentHealth();

                ShipObject* target = dynamic_cast<ShipObject*>(collidedObject.get(0).get());
                float min = ship->getComponentMinDamageMap()->get(12+projectile->weaponIndex);
                float max = ship->getComponentMaxDamageMap()->get(12+projectile->weaponIndex);
                float dmg = (System::getMTRand()->rand() * (max-min)) + min;

                if (target != NULL) {
                    Locker locker(target);
                    info("Damaging Ship for " + String::valueOf(dmg) + " damage", true);
                    Vector3 right = target->getDirection()->toMatrix3()[2];
                    float val = right.dotProduct(reverse);
                    bool hitFront = val > 0;
                    float shields = hitFront ? target->getFrontShield() : target->getRearShield();
                    float armor = target->getCurrentArmorMap()->get(hitFront ? 4 : 5);
                    float chassis = target->getChassisCurrentHealth();
                    int hitType = 0;

                    if (shields > 0.0f && dmg > 0.0f) {
                        float orig = shields;
                        shields -= dmg;
                        if (shields < 0) {
                            dmg = shields * -1.0f;
                            shields = 0.0f;
                        } else {
                            dmg = 0;
                        }

                        if (hitFront) {
                            target->setFrontShield(shields, false);
                        }
                        target->info("Hit for " + String::valueOf(orig-shields) + " damage in the " + (hitFront ? "front" : "rear") + " shield", true);
                        //OnShipHit *shipHit = new OnShipHit(target, reverse, collisionPoint, hitType, shields, orig);
                        //ship->broadcastMessage(shipHit, true);
                    }

                    if (armor > 0.0f && dmg > 0.0f) {
                        float orig = armor;
                        armor -= dmg;//x:3550.77, y:-4931.46, z:73.2656)
                        if (armor < 0) {
                            dmg = armor * -1.0f;
                            armor = 0.0f;
                        } else {
                            dmg = 0;
                        }
                        //target->setComponentArmor(hitFront ? 4 : 5, armor);
                        hitType = 1;
                        // do armor damage
                        target->info("Hit for " + String::valueOf(orig-armor) + " damage in the " + (hitFront ? "front" : "rear") + " armor", true);

                        //OnShipHit *shipHit = new OnShipHit(target, reverse, collisionPoint, hitType, armor, orig);
                        //ship->broadcastMessage(shipHit, true);
                    }


                    if (dmg > 0.0f && chassis > 0.0f) {
                        float orig = chassis;
                        chassis -= dmg;
                        if (chassis < 0) {
                            dmg = chassis * -1.0f;
                            chassis = 0.0f;
                        } else {
                            dmg = 0.0f;
                        }

                        target->setCurrentChassisHealth(chassis);
                        hitType = 2;
                        target->info("Hit for " + String::valueOf(orig-chassis) + " chassis damage", true);

                    }
                    OnShipHit *shipHit = new OnShipHit(target, reverse, collisionPoint, hitType, chassis, 0.0f);
                    ship->broadcastMessage(shipHit, true);
                }
                delete projectile;
                projectiles.remove(i);
            }
        }

        if (dist > data->getSquaredRange()) {
            info("Projectile moving out of range", true);
            info("Final position: " + (projectile->startPosition + (dir * data->getRange())).toString(), true);
            delete projectile;
            projectiles.remove(i);
        }
    }
}

void ShipManager::loadShipComponentData() {
    IffStream* iffStream = DataArchiveStore::instance()->openIffFile(
            "datatables/space/ship_components.iff");

    if (iffStream == NULL) {
        fatal("datatables/space/ship_components.iff could not be found.");
        return;
    }

    DataTableIff dtiff;
    dtiff.readObject(iffStream);

    for (int i = 0; i < dtiff.getTotalRows(); ++i) {
        DataTableRow* row = dtiff.getRow(i);

        Reference<ShipComponentData*> component = new ShipComponentData();
        component->readObject(row);

        //info("loaded ship component " + component->getName() + " crc:0x" + String::hexvalueOf(int(component->getName().hashCode())), true);

        shipComponents.put(component->getName().hashCode(), component);
        shipComponentTemplateNames.put(component->getObjectTemplate(), component);
    }
    delete iffStream;
}

void ShipManager::loadShipWeaponData() {
    IffStream* iffStream = DataArchiveStore::instance()->openIffFile(
            "datatables/space/ship_weapon_components.iff");

    if (iffStream == NULL) {
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


ShipObject* ShipManager::generateShip(Reference<CreatureObject*> owner, String templateName) {
    ManagedReference<ShipObject*> ship = owner->getZoneServer()->createObject(String::hashCode(templateName), 1).castTo<ShipObject*>();
    return ship;
}
ShipObject* ShipManager::generateImperialNewbieShip(Reference<CreatureObject*> owner) {
    ZoneServer* server = owner->getZoneServer();
    ManagedReference<ShipObject*> ship = generateShip(owner, "object/ship/player/player_basic_z95.iff");

    ManagedReference<ShipReactorComponent*> reactor = server->createObject(STRING_HASHCODE("object/tangible/ship/components/reactor/rct_generic.iff")).castTo<ShipReactorComponent*>();
    {
        Locker locker(reactor);
        reactor->setHitpointsMax(135);
        reactor->setHitpoints(135);
        reactor->setArmorMax(70);
        reactor->setArmor(70);
        reactor->setReactorGenerationRate(10000);
        reactor->setMass(1320);
        ship->install(owner, reactor, 0, false);
    }

    ManagedReference<ShipCapacitorComponent*> capacitor = server->createObject(STRING_HASHCODE("object/tangible/ship/components/weapon_capacitor/cap_z95_basic.iff")).castTo<ShipCapacitorComponent*>();
    {
        Locker locker(capacitor);
        capacitor->setHitpointsMax(625);
        capacitor->setHitpoints(625);
        capacitor->setArmorMax(320);
        capacitor->setArmor(320);
        capacitor->setMass(1000);
        capacitor->setRechargeRate(20);
        capacitor->setCapacitorEnergy(500);
        ship->install(owner, capacitor, 6, false);
    }
    ManagedReference<ShipEngineComponent*> engine = server->createObject(STRING_HASHCODE("object/tangible/ship/components/engine/eng_z95_basic.iff")).castTo<ShipEngineComponent*>();
    {
        Locker locker(engine);
        engine->setHitpointsMax(150);
        engine->setHitpoints(150);
        engine->setArmorMax(75);
        engine->setArmor(75);
        engine->setMass(900);
        
        engine->setMaxSpeed(42);
        engine->setMaxPitch(45/57.2958f);
        engine->setMaxYaw(45/57.2958f);
        engine->setMaxRoll(45/57.2958f);
        engine->setEnergyCost(1500);
        ship->install(owner, engine, 1, false);
    }
    
    ManagedReference<ShipShieldComponent*> shield = server->createObject(STRING_HASHCODE("object/tangible/ship/components/shield_generator/shd_z95_basic.iff")).castTo<ShipShieldComponent*>();
    {
        Locker locker(shield);
        shield->setHitpointsMax(150);
        shield->setHitpoints(150);
        shield->setArmorMax(75);
        shield->setArmor(75);
        shield->setMass(1100);
        shield->setRechargeRate(1.45);
        shield->setFrontHitpoints(200);
        shield->setRearHitpoints(200);
        shield->setEnergyCost(2500);
        ship->install(owner, shield, 2, false);
        
    }
    ManagedReference<ShipArmorComponent*> armor0 = server->createObject(STRING_HASHCODE("object/tangible/ship/components/armor/armor_z95_basic.iff")).castTo<ShipArmorComponent*>();
    {
        Locker locker(armor0);
        armor0->setHitpointsMax(160);
        armor0->setHitpoints(160);
        armor0->setArmorMax(160);
        armor0->setArmor(160);
        armor0->setMass(900);
        ship->install(owner, armor0, 4, false);
    }
    ManagedReference<ShipArmorComponent*> armor1 = server->createObject(STRING_HASHCODE("object/tangible/ship/components/armor/armor_z95_basic.iff")).castTo<ShipArmorComponent*>();
    {
        Locker locker(armor1);
        armor1->setHitpointsMax(160);
        armor1->setHitpoints(160);
        armor1->setArmorMax(160);
        armor1->setArmor(160);
        armor1->setMass(900);
        ship->install(owner, armor1, 5, false);
    }
    ManagedReference<ShipWeaponComponent*> weapon = server->createObject(STRING_HASHCODE("object/tangible/ship/components/weapon/wpn_z95_basic.iff")).castTo<ShipWeaponComponent*>();
    {
        Locker locker(weapon);
        weapon->setHitpointsMax(150);
        weapon->setHitpoints(150);
        weapon->setArmorMax(75);
        weapon->setArmor(75);
        weapon->setMass(2000);
        weapon->setEnergyCost(1000);
        weapon->setMinDamage(300);
        weapon->setMaxDamage(400);
        weapon->setShieldEffectiveness(0.5f);
        weapon->setArmorEffectiveness(0.5f);
        weapon->setEnergyPerShot(20.0f);
        weapon->setRefireRate(0.34f);
        ship->install(owner, weapon, 12, false);
    }
    
    Locker locker(ship);
    ship->setShipName("player_basic_z95");
    ship->setChassisMaxHealth(1000.0f);
    ship->setCurrentChassisHealth(500.0f);
    return ship;
}
ShipObject* ShipManager::generateRebelNewbieShip(Reference<CreatureObject*> owner) {
    ManagedReference<ShipObject*> ship = generateShip(owner, "object/ship/player/player_basic_hutt_light.iff");
    return ship;
}
ShipObject* ShipManager::generateNeutralNewbieShip(Reference<CreatureObject*> owner) {
    ManagedReference<ShipObject*> ship = generateShip(owner, "object/ship/player/player_basic_tiefighter.iff");
    return ship;
}

