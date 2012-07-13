/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef CITYSPAWNMAP_H_
#define CITYSPAWNMAP_H_

#include "NpcSpawnPoint.h"

namespace server {
namespace zone {
namespace managers {
namespace mission {
namespace spawnmaps {

/**
 * Container for all spawn points in a city and function to find a suitable spawn point.
 */
class CitySpawnMap : public Object, Logger {
protected:
	/**
	 * The coordinates of the city center.
	 */
	Vector3 cityCenter;

	/**
	 * The city radius.
	 */
	float radius;

	/**
	 * The city name.
	 */
	String cityName;

	/**
	 * Vector with all spawn points in the city.
	 */
	Vector<Reference<NpcSpawnPoint* > > npcSpawnMap;

	/**
	 * Checks if a spawn point fulfills certain requirements (spawn type, distance and is free to use).
	 * @param npc the spawn point to check.
	 * @param position the position to check distance from.
	 * @param minDistance the minimum distance between the spawn point and the supplied position.
	 * @param minDistance the maximum distance between the spawn point and the supplied position.
	 * @param spawnType spawn type bitmask that must be fulfilled.
	 * @return true if the spawn fulfills spawn type, distance and is free, false otherwise.
	 */
	bool fulfillsRequirements(NpcSpawnPoint* npc, const Vector3* position, const float minDistance, const float maxDistance, int spawnType) {
		if (npc != NULL) {
			if (((npc->getSpawnType() & spawnType) == spawnType)) {
				float squaredDistance = npc->getPosition()->squaredDistanceTo(*position);
				if ((squaredDistance <= maxDistance * maxDistance) &&
					(squaredDistance >= minDistance * minDistance)) {
					//NPC matches requirements.
					return true;
				}
			}
		}

		return false;
	}

public:
	/**
	 * Read the object from a LuaObject.
	 * @param luaObject the object to load from.
	 */
	void readObject(LuaObject* luaObject) {
		cityName = luaObject->getStringAt(2);
		cityCenter.setX(luaObject->getFloatAt(3));
		cityCenter.setY(luaObject->getFloatAt(4));
		radius = luaObject->getFloatAt(5);
	}

	/**
	 * Get the city center coordinates.
	 * @return city center position.
	 */
	inline Vector3* getCityCenter() {
		return &cityCenter;
	}

	/**
	 * Returns a reandom NPC spawn point of the requested spawn type within the minimum and maximum distance
	 * from the given position if it exists.
	 * @param position The position to measure distance from.
	 * @param spawnType the spawn type bit mask needed on the spawn point.
	 * @param minDistance minimum distance between the spawn point and the given position.
	 * @param maxDistance maximum distance between the spawn point and the given position.
	 * @return random spawn point matching the requirements or NULL if none can be found.
	 */
	NpcSpawnPoint* getRandomNpcSpawnPoint(const Vector3* position, const int spawnType, const float minDistance = 0.0, const float maxDistance = 100000.0) {
		if (npcSpawnMap.size() == 0) {
			return NULL;
		}

		//Try 100 random npc spawn points, return the first that fulfills the requirements.
		int maximumNumberOfTries = (npcSpawnMap.size() / 4) + 1;
		while (maximumNumberOfTries > 0) {
			int npcNumber = System::random(npcSpawnMap.size() - 1);

			NpcSpawnPoint* npc = npcSpawnMap.get(npcNumber);

			if (fulfillsRequirements(npc, position, minDistance, maxDistance, spawnType)) {
				return npc;
			}

			maximumNumberOfTries--;
		}

		//100 random npc spawn points failed, do a full iteration and pick the first npc that match.
		for (int i = 0; i < npcSpawnMap.size(); ++i) {
			NpcSpawnPoint* npc = npcSpawnMap.get(i);

			if (fulfillsRequirements(npc, position, minDistance, maxDistance, spawnType)) {
				return npc;
			}
		}

		//No npc matches the requirements.
		return NULL;
	}

	/**
	 * Add a NPC to the spawn map for the city.
	 * @param npc the NPC to add.
	 */
	void addNpc(Reference<NpcSpawnPoint* > npc) {
		npcSpawnMap.add(npc);
	}

	/**
	 * Finds the nearest NPC spawn point.
	 * @param position the position to search from.
	 * @return the nearest NPC spawn point.
	 */
	NpcSpawnPoint* getNearestNpcSpawnPoint(Vector3* position) {
		float minimumSquaredDistance = 100000.0f * 100000.0f;
		NpcSpawnPoint* nearestNpcSpawnPoint = NULL;
		//Iterate over all spawn points.
		for (int i = 0; i < npcSpawnMap.size(); i++) {
			//Calculate distance between spawn point and supplied position and store the smallest distance.
			float squaredDistance = npcSpawnMap.get(i)->getPosition()->squaredDistanceTo(*position);
			if (minimumSquaredDistance > squaredDistance) {
				minimumSquaredDistance = squaredDistance;
				nearestNpcSpawnPoint = npcSpawnMap.get(i);
			}
		}

		return nearestNpcSpawnPoint;
	}

	/**
	 * Finds a spawn point on a certain location.
	 * @param position the position to search.
	 * @return the spawn point on the position or NULL if none exist.
	 */
	NpcSpawnPoint* findSpawnAt(Vector3* position) {
		for (int i = 0; i < npcSpawnMap.size(); i++) {
			if (npcSpawnMap.get(i)->getPosition()->squaredDistanceTo(*position) < 25.0f) {
				return npcSpawnMap.get(i);
			}
		}

		return NULL;
	}

	/**
	 * Load the object from a stream.
	 * @param stream the stream to load the object from.
	 * @return true if successful.
	 */
	bool parseFromBinaryStream(ObjectInputStream* stream) {
		bool result = cityCenter.parseFromBinaryStream(stream);
		return result & npcSpawnMap.parseFromBinaryStream(stream);
	}

	/**
	 * Write the object to a stream.
	 * @param stream the stream to write the object to.
	 * @return true if successful.
	 */
	bool toBinaryStream(ObjectOutputStream* stream) {
		bool result = cityCenter.toBinaryStream(stream);
		return result & npcSpawnMap.toBinaryStream(stream);
	}

	/**
	 * Saves the spawn points to a file.
	 * @param file the file stream to save the spawn points to.
	 * @param itemsBefore indicates if items has been added before from another city.
	 * @return number of npc spawns written.
	 */
	int saveSpawnPoints(std::ofstream& file, bool itemsBefore) {
		for (int i = 0; i < npcSpawnMap.size(); i++) {
			if (i > 0 || itemsBefore) {
				file << "," << std::endl;
			}
			npcSpawnMap.get(i)->saveSpawnPoint(file);
		}

		return npcSpawnMap.size();
	}
};

} // namespace spawnmaps
} // namespace mission
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::mission::spawnmaps;

#endif /* CITYSPAWNMAP_H_ */
