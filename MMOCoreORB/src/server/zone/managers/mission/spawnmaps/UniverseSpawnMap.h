/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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
