/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MISSIONNPCSPAWNMAP_H_
#define MISSIONNPCSPAWNMAP_H_

#include "engine/util/u3d/Vector3.h"
#include "engine/log/Logger.h"
#include "UniverseSpawnMap.h"
#include "engine/core/ManagedObject.h"

namespace server {
namespace zone {
namespace managers {
namespace mission {
namespace spawnmaps {

/**
 * Class implementing methods to find a suitable spawn point for mission NPC's.
 */
class MissionNpcSpawnMap : public ManagedObject, Logger {
protected:
	/**
	 * Spawn points in the world.
	 */
	UniverseSpawnMap spawnMap;

public:
	/**
	 * Constructor.
	 */
	MissionNpcSpawnMap() : ManagedObject(), Logger("MissionNpcSpawnMap") {}
	
	/**
	 * Destructor.
	 */
	~MissionNpcSpawnMap() {}
	
	/**
	 * Load all spawn points from the lua script file.
	 */
	void loadSpawnPointsFromLua();

	/**
	 * Find a random spawn point on the requested planet within the minimum and maximum distance from the
	 * supplied position of the requested spawn type.
	 * @param planetCRC the CRC of the name of the planet to find a spawn on.
	 * @param position the position to measure distance from/to.
	 * @param spawnType the spawn type bitmask required for the spawn.
	 * @param minDistance the minimum distance between the spawn point and the position supplied.
	 * @param minDistance the maximum distance between the spawn point and the position supplied.
	 * @return random npc matching requirements or NULL if none could be found.
	 */
	NpcSpawnPoint* getRandomNpcSpawnPoint(const uint32 planetCRC, const Vector3* position, const int spawnType, const float minDistance, const float maxDistance);

	/**
	 * Get the center coordinates of a random city not close to the supplied coordinates.
	 * @param planetCRC the CRC of the name of the planet to find a city on.
	 * @param notCloseToPosition the city closest to this position will not be returned unless it is the only city.
	 * @return random city not close to the coordinates.
	 */
	Vector3* getRandomCityCoordinates(const uint32 planetCRC, const Vector3* notCloseToPosition);

	/**
	 * Add a spawn point to the specified planet.
	 * @param planetCRC the CRC of the planet name.
	 * @param npc the NPC to add.
	 * @return the added NPC spawn point or the nearest existing spawn point if the new is within minimum distance.
	 */
	NpcSpawnPoint* addSpawnPoint(uint32 planetCRC, Reference<NpcSpawnPoint* > npc);

	/**
	 * Finds a spawn point on a certain location.
	 * @param planetCRC the CRC of the planet name.
	 * @param position the position to search.
	 * @return the spawn point on the position or NULL if none exist.
	 */
	NpcSpawnPoint* findSpawnAt(uint32 planetCRC, Vector3* position);

	/**
	 * Read the object from a stream.
	 * @param stream stream to read from.
	 * @return true if successful.
	 */
	bool parseFromBinaryStream(ObjectInputStream* stream) {
		return spawnMap.parseFromBinaryStream(stream);
	}

	/**
	 * Write the object to a stream.
	 * @param stream stream to write to.
	 * @param true if successful.
	 */
	bool toBinaryStream(ObjectOutputStream* stream) {
		return spawnMap.toBinaryStream(stream);
	}

	/**
	 * Save all spawn points to lua script.
	 */
	void saveSpawnPoints();
};

} // namespace spawnmaps
} // namespace mission
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::mission::spawnmaps;

#endif /* MISSIONNPCSPAWNMAP_H_ */
