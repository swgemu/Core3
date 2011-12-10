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

#ifndef MISSIONNPCSPAWNMAP_H_
#define MISSIONNPCSPAWNMAP_H_

#include "engine/util/u3d/Vector3.h"
#include "engine/log/Logger.h"
#include "UniverseSpawnMap.h"

namespace server {
namespace zone {
namespace managers {
namespace mission {
namespace spawnmaps {

/**
 * Class implementing methods to find a suitable spawn point for mission NPC's.
 */
class MissionNpcSpawnMap : public Logger {
protected:
	/**
	 * Spawn points in the world.
	 */
	UniverseSpawnMap spawnMap;

public:
	/**
	 * Constructor.
	 */
	MissionNpcSpawnMap() : Logger("MissionNpcSpawnMap") {}
	
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
	 */
	NpcSpawnPoint* getRandomNpcSpawnPoint(const String& planetName, const Vector3* position, const int spawnType, const float minDistance, const float maxDistance);

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
};

} // namespace spawnmaps
} // namespace mission
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::mission::spawnmaps;

#endif /* MISSIONNPCSPAWNMAP_H_ */
