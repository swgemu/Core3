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
#include "server/zone/objects/ship/ComponentSlots.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/ship/ShipAppearanceData.h"

class ShipChassisData;

class ShipManager : public Singleton<ShipManager>, public Object, public Logger {
	/*class ProjectileThread : public Thread {
		void run() {
			while (true) {
				Logger::console.info(true) << "projectile thread ran";

				ShipManager::instance()->checkProjectiles();
				Thread::sleep(1000);
			}
		}
	};*/

	HashTable<uint32, Reference<ShipComponentData*>> shipComponents;
	HashTable<String, ShipComponentData*> shipComponentTemplateNames;
	HashTable<String, Reference<ShipAppearanceData*>> shipAppearanceData;
	HashTable<uint32, Reference<ShipProjectileData*>> shipProjectileData;
	HashTable<String, ShipProjectileData*> shipProjectiletTemplateNames;
	VectorMap<String, Vector3> hyperspaceLocations;
	VectorMap<String, String> hyperspaceZones;
	VectorMap<String, const ShipChassisData*> chassisData;
	VectorMap<String, String> componentFolders;
	Mutex projectileMutex;

	//ProjectileThread* projectileThread;

	void checkProjectiles();
	void loadShipComponentData();
	void loadShipWeaponData();
	void loadShipChassisData();
	void loadHyperspaceLocations();
	void loadShipAppearanceData();

	bool doComponentDamage(ShipObject* ship, const Vector3& collisionPoint, const Vector3& direction, float& damage, int& slot, float& previous, float& current) const;

public:
	enum {
		SHIP = 0,
		FIGHTERSHIP = 1,
		POBSHIP = 2,
		SPACESTATION = 3
	};

	ShipManager() {
		setLoggingName("ShipManager");
		setGlobalLogging(false);
		setLogging(false);
	};

	void initialize();

	static void notifyShipHit(ShipObject* target, const Vector3& localDir, int type, float curHealth, float prevHealth);

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
		if (name.contains(".iff")) {
			return shipComponentTemplateNames.get(name);
		}

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

	const ShipChassisData* getChassisData(String shipName) {
		return chassisData.get(shipName);
	}

	const ShipAppearanceData* getAppearanceData(const String& shipName) const {
		return shipAppearanceData.get(shipName);
	}

	class ShipProjectile : public Object {
	protected:
		ManagedReference<ShipObject*> ship;
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
			speed = projectileSpeed;
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

		ManagedReference<ShipObject*>& getShip() {
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

	bool applyDamage(const ShipProjectile* projectile, Reference<ShipObject*>& ship, const Vector3& collisionPoint, const Vector<ManagedReference<SceneObject*>>& collidedObject) const;

	bool damageComponent(ShipObject* ship, float& damage, int closestSlot, const Vector3& direction) const;

	void loadAiShipComponentData(ShipObject* ship);

	void loadShipComponentObjects(ShipObject* ship);

	ShipControlDevice* createShipControlDevice(ShipObject* ship);

public:
	ShipObject* createShip(const String& shipName, int persistence = 0, bool loadComponents = true);

	void createPlayerShip(CreatureObject* owner, const String& shipName, bool loadComponents = true);

	String componentSlotToString(int slot) {
		switch (slot) {
			case Components::REACTOR: return "reactor";
			case Components::ENGINE: return "engine";
			case Components::SHIELD0: return "shield_0";
			case Components::SHIELD1: return "shield_1";
			case Components::ARMOR0: return "armor_0";
			case Components::ARMOR1: return "armor_1";
			case Components::CAPACITOR: return "capacitor";
			case Components::BOOSTER: return "booster";
			case Components::DROID_INTERFACE: return "droid_interface";
			case Components::BRIDGE: return "bridge";
			case Components::HANGAR: return "hangar";
			case Components::TARGETING_STATION: return "targeting_station";
			default: {
				if (slot >= Components::WEAPON_START && slot <= 99) {
					return "weapon_" + String::valueOf(slot - Components::WEAPON_START);
				} else {
					return "";
				}
			}
		}
	}
};


#endif /* SHIPMANAGER_H_ */
