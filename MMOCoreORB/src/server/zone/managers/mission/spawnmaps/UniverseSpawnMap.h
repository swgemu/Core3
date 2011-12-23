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

#ifndef UNIVERSESPAWNMAP_H_
#define UNIVERSESPAWNMAP_H_

#include "PlanetSpawnMap.h"

namespace server {
namespace zone {
namespace managers {
namespace mission {
namespace spawnmaps {

/**
 * Container for all planets in the universe and their spawn points.
 */
class UniverseSpawnMap : public Object, Logger {
protected:
	/**
	 * Map for all planets and their spawn points.
	 */
	VectorMap<uint32, Reference<PlanetSpawnMap* > > planetSpawnMaps;

public:
	/**
	 * Read the object from a LuaObject.
	 * @param luaObject the object to load from.
	 */
	void readObject(LuaObject* luaObject) {
		LuaObject planets = luaObject->getObjectField("planets");

		for (int numberOfPlanets = 1; numberOfPlanets <= planets.getTableSize(); ++numberOfPlanets) {
			lua_rawgeti(luaObject->getLuaState(), -1, numberOfPlanets);

			LuaObject luaPlanetObj(luaObject->getLuaState());

			String planetName = luaPlanetObj.getStringField("name");

			Reference<PlanetSpawnMap*> planet = new PlanetSpawnMap();

			if (planetSpawnMaps.contains(planetName.hashCode())) {
				planet = planetSpawnMaps.get(planetName.hashCode());
			}

			planet->readObject(&luaPlanetObj);

			planetSpawnMaps.put(planet->getPlanetName().hashCode(), planet);

			luaPlanetObj.pop();
		}
		planets.pop();
	}

	/**
	 * Add cities from lua object.
	 * @param cities the cities to add.
	 */
	void addCities(LuaObject* cities) {
		for (int numberOfCities = 1; numberOfCities <= cities->getTableSize(); numberOfCities++) {
			lua_rawgeti(cities->getLuaState(), -1, numberOfCities);

			LuaObject luaCityObj(cities->getLuaState());

			String planet = luaCityObj.getStringAt(1);

			Reference<CitySpawnMap* > city = new CitySpawnMap();
			city->readObject(&luaCityObj);

			luaCityObj.pop();

			if (!planetSpawnMaps.contains(planet.hashCode())) {
				Reference<PlanetSpawnMap*> p = new PlanetSpawnMap(planet);
				planetSpawnMaps.put(planet.hashCode(), p);
			}

			planetSpawnMaps.get(planet.hashCode())->addCity(city);
		}
		cities->pop();
	}

	/**
	 * Return a requested planet.
	 * @param planetName the name of the planet.
	 * @return the requested planet.
	 */
	PlanetSpawnMap* getPlanet(const uint32 planetCRC) {
		return planetSpawnMaps.get(planetCRC);
	}

	/**
	 * Load the object from a stream.
	 * @param stream the stream to load the object from.
	 * @return true if successful.
	 */
	bool parseFromBinaryStream(ObjectInputStream* stream) {
		return planetSpawnMaps.parseFromBinaryStream(stream);
	}

	/**
	 * Write the object to a stream.
	 * @param stream the stream to write the object to.
	 * @return true if successful.
	 */
	bool toBinaryStream(ObjectOutputStream* stream) {
		return planetSpawnMaps.toBinaryStream(stream);
	}

	/**
	 * Saves the spawn points to a file.
	 * @param file the file stream to save the spawn points to.
	 */
	void saveSpawnPoints(std::ofstream& file) {
		for (int i = 0; i < planetSpawnMaps.size(); i++) {
			planetSpawnMaps.get(i)->saveSpawnPoints(file);
		}
	}
};

} // namespace spawnmaps
} // namespace mission
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::mission::spawnmaps;

#endif /* UNIVERSESPAWNMAP_H_ */
