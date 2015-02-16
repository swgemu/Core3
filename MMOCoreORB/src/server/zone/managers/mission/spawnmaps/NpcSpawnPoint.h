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

#ifndef NPCSPAWNPOINT_H_
#define NPCSPAWNPOINT_H_

#include "engine/util/u3d/Vector3.h"
#include "engine/util/u3d/Quaternion.h"
#include "engine/log/Logger.h"
#include "engine/lua/Lua.h"
#include "engine/orb/object/DistributedObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/terrain/TerrainManager.h"
#include <iostream>
#include <fstream>

namespace server {
namespace zone {
namespace managers {
namespace mission {
namespace spawnmaps {
namespace events {

class DespawnMissionNpcTask;

} // namespace events
} // namespace spawnmaps
} // namespace mission
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::mission::spawnmaps::events;

namespace server {
namespace zone {
namespace managers {
namespace mission {
namespace spawnmaps {

/**
 * Container for a NPC spawn point usable in missions.
 */
class NpcSpawnPoint : public DistributedObject, public Logger {
protected:
	/**
	 * The position on the planet.
	 */
	Vector3 position;

	/**
	 * The direction the npc faces.
	 */
	Quaternion direction;

	/**
	 * Spawn type mask.
	 */
	int spawnType;

	/**
	 * Indicator if the spawn is in use or not (i.e. free to use in a new mission).
	 */
	int inUseByNumberOfMissions;

	ManagedReference<AiAgent*> npc;

	Reference<DespawnMissionNpcTask*> despawnMissionNpcTask;

	bool npcSpawned;

public:
	
	enum {
		NOSPAWN        = 1, // Spawn type no spawn.
		NEUTRALSPAWN   = 2, // Spawn type neutral spawn.
		IMPERIALSPAWN  = 4, // Spawn type imperial spawn.
		REBELSPAWN     = 8, // Spawn type rebel spawn.
		BHTARGETSPAWN  = 16 //Spawn type bh target.
	};
	
	/**
	 * Default constructor.
	 */
	NpcSpawnPoint();

	/**
	 * Constructor for dynamic NPC spawn point creation.
	 * @param player Player creature object to get position and direction from.
	 * @param spawnTypes string containing the spawn types for the spawn point.
	 */
	NpcSpawnPoint(CreatureObject* player, const String& spawnTypes);

	/**
	 * Loads the object from a lua script file.
	 * @param luaObject the object to load the spawn point from.
	 */
	void readObject(LuaObject* luaObject);

	/**
	 * Get the in use information.
	 * @return true if spawn already is in use, false if it is free to use.
	 */
	inline int getInUse() {
		return inUseByNumberOfMissions;
	}

	/**
	 * Get the spawn type bit mask.
	 * @return the spawn type bit mask.
	 */
	inline int getSpawnType() {
		return spawnType;
	}

	/**
	 * Get the position for the spawn on the planet.
	 * @return the position for the spawn on the planet.
	 */
	inline Vector3* getPosition() {
		return &position;
	}

	/**
	 * Get the direction the spawn point npc should face.
	 * @return the direction the spawn point npc should face.
	 */
	inline Quaternion* getDirection() {
		return &direction;
	}

	/**
	 * Load the object from a stream.
	 * @param stream stream to load from.
	 * @return true if successful.
	 */
	bool parseFromBinaryStream(ObjectInputStream* stream);

	/**
	 * Write the spawn point to a stream.
	 * @param stream stream to write to.
	 * @return true if successful.
	 */
	bool toBinaryStream(ObjectOutputStream* stream);

	/**
	 * Saves the spawn points to a file.
	 * @param file the file stream to save the spawn points to.
	 */
	void saveSpawnPoint(std::ofstream& file) {
		file << "\t\t{ " << position.getX() << ", " << position.getY();
		file << ", " << direction.getRadians() << ", " << spawnType << " }";
	}

	String toString() {
		return "NpcSpawnPoint at " + position.toString() + " of spawntype " + String::valueOf(spawnType) + " is " + (inUseByNumberOfMissions > 0 ? " in use." : "free.");
	}

	void allocateNpc(TerrainManager* terrainManager, CreatureManager* creatureManager);

	void freeNpc(Reference<MissionManager*> missionManager);

	void despawnNpc();

};

} // namespace spawnmaps
} // namespace mission
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::mission::spawnmaps;

#endif /* NPCSPAWNPOINT_H_ */
