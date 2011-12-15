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

#ifndef PLANETSPAWNMAP_H_
#define PLANETSPAWNMAP_H_

#include <limits.h>
#include "CitySpawnMap.h"

namespace server {
namespace zone {
namespace managers {
namespace mission {
namespace spawnmaps {

/**
 * Container for all cities on a planet and their mission NPC spawn points.
 */
class PlanetSpawnMap : public Object {
protected:
	/**
	 * Vector of cities.
	 */
	Vector<Reference<CitySpawnMap*> > citySpawnMaps;

	/**
	 * Name of the planet.
	 */
	String planetName;

	/**
	 * Finds the city number closest to the supplied position on the planet.
	 * @param position the position to search from.
	 * @return closest city number or -1 if none is found.
	 */
	int getClosestCityNumber(const Vector3* position) {
		int city = -1;
		float minSquaredDistance = 100000.0 * 100000.0;
		for (int i = 0; i < citySpawnMaps.size(); i++) {
			float squaredDistance = citySpawnMaps.get(i)->getCityCenter()->distanceTo(*position);
			if (minSquaredDistance >= squaredDistance) {
				minSquaredDistance = squaredDistance;
				city = i;
			}
		}

		return city;
	}

public:
	/**
	 * Loads the object from a LuaObject.
	 * @param luaObject object to load from.
	 */
	void readObject(LuaObject* luaObject) {
		planetName = luaObject->getStringField("name");

		LuaObject cities = luaObject->getObjectField("cities");
		for (int numberOfCities = 1; numberOfCities <= cities.getTableSize(); ++numberOfCities) {
			lua_rawgeti(luaObject->getLuaState(), -1, numberOfCities);

			LuaObject luaCityObj(luaObject->getLuaState());

			Reference<CitySpawnMap*> city = new CitySpawnMap();
			city->readObject(&luaCityObj);

			citySpawnMaps.add(city);

			luaCityObj.pop();
		}
		cities.pop();
	}

	/**
	 * Get the planet name.
	 * @return planet name.
	 */
	inline String getPlanetName() {
		return planetName;
	}

	/**
	 * Finds the city closest to the supplied position on the planet.
	 * @param position the position to search from.
	 * @return closest city or NULL if no city is available on the planet.
	 */
	CitySpawnMap* getClosestCity(const Vector3* position) {
		int cityNumber = getClosestCityNumber(position);

		if (cityNumber >= 0) {
			return citySpawnMaps.get(cityNumber);
		} else {
			return NULL;
		}
	}

	CitySpawnMap* getRandomCityNotCloseTo(const Vector3* position) {
		if (citySpawnMaps.size() == 1) {
			//Only one city, return it.
			return citySpawnMaps.get(0);
		} else if (citySpawnMaps.size() > 1) {
			//Get city number of city closest to the supplied position.
			int closestCityNumber = getClosestCityNumber(position);

			//Generate a random city number.
			int randomCityNumber = System::random(citySpawnMaps.size() - 2);
			if (randomCityNumber >= closestCityNumber) {
				//Add one to the city number to skip the closest city.
				randomCityNumber++;
			}

			return citySpawnMaps.get(randomCityNumber);
		} else {
			//No cities.
			return NULL;
		}
	}

	/**
	 * Load the object from a stream.
	 * @param stream the stream to load the object from.
	 * @return true if successful.
	 */
	bool parseFromBinaryStream(ObjectInputStream* stream) {
		bool result = planetName.parseFromBinaryStream(stream);
		return result & citySpawnMaps.parseFromBinaryStream(stream);
	}

	/**
	 * Write the object to a stream.
	 * @param stream the stream to write the object to.
	 * @return true if successful.
	 */
	bool toBinaryStream(ObjectOutputStream* stream) {
		bool result = planetName.toBinaryStream(stream);
		return result & citySpawnMaps.toBinaryStream(stream);
	}
};

} // namespace spawnmaps
} // namespace mission
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::mission::spawnmaps;

#endif /* PLANETSPAWNMAP_H_ */
