/*
 * ShipManager.h
 *
 *  Created on: 18/10/2013
 *      Author: victor
 */

#ifndef SHIPMANAGER_H_
#define SHIPMANAGER_H_

#include "server/zone/objects/ship/ShipComponentData.h"
#include "server/zone/objects/ship/ShipProjectileData.h"

#include "server/zone/objects/ship/ShipObject.h"

class ShipChassisData;

class ShipManager : public Singleton<ShipManager>, public Object, public Logger {
	class ProjectileThread : public Thread {
		void run() {
			while(true) {
				ShipManager::instance()->checkProjectiles();
				Thread::sleep(5);
			}
		}
	};
	HashTable<uint32, Reference<ShipComponentData*> > shipComponents;
    HashTable<String, ShipComponentData*> shipComponentTemplateNames;

    HashTable<uint32, Reference<ShipProjectileData*> > shipProjectileData;
    HashTable<String, ShipProjectileData*> shipProjectiletTemplateNames;
	VectorMap<String, Vector3> hyperspaceLocations;
    VectorMap<String, String> hyperspaceZones;
	VectorMap<String, const ShipChassisData*> chassisData;
	VectorMap<String, String> componentFolders;
    Mutex projectileMutex;

	ProjectileThread *projectileThread;
	void checkProjectiles();
    void loadShipComponentData();
    void loadShipWeaponData();
	void loadShipChassisData();
	void loadHyperspaceLocations();
	bool doComponentDamage(ShipObject* ship, const Vector3& collisionPoint, const Vector3& direction, float& damage, int& slot, float& previous, float& current) const;
public:
	ShipManager();

	static void notifyShipHit(ShipObject *target, const Vector3& localDir, int type, float curHealth, float prevHealth);

	bool hyperspaceLocationExists(const String& name) const {
		return hyperspaceLocations.contains(name) && hyperspaceZones.contains(name);
	}

	const Vector3& getHyperspaceLocation(const String& name) const {
		return hyperspaceLocations.get(name);
	}

    const String& getHyperspaceZone(const String& name) const {
        return hyperspaceZones.get(name);
    }

	const ShipComponentData* getShipComponent(const String& name) const {
		return shipComponents.get(name.hashCode());
	}

	const ShipComponentData* getShipComponent(uint32 hash) const {
		return shipComponents.get(hash);
	}
    
    ShipComponentData* getShipComponentFromTemplate(String templateName) {
        return shipComponentTemplateNames.get(templateName);
    }

	ShipProjectileData* getProjectileData(uint32 hash) {
		return shipProjectileData.get(hash);
	}
    ShipObject* generateShip(String templateName);
    ShipObject* generateImperialNewbieShip(Reference<CreatureObject*> owner);
    ShipObject* generateRebelNewbieShip(Reference<CreatureObject*> owner);
    ShipObject* generateNeutralNewbieShip(Reference<CreatureObject*> owner);

	class ShipProjectile : public Object {
    protected:
		WeakReference<ShipObject*> ship;
		uint8 weaponIndex;
		uint8 projectileType;
		uint8 componentIndex;
        uint64 lastUpdate;
        Vector3 startPosition;
		Vector3 position;
		Vector3 direction;
		float speed;
		float range;
		float rangeSq;
	public:
		ShipProjectile(Reference<ShipObject*> ship, uint8 weapon, uint8 projectile, uint8 component, Vector3 start, Vector3 end, float projectileSpeed, float projectileRange, long time) {
			this->ship = ship;
			weaponIndex = weapon;
			projectileType = projectile;
			componentIndex = component;
			startPosition = position = start;
			direction = end;
			speed=projectileSpeed;
			range = projectileRange;
			rangeSq = range * range;
			lastUpdate = time;
		}

		float peekDelta() {
			return (System::getMiliTime() - lastUpdate) / 1000.0f;
		}
        float getDelta() {
            uint64 current = System::getMiliTime();
            uint64 temp = lastUpdate;

            lastUpdate = current;
            return (current - temp) / 1000.0f;
        }

        WeakReference<ShipObject*>& getShip() {
            return ship;
        }

        friend class ShipManager;
	};

	void addProjectile(ShipProjectile* projectile) {
        Locker locker(&projectileMutex);
		projectiles.add(projectile);
	}

private:
	Vector<ShipProjectile*> projectiles;

	bool applyDamage(const ShipProjectile *projectile, Reference<ShipObject *> &ship, const Vector3 &collisionPoint,
						 const Vector<ManagedReference<SceneObject *>> &collidedObject) const;

	bool damageComponent(ShipObject *ship, float &damage, int closestSlot, const Vector3& direction) const;
};

#endif /* SHIPMANAGER_H_ */
