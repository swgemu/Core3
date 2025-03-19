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
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/objects/ship/ComponentSlots.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/ship/ShipAppearanceData.h"
#include "server/zone/objects/ship/ShipCollisionData.h"
#include "server/zone/objects/ship/ShipMissileData.h"
#include "server/zone/objects/ship/ShipCountermeasureData.h"
#include "server/zone/objects/ship/components/ShipChassisComponent.h"
#include "server/zone/objects/ship/ShipTurretData.h"
#include "server/zone/managers/ship/DroidCommandData.h"
#include "ShipUniqueIdMap.h"
#include "SpaceSpawnGroup.h"

namespace server {
namespace zone {
namespace managers {
namespace ship {

class ShipManager : public Singleton<ShipManager>, public Object, public Logger {
private:
	class ShipAiAgentUpdateTransformTask: public Task, public Logger {
	protected:
		Vector<ManagedWeakReference<ShipObject*>> uniqueIdMapCopy;
		Reference<ShipManager*> shipManagerRef;
		int64 iteration;

	public:
		const static int INTERVALMAX = 200;
		const static int INTERVALMIN = 100;
		const static int PRIORITYMAX = 5;

		ShipAiAgentUpdateTransformTask(ShipManager* shipManager) : Task() {
			setLoggingName("UpdateShipAiAgentTransformTask");

			shipManagerRef = shipManager;
			iteration = 0;
		}

		void run() {
			auto shipManager = shipManagerRef.get();

			if (shipManager == nullptr) {
				return;
			}

			int64 startTime = System::getMiliTime();

			try {
			int priority = ++iteration % PRIORITYMAX;

			if (priority == 0) {
				const auto uniqueIdMap = shipManager->getShipUniqueIdMap();

				if (uniqueIdMap == nullptr) {
					return;
				}

				uniqueIdMap->safeCopyTo(uniqueIdMapCopy);
			}

			for (int i = 0; i < uniqueIdMapCopy.size(); ++i) {
				auto ship = uniqueIdMapCopy.get(i).get();

				if (ship == nullptr || !ship->isShipAiAgent()) {
					continue;
				}

				auto agent = ship->asShipAiAgent();

				if (agent == nullptr) {
					continue;
				}

				Locker lock(agent);

				bool lightUpdate = (i % PRIORITYMAX) != priority;
				agent->updateTransform(lightUpdate);
			}
			} catch (...) {
			}

			int64 deltaTime = System::getMiliTime() - startTime;
			int64 interval = Math::max(INTERVALMAX - deltaTime, (int64)INTERVALMIN);

			reschedule(interval);
		}
	};

protected:
	Reference<Lua*> lua;

	HashTable<uint32, Reference<ShipComponentData*>> shipComponents;
	HashTable<String, ShipComponentData*> shipComponentTemplateNames;
	HashTable<String, Reference<ShipAppearanceData*>> shipAppearanceData;
	HashTable<uint32, Reference<ShipProjectileData*>> shipProjectileData;
	HashTable<String, ShipProjectileData*> shipProjectiletTemplateNames;
	HashTable<uint32, Reference<ShipCollisionData*>> shipCollisionData;
	HashTable<String, Reference<ShipChassisData*>> chassisData;

	HashTable<uint32, Reference<ShipMissileData*>> missileData;
	HashTable<uint32, Reference<ShipCountermeasureData*>> countermeasureData;
	VectorMap<String, VectorMap<uint32, Reference<ShipTurretData*>>> turretData;

	VectorMap<String, Vector3> hyperspaceLocations;
	VectorMap<String, String> hyperspaceZones;

	HashTable<uint32, Reference<SpaceSpawnGroup*>> spawnGroupMap;

	HashTable<uint32, Reference<DroidCommandData*>> DroidCommands;

	ShipUniqueIdMap shipUniqueIdMap;
	ShipAiAgentUpdateTransformTask* updateTransformTask;

	void checkProjectiles();
	void loadShipComponentData();
	void loadShipWeaponData();
	void loadShipChassisData();
	void loadHyperspaceLocations();
	void loadShipAppearanceData();
	void loadShipMissileData();
	void loadShipCountermeasureData();
	void loadShipCollisionData();
	void loadShipTurretIffData();
	void loadShipTurretLuaData();
	void loadDroidCommands();

public:
	enum {
		SHIP = 0,
		FIGHTERSHIP = 1,
		POBSHIP = 2,
		SPACESTATION = 3
	};

	const static int NO_CERT_COST_MULTI = 5;

