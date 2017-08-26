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
    Mutex projectileMutex;

	ProjectileThread *projectileThread;
	void checkProjectiles();
    void loadShipComponentData();
    void loadShipWeaponData();
public:
	ShipManager();

	ShipComponentData* getShipComponent(const String& name) {
		return shipComponents.get(name.hashCode());
	}

	ShipComponentData* getShipComponent(uint32 hash) {
		return shipComponents.get(hash);
	}
    
    ShipComponentData* getShipComponentFromTemplate(String templateName) {
        return shipComponentTemplateNames.get(templateName);
    }


    
    ShipObject* generateShip(Reference<CreatureObject*> owner, String templateName);
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
	public:
		ShipProjectile(Reference<ShipObject*> ship, uint8 weapon, uint8 projectile, uint8 component, Vector3 start, Vector3 end, long time) {
			this->ship = ship;
			weaponIndex = weapon;
			projectileType = projectile;
			componentIndex = component;
			startPosition = position = start;
			direction = end;
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
};

#endif /* SHIPMANAGER_H_ */
