#ifndef SHIPPROJECTILEVECTOR_H_
#define SHIPPROJECTILEVECTOR_H_

#include "engine/engine.h"
#include "ShipProjectile.h"
#include "server/zone/objects/ship/ShipObject.h"

class ShipProjectileMapEntry : public Object {
private:
	ManagedWeakReference<ShipObject*> shipRef;
	Vector<ShipProjectile*> projectileVector;

public:
	ShipProjectileMapEntry() : Object() {

	}

	~ShipProjectileMapEntry() {
		for (int i = projectileVector.size(); -1 > --i;) {
			remove(i);
		}
	}

	ShipProjectileMapEntry(ShipObject* ship) : Object() {
		shipRef = ship;
	}

	ShipObject* getShip() {
		return shipRef.get().get();
	}

	ShipProjectile* getProjectile(int index) {
		if (projectileVector.size() > index) {
			return projectileVector.get(index);
		}

		return nullptr;
	}

	void add(ShipProjectile* projectile) {
		projectileVector.add(projectile);
	}

	void remove(int index) {
		if (projectileVector.size() > index) {
			auto entry = projectileVector.get(index);

			if (entry != nullptr) {
				delete entry;
				entry = nullptr;
			}

			projectileVector.remove(index);
		}
	}

	int size() const {
		return projectileVector.size();
	}
};

class ShipProjectileMap {
private:
	VectorMap<uint64, ShipProjectileMapEntry> projectileMap;
	mutable ReadWriteLock sync;

public:
	ShipProjectileMap() {
		projectileMap.setNoDuplicateInsertPlan();
	}

	ShipObject* getShip(int mapIndex) {
		ReadLocker lock(&sync);

		if (projectileMap.size() > mapIndex) {
			return projectileMap.elementAt(mapIndex).getValue().getShip();
		}

		return nullptr;
	}

	ShipProjectileMapEntry* getEntry(int mapIndex) {
		ReadLocker lock(&sync);

		if (projectileMap.size() > mapIndex) {
			return &projectileMap.elementAt(mapIndex).getValue();
		}

		return nullptr;
	}

	ShipProjectileMapEntry* getEntry(ShipObject* ship) {
		ReadLocker lock(&sync);

		uint64 objectID = ship->getObjectID();
		int index = projectileMap.find(objectID);

		if (index != -1) {
			return getEntry(index);
		}

		return nullptr;
	}

	ShipProjectile* getProjectile(int mapIndex, int entryIndex) {
		ReadLocker lock(&sync);

		auto entry = getEntry(mapIndex);

		if (entry != nullptr) {
			return entry->getProjectile(entryIndex);
		}

		return nullptr;
	}

	void addProjectile(ShipObject* ship, ShipProjectile* projectile) {
		Locker lock(&sync);

		uint64 objectID = ship->getObjectID();
		int index = projectileMap.find(objectID);

		if (index == -1) {
			auto element = VectorMapEntry<uint64, ShipProjectileMapEntry>(objectID, ShipProjectileMapEntry(ship));
			projectileMap.add(std::move(element));
			index = projectileMap.size() - 1;
		}

		auto entry = getEntry(index);

		if (entry != nullptr) {
			entry->add(projectile);
		}
	}

	void removeProjectile(int mapIndex, int entryIndex) {
		Locker lock(&sync);

		auto entry = getEntry(mapIndex);

		if (entry != nullptr) {
			entry->remove(entryIndex);
		}
	}

	void removeShip(int mapIndex) {
		Locker lock(&sync);

		if (projectileMap.size() > mapIndex) {
			auto entry = getEntry(mapIndex);
			if (entry == nullptr) {
				return;
			}

			for (int i = 0; i < entry->size(); ++i) {
				entry->remove(i);
			}

			projectileMap.remove(mapIndex);
		}
	}

	int entrySize(int mapIndex) const {
		ReadLocker lock(&sync);

		if (projectileMap.size() > mapIndex) {
			return projectileMap.elementAt(mapIndex).getValue().size();
		}

		return 0;
	}

	int mapSize() const {
		ReadLocker lock(&sync);

		return projectileMap.size();
	}
};

#endif // SHIPPROJECTILE_H_