	enum LUA_ERROR_CODE {
		NO_ERROR = 0,
		GENERAL_ERROR,
		DUPLICATE_SHIP_MOBILE,
		INCORRECT_ARGUMENTS,
		DUPLICATE_CONVO
	};

	static int ERROR_CODE;

	ShipManager();
	virtual ~ShipManager() {};

	void initialize();
	void stop();

	static int checkArgumentCount(lua_State* L, int args);
	static int includeFile(lua_State* L);
	static int addShipSpawnGroup(lua_State* L);

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

	const ShipComponentData* getShipComponentFromTemplate(const String& templateName) const {
		return shipComponentTemplateNames.get(templateName);
	}

	const ShipProjectileData* getProjectileData(uint32 hash) const {
		return shipProjectileData.get(hash);
	}

	const ShipChassisData* getChassisData(const String& shipName) const {
		return chassisData.get(shipName);
	}

	const ShipAppearanceData* getAppearanceData(const String& shipName) const {
		return shipAppearanceData.get(shipName);
	}

	const ShipTurretData* getShipTurretData(const String& shipName, uint32 slot) const {
		return turretData.get(shipName).get(slot);
	}

	const ShipCollisionData* getCollisionData(ShipObject* ship) {
		if (ship == nullptr) {
			return nullptr;
		}

		return shipCollisionData.get(ship->getServerObjectCRC());
	}

	const ShipMissileData* getMissileData(uint32 ammoType) const {
		return missileData.get(ammoType);
	}

	const ShipCountermeasureData* getCountermeasureData(uint32 ammoType) const {
		return countermeasureData.get(ammoType);
	}

	ShipUniqueIdMap* getShipUniqueIdMap() {
		return &shipUniqueIdMap;
	}

private:
	int loadShipSpawnGroups();
	void loadShipComponentObjects(ShipObject* ship);
	ShipControlDevice* createShipControlDevice(ShipObject* ship);

public:
	ShipAiAgent* createAiShip(const String& shipName);
	ShipAiAgent* createAiShip(const String& shipName, uint32 shipCRC);
	ShipObject* createPlayerShip(CreatureObject* owner, const String& shipName, const String& certificationRequired, bool loadComponents = false);

	bool createDeedFromChassis(CreatureObject* owner, ShipChassisComponent* chassisBlueprint, CreatureObject* chassisDealer);

	/**
	* @pre { destructor and destructedObject locked }
	* @post { destructor and destructedObject locked }
	* @param destructorShip pre-locked
	* @param destructedShip pre-locked
	*/

	int notifyDestruction(ShipObject* destructorShip, ShipAiAgent* destructedShip, int condition, bool isCombatAction);

	/**
	 * Sends a sui list box containing information about the structure.
	 * @param creature The creature receiving the report.
	 * @param pobShip The pobShip the report is about.
	 */
	void reportPobShipStatus(CreatureObject* creature, PobShipObject* pobShip, SceneObject* terminal);

	/**
	 * Sends a Sui prompt to the player asking if they wish to delete all the items in their ship.
	 * @param creature The player receiving the prompt.
	 * @param pobShip The POB ship that will have all items deleted.
	 */
	void promptDeleteAllItems(CreatureObject* creature, PobShipObject* pobShip);

	/**
	 * Sends a Sui prompt to the player asking if they want to move the first item in the pob ship to their feet.
	 * @param creature The creature who the item will be moved to.
	 * @param pobShip The structure which holds the items.
	 */
	void promptFindLostItems(CreatureObject* creature, PobShipObject* pobShip);

	/**
	 * Sends a Sui prompt to the player asking if they want rename their ship
	 * @param creature The creature who owns the ship
	 * @param the ship control device
	 */
	void promptNameShip(CreatureObject* creature, ShipControlDevice* shipDevice);

	void reDeedShip(CreatureObject* creature, ShipControlDevice* shipDevice);

	HashTableIterator<uint32, Reference<SpaceSpawnGroup*>> spawnGroupIterator() {
		return spawnGroupMap.iterator();
	}

	SpaceSpawnGroup* getSpaceSpawnGroup(uint32 crc) {
		return spawnGroupMap.get(crc);
	}

	uint16 setShipUniqueID(ShipObject* ship);

	void dropShipUniqueID(ShipObject* ship);

	DroidCommandData* getDroidCommandData(uint32 hashCode) const {
		return DroidCommands.get(hashCode);
	}
};

} // namespace ship
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::ship;

#endif /* SHIPMANAGER_H_ */
